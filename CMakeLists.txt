cmake_minimum_required(VERSION 3.27)
project(awesome_linux C)

set(CMAKE_C_STANDARD 11)

add_executable(awesome_linux main.c
        readwrite.h
        pretty.h
        pretty.c
        readwrite.c)
