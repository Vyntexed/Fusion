// Starting screen the first screen you ese

#include <windows.h>
#include <iostream>

#include "../../essential/window/window.h"
#include "../../essential/logger/logger.h"

class start_window
{
    int create(){
        HINSTANCE hInstance = GetModuleHandle(NULL);
        int nCmdShow = SW_SHOWDEFAULT;

        AppWindow window(hInstance);
        if (!window.Create(L"Fusion", 800, 600)) {
            Logger::error("Failed to create window!");
            return 0;
        }
        window.Show(nCmdShow);
        window.RunMessageLoop();
    };
};