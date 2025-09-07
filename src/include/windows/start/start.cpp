#include "start.h"
#include "../../essential/logger/logger.h"
#include "../../essential/window/window.h" // Your DX12 AppWindow

int start_window::create()
{
    Logger::debug("Attempting to create start_window");

    // Instead of WinMain's parameters:
    HINSTANCE hInst = GetModuleHandle(nullptr);
    AppWindow app(hInst);

    if (!app.Create(L"Fusion Start", 800, 600))
        return -1;

    Logger::success("start_window succesfully creat5ed");
    Logger::debug("Attempting to call show");

    app.Show(SW_SHOWDEFAULT);
    Logger::success("start_window show succesfully called");

    app.RunMessageLoop();



    return 1; // success
}
