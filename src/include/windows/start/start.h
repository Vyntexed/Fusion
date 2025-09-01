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

private:
    AppWindow window{ nullptr }; // make it a member, initialize with nullptr
};
