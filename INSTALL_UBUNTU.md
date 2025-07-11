# Building SRK Git on Ubuntu

## Install Dependencies

```bash
# Update package list
sudo apt update

# Install Qt 6 development packages
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential git

# Alternative: Install Qt 6 with additional components
sudo apt install qt6-base-dev qt6-tools-dev qt6-tools-dev-tools cmake build-essential git libqt6widgets6 libqt6core6

# Verify installations
qmake6 --version
cmake --version
git --version
```

## Build the Application

```bash
# Navigate to the project directory
cd /home/sacaf/Desktop/dev/srk-git

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the application
make -j$(nproc)

# Alternative: Use ninja for faster builds (optional)
# sudo apt install ninja-build
# cmake .. -G Ninja
# ninja
```

## Run the Application

```bash
# From the build directory
./SRKGit

# Or from the project root
./build/SRKGit
```

## Troubleshooting

### Qt 6 Not Found
If CMake can't find Qt 6:

```bash
# Check Qt 6 installation
dpkg -l | grep qt6

# If not found, install Qt 6:
sudo apt install qt6-base-dev qt6-tools-dev

# For older Ubuntu versions, you might need to add Qt PPA:
sudo add-apt-repository ppa:beineri/opt-qt-6.5.0-focal
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev
```

### CMake Version Issues
If CMake version is too old:

```bash
# Check CMake version
cmake --version

# If < 3.16, install newer version:
sudo apt remove cmake
sudo apt install cmake

# Or install from snap:
sudo snap install cmake --classic
```

### Build Errors
If you encounter build errors:

```bash
# Clean build directory
rm -rf build
mkdir build
cd build

# Try with verbose output
cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON
make VERBOSE=1
```

### Missing Git
If Git is not installed:

```bash
sudo apt install git
```

## Desktop Integration (Optional)

Create a desktop entry:

```bash
# Create desktop file
cat > ~/.local/share/applications/srk-git.desktop << EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=SRK Git
Comment=Git Repository Manager
Exec=/home/sacaf/Desktop/dev/srk-git/build/SRKGit
Icon=git
Terminal=false
Categories=Development;RevisionControl;
EOF

# Update desktop database
update-desktop-database ~/.local/share/applications/
```

## System Requirements

- Ubuntu 20.04 LTS or newer
- Qt 6.0 or higher
- CMake 3.16 or higher
- GCC 9 or higher (for C++17 support)
- Git 2.0 or higher
- At least 1GB RAM
- 100MB disk space for build files