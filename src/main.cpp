//
// Created by gabrielaraujo on 09/03/2026.
//

#include <iostream>

#include "engines/FixEngine.h"
#include "socket/Socket.h"
#include "environment/Environment.h"
#include "interactions/ServiceLogonInteraction.h"

void process_message(std::string buffer) {
    std::cout << "My Message is: " << buffer << std::endl;

    Socket::getInstance().sendmsg("Recebi :)");
}

int main(int argc, char* argv[]) {
    std::cout << "Starting FIX Gateway..." << std::endl;
    std::cout << "Repository: https://github.com/dotrujos/fix-gateway" << std::endl;

    const std::vector<std::string_view> args(argv, argv + argc);
    std::string env_path;

    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--env-file" && i + 1 < args.size()) {
            env_path = args[++i];
        }
    }

    if (!env_path.empty()) {
        Environment::getInstance().parseEnv(env_path);
    }

    Socket::getInstance().init();
    auto fix_engine = FixEngine();

    while (true) {
        if (Socket::getInstance().wait()) {

            bool isConnected = true;

            while (isConnected) {
                isConnected = Socket::getInstance().recivemsg([&](std::string msg) {
                    fix_engine.run(msg);
                });
            }

            std::cout << "Connection closed. Returning to wait mode." << std::endl;
        }
    }

    Socket::getInstance().end();

    return 0;
}
