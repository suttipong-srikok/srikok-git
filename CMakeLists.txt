cmake_minimum_required(VERSION 3.16)
project(SrikokGit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/gitmanager.cpp
    src/repositorybrowser.cpp
    src/commithistory.cpp
    src/stagingarea.cpp
    src/branchmanager.cpp
    src/remotemanager.cpp
    src/diffviewer.cpp
    src/settings.cpp
)

set(HEADERS
    src/mainwindow.h
    src/gitmanager.h
    src/repositorybrowser.h
    src/commithistory.h
    src/stagingarea.h
    src/branchmanager.h
    src/remotemanager.h
    src/diffviewer.h
    src/settings.h
)

qt_add_executable(SrikokGit ${SOURCES} ${HEADERS})

target_link_libraries(SrikokGit PRIVATE Qt6::Core Qt6::Widgets)

set_target_properties(SrikokGit PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)