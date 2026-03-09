cmake_minimum_required(VERSION 3.15)
project(CFixGateway CXX)

find_package(GTest CONFIG REQUIRED)

add_executable(app main.cpp
        src/socket/Socket.cpp
        src/socket/Socket.h)

include(CTest)
enable_testing()

add_executable(unit_tests
        tests/socket/Socket_Test.cpp
        src/socket/Socket.cpp
        src/socket/Socket.h)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)
add_test(NAME unit_tests COMMAND unit_tests)