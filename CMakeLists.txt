cmake_minimum_required(VERSION 3.0)
project(Prog2Beleg)

set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set (PROJECT_RESSOURCE_DIR ${CMAKE_SOURCE_DIR}/res)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Only on my OSX MBP13
#set(QTDIR "/opt/local/libexec/qt4" CACHE PATH "FOO" FORCE)
#set(QT_QMAKE_EXECUTABLE "/opt/local/libexec/qt4/bin/qmake" CACHE FILEPATH "BAR" FORCE)

find_package(Qt4 REQUIRED)

include_directories(${Qt_INCLUDE_DIR})

set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/medium.cpp
        ${PROJECT_SOURCE_DIR}/medium.h
        ${PROJECT_SOURCE_DIR}/book.cpp
        ${PROJECT_SOURCE_DIR}/book.h
        ${PROJECT_SOURCE_DIR}/dvd.cpp
        ${PROJECT_SOURCE_DIR}/dvd.h
        ${PROJECT_SOURCE_DIR}/person.cpp
        ${PROJECT_SOURCE_DIR}/person.h
        ${PROJECT_SOURCE_DIR}/library.cpp
        ${PROJECT_SOURCE_DIR}/library.h
        ${PROJECT_SOURCE_DIR}/library_file.h)
add_executable(Prog2Beleg ${SOURCE_FILES})

if(NOT(Qt4_FOUND))
    target_link_libraries(Prog2Beleg Qt5::Widgets)
    else()
    target_link_libraries(Prog2Beleg Qt4::QtCore Qt4::QtDeclarative)
endif()

configure_file(${PROJECT_RESSOURCE_DIR}/main_window.qml main_window.qml COPYONLY)


set_property(TARGET Prog2Beleg PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET Prog2Beleg PROPERTY CXX_STANDARD 11)