#include "logger.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>

static HANDLE hConsole = nullptr;

// Convert hex color "#RRGGBB" to RGB integers
static void hex_to_rgb(const std::string& hex, int &r, int &g, int &b) {
    if (hex.size() == 7 && hex[0] == '#') {
        std::stringstream ss;
        ss << std::hex << hex.substr(1,2); ss >> r; ss.clear();
        ss << std::hex << hex.substr(3,2); ss >> g; ss.clear();
        ss << std::hex << hex.substr(5,2); ss >> b;
    } else {
        r = g = b = 255; // fallback white
    }
}

void Logger::init() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole) {
        DWORD mode = 0;
        if (GetConsoleMode(hConsole, &mode)) {
            SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    }

    // Enable UTF-8 output
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Logger::close() {
    // No special cleanup needed
    hConsole = nullptr;
}

void Logger::log(const std::string& hexColor, const std::string& message) {
    int r, g, b;
    hex_to_rgb(hexColor, r, g, b);

    std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
              << message
              << "\033[0m" << std::endl; // Reset color
}

// Predefined levels using your colors
void Logger::info(const std::string& message) {
    log("#6fa8dc", "[INFO] " + message);      // Blue
}

void Logger::success(const std::string& message) {
    log("#8CEFAE", "[OK] " + message);        // Green
}

void Logger::warning(const std::string& message) {
    log("#ffe084", "[WARNING] " + message);   // Yellow
}

void Logger::error(const std::string& message) {
    log("#FF5C5D", "[ERROR] " + message);     // Red
}

void Logger::debug(const std::string& message) {
    log("#ffffffff", "[DEBUG] " + message);     // White
}

void Logger::fatal(const std::string& message) {
    log("#ff0000ff", "[💀] " + message);     // Red
}
