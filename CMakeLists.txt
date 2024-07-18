cmake_minimum_required(VERSION 3.26.0)
project(ToyGameEngine VERSION 0.0.1)


if (MSVC)
    add_compile_options("/utf-8")
    add_compile_options("/arch:AVX2")
    add_compile_options("/GL")
    add_compile_options("/MP")
    add_link_options("/LTCG")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets OpenGL Gui Core Multimedia)

add_subdirectory(src)
include_directories(inc)
file(GLOB QOBJECT_HEADS inc/Demo/MainWindow.hpp)

qt_add_executable(ToyGameEngine
    MANUAL_FINALIZATION
    src/Demo/main.cpp
    ${QOBJECT_HEADS}

    ${DEMO_SOURCES}
    ${CANVAS_SOURCES}
    ${MATH_SOURCES}
    ${SPIRIT_SOURCES}
    ${SCENE_SOURCES}
    ${RESOURCE_SOURCES}
)

target_link_libraries(ToyGameEngine PRIVATE Qt6::Widgets Qt6::OpenGLWidgets Qt6::OpenGL Qt6::Gui Qt6::Core Qt6:Multimedia)
target_compile_definitions(ToyGameEngine PUBLIC POINTERHOLDER_TRANSITION=0)

qt_finalize_executable(ToyGameEngine)