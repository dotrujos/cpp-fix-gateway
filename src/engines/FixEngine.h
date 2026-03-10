//
// Created by gabrielaraujo on 09/03/2026.
//

#ifndef CFIXGATEWAY_FIXENGINE_H
#define CFIXGATEWAY_FIXENGINE_H

#include <string>
#include "../decoders/FixDecoder.h"

class FixEngine {
private:
    FixDecoder fix_decoder = FixDecoder();
public:
    void run(const std::string &fix);
};


#endif //CFIXGATEWAY_FIXENGINE_H