#pragma once

#include <windows.h>
#include "../../essential/window/window.h"
#include "../../essential/logger/logger.h"
#include <string>

class start_window
{
public:
    // Create and show the window
    int create();

    // Draw text inside the window
    void drawText(const std::wstring& text);

private:
    AppWindow window{ nullptr }; // make it a member, initialize with nullptr
};
