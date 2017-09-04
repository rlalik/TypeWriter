cmake_minimum_required(VERSION 3.0.0)

add_executable(tw_demo demo.cpp)
target_link_libraries(tw_demo typewriter)

add_executable(tw_demo_c demo.c)
target_link_libraries(tw_demo_c typewriter)
