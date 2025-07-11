#ifndef REMOTEMANAGER_H
#define REMOTEMANAGER_H

#include <QObject>

class GitManager;

class RemoteManager : public QObject
{
    Q_OBJECT

public:
    explicit RemoteManager(GitManager *gitManager, QObject *parent = nullptr);

private:
    GitManager *m_gitManager;
};

#endif // REMOTEMANAGER_H