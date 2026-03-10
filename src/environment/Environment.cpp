//
// Created by gabrielaraujo on 10/03/2026.
//

#include "Environment.h"
#include "../utils/StringUtils.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

Environment &Environment::getInstance() {
    static Environment instance;
    return instance;
}

bool Environment::parseEnv(std::string path) {
    if (path.empty()) {
        std::cout << "--env-file is null. Using shell env" << std::endl;
        return false;
    } 

    std::string line;
    std::ifstream EnvironmentFile(path);

    while (getline(EnvironmentFile, line)) {
        std::vector<std::string> env = split_string(line, '=');

        std::string key = env.at(0);
        std::string value = env.at(1);

        if (!key.empty() && !value.empty()) {
            std::cout << "Adding to environment - " << key << ": " << value << std::endl;
            environments.insert({ key, value });
        }
    }

    EnvironmentFile.close();

    return true;
}

std::string Environment::get(std::string key) {
    auto it = environments.find(key);
    if (it != environments.end()) {
        return it->second;
    }

    const char* env_ptr = std::getenv(key.c_str());

    if (env_ptr != nullptr) {
        return std::string(env_ptr);
    }

    return "";
}