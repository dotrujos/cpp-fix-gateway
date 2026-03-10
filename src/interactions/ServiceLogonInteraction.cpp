//
// Created by gabrielaraujo on 10/03/2026.
//

#include "ServiceLogonInteraction.h"

#include "../models/FixMessage.h"
#include "../socket/Socket.h"

void ServiceLogonInteraction::perform(FixMessage message) {
    Socket::getInstance().sendmsg("35=A");
}
