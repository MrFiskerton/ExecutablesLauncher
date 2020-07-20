cmake_minimum_required(VERSION 3.17)
project(ExecutablesLauncher VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(
        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo

        -std=c++17 -O0 -g #-O3 -s
)

#====================================================================================

enable_testing()

find_package(GTest REQUIRED)
add_subdirectory(test)



add_executable(ExecutablesLauncher main.cpp LaunchExecutablesInDir.cpp)