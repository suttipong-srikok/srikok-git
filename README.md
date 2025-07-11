# SRK Git

A Git repository manager built with Qt and C++.

## Features

- **Repository Management**: Open existing Git repositories and clone remote repositories
- **File Browser**: Navigate and view repository files with status indicators
- **Commit History**: View commit history with detailed information
- **Staging Area**: Stage/unstage files and create commits with messages
- **Branch Management**: Create, switch, merge, and delete branches
- **Remote Operations**: Clone, push, pull, and fetch from remote repositories
- **Diff Viewer**: View file differences and changes
- **Settings**: Configure user information and Git settings

## Requirements

- Qt 6.0 or higher
- CMake 3.16 or higher
- Git installed on the system
- C++17 compatible compiler

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
./build/SRKGit
```

## Usage

1. **Open Repository**: Use File → Open Repository to open an existing Git repository
2. **Clone Repository**: Use File → Clone Repository to clone a remote repository
3. **Browse Files**: Use the repository browser to view files and their status
4. **Stage Changes**: Click on files in the repository browser to stage/unstage them
5. **Commit**: Use the staging area to write commit messages and commit changes
6. **View History**: Browse commit history in the commit history panel
7. **Branch Management**: Use the Repository menu to manage branches
8. **View Differences**: Select files to view their differences in the diff viewer

## Architecture

The application is structured with the following main components:

- **MainWindow**: The main application window and UI coordinator
- **GitManager**: Core Git operations interface
- **RepositoryBrowser**: File tree view with Git status
- **CommitHistory**: Commit log viewer
- **StagingArea**: File staging and commit interface
- **BranchManager**: Branch operations dialog
- **RemoteManager**: Remote repository operations
- **DiffViewer**: File difference viewer
- **Settings**: Application configuration

## Company

**SRK IT Service**
- Application Name: SRK Git
- Version: 1.0.0
- Copyright © 2024 SRK IT Service

## License

This project is proprietary software of SRK IT Service.