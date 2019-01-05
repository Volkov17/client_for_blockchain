
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



project(client_for_blockchain)
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Wno-unused-command-line-argument -Wshadow -Wnon-virtual-dtor -pedantic")


# enum your files and delete this comment


add_executable(client_for_blockchain project/client_main.cpp)
