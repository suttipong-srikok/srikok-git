#include "gitmanager.h"
#include <QDebug>
#include <QRegularExpression>
#include <QDateTime>

GitManager::GitManager(QObject *parent)
    : QObject(parent)
    , m_isRepositoryOpen(false)
{
}

bool GitManager::openRepository(const QString &path)
{
    QDir dir(path);
    if (!dir.exists() || !dir.exists(".git")) {
        m_lastError = "Not a valid Git repository";
        return false;
    }
    
    m_repositoryPath = path;
    m_isRepositoryOpen = true;
    
    emit repositoryChanged();
    return true;
}

bool GitManager::cloneRepository(const QString &url, const QString &path)
{
    QStringList args;
    args << "clone" << url << path;
    
    if (executeGitCommand("git", args)) {
        m_repositoryPath = path;
        m_isRepositoryOpen = true;
        emit repositoryChanged();
        return true;
    }
    
    return false;
}

bool GitManager::isRepositoryOpen() const
{
    return m_isRepositoryOpen;
}

QString GitManager::getRepositoryPath() const
{
    return m_repositoryPath;
}

QString GitManager::getCurrentBranch() const
{
    if (!m_isRepositoryOpen) return QString();
    
    QString output;
    QStringList args;
    args << "rev-parse" << "--abbrev-ref" << "HEAD";
    
    if (executeGitCommand("git", args, output)) {
        return output.trimmed();
    }
    
    return QString();
}

QStringList GitManager::getBranches() const
{
    if (!m_isRepositoryOpen) return QStringList();
    
    QString output;
    QStringList args;
    args << "branch";
    
    if (executeGitCommand("git", args, output)) {
        QStringList branches;
        QStringList lines = output.split('\n');
        
        for (const QString &line : lines) {
            QString branch = line.trimmed();
            if (branch.startsWith("* ")) {
                branch = branch.mid(2);
            }
            if (!branch.isEmpty()) {
                branches.append(branch);
            }
        }
        
        return branches;
    }
    
    return QStringList();
}

QStringList GitManager::getRemoteBranches() const
{
    if (!m_isRepositoryOpen) return QStringList();
    
    QString output;
    QStringList args;
    args << "branch" << "-r";
    
    if (executeGitCommand("git", args, output)) {
        QStringList branches;
        QStringList lines = output.split('\n');
        
        for (const QString &line : lines) {
            QString branch = line.trimmed();
            if (!branch.isEmpty() && !branch.contains("HEAD")) {
                branches.append(branch);
            }
        }
        
        return branches;
    }
    
    return QStringList();
}

QStringList GitManager::getRemotes() const
{
    if (!m_isRepositoryOpen) return QStringList();
    
    QString output;
    QStringList args;
    args << "remote";
    
    if (executeGitCommand("git", args, output)) {
        return output.split('\n', Qt::SkipEmptyParts);
    }
    
    return QStringList();
}

QList<GitFileStatus> GitManager::getFileStatus() const
{
    QList<GitFileStatus> files;
    
    if (!m_isRepositoryOpen) return files;
    
    QString output;
    QStringList args;
    args << "status" << "--porcelain";
    
    if (executeGitCommand("git", args, output)) {
        QStringList lines = output.split('\n');
        
        for (const QString &line : lines) {
            if (line.length() >= 3) {
                GitFileStatus file;
                file.status = line.left(2);
                file.filePath = line.mid(3);
                file.isStaged = (file.status[0] != ' ' && file.status[0] != '?');
                file.isModified = (file.status[1] != ' ');
                file.isUntracked = (file.status == "??");
                file.isDeleted = (file.status.contains('D'));
                
                files.append(file);
            }
        }
    }
    
    return files;
}

QList<GitCommit> GitManager::getCommitHistory(int limit) const
{
    QList<GitCommit> commits;
    
    if (!m_isRepositoryOpen) return commits;
    
    QString output;
    QStringList args;
    args << "log" << "--oneline" << "--pretty=format:%H|%an|%ad|%s|%P" << "--date=short";
    if (limit > 0) {
        args << "-n" << QString::number(limit);
    }
    
    if (executeGitCommand("git", args, output)) {
        QStringList lines = output.split('\n');
        
        for (const QString &line : lines) {
            if (!line.isEmpty()) {
                QStringList parts = line.split('|');
                if (parts.size() >= 4) {
                    GitCommit commit;
                    commit.hash = parts[0];
                    commit.author = parts[1];
                    commit.date = parts[2];
                    commit.message = parts[3];
                    if (parts.size() > 4) {
                        commit.parents = parts[4].split(' ', Qt::SkipEmptyParts);
                    }
                    
                    commits.append(commit);
                }
            }
        }
    }
    
    return commits;
}

QString GitManager::getFileContent(const QString &filePath, const QString &revision) const
{
    if (!m_isRepositoryOpen) return QString();
    
    QString output;
    QStringList args;
    args << "show" << (revision + ":" + filePath);
    
    if (executeGitCommand("git", args, output)) {
        return output;
    }
    
    return QString();
}

QString GitManager::getFileDiff(const QString &filePath) const
{
    if (!m_isRepositoryOpen) return QString();
    
    QString output;
    QStringList args;
    args << "diff" << filePath;
    
    if (executeGitCommand("git", args, output)) {
        return output;
    }
    
    return QString();
}

bool GitManager::stageFile(const QString &filePath)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "add" << filePath;
    
    if (executeGitCommand("git", args)) {
        emit fileStatusChanged();
        return true;
    }
    
    return false;
}

bool GitManager::unstageFile(const QString &filePath)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "reset" << "HEAD" << filePath;
    
    if (executeGitCommand("git", args)) {
        emit fileStatusChanged();
        return true;
    }
    
    return false;
}

bool GitManager::stageAll()
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "add" << ".";
    
    if (executeGitCommand("git", args)) {
        emit fileStatusChanged();
        return true;
    }
    
    return false;
}

bool GitManager::unstageAll()
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "reset" << "HEAD";
    
    if (executeGitCommand("git", args)) {
        emit fileStatusChanged();
        return true;
    }
    
    return false;
}

bool GitManager::commit(const QString &message)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "commit" << "-m" << message;
    
    if (executeGitCommand("git", args)) {
        emit fileStatusChanged();
        return true;
    }
    
    return false;
}

bool GitManager::createBranch(const QString &branchName)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "branch" << branchName;
    
    if (executeGitCommand("git", args)) {
        emit branchChanged();
        return true;
    }
    
    return false;
}

bool GitManager::switchBranch(const QString &branchName)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "checkout" << branchName;
    
    if (executeGitCommand("git", args)) {
        emit branchChanged();
        emit repositoryChanged();
        return true;
    }
    
    return false;
}

bool GitManager::deleteBranch(const QString &branchName)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "branch" << "-d" << branchName;
    
    if (executeGitCommand("git", args)) {
        emit branchChanged();
        return true;
    }
    
    return false;
}

bool GitManager::mergeBranch(const QString &branchName)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "merge" << branchName;
    
    if (executeGitCommand("git", args)) {
        emit repositoryChanged();
        return true;
    }
    
    return false;
}

bool GitManager::addRemote(const QString &name, const QString &url)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "remote" << "add" << name << url;
    
    return executeGitCommand("git", args);
}

bool GitManager::removeRemote(const QString &name)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "remote" << "remove" << name;
    
    return executeGitCommand("git", args);
}

bool GitManager::fetch(const QString &remote)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "fetch" << remote;
    
    if (executeGitCommand("git", args)) {
        emit repositoryChanged();
        return true;
    }
    
    return false;
}

bool GitManager::pull(const QString &remote, const QString &branch)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "pull" << remote;
    if (!branch.isEmpty()) {
        args << branch;
    }
    
    if (executeGitCommand("git", args)) {
        emit repositoryChanged();
        return true;
    }
    
    return false;
}

bool GitManager::push(const QString &remote, const QString &branch)
{
    if (!m_isRepositoryOpen) return false;
    
    QStringList args;
    args << "push" << remote;
    if (!branch.isEmpty()) {
        args << branch;
    }
    
    if (executeGitCommand("git", args)) {
        emit repositoryChanged();
        return true;
    }
    
    return false;
}

QString GitManager::getLastError() const
{
    return m_lastError;
}

bool GitManager::executeGitCommand(const QString &command, const QStringList &args, QString &output) const
{
    QProcess process;
    process.setWorkingDirectory(m_repositoryPath);
    process.start(command, args);
    
    if (!process.waitForFinished(30000)) {
        const_cast<GitManager*>(this)->m_lastError = "Command timeout: " + command + " " + args.join(" ");
        return false;
    }
    
    if (process.exitCode() != 0) {
        const_cast<GitManager*>(this)->m_lastError = process.readAllStandardError();
        return false;
    }
    
    output = process.readAllStandardOutput();
    return true;
}

bool GitManager::executeGitCommand(const QString &command, const QStringList &args) const
{
    QString output;
    return executeGitCommand(command, args, output);
}

QString GitManager::parseGitOutput(const QString &output) const
{
    return output.trimmed();
}