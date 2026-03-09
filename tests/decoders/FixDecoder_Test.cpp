//
// Created by gabrielaraujo on 09/03/2026.
//

#include "../../src/decoders/FixDecoder.h"

#include <gtest/gtest.h>

TEST(FixDecoderUnitTest, DecodeMessageSuccessfully) {
    std::string message = "8=FIX.4.4|9=145|35=D|34=2|49=CLIENTE_XYZ|52=20260309-14:10:05.120|56=B3_EXCHANGE|11=ID_789|21=1|55=VALE3|54=1|38=500|40=2|44=70.25|59=0|10=092|";

    auto decoder = FixDecoder();

    FixMessage decodedMessage = decoder.decode(message);

    ASSERT_EQ(decodedMessage.begin_string, "FIX.4.4");
    ASSERT_EQ(decodedMessage.body_length, 145);
    ASSERT_EQ(decodedMessage.message_type, "D");
    ASSERT_EQ(decodedMessage.message_sequence_num, 2);
    ASSERT_EQ(decodedMessage.sender_id, "CLIENTE_XYZ");
    ASSERT_EQ(decodedMessage.target_id, "B3_EXCHANGE");

    ASSERT_EQ(decodedMessage.ci_order_id, "ID_789");
    ASSERT_EQ(decodedMessage.symbol, "VALE3");
    ASSERT_EQ(decodedMessage.side, 1);
    ASSERT_EQ(decodedMessage.order_quantity, 500);
    ASSERT_DOUBLE_EQ(decodedMessage.price, 70.25);
    ASSERT_EQ(decodedMessage.time_in_force, 0);

    ASSERT_EQ(decodedMessage.check_sum, "092");
}