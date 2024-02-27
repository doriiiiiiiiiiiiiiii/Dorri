#include "pch.h"
#include "CE_InputManager.h"

void CE_InputManager::Update()
{
    bool winValid = IsWindow(Win32MNGR->GetWindowHandle());
    bool winVisible = IsWindowVisible(Win32MNGR->GetWindowHandle());
    bool winForeground = GetForegroundWindow() == Win32MNGR->GetWindowHandle();

    if (!(winValid && winVisible && winForeground))
    {
        return;
    }

    //키보드
    for (UINT16 keyScan = 0; keyScan < 256; ++keyScan)
    {
        _keyboardStates[keyScan] = (WIN32::GetAsyncKeyState(keyScan) & 0x8000) != false;
    }

    //마우스
    WIN32::GetCursorPos(&_cursorPos);   //마우스 커서 좌표 업데이트
    _clientCursorPos = _cursorPos;

    WIN32::ScreenToClient(Win32MNGR->GetWindowHandle(), &_clientCursorPos);

    _mouseStates[static_cast<UINT8>(MouseKeys::LEFT)] = (WIN32::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != false;
    _mouseStates[static_cast<UINT8>(MouseKeys::RIGHT)] = (WIN32::GetAsyncKeyState(VK_RBUTTON) & 0x8000) != false;
    _mouseStates[static_cast<UINT8>(MouseKeys::MIDDLE)] = (WIN32::GetAsyncKeyState(VK_MBUTTON) & 0x8000) != false;
    _mouseStates[static_cast<UINT8>(MouseKeys::SIDE_UP)] = (WIN32::GetAsyncKeyState(VK_XBUTTON2) & 0x8000) != false;
    _mouseStates[static_cast<UINT8>(MouseKeys::SIDE_DOWN)] = (WIN32::GetAsyncKeyState(VK_XBUTTON1) & 0x8000) != false;
}