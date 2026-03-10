#include <gtest/gtest.h>
#include "../../src/socket/Socket.h"
#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <future>

TEST(SocketIntegrationTest, ReciveMsgSuccessfully) {
    std::string received_msg;
    std::promise<void> message_received_promise;
    auto message_received_future = message_received_promise.get_future();

    std::thread server_thread([&received_msg, &message_received_promise]() {
        Socket::getInstance().init();
        Socket::getInstance().recivemsg([&received_msg, &message_received_promise](std::string msg) {
            received_msg = msg;
            message_received_promise.set_value();
        });
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_GT(client_fd, 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    int connect_res = connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    ASSERT_EQ(connect_res, 0) << "Failed to connect to the Socket::getInstance()";

    std::string test_message = "Hello from client!";
    send(client_fd, test_message.c_str(), test_message.length(), 0);

    if (message_received_future.wait_for(std::chrono::seconds(2)) == std::future_status::ready) {
        EXPECT_STREQ(received_msg.c_str(), test_message.c_str());
    } else {
        FAIL() << "Message reception timed out";
    }

    close(client_fd);
    Socket::getInstance().end();
    if (server_thread.joinable()) {
        server_thread.join();
    }
}
