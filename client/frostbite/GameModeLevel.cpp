#include "GameModeLevel.h"

GameModeLevel::GameModeLevel(int gamemode, int level, QList<int> teamList) : gamemode(gamemode), level(level), teamList(teamList)
{

}

GameModeLevel::~GameModeLevel()
{

}

int GameModeLevel::getGamemode() const
{
    return gamemode;
}

int GameModeLevel::getLevel() const
{
    return level;
}

QList<int> GameModeLevel::getTeamList() const
{
    return teamList;
}
