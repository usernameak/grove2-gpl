// GroveEngine 2
// Copyright (C) 2020-2025 usernameak
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3, as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <grMain.h>
#include <gtlModule/ModuleLoader.h>
#include <grDX11/DX11Module.h>
#include <nlohmann/json.hpp>

#include <string_view>

#include <gtlUtil/CommandLineParser.h>
#include <nxfResource/ResourceManager.h>
#include <nxfResource/RMEx/ExtendedResourceManager.h>
#include <nxfResource/Archive/GPKArchive.h>
#include <nxfResource/ResourceConfig.h>
#include <nxfSerialization/NXFFileWriter.h>
#include <nxfUtil/BinaryResource.h>

#include <grRenderCore/Pipeline/PipelineLibrary.h>
#include <grDX11/PipelineObject.h>

#include <d3dcompiler.h>
#include <ranges>
#include <wrl/client.h>

namespace dx11plcc {
    class IncludeHandler final : public ID3DInclude {
        std::unordered_map<LPCVOID, gtl::String> paths;

    public:
        STDMETHOD(Open)
        (D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) override {
            if (IncludeType == D3D_INCLUDE_LOCAL) {
                auto it = paths.find(pParentData);
                if (it != paths.end()) {
                    HRESULT hr = Open(nxfResourceManager::parentPath(it->second), pFileName, ppData, pBytes);
                    if (SUCCEEDED(hr)) {
                        return hr;
                    }
                }
            }
            HRESULT hr = Open(GTXT("/shaders/dx11/pipeline"), pFileName, ppData, pBytes);
            return hr;
        }

        STDMETHOD(Close)
        (LPCVOID pData) override {
            paths.erase(pData);

            gtlDeleteArray static_cast<const unsigned char *>(pData);

            return S_OK;
        }

        HRESULT Open(const gtl::String &path, LPCVOID *ppData, UINT *pBytes) {
            auto stream = nxf_getRM()->get_resourceStream(path);
            if (!stream) {
                return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
            }

            gnaPointer<nxfBinaryResource> res;
            gnaStatus status = stream->readAll(res);
            if (!status) {
                return E_FAIL;
            }

            auto *buf = gtlNew unsigned char[res->size];
            memcpy(buf, res->data, res->size);

            paths[buf] = path;

            *ppData = buf;
            *pBytes = res->size;

            return S_OK;
        }

    private:
        HRESULT Open(const gtl::String &parentPath, LPCSTR pFileName, LPCVOID *ppData, UINT *pBytes) {
            gtl::String path = parentPath;
            path += GTXT('/');
            path += gtl::String(pFileName, gtl::String::S_CHARSET_UTF8);

            return Open(path, ppData, pBytes);
        }
    };
}

static gnaStatus readJSONFromFile(const gtl::String &path, nlohmann::json &result) {
    using json = nlohmann::json;

    gnaPointer<nxfInputStream> stream;
    GNA_CHECK_STATUS(nxf_getRM()->get_resourceStream(path, stream));

    gnaPointer<nxfBinaryResource> binary;
    GNA_CHECK_STATUS(stream->readAll(binary));

    try {
        result = json::parse(std::string_view((const char *)binary->data, binary->size));
    } catch (const json::parse_error &e) {
        return { GNA_E_FAILED, e.what() };
    }

    return GNA_E_OK;
}

static gnaPointer<nxfBinaryResource> compileShader(
    const gtl::String &path,
    const char *shader_target,
    const std::unordered_map<gtl::AString, gtl::AString> &compileDefinitions = {}) {

    LPCVOID shaderData;
    UINT shaderBytes;

    gtl::AString aShaderPath(GTXT("Z:\\") + path, gtl::AString::S_CHARSET_UTF8);

    dx11plcc::IncludeHandler includeHandler;
    if (FAILED(includeHandler.Open(path, &shaderData, &shaderBytes))) {
        GR_FATAL(GTXT("Cannot open %ls"), path.toCString());
    }

    Microsoft::WRL::ComPtr<ID3DBlob> bytecode      = nullptr,
                                     errorMessages = nullptr;

    D3D_SHADER_MACRO *macros = nullptr;
    if (!compileDefinitions.empty()) {
        macros = gtlNew D3D_SHADER_MACRO[compileDefinitions.size() + 1];

        int i = 0;
        for (const auto &[key, value] : compileDefinitions) {
            macros[i].Name       = key.toCString();
            macros[i].Definition = value.toCString();
            i++;
        }

        auto &terminator      = macros[compileDefinitions.size()];
        terminator.Name       = nullptr;
        terminator.Definition = nullptr;
    }

    HRESULT compileStatus = D3DCompile2(
        shaderData,
        shaderBytes,
        aShaderPath.toCString(),
        macros,
        &includeHandler,
        "main",        // entrypoint name
        shader_target, // target model
        D3DCOMPILE_DEBUG |
            D3DCOMPILE_OPTIMIZATION_LEVEL2 |
            D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, // compile flags
        0,                                    // fx flags
        0, nullptr, 0,                        // secondary data
        &bytecode,
        &errorMessages);

    gtlDeleteArray macros;

    if (errorMessages) {
        gtl::String sErrorMessages(
            static_cast<const char *>(errorMessages->GetBufferPointer()),
            gtl::String::S_CHARSET_NATIVE);
        GR_WARNING(GTXT("%ls"), sErrorMessages.toCString());
    }
    if (FAILED(compileStatus)) {
        GR_FATAL(GTXT("Compilation failed. See above for an error log."));
    }
    return gnaNew<nxfBinaryResource>(bytecode->GetBufferSize(), bytecode->GetBufferPointer());
}

template <typename V>
    requires(std::ranges::sized_range<V> && std::ranges::random_access_range<V>)
class SubsetView : public std::ranges::view_interface<SubsetView<V>> {
    V m_base;

    class SubsetIterator : public std::forward_iterator_tag {
        V m_baseRange;
        size_t m_bitmask;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type      = std::vector<std::ranges::range_value_t<V>>;

        SubsetIterator() : m_bitmask(0) {}

        SubsetIterator(V baseRange, size_t bitmask)
            : m_baseRange(std::move(baseRange)),
              m_bitmask(bitmask) {}

        value_type operator*() const {
            value_type vec;
            for (size_t i = 0; i < CHAR_BIT * sizeof(size_t); i++) {
                if ((m_bitmask >> i) & 1u) {
                    vec.push_back(*(m_baseRange.begin() + i));
                }
            }
            return vec;
        }

        SubsetIterator &operator++() {
            m_bitmask++;
            return *this;
        }

        SubsetIterator operator++(int) {
            SubsetIterator newIter = SubsetIterator(m_baseRange, m_bitmask);
            m_bitmask++;
            return newIter;
        }

        bool operator==(const SubsetIterator &other) const {
            if (other.m_baseRange.begin() != m_baseRange.begin()) return false;
            if (other.m_bitmask != m_bitmask) return false;
            return true;
        }
    };

public:
    explicit SubsetView(V base) : m_base(std::move(base)) {
        assert(std::ranges::size(m_base) < CHAR_BIT * sizeof(size_t));
    }

    auto begin() const {
        return SubsetIterator(m_base, 0);
    }

    auto end() const {
        return SubsetIterator(m_base, static_cast<size_t>(1) << std::ranges::size(m_base));
    }
};

int GR_MAIN_CALLCONV grMain(int argc, gtl::WIDECHAR *wargv[]) {
    using json = nlohmann::json;

    grLog_useWindowsDebugOutput = false;

    gnaSingleton<gtlModuleLoader>()->loadModule(&GROVE2_MODULE_INFO(grDX11));

    gtlUtil::CommandLineParser parser;

    auto &resConfArgument    = parser.registerValueArgument(GTXT("-res-conf"));
    auto &sourceFileArgument = parser.registerValueArgument(GTXT("-source-file"));
    parser.parse(argc, wargv);

    if (!resConfArgument) {
        GR_FATAL(GTXT("Resource config is not specified"));
    }
    if (!sourceFileArgument) {
        GR_FATAL(GTXT("Source file is not specified"));
    }
    nxfResource::ResourceConfig resConf;
    gnaStatus status = resConf.loadConfig(*resConfArgument);
    if (!status) {
        GR_FATAL(GTXT("Error reading resource config, %ls"), status.get_errorMessage().toCString());
    }
    nxf_setRM(resConf.buildResourceManager());

    json jsonData_;
    status = readJSONFromFile(*sourceFileArgument, jsonData_);
    if (!status) {
        GR_FATAL(GTXT("Error reading source file, %ls"), status.get_errorMessage().toCString());
    }

    const json &jsonData = jsonData_;

    auto pipelineLibrary = gnaNew<grRenderCore::PipelineLibrary>();

    const auto &pipelinesTable = jsonData.at("Pipelines");

    for (const auto &[key, value] : pipelinesTable.items()) {
        const auto &pipelineTable = value;
        if (!pipelineTable.is_object()) {
            GR_FATAL(GTXT("`Pipelines` contains a non-table"));
        }

        auto vertexShaderProp = pipelineTable.find("VertexShader");
        if (vertexShaderProp == pipelineTable.end()) {
            GR_FATAL(GTXT("Vertex shader is not specified"));
        }
        gtl::String vertexShaderPath = vertexShaderProp->get<std::string>().c_str();

        auto pixelShaderProp        = pipelineTable.find("PixelShader");
        gtl::String pixelShaderPath = pixelShaderProp != pipelineTable.end()
                                        ? pixelShaderProp->get<std::string>().c_str()
                                        : gtl::String();

        std::vector<grRenderCore::BlendMode> blendModes;
        std::vector<gtl::AString> keywords;
        std::vector<grRenderCore::VertexFormatAttribute> optionalVertexAttributes;
        std::vector<grRenderCore::VertexFormatAttribute> requiredVertexAttributes;
        auto cullMode    = grDX11::PipelineObject::CULL_MODE_BACK;
        bool depthTest   = true;
        bool scissorTest = false;

        auto blendModesProp = pipelineTable.find("BlendModes");
        if (blendModesProp != pipelineTable.end()) {
            for (auto &blendModeValue : *blendModesProp) {
                gtl::AString blendModeName = blendModeValue.get<std::string>().c_str();
                if (blendModeName == "Normal") {
                    blendModes.push_back(grRenderCore::BLEND_MODE_NORMAL);
                } else if (blendModeName == "Translucent") {
                    blendModes.push_back(grRenderCore::BLEND_MODE_TRANSLUCENT);
                } else {
                    GR_FATAL(GTXT("Unsupported blend mode %hs specified"), blendModeName.toCString());
                }
            }
        } else {
            blendModes.push_back(grRenderCore::BLEND_MODE_NORMAL);
        }

        auto keywordsProp = pipelineTable.find("Keywords");
        if (keywordsProp != pipelineTable.end()) {
            for (auto &keywordValue : *keywordsProp) {
                gtl::AString keywordName = keywordValue.get<std::string>().c_str();
                keywords.push_back(keywordName);
            }
        }

        auto vertexAttributesProp = pipelineTable.find("VertexAttributes");
        if (vertexAttributesProp != pipelineTable.end()) {
            for (auto &[name, vertexAttributeValue] : vertexAttributesProp->items()) {
                gtl::PooledAString aName = name.c_str();

                auto vfa = grRenderCore::interpretVFAName(aName);
                if (vfa == grRenderCore::VFA_INVALID) {
                    GR_FATAL(GTXT("Invalid vertex format attribute `%hs`"), aName.toCString());
                }

                bool required     = false;
                auto requiredProp = vertexAttributeValue.find("required");
                if (requiredProp != vertexAttributeValue.end()) {
                    required = requiredProp->get<bool>();
                }
                if (required) {
                    requiredVertexAttributes.push_back(vfa);
                } else {
                    optionalVertexAttributes.push_back(vfa);
                }
            }
        }

        auto cullModeProp = pipelineTable.find("CullMode");
        if (cullModeProp != pipelineTable.end()) {
            gtl::AString cullModeName = cullModeProp->get<std::string>().c_str();
            if (cullModeName == "Back") {
                cullMode = grDX11::PipelineObject::CULL_MODE_BACK;
            } else if (cullModeName == "Front") {
                cullMode = grDX11::PipelineObject::CULL_MODE_FRONT;
            } else if (cullModeName == "None") {
                cullMode = grDX11::PipelineObject::CULL_MODE_NONE;
            } else {
                GR_FATAL(GTXT("Unsupported cull mode %hs specified"), cullModeName.toCString());
            }
        }

        auto depthTestProp = pipelineTable.find("DepthTest");
        if (depthTestProp != pipelineTable.end()) {
            depthTest = depthTestProp->get<bool>();
        }

        auto scissorTestProp = pipelineTable.find("ScissorTest");
        if (scissorTestProp != pipelineTable.end()) {
            scissorTest = scissorTestProp->get<bool>();
        }

        std::ranges::ref_view optionalVAttrRv(optionalVertexAttributes);
        std::ranges::ref_view keywordRv(keywords);
        SubsetView optionalVAttrSubsets(optionalVAttrRv);
        SubsetView keywordSubsets(keywordRv);

        for (auto keywordSubset : keywordSubsets) {
            for (auto optionalVAttrSubset : optionalVAttrSubsets) {
                for (grRenderCore::BlendMode blendMode : blendModes) {
                    std::underlying_type_t<grRenderCore::VertexFormatFlags> vertexFormat = 0;
                    std::unordered_map<gtl::AString, gtl::AString> compileDefinitions;

                    for (const auto &str : keywordSubset) {
                        compileDefinitions[str] = "1";
                    }

                    for (auto vfa : requiredVertexAttributes) {
                        vertexFormat |= vertexFormatAttribToFlag(vfa);

                        gtl::AString defName = "GR_VERTEXFORMAT_";
                        defName += gtl::AString(toVFAName(vfa));
                        compileDefinitions[defName] = "1";
                    }

                    for (auto vfa : optionalVAttrSubset) {
                        vertexFormat |= vertexFormatAttribToFlag(vfa);

                        gtl::AString defName = "GR_VERTEXFORMAT_";
                        defName += gtl::AString(toVFAName(vfa));
                        compileDefinitions[defName] = "1";
                    }

                    auto pipeline = gnaNew<grDX11::PipelineObject>();
                    pipeline->set_name(key.data());
                    pipeline->set_vertexFormat(vertexFormat);
                    pipeline->set_blendMode(blendMode);
                    pipeline->set_depthTest(depthTest);
                    pipeline->set_scissorTest(scissorTest);
                    pipeline->set_cullMode(cullMode);

                    std::unordered_set<gtl::Name> keywordSet;
                    keywordSet.insert(keywordSubset.begin(), keywordSubset.end());

                    pipeline->set_keywords(keywordSet);

                    auto vertexShaderBytes = compileShader(vertexShaderPath, "vs_4_0", compileDefinitions);
                    pipeline->set_vertexShaderBinary(vertexShaderBytes);

                    if (!pixelShaderPath.empty()) {
                        auto pixelShaderBytes = compileShader(pixelShaderPath, "ps_4_0", compileDefinitions);
                        pipeline->set_pixelShaderBinary(pixelShaderBytes);
                    }

                    pipelineLibrary->addPipeline(pipeline);
                }
            }
        }
    }

    auto *mutRM = dynamic_cast<nxfMutableResourceManager *>(nxf_getRM());
    if (!mutRM) {
        GR_FATAL(GTXT("Resource manager is immutable!"));
    }

    auto stream = mutRM->get_resourceOutputStream(GTXT("/shaders/dx11/main.nxf"));
    if (!stream) {
        GR_FATAL(GTXT("Cannot open output stream."));
    }

    nxfSerialization::NXFFileWriter writer(stream);
    status = writer.writeNXFFile(pipelineLibrary);
    if (!status) {
        GR_FATAL(GTXT("Cannot write output file - %ls."), status.get_errorMessage().toCString());
    }

    GR_INFO(GTXT("Compilation successful!"));

    return 0;
}
