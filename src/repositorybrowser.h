#ifndef REPOSITORYBROWSER_H
#define REPOSITORYBROWSER_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

class GitManager;

class RepositoryBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit RepositoryBrowser(GitManager *gitManager, QWidget *parent = nullptr);
    
    void refresh();

signals:
    void fileSelected(const QString &filePath);
    void fileDoubleClicked(const QString &filePath);

private slots:
    void onItemClicked(const QModelIndex &index);
    void onItemDoubleClicked(const QModelIndex &index);
    void showContextMenu(const QPoint &point);
    void stageFile();
    void unstageFile();
    void discardChanges();
    void openFile();

private:
    void setupUI();
    void populateTree();
    void addFileToTree(const QString &filePath, const QString &status, QStandardItem *parent = nullptr);
    QString getFileStatus(const QString &filePath) const;
    QStandardItem *findOrCreatePath(const QString &path, QStandardItem *parent = nullptr);
    
    GitManager *m_gitManager;
    QTreeView *m_treeView;
    QStandardItemModel *m_model;
    QLabel *m_titleLabel;
    QPushButton *m_refreshButton;
    
    QMenu *m_contextMenu;
    QAction *m_stageAction;
    QAction *m_unstageAction;
    QAction *m_discardAction;
    QAction *m_openAction;
    
    QString m_selectedFile;
};

#endif // REPOSITORYBROWSER_H