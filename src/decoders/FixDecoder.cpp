//
// Created by gabrielaraujo on 09/03/2026.
//

#include "FixDecoder.h"

#include <iostream>
#include <sstream>

std::vector<std::string> FixDecoder::split_string(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

FixMessage FixDecoder::decode(std::string message) {
    std::vector<std::string> messages = split_string(message, '|');
    std::vector<std::vector<std::string>> informations;
    for (auto message : messages) {
        std::vector<std::string> info = split_string(message, '=');
        informations.push_back(info);
    }

    FixMessage fix_message;

    try {
        for (auto information : informations) {
            std::string tag = information.at(0);
            std::string value = information.at(1);

            if (tag.empty() || value.empty()) {
                std::cerr << "Invalid Tag/Value: " << tag << "=" << value << std::endl;
                return fix_message;
            }

            if (tag == "8") fix_message.begin_string = value;
            if (tag == "9") fix_message.body_length = std::stoi(value);
            if (tag == "35") fix_message.message_type = value;
            if (tag == "34") fix_message.message_sequence_num = std::stoi(value);
            if (tag == "49") fix_message.sender_id = value;
            if (tag == "56") fix_message.target_id = value;
            if (tag == "11") fix_message.ci_order_id = value;
            if (tag == "54") fix_message.side = std::stoi(value);
            if (tag == "55") fix_message.symbol = value;
            if (tag == "44") fix_message.price = std::stod(value);
            if (tag == "59") fix_message.time_in_force = std::stoi(value);
            if (tag == "10") fix_message.check_sum = value;
            if (tag == "38") fix_message.order_quantity = std::stoi(value);
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }

    return fix_message;
}
