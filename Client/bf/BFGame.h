#ifndef BFGAME_H
#define BFGAME_H

#include "Game.h"

class BFGame : public Game
{

public:
    explicit BFGame(const QString &host, const int &port, const QString &password);
    ~BFGame();

protected:
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

    QString getSquadName(const int &squadId);
};

#endif // BFGAME_H
