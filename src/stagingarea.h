#ifndef STAGINGAREA_H
#define STAGINGAREA_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QSplitter>

class GitManager;

class StagingArea : public QWidget
{
    Q_OBJECT

public:
    explicit StagingArea(GitManager *gitManager, QWidget *parent = nullptr);
    
    void refresh();

private slots:
    void commitChanges();
    void stageAll();
    void unstageAll();
    void onFileClicked(const QModelIndex &index);

private:
    void setupUI();
    void populateFileList();
    
    GitManager *m_gitManager;
    QListView *m_listView;
    QStandardItemModel *m_model;
    QTextEdit *m_commitMessage;
    QLineEdit *m_commitSummary;
    QPushButton *m_commitButton;
    QPushButton *m_stageAllButton;
    QPushButton *m_unstageAllButton;
    QLabel *m_titleLabel;
    QSplitter *m_splitter;
};

#endif // STAGINGAREA_H