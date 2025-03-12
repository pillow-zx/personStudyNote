cmake_minimum_required(VERSION 3.30)
project(clion C)

set(CMAKE_C_STANDARD 11)

add_executable(clion main.c
        linkedlist.c
        linkedlist.h)
