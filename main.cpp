//
// Created by gabrielaraujo on 09/03/2026.
//

#include <iostream>

#include "src/socket/Socket.h"

void process_message(std::string buffer) {
    std::cout << "My Message is: " << buffer << std::endl;
}

int main() {
    auto socket = Socket();

    socket.init(5);
    socket.recivemsg(process_message);
    socket.end();

    return 0;
}
