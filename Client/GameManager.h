#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameEntry.h"

#include "BFBC2Widget.h"
#include "BF4Widget.h"
#include "MinecraftWidget.h"

class GameManager : public QObject
{
    Q_OBJECT

public:
    explicit GameManager(QObject *parent = 0);
    ~GameManager();

    GameEntry getGame(const int &index);
    QList<GameEntry> getGames();

private:
    QList<GameEntry> gameList;

};

#endif // GAMEMANAGER_H
