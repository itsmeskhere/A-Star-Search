cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 17)

project(a_star_search)

include_directories(include)

add_executable(a_star_search src/main.cpp src/board.cpp src/a_star_search.cpp)