#pragma once

#include <windows.h>
#include <wrl.h>
#include <string>
#include "../window/WebView/WebView2.h" // adjust path if needed

using Microsoft::WRL::ComPtr;
using Microsoft::WRL::RuntimeClass;
using Microsoft::WRL::ClassicCom;

class EnvHandler;
class ControllerHandler;

class AppWindow {
public:
    AppWindow(HINSTANCE hInst);

    bool Create(LPCWSTR title, int width, int height);
    void Show(int nCmdShow);
    void RunMessageLoop();

private:
    HINSTANCE hInstance;
    HWND hwnd;

    ComPtr<ICoreWebView2Controller> webviewController;
    ComPtr<ICoreWebView2> webview;

    void InitWebView();

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Allow COM handlers to access private members
    friend class EnvHandler;
    friend class ControllerHandler;
};
