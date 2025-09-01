#include "window.h"

// Constructor
AppWindow::AppWindow(HINSTANCE hInst) : hInstance(hInst), hwnd(NULL) {}

// Create the window
bool AppWindow::Create(LPCWSTR title, int width, int height)
{
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MWC";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassW(&wc);

    hwnd = CreateWindowExW(
        0, L"MWC", title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, hInstance, this
    );

    return hwnd != NULL;
}

// Show window
void AppWindow::Show(int nCmdShow)
{
    ShowWindow(hwnd, nCmdShow);
}

// Message loop
void AppWindow::RunMessageLoop()
{
    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

// Draw text helper
void AppWindow::drawText(const std::wstring& text)
{
    if (!hwnd) Logger::info("No hwnd found when calling drawText"); return;

    HDC hdc = GetDC(hwnd);
    if (!hdc) Logger::info("No hdc found in drawText"); return;

    RECT rect;
    GetClientRect(hwnd, &rect);

    SetBkMode(hdc, TRANSPARENT);
    DrawTextW(hdc, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    ReleaseDC(hwnd, hdc);
    InvalidateRect(hwnd, nullptr, TRUE); // force repaint
}

// Draw button helper (native Win32 button)
void AppWindow::drawButton(int id, const std::wstring& text, int x, int y, int width, int height)
{
    if (!hwnd) Logger::info("No hwnd found when calling drawButton"); return;

    CreateWindowW(
        L"BUTTON", text.c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x, y, width, height,
        hwnd,
        (HMENU)(INT_PTR)id,   // ✅ safe cast for both 32/64-bit
        GetModuleHandle(NULL),
        nullptr
    );
}


// Window procedure
LRESULT CALLBACK AppWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // Example button ID
            MessageBoxW(hwnd, L"Button clicked!", L"Info", MB_OK);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
