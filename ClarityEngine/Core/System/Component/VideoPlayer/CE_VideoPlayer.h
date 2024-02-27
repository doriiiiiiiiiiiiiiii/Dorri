#pragma once

class CE_VideoPlayer final : public CE_GameObject
{
    //경고!
    //friend class를 선언했으니 접근 방법에 주의할 것
    friend class CallbackInterface;

private:

    std::unique_ptr<DirectX::SpriteBatch> _texture = nullptr;
    ComPtr<ID3D11ShaderResourceView> _srv = nullptr;

    ComPtr<IMFMediaEngine> _mediaEngine = nullptr;
    ComPtr<IMFMediaEngineNotify> _callbacks = nullptr;

    std::wstring _path = nullptr; //미디어 소스의 경로

    D3D11_TEXTURE2D_DESC _desc{};
    RECT _videoSize{};
    FLOAT _videoVolume = 1;

private:

    void CreateTexture2D();

public:

    CE_VideoPlayer(const std::wstring& path);
    ~CE_VideoPlayer();

    void Update() override;
    void Render() override;

    void StartUp();
    void Shutdown();

    void SetVolume(const FLOAT& volume) { _videoVolume = volume; }
    void Play() { _mediaEngine->Play(); }
    void Stop() { _mediaEngine->Pause(); }

    Vec2 GetVideoRes() const { return Vec2(static_cast<FLOAT>(_videoSize.right), static_cast<FLOAT>(_videoSize.bottom)); }
    void SetVideoRes(const Vec2& res) { _videoSize.right = static_cast<LONG>(res.x); _videoSize.bottom = static_cast<LONG>(res.y); }
};

using VideoPlayer = CE_VideoPlayer; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리

class CallbackInterface : public IMFMediaEngineNotify
{
private:

    std::unique_ptr<CE_VideoPlayer> _videoPlayer = nullptr;
    UINT32 _cRef = 1;

public:

    CallbackInterface(CE_VideoPlayer* player)
    {
        _videoPlayer.reset(player);
    }

    ~CallbackInterface()
    {

    }

    virtual HRESULT STDMETHODCALLTYPE EventNotify
    (
        _In_  DWORD event,
        _In_  DWORD_PTR param1,
        _In_  DWORD param2
    ) override
    {

        switch (event)
        {
        case MF_MEDIA_ENGINE_EVENT_LOADEDDATA:
        {
            DWORD width = 0, height = 0;

            _videoPlayer->_mediaEngine->GetNativeVideoSize(&width, &height);
            _videoPlayer->_videoSize.right = static_cast<LONG>(width);
            _videoPlayer->_videoSize.bottom = static_cast<LONG>(height);

            _videoPlayer->_mediaEngine->SetVolume(_videoPlayer->_videoVolume);
            break;
        }
        case MF_MEDIA_ENGINE_EVENT_CANPLAY:
            _videoPlayer->_mediaEngine->Play();
            break;

        case MF_MEDIA_ENGINE_EVENT_PLAYING:
            break;

        case MF_MEDIA_ENGINE_EVENT_ENDED:
            _videoPlayer->_srv.Reset();
            break;
        }
        return S_OK;
    }

    STDMETHODIMP QueryInterface(REFIID riid, void** ppv) override
    {
        if (__uuidof(IMFMediaEngineNotify) == riid)
        {
            *ppv = static_cast<IMFMediaEngineNotify*>(this);
        }
        else
        {
            *ppv = nullptr;
            return E_NOINTERFACE;
        }

        AddRef();

        return S_OK;
    }

    STDMETHODIMP_(ULONG) AddRef() override
    {
        return InterlockedIncrement(&_cRef);
    }

    STDMETHODIMP_(ULONG) Release() override
    {
        LONG cRef = InterlockedDecrement(&_cRef);
        if (cRef == 0)
        {
            delete this;
        }
        return cRef;
    }
};