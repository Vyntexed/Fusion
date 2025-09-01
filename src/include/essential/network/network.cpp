#include "network.h"

#ifdef _WIN32
#include <cstdio>
#define popen _popen
#define pclose _pclose
#else
#include <cstdio>
#endif

#include <string>

std::string Network::fetch(const std::string& url) 
{
    std::string data;
    std::string command = "curl -s " + url;  // silent mode

    char buffer[256];
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "";  // return empty string on failure
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        data += buffer;
    }

    pclose(pipe);
    return data;
}