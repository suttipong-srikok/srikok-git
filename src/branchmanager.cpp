#include "branchmanager.h"
#include "gitmanager.h"
#include <QMessageBox>
#include <QInputDialog>

BranchManager::BranchManager(GitManager *gitManager, QObject *parent)
    : QObject(parent)
    , m_gitManager(gitManager)
    , m_dialog(nullptr)
{
}

void BranchManager::setupUI()
{
    m_dialog = new QDialog();
    m_dialog->setWindowTitle("Branch Manager");
    m_dialog->resize(400, 300);
    
    QVBoxLayout *layout = new QVBoxLayout(m_dialog);
    
    QLabel *titleLabel = new QLabel("Branches");
    titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    
    m_branchList = new QListWidget;
    
    QHBoxLayout *createLayout = new QHBoxLayout;
    m_branchNameEdit = new QLineEdit;
    m_branchNameEdit->setPlaceholderText("New branch name...");
    m_createButton = new QPushButton("Create");
    
    createLayout->addWidget(m_branchNameEdit);
    createLayout->addWidget(m_createButton);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_switchButton = new QPushButton("Switch");
    m_deleteButton = new QPushButton("Delete");
    m_mergeButton = new QPushButton("Merge");
    m_refreshButton = new QPushButton("Refresh");
    
    buttonLayout->addWidget(m_switchButton);
    buttonLayout->addWidget(m_deleteButton);
    buttonLayout->addWidget(m_mergeButton);
    buttonLayout->addWidget(m_refreshButton);
    
    layout->addWidget(titleLabel);
    layout->addWidget(m_branchList);
    layout->addLayout(createLayout);
    layout->addLayout(buttonLayout);
    
    connect(m_createButton, &QPushButton::clicked, this, &BranchManager::createBranch);
    connect(m_switchButton, &QPushButton::clicked, this, &BranchManager::switchBranch);
    connect(m_deleteButton, &QPushButton::clicked, this, &BranchManager::deleteBranch);
    connect(m_mergeButton, &QPushButton::clicked, this, &BranchManager::mergeBranch);
    connect(m_refreshButton, &QPushButton::clicked, this, &BranchManager::refreshBranches);
}

void BranchManager::showBranchDialog()
{
    if (!m_dialog) {
        setupUI();
    }
    
    populateBranchList();
    m_dialog->exec();
}

void BranchManager::populateBranchList()
{
    m_branchList->clear();
    
    if (!m_gitManager->isRepositoryOpen()) {
        return;
    }
    
    QStringList branches = m_gitManager->getBranches();
    QString currentBranch = m_gitManager->getCurrentBranch();
    
    for (const QString &branch : branches) {
        QListWidgetItem *item = new QListWidgetItem(branch);
        if (branch == currentBranch) {
            item->setText("* " + branch);
            item->setBackground(QBrush(QColor(0, 255, 0, 50)));
        }
        m_branchList->addItem(item);
    }
}

void BranchManager::createBranch()
{
    QString branchName = m_branchNameEdit->text().trimmed();
    if (branchName.isEmpty()) {
        QMessageBox::warning(m_dialog, "Error", "Please enter a branch name.");
        return;
    }
    
    if (m_gitManager->createBranch(branchName)) {
        m_branchNameEdit->clear();
        populateBranchList();
        QMessageBox::information(m_dialog, "Success", "Branch created successfully!");
    } else {
        QMessageBox::warning(m_dialog, "Error", "Failed to create branch: " + m_gitManager->getLastError());
    }
}

void BranchManager::switchBranch()
{
    QListWidgetItem *current = m_branchList->currentItem();
    if (!current) {
        QMessageBox::warning(m_dialog, "Error", "Please select a branch to switch to.");
        return;
    }
    
    QString branchName = current->text();
    if (branchName.startsWith("* ")) {
        branchName = branchName.mid(2);
    }
    
    if (m_gitManager->switchBranch(branchName)) {
        populateBranchList();
        QMessageBox::information(m_dialog, "Success", "Switched to branch: " + branchName);
    } else {
        QMessageBox::warning(m_dialog, "Error", "Failed to switch branch: " + m_gitManager->getLastError());
    }
}

void BranchManager::deleteBranch()
{
    QListWidgetItem *current = m_branchList->currentItem();
    if (!current) {
        QMessageBox::warning(m_dialog, "Error", "Please select a branch to delete.");
        return;
    }
    
    QString branchName = current->text();
    if (branchName.startsWith("* ")) {
        QMessageBox::warning(m_dialog, "Error", "Cannot delete the current branch.");
        return;
    }
    
    int ret = QMessageBox::question(m_dialog, "Delete Branch", 
        "Are you sure you want to delete branch: " + branchName + "?",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        if (m_gitManager->deleteBranch(branchName)) {
            populateBranchList();
            QMessageBox::information(m_dialog, "Success", "Branch deleted successfully!");
        } else {
            QMessageBox::warning(m_dialog, "Error", "Failed to delete branch: " + m_gitManager->getLastError());
        }
    }
}

void BranchManager::mergeBranch()
{
    QListWidgetItem *current = m_branchList->currentItem();
    if (!current) {
        QMessageBox::warning(m_dialog, "Error", "Please select a branch to merge.");
        return;
    }
    
    QString branchName = current->text();
    if (branchName.startsWith("* ")) {
        QMessageBox::warning(m_dialog, "Error", "Cannot merge the current branch into itself.");
        return;
    }
    
    int ret = QMessageBox::question(m_dialog, "Merge Branch", 
        "Are you sure you want to merge branch: " + branchName + " into the current branch?",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        if (m_gitManager->mergeBranch(branchName)) {
            QMessageBox::information(m_dialog, "Success", "Branch merged successfully!");
        } else {
            QMessageBox::warning(m_dialog, "Error", "Failed to merge branch: " + m_gitManager->getLastError());
        }
    }
}

void BranchManager::refreshBranches()
{
    populateBranchList();
}