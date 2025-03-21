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

#include "VideoOutputManager.h"

#include "DX11RenderInterface.h"
#include <grRenderCore/RenderTarget/RenderTargetSet.h>
#include <dxgi1_2.h>
#include <dxgi1_4.h>

namespace grDX11 {
    class DX11VideoOutput : public grRenderCore::VideoOutput {
        DX11RenderInterface *m_renderInterface;
        HWND m_hwnd;
        Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backbufferTexture;
        gnaPointer<grRenderCore::RenderTargetSet> m_renderTargetSet;
        gnaPointer<grImg::Image> m_backbufferImage;
        grDimension m_currentBackbuffersSize;
        grDimension m_newBackbuffersSize;

    public:
        DX11VideoOutput(DX11RenderInterface *renderInterface, HWND hwnd)
            : m_renderInterface(renderInterface),
              m_hwnd(hwnd),
              m_swapChain(nullptr),
              m_currentBackbuffersSize{ 0, 0 } {}

        void initialize() {
            DXGI_SWAP_CHAIN_DESC swapChainDesc{};
            swapChainDesc.BufferDesc.Width                   = 0;
            swapChainDesc.BufferDesc.Height                  = 0;
            swapChainDesc.BufferDesc.RefreshRate.Numerator   = 0;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
            swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_B8G8R8A8_UNORM;
            swapChainDesc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            swapChainDesc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

            swapChainDesc.SampleDesc.Count   = 1;
            swapChainDesc.SampleDesc.Quality = 0;

            swapChainDesc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount  = 2;
            swapChainDesc.OutputWindow = m_hwnd;
            swapChainDesc.Windowed     = TRUE;
            swapChainDesc.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
            swapChainDesc.Flags        = 0;

            Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;
            if (FAILED(m_renderInterface->m_dxgiFactory.As<IDXGIFactory2>(&dxgiFactory2))) {
                dxgiFactory2 = nullptr;
            }

            Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory4 = nullptr;
            if (FAILED(m_renderInterface->m_dxgiFactory.As<IDXGIFactory4>(&dxgiFactory4))) {
                dxgiFactory4 = nullptr;
            }

            if (dxgiFactory4) {
                swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            } else if (dxgiFactory2) {
                swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
            }

            HRESULT hres = m_renderInterface->m_dxgiFactory->CreateSwapChain(
                m_renderInterface->m_device.Get(),
                &swapChainDesc,
                &m_swapChain);
            if (FAILED(hres)) {
                GR_FATAL(GTXT("Could not create DXGI swapchain"));
            }

            initializeBackbuffers();
        }

        gnaWeakPointer<grRenderCore::RenderTargetSet> getBackbufferRenderTargetSet() override {
            return m_renderTargetSet;
        }

        void swapBuffers() override {
            HRESULT hres = m_swapChain->Present(1, 0);
            if (FAILED(hres)) {
                GR_FATAL(GTXT("Failed to present backbuffer; error 0x%08x"), hres);
            }
        }

        void prepareBackbuffers() override {
            if (m_currentBackbuffersSize == m_newBackbuffersSize) return;
            m_currentBackbuffersSize = m_newBackbuffersSize;

            m_backbufferImage   = nullptr;
            m_backbufferTexture = nullptr;
            m_renderTargetSet   = nullptr;

            HRESULT hres = m_swapChain->ResizeBuffers(2,
                m_newBackbuffersSize.width, m_newBackbuffersSize.height,
                DXGI_FORMAT_B8G8R8A8_UNORM, 0);
            if (FAILED(hres)) {
                GR_FATAL(GTXT("Failed to resize backbuffer; error 0x%08x"), hres);
            }
            initializeBackbuffers();
        }

        void resizeBackbuffers(uint32_t width, uint32_t height) override {
            m_newBackbuffersSize = { (int) width, (int) height };
        }

    private:
        void initializeBackbuffers() {
            if (FAILED(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&m_backbufferTexture)))) {
                GR_FATAL(GTXT("Could not get DXGI backbuffer texture"));
            }

            m_backbufferImage = gnaNew<grImg::Image>(GTXT("<backbuffer image>"));
            m_backbufferImage->loadSurface(0, 0, grImg::ImageFormat::IMGFMT_ARGB8_SRGB, m_backbufferTexture.Get());

            auto rtsBuilder = m_renderInterface->createRTSBuilder();
            rtsBuilder->setColorImage(0, m_backbufferImage);
            m_renderTargetSet = rtsBuilder->build();
        }
    };
}

gnaPointer<grRenderCore::VideoOutput> grDX11::VideoOutputManager::createFromNativeWindow(
    void *nativeWindow,
    const grRenderCore::VideoOutputCreateOptions &createOptions) {

    HWND hwnd   = (HWND)nativeWindow;
    auto output = gnaNew<DX11VideoOutput>(m_renderInterface, hwnd);
    output->initialize();
    return output;
}
