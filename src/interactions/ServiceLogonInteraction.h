//
// Created by gabrielaraujo on 10/03/2026.
//

#ifndef CFIXGATEWAY_SERVICELOGON_H
#define CFIXGATEWAY_SERVICELOGON_H
#include "../models/FixMessage.h"


class ServiceLogonInteraction {
public:
    void perform(FixMessage message);
};


#endif //CFIXGATEWAY_SERVICELOGON_H