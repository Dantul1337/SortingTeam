cmake_minimum_required(VERSION 3.16)

project(SequentialListSorting LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(sort_benchmark
    main.cpp
    structures/linked_list.cpp
    structures/data_loader.cpp
    benchmark/benchmark.cpp
    benchmark/registry.cpp
)

foreach(name insertion merge quick radix)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/algorithms/${name}_sort.cpp")
        target_sources(sort_benchmark PRIVATE algorithms/${name}_sort.cpp)
    else()
        message(STATUS "Algorithm '${name}': using STUB (algorithms/${name}_sort.cpp not found)")
        target_sources(sort_benchmark PRIVATE benchmark/stubs/${name}_sort_stub.cpp)
    endif()
endforeach()

target_include_directories(sort_benchmark PRIVATE include benchmark ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(sort_benchmark PRIVATE SORT_PROJECT_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")

if(MSVC)
    target_compile_options(sort_benchmark PRIVATE /W4)
else()
    target_compile_options(sort_benchmark PRIVATE -Wall -Wextra -Wpedantic)
endif()