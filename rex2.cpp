#include <iostream>
#include <string>
#include <regex>

int main() {
    // Regex to match an HTTP request line like "GET / HTTP/1.1"
    std::regex pattern(R"((GET|POST|PUT|DELETE)\s+(\S+)\s+(HTTP/\d\.\d))");

    // The string we want to search
    std::string request = "GET /index.html HTTP/1.1";

    std::smatch matches;  // Will hold the matched groups
    if (std::regex_match(request, matches, pattern)) {
        // Extracting the matched parts (method, path, version)
        std::cout << "Method: " << matches[1] << std::endl;
        std::cout << "Path: " << matches[2] << std::endl;
        std::cout << "Version: " << matches[3] << std::endl;
    } else {
        std::cout << "No match found!" << std::endl;
    }

    return 0;
}

