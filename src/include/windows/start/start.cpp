#include "start.h"

int start_window::create()
{
    Logger::debug("Attempting to create start_window");

    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOWDEFAULT;

    // Initialize AppWindow member
    window = AppWindow(hInstance);

    if (!window.Create(L"Fusion", 300, 600)) {
        Logger::error("Failed to create window!");
        return 0;
    }

    window.Show(nCmdShow);
    window.RunMessageLoop();

    return 1; // success
}

void start_window::drawText(const std::wstring& text)
{
    HWND hwnd = window.getHWND(); // get window handle safely
    if (!hwnd) return;

    RECT rect;
    GetClientRect(hwnd, &rect);

    HDC hdc = GetDC(hwnd);
    if (!hdc) return;

    DrawTextW(hdc, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    ReleaseDC(hwnd, hdc);
    InvalidateRect(hwnd, nullptr, TRUE); // force repaint
}
