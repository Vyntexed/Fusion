#pragma once

#include <windows.h>

class AppWindow {
public:
    // Constructor
    explicit AppWindow(HINSTANCE hInst);

    // Create the window
    bool Create(LPCWSTR title, int width, int height);

    // Show the window
    void Show(int nCmdShow);

    // Run the message loop
    void RunMessageLoop();

    // Getter for hwnd
    HWND getHWND() const;

private:
    HWND hwnd;          // Window handle (private)
    HINSTANCE hInstance;

    // Window procedure
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
