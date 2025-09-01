#pragma once
#include <windows.h>
#include <string>
#include "../logger/logger.h"

class AppWindow {
public:
    AppWindow(HINSTANCE hInst);

    bool Create(LPCWSTR title, int width, int height);
    void Show(int nCmdShow);
    void RunMessageLoop();

    // New drawing helpers
    void drawText(const std::wstring& text);
    void drawButton(int id, const std::wstring& label, int x, int y, int width, int height);

    HWND getHWND() const { return hwnd; }

private:
    HINSTANCE hInstance;
    HWND hwnd;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
