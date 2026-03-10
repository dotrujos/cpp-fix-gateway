//
// Created by gabrielaraujo on 09/03/2026.
//

#include "FixDecoder.h"
#include "../models/FixTags.h"
#include "../utils/StringUtils.h"

#include <iostream>
#include <sstream>

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

            int itag = std::stoi(tag);

            if (itag == FixTags::BEGIN_STRING) fix_message.begin_string = value;
            if (itag == FixTags::BODY_LENGTH) fix_message.body_length = std::stoi(value);
            if (itag == FixTags::MESSAGE_TYPE) fix_message.message_type = value;
            if (itag == FixTags::MESSAGE_SEQUENCE_NUM) fix_message.message_sequence_num = std::stoi(value);
            if (itag == FixTags::SENDER_ID) fix_message.sender_id = value;
            if (itag == FixTags::TARGET_ID) fix_message.target_id = value;
            if (itag == FixTags::CI_ORDER_ID) fix_message.ci_order_id = value;
            if (itag == FixTags::SIDE) fix_message.side = std::stoi(value);
            if (itag == FixTags::SYMBOL) fix_message.symbol = value;
            if (itag == FixTags::PRICE) fix_message.price = std::stod(value);
            if (itag == FixTags::TIME_IN_FORCE) fix_message.time_in_force = std::stoi(value);
            if (itag == FixTags::CHECK_SUM) fix_message.check_sum = value;
            if (itag == FixTags::ORDER_QUANTITY) fix_message.order_quantity = std::stoi(value);
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }

    return fix_message;
}
