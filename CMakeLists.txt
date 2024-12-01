cmake_minimum_required(VERSION 3.24)

project(x)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(x
    dl.cpp
    error.cpp
    fs.cpp
    mmap.cpp
)
target_include_directories(x PUBLIC include)