#include "stagingarea.h"
#include "gitmanager.h"
#include <QMessageBox>
#include <QGroupBox>

StagingArea::StagingArea(GitManager *gitManager, QWidget *parent)
    : QWidget(parent)
    , m_gitManager(gitManager)
    , m_listView(nullptr)
    , m_model(nullptr)
    , m_commitMessage(nullptr)
    , m_commitSummary(nullptr)
    , m_commitButton(nullptr)
    , m_stageAllButton(nullptr)
    , m_unstageAllButton(nullptr)
    , m_titleLabel(nullptr)
    , m_splitter(nullptr)
{
    setupUI();
    
    connect(m_gitManager, &GitManager::repositoryChanged, this, &StagingArea::refresh);
    connect(m_gitManager, &GitManager::fileStatusChanged, this, &StagingArea::refresh);
}

void StagingArea::setupUI()
{
    setWindowTitle("Staging Area");
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    m_titleLabel = new QLabel("Staging Area");
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 12px; padding: 5px;");
    
    m_splitter = new QSplitter(Qt::Vertical);
    
    QWidget *fileListWidget = new QWidget;
    QVBoxLayout *fileListLayout = new QVBoxLayout(fileListWidget);
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    m_stageAllButton = new QPushButton("Stage All");
    m_unstageAllButton = new QPushButton("Unstage All");
    
    connect(m_stageAllButton, &QPushButton::clicked, this, &StagingArea::stageAll);
    connect(m_unstageAllButton, &QPushButton::clicked, this, &StagingArea::unstageAll);
    
    buttonsLayout->addWidget(m_stageAllButton);
    buttonsLayout->addWidget(m_unstageAllButton);
    buttonsLayout->addStretch();
    
    m_listView = new QListView;
    m_model = new QStandardItemModel(this);
    m_listView->setModel(m_model);
    m_listView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_listView->setAlternatingRowColors(true);
    
    connect(m_listView, &QListView::clicked, this, &StagingArea::onFileClicked);
    
    fileListLayout->addLayout(buttonsLayout);
    fileListLayout->addWidget(m_listView);
    
    QGroupBox *commitGroup = new QGroupBox("Commit");
    QVBoxLayout *commitLayout = new QVBoxLayout(commitGroup);
    
    QLabel *summaryLabel = new QLabel("Summary:");
    m_commitSummary = new QLineEdit;
    m_commitSummary->setPlaceholderText("Enter commit summary...");
    
    QLabel *messageLabel = new QLabel("Description:");
    m_commitMessage = new QTextEdit;
    m_commitMessage->setPlaceholderText("Enter detailed commit message...");
    m_commitMessage->setMaximumHeight(80);
    
    m_commitButton = new QPushButton("Commit");
    m_commitButton->setEnabled(false);
    
    connect(m_commitButton, &QPushButton::clicked, this, &StagingArea::commitChanges);
    connect(m_commitSummary, &QLineEdit::textChanged, [this](const QString &text) {
        m_commitButton->setEnabled(!text.isEmpty());
    });
    
    commitLayout->addWidget(summaryLabel);
    commitLayout->addWidget(m_commitSummary);
    commitLayout->addWidget(messageLabel);
    commitLayout->addWidget(m_commitMessage);
    commitLayout->addWidget(m_commitButton);
    
    m_splitter->addWidget(fileListWidget);
    m_splitter->addWidget(commitGroup);
    m_splitter->setSizes({200, 150});
    
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_splitter);
}

void StagingArea::refresh()
{
    if (!m_gitManager->isRepositoryOpen()) {
        m_model->clear();
        return;
    }
    
    populateFileList();
}

void StagingArea::populateFileList()
{
    m_model->clear();
    
    QList<GitFileStatus> files = m_gitManager->getFileStatus();
    
    for (const GitFileStatus &file : files) {
        QStandardItem *item = new QStandardItem();
        
        QString displayText = QString("%1 %2")
            .arg(file.status)
            .arg(file.filePath);
        
        item->setText(displayText);
        item->setData(file.filePath, Qt::UserRole);
        item->setData(file.status, Qt::UserRole + 1);
        
        if (file.isStaged) {
            item->setBackground(QBrush(QColor(0, 255, 0, 50)));
        } else if (file.isModified) {
            item->setBackground(QBrush(QColor(255, 255, 0, 50)));
        } else if (file.isUntracked) {
            item->setBackground(QBrush(QColor(128, 128, 128, 50)));
        }
        
        m_model->appendRow(item);
    }
}

void StagingArea::commitChanges()
{
    QString summary = m_commitSummary->text().trimmed();
    QString description = m_commitMessage->toPlainText().trimmed();
    
    if (summary.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a commit summary.");
        return;
    }
    
    QString fullMessage = summary;
    if (!description.isEmpty()) {
        fullMessage += "\n\n" + description;
    }
    
    if (m_gitManager->commit(fullMessage)) {
        m_commitSummary->clear();
        m_commitMessage->clear();
        QMessageBox::information(this, "Success", "Changes committed successfully!");
        refresh();
    } else {
        QMessageBox::warning(this, "Error", "Failed to commit changes: " + m_gitManager->getLastError());
    }
}

void StagingArea::stageAll()
{
    if (m_gitManager->stageAll()) {
        refresh();
    } else {
        QMessageBox::warning(this, "Error", "Failed to stage all files: " + m_gitManager->getLastError());
    }
}

void StagingArea::unstageAll()
{
    if (m_gitManager->unstageAll()) {
        refresh();
    } else {
        QMessageBox::warning(this, "Error", "Failed to unstage all files: " + m_gitManager->getLastError());
    }
}

void StagingArea::onFileClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QStandardItem *item = m_model->itemFromIndex(index);
        if (item) {
            QString filePath = item->data(Qt::UserRole).toString();
            QString status = item->data(Qt::UserRole + 1).toString();
            
            if (status.at(0) != ' ' && status.at(0) != '?') {
                if (m_gitManager->unstageFile(filePath)) {
                    refresh();
                }
            } else {
                if (m_gitManager->stageFile(filePath)) {
                    refresh();
                }
            }
        }
    }
}