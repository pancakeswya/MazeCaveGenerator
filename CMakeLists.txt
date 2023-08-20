cmake_minimum_required(VERSION 3.5)

project(MazeCaveGenerator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/base/worker_thread.h
        src/base/worker_thread.cc
        src/model/cave.h
        src/model/cave.cc
        src/model/maze.h
        src/model/maze.cc
        src/view/cave_view.h
        src/view/cave_view.cc
        src/view/maze_view.h
        src/view/maze_view.cc
        src/view/loader.h
        src/view/loader.cc
        src/view/mainwindow.h
        src/view/mainwindow.cc
        ui/mainwindow.ui
        src/main.cc
)

include_directories("includes/base/" "includes/model/" "includes/view/")

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

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

target_link_libraries(MazeCaveGenerator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

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
