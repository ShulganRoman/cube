cmake_minimum_required(VERSION 3.28)
project(so_cube)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.5 COMPONENTS system graphics audio REQUIRED)

add_executable(so_cube main.cpp
        camstream.h)

target_link_libraries(so_cube sfml-system sfml-graphics sfml-audio)
