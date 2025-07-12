# Building Srikok Git from Scratch - Complete Development Guide

## Table of Contents
1. [Project Overview](#project-overview)
2. [Development Environment Setup](#development-environment-setup)
3. [Technology Stack](#technology-stack)
4. [Project Structure](#project-structure)
5. [Step-by-Step Implementation](#step-by-step-implementation)
6. [Building and Testing](#building-and-testing)
7. [Deployment](#deployment)
8. [Advanced Features](#advanced-features)
9. [Troubleshooting](#troubleshooting)

## Project Overview

**Srikok Git** is a comprehensive Git repository management application built with Qt 6 and C++17. This guide provides complete instructions for building the application from scratch, including all tools, frameworks, and technologies required.

### Application Specifications
- **Name**: Srikok Git
- **Version**: 1.0.0
- **Developer**: Srikoksoft
- **License**: Proprietary Software
- **Target Platforms**: Linux (Ubuntu 20.04+), Windows 10+, macOS 10.15+

### Core Features to Implement
- Git repository management (open, clone, create)
- File browser with Git status indicators
- Staging area for commit preparation
- Commit history viewer with detailed information
- Branch management (create, switch, merge, delete)
- Remote operations (fetch, pull, push)
- Diff viewer for file changes
- Settings and configuration management

## Development Environment Setup

### 1. Operating System Requirements

#### Ubuntu Linux (Recommended)
```bash
# Check Ubuntu version
lsb_release -a

# Minimum: Ubuntu 20.04 LTS
# Recommended: Ubuntu 22.04 LTS or newer
```

#### Alternative Platforms
- **Windows**: Windows 10 or 11 with WSL2 or native development
- **macOS**: macOS 10.15 Catalina or newer with Xcode

### 2. Install Development Tools

#### Essential Development Packages
```bash
# Update system packages
sudo apt update && sudo apt upgrade -y

# Install essential build tools
sudo apt install -y \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    git \
    curl \
    wget \
    unzip

# Install GCC/G++ with C++17 support
sudo apt install -y \
    gcc-11 \
    g++-11

# Set GCC 11 as default (if multiple versions installed)
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 60
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 60

# Verify installation
gcc --version
g++ --version
cmake --version
```

#### Git Configuration
```bash
# Install Git (if not already installed)
sudo apt install git

# Configure Git globally
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
git config --global init.defaultBranch main

# Verify Git configuration
git config --list
```

### 3. Qt 6 Framework Installation

#### Option A: Package Manager Installation (Recommended)
```bash
# Install Qt 6 development packages
sudo apt install -y \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    qt6-documentation-tools \
    libqt6widgets6 \
    libqt6core6 \
    libqt6gui6

# Install additional Qt 6 modules
sudo apt install -y \
    qt6-base-dev-tools \
    qt6-qmake \
    qmake6

# Verify Qt 6 installation
qmake6 --version
pkg-config --modversion Qt6Core
```

#### Option B: Qt Online Installer (Alternative)
```bash
# Download Qt online installer
wget https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run

# Make installer executable
chmod +x qt-unified-linux-x64-online.run

# Run installer (GUI)
./qt-unified-linux-x64-online.run

# Select Qt 6.5.0 or newer with the following components:
# - Qt 6.x.x Desktop gcc 64-bit
# - Qt Creator (optional but recommended)
# - CMake integration
```

### 4. Development IDE Setup

#### Qt Creator (Recommended)
```bash
# Install Qt Creator
sudo apt install qtcreator

# Alternative: Download latest Qt Creator
# Visit: https://www.qt.io/download-qt-installer
```

#### Visual Studio Code (Alternative)
```bash
# Install VS Code
sudo apt install code

# Install essential extensions:
# - C/C++ Extension Pack
# - CMake Tools
# - Qt for Python (optional)
# - GitLens
```

### 5. Additional Development Tools

#### Debugging and Profiling Tools
```bash
# Install debugging tools
sudo apt install -y \
    gdb \
    valgrind \
    cppcheck \
    clang-format \
    clang-tidy

# Install documentation tools
sudo apt install -y \
    doxygen \
    graphviz \
    plantuml
```

## Technology Stack

### Core Technologies
- **Programming Language**: C++17
- **GUI Framework**: Qt 6.x (Qt6::Core, Qt6::Widgets)
- **Build System**: CMake 3.16+
- **Version Control**: Git 2.0+
- **Compiler**: GCC 9+ or Clang 10+

### Qt 6 Modules Used
- **Qt6::Core**: Core functionality, signals/slots, event system
- **Qt6::Widgets**: GUI widgets (QMainWindow, QTreeView, QListView, etc.)
- **Qt6::Gui**: Graphics and windowing system

### Development Tools
- **Build Generator**: CMake with Ninja or Make
- **Package Manager**: apt (Ubuntu), vcpkg (optional)
- **Debugger**: GDB or LLDB
- **Code Analysis**: Cppcheck, Clang-Tidy
- **Documentation**: Doxygen

## Project Structure

### 1. Create Project Directory Structure

```bash
# Create main project directory
mkdir -p srikok-git && cd srikok-git

# Create source directory structure
mkdir -p src/{core,ui,dialogs,models,utils}
mkdir -p include/{core,ui,dialogs,models,utils}
mkdir -p resources/{icons,styles,translations}
mkdir -p docs
mkdir -p tests
mkdir -p scripts
mkdir -p build

# Create initial files
touch CMakeLists.txt
touch README.md
touch LICENSE
touch .gitignore
```

### 2. Project Directory Layout

```
srikok-git/
├── CMakeLists.txt                 # Main CMake configuration
├── README.md                      # Project documentation
├── LICENSE                        # License file
├── .gitignore                     # Git ignore rules
├── BUILD_FROM_SCRATCH.md         # This guide
├── INSTALL_UBUNTU.md             # Installation instructions
├── src/                          # Source code
│   ├── main.cpp                  # Application entry point
│   ├── mainwindow.cpp           # Main window implementation
│   ├── core/                    # Core application logic
│   │   ├── gitmanager.cpp       # Git operations
│   │   └── settings.cpp         # Application settings
│   ├── ui/                      # User interface components
│   │   ├── repositorybrowser.cpp # File browser
│   │   ├── commithistory.cpp    # Commit history viewer
│   │   ├── stagingarea.cpp      # Staging interface
│   │   └── diffviewer.cpp       # Diff viewer
│   └── dialogs/                 # Dialog windows
│       ├── branchmanager.cpp    # Branch management
│       └── remotemanager.cpp    # Remote operations
├── include/                     # Header files
│   ├── mainwindow.h
│   ├── core/
│   ├── ui/
│   └── dialogs/
├── resources/                   # Application resources
│   ├── icons/                   # Application icons
│   ├── styles/                  # Stylesheets
│   └── translations/            # Internationalization
├── docs/                        # Documentation
├── tests/                       # Unit tests
├── scripts/                     # Build/deployment scripts
└── build/                       # Build output directory
```

## Step-by-Step Implementation

### Step 1: Project Initialization

#### 1.1 Create CMakeLists.txt
```cmake
# File: CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(SrikokGit 
    VERSION 1.0.0
    DESCRIPTION "Git Repository Manager"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable Qt MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add executable
add_executable(SrikokGit
    src/main.cpp
    src/mainwindow.cpp
    src/core/gitmanager.cpp
    src/core/settings.cpp
    src/ui/repositorybrowser.cpp
    src/ui/commithistory.cpp
    src/ui/stagingarea.cpp
    src/ui/diffviewer.cpp
    src/dialogs/branchmanager.cpp
    src/dialogs/remotemanager.cpp
)

# Include directories
target_include_directories(SrikokGit PRIVATE
    include
    include/core
    include/ui
    include/dialogs
)

# Link Qt libraries
target_link_libraries(SrikokGit Qt6::Core Qt6::Widgets)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(SrikokGit PRIVATE -Wall -Wextra -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(SrikokGit PRIVATE -Wall -Wextra -pedantic)
endif()

# Platform-specific settings
if(WIN32)
    set_target_properties(SrikokGit PROPERTIES WIN32_EXECUTABLE TRUE)
elseif(APPLE)
    set_target_properties(SrikokGit PROPERTIES MACOSX_BUNDLE TRUE)
endif()
```

#### 1.2 Create .gitignore
```gitignore
# File: .gitignore

# Build directories
build/
*build*/
*.build/

# CMake
CMakeCache.txt
CMakeFiles/
CMakeScripts/
Makefile
cmake_install.cmake
install_manifest.txt
CTestTestfile.cmake
*.cmake

# Qt
*.pro.user
*.pro.user.*
*.qws
*.qm
.qmake.cache
.qmake.stash
*.moc
moc_*.cpp
moc_*.h
qrc_*.cpp
ui_*.h
Makefile*
*-build-*

# Compiled Object files
*.slo
*.lo
*.o
*.obj

# Executables
*.exe
*.out
*.app
SrikokGit

# Libraries
*.lib
*.a
*.la
*.so
*.dll
*.dylib

# Qt Creator
CMakeLists.txt.user
CMakeLists.txt.user.*

# IDE
.vscode/
.vs/
*.vcxproj
*.vcxproj.filters
*.sln

# System
.DS_Store
Thumbs.db
*.swp
*.swo
*~

# Logs
*.log

# Package files
*.deb
*.rpm
*.pkg
```

### Step 2: Core Application Structure

#### 2.1 Create Main Application Entry Point

```cpp
// File: src/main.cpp
#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QStyleFactory>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Srikok Git");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Srikoksoft");
    app.setOrganizationDomain("srikoksoft.com");
    
    // Set application icon
    app.setWindowIcon(QIcon(":/icons/srikok-git.png"));
    
    // Create main window
    MainWindow window;
    window.show();
    
    return app.exec();
}
```

#### 2.2 Create Main Window Header

```cpp
// File: include/mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

// Forward declarations
class GitManager;
class RepositoryBrowser;
class CommitHistory;
class StagingArea;
class DiffViewer;
class BranchManager;
class RemoteManager;
class Settings;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openRepository();
    void cloneRepository();
    void refreshRepository();
    void showSettings();
    void showBranchManager();
    void showRemoteManager();
    void showAbout();
    void onRepositoryChanged();
    void updateStatusBar();

private:
    void setupUi();
    void setupMenus();
    void setupToolbars();
    void setupStatusBar();
    void setupConnections();
    void loadSettings();
    void saveSettings();

    // Core components
    GitManager *m_gitManager;
    
    // UI components
    QSplitter *m_mainSplitter;
    QSplitter *m_leftSplitter;
    QSplitter *m_rightSplitter;
    
    RepositoryBrowser *m_repositoryBrowser;
    CommitHistory *m_commitHistory;
    StagingArea *m_stagingArea;
    DiffViewer *m_diffViewer;
    
    // Dialogs
    BranchManager *m_branchManager;
    RemoteManager *m_remoteManager;
    Settings *m_settings;
    
    // Menu actions
    QAction *m_openRepoAction;
    QAction *m_cloneRepoAction;
    QAction *m_refreshAction;
    QAction *m_exitAction;
    QAction *m_settingsAction;
    QAction *m_branchAction;
    QAction *m_remoteAction;
    QAction *m_aboutAction;
    
    // Status bar
    QLabel *m_repoPathLabel;
    QLabel *m_currentBranchLabel;
    QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H
```

#### 2.3 Create Main Window Implementation

```cpp
// File: src/mainwindow.cpp
#include "mainwindow.h"
#include "gitmanager.h"
#include "repositorybrowser.h"
#include "commithistory.h"
#include "stagingarea.h"
#include "diffviewer.h"
#include "branchmanager.h"
#include "remotemanager.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_gitManager(nullptr)
    , m_mainSplitter(nullptr)
    , m_leftSplitter(nullptr)
    , m_rightSplitter(nullptr)
    , m_repositoryBrowser(nullptr)
    , m_commitHistory(nullptr)
    , m_stagingArea(nullptr)
    , m_diffViewer(nullptr)
    , m_branchManager(nullptr)
    , m_remoteManager(nullptr)
    , m_settings(nullptr)
{
    setWindowTitle("Srikok Git - Git Repository Manager");
    setMinimumSize(1200, 800);
    resize(1400, 900);
    
    // Initialize components
    m_gitManager = new GitManager(this);
    
    setupUi();
    setupMenus();
    setupToolbars();
    setupStatusBar();
    setupConnections();
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
}

void MainWindow::setupUi()
{
    // Create main splitter (horizontal)
    m_mainSplitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(m_mainSplitter);
    
    // Create left splitter (vertical)
    m_leftSplitter = new QSplitter(Qt::Vertical, this);
    m_mainSplitter->addWidget(m_leftSplitter);
    
    // Create right splitter (vertical)
    m_rightSplitter = new QSplitter(Qt::Vertical, this);
    m_mainSplitter->addWidget(m_rightSplitter);
    
    // Create UI components
    m_repositoryBrowser = new RepositoryBrowser(m_gitManager, this);
    m_commitHistory = new CommitHistory(m_gitManager, this);
    m_stagingArea = new StagingArea(m_gitManager, this);
    m_diffViewer = new DiffViewer(m_gitManager, this);
    
    // Add components to splitters
    m_leftSplitter->addWidget(m_repositoryBrowser);
    m_leftSplitter->addWidget(m_stagingArea);
    
    m_rightSplitter->addWidget(m_commitHistory);
    m_rightSplitter->addWidget(m_diffViewer);
    
    // Set splitter proportions
    m_mainSplitter->setSizes({400, 800});
    m_leftSplitter->setSizes({300, 300});
    m_rightSplitter->setSizes({400, 400});
}

void MainWindow::setupMenus()
{
    // File menu
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    m_openRepoAction = new QAction("&Open Repository...", this);
    m_openRepoAction->setShortcut(QKeySequence::Open);
    m_openRepoAction->setStatusTip("Open an existing Git repository");
    fileMenu->addAction(m_openRepoAction);
    
    m_cloneRepoAction = new QAction("&Clone Repository...", this);
    m_cloneRepoAction->setShortcut(QKeySequence("Ctrl+Shift+O"));
    m_cloneRepoAction->setStatusTip("Clone a repository from remote URL");
    fileMenu->addAction(m_cloneRepoAction);
    
    fileMenu->addSeparator();
    
    m_refreshAction = new QAction("&Refresh", this);
    m_refreshAction->setShortcut(QKeySequence::Refresh);
    m_refreshAction->setStatusTip("Refresh repository status");
    fileMenu->addAction(m_refreshAction);
    
    fileMenu->addSeparator();
    
    m_exitAction = new QAction("E&xit", this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_exitAction->setStatusTip("Exit the application");
    fileMenu->addAction(m_exitAction);
    
    // Repository menu
    QMenu *repoMenu = menuBar()->addMenu("&Repository");
    
    m_branchAction = new QAction("&Branch Manager...", this);
    m_branchAction->setStatusTip("Manage repository branches");
    repoMenu->addAction(m_branchAction);
    
    m_remoteAction = new QAction("&Remote Manager...", this);
    m_remoteAction->setStatusTip("Manage remote repositories");
    repoMenu->addAction(m_remoteAction);
    
    // Tools menu
    QMenu *toolsMenu = menuBar()->addMenu("&Tools");
    
    m_settingsAction = new QAction("&Settings...", this);
    m_settingsAction->setStatusTip("Configure application settings");
    toolsMenu->addAction(m_settingsAction);
    
    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    
    m_aboutAction = new QAction("&About", this);
    m_aboutAction->setStatusTip("About Srikok Git");
    helpMenu->addAction(m_aboutAction);
}

void MainWindow::setupToolbars()
{
    QToolBar *mainToolBar = addToolBar("Main");
    mainToolBar->addAction(m_openRepoAction);
    mainToolBar->addAction(m_cloneRepoAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(m_refreshAction);
}

void MainWindow::setupStatusBar()
{
    m_repoPathLabel = new QLabel("No repository");
    m_currentBranchLabel = new QLabel("");
    m_statusLabel = new QLabel("Ready");
    
    statusBar()->addWidget(m_repoPathLabel);
    statusBar()->addPermanentWidget(m_currentBranchLabel);
    statusBar()->addPermanentWidget(m_statusLabel);
}

void MainWindow::setupConnections()
{
    // Menu actions
    connect(m_openRepoAction, &QAction::triggered, this, &MainWindow::openRepository);
    connect(m_cloneRepoAction, &QAction::triggered, this, &MainWindow::cloneRepository);
    connect(m_refreshAction, &QAction::triggered, this, &MainWindow::refreshRepository);
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    connect(m_settingsAction, &QAction::triggered, this, &MainWindow::showSettings);
    connect(m_branchAction, &QAction::triggered, this, &MainWindow::showBranchManager);
    connect(m_remoteAction, &QAction::triggered, this, &MainWindow::showRemoteManager);
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    
    // Git manager signals
    connect(m_gitManager, &GitManager::repositoryChanged, this, &MainWindow::onRepositoryChanged);
    connect(m_gitManager, &GitManager::statusChanged, this, &MainWindow::updateStatusBar);
}

void MainWindow::openRepository()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Open Repository");
    if (!dir.isEmpty()) {
        if (m_gitManager->openRepository(dir)) {
            m_repoPathLabel->setText(dir);
            refreshRepository();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open repository");
        }
    }
}

void MainWindow::cloneRepository()
{
    // Implementation for clone dialog
    // This would show a dialog to enter repository URL and destination
}

void MainWindow::refreshRepository()
{
    if (m_gitManager->hasRepository()) {
        m_gitManager->refreshStatus();
    }
}

void MainWindow::showSettings()
{
    if (!m_settings) {
        m_settings = new Settings(this);
    }
    m_settings->exec();
}

void MainWindow::showBranchManager()
{
    if (!m_branchManager) {
        m_branchManager = new BranchManager(m_gitManager, this);
    }
    m_branchManager->exec();
}

void MainWindow::showRemoteManager()
{
    if (!m_remoteManager) {
        m_remoteManager = new RemoteManager(m_gitManager, this);
    }
    m_remoteManager->exec();
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "About Srikok Git",
        "<h2>Srikok Git 1.0.0</h2>"
        "<p>A comprehensive Git repository management application.</p>"
        "<p>Built with Qt 6 and C++17</p>"
        "<p>Copyright © 2025 Srikoksoft</p>"
        "<p>Website: <a href='http://srikoksoft.com'>srikoksoft.com</a></p>");
}

void MainWindow::onRepositoryChanged()
{
    updateStatusBar();
    // Refresh all components
    if (m_repositoryBrowser) m_repositoryBrowser->refresh();
    if (m_commitHistory) m_commitHistory->refresh();
    if (m_stagingArea) m_stagingArea->refresh();
}

void MainWindow::updateStatusBar()
{
    if (m_gitManager->hasRepository()) {
        QString branch = m_gitManager->getCurrentBranch();
        m_currentBranchLabel->setText(QString("Branch: %1").arg(branch));
        m_statusLabel->setText("Ready");
    } else {
        m_currentBranchLabel->setText("");
        m_statusLabel->setText("No repository");
    }
}

void MainWindow::loadSettings()
{
    // Load window geometry and state
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    
    // Restore splitter states
    m_mainSplitter->restoreState(settings.value("mainSplitter").toByteArray());
    m_leftSplitter->restoreState(settings.value("leftSplitter").toByteArray());
    m_rightSplitter->restoreState(settings.value("rightSplitter").toByteArray());
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("mainSplitter", m_mainSplitter->saveState());
    settings.setValue("leftSplitter", m_leftSplitter->saveState());
    settings.setValue("rightSplitter", m_rightSplitter->saveState());
}

#include "mainwindow.moc"
```

### Step 3: Git Manager Core Implementation

#### 3.1 Create Git Manager Header

```cpp
// File: include/core/gitmanager.h
#ifndef GITMANAGER_H
#define GITMANAGER_H

#include <QObject>
#include <QProcess>
#include <QDir>
#include <QStringList>
#include <QDateTime>

struct GitFileStatus {
    QString filePath;
    QString status;          // M, A, D, R, C, U, ?
    bool isStaged;
    bool isModified;
    bool isUntracked;
    bool isDeleted;
    
    GitFileStatus() : isStaged(false), isModified(false), 
                     isUntracked(false), isDeleted(false) {}
};

struct GitCommit {
    QString hash;
    QString shortHash;
    QString author;
    QString email;
    QDateTime date;
    QString message;
    QString summary;
    QStringList parents;
    
    GitCommit() {}
};

struct GitBranch {
    QString name;
    QString fullName;
    bool isCurrent;
    bool isRemote;
    QString tracking;
    QString upstream;
    
    GitBranch() : isCurrent(false), isRemote(false) {}
};

struct GitRemote {
    QString name;
    QString fetchUrl;
    QString pushUrl;
    
    GitRemote() {}
};

class GitManager : public QObject
{
    Q_OBJECT

public:
    explicit GitManager(QObject *parent = nullptr);
    ~GitManager();

    // Repository operations
    bool openRepository(const QString &path);
    bool cloneRepository(const QString &url, const QString &destination);
    bool createRepository(const QString &path);
    void closeRepository();
    bool hasRepository() const;
    QString getRepositoryPath() const;

    // Status operations
    void refreshStatus();
    QList<GitFileStatus> getFileStatus() const;
    QList<GitFileStatus> getStagedFiles() const;
    QList<GitFileStatus> getUnstagedFiles() const;

    // File operations
    bool stageFile(const QString &filePath);
    bool unstageFile(const QString &filePath);
    bool stageAllFiles();
    bool unstageAllFiles();
    bool discardChanges(const QString &filePath);

    // Commit operations
    bool commit(const QString &message, const QString &description = QString());
    QList<GitCommit> getCommitHistory(int maxCount = 100) const;
    QString getCommitDiff(const QString &commitHash) const;

    // Branch operations
    QList<GitBranch> getBranches() const;
    QString getCurrentBranch() const;
    bool createBranch(const QString &branchName, const QString &startPoint = QString());
    bool switchBranch(const QString &branchName);
    bool deleteBranch(const QString &branchName, bool force = false);
    bool mergeBranch(const QString &branchName);

    // Remote operations
    QList<GitRemote> getRemotes() const;
    bool addRemote(const QString &name, const QString &url);
    bool removeRemote(const QString &name);
    bool fetch(const QString &remote = QString());
    bool pull(const QString &remote = QString(), const QString &branch = QString());
    bool push(const QString &remote = QString(), const QString &branch = QString());

    // Diff operations
    QString getFileDiff(const QString &filePath) const;
    QString getStagedDiff() const;
    QString getUnstagedDiff() const;

    // Utility functions
    bool isValidRepository(const QString &path) const;
    QString getGitVersion() const;

signals:
    void repositoryChanged();
    void statusChanged();
    void operationCompleted(const QString &operation, bool success, const QString &message);

private slots:
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessError(QProcess::ProcessError error);

private:
    bool executeGitCommand(const QStringList &arguments, QString *output = nullptr, int timeoutMs = 30000);
    QStringList parseGitStatus(const QString &statusOutput) const;
    GitCommit parseCommitInfo(const QString &commitLine) const;
    GitBranch parseBranchInfo(const QString &branchLine) const;
    GitRemote parseRemoteInfo(const QString &remoteLine) const;

    QString m_repositoryPath;
    QProcess *m_gitProcess;
    bool m_hasRepository;
    QList<GitFileStatus> m_fileStatus;
    QString m_currentBranch;
};

#endif // GITMANAGER_H
```

#### 3.2 Create Git Manager Implementation

```cpp
// File: src/core/gitmanager.cpp
#include "gitmanager.h"
#include <QDebug>
#include <QFileInfo>
#include <QStandardPaths>
#include <QCoreApplication>

GitManager::GitManager(QObject *parent)
    : QObject(parent)
    , m_gitProcess(nullptr)
    , m_hasRepository(false)
{
    m_gitProcess = new QProcess(this);
    connect(m_gitProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &GitManager::onProcessFinished);
    connect(m_gitProcess, &QProcess::errorOccurred,
            this, &GitManager::onProcessError);
}

GitManager::~GitManager()
{
    if (m_gitProcess && m_gitProcess->state() != QProcess::NotRunning) {
        m_gitProcess->kill();
        m_gitProcess->waitForFinished(3000);
    }
}

bool GitManager::openRepository(const QString &path)
{
    if (!isValidRepository(path)) {
        return false;
    }

    m_repositoryPath = path;
    m_hasRepository = true;
    
    // Get current branch
    QString output;
    if (executeGitCommand({"branch", "--show-current"}, &output)) {
        m_currentBranch = output.trimmed();
    }

    emit repositoryChanged();
    refreshStatus();
    return true;
}

bool GitManager::cloneRepository(const QString &url, const QString &destination)
{
    if (url.isEmpty() || destination.isEmpty()) {
        return false;
    }

    QStringList args = {"clone", url, destination};
    QString output;
    
    if (executeGitCommand(args, &output, 120000)) { // 2 minute timeout for clone
        return openRepository(destination);
    }
    
    return false;
}

bool GitManager::createRepository(const QString &path)
{
    QDir dir(path);
    if (!dir.exists() && !dir.mkpath(".")) {
        return false;
    }

    QString oldPath = m_repositoryPath;
    m_repositoryPath = path;
    
    QString output;
    if (executeGitCommand({"init"}, &output)) {
        m_hasRepository = true;
        m_currentBranch = "main"; // or "master" depending on Git config
        emit repositoryChanged();
        return true;
    }
    
    m_repositoryPath = oldPath;
    return false;
}

void GitManager::closeRepository()
{
    m_repositoryPath.clear();
    m_hasRepository = false;
    m_currentBranch.clear();
    m_fileStatus.clear();
    emit repositoryChanged();
}

bool GitManager::hasRepository() const
{
    return m_hasRepository && !m_repositoryPath.isEmpty();
}

QString GitManager::getRepositoryPath() const
{
    return m_repositoryPath;
}

void GitManager::refreshStatus()
{
    if (!hasRepository()) {
        return;
    }

    QString output;
    if (executeGitCommand({"status", "--porcelain=v1"}, &output)) {
        QStringList statusLines = parseGitStatus(output);
        
        m_fileStatus.clear();
        for (const QString &line : statusLines) {
            if (line.length() >= 3) {
                GitFileStatus fileStatus;
                fileStatus.status = line.left(2);
                fileStatus.filePath = line.mid(3);
                
                // Parse status flags
                QChar staged = line[0];
                QChar unstaged = line[1];
                
                fileStatus.isStaged = (staged != ' ' && staged != '?');
                fileStatus.isModified = (unstaged == 'M');
                fileStatus.isUntracked = (staged == '?' && unstaged == '?');
                fileStatus.isDeleted = (unstaged == 'D' || staged == 'D');
                
                m_fileStatus.append(fileStatus);
            }
        }
    }

    // Update current branch
    if (executeGitCommand({"branch", "--show-current"}, &output)) {
        m_currentBranch = output.trimmed();
    }

    emit statusChanged();
}

QList<GitFileStatus> GitManager::getFileStatus() const
{
    return m_fileStatus;
}

QList<GitFileStatus> GitManager::getStagedFiles() const
{
    QList<GitFileStatus> staged;
    for (const GitFileStatus &status : m_fileStatus) {
        if (status.isStaged) {
            staged.append(status);
        }
    }
    return staged;
}

QList<GitFileStatus> GitManager::getUnstagedFiles() const
{
    QList<GitFileStatus> unstaged;
    for (const GitFileStatus &status : m_fileStatus) {
        if (!status.isStaged || status.isModified) {
            unstaged.append(status);
        }
    }
    return unstaged;
}

bool GitManager::stageFile(const QString &filePath)
{
    if (!hasRepository() || filePath.isEmpty()) {
        return false;
    }

    QString output;
    bool success = executeGitCommand({"add", filePath}, &output);
    if (success) {
        refreshStatus();
    }
    return success;
}

bool GitManager::unstageFile(const QString &filePath)
{
    if (!hasRepository() || filePath.isEmpty()) {
        return false;
    }

    QString output;
    bool success = executeGitCommand({"reset", "HEAD", filePath}, &output);
    if (success) {
        refreshStatus();
    }
    return success;
}

bool GitManager::stageAllFiles()
{
    if (!hasRepository()) {
        return false;
    }

    QString output;
    bool success = executeGitCommand({"add", "."}, &output);
    if (success) {
        refreshStatus();
    }
    return success;
}

bool GitManager::unstageAllFiles()
{
    if (!hasRepository()) {
        return false;
    }

    QString output;
    bool success = executeGitCommand({"reset", "HEAD"}, &output);
    if (success) {
        refreshStatus();
    }
    return success;
}

bool GitManager::discardChanges(const QString &filePath)
{
    if (!hasRepository() || filePath.isEmpty()) {
        return false;
    }

    QString output;
    bool success = executeGitCommand({"checkout", "--", filePath}, &output);
    if (success) {
        refreshStatus();
    }
    return success;
}

bool GitManager::commit(const QString &message, const QString &description)
{
    if (!hasRepository() || message.isEmpty()) {
        return false;
    }

    QString fullMessage = message;
    if (!description.isEmpty()) {
        fullMessage += "\n\n" + description;
    }

    QString output;
    bool success = executeGitCommand({"commit", "-m", fullMessage}, &output);
    if (success) {
        refreshStatus();
        emit operationCompleted("commit", true, "Commit created successfully");
    } else {
        emit operationCompleted("commit", false, output);
    }
    return success;
}

QList<GitCommit> GitManager::getCommitHistory(int maxCount) const
{
    QList<GitCommit> commits;
    if (!hasRepository()) {
        return commits;
    }

    QString output;
    QStringList args = {"log", "--oneline", "--pretty=format:%H|%h|%an|%ae|%ad|%s|%P", 
                       "--date=iso", "-n", QString::number(maxCount)};
    
    if (executeGitCommand(args, &output)) {
        QStringList lines = output.split('\n', Qt::SkipEmptyParts);
        for (const QString &line : lines) {
            GitCommit commit = parseCommitInfo(line);
            if (!commit.hash.isEmpty()) {
                commits.append(commit);
            }
        }
    }

    return commits;
}

QString GitManager::getCurrentBranch() const
{
    return m_currentBranch;
}

QList<GitBranch> GitManager::getBranches() const
{
    QList<GitBranch> branches;
    if (!hasRepository()) {
        return branches;
    }

    QString output;
    if (executeGitCommand({"branch", "-a", "-v"}, &output)) {
        QStringList lines = output.split('\n', Qt::SkipEmptyParts);
        for (const QString &line : lines) {
            GitBranch branch = parseBranchInfo(line);
            if (!branch.name.isEmpty()) {
                branches.append(branch);
            }
        }
    }

    return branches;
}

bool GitManager::executeGitCommand(const QStringList &arguments, QString *output, int timeoutMs)
{
    if (!m_gitProcess) {
        return false;
    }

    if (m_gitProcess->state() != QProcess::NotRunning) {
        m_gitProcess->kill();
        m_gitProcess->waitForFinished(3000);
    }

    // Set working directory if we have a repository
    if (hasRepository()) {
        m_gitProcess->setWorkingDirectory(m_repositoryPath);
    }

    m_gitProcess->start("git", arguments);
    
    if (!m_gitProcess->waitForStarted(5000)) {
        qWarning() << "Failed to start git process";
        return false;
    }

    if (!m_gitProcess->waitForFinished(timeoutMs)) {
        qWarning() << "Git command timed out";
        m_gitProcess->kill();
        return false;
    }

    int exitCode = m_gitProcess->exitCode();
    if (output) {
        *output = QString::fromUtf8(m_gitProcess->readAllStandardOutput());
    }

    if (exitCode != 0) {
        QString error = QString::fromUtf8(m_gitProcess->readAllStandardError());
        qWarning() << "Git command failed:" << arguments.join(" ") << "Error:" << error;
    }

    return exitCode == 0;
}

QStringList GitManager::parseGitStatus(const QString &statusOutput) const
{
    return statusOutput.split('\n', Qt::SkipEmptyParts);
}

GitCommit GitManager::parseCommitInfo(const QString &commitLine) const
{
    GitCommit commit;
    QStringList parts = commitLine.split('|');
    
    if (parts.size() >= 6) {
        commit.hash = parts[0];
        commit.shortHash = parts[1];
        commit.author = parts[2];
        commit.email = parts[3];
        commit.date = QDateTime::fromString(parts[4], Qt::ISODate);
        commit.summary = parts[5];
        
        if (parts.size() > 6 && !parts[6].isEmpty()) {
            commit.parents = parts[6].split(' ', Qt::SkipEmptyParts);
        }
    }
    
    return commit;
}

GitBranch GitManager::parseBranchInfo(const QString &branchLine) const
{
    GitBranch branch;
    QString line = branchLine.trimmed();
    
    if (line.startsWith("* ")) {
        branch.isCurrent = true;
        line = line.mid(2).trimmed();
    } else if (line.startsWith("  ")) {
        line = line.mid(2).trimmed();
    }
    
    if (line.startsWith("remotes/")) {
        branch.isRemote = true;
        branch.fullName = line;
        int slashIndex = line.indexOf('/', 8); // Skip "remotes/"
        if (slashIndex > 0) {
            branch.name = line.mid(slashIndex + 1);
        }
    } else {
        int spaceIndex = line.indexOf(' ');
        if (spaceIndex > 0) {
            branch.name = line.left(spaceIndex);
        } else {
            branch.name = line;
        }
        branch.fullName = branch.name;
    }
    
    return branch;
}

bool GitManager::isValidRepository(const QString &path) const
{
    QDir dir(path);
    return dir.exists() && dir.exists(".git");
}

QString GitManager::getGitVersion() const
{
    QString output;
    QProcess process;
    process.start("git", {"--version"});
    if (process.waitForFinished(5000)) {
        output = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
    }
    return output;
}

void GitManager::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode)
    Q_UNUSED(exitStatus)
    // Handle process completion if needed
}

void GitManager::onProcessError(QProcess::ProcessError error)
{
    QString errorString;
    switch (error) {
    case QProcess::FailedToStart:
        errorString = "Failed to start Git process";
        break;
    case QProcess::Crashed:
        errorString = "Git process crashed";
        break;
    case QProcess::Timedout:
        errorString = "Git process timed out";
        break;
    default:
        errorString = "Unknown Git process error";
        break;
    }
    
    qWarning() << "Git process error:" << errorString;
    emit operationCompleted("git", false, errorString);
}

#include "gitmanager.moc"
```

### Step 4: User Interface Components

#### 4.1 Repository Browser Implementation

```cpp
// File: include/ui/repositorybrowser.h
#ifndef REPOSITORYBROWSER_H
#define REPOSITORYBROWSER_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>

class GitManager;

class RepositoryBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit RepositoryBrowser(GitManager *gitManager, QWidget *parent = nullptr);
    ~RepositoryBrowser();

    void refresh();

signals:
    void fileSelected(const QString &filePath);
    void fileDoubleClicked(const QString &filePath);

private slots:
    void onItemClicked(const QModelIndex &index);
    void onItemDoubleClicked(const QModelIndex &index);
    void onCustomContextMenuRequested(const QPoint &pos);
    void stageFile();
    void unstageFile();
    void discardChanges();
    void openFile();

private:
    void setupUi();
    void setupContextMenu();
    void populateFileList();
    QString getFilePathFromIndex(const QModelIndex &index) const;
    QIcon getStatusIcon(const QString &status) const;

    GitManager *m_gitManager;
    QTreeView *m_treeView;
    QStandardItemModel *m_model;
    QVBoxLayout *m_layout;
    
    // Context menu
    QMenu *m_contextMenu;
    QAction *m_stageAction;
    QAction *m_unstageAction;
    QAction *m_discardAction;
    QAction *m_openAction;
    
    QString m_selectedFilePath;
};

#endif // REPOSITORYBROWSER_H
```

#### 4.2 Repository Browser Implementation

```cpp
// File: src/ui/repositorybrowser.cpp
#include "repositorybrowser.h"
#include "gitmanager.h"
#include <QApplication>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

RepositoryBrowser::RepositoryBrowser(GitManager *gitManager, QWidget *parent)
    : QWidget(parent)
    , m_gitManager(gitManager)
    , m_treeView(nullptr)
    , m_model(nullptr)
    , m_layout(nullptr)
    , m_contextMenu(nullptr)
{
    setupUi();
    setupContextMenu();
    
    // Connect to git manager signals
    connect(m_gitManager, &GitManager::statusChanged, this, &RepositoryBrowser::refresh);
    connect(m_gitManager, &GitManager::repositoryChanged, this, &RepositoryBrowser::refresh);
}

RepositoryBrowser::~RepositoryBrowser()
{
}

void RepositoryBrowser::setupUi()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    
    m_treeView = new QTreeView(this);
    m_model = new QStandardItemModel(this);
    
    // Set up model headers
    m_model->setHorizontalHeaderLabels({"File", "Status"});
    
    m_treeView->setModel(m_model);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeView->setAlternatingRowColors(true);
    
    // Set column widths
    m_treeView->header()->setStretchLastSection(false);
    m_treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_treeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    
    m_layout->addWidget(m_treeView);
    
    // Connect signals
    connect(m_treeView, &QTreeView::clicked, this, &RepositoryBrowser::onItemClicked);
    connect(m_treeView, &QTreeView::doubleClicked, this, &RepositoryBrowser::onItemDoubleClicked);
    connect(m_treeView, &QTreeView::customContextMenuRequested, 
            this, &RepositoryBrowser::onCustomContextMenuRequested);
}

void RepositoryBrowser::setupContextMenu()
{
    m_contextMenu = new QMenu(this);
    
    m_stageAction = new QAction("Stage File", this);
    m_unstageAction = new QAction("Unstage File", this);
    m_discardAction = new QAction("Discard Changes", this);
    m_openAction = new QAction("Open File", this);
    
    m_contextMenu->addAction(m_stageAction);
    m_contextMenu->addAction(m_unstageAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_discardAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_openAction);
    
    connect(m_stageAction, &QAction::triggered, this, &RepositoryBrowser::stageFile);
    connect(m_unstageAction, &QAction::triggered, this, &RepositoryBrowser::unstageFile);
    connect(m_discardAction, &QAction::triggered, this, &RepositoryBrowser::discardChanges);
    connect(m_openAction, &QAction::triggered, this, &RepositoryBrowser::openFile);
}

void RepositoryBrowser::refresh()
{
    populateFileList();
}

void RepositoryBrowser::populateFileList()
{
    m_model->clear();
    m_model->setHorizontalHeaderLabels({"File", "Status"});
    
    if (!m_gitManager->hasRepository()) {
        return;
    }
    
    QList<GitFileStatus> fileStatus = m_gitManager->getFileStatus();
    
    for (const GitFileStatus &status : fileStatus) {
        QStandardItem *fileItem = new QStandardItem(status.filePath);
        QStandardItem *statusItem = new QStandardItem(status.status);
        
        // Set icons based on status
        fileItem->setIcon(getStatusIcon(status.status));
        
        // Set tooltips
        QString tooltip = QString("File: %1\nStatus: %2").arg(status.filePath, status.status);
        fileItem->setToolTip(tooltip);
        statusItem->setToolTip(tooltip);
        
        // Color coding
        if (status.isStaged) {
            fileItem->setForeground(QColor(0, 128, 0)); // Green for staged
        } else if (status.isModified) {
            fileItem->setForeground(QColor(255, 165, 0)); // Orange for modified
        } else if (status.isUntracked) {
            fileItem->setForeground(QColor(128, 128, 128)); // Gray for untracked
        }
        
        m_model->appendRow({fileItem, statusItem});
    }
    
    // Expand all and resize columns
    m_treeView->expandAll();
    m_treeView->resizeColumnToContents(1);
}

QIcon RepositoryBrowser::getStatusIcon(const QString &status) const
{
    // Return appropriate icons based on Git status
    // This is a simplified version - you might want to use actual icons
    if (status.contains('M')) {
        return QIcon(); // Modified icon
    } else if (status.contains('A')) {
        return QIcon(); // Added icon
    } else if (status.contains('D')) {
        return QIcon(); // Deleted icon
    } else if (status.contains('?')) {
        return QIcon(); // Untracked icon
    }
    return QIcon();
}

void RepositoryBrowser::onItemClicked(const QModelIndex &index)
{
    QString filePath = getFilePathFromIndex(index);
    if (!filePath.isEmpty()) {
        m_selectedFilePath = filePath;
        emit fileSelected(filePath);
    }
}

void RepositoryBrowser::onItemDoubleClicked(const QModelIndex &index)
{
    QString filePath = getFilePathFromIndex(index);
    if (!filePath.isEmpty()) {
        emit fileDoubleClicked(filePath);
    }
}

void RepositoryBrowser::onCustomContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = m_treeView->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    
    QString filePath = getFilePathFromIndex(index);
    if (filePath.isEmpty()) {
        return;
    }
    
    m_selectedFilePath = filePath;
    
    // Get file status to enable/disable appropriate actions
    QList<GitFileStatus> fileStatus = m_gitManager->getFileStatus();
    bool isStaged = false;
    bool isModified = false;
    
    for (const GitFileStatus &status : fileStatus) {
        if (status.filePath == filePath) {
            isStaged = status.isStaged;
            isModified = status.isModified || status.isUntracked;
            break;
        }
    }
    
    m_stageAction->setEnabled(isModified && !isStaged);
    m_unstageAction->setEnabled(isStaged);
    m_discardAction->setEnabled(isModified);
    
    m_contextMenu->exec(m_treeView->mapToGlobal(pos));
}

QString RepositoryBrowser::getFilePathFromIndex(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QString();
    }
    
    // Get the file path from the first column
    QModelIndex fileIndex = index.sibling(index.row(), 0);
    return m_model->itemFromIndex(fileIndex)->text();
}

void RepositoryBrowser::stageFile()
{
    if (!m_selectedFilePath.isEmpty()) {
        if (m_gitManager->stageFile(m_selectedFilePath)) {
            refresh();
        } else {
            QMessageBox::warning(this, "Error", "Failed to stage file");
        }
    }
}

void RepositoryBrowser::unstageFile()
{
    if (!m_selectedFilePath.isEmpty()) {
        if (m_gitManager->unstageFile(m_selectedFilePath)) {
            refresh();
        } else {
            QMessageBox::warning(this, "Error", "Failed to unstage file");
        }
    }
}

void RepositoryBrowser::discardChanges()
{
    if (m_selectedFilePath.isEmpty()) {
        return;
    }
    
    int ret = QMessageBox::question(this, "Discard Changes",
        QString("Are you sure you want to discard changes to '%1'?\n"
                "This action cannot be undone.").arg(m_selectedFilePath),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        if (m_gitManager->discardChanges(m_selectedFilePath)) {
            refresh();
        } else {
            QMessageBox::warning(this, "Error", "Failed to discard changes");
        }
    }
}

void RepositoryBrowser::openFile()
{
    if (!m_selectedFilePath.isEmpty() && m_gitManager->hasRepository()) {
        QString fullPath = m_gitManager->getRepositoryPath() + "/" + m_selectedFilePath;
        QDesktopServices::openUrl(QUrl::fromLocalFile(fullPath));
    }
}

#include "repositorybrowser.moc"
```

### Step 5: Building and Testing

#### 5.1 Build Configuration

```bash
# Create build script
# File: scripts/build.sh
#!/bin/bash

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Building Srikok Git...${NC}"

# Check if build directory exists
if [ ! -d "build" ]; then
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir build
fi

cd build

# Configure with CMake
echo -e "${YELLOW}Configuring with CMake...${NC}"
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the application
echo -e "${YELLOW}Building application...${NC}"
make -j$(nproc)

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Build successful!${NC}"
    echo -e "${GREEN}Executable location: ./build/SrikokGit${NC}"
else
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi
```

#### 5.2 Debug Build Script

```bash
# File: scripts/build-debug.sh
#!/bin/bash

set -e

echo "Building Srikok Git (Debug)..."

if [ ! -d "build-debug" ]; then
    mkdir build-debug
fi

cd build-debug

cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=ON
make -j$(nproc)

echo "Debug build complete!"
echo "Run with: ./build-debug/SrikokGit"
echo "Debug with: gdb ./build-debug/SrikokGit"
```

#### 5.3 Testing Framework Setup

```cpp
// File: tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Test)

# Enable testing
enable_testing()

# Test executable
add_executable(test_srikok_git
    test_main.cpp
    test_gitmanager.cpp
    test_mainwindow.cpp
)

target_link_libraries(test_srikok_git
    Qt6::Test
    Qt6::Core
    Qt6::Widgets
)

# Include source directories
target_include_directories(test_srikok_git PRIVATE
    ../include
    ../include/core
    ../include/ui
    ../include/dialogs
)

# Add test
add_test(NAME SrikokGitTests COMMAND test_srikok_git)
```

#### 5.4 Basic Test Implementation

```cpp
// File: tests/test_main.cpp
#include <QtTest>
#include "test_gitmanager.h"
#include "test_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    int result = 0;
    
    // Run GitManager tests
    TestGitManager gitManagerTest;
    result |= QTest::qExec(&gitManagerTest, argc, argv);
    
    // Run MainWindow tests
    TestMainWindow mainWindowTest;
    result |= QTest::qExec(&mainWindowTest, argc, argv);
    
    return result;
}
```

### Step 6: Deployment

#### 6.1 Installation Script

```bash
# File: scripts/install.sh
#!/bin/bash

set -e

PREFIX=${1:-/usr/local}
DESKTOP_FILES_DIR="$HOME/.local/share/applications"

echo "Installing Srikok Git to $PREFIX"

# Build if not already built
if [ ! -f "build/SrikokGit" ]; then
    echo "Building application first..."
    ./scripts/build.sh
fi

# Install binary
echo "Installing binary..."
sudo cp build/SrikokGit "$PREFIX/bin/"
sudo chmod +x "$PREFIX/bin/SrikokGit"

# Create desktop file
echo "Creating desktop entry..."
mkdir -p "$DESKTOP_FILES_DIR"

cat > "$DESKTOP_FILES_DIR/srikok-git.desktop" << EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=Srikok Git
GenericName=Git Repository Manager
Comment=Comprehensive Git repository management with Qt 6
Exec=$PREFIX/bin/SrikokGit
Icon=git
Terminal=false
StartupNotify=true
Categories=Development;RevisionControl;Qt;
MimeType=x-scheme-handler/git;
Keywords=git;version;control;repository;commit;branch;
EOF

chmod +x "$DESKTOP_FILES_DIR/srikok-git.desktop"
update-desktop-database "$DESKTOP_FILES_DIR"

echo "Installation complete!"
echo "You can now run 'SrikokGit' from the command line"
echo "or find it in your application menu."
```

#### 6.2 Package Creation

```bash
# File: scripts/create-deb.sh
#!/bin/bash

set -e

VERSION="1.0.0"
ARCH="amd64"
PACKAGE_NAME="srikok-git"

# Create package directory structure
mkdir -p "dist/${PACKAGE_NAME}_${VERSION}_${ARCH}/DEBIAN"
mkdir -p "dist/${PACKAGE_NAME}_${VERSION}_${ARCH}/usr/bin"
mkdir -p "dist/${PACKAGE_NAME}_${VERSION}_${ARCH}/usr/share/applications"

# Copy binary
cp build/SrikokGit "dist/${PACKAGE_NAME}_${VERSION}_${ARCH}/usr/bin/"

# Create control file
cat > "dist/${PACKAGE_NAME}_${VERSION}_${ARCH}/DEBIAN/control" << EOF
Package: ${PACKAGE_NAME}
Version: ${VERSION}
Section: devel
Priority: optional
Architecture: ${ARCH}
Depends: libqt6core6, libqt6widgets6, libqt6gui6, git
Maintainer: Srikoksoft <support@srikoksoft.com>
Description: Git Repository Manager
 A comprehensive Git repository management application built with Qt 6.
 Provides an intuitive graphical interface for Git operations including
 repository management, file staging, commit history, branch management,
 and remote operations.
EOF

# Create desktop file
cat > "dist/${PACKAGE_NAME}_${VERSION}_${ARCH}/usr/share/applications/srikok-git.desktop" << EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=Srikok Git
GenericName=Git Repository Manager
Comment=Comprehensive Git repository management with Qt 6
Exec=/usr/bin/SrikokGit
Icon=git
Terminal=false
StartupNotify=true
Categories=Development;RevisionControl;Qt;
MimeType=x-scheme-handler/git;
Keywords=git;version;control;repository;commit;branch;
EOF

# Build package
dpkg-deb --build "dist/${PACKAGE_NAME}_${VERSION}_${ARCH}"

echo "Debian package created: dist/${PACKAGE_NAME}_${VERSION}_${ARCH}.deb"
```

## Advanced Features

### Internationalization Support

```cpp
// File: src/core/translations.cpp
#include <QTranslator>
#include <QApplication>
#include <QLibraryInfo>
#include <QDir>

void loadTranslations(QApplication &app)
{
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                     QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator appTranslator;
    appTranslator.load("srikok-git_" + QLocale::system().name(),
                      ":/translations");
    app.installTranslator(&appTranslator);
}
```

### Plugin System Architecture

```cpp
// File: include/core/plugininterface.h
#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <QString>
#include <QWidget>

class GitManager;
class MainWindow;

class PluginInterface
{
public:
    virtual ~PluginInterface() = default;
    virtual QString pluginName() const = 0;
    virtual QString pluginVersion() const = 0;
    virtual QString pluginDescription() const = 0;
    virtual bool initialize(GitManager *gitManager, MainWindow *mainWindow) = 0;
    virtual void cleanup() = 0;
    virtual QWidget *createWidget() = 0;
};

Q_DECLARE_INTERFACE(PluginInterface, "com.srikoksoft.SrikokGit.PluginInterface/1.0")

#endif // PLUGININTERFACE_H
```

## Troubleshooting

### Common Build Issues

#### Qt 6 Not Found
```bash
# Solution 1: Set Qt path explicitly
export Qt6_DIR=/usr/lib/x86_64-linux-gnu/cmake/Qt6
cmake .. -DQt6_DIR=$Qt6_DIR

# Solution 2: Install Qt 6 development packages
sudo apt install qt6-base-dev qt6-tools-dev

# Solution 3: Use Qt installer
# Download from https://www.qt.io/download-qt-installer
```

#### CMake Version Issues
```bash
# Check CMake version
cmake --version

# Install newer CMake if needed
sudo apt remove cmake
sudo snap install cmake --classic

# Or build from source
wget https://cmake.org/files/v3.25/cmake-3.25.0.tar.gz
tar -xzf cmake-3.25.0.tar.gz
cd cmake-3.25.0
./bootstrap && make && sudo make install
```

#### Compiler Issues
```bash
# Install C++17 compatible compiler
sudo apt install gcc-11 g++-11

# Set as default
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 60
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 60

# Verify C++17 support
g++ -std=c++17 --version
```

### Runtime Issues

#### Missing Libraries
```bash
# Check dependencies
ldd ./build/SrikokGit

# Install missing Qt libraries
sudo apt install libqt6widgets6 libqt6core6 libqt6gui6

# Check library paths
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
```

#### Git Integration Problems
```bash
# Verify Git installation
git --version
which git

# Check Git configuration
git config --list

# Test Git in repository
cd /path/to/repo
git status
```

### Performance Optimization

#### Build Performance
```bash
# Use Ninja for faster builds
sudo apt install ninja-build
cmake .. -G Ninja
ninja -j$(nproc)

# Use ccache for faster rebuilds
sudo apt install ccache
export CC="ccache gcc"
export CXX="ccache g++"
cmake ..
```

#### Runtime Performance
```bash
# Enable Qt optimizations
export QT_LOGGING_RULES="*.debug=false"
export QT_AUTO_SCREEN_SCALE_FACTOR=1

# Use release build for production
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O3 -march=native"
```

## Conclusion

This comprehensive guide provides everything needed to build Srikok Git from scratch. The application demonstrates modern C++17 development with Qt 6, following best practices for:

- Cross-platform GUI development
- Git integration and version control
- Modular architecture design
- Build system configuration
- Testing and deployment
- Documentation and maintenance

For additional support and updates, visit [srikoksoft.com](http://srikoksoft.com) or refer to the project documentation.

**Srikoksoft Development Team**  
*Building innovative software solutions*