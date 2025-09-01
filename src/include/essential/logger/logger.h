#pragma once
#include <string>

class Logger {
public:
    // Initialize the console (enable ANSI colors)
    static void init();

    // Optional cleanup (does nothing here)
    static void close();

    // Log a message with any custom hex color
    static void log(const std::string& hexColor, const std::string& message);

    // Predefined levels
    static void info(const std::string& message);     // Green
    static void success(const std::string& message);  // Green
    static void warning(const std::string& message);  // Yellow
    static void error(const std::string& message);    // Red
    static void debug(const std::string& message);    // Blue
};
