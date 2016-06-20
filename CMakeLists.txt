cmake_minimum_required(VERSION 3.0)
project(Prog2Beleg)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Only on my OSX MBP13
#set(QTDIR "/opt/local/libexec/qt4" CACHE PATH "FOO" FORCE)
#set(QT_QMAKE_EXECUTABLE "/opt/local/libexec/qt4/bin/qmake" CACHE FILEPATH "BAR" FORCE)

find_package(Qt4 REQUIRED)

include_directories(${Qt_INCLUDE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(Prog2Beleg ${SOURCE_FILES})

if(NOT(Qt4_FOUND))
    target_link_libraries(Prog2Beleg Qt5::Widgets)
    else()
    target_link_libraries(Prog2Beleg Qt4::QtCore Qt4::QtDeclarative)
endif()

configure_file(main_window.qml main_window.qml COPYONLY)


set_property(TARGET Prog2Beleg PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET Prog2Beleg PROPERTY CXX_STANDARD 11)