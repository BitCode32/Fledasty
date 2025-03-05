cmake_minimum_required(VERSION 3.10)
project(Fledasty C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/Include)
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/Src/*.c")

add_library(Fledasty STATIC ${SRC_FILES})
add_executable(FledastyApp ${PROJECT_SOURCE_DIR}/Src/Main.c)

target_link_libraries(FledastyApp Fledasty)

if (MSVC)
    target_compile_options(Fledasty PRIVATE /W4)
else()
    target_compile_options(Fledasty PRIVATE -Wall -Wextra -pedantic)
endif()