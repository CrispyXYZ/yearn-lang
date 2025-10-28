cmake_minimum_required(VERSION 3.20)
project(yearn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(yearn
        src/main.cpp
        src/token.cpp
        src/interpreter.cpp
        src/interpreter.h
)
