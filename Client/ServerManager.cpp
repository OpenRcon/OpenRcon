#include "ServerManager.h"

ServerManager::ServerManager(QObject *parent) : QObject(parent)
{
    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Load the stored servers.
    loadServers();

    emit (onServerUpdate());
}

ServerManager::~ServerManager()
{
    saveServers();

    delete settings;
}

void ServerManager::loadServers()
{
    settings->beginGroup("ServerManager");
        int size = settings->beginReadArray("Servers");

        for (int i = 0; i < size; i++) {
            settings->setArrayIndex(i);

            ServerEntry *entry = new ServerEntry(
                settings->value("Game").toInt(),
                settings->value("Name").toString(),
                settings->value("Host").toString(),
                settings->value("Port").toInt(),
                settings->value("Password").toString()
            );

            serverList.append(entry);
        }

        settings->endArray();
    settings->endGroup();
}

void ServerManager::saveServers()
{
    settings->beginGroup("ServerManager");
        settings->remove("Servers");

        int size = serverList.size();
        settings->beginWriteArray("Servers");
            for (int i = 0; i < size; i++) {
                settings->setArrayIndex(i);

                ServerEntry *entry = serverList.at(i);
                settings->setValue("Game", entry->game);
                settings->setValue("Name", entry->name);
                settings->setValue("Host", entry->host);
                settings->setValue("Port", entry->port);
                settings->setValue("Password", entry->password);
            }
        settings->endArray();
    settings->endGroup();
}

ServerEntry* ServerManager::getServer(const int &index)
{
    return serverList.at(index);
}

ServerEntry* ServerManager::getServer(ServerEntry *serverEntry)
{
    return getServer(serverList.indexOf(serverEntry));
}

void ServerManager::setServers(const QList<ServerEntry *> &list)
{
    serverList.clear();
    serverList = list;

    emit (onServerUpdate());
}

QList<ServerEntry *> ServerManager::getServers()
{
    return serverList;
}

QList<ServerEntry *> ServerManager::getServers(const int &gameIndex)
{
    QList<ServerEntry *> list;

    foreach (ServerEntry *entry, serverList) {
        if (entry->game == gameIndex) {
            list.append(entry);
        }
    }

    return list;
}

void ServerManager::addServer(ServerEntry *serverEntry)
{
    serverList.append(serverEntry);

    emit (onServerUpdate());
}

void ServerManager::removeServer(const int &index)
{
    serverList.removeAt(index);

    emit (onServerUpdate());
}

void ServerManager::removeServer(ServerEntry *serverEntry)
{
    removeServer(serverList.indexOf(serverEntry));
}
