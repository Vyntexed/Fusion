#pragma once

#include <windows.h>
#include <string>

class AppWindow {
public:
    AppWindow(HINSTANCE hInst);

    bool Create(LPCWSTR title, int width, int height);
    void Show(int nCmdShow);
    void RunMessageLoop();

private:
    HINSTANCE hInstance;
    HWND hwnd;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
