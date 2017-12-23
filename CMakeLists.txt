cmake_minimum_required(VERSION 3.8)
project(_asd2_pliki_programu)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        plecak.cpp
        plecak.h
        plecak_main.cpp)

add_executable(_asd2_pliki_programu ${SOURCE_FILES})