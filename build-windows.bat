@echo off
REM Windows Build Script for Srikok Git
REM This script builds the application using CMake and Qt 6

echo Building Srikok Git for Windows...
echo.

REM Check if Qt6 is installed
where qmake >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: Qt6 is not found in PATH
    echo Please install Qt6 and add it to your PATH
    echo Download from: https://www.qt.io/download-qt-installer
    pause
    exit /b 1
)

REM Check if CMake is installed
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: CMake is not found in PATH
    echo Please install CMake and add it to your PATH
    echo Download from: https://cmake.org/download/
    pause
    exit /b 1
)

REM Check if we have a C++ compiler
where cl >nul 2>nul
if %errorlevel% neq 0 (
    where g++ >nul 2>nul
    if %errorlevel% neq 0 (
        echo Error: No C++ compiler found
        echo Please install Visual Studio or MinGW
        pause
        exit /b 1
    )
)

REM Create build directory
if not exist "build" mkdir build
cd build

REM Configure with CMake
echo Configuring with CMake...
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=%Qt6_DIR%
if %errorlevel% neq 0 (
    echo Error: CMake configuration failed
    pause
    exit /b 1
)

REM Build the application
echo Building application...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo Error: Build failed
    pause
    exit /b 1
)

echo.
echo Build successful!
echo Executable location: build\Release\SrikokGit.exe
echo.

REM Check if executable was created
if exist "Release\SrikokGit.exe" (
    echo You can run the application with: build\Release\SrikokGit.exe
) else if exist "SrikokGit.exe" (
    echo You can run the application with: build\SrikokGit.exe
) else (
    echo Warning: Executable not found in expected location
)

pause