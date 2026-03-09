//
// Created by gabrielaraujo on 09/03/2026.
//

#ifndef CFIXGATEWAY_FIXMESSAGE_H
#define CFIXGATEWAY_FIXMESSAGE_H
#include <string>

typedef struct  {
    std::string begin_string;
    int body_length;
    std::string message_type;
    int message_sequence_num;
    std::string sender_id;
    std::string target_id;
    std::string ci_order_id;
    int side;
    std::string symbol;
    int order_quantity;
    double price;
    int time_in_force;
    std::string check_sum;
} FixMessage;

#endif //CFIXGATEWAY_FIXMESSAGE_H