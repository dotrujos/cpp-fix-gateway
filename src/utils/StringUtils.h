//
// Created by gabrielaraujo on 10/03/2026.
//

#include <vector>
#include <sstream>

#ifndef CFIXGATEWAY_STRINGUTILS_H
#define CFIXGATEWAY_STRINGUTILS_H

inline std::vector<std::string> split_string(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

#endif //CFIXGATEWAY_STRINGUTILS_H