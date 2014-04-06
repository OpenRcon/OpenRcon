#ifndef BFBASEGAME_H
#define BFBASEGAME_H

#include "Game.h"

class BFBaseGame : public Game
{

public:
    explicit BFBaseGame(const QString &host, const int &port, const QString &password);
    ~BFBaseGame();

protected:
    QStringList commandList;

    enum PlayerSubset {
        All,
        Team,
        Squad,
        Player
    };

    enum Squad {
        Alpha,
        Bravo,
        Charlie,
        Delta,
        Echo,
        Foxtrot,
        Golf,
        Hotel
    };

    QString getPlayerSubsetName(const int &playerSubset);
    QString getSquadName(const int &squadId);

};

#endif // BFBASEGAME_H
