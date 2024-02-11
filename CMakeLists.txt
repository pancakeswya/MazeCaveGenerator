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
            src/model/maze/serializer.cc
            src/model/maze/serializer.h
            src/model/maze/solver.cc
            src/model/maze/solver.h)

set_target_properties(Maze PROPERTIES OUTPUT_NAME "maze")

add_library(Cave STATIC
            src/model/cave/generator.cc
            src/model/cave/generator.h
            src/model/cave/serializer.cc
            src/model/cave/serializer.h)

set_target_properties(Cave PROPERTIES OUTPUT_NAME "cave")

add_library(Model STATIC
            src/model/maze_model.cc
            src/model/maze_model.h
            src/model/cave_model.cc
            src/model/cave_model.h)

target_link_libraries(Model Maze Cave)

set_target_properties(Model PROPERTIES OUTPUT_NAME "model")

add_library(Controller STATIC
            src/controller/controller.cc
            src/controller/controller.h)

target_link_libraries(Controller Model)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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

target_link_libraries(MazeCaveGenerator PRIVATE Worker Controller Qt${QT_VERSION_MAJOR}::Widgets)

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
