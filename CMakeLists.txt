cmake_minimum_required(VERSION 3.31)
project(image_ascii_convertor)

set(CMAKE_CXX_STANDARD 20)

# creating a library for the convertor logic
add_library(Convertor
        convertor/convertor.cpp
        convertor/convertor.h
)

add_executable(image_ascii_convertor main.cpp)
target_link_libraries(Convertor)
