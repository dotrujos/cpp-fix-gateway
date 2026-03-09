cmake_minimum_required(VERSION 3.15)
project(CFixGateway CXX)

find_package(GTest CONFIG REQUIRED)

add_executable(app main.cpp
        src/socket/Socket.cpp
        src/socket/Socket.h)

#add_executable(unit_tests)
#target_link_libraries(unit_tests PRIVATE GTest::gtest_main)