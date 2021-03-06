cmake_minimum_required(VERSION 3.0)
project(Prog2Beleg)

set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set (PROJECT_RESSOURCE_DIR ${CMAKE_SOURCE_DIR}/res)
set(PROJECT_TEST_DIR ${CMAKE_SOURCE_DIR}/test)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Only on my OSX MBP13
#set(QTDIR "/opt/local/libexec/qt4" CACHE PATH "FOO" FORCE)
#set(QT_QMAKE_EXECUTABLE "/opt/local/libexec/qt4/bin/qmake" CACHE FILEPATH "BAR" FORCE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5QML REQUIRED)
find_package(Qt5Widgets REQUIRED)



include_directories(${Qt_INCLUDE_DIR})

set(core_logic_files
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

set(qt_adapter_files
        ${PROJECT_SOURCE_DIR}/library_qt_adapters.h
        ${PROJECT_SOURCE_DIR}/library_qt_adapters.cpp
        )


add_executable(Prog2Beleg ${PROJECT_SOURCE_DIR}/main.cpp ${SOURCE_FILES} ${core_logic_files} ${qt_adapter_files})
target_link_libraries(Prog2Beleg Qt5::Core Qt5::Quick Qt5::Widgets)
configure_file(${PROJECT_RESSOURCE_DIR}/main_window.qml main_window.qml COPYONLY)

set_property(TARGET Prog2Beleg PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET Prog2Beleg PROPERTY CXX_STANDARD 11)

enable_testing()
add_executable(core_logic_test ${PROJECT_TEST_DIR}/core_logic_tests.cpp ${core_logic_files})
target_link_libraries(core_logic_test Qt5::Test Qt5::Core Qt5::Quick)
add_test(NAME core_logic_test COMMAND core_logic_test)
set_property(TARGET core_logic_test PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET core_logic_test PROPERTY CXX_STANDARD 11)