#include "window.h"
#include <windows.h>
#include <wrl.h>
#include <wrl/client.h>
#include "../window/WebView/WebView2.h"

const wchar_t* CLASS_NAME = L"MyWindowClass";

// Forward declaration of COM handler classes
class ControllerHandler : public Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>
{
    AppWindow* window;
public:
    ControllerHandler(AppWindow* w) : window(w) {}
    HRESULT STDMETHODCALLTYPE Invoke(HRESULT result, ICoreWebView2Controller* controller) final
    {
        if (controller)
        {
            window->webviewController = controller;
            controller->get_CoreWebView2(window->webview.GetAddressOf());

            RECT bounds;
            GetClientRect(window->hwnd, &bounds);
            controller->put_Bounds(bounds);

            window->webview->Navigate(L"include/monaco/editor.html");
        }
        return S_OK;
    }
};

class EnvHandler : public Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>
{
    AppWindow* window;
public:
    EnvHandler(AppWindow* w) : window(w) {}
    HRESULT STDMETHODCALLTYPE Invoke(HRESULT result, ICoreWebView2Environment* env) final
    {
        if (env)
        {
            env->CreateCoreWebView2Controller(window->hwnd, Microsoft::WRL::Make<ControllerHandler>(window).Get());
        }
        return S_OK;
    }
};

// ------------------ AppWindow implementation ------------------

AppWindow::AppWindow(HINSTANCE hInst) : hInstance(hInst), hwnd(NULL) {}

void AppWindow::InitWebView()
{
    CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
        Microsoft::WRL::Make<EnvHandler>(this).Get());
}

bool AppWindow::Create(LPCWSTR title, int width, int height)
{
    WNDCLASSW wc = {};
    wc.lpfnWndProc = AppWindow::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassW(&wc);

    hwnd = CreateWindowExW(
        0, CLASS_NAME, title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hInstance, this
    );

    if (hwnd)
        InitWebView();

    return hwnd != NULL;
}

void AppWindow::Show(int nCmdShow)
{
    ShowWindow(hwnd, nCmdShow);
}

void AppWindow::RunMessageLoop()
{
    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

LRESULT CALLBACK AppWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    AppWindow* window = nullptr;
    if (uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        window = (AppWindow*)cs->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
        window->hwnd = hwnd;
    }
    else
    {
        window = (AppWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    switch (uMsg)
    {
    case WM_SIZE:
        if (window && window->webviewController)
        {
            RECT bounds;
            GetClientRect(hwnd, &bounds);
            window->webviewController->put_Bounds(bounds);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);
        DrawTextW(hdc, L"Sex!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
    } break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
