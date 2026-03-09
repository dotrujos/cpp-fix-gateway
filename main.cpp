//
// Created by gabrielaraujo on 09/03/2026.
//

#include <iostream>

#include "src/socket/Socket.h"

void process_message(std::string buffer) {
    std::cout << "My Message is: " << buffer << std::endl;

    Socket::getInstance().sendmsg("Recebi :)");
}

int main() {
    Socket::getInstance().init(5);

    while (true) {
        Socket::getInstance().recivemsg(process_message);
    }

    Socket::getInstance().end();

    return 0;
}
