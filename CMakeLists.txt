cmake_minimum_required(VERSION 3.16)
project(divide-simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(divide-simulator main.cpp TestElement.cpp TestElement.h Result.cpp Result.h Restoring.cpp Restoring.h NonRestoring.cpp NonRestoring.h)
