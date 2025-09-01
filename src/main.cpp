#include <iostream>
#include <windows.h>

#include "include/monaco/editor.h"
#include "include/essential/logger/logger.h"
#include "include/essential/window/window.h" // Your existing window class

int main() {

    // Logger
    Logger::init();
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Editor installation/update logic
    if (Editor::is_installed() && Editor::current_editor_version() != Editor::latest_editor_version()) {
        Logger::info("Updating Editor to " + Editor::latest_editor_version());
        Editor::install();
        Logger::success("Editor successfully updated");
    } else if (!Editor::is_installed()) {
        Logger::info("Installing editor...");
        Editor::install();
        Logger::success("Successfully installed editor at " + Editor::get_editor());
    }

    Logger::init();
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Window stuff

    Logger::close();
    return 0;
}
