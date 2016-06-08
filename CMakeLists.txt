cmake_minimum_required(VERSION 3.0)
project(Prog2Beleg)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt4 REQUIRED)
include_directories(${Qt_INCLUDE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(Prog2Beleg ${SOURCE_FILES})

target_link_libraries(Prog2Beleg Qt4::QtGui)

set_property(TARGET Prog2Beleg PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET Prog2Beleg PROPERTY CXX_STANDARD 11)