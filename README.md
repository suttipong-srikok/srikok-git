# Srikok Git

A comprehensive Git repository management application built with Qt 6 and C++17, providing a modern graphical interface for Git operations and repository management.

## Overview

Srikok Git is a feature-rich Git GUI client that streamlines version control workflows with an intuitive multi-panel interface. Built using Qt 6's robust widget system, it offers seamless Git integration with real-time status updates and comprehensive repository management capabilities.

## Key Features

### Core Git Operations
- **Repository Management**: Open existing repositories, clone from remote URLs with validation
- **File Management**: File browser with Git status indicators and context menu operations
- **Commit Operations**: Create commits with detailed messages, view comprehensive commit history
- **Staging Area**: Interactive file staging/unstaging with visual feedback

### Advanced Functionality
- **Branch Management**: Create, switch, merge, and delete branches with full branch visualization
- **Remote Operations**: Clone, fetch, pull, and push operations with remote repository management
- **Diff Viewer**: Comprehensive file difference visualization and change tracking
- **Settings Management**: User configuration for Git credentials and application preferences

### User Interface
- **Multi-Panel Layout**: Resizable splitter-based interface with repository browser, staging area, commit history, and diff viewer
- **Context-Sensitive Menus**: Right-click operations on files and branches
- **Status Indicators**: Real-time visual feedback for Git file states
- **Keyboard Shortcuts**: Standard shortcuts for efficient workflow (Ctrl+O, Ctrl+Shift+O, F5)

## System Requirements

### Minimum Requirements
- **Operating System**: Ubuntu 20.04 LTS or newer (Linux), Windows 10+, macOS 10.15+
- **Qt Framework**: Qt 6.0 or higher
- **Build System**: CMake 3.16 or higher
- **Compiler**: GCC 9+ or equivalent C++17-compatible compiler
- **Version Control**: Git 2.0 or higher
- **Memory**: 1GB RAM minimum
- **Storage**: 100MB for build files

### Development Dependencies
- Qt6::Core and Qt6::Widgets modules
- qt6-base-dev and qt6-tools-dev packages
- CMake and build-essential tools

## Quick Start

### Building from Source

```bash
# Clone or navigate to project directory
cd srikok-git

# Create and enter build directory
mkdir build && cd build

# Configure build with CMake
cmake ..

# Build application (use all available cores)
make -j$(nproc)

# Run the application
./SrikokGit
```

### Alternative Build with Ninja (Faster)

```bash
# Install ninja build system
sudo apt install ninja-build

# Configure with Ninja generator
cmake .. -G Ninja

# Build with Ninja
ninja
```

## Application Usage

### Getting Started
1. **Open Repository**: File → Open Repository or Ctrl+O to browse existing Git repositories
2. **Clone Repository**: File → Clone Repository or Ctrl+Shift+O to clone from remote URL
3. **Repository Browser**: Navigate files with real-time Git status indicators

### File Operations
4. **Stage Changes**: Right-click files to stage/unstage, or use staging area controls
5. **Create Commits**: Write commit messages in staging area and commit changes
6. **View History**: Browse detailed commit history with author, date, and message information

### Branch Management
7. **Branch Operations**: Repository menu provides branch creation, switching, merging, and deletion
8. **Remote Sync**: Use Repository menu for fetch, pull, and push operations

### Advanced Features
9. **Diff Viewing**: Select files to view detailed differences and changes
10. **Settings**: Configure user information, Git paths, and application preferences

## Architecture Overview

### Core Components

**Application Layer:**
- **MainWindow** (`mainwindow.h/cpp`): Central UI coordinator with 1200x800 pixel interface, menu system, toolbar, and status bar
- **Settings** (`settings.h/cpp`): Tabbed configuration interface for user preferences and Git settings

**Git Integration Layer:**
- **GitManager** (`gitmanager.h/cpp`): Core Git operations using QProcess with error handling and signal-based communication
- **Data Structures**: GitFileStatus and GitCommit objects for structured Git data management

**User Interface Components:**
- **RepositoryBrowser** (`repositorybrowser.h/cpp`): QTreeView-based file browser with Git status integration
- **CommitHistory** (`commithistory.h/cpp`): QListView commit display with detailed commit information
- **StagingArea** (`stagingarea.h/cpp`): Interactive staging interface with commit message composition
- **BranchManager** (`branchmanager.h/cpp`): Dialog-based branch management with QListWidget display
- **RemoteManager** (`remotemanager.h/cpp`): Remote repository operations interface
- **DiffViewer** (`diffviewer.h/cpp`): QTextEdit-based file difference visualization

### Technology Stack
- **Framework**: Qt 6 with Widgets module for cross-platform GUI
- **Language**: C++17 for modern language features and performance
- **Build System**: CMake for cross-platform build management
- **Git Integration**: QProcess-based Git command execution with output parsing
- **Data Models**: QStandardItemModel for efficient data display
- **Layout Management**: QSplitter for responsive multi-panel interface

## Development Information

### Company Details
**Srikoksoft**
- **Application**: Srikok Git
- **Version**: 1.0.0
- **Website**: srikoksoft.com
- **Copyright**: © 2025 Srikoksoft
- **License**: Proprietary Software

### Contributing
This is proprietary software developed by Srikoksoft. For support or inquiries, please contact through official channels.

## Support

For technical support, installation issues, or feature requests, please refer to the official Srikoksoft support channels or documentation.