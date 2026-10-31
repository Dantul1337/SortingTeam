cmake_minimum_required(VERSION 3.16)

project(SequentialListSorting LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sort_benchmark
    main.cpp
)

if(MSVC)
    target_compile_options(sort_benchmark PRIVATE /W4)
else()
    target_compile_options(sort_benchmark PRIVATE -Wall -Wextra -Wpedantic)
endif()
