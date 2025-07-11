#include "diffviewer.h"
#include "gitmanager.h"
#include <QFont>

DiffViewer::DiffViewer(GitManager *gitManager, QWidget *parent)
    : QWidget(parent)
    , m_gitManager(gitManager)
    , m_textEdit(nullptr)
    , m_titleLabel(nullptr)
{
    setupUI();
}

void DiffViewer::setupUI()
{
    setWindowTitle("Diff Viewer");
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    m_titleLabel = new QLabel("Diff Viewer");
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 12px; padding: 5px;");
    
    m_textEdit = new QTextEdit;
    m_textEdit->setReadOnly(true);
    m_textEdit->setPlainText("Select a file to view differences...");
    
    QFont font("Courier New", 9);
    m_textEdit->setFont(font);
    
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_textEdit);
}

void DiffViewer::showFileDiff(const QString &filePath)
{
    if (!m_gitManager->isRepositoryOpen()) {
        m_textEdit->setPlainText("No repository opened...");
        return;
    }
    
    QString diff = m_gitManager->getFileDiff(filePath);
    
    if (diff.isEmpty()) {
        m_textEdit->setPlainText("No differences found for: " + filePath);
    } else {
        m_titleLabel->setText("Diff: " + filePath);
        m_textEdit->setPlainText(diff);
    }
}

void DiffViewer::clear()
{
    m_titleLabel->setText("Diff Viewer");
    m_textEdit->setPlainText("Select a file to view differences...");
}