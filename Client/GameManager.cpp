#include "GameManager.h"

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    // Adds all games to the list.
    gameList.append(GameEntry(0, "Battlefield: Bad Company 2", ":/bfbc2/icons/bfbc2.png"));
    gameList.append(GameEntry(1, "Battlefield 4", ":/bf4/icons/bf4.png"));
    gameList.append(GameEntry(2, "Minecraft", ":/minecraft/icons/minecraft.png"));
}

GameManager::~GameManager()
{

}

GameEntry GameManager::getGame(const int &index)
{
    return gameList.at(index);
}

QList<GameEntry> GameManager::getGames()
{
    return gameList;
}
