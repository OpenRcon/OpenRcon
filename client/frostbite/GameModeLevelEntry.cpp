#include "GameModeLevelEntry.h"

GameModeLevelEntry::GameModeLevelEntry(int gamemode, int level, QList<int> teamList) : gamemode(gamemode), level(level), teamList(teamList)
{

}

GameModeLevelEntry::~GameModeLevelEntry()
{

}

int GameModeLevelEntry::getGamemode()
{
    return gamemode;
}

int GameModeLevelEntry::getLevel()
{
    return level;
}

QList<int> GameModeLevelEntry::getTeamList()
{
    return teamList;
}
