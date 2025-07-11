#include "repositorybrowser.h"
#include "gitmanager.h"
#include <QHeaderView>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QIcon>
#include <QFileInfo>

RepositoryBrowser::RepositoryBrowser(GitManager *gitManager, QWidget *parent)
    : QWidget(parent)
    , m_gitManager(gitManager)
    , m_treeView(nullptr)
    , m_model(nullptr)
    , m_titleLabel(nullptr)
    , m_refreshButton(nullptr)
    , m_contextMenu(nullptr)
{
    setupUI();
    
    connect(m_gitManager, &GitManager::repositoryChanged, this, &RepositoryBrowser::refresh);
    connect(m_gitManager, &GitManager::fileStatusChanged, this, &RepositoryBrowser::refresh);
}

void RepositoryBrowser::setupUI()
{
    setWindowTitle("Repository Browser");
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QHBoxLayout *headerLayout = new QHBoxLayout;
    m_titleLabel = new QLabel("Repository Files");
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 12px; padding: 5px;");
    
    m_refreshButton = new QPushButton("Refresh");
    m_refreshButton->setMaximumWidth(80);
    connect(m_refreshButton, &QPushButton::clicked, this, &RepositoryBrowser::refresh);
    
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_refreshButton);
    
    m_treeView = new QTreeView;
    m_model = new QStandardItemModel(this);
    m_model->setHorizontalHeaderLabels({"File", "Status"});
    
    m_treeView->setModel(m_model);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeView->setAlternatingRowColors(true);
    m_treeView->header()->setStretchLastSection(true);
    m_treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_treeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    
    connect(m_treeView, &QTreeView::clicked, this, &RepositoryBrowser::onItemClicked);
    connect(m_treeView, &QTreeView::doubleClicked, this, &RepositoryBrowser::onItemDoubleClicked);
    connect(m_treeView, &QTreeView::customContextMenuRequested, this, &RepositoryBrowser::showContextMenu);
    
    layout->addLayout(headerLayout);
    layout->addWidget(m_treeView);
    
    m_contextMenu = new QMenu(this);
    m_stageAction = m_contextMenu->addAction("Stage File");
    m_unstageAction = m_contextMenu->addAction("Unstage File");
    m_contextMenu->addSeparator();
    m_discardAction = m_contextMenu->addAction("Discard Changes");
    m_contextMenu->addSeparator();
    m_openAction = m_contextMenu->addAction("Open File");
    
    connect(m_stageAction, &QAction::triggered, this, &RepositoryBrowser::stageFile);
    connect(m_unstageAction, &QAction::triggered, this, &RepositoryBrowser::unstageFile);
    connect(m_discardAction, &QAction::triggered, this, &RepositoryBrowser::discardChanges);
    connect(m_openAction, &QAction::triggered, this, &RepositoryBrowser::openFile);
}

void RepositoryBrowser::refresh()
{
    if (!m_gitManager->isRepositoryOpen()) {
        m_model->clear();
        m_model->setHorizontalHeaderLabels({"File", "Status"});
        return;
    }
    
    populateTree();
}

void RepositoryBrowser::populateTree()
{
    m_model->clear();
    m_model->setHorizontalHeaderLabels({"File", "Status"});
    
    QStandardItem *rootItem = m_model->invisibleRootItem();
    
    QList<GitFileStatus> files = m_gitManager->getFileStatus();
    
    for (const GitFileStatus &file : files) {
        addFileToTree(file.filePath, file.status, rootItem);
    }
    
    m_treeView->expandAll();
}

void RepositoryBrowser::addFileToTree(const QString &filePath, const QString &status, QStandardItem *parent)
{
    QStringList pathParts = filePath.split('/', Qt::SkipEmptyParts);
    QStandardItem *currentParent = parent ? parent : m_model->invisibleRootItem();
    
    for (int i = 0; i < pathParts.size() - 1; ++i) {
        currentParent = findOrCreatePath(pathParts[i], currentParent);
    }
    
    QStandardItem *fileItem = new QStandardItem(pathParts.last());
    QStandardItem *statusItem = new QStandardItem(status);
    
    QFileInfo fileInfo(filePath);
    if (fileInfo.isFile()) {
        QString extension = fileInfo.suffix().toLower();
        if (extension == "cpp" || extension == "cc" || extension == "cxx") {
            fileItem->setIcon(QIcon(":/icons/cpp.png"));
        } else if (extension == "h" || extension == "hpp") {
            fileItem->setIcon(QIcon(":/icons/header.png"));
        } else if (extension == "txt") {
            fileItem->setIcon(QIcon(":/icons/text.png"));
        } else {
            fileItem->setIcon(QIcon(":/icons/file.png"));
        }
    } else {
        fileItem->setIcon(QIcon(":/icons/folder.png"));
    }
    
    fileItem->setData(filePath, Qt::UserRole);
    statusItem->setData(status, Qt::UserRole);
    
    if (status.contains('M')) {
        statusItem->setBackground(QBrush(QColor(255, 255, 0, 100)));
    } else if (status.contains('A')) {
        statusItem->setBackground(QBrush(QColor(0, 255, 0, 100)));
    } else if (status.contains('D')) {
        statusItem->setBackground(QBrush(QColor(255, 0, 0, 100)));
    } else if (status.contains('?')) {
        statusItem->setBackground(QBrush(QColor(128, 128, 128, 100)));
    }
    
    currentParent->appendRow({fileItem, statusItem});
}

QStandardItem *RepositoryBrowser::findOrCreatePath(const QString &path, QStandardItem *parent)
{
    QStandardItem *currentParent = parent ? parent : m_model->invisibleRootItem();
    
    for (int i = 0; i < currentParent->rowCount(); ++i) {
        QStandardItem *child = currentParent->child(i, 0);
        if (child && child->text() == path) {
            return child;
        }
    }
    
    QStandardItem *newItem = new QStandardItem(path);
    QStandardItem *statusItem = new QStandardItem("");
    newItem->setIcon(QIcon(":/icons/folder.png"));
    
    currentParent->appendRow({newItem, statusItem});
    return newItem;
}

void RepositoryBrowser::onItemClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QStandardItem *item = m_model->itemFromIndex(index);
        if (item) {
            QString filePath = item->data(Qt::UserRole).toString();
            if (!filePath.isEmpty()) {
                m_selectedFile = filePath;
                emit fileSelected(filePath);
            }
        }
    }
}

void RepositoryBrowser::onItemDoubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QStandardItem *item = m_model->itemFromIndex(index);
        if (item) {
            QString filePath = item->data(Qt::UserRole).toString();
            if (!filePath.isEmpty()) {
                emit fileDoubleClicked(filePath);
            }
        }
    }
}

void RepositoryBrowser::showContextMenu(const QPoint &point)
{
    QModelIndex index = m_treeView->indexAt(point);
    if (index.isValid()) {
        QStandardItem *item = m_model->itemFromIndex(index);
        if (item) {
            QString filePath = item->data(Qt::UserRole).toString();
            if (!filePath.isEmpty()) {
                m_selectedFile = filePath;
                
                QString status = getFileStatus(filePath);
                m_stageAction->setEnabled(!status.isEmpty() && !status.at(0).isSpace());
                m_unstageAction->setEnabled(!status.isEmpty() && status.at(0) != ' ' && status.at(0) != '?');
                m_discardAction->setEnabled(!status.isEmpty() && status.contains('M'));
                
                m_contextMenu->exec(m_treeView->mapToGlobal(point));
            }
        }
    }
}

QString RepositoryBrowser::getFileStatus(const QString &filePath) const
{
    QList<GitFileStatus> files = m_gitManager->getFileStatus();
    
    for (const GitFileStatus &file : files) {
        if (file.filePath == filePath) {
            return file.status;
        }
    }
    
    return QString();
}

void RepositoryBrowser::stageFile()
{
    if (!m_selectedFile.isEmpty()) {
        if (m_gitManager->stageFile(m_selectedFile)) {
            refresh();
        } else {
            QMessageBox::warning(this, "Error", "Failed to stage file: " + m_gitManager->getLastError());
        }
    }
}

void RepositoryBrowser::unstageFile()
{
    if (!m_selectedFile.isEmpty()) {
        if (m_gitManager->unstageFile(m_selectedFile)) {
            refresh();
        } else {
            QMessageBox::warning(this, "Error", "Failed to unstage file: " + m_gitManager->getLastError());
        }
    }
}

void RepositoryBrowser::discardChanges()
{
    if (!m_selectedFile.isEmpty()) {
        int ret = QMessageBox::question(this, "Discard Changes", 
            "Are you sure you want to discard changes to " + m_selectedFile + "?\nThis action cannot be undone.",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        
        if (ret == QMessageBox::Yes) {
            QMessageBox::information(this, "Info", "Discard changes functionality not yet implemented");
        }
    }
}

void RepositoryBrowser::openFile()
{
    if (!m_selectedFile.isEmpty()) {
        QString fullPath = m_gitManager->getRepositoryPath() + "/" + m_selectedFile;
        QDesktopServices::openUrl(QUrl::fromLocalFile(fullPath));
    }
}