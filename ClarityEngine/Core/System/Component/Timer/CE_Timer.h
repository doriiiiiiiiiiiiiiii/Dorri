#pragma once

class CE_Timer final
{
private:

    std::chrono::high_resolution_clock::time_point _startPoint;
    std::chrono::high_resolution_clock::time_point _endPoint;

public:

    void Start() noexcept { _startPoint = std::chrono::high_resolution_clock::now(); }
    void Stop() noexcept { _endPoint = std::chrono::high_resolution_clock::now(); }

    UINT64 ElapsedTime() const noexcept;
    DOUBLE HighElapsedTime() const noexcept;
};

using Timer = CE_Timer; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리