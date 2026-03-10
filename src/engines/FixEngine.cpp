//
// Created by gabrielaraujo on 09/03/2026.
//

#include "FixEngine.h"

#include <iostream>

#include "../interactions/ServiceLogonInteraction.h"

void FixEngine::run(const std::string &fix) {
    FixMessage message = fix_decoder.decode(fix);

    if (message.message_type == "A") {
        auto service = ServiceLogonInteraction();
        service.perform(message);
    }
}
