cmake_minimum_required(VERSION 3.10)
project(Fledasty C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Lib/Headers")

if(WIN32)
    set (HALLOCY_LIB_PATH "${CMAKE_SOURCE_DIR}/Lib/Windows/Hallocy.lib")
elseif(UNIX)
    set (HALLOCY_LIB_PATH "${CMAKE_SOURCE_DIR}/Lib/Linux/libHallocy.a")
endif()

include_directories(${PROJECT_SOURCE_DIR}/Include)
include_directories(${LIB_INCLUDE_DIR})
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/Src/*.c")

add_library(Fledasty STATIC ${SRC_FILES})
add_executable(FledastyApp ${PROJECT_SOURCE_DIR}/Src/Main.c)

target_link_libraries(Fledasty PRIVATE ${HALLOCY_LIB_PATH})
target_link_libraries(FledastyApp Fledasty)

if (MSVC)
    target_compile_options(Fledasty PRIVATE /W4 /Zl)
else()
    target_compile_options(Fledasty PRIVATE -Wall -Wextra -pedantic)
endif()