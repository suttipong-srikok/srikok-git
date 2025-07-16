# Building Srikok Git on Windows

This guide provides comprehensive instructions for building and running Srikok Git on Windows operating systems.

## System Requirements

### Minimum Requirements
- **Operating System**: Windows 10 version 1903 or later
- **Architecture**: x64 (64-bit)
- **RAM**: 4 GB minimum, 8 GB recommended
- **Storage**: 2 GB free space for build tools and dependencies

### Recommended Requirements
- **Operating System**: Windows 11 or Windows 10 version 21H2
- **Architecture**: x64 (64-bit)
- **RAM**: 8 GB or more
- **Storage**: 5 GB free space

## Prerequisites

### 1. Install Git for Windows
```powershell
# Download and install from: https://git-scm.com/download/win
# Or use Windows Package Manager (winget)
winget install Git.Git
```

### 2. Install Visual Studio Build Tools or Visual Studio
Choose one of the following options:

#### Option A: Visual Studio 2022 (Recommended)
```powershell
# Download from: https://visualstudio.microsoft.com/downloads/
# Select "Desktop development with C++" workload
# Ensure C++ CMake Tools are included
```

#### Option B: Visual Studio Build Tools 2022
```powershell
# Download from: https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022
# Select "C++ build tools" workload
```

#### Option C: MinGW-w64 (Alternative)
```powershell
# Download from: https://www.mingw-w64.org/downloads/
# Or use MSYS2: https://www.msys2.org/
```

### 3. Install CMake
```powershell
# Download from: https://cmake.org/download/
# Or use winget
winget install Kitware.CMake
```

### 4. Install Qt 6
#### Option A: Qt Online Installer (Recommended)
```powershell
# Download from: https://www.qt.io/download-qt-installer
# Select Qt 6.5.0 or later
# Choose "Desktop gcc 64-bit" or "MSVC 2022 64-bit"
```

#### Option B: Qt from vcpkg
```powershell
# Install vcpkg first
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\\bootstrap-vcpkg.bat
.\\vcpkg integrate install

# Install Qt6
.\\vcpkg install qt6-base:x64-windows
.\\vcpkg install qt6-tools:x64-windows
```

## Environment Setup

### 1. Configure Environment Variables
Add the following to your system PATH:
```
C:\\Qt\\6.5.0\\msvc2022_64\\bin          # Qt binaries
C:\\Qt\\Tools\\CMake_64\\bin             # Qt CMake (if using Qt installer)
C:\\Program Files\\CMake\\bin            # CMake
C:\\Program Files\\Git\\bin              # Git
```

### 2. Set Qt6_DIR (if needed)
```powershell
# If Qt6 is not found automatically, set Qt6_DIR
$env:Qt6_DIR = "C:\\Qt\\6.5.0\\msvc2022_64\\lib\\cmake\\Qt6"
```

### 3. Configure Visual Studio Environment
```powershell
# For Visual Studio 2022
# Open "Developer Command Prompt for VS 2022" or
# Open "Developer PowerShell for VS 2022"
```

## Building the Application

### Method 1: Using Batch Script (Easiest)
```batch
# Navigate to project directory
cd C:\\path\\to\\srikok-git

# Run the build script
build-windows.bat
```

### Method 2: Using PowerShell Script
```powershell
# Navigate to project directory
cd C:\\path\\to\\srikok-git

# Set execution policy if needed
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

# Run the build script
.\\build-windows.ps1
```

### Method 3: Manual Build Steps
```powershell
# Navigate to project directory
cd C:\\path\\to\\srikok-git

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:\\Qt\\6.5.0\\msvc2022_64"

# Build the application
cmake --build . --config Release

# Or build with specific generator
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

## Build Configuration Options

### Debug Build
```powershell
# Configure for debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:\\Qt\\6.5.0\\msvc2022_64"

# Build debug version
cmake --build . --config Debug
```

### Release Build with Optimizations
```powershell
# Configure for optimized release
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="/O2 /Ob2" -DCMAKE_PREFIX_PATH="C:\\Qt\\6.5.0\\msvc2022_64"

# Build release version
cmake --build . --config Release
```

### Build with Ninja (Faster)
```powershell
# Install Ninja
winget install Ninja-build.Ninja

# Configure with Ninja generator
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:\\Qt\\6.5.0\\msvc2022_64"

# Build with Ninja
ninja
```

## Running the Application

### After Successful Build
```powershell
# Navigate to build directory
cd build

# Run the application
.\\Release\\SrikokGit.exe
# Or
.\\Debug\\SrikokGit.exe
```

### Required DLLs
The application needs these Qt DLLs in the same directory:
- Qt6Core.dll
- Qt6Gui.dll
- Qt6Widgets.dll
- Plus platform plugins in platforms/ subdirectory

## Deployment

### Create Deployment Package
```powershell
# Use windeployqt to gather dependencies
cd build\\Release
windeployqt.exe SrikokGit.exe

# This creates a deployable package with all required DLLs
```

### Manual Deployment
```powershell
# Copy required Qt DLLs to application directory
copy "C:\\Qt\\6.5.0\\msvc2022_64\\bin\\Qt6Core.dll" .
copy "C:\\Qt\\6.5.0\\msvc2022_64\\bin\\Qt6Gui.dll" .
copy "C:\\Qt\\6.5.0\\msvc2022_64\\bin\\Qt6Widgets.dll" .

# Copy platform plugins
mkdir platforms
copy "C:\\Qt\\6.5.0\\msvc2022_64\\plugins\\platforms\\qwindows.dll" platforms\\
```

## Troubleshooting

### Common Issues

#### Qt6 Not Found
```powershell
# Set Qt6_DIR explicitly
$env:Qt6_DIR = "C:\\Qt\\6.5.0\\msvc2022_64\\lib\\cmake\\Qt6"
cmake .. -DQt6_DIR="C:\\Qt\\6.5.0\\msvc2022_64\\lib\\cmake\\Qt6"
```

#### CMake Not Found
```powershell
# Add CMake to PATH
$env:PATH += ";C:\\Program Files\\CMake\\bin"
```

#### Compiler Not Found
```powershell
# Open Developer Command Prompt for VS 2022
# Or ensure Visual Studio is properly installed
```

#### Missing DLLs at Runtime
```powershell
# Run windeployqt to copy required DLLs
windeployqt.exe SrikokGit.exe

# Or manually copy Qt DLLs to application directory
```

#### Build Errors
```powershell
# Clean build directory
cd build
cmake --build . --target clean

# Or delete build directory and start fresh
cd ..
rmdir /s build
mkdir build
cd build
cmake ..
```

### Performance Tips

#### Parallel Build
```powershell
# Use parallel compilation
cmake --build . --config Release --parallel 8
```

#### Use ccache (if available)
```powershell
# Install ccache
winget install ccache

# Configure CMake to use ccache
cmake .. -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
```

## Advanced Configuration

### Custom Qt Installation
```powershell
# For non-standard Qt installation
cmake .. -DCMAKE_PREFIX_PATH="D:\\CustomQt\\6.5.0\\msvc2022_64"
```

### Static Build
```powershell
# Configure for static linking (requires static Qt build)
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
```

### Cross-compilation
```powershell
# For ARM64 Windows (requires ARM64 Qt)
cmake .. -A ARM64 -DCMAKE_PREFIX_PATH="C:\\Qt\\6.5.0\\msvc2022_arm64"
```

## Testing

### Run Tests
```powershell
# If tests are available
cd build
ctest --output-on-failure
```

## Package Creation

### Create Windows Installer
```powershell
# Install NSIS or WiX Toolset
# Add CPack configuration to CMakeLists.txt
# Generate installer
cmake --build . --target package
```

## Visual Studio Integration

### Open in Visual Studio
```powershell
# Generate Visual Studio solution
cmake .. -G "Visual Studio 17 2022" -A x64

# Open the generated solution
start SrikokGit.sln
```

### Qt Visual Studio Tools
```powershell
# Install Qt Visual Studio Tools extension
# Available in Visual Studio Marketplace
```

## Continuous Integration

### GitHub Actions Example
```yaml
name: Windows Build
on: [push, pull_request]
jobs:
  build:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v3
      - name: Setup Qt
        uses: jurplel/install-qt-action@v3
        with:
          version: '6.5.0'
          arch: 'win64_msvc2022_64'
      - name: Configure CMake
        run: cmake -B build -DCMAKE_BUILD_TYPE=Release
      - name: Build
        run: cmake --build build --config Release
```

## Support

For Windows-specific build issues:
1. Check system requirements
2. Verify all prerequisites are installed
3. Check environment variables
4. Try clean build
5. Consult Qt documentation for Windows
6. Submit issue with build logs

## License
This build documentation is part of the Srikok Git project.
Copyright © 2025 Srikoksoft