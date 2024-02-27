#pragma once

class CE_AudioPlayer final
{
private:

    DirectX::AudioEngine _audioEngine;
    std::unique_ptr<DirectX::SoundEffect> _soundEffect = nullptr;
    std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> _soundInstances;

    UINT32 _capacity = 0;
    UINT32 _currentIndex = 0;

public:

    CE_AudioPlayer(const std::wstring& path, const UINT32& buffSize = 1024);
    ~CE_AudioPlayer();

    void Play(const bool& isLoop = false, const bool& shortLength = false);
    void SetVolume(const FLOAT& volume);
    void SetPitch(const FLOAT& pitch);

    void Pause();
    void Resume();

    void Stop();
    void Clear();
};

using AudioPlayer = CE_AudioPlayer; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리