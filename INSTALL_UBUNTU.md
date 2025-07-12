# Building Srikok Git on Ubuntu

Complete installation and build guide for Srikok Git - a comprehensive Qt 6-based Git repository management application.

## System Requirements

### Minimum Requirements
- **Ubuntu Version**: 20.04 LTS or newer
- **Qt Framework**: Qt 6.0 or higher (with Qt6::Core and Qt6::Widgets modules)
- **Build System**: CMake 3.16 or higher
- **Compiler**: GCC 9+ or Clang 10+ (C++17 support required)
- **Version Control**: Git 2.0 or higher
- **Memory**: 1GB RAM minimum, 2GB recommended
- **Storage**: 100MB for build files, 500MB for full development setup

### Supported Ubuntu Versions
- Ubuntu 22.04 LTS (Jammy Jellyfish) - Recommended
- Ubuntu 20.04 LTS (Focal Fossa)
- Ubuntu 24.04 LTS (Noble Numbat)

## Install Dependencies

### Standard Installation (Recommended)

```bash
# Update package repository
sudo apt update && sudo apt upgrade -y

# Install Qt 6 development packages and build tools
sudo apt install -y \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    cmake \
    build-essential \
    git \
    pkg-config

# Install Qt 6 runtime libraries (if not already installed)
sudo apt install -y \
    libqt6widgets6 \
    libqt6core6 \
    libqt6gui6

# Verify installations
echo "Checking installed versions:"
qmake6 --version
cmake --version
gcc --version
git --version
```

### Comprehensive Installation (Development Setup)

```bash
# Install additional development tools and Qt modules
sudo apt install -y \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    qt6-documentation-tools \
    cmake \
    ninja-build \
    build-essential \
    git \
    pkg-config \
    gdb \
    valgrind \
    clang-format

# Install additional Qt 6 components (optional but recommended)
sudo apt install -y \
    libqt6widgets6 \
    libqt6core6 \
    libqt6gui6 \
    qt6-base-dev-tools
```

## Build the Application

### Quick Build Process

```bash
# Navigate to the project directory
cd srikok-git

# Create and configure build directory
mkdir -p build && cd build

# Configure build with CMake (Release build)
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build application using all available CPU cores
make -j$(nproc)

# Verify build success
ls -la SrikokGit
```

### Advanced Build Options

#### Debug Build (for development)
```bash
# Configure for debug build with additional information
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=ON

# Build with debug symbols
make -j$(nproc)
```

#### Ninja Build (Faster compilation)
```bash
# Install ninja build system
sudo apt install ninja-build

# Configure with Ninja generator
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release

# Build with Ninja (typically faster than make)
ninja

# Alternative: Ninja with verbose output
ninja -v
```

#### Custom Qt Installation Path
```bash
# If Qt 6 is installed in a custom location
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt6

# Example for Qt installed via Qt installer
cmake .. -DCMAKE_PREFIX_PATH=/opt/Qt/6.5.0/gcc_64
```

## Run the Application

### Standard Execution
```bash
# From the build directory
./SrikokGit

# Or with absolute path from project root
./build/SrikokGit

# Run with specific repository (optional)
./SrikokGit /path/to/git/repository
```

### Debug Execution
```bash
# Run with debugging information
gdb ./SrikokGit

# Run with memory checking (if valgrind installed)
valgrind --leak-check=full ./SrikokGit
```

## Troubleshooting

### Qt 6 Installation Issues

#### Qt 6 Not Found by CMake
```bash
# Check Qt 6 installation status
dpkg -l | grep qt6-base-dev

# If packages are missing, install them
sudo apt install qt6-base-dev qt6-tools-dev

# Check Qt 6 installation path
find /usr -name "Qt6Config.cmake" 2>/dev/null

# Set Qt 6 path explicitly if needed
export Qt6_DIR=/usr/lib/x86_64-linux-gnu/cmake/Qt6
cmake .. -DQt6_DIR=$Qt6_DIR
```

#### For Older Ubuntu Versions (20.04)
```bash
# Add Qt PPA for newer Qt versions if needed
sudo add-apt-repository ppa:beineri/opt-qt-6.5.0-focal
sudo apt update
sudo apt install qt65-base qt65-tools

# Configure build with PPA Qt
cmake .. -DCMAKE_PREFIX_PATH=/opt/qt65
```

### CMake Configuration Issues

#### CMake Version Too Old
```bash
# Check current CMake version
cmake --version

# Remove old CMake and install newer version
sudo apt remove cmake
sudo apt install cmake

# Alternative: Install latest CMake from snap
sudo snap install cmake --classic

# Verify CMake can find Qt 6
cmake .. --debug-output
```

#### Missing CMake Modules
```bash
# Install additional CMake modules
sudo apt install cmake-data

# Clear CMake cache and reconfigure
rm -rf CMakeCache.txt CMakeFiles/
cmake ..
```

### Compilation Errors

#### C++17 Compiler Support
```bash
# Verify GCC version supports C++17
gcc --version

# If GCC is too old, install newer version
sudo apt install gcc-11 g++-11

# Configure CMake to use specific compiler
cmake .. -DCMAKE_CXX_COMPILER=g++-11 -DCMAKE_C_COMPILER=gcc-11
```

#### Build Failures and Clean Rebuild
```bash
# Complete clean rebuild
rm -rf build
mkdir build && cd build

# Configure with verbose output for debugging
cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON

# Build with verbose output
make VERBOSE=1

# Alternative: Build single-threaded for better error visibility
make -j1
```

#### Memory Issues During Build
```bash
# Check available memory
free -h

# Build with limited parallelism if low memory
make -j2  # Use only 2 cores instead of all

# Or build single-threaded
make -j1
```

### Runtime Issues

#### Missing Qt 6 Libraries
```bash
# Check library dependencies
ldd ./SrikokGit

# Install missing Qt 6 runtime libraries
sudo apt install libqt6widgets6 libqt6core6 libqt6gui6

# Check Qt 6 plugin paths
export QT_DEBUG_PLUGINS=1
./SrikokGit
```

#### Git Command Not Found
```bash
# Install Git if missing
sudo apt install git

# Verify Git installation and add to PATH if needed
which git
echo $PATH
```

## Desktop Integration

### Create Desktop Entry
```bash
# Create application desktop file
mkdir -p ~/.local/share/applications

cat > ~/.local/share/applications/srikok-git.desktop << 'EOF'
[Desktop Entry]
Version=1.0
Type=Application
Name=Srikok Git
GenericName=Git Repository Manager
Comment=Comprehensive Git repository management with Qt 6
Exec=/home/$USER/Desktop/dev/srikok-git/build/SrikokGit
Icon=git
Terminal=false
StartupNotify=true
Categories=Development;RevisionControl;Qt;
MimeType=x-scheme-handler/git;
Keywords=git;version;control;repository;commit;branch;
EOF

# Update desktop database
update-desktop-database ~/.local/share/applications/

# Make desktop file executable
chmod +x ~/.local/share/applications/srikok-git.desktop
```

### System-wide Installation (Optional)
```bash
# Install system-wide (requires sudo)
sudo cp ./build/SrikokGit /usr/local/bin/
sudo cp ~/.local/share/applications/srikok-git.desktop /usr/share/applications/

# Update system desktop database
sudo update-desktop-database /usr/share/applications/
```

## Development Setup

### IDE Integration
```bash
# For Qt Creator development
sudo apt install qtcreator

# Open project in Qt Creator
qtcreator CMakeLists.txt

# For VS Code with C++ extension
sudo apt install code
code .
```

### Additional Development Tools
```bash
# Install debugging and profiling tools
sudo apt install \
    gdb \
    valgrind \
    cppcheck \
    clang-format \
    clang-tidy

# Install documentation tools
sudo apt install \
    doxygen \
    graphviz
```

## Performance Optimization

### Build Optimization
```bash
# Optimized release build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O3 -march=native"

# Link-time optimization (if supported)
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON
```

### Runtime Performance
```bash
# Set Qt scaling for high-DPI displays
export QT_AUTO_SCREEN_SCALE_FACTOR=1

# Optimize Qt rendering (if needed)
export QT_QUICK_CONTROLS_STYLE=Material
```

## Uninstall

### Remove Built Application
```bash
# Remove build directory
rm -rf build

# Remove desktop integration
rm ~/.local/share/applications/srikok-git.desktop
update-desktop-database ~/.local/share/applications/
```

### Remove Development Dependencies (Optional)
```bash
# Remove Qt 6 development packages (keep runtime if other apps need them)
sudo apt remove qt6-base-dev qt6-tools-dev qt6-tools-dev-tools

# Remove build tools (be careful with build-essential)
sudo apt remove cmake ninja-build

# Clean package cache
sudo apt autoremove
sudo apt autoclean
```

## Support and Documentation

For additional support:
- Check the main README.md for application usage
- Verify all dependencies are correctly installed
- Ensure your Ubuntu version is supported
- Contact Srikoksoft support for application-specific issues

**Srikoksoft Development Team**
- Website: srikoksoft.com
- Application: Srikok Git v1.0.0
- License: Proprietary Software