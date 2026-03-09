//
// Created by gabrielaraujo on 09/03/2026.
//

#include <netinet/in.h>

#ifndef CFIXGATEWAY_SOCKET_H
#define CFIXGATEWAY_SOCKET_H

class Socket {
private:
    sockaddr_in serveraddress;
public:
    int serversocket;
    void init(int maximumconn);
    void end() const;
};


#endif //CFIXGATEWAY_SOCKET_H