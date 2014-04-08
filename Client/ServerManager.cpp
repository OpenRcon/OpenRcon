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
                settings->value(SETTINGS_SERVERENTRY_GAME).toInt(),
                settings->value(SETTINGS_SERVERENTRY_NAME).toString(),
                settings->value(SETTINGS_SERVERENTRY_HOST).toString(),
                settings->value(SETTINGS_SERVERENTRY_PORT).toInt(),
                settings->value(SETTINGS_SERVERENTRY_PASSWORD).toString()
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
        const int size = serverList.size();
        settings->beginWriteArray(SETTINGS_SERVERENTRIES);
            for (int i = 0; i < size; i++) {
                settings->setArrayIndex(i);
                    settings->setValue(SETTINGS_SERVERENTRY_GAME, serverList.at(i).game);
                    settings->setValue(SETTINGS_SERVERENTRY_NAME, serverList.at(i).name);
                    settings->setValue(SETTINGS_SERVERENTRY_HOST, serverList.at(i).host);
                    settings->setValue(SETTINGS_SERVERENTRY_PORT, serverList.at(i).port);
                    settings->setValue(SETTINGS_SERVERENTRY_PASSWORD, serverList.at(i).password);
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

void ServerManager::addServer(const ServerEntry &serverEntry)
{
    serverList.append(serverEntry);
}

void ServerManager::removeServer(const int &index)
{
    serverList.removeAt(index);
}

void ServerManager::removeServer(const ServerEntry &serverEntry)
{
    removeServer(serverList.indexOf(serverEntry));
}

void ServerManager::connectToServer(const int &index)
{
    ServerEntry entry = getServer(index);
//    OpenRcon *openRcon = OpenRcon::getInstance();
//    openRcon->newTab(entry.game, entry.name, entry.host, entry.port, entry.password);
}

void ServerManager::connectToServer(const ServerEntry &serverEntry)
{
    connectToServer(serverList.indexOf(serverEntry));
}
