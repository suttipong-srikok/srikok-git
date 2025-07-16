cmake_minimum_required(VERSION 3.16)
project(SrikokGit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform-specific compiler flags
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Enable UTF-8 support
    add_definitions(-DUNICODE -D_UNICODE)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

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

# Platform-specific properties
set_target_properties(SrikokGit PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# Windows-specific settings
if(WIN32)
    # Set output directory for Windows
    set_target_properties(SrikokGit PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
    )
    
    # Windows manifest and icon support
    if(EXISTS "${CMAKE_SOURCE_DIR}/resources/windows/SrikokGit.rc")
        target_sources(SrikokGit PRIVATE resources/windows/SrikokGit.rc)
    endif()
    
    # Link Windows libraries
    target_link_libraries(SrikokGit PRIVATE ws2_32)
endif()

# Install rules
install(TARGETS SrikokGit
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)