#pragma once

//'GetState()'를 호출할 때마다 상태가 변함
class CE_FlipFlop final
{
private:

    bool _gateFlags = false;

public:

    const bool& GetState() noexcept { return _gateFlags = !_gateFlags; }
};

using FlipFlop = CE_FlipFlop; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리