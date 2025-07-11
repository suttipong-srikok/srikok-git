#ifndef GITMANAGER_H
#define GITMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QFileInfo>
#include <QDir>

struct GitFileStatus {
    QString filePath;
    QString status;
    bool isStaged;
    bool isModified;
    bool isUntracked;
    bool isDeleted;
};

struct GitCommit {
    QString hash;
    QString author;
    QString date;
    QString message;
    QStringList parents;
};

class GitManager : public QObject
{
    Q_OBJECT

public:
    explicit GitManager(QObject *parent = nullptr);
    
    bool openRepository(const QString &path);
    bool cloneRepository(const QString &url, const QString &path);
    bool isRepositoryOpen() const;
    QString getRepositoryPath() const;
    
    QString getCurrentBranch() const;
    QStringList getBranches() const;
    QStringList getRemoteBranches() const;
    QStringList getRemotes() const;
    
    QList<GitFileStatus> getFileStatus() const;
    QList<GitCommit> getCommitHistory(int limit = 100) const;
    QString getFileContent(const QString &filePath, const QString &revision = "HEAD") const;
    QString getFileDiff(const QString &filePath) const;
    
    bool stageFile(const QString &filePath);
    bool unstageFile(const QString &filePath);
    bool stageAll();
    bool unstageAll();
    
    bool commit(const QString &message);
    bool createBranch(const QString &branchName);
    bool switchBranch(const QString &branchName);
    bool deleteBranch(const QString &branchName);
    bool mergeBranch(const QString &branchName);
    
    bool addRemote(const QString &name, const QString &url);
    bool removeRemote(const QString &name);
    bool fetch(const QString &remote = "origin");
    bool pull(const QString &remote = "origin", const QString &branch = "");
    bool push(const QString &remote = "origin", const QString &branch = "");
    
    QString getLastError() const;

signals:
    void repositoryChanged();
    void fileStatusChanged();
    void branchChanged();

private:
    bool executeGitCommand(const QString &command, const QStringList &args, QString &output) const;
    bool executeGitCommand(const QString &command, const QStringList &args) const;
    QString parseGitOutput(const QString &output) const;
    
    QString m_repositoryPath;
    QString m_lastError;
    bool m_isRepositoryOpen;
};

#endif // GITMANAGER_H