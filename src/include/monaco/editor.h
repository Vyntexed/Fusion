#pragma once
#include <string>

class Editor {
public:
    static bool is_installed();
    static void install();
    static std::string get_editor();
    static std::string current_editor_version();
    static std::string latest_editor_version();
};
