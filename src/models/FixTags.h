//
// Created by gabrielaraujo on 10/03/2026.
//

#ifndef CFIXGATEWAY_FIXTAGS_H
#define CFIXGATEWAY_FIXTAGS_H

enum FixTags {
    BEGIN_STRING = 8,
    BODY_LENGTH = 9,
    CHECK_SUM = 10,
    CI_ORDER_ID = 11,
    MESSAGE_SEQUENCE_NUM = 34,
    MESSAGE_TYPE = 35,
    ORDER_QUANTITY = 38,
    PRICE = 44,
    SENDER_ID = 49,
    SIDE = 54,
    SYMBOL = 55,
    TARGET_ID = 56,
    TIME_IN_FORCE = 59
};

#endif //CFIXGATEWAY_FIXTAGS_H