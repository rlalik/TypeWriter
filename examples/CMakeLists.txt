cmake_minimum_required(VERSION 3.0.0)

add_executable(demo demo.cpp)
target_link_libraries(demo typewriter)

add_executable(demo_c demo.c)
target_link_libraries(demo_c typewriter)
