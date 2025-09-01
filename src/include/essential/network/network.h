#include <string>

class Network {
public:
    Network() = default;

    // Fetch the website data and return it as a string
    std::string fetch(const std::string& url);
};