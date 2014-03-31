#ifndef BF4GAMEMODE_H
#define BF4GAMEMODE_H

#include <QObject>

class BF4GameMode : public QObject
{
    Q_OBJECT

public:
    BF4GameMode(const QString &engineName, const QString &name, const int &players, const int &commanders, const int &spectators, QObject *parent = 0);
    ~BF4GameMode();

    QString getEngineName();
    QString getName();
    int getPlayers();
    int getCommanders();
    int getSpectators();

private:
    QString engineName;
    QString name;
    int players;
    int commanders;
    int spectators;

};

#endif // BF4GAMEMODE_H
