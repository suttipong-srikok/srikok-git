#include "remotemanager.h"
#include "gitmanager.h"

RemoteManager::RemoteManager(GitManager *gitManager, QObject *parent)
    : QObject(parent)
    , m_gitManager(gitManager)
{
}