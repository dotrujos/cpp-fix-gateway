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
    sockaddr_in serveraddress;
public:
    int serversocket;
    int clientsocket;
    void init(int maximumconn);
    void recivemsg(std::function<void(std::string)> callback);
    void end() const;
};


#endif //CFIXGATEWAY_SOCKET_H