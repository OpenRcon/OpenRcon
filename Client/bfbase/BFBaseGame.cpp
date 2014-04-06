#include "BFBaseGame.h"

BFBaseGame::BFBaseGame(const QString &host, const int &port, const QString &password) : Game(host, port, password)
{

}

BFBaseGame::~BFBaseGame()
{

}

QString BFBaseGame::getPlayerSubsetName(const int &playerSubset)
{
    QString playerSubsetName;

    switch (playerSubset) {
        case All:
            playerSubsetName = "All";
            break;

        case Team:
            playerSubsetName = "Team";
            break;

        case Squad:
            playerSubsetName = "Squad";
            break;

        case Player:
            playerSubsetName = "Player";
            break;
    }

    return playerSubsetName;
}

QString BFBaseGame::getSquadName(const int &squadId)
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
