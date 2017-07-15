cmake_minimum_required(VERSION 3.6)
project(xor)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES xor.cpp
        ../../include/activations.h
        ../../include/array.h
        ../../include/network.h)
add_executable(xor ${SOURCE_FILES})