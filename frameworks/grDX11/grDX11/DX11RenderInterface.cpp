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

#include "DX11RenderInterface.h"
#include "PipelineObject.h"
#include "PipelineRenderObject.h"
#include "RenderTargetSet.h"
#include "ImageRenderData.h"
#include "CmdList.h"
#include "DX11MeshRenderer.h"
#include "ConstBuffer.h"
#include "Sampler.h"

#include <gtlMemory/RcObject.h>
#include <grImg/Image.h>
#include <grRenderCore/Mesh/Mesh.h>
#include <grRenderCore/ConstantBuffer/ConstantBuffer.h>
#include <grRenderCore/RenderTarget/RenderTargetSet.h>
#include <nxfResource/ResourceManager.h>
#include <nxfSerialization/NXFFileReader.h>
#include <dxgi1_3.h>

typedef HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY_1)(REFIID riid, void **ppFactory);
typedef HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY_2)(UINT flags, REFIID riid, void **ppFactory);
typedef HRESULT(WINAPI *PFN_D3D11_CREATE_DEVICE)(
    IDXGIAdapter *pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL *pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    ID3D11Device **ppDevice,
    D3D_FEATURE_LEVEL *pFeatureLevel,
    ID3D11DeviceContext **ppImmediateContext);

grDX11::DX11RenderInterface::DX11RenderInterface()
    : m_videoOutputManager(this),
      m_constBufferPool(this),
      m_rasterizerStateCache(this),
      m_dxgiLib(nullptr),
      m_d3d11Lib(nullptr) {
}

grDX11::DX11RenderInterface::~DX11RenderInterface() {
    if (m_dxgiLib) FreeLibrary(m_dxgiLib);
    if (m_d3d11Lib) FreeLibrary(m_d3d11Lib);
}

void grDX11::DX11RenderInterface::initialize() {
    using Microsoft::WRL::ComPtr;

    RenderInterface::initialize();

    m_dxgiLib = LoadLibraryW(L"dxgi.dll");
    if (!m_dxgiLib) {
        GR_FATAL(GTXT("dxgi.dll not found; is Direct3D 11 supported on your system?"));
    }
    HRESULT hres               = S_OK;
    auto pfnCreateDxgiFactory2 = (PFN_CREATE_DXGI_FACTORY_2)GetProcAddress(m_dxgiLib, "CreateDXGIFactory2");
    if (pfnCreateDxgiFactory2) {
        UINT factoryFlags = 0;
#ifdef _DEBUG
        factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
        hres = pfnCreateDxgiFactory2(factoryFlags, IID_PPV_ARGS(&m_dxgiFactory));
    } else {
        auto pfnCreateDxgiFactory1 = (PFN_CREATE_DXGI_FACTORY_1)GetProcAddress(m_dxgiLib, "CreateDXGIFactory1");
        if (!pfnCreateDxgiFactory1) {
            FreeLibrary(m_dxgiLib);
            m_dxgiLib = nullptr;
            GR_FATAL(GTXT("CreateDXGIFactory1 not found; is DXGI 1.1 supported on your system?"));
        }
        hres = pfnCreateDxgiFactory1(IID_PPV_ARGS(&m_dxgiFactory));
    }

    if (FAILED(hres)) {
        FreeLibrary(m_dxgiLib);
        m_dxgiLib = nullptr;
        GR_FATAL(GTXT("Failed to create DXGI factory; is DXGI 1.1 supported on your system?"));
    }

    ComPtr<IDXGIAdapter1> adapter = nullptr;

    hres = m_dxgiFactory->EnumAdapters1(0, &adapter); // TODO: adapter selection
    if (hres == DXGI_ERROR_NOT_FOUND) {
        FreeLibrary(m_dxgiLib);
        m_dxgiLib = nullptr;
        GR_FATAL(GTXT("No DXGI adapter found. Check your graphics card drivers."));
    }
    if (FAILED(hres)) {
        FreeLibrary(m_dxgiLib);
        m_dxgiLib = nullptr;
        GR_FATAL(GTXT("Failed to enumerate DXGI adapters"));
    }

    DXGI_ADAPTER_DESC1 desc;
    hres = adapter->GetDesc1(&desc);
    if (FAILED(hres)) {
        FreeLibrary(m_dxgiLib);
        m_dxgiLib = nullptr;
        GR_FATAL(GTXT("Failed to get DXGI adapter description"));
    }
    GR_INFO(GTXT("DXGI Adapter: %ls"), desc.Description);

    m_d3d11Lib = LoadLibraryW(L"d3d11.dll");
    if (!m_d3d11Lib) {
        FreeLibrary(m_dxgiLib);
        m_dxgiLib = nullptr;
        GR_FATAL(GTXT("d3d11.dll not found; is Direct3D 11 supported on your system?"));
    }

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_10_0,
    };

    auto pfnD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(m_d3d11Lib, "D3D11CreateDevice");

    UINT createFlags = 0;
#ifdef _DEBUG
    createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;

    hres = pfnD3D11CreateDevice(
        adapter.Get(),
        D3D_DRIVER_TYPE_UNKNOWN,
        nullptr,     // no sw rasterizer
        createFlags, // flags
        featureLevels,
        std::size(featureLevels),
        D3D11_SDK_VERSION,
        &m_device,
        &featureLevel,
        &m_immediateContext);
    if (FAILED(hres)) {
        FreeLibrary(m_dxgiLib);
        FreeLibrary(m_d3d11Lib);
        m_dxgiLib  = nullptr;
        m_d3d11Lib = nullptr;
        GR_FATAL(GTXT("Could not create D3D11 device; error 0x%08x"), hres);
    }

    GR_INFO(GTXT("D3D Feature Level: %d_%d"), featureLevel >> 12, featureLevel & 0xFFF);

    loadPipelines();
}

void grDX11::DX11RenderInterface::destroy() {
    gtlDelete this;
}

void grDX11::DX11RenderInterface::loadPipelines() {
    nxfResourceManager *resMan = nxf_getRM();

    gnaPointer<nxfInputStream> stream;
    gnaStatus status = resMan->get_resourceStream(GTXT("/shaders/dx11/main.nxf"), stream);
    if (!status) {
        GR_FATAL(GTXT("Could not initialize DX11 render interface; cannot load pipeline file - error %ls"),
            status.get_errorMessage().toCString());
    }

    nxfSerialization::NXFFileReader reader(stream);
    status = reader.readNXFFile();
    if (!status) {
        GR_FATAL(GTXT("Could not initialize DX11 render interface; cannot parse pipeline file - error %ls"),
            status.get_errorMessage().toCString());
    }
    m_pipelineLibrary = reader.getRootObject<grRenderCore::PipelineLibrary>();
    for (auto &pipeline : m_pipelineLibrary->getPipelines()) {
        loadPipeline(pipeline.second.cast<grDX11::PipelineObject>());
    }
}

void grDX11::DX11RenderInterface::loadPipeline(gnaWeakPointer<grDX11::PipelineObject> pipeline) {
    auto *renderObject = gtlNew grDX11::PipelineRenderObject(this);
    gnaStatus status   = renderObject->initialize(pipeline);
    if (!status) {
        gtlDelete renderObject;

        GR_FATAL(GTXT("Could not initialize pipeline: error %ls"), status.get_errorMessage().toCString());
    }

    pipeline->set_renderObject(renderObject);
    m_loadedPipelines.push_back(pipeline);
}


gnaWeakPointer<grRenderCore::PipelineLibrary> grDX11::DX11RenderInterface::get_pipelineLibrary() {
    return m_pipelineLibrary;
}

void grDX11::DX11RenderInterface::registerTexture(gnaPointer<grImg::Image> image) {
    if (image->m_rendererData) return; // already initialized

    auto *renderData      = gtlNew ImageRenderData(this, image);
    image->m_rendererData = renderData;
    renderData->loadToGPU();
}

void grDX11::DX11RenderInterface::registerOrUpdateConstantBuffer(gnaPointer<grRenderCore::ConstantBuffer> cb) {
    gnaPointer<ConstBufferRenderData> renderData = cb->m_rendererData.cast<ConstBufferRenderData>();
    if (!renderData) {
        renderData         = gnaNew<ConstBufferRenderData>(this, cb);
        cb->m_rendererData = renderData;
    }

    renderData->loadToGPU();
}

void grDX11::DX11RenderInterface::registerOrUpdateMesh(gnaPointer<grRenderCore::Mesh> mesh, uint32_t flags) {
    gnaPointer<MeshRenderer> renderData = mesh->renderer.cast<MeshRenderer>();
    if (!renderData) {
        renderData     = gnaNew<MeshRenderer>(this, mesh);
        mesh->renderer = renderData;
    }

    renderData->loadToGPU(flags);
}

void grDX11::DX11RenderInterface::registerOrUpdateInstancedMesh(gnaPointer<grRenderCore::InstancedMesh> mesh, uint32_t flags) {
    gnaPointer<InstancedMeshRenderer> renderData = mesh->renderer.cast<InstancedMeshRenderer>();
    if (!renderData) {
        renderData     = gnaNew<InstancedMeshRenderer>(this, mesh);
        mesh->renderer = renderData;
    }

    renderData->loadToGPU(flags);
}

gnaPointer<grRenderCore::CmdListEmitter> grDX11::DX11RenderInterface::createCmdListEmitter() {
    return gnaNew<CmdListEmitter>(this);
}

gnaPointer<grRenderCore::RenderTargetSetBuilder> grDX11::DX11RenderInterface::createRTSBuilder() {
    return gnaNew<RenderTargetSetBuilder>(this);
}

void grDX11::DX11RenderInterface::executeRenderPass(gnaWeakPointer<grRenderCore::CmdList> cmdList) {
    if (cmdList) {
        cmdList->execute();
    }
}

grRenderCore::VideoOutputManager *grDX11::DX11RenderInterface::get_videoOutputManager() {
    return &m_videoOutputManager;
}

gtlMath2::Matrix4x4f grDX11::DX11RenderInterface::convertProjectionMatrix(const gtlMath2::Matrix4x4f &matrix, bool isForTexture) {
    return matrix;
}

gnaPointer<grRenderCore::Sampler> grDX11::DX11RenderInterface::findSampler(const grRenderCore::SamplerProperties &properties) {
    auto it = m_samplerCache.find(properties);
    if (it == m_samplerCache.end()) {
        return m_samplerCache[properties] = gnaNew<Sampler>(this, properties);
    }
    return it->second;
}
