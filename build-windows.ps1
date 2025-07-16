# Windows PowerShell Build Script for Srikok Git
# This script builds the application using CMake and Qt 6

Write-Host "Building Srikok Git for Windows..." -ForegroundColor Green
Write-Host ""

# Function to check if a command exists
function Test-Command {
    param($Command)
    try {
        Get-Command $Command -ErrorAction Stop
        return $true
    } catch {
        return $false
    }
}

# Check if Qt6 is installed
if (-not (Test-Command "qmake")) {
    Write-Host "Error: Qt6 is not found in PATH" -ForegroundColor Red
    Write-Host "Please install Qt6 and add it to your PATH" -ForegroundColor Yellow
    Write-Host "Download from: https://www.qt.io/download-qt-installer" -ForegroundColor Yellow
    Read-Host "Press Enter to exit"
    exit 1
}

# Check if CMake is installed
if (-not (Test-Command "cmake")) {
    Write-Host "Error: CMake is not found in PATH" -ForegroundColor Red
    Write-Host "Please install CMake and add it to your PATH" -ForegroundColor Yellow
    Write-Host "Download from: https://cmake.org/download/" -ForegroundColor Yellow
    Read-Host "Press Enter to exit"
    exit 1
}

# Check if we have a C++ compiler
if (-not (Test-Command "cl") -and -not (Test-Command "g++")) {
    Write-Host "Error: No C++ compiler found" -ForegroundColor Red
    Write-Host "Please install Visual Studio or MinGW" -ForegroundColor Yellow
    Read-Host "Press Enter to exit"
    exit 1
}

# Create build directory
if (-not (Test-Path "build")) {
    Write-Host "Creating build directory..." -ForegroundColor Yellow
    New-Item -ItemType Directory -Name "build" | Out-Null
}

Set-Location "build"

# Configure with CMake
Write-Host "Configuring with CMake..." -ForegroundColor Yellow
$configResult = Start-Process -FilePath "cmake" -ArgumentList "..", "-DCMAKE_BUILD_TYPE=Release" -Wait -PassThru -NoNewWindow

if ($configResult.ExitCode -ne 0) {
    Write-Host "Error: CMake configuration failed" -ForegroundColor Red
    Set-Location ".."
    Read-Host "Press Enter to exit"
    exit 1
}

# Build the application
Write-Host "Building application..." -ForegroundColor Yellow
$buildResult = Start-Process -FilePath "cmake" -ArgumentList "--build", ".", "--config", "Release" -Wait -PassThru -NoNewWindow

if ($buildResult.ExitCode -ne 0) {
    Write-Host "Error: Build failed" -ForegroundColor Red
    Set-Location ".."
    Read-Host "Press Enter to exit"
    exit 1
}

Write-Host ""
Write-Host "Build successful!" -ForegroundColor Green
Write-Host "Executable location: build\Release\SrikokGit.exe" -ForegroundColor Green
Write-Host ""

# Check if executable was created
if (Test-Path "Release\SrikokGit.exe") {
    Write-Host "You can run the application with: build\Release\SrikokGit.exe" -ForegroundColor Cyan
} elseif (Test-Path "SrikokGit.exe") {
    Write-Host "You can run the application with: build\SrikokGit.exe" -ForegroundColor Cyan
} else {
    Write-Host "Warning: Executable not found in expected location" -ForegroundColor Yellow
}

Set-Location ".."
Read-Host "Press Enter to exit"