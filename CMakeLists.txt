cmake_minimum_required(VERSION 3.16)
project(PhotoStudioManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
)

list(FILTER SOURCES EXCLUDE REGEX ".*main\\.c$")

add_executable(photo_studio ${SOURCES})