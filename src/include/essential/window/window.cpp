#include "window.h"

// ------------------ Constructor ------------------
AppWindow::AppWindow(HINSTANCE hInst)
    : hInstance(hInst), hwnd(nullptr) {}

// ------------------ Create Window ------------------
bool AppWindow::Create(LPCWSTR title, int width, int height)
{
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"FusionWindowClass"; // Rebranded
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    RegisterClassW(&wc);

    hwnd = CreateWindowExW(
        0, L"FusionWindowClass", title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, hInstance, this
    );

    return hwnd != nullptr;
}

// ------------------ Show Window ------------------
void AppWindow::Show(int nCmdShow)
{
    ShowWindow(hwnd, nCmdShow);
}

// ------------------ Message Loop ------------------
void AppWindow::RunMessageLoop()
{
    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

// ------------------ Getter for HWND ------------------
HWND AppWindow::getHWND() const
{
    return hwnd;
}

// ------------------ Window Procedure ------------------
LRESULT CALLBACK AppWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    AppWindow* window = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        window = reinterpret_cast<AppWindow*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        window->hwnd = hwnd;
    }
    else
    {
        window = reinterpret_cast<AppWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    switch (uMsg)
    {
    case WM_PAINT:
    {
        if (window)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect;
            GetClientRect(hwnd, &rect);
            DrawTextW(hdc, L"Hello, Fusion!", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            EndPaint(hwnd, &ps);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
