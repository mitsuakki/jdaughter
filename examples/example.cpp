#include <iostream>
#include <string>
#include "jdaughter.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <json_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    auto j = jdaughter::parse_file(filename);
    if (j.is_null()) {
        std::cerr << "Error parsing JSON: Could not open file: " << filename << std::endl;
        return 1;
    }

    for (const auto& user : j.at("users")) {
        std::cout << "- ID: " << user.at("id").get<std::string>() << "\n";
        std::cout << "  Name: " << user.at("name").get<std::string>() << "\n";
        std::cout << "  Email: " << user.at("email").get<std::string>() << "\n";
        std::cout << "  Role: " << user.at("role").get<std::string>() << "\n\n";
    }

    return 0;
}
