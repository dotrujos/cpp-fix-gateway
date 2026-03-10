//
// Created by gabrielaraujo on 09/03/2026.
//

#include "Socket.h"
#include "../environment/Environment.h"

#include <cstring>
#include <iostream>
#include <unistd.h>

Socket &Socket::getInstance() {
    static Socket instance;
    return instance;
}

Socket::Socket() : serversocket(-1), clientsocket(-1) {
    memset(&serveraddress, 0, sizeof(serveraddress));
}

void Socket::init() {
    std::string port = Environment::getInstance().get("PORT");
    std::string maximum_conn = Environment::getInstance().get("MAXIMUM_CONNECTIONS");

    if (port.empty()) port = "8080";
    if (maximum_conn.empty()) maximum_conn = "5";

    serversocket = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(serversocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(std::stoi(port));
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serversocket, reinterpret_cast<struct sockaddr *>(&serveraddress), sizeof(serveraddress)) < 0) {
        perror("Bind failed");
        return;
    }

    listen(serversocket, std::stoi(maximum_conn));
    std::cout << "Server listening on port: " << port << std::endl;
}

bool Socket::sendmsg(std::string msg) {
    if (clientsocket == -1) {
        std::cerr << "No client found to send messsage" << std::endl;
        return false;
    }

    for (char &c : msg) {
        if (c == '|') c = '\x01';
    }

    ssize_t bytesSent = send(clientsocket, msg.c_str(), msg.length(), 0);

    if (bytesSent == -1) {
        perror("Failed to send message");
        return false;
    }

    return true;
}

bool Socket::wait() {
    std::cout << "Waiting for a new connection..." << std::endl;

    clientsocket = accept(serversocket, nullptr, nullptr);

    if (clientsocket < 0) {
        perror("Accept failed");
        return false;
    }

    std::cout << "New client connected!" << std::endl;
    return true;
}

bool Socket::recivemsg(std::function<void(std::string)> callback) {
    char buffer[1024] = {0};

    ssize_t bytesRead = recv(clientsocket, buffer, sizeof(buffer), 0);

    if (bytesRead <= 0) {
        close(clientsocket);
        clientsocket = -1;
        return false;
    }

    callback(std::string(buffer, bytesRead));
    return true;
}

void Socket::end() const {
    close(serversocket);
}
