#include "pch.h"
#include "CE_AudioPlayer.h"

CE_AudioPlayer::CE_AudioPlayer(const std::wstring& path, const UINT32& buffSize)
    : _capacity(buffSize)
    , _currentIndex(0)
{
    _soundEffect = std::make_unique<DirectX::SoundEffect>(&_audioEngine, path.c_str());
    _soundInstances.reserve(_capacity);
}

CE_AudioPlayer::~CE_AudioPlayer()
{
    CE_AudioPlayer::Clear();
}

void CE_AudioPlayer::Play(const bool& isLoop, const bool& shortLength)
{
    if (_soundInstances.size() < _capacity)
    {
        _soundInstances.push_back(_soundEffect->CreateInstance());
    }
    else
    {
        //생성된 순서대로 사운드 인스턴스를 덮어씀
        _soundInstances[_currentIndex] = _soundEffect->CreateInstance();
        _currentIndex = (_currentIndex + 1) % _capacity;
    }

    _soundInstances.back()->Play(isLoop);
}

void CE_AudioPlayer::SetVolume(const FLOAT& volume)
{
    if (!_soundInstances.empty())
    {
        _soundInstances.back()->SetVolume(volume);
    }
}

void CE_AudioPlayer::SetPitch(const FLOAT& pitch)
{
    if (!_soundInstances.empty())
    {
        _soundInstances.back()->SetPitch(pitch);
    }
}

void CE_AudioPlayer::Pause()
{
    if (!_soundInstances.empty())
    {
        _soundInstances.back()->Pause();
    }
}

void CE_AudioPlayer::Resume()
{
    if (!_soundInstances.empty())
    {
        _soundInstances.back()->Resume();
    }
}

void CE_AudioPlayer::Stop()
{
    if (!_soundInstances.empty())
    {
        _soundInstances.back()->Stop();
    }
}

void CE_AudioPlayer::Clear()
{
    //메모리 릭 방지를 위한 사운드 인스턴스 해제
    for (auto& instance : _soundInstances)
    {
        instance.reset(nullptr);
    }

    _soundInstances.clear();
}