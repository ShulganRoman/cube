cmake_minimum_required(VERSION 3.28)
project(so_cube)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.5 COMPONENTS system graphics audio REQUIRED)

add_executable(so_cube main.cpp)

target_include_directories(so_cube PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(so_cube PRIVATE cxx_std_20)

target_link_libraries(so_cube sfml-system sfml-graphics sfml-audio)
