#pragma once
#define InputMNGR CE_InputManager::GetInstance()

//각 입력장치의 버튼을 정의하는 상수
constexpr UINT16 KEYBOARD_BUTTONS(256);
constexpr UINT8 MOUSE_BUTTONS(5);

enum class MouseKeys : UINT8    //마우스 버튼 전용 플래그
{
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2,     //마우스 휠 버튼
    SIDE_UP = 3,    //사이드 업 버튼
    SIDE_DOWN = 4   //사이드 다운 버튼
};

class CE_InputManager final : public CE_Singleton<CE_InputManager>
{
private:

    //마우스 커서 좌표
    POINT _cursorPos{};
    POINT _clientCursorPos{};

    bool _keyboardStates[KEYBOARD_BUTTONS]{};
    bool _mouseStates[MOUSE_BUTTONS]{};

public:

    //키보드
    const bool& KeyPressed(const UINT16& keyCode) const noexcept { return _keyboardStates[keyCode]; }
    const bool KeyReleased(const UINT16& keyCode) const noexcept { return !_keyboardStates[keyCode]; }

    //마우스
    const POINT& GetWinMousePos() const noexcept { return _cursorPos; }
    const LONG& GetWinMouseX() const noexcept { return _cursorPos.x; }
    const LONG& GetWinMouseY() const noexcept { return _cursorPos.y; }

    const POINT& GetClientMousePos() const noexcept { return _clientCursorPos; }
    const LONG& GetClientMouseX() const noexcept { return _clientCursorPos.x; }
    const LONG& GetClientMouseY() const noexcept { return _clientCursorPos.y; }

    const bool& KeyPressed(const MouseKeys& keyCode) const noexcept { return _mouseStates[static_cast<UINT8>(keyCode)]; }
    const bool KeyReleased(const MouseKeys& keyCode) const noexcept { return !_mouseStates[static_cast<UINT8>(keyCode)]; }

    //입력 상태 업데이트
    void Update();
};