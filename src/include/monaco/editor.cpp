#include "editor.h"
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>

#include "../essential/network/network.h" // go up a few

const char* conf = "include\\monaco\\editor.html";
const char* conf_version = "include\\monaco\\version.fsv"; // General Fusion Version File
 
bool Editor::is_installed() {
    if (FILE *file = fopen(conf, "r")) {
        fclose(file);
        return true;
    } 
    return false;
}

void Editor::install() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH); // Gets path

    std::string fullPath(path);
    std::string dir = fullPath.substr(0, fullPath.find_last_of("\\/"));

    std::string com = 
        "powershell -Command \"Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Vyntexed/Fusion/refs/heads/externals/editor/monaco.html' -OutFile '" 
        + dir + "\\" + conf + "'\"";

    std::string cnf = 
        "powershell -Command \"Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Vyntexed/Fusion/refs/heads/externals/editor/version' -OutFile '" 
        + dir + "\\" + conf_version + "'\"";



    system(com.c_str()); // run PowerShell download
    system(cnf.c_str()); // run Powershell Version Download
}

std::string Editor::current_editor_version()
{
    // Get executable path
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    std::string fullPath(path);
    std::string dir = fullPath.substr(0, fullPath.find_last_of("\\/"));

    // Build full path to conf_version
    std::string versionFile = dir + "\\"+conf_version;

    // Open file and read content
    std::ifstream file(versionFile);
    if (!file.is_open()) {
        return ""; // could not open file
    }

    std::ostringstream ss;
    ss << file.rdbuf(); // read entire file

    return ss.str();
}

std::string Editor::latest_editor_version()
{
    Network net;
    return net.fetch("https://raw.githubusercontent.com/Vyntexed/Fusion/refs/heads/externals/editor/version");
}

std::string Editor::get_editor() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    std::string fullPath(path);
    fullPath = fullPath.substr(0, fullPath.find_last_of("\\/"));

    return fullPath + "\\" + conf;
}
