#ifndef BF4GAMEMODE_H
#define BF4GAMEMODE_H

#include <QObject>

class BF4GameMode : public QObject
{
    Q_OBJECT

public:
    BF4GameMode(const QString &engineName, const QString &name, const int &playerCount, const int &commanderCount, const int &spectatorCount, QObject *parent = 0);
    ~BF4GameMode();

    QString getEngineName();
    QString getName();
    int getPlayerCount();
    int getCommanderCount();
    int getSpectatorCount();

private:
    QString engineName;
    QString name;
    int playerCount;
    int commanderCount;
    int spectatorCount;

};

#endif // BF4GAMEMODE_H
