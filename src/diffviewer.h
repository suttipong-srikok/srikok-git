#ifndef DIFFVIEWER_H
#define DIFFVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>

class GitManager;

class DiffViewer : public QWidget
{
    Q_OBJECT

public:
    explicit DiffViewer(GitManager *gitManager, QWidget *parent = nullptr);
    
    void showFileDiff(const QString &filePath);
    void clear();

private:
    void setupUI();
    
    GitManager *m_gitManager;
    QTextEdit *m_textEdit;
    QLabel *m_titleLabel;
};

#endif // DIFFVIEWER_H