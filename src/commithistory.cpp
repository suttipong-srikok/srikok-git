#include "commithistory.h"
#include "gitmanager.h"
#include <QFont>
#include <QFontMetrics>

CommitHistory::CommitHistory(GitManager *gitManager, QWidget *parent)
    : QWidget(parent)
    , m_gitManager(gitManager)
    , m_listView(nullptr)
    , m_model(nullptr)
    , m_detailsView(nullptr)
    , m_splitter(nullptr)
    , m_titleLabel(nullptr)
    , m_refreshButton(nullptr)
{
    setupUI();
    
    connect(m_gitManager, &GitManager::repositoryChanged, this, &CommitHistory::refresh);
    connect(m_gitManager, &GitManager::branchChanged, this, &CommitHistory::refresh);
}

void CommitHistory::setupUI()
{
    setWindowTitle("Commit History");
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QHBoxLayout *headerLayout = new QHBoxLayout;
    m_titleLabel = new QLabel("Commit History");
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 12px; padding: 5px;");
    
    m_refreshButton = new QPushButton("Refresh");
    m_refreshButton->setMaximumWidth(80);
    connect(m_refreshButton, &QPushButton::clicked, this, &CommitHistory::refresh);
    
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_refreshButton);
    
    m_splitter = new QSplitter(Qt::Vertical);
    
    m_listView = new QListView;
    m_model = new QStandardItemModel(this);
    m_listView->setModel(m_model);
    m_listView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_listView->setAlternatingRowColors(true);
    
    connect(m_listView, &QListView::clicked, this, &CommitHistory::onCommitClicked);
    
    m_detailsView = new QTextEdit;
    m_detailsView->setReadOnly(true);
    m_detailsView->setMaximumHeight(150);
    m_detailsView->setPlainText("Select a commit to view details...");
    
    m_splitter->addWidget(m_listView);
    m_splitter->addWidget(m_detailsView);
    m_splitter->setSizes({300, 150});
    
    layout->addLayout(headerLayout);
    layout->addWidget(m_splitter);
}

void CommitHistory::refresh()
{
    if (!m_gitManager->isRepositoryOpen()) {
        m_model->clear();
        m_detailsView->setPlainText("No repository opened...");
        return;
    }
    
    populateCommitList();
}

void CommitHistory::populateCommitList()
{
    m_model->clear();
    
    QList<GitCommit> commits = m_gitManager->getCommitHistory(100);
    
    for (const GitCommit &commit : commits) {
        QStandardItem *item = new QStandardItem();
        
        QString displayText = QString("%1 - %2\n%3 (%4)")
            .arg(commit.hash.left(8))
            .arg(commit.message)
            .arg(commit.author)
            .arg(commit.date);
        
        item->setText(displayText);
        item->setData(commit.hash, Qt::UserRole);
        item->setData(commit.message, Qt::UserRole + 1);
        item->setData(commit.author, Qt::UserRole + 2);
        item->setData(commit.date, Qt::UserRole + 3);
        
        QFont font = item->font();
        font.setFamily("Courier New");
        font.setPointSize(9);
        item->setFont(font);
        
        item->setToolTip(QString("Hash: %1\nAuthor: %2\nDate: %3\nMessage: %4")
            .arg(commit.hash)
            .arg(commit.author)
            .arg(commit.date)
            .arg(commit.message));
        
        m_model->appendRow(item);
    }
}

void CommitHistory::onCommitClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QStandardItem *item = m_model->itemFromIndex(index);
        if (item) {
            QString commitHash = item->data(Qt::UserRole).toString();
            if (!commitHash.isEmpty()) {
                m_selectedCommit = commitHash;
                showCommitDetails(commitHash);
                emit commitSelected(commitHash);
            }
        }
    }
}

void CommitHistory::showCommitDetails(const QString &commitHash)
{
    QModelIndex index = m_listView->currentIndex();
    if (index.isValid()) {
        QStandardItem *item = m_model->itemFromIndex(index);
        if (item) {
            QString hash = item->data(Qt::UserRole).toString();
            QString message = item->data(Qt::UserRole + 1).toString();
            QString author = item->data(Qt::UserRole + 2).toString();
            QString date = item->data(Qt::UserRole + 3).toString();
            
            QString details = QString("Commit: %1\nAuthor: %2\nDate: %3\n\nMessage:\n%4")
                .arg(hash)
                .arg(author)
                .arg(date)
                .arg(message);
            
            m_detailsView->setPlainText(details);
        }
    }
}