//
// Created by gabrielaraujo on 10/03/2026.
//

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <iomanip>

std::string formatFix(std::string msg) {
    for (char &c : msg) if (c == '|') c = '\x01';
    return msg;
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Erro ao criar socket" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Endereço inválido" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Conexão falhou. O servidor está rodando na porta 8080?" << std::endl;
        return -1;
    }

    std::cout << "Conectado ao servidor FIX na porta 8080!" << std::endl;

    std::string raw_body = "35=A|49=SENDER|56=TARGET|34=1|52=20260310-15:00:00|98=0|108=30|";
    std::string fix_msg = "8=FIX.4.4|9=" + std::to_string(raw_body.length()) + "|" + raw_body;

    fix_msg += "10=063|";

    std::string final_packet = fix_msg;

    send(sock, final_packet.c_str(), final_packet.length(), 0);
    std::cout << "Mensagem de Logon enviada: " << fix_msg << std::endl;

    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    std::cout << "Resposta do servidor: " << buffer << std::endl;

    close(sock);
    return 0;
}