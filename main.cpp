//
// Created by gabrielaraujo on 09/03/2026.
//

#include <iostream>

#include "src/socket/Socket.h"

int main(void) {
    auto socket = Socket();

    socket.init(5);

    const int clientSocket = accept(socket.serversocket, nullptr, nullptr);
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::cout << buffer << std::endl;

    socket.end();

    return 0;
}
