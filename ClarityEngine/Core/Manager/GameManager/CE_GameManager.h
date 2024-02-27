#pragma once
#define GameMNGR CE_GameManager::GetInstance()

constexpr UINT8 SECONDS(1 << 0);
constexpr UINT8 FPS_NUM(1 << 0);
constexpr UINT16 FPS_DEN(120);      //렌더링 목표 프레임

class CE_GameManager final : public CE_Singleton<CE_GameManager>
{
    //chrono의 타이머를 using 문으로 축약
    using frameRate = std::chrono::duration <UINT64, std::ratio<FPS_NUM, FPS_DEN>>;
    using setTimer = std::chrono::high_resolution_clock;

private:

    std::atomic_bool _threadState = true;

    std::jthread _ASyncUpdateThread;
    std::jthread _gameUpdateThread;

private:

    void ASyncProcess();
    void GameProcess();

    template <typename CLOCK, typename DURATION>
    void FrameRateController(std::chrono::time_point<CLOCK, DURATION> timePoint);

public:

    const UINT16& GetTargetFPS() const noexcept { return FPS_DEN; }

    void Init();
    void GameQuit();
};

template<typename CLOCK, typename DURATION>
inline void CE_GameManager::FrameRateController(std::chrono::time_point<CLOCK, DURATION> tPoint)
{
    std::this_thread::sleep_until(tPoint - std::chrono::microseconds(10)); //10us(마이크로초) 추가 대기 [쓰레드 쿨 다운]
    while (tPoint >= CLOCK::now()) {};
}