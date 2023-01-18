cmake_minimum_required(VERSION 3.5)

project(AndroidController2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sensors Network)
set(HEADERS
    src/dpadbutton.h
    src/gamepad.h
    src/gamepadbutton.h
    src/gamepadellipsebutton.h
    src/gamepadnamedbutton.h
    src/gamepadrectbutton.h
    src/joystick.h
    src/mainwidget.h
    src/mainwindow.h
    src/settingswidget.h
    src/util.h
)

set(PROJECT_SOURCES
    ${HEADERS}
    src/main.cpp
    src/dpadbutton.cpp
    src/gamepad.cpp
    src/gamepadbutton.cpp
    src/gamepadellipsebutton.cpp
    src/gamepadnamedbutton.cpp
    src/gamepadrectbutton.cpp
    src/joystick.cpp
    src/mainwidget.cpp
    src/mainwindow.cpp
    src/settingswidget.cpp
    resources/darkstyle.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AndroidController2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET AndroidController2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(AndroidController2 SHARED
            ${PROJECT_SOURCES}
        )
        set(ANDROID_PACKAGE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/android CACHE INTERNAL "")

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AndroidController2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(AndroidController2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sensors Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(AndroidController2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS AndroidController2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
target_compile_options(AndroidController2 PRIVATE -Wall -Wextra -Wpedantic -Werror)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AndroidController2)
endif()
