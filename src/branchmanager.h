#ifndef BRANCHMANAGER_H
#define BRANCHMANAGER_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class GitManager;

class BranchManager : public QObject
{
    Q_OBJECT

public:
    explicit BranchManager(GitManager *gitManager, QObject *parent = nullptr);
    
    void showBranchDialog();

private slots:
    void createBranch();
    void switchBranch();
    void deleteBranch();
    void mergeBranch();
    void refreshBranches();

private:
    GitManager *m_gitManager;
    QDialog *m_dialog;
    QListWidget *m_branchList;
    QLineEdit *m_branchNameEdit;
    QPushButton *m_createButton;
    QPushButton *m_switchButton;
    QPushButton *m_deleteButton;
    QPushButton *m_mergeButton;
    QPushButton *m_refreshButton;
    
    void setupUI();
    void populateBranchList();
};

#endif // BRANCHMANAGER_H