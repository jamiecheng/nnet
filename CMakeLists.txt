cmake_minimum_required(VERSION 3.6)
project(net)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES xor.cpp
        activations.h
        array.h
        network.h)
add_executable(net ${SOURCE_FILES})