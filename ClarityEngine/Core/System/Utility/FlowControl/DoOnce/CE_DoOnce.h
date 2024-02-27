#pragma once

//가독성을 위해 작성된 매크로 (상황에 따라 사용할 것)
#define NOT_PASSED(OBJ) !OBJ.GetState()
#define PASSED(OBJ) OBJ.GetState()

//CE_DoOnce객체 사용 시 작업이 한 번만 실행되도록 보장할 수 있음
class CE_DoOnce final
{
private:

    bool _blockingFlag = false;

public:

    const bool& GetState() const noexcept { return _blockingFlag; }

    void Block() noexcept { _blockingFlag = true; }
    void Reset() noexcept { _blockingFlag = false; }
};

using DoOnce = CE_DoOnce; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리