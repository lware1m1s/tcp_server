cmake_minimum_required(VERSION 3.13)
project(tcp_srv)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

add_executable(tcp_server
    main.cpp
    src/client.cpp
    src/counter.cpp
    src/tcp_srv.cpp)