//
// Created by gabrielaraujo on 09/03/2026.
//

#include <iostream>

#include "src/socket/Socket.h"
#include "src/environment/Environment.h"

void process_message(std::string buffer) {
    std::cout << "My Message is: " << buffer << std::endl;

    Socket::getInstance().sendmsg("Recebi :)");
}

int main(int argc, char* argv[]) {
    std::cout << "Starting FIX Gateway..." << std::endl;
    std::cout << "Repository: https://github.com/dotrujos/cpp-fix-gateway" << std::endl;

    const std::vector<std::string_view> args(argv, argv + argc);
    std::string env_path;

    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--env-file" && i + 1 < args.size()) {
            env_path = args[++i];
        }
    }

    if (!env_path.empty()) {
        Environment::getInstance().parseEnv(env_path);
    } else {
       Environment::getInstance().parseEnv(".env"); 
    }

    Socket::getInstance().init();

    while (true) {
        Socket::getInstance().recivemsg(process_message);
    }

    Socket::getInstance().end();

    return 0;
}
