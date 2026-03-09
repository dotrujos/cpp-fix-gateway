//
// Created by gabrielaraujo on 09/03/2026.
//

#include <functional>
#include <string>
#include <netinet/in.h>

#ifndef CFIXGATEWAY_SOCKET_H
#define CFIXGATEWAY_SOCKET_H

class Socket {
private:
    sockaddr_in serveraddress{};
    int serversocket;
    int clientsocket;

    Socket();
public:
    static Socket& getInstance();
    void init(int maximumconn);
    void recivemsg(std::function<void(std::string)> callback);
    bool sendmsg(std::string msg);
    void end() const;

    Socket(Socket const&) = delete;
    void operator=(Socket const&) = delete;
};


#endif //CFIXGATEWAY_SOCKET_H