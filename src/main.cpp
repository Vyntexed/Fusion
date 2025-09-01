#include <iostream>
#include <windows.h>

#include "include/monaco/editor.h"
#include "include/essential/logger/logger.h"
#include "include/essential/window/window.h"
#include "include/windows/start/start.h"

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

    start_window starting_window;

    if (!starting_window.create()){
        Logger::fatal("Could not create start_window");
        std::cin.get(); // pauses execution without closing window
        return 0;
    }

    starting_window.drawText(L"Hello, World!");

    Logger::close();
    return 0;
}
