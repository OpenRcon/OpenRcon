#include "BF4GameMode.h"

BF4GameMode::BF4GameMode(const QString &engineName, const QString &name, const int &players, const int &commanders, const int &spectators, QObject *parent) : QObject(parent), engineName(engineName), name(name), players(players), commanders(commanders), spectators(spectators)
{

}

BF4GameMode::~BF4GameMode()
{

}

QString BF4GameMode::getEngineName()
{
    return engineName;
}

QString BF4GameMode::getName()
{
    return name;
}

int BF4GameMode::getPlayers()
{
    return players;
}

int BF4GameMode::getCommanders()
{
    return commanders;
}

int BF4GameMode::getSpectators()
{
    return spectators;
}
