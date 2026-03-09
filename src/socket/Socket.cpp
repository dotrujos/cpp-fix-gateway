//
// Created by gabrielaraujo on 09/03/2026.
//

#include "Socket.h"

#include <iostream>
#include <unistd.h>

void Socket::init(int maximumconn) {
    serversocket = socket(AF_INET, SOCK_STREAM, 0);

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(8080);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket, reinterpret_cast<struct sockaddr *>(&serveraddress), sizeof(serveraddress));
    listen(serversocket, maximumconn);

    std::cout << "Server started at: " << serveraddress.sin_port << std::endl;

    clientsocket = accept(serversocket, nullptr, nullptr);
}

void Socket::recivemsg(std::function<void(std::string)> callback) {
    char buffer[1024] = {0};
    recv(clientsocket, buffer, sizeof(buffer), 0);

    std::cout << "Recived message: " << buffer << std::endl;

    callback(buffer);
}

void Socket::end() const {
    close(serversocket);
}
