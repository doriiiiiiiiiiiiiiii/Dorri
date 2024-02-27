#include "pch.h"
#include "CE_GraphicsManager.h"

void CE_GraphicsManager::Init()
{
    CreateDevSC();
    CreateRTV();
    SetViewport();
}

void CE_GraphicsManager::CreateDevSC()
{
    //WinGDI를 사용해 사용자의 모니터 정보를 불러옵니다.
    DEVMODEW deviceMode{};
    {
        deviceMode.dmSize = sizeof(DEVMODEW);
        WIN32::EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &deviceMode);
    }

    DXGI_SWAP_CHAIN_DESC desc{};
    {
        desc.BufferDesc.Width = Win32MNGR->GetWidth();
        desc.BufferDesc.Height = Win32MNGR->GetHeight();
        desc.BufferDesc.RefreshRate.Numerator = deviceMode.dmDisplayFrequency;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;

        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = 1;

        desc.OutputWindow = Win32MNGR->GetWindowHandle();
        desc.Windowed = true;
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    }

    HRESULT hr = WIN32::D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &desc,
        _swChain.GetAddressOf(),
        _dev.GetAddressOf(),
        nullptr,
        _devContext.GetAddressOf()
    );
    assert(SUCCEEDED(hr));

    ComPtr<ID3D10Multithread> mt = nullptr;    //다이렉트X 멀티 쓰레드 동기화 작업 (DX10)
    _dev->QueryInterface<ID3D10Multithread>(mt.GetAddressOf());
    mt->SetMultithreadProtected(true);

    WIN32::MFCreateDXGIDeviceManager(&_dxgiResetToken, _dxgiManager.GetAddressOf());
    _dxgiManager->ResetDevice(_dev.Get(), _dxgiResetToken);
}

void CE_GraphicsManager::CreateRTV()
{
    ComPtr<ID3D11Texture2D> backBuff = nullptr;

    HRESULT hr = _swChain->GetBuffer
    (
        0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(backBuff.GetAddressOf())
    );
    assert(SUCCEEDED(hr));

    hr = _dev->CreateRenderTargetView(backBuff.Get(), nullptr, _rtv.GetAddressOf());
    assert(SUCCEEDED(hr));
}

void CE_GraphicsManager::SetViewport()
{
    _viewport.TopLeftX = 0.f;
    _viewport.TopLeftY = 0.f;
    _viewport.Width = static_cast<FLOAT>(Win32MNGR->GetWidth());
    _viewport.Height = static_cast<FLOAT>(Win32MNGR->GetHeight());
    _viewport.MinDepth = 0.f;
    _viewport.MaxDepth = 1.f;
}

void CE_GraphicsManager::SetRenderFrameLimitMode(const RenderFrameLimitMode& state) noexcept
{
    switch (state)
    {
    case RenderFrameLimitMode::UNLIMIT:
        _renderState = RenderFrameLimitMode::UNLIMIT;
        break;

    case RenderFrameLimitMode::V_SYNC:
        _renderState = RenderFrameLimitMode::V_SYNC;
        break;

    case RenderFrameLimitMode::SINGLE_BUFFER:
        _renderState = RenderFrameLimitMode::SINGLE_BUFFER;
        break;

    case RenderFrameLimitMode::DOUBLE_BUFFER:
        _renderState = RenderFrameLimitMode::DOUBLE_BUFFER;
        break;

    case RenderFrameLimitMode::TRIPLE_BUFFER:
        _renderState = RenderFrameLimitMode::TRIPLE_BUFFER;
        break;
    }
}

void CE_GraphicsManager::RenderBegin()
{
    _devContext->OMSetRenderTargets(1, _rtv.GetAddressOf(), nullptr);
    _devContext->ClearRenderTargetView(_rtv.Get(), _defColor);
    _devContext->RSSetViewports(1, &_viewport);
}

void CE_GraphicsManager::RenderEnd()
{
    HRESULT hr = _swChain->Present(static_cast<UINT8>(_renderState), 0);
    assert(SUCCEEDED(hr));
}