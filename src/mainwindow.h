#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTreeView>
#include <QListView>
#include <QTextEdit>
#include <QAction>
#include <QLabel>

class GitManager;
class RepositoryBrowser;
class CommitHistory;
class StagingArea;
class BranchManager;
class RemoteManager;
class DiffViewer;
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
    void showSettings();
    void showAbout();
    void refreshRepository();

private:
    void setupUI();
    void setupMenus();
    void setupToolbar();
    void setupStatusBar();
    void createActions();
    void connectSignals();

    QWidget *m_centralWidget;
    QSplitter *m_mainSplitter;
    QSplitter *m_leftSplitter;
    QSplitter *m_rightSplitter;
    
    RepositoryBrowser *m_repositoryBrowser;
    CommitHistory *m_commitHistory;
    StagingArea *m_stagingArea;
    DiffViewer *m_diffViewer;
    
    GitManager *m_gitManager;
    BranchManager *m_branchManager;
    RemoteManager *m_remoteManager;
    Settings *m_settings;
    
    QAction *m_openAction;
    QAction *m_cloneAction;
    QAction *m_refreshAction;
    QAction *m_settingsAction;
    QAction *m_aboutAction;
    QAction *m_exitAction;
    
    QLabel *m_statusLabel;
    QLabel *m_branchLabel;
    QLabel *m_repoLabel;
};

#endif // MAINWINDOW_H