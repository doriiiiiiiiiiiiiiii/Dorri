#pragma once
#define Win32MNGR CE_Win32Manager::GetInstance()

class CE_Win32Manager final : public CE_Singleton<CE_Win32Manager>
{
private:

    HINSTANCE _hInstance = nullptr;
    HWND _hWnd = nullptr;

    LPCWSTR _title = nullptr;
    UINT32 _width = 0;
    UINT32 _height = 0;

private:

    static LRESULT WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

    void SetupWindow();
    void ReleaseWindow();

public:

    const HWND& GetWindowHandle() const noexcept { return _hWnd; }
    const UINT32& GetWidth() const noexcept { return _width; }
    const UINT32& GetHeight() const noexcept { return _height; }

    void Init
    (
        const HINSTANCE& hInstance = nullptr,
        const LPCWSTR& title = L"Welcome to the ClarityEngine! (Dev By Nahgie)",
        const UINT32& width = 1280,
        const UINT32& height = 720
    );
};