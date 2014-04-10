#include "ServerManager.h"

ServerManager::ServerManager(QObject *parent) : QObject(parent)
{
    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Load the stored servers.
    loadServers();
}

ServerManager::~ServerManager()
{
    saveServers();

    delete settings;
}

void ServerManager::loadServers()
{
    settings->beginGroup(SETTINGS_SERVERMANAGER);
        int size = settings->beginReadArray(SETTINGS_SERVERENTRIES);

        for (int i = 0; i < size; i++) {
            settings->setArrayIndex(i);

            ServerEntry entry = ServerEntry(
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
    settings->beginGroup(SETTINGS_SERVERMANAGER);
        settings->remove(SETTINGS_SERVERENTRIES);

        int size = serverList.size();
        settings->beginWriteArray(SETTINGS_SERVERENTRIES);
            for (int i = 0; i < size; i++) {
                settings->setArrayIndex(i);

                ServerEntry entry = serverList.at(i);
                settings->setValue("Game", entry.game);
                settings->setValue("Name", entry.name);
                settings->setValue("Host", entry.host);
                settings->setValue("Port", entry.port);
                settings->setValue("Password", entry.password);
            }
        settings->endArray();
    settings->endGroup();
}

ServerEntry ServerManager::getServer(const int &index)
{
    return serverList.at(index);
}

QList<ServerEntry> ServerManager::getServers()
{
    return serverList;
}

QList<ServerEntry> ServerManager::getServers(const int &game)
{
    QList<ServerEntry> list;

    foreach (ServerEntry entry, serverList) {
        if (entry.game == game) {
            list.append(entry);
        }
    }

    return list;
}

void ServerManager::addServer(ServerEntry &serverEntry)
{
    serverList.append(serverEntry);
}

void ServerManager::editServer(ServerEntry &serverEntry)
{
    int index = serverList.indexOf(serverEntry);
    serverList.removeAll(serverEntry);
}

void ServerManager::removeServer(const int &index)
{
    serverList.removeAt(index);
}

void ServerManager::removeServer(ServerEntry &serverEntry)
{
    removeServer(serverList.indexOf(serverEntry));
}
