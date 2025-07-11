#ifndef COMMITHISTORY_H
#define COMMITHISTORY_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QSplitter>

class GitManager;

class CommitHistory : public QWidget
{
    Q_OBJECT

public:
    explicit CommitHistory(GitManager *gitManager, QWidget *parent = nullptr);
    
    void refresh();

signals:
    void commitSelected(const QString &commitHash);

private slots:
    void onCommitClicked(const QModelIndex &index);
    void showCommitDetails(const QString &commitHash);

private:
    void setupUI();
    void populateCommitList();
    
    GitManager *m_gitManager;
    QListView *m_listView;
    QStandardItemModel *m_model;
    QTextEdit *m_detailsView;
    QSplitter *m_splitter;
    QLabel *m_titleLabel;
    QPushButton *m_refreshButton;
    
    QString m_selectedCommit;
};

#endif // COMMITHISTORY_H