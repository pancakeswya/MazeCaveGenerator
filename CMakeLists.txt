cmake_minimum_required(VERSION 3.5)

project(MazeCaveGenerator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(Maze STATIC
            src/model/maze/generator.cc
            src/model/maze/generator.h
            src/model/maze/solver.cc
            src/model/maze/solver.h)

add_library(Cave STATIC
            src/model/cave/generator.cc
            src/model/cave/generator.h)

add_library(Serializer STATIC
            src/model/serializer.cc
            src/model/serializer.h)

add_library(Model STATIC
            src/model/model.cc
            src/model/model.h)

target_link_libraries(Model Maze Cave Serializer)

add_library(Controller STATIC
            src/controller/controller.cc
            src/controller/controller.h)

target_link_libraries(Controller Model)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(Painter STATIC
            src/view/painter.cc
            src/view/painter.h)

target_link_libraries(Painter Qt${QT_VERSION_MAJOR}::Widgets)

add_library(Worker STATIC
            src/concurrency/worker_thread.cc
            src/concurrency/worker_thread.h)

target_link_libraries(Worker Qt${QT_VERSION_MAJOR}::Widgets)

set(PROJECT_SOURCES
            src/view/loader.cc
            src/view/loader.h
            src/view/view.cc
            src/view/view.h
            src/view/view.ui
            src/main.cc
)

include_directories("src")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MazeCaveGenerator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(MazeCaveGenerator
            ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(MazeCaveGenerator PRIVATE Painter Worker Controller Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(MazeCaveGenerator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MazeCaveGenerator)
endif()
