#include "pch.h"
#include "CE_VideoPlayer.h"

CE_VideoPlayer::CE_VideoPlayer(const std::wstring& path)
    : _path(path)
    , _texture(std::make_unique<DirectX::SpriteBatch>(GraphicsDevContext.Get()))
{
    CE_VideoPlayer::StartUp();
}

CE_VideoPlayer::~CE_VideoPlayer()
{
    CE_VideoPlayer::Shutdown();
}

void CE_VideoPlayer::StartUp()
{
    HRESULT hr = WIN32::MFStartup(MF_VERSION);
    assert(SUCCEEDED(hr));

    ComPtr<IMFMediaEngineClassFactory> factory = nullptr;

    hr = WIN32::CoCreateInstance(CLSID_MFMediaEngineClassFactory, nullptr, CLSCTX_ALL, IID_PPV_ARGS(factory.GetAddressOf()));
    assert(SUCCEEDED(hr));

    DWORD flags = MF_MEDIA_ENGINE_REAL_TIME_MODE;

    ComPtr<IMFAttributes> attributes = nullptr;
    hr = WIN32::MFCreateAttributes(&attributes, 1);
    assert(SUCCEEDED(hr));

    _callbacks = ComPtr<CallbackInterface>(new CallbackInterface(this));

    hr = attributes->SetUnknown(MF_MEDIA_ENGINE_CALLBACK, _callbacks.Get());
    assert(SUCCEEDED(hr));

    hr = attributes->SetUINT32(MF_MEDIA_ENGINE_VIDEO_OUTPUT_FORMAT, DXGI_FORMAT_R8G8B8A8_UNORM);
    assert(SUCCEEDED(hr));

    hr = attributes->SetUnknown(MF_MEDIA_ENGINE_DXGI_MANAGER, GraphicsDXGI.Get());
    assert(SUCCEEDED(hr));

    hr = factory->CreateInstance(flags, attributes.Get(), _mediaEngine.GetAddressOf());
    assert(SUCCEEDED(hr));

    hr = _mediaEngine->SetSource((BSTR)_path.c_str());
    assert(SUCCEEDED(hr));

    hr = _mediaEngine->SetPreload(MF_MEDIA_ENGINE_PRELOAD_METADATA);
    assert(SUCCEEDED(hr));

    hr = _mediaEngine->Load();
    assert(SUCCEEDED(hr));

    CE_VideoPlayer::CreateTexture2D();
}

void CE_VideoPlayer::Shutdown()
{
    if (_mediaEngine)
    {
        _mediaEngine->Shutdown();
    }

    HRESULT hr = WIN32::MFShutdown();
    assert(SUCCEEDED(hr));
}

void CE_VideoPlayer::CreateTexture2D()
{
    _desc.Width = Win32MNGR->GetWidth();
    _desc.Height = Win32MNGR->GetHeight();
    _desc.MipLevels = 1;
    _desc.ArraySize = 1;
    _desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    _desc.SampleDesc.Count = 1;
    _desc.SampleDesc.Quality = 0;
    _desc.Usage = D3D11_USAGE_DEFAULT;
    _desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    _desc.CPUAccessFlags = false;
    _desc.MiscFlags = false;
}

void CE_VideoPlayer::Update()
{
    INT64 pts;

    if (_mediaEngine->OnVideoStreamTick(&pts) == S_OK)
    {
        ComPtr<ID3D11Texture2D> videoTexture = nullptr;

        HRESULT hr = GraphicsDev->CreateTexture2D(&_desc, nullptr, videoTexture.GetAddressOf());
        assert(SUCCEEDED(hr));

        hr = _mediaEngine->TransferVideoFrame(videoTexture.Get(), nullptr, &_videoSize, nullptr);
        assert(SUCCEEDED(hr));

        hr = GraphicsDev->CreateShaderResourceView(videoTexture.Get(), nullptr, &_srv);
        assert(SUCCEEDED(hr));
    }
}

void CE_VideoPlayer::Render()
{
    if (_srv)
    {
        _texture->Begin();

        _texture->Draw(_srv.Get(), Vec2(0, 0));

        _texture->End();
    }
}