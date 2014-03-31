#include "BF4GameMode.h"

BF4GameMode::BF4GameMode(const QString &engineName, const QString &name, const int &playerCount, const int &commanderCount, const int &spectatorCount, QObject *parent) : QObject(parent), engineName(engineName), name(name), playerCount(playerCount), commanderCount(commanderCount), spectatorCount(spectatorCount)
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

int BF4GameMode::getPlayerCount()
{
    return playerCount;
}

int BF4GameMode::getCommanderCount()
{
    return commanderCount;
}

int BF4GameMode::getSpectatorCount()
{
    return spectatorCount;
}
