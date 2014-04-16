#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QSettings>

#include "Constants.h"
#include "ServerEntry.h"

using namespace Constants;

class ServerManager : public QObject
{
    Q_OBJECT

public:
    explicit ServerManager(QObject *parent);
    ~ServerManager();

    ServerEntry* getServer(const int &index);
    ServerEntry* getServer(ServerEntry *serverEntry);
    void setServers(const QList<ServerEntry *> &list);

    QList<ServerEntry *> getServers();
    QList<ServerEntry *> getServers(const int &gameIndex);

    void addServer(ServerEntry *serverEntry);
    void editServer(ServerEntry *serverEntry);
    void removeServer(const int &index);
    void removeServer(ServerEntry *serverEntry);

private:
    QSettings *settings;
    QList<ServerEntry *> serverList;

    void loadServers();
    void saveServers();

};

#endif // SERVERMANAGER_H
