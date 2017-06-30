cmake_minimum_required(VERSION 3.6)
project(net)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp net.hpp layer.hpp neuron.hpp array.hpp)
add_executable(net ${SOURCE_FILES})