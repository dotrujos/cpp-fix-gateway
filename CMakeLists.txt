cmake_minimum_required(VERSION 3.15)
project(CFixGateway CXX)

add_executable(app main.cpp
        src/socket/Socket.cpp
        src/socket/Socket.h)