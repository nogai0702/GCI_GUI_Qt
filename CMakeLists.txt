cmake_minimum_required(VERSION 3.16)

project(GciGui VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/core/GciCalculator.h
    src/core/GciCalculator.cpp
    src/gui/MainWindow.h
    src/gui/MainWindow.cpp
    src/gui/MainWindow.ui
    resources.qrc
)

if(APPLE)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER my.example.gci-gui)
    set(MACOSX_BUNDLE_BUNDLE_EXTENSION "")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_COPYRIGHT "Copyright © 2026")
endif()

add_executable(GciGui ${PROJECT_SOURCES})

# If no version was passed (e.g., building locally), default to "dev"
if(NOT DEFINED APP_VERSION)
    set(APP_VERSION "dev")
endif()

# Pass the version string to the C++ compiler
# The escaped quotes (\" \") are crucial so C++ reads it as a string literal
target_compile_definitions(GciGui PRIVATE APP_VERSION=\"${APP_VERSION}\")

target_link_libraries(GciGui PRIVATE Qt6::Widgets dwmapi)

install(TARGETS GciGui
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
