#include "mainwindow.h"
#include "gitmanager.h"
#include "repositorybrowser.h"
#include "commithistory.h"
#include "stagingarea.h"
#include "branchmanager.h"
#include "remotemanager.h"
#include "diffviewer.h"
#include "settings.h"

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainSplitter(nullptr)
    , m_leftSplitter(nullptr)
    , m_rightSplitter(nullptr)
    , m_repositoryBrowser(nullptr)
    , m_commitHistory(nullptr)
    , m_stagingArea(nullptr)
    , m_diffViewer(nullptr)
    , m_gitManager(nullptr)
    , m_branchManager(nullptr)
    , m_remoteManager(nullptr)
    , m_settings(nullptr)
{
    setWindowTitle("SRK Git - Git Repository Manager");
    setWindowIcon(QIcon(":/icons/app.png"));
    resize(1200, 800);
    
    m_gitManager = new GitManager(this);
    m_branchManager = new BranchManager(m_gitManager, this);
    m_remoteManager = new RemoteManager(m_gitManager, this);
    m_settings = new Settings(this);
    
    setupUI();
    setupMenus();
    setupToolbar();
    setupStatusBar();
    createActions();
    connectSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget;
    setCentralWidget(m_centralWidget);
    
    m_mainSplitter = new QSplitter(Qt::Horizontal);
    m_leftSplitter = new QSplitter(Qt::Vertical);
    m_rightSplitter = new QSplitter(Qt::Vertical);
    
    m_repositoryBrowser = new RepositoryBrowser(m_gitManager, this);
    m_commitHistory = new CommitHistory(m_gitManager, this);
    m_stagingArea = new StagingArea(m_gitManager, this);
    m_diffViewer = new DiffViewer(m_gitManager, this);
    
    m_leftSplitter->addWidget(m_repositoryBrowser);
    m_leftSplitter->addWidget(m_stagingArea);
    m_leftSplitter->setSizes({400, 300});
    
    m_rightSplitter->addWidget(m_commitHistory);
    m_rightSplitter->addWidget(m_diffViewer);
    m_rightSplitter->setSizes({300, 400});
    
    m_mainSplitter->addWidget(m_leftSplitter);
    m_mainSplitter->addWidget(m_rightSplitter);
    m_mainSplitter->setSizes({500, 700});
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_mainSplitter);
    m_centralWidget->setLayout(layout);
}

void MainWindow::setupMenus()
{
    QMenuBar *menuBar = this->menuBar();
    
    QMenu *fileMenu = menuBar->addMenu("&File");
    QMenu *repositoryMenu = menuBar->addMenu("&Repository");
    QMenu *branchMenu = menuBar->addMenu("&Branch");
    QMenu *remoteMenu = menuBar->addMenu("&Remote");
    QMenu *viewMenu = menuBar->addMenu("&View");
    QMenu *helpMenu = menuBar->addMenu("&Help");
    
    m_openAction = new QAction("&Open Repository...", this);
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setStatusTip("Open an existing Git repository");
    
    m_cloneAction = new QAction("&Clone Repository...", this);
    m_cloneAction->setShortcut(QKeySequence("Ctrl+Shift+O"));
    m_cloneAction->setStatusTip("Clone a remote Git repository");
    
    m_refreshAction = new QAction("&Refresh", this);
    m_refreshAction->setShortcut(QKeySequence::Refresh);
    m_refreshAction->setStatusTip("Refresh repository status");
    
    m_settingsAction = new QAction("&Settings...", this);
    m_settingsAction->setShortcut(QKeySequence::Preferences);
    m_settingsAction->setStatusTip("Configure application settings");
    
    m_aboutAction = new QAction("&About SRK Git", this);
    m_aboutAction->setStatusTip("Show information about SRK Git");
    
    m_exitAction = new QAction("E&xit", this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_exitAction->setStatusTip("Exit the application");
    
    fileMenu->addAction(m_openAction);
    fileMenu->addAction(m_cloneAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_settingsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_exitAction);
    
    repositoryMenu->addAction(m_refreshAction);
    
    helpMenu->addAction(m_aboutAction);
}

void MainWindow::setupToolbar()
{
    QToolBar *mainToolBar = addToolBar("Main");
    mainToolBar->addAction(m_openAction);
    mainToolBar->addAction(m_cloneAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(m_refreshAction);
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel("Ready");
    m_branchLabel = new QLabel("No repository");
    m_repoLabel = new QLabel("");
    
    statusBar()->addWidget(m_statusLabel);
    statusBar()->addPermanentWidget(m_branchLabel);
    statusBar()->addPermanentWidget(m_repoLabel);
}

void MainWindow::createActions()
{
}

void MainWindow::connectSignals()
{
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openRepository);
    connect(m_cloneAction, &QAction::triggered, this, &MainWindow::cloneRepository);
    connect(m_refreshAction, &QAction::triggered, this, &MainWindow::refreshRepository);
    connect(m_settingsAction, &QAction::triggered, this, &MainWindow::showSettings);
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::openRepository()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Open Git Repository", QString(), QFileDialog::ShowDirsOnly);
    if (!dir.isEmpty()) {
        if (m_gitManager->openRepository(dir)) {
            m_statusLabel->setText("Repository opened: " + dir);
            m_repoLabel->setText(dir);
            refreshRepository();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open repository. Not a valid Git repository.");
        }
    }
}

void MainWindow::cloneRepository()
{
    bool ok;
    QString url = QInputDialog::getText(this, "Clone Repository", "Repository URL:", QLineEdit::Normal, QString(), &ok);
    if (ok && !url.isEmpty()) {
        QString dir = QFileDialog::getExistingDirectory(this, "Choose Clone Directory", QString(), QFileDialog::ShowDirsOnly);
        if (!dir.isEmpty()) {
            if (m_gitManager->cloneRepository(url, dir)) {
                m_statusLabel->setText("Repository cloned: " + url);
                openRepository();
            } else {
                QMessageBox::warning(this, "Error", "Failed to clone repository.");
            }
        }
    }
}

void MainWindow::refreshRepository()
{
    if (m_gitManager->isRepositoryOpen()) {
        m_repositoryBrowser->refresh();
        m_commitHistory->refresh();
        m_stagingArea->refresh();
        
        QString branch = m_gitManager->getCurrentBranch();
        m_branchLabel->setText("Branch: " + branch);
        m_statusLabel->setText("Repository refreshed");
    }
}

void MainWindow::showSettings()
{
    m_settings->show();
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "About SRK Git", 
        "SRK Git v1.0.0\n\n"
        "A Git repository manager.\n\n"
        "Copyright © 2024 SRK IT Service\n"
        "Built with Qt and C++");
}

