#include "BFGame.h"

BFGame::BFGame(const QString &host, const int &port, const QString &password) : Game(host, port, password)
{

}

BFGame::~BFGame()
{

}

QString BFGame::getSquadName(const int &squadId)
{
    QString squadName;

    switch (squadId) {
        case Alpha:
            squadName = "Alpha";
            break;

        case Bravo:
            squadName = "Bravo";
            break;

        case Charlie:
            squadName = "Charlie";
            break;

        case Delta:
            squadName = "Delta";
            break;

        case Echo:
            squadName = "Echo";
            break;

        case Foxtrot:
            squadName = "Foxtrot";
            break;

        case Golf:
            squadName = "Golf";
        break;

        case Hotel:
            squadName = "Hotel";
            break;

    }

    return squadName;
}
