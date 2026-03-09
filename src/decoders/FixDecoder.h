//
// Created by gabrielaraujo on 09/03/2026.
//

#include <vector>

#include "../models/FixMessage.h"

#ifndef CFIXGATEWAY_FIXDECODER_H
#define CFIXGATEWAY_FIXDECODER_H

class FixDecoder {
private:
    std::vector<std::string> split_string(const std::string& str, char delimiter);
public:
    FixMessage decode(std::string message);
};


#endif //CFIXGATEWAY_FIXDECODER_H