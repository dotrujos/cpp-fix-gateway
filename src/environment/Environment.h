//
// Created by gabrielaraujo on 10/03/2026.
//

#include <string>
#include <unordered_map>

#ifndef CFIXGATEWAY_ENVIRONMENT_H
#define CFIXGATEWAY_ENVIRONMENT_H

class Environment{
private:
    std::unordered_map<std::string, std::string> environments = {};

    Environment() = default;
public:
    static Environment& getInstance();

    bool parseEnv(std::string path);
    std::string get(std::string key);
};

#endif //CFIXGATEWAY_ENVIRONMENT_H