#include "start.h"
#include "../../essential/logger/logger.h"

int start_window::create()
{
    Logger::debug("Attempting to create start_window");

    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOWDEFAULT;

    // Initialize AppWindow member
    window = AppWindow(hInstance);

    if (!window.Create(L"Fusion", 300, 600)) {
        Logger::error("Failed to create window");
        return 0;
    }

    Logger::success("Successfully created start_window");

    // Add a button directly here
    HWND hwnd = window.getHWND();
    if (hwnd) {
        CreateWindowW(
            L"BUTTON", L"Click Me",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 50, 200, 40,        // x, y, width, height
            hwnd,
            (HMENU)(INT_PTR)1,      // button ID = 1
            GetModuleHandle(NULL),
            nullptr
        );

        Logger::debug("Button created in start_window");
    }

    // Show and run
    window.Show(nCmdShow);
    window.RunMessageLoop();

    return 1; // success
}