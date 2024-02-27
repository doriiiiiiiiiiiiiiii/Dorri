#include "pch.h"
#include "CE_Timer.h"

UINT64 CE_Timer::ElapsedTime() const noexcept
{
    std::chrono::duration<UINT64, std::milli> duration;
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(_endPoint - _startPoint);

    return duration.count();
}

DOUBLE CE_Timer::HighElapsedTime() const noexcept
{
    std::chrono::duration<DOUBLE> duration;
    duration = std::chrono::duration<DOUBLE>(_endPoint - _startPoint);

    return duration.count();
}