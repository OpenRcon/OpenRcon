#include "BFLevels.h"

BFLevels::BFLevels(QObject *parent) : QObject(parent)
{

}

BFLevels::~BFLevels()
{

}

LevelEntry BFLevels::getLevel(const int &index)
{
    return levelList.at(index);
}

LevelEntry BFLevels::getLevel(const QString &name)
{
    foreach (LevelEntry entry, levelList) {
        if (entry.engineName == name || entry.name == name) {
            return entry;
        }
    }

    return LevelEntry();
}

GameModeEntry BFLevels::getGameMode(const int &index)
{
    return gameModeList.at(index);
}

GameModeEntry BFLevels::getGameMode(const QString &name)
{
    foreach (GameModeEntry entry, gameModeList) {
        if (entry.engineName == name || entry.name == name) {
            return entry;
        }
    }

    return GameModeEntry("lol", "lol", 2, 2, 2);
}

QList<LevelEntry> BFLevels::getLevels()
{
    return levelList;
}

QList<LevelEntry> BFLevels::getLevels(const int &gameModeIndex)
{
    QList<LevelEntry> list;

    foreach (int index, levelMap.values(gameModeIndex)) {
        list.append(levelList.at(index));
    }

    return list;
}

QList<GameModeEntry> BFLevels::getGameModes()
{
    return gameModeList;
}

QStringList BFLevels::getLevelNames()
{
    QStringList list;

    foreach (LevelEntry entry, levelList) {
        list.append(entry.name);
    }

    return list;
}

QStringList BFLevels::getGameModeNames()
{
    QStringList list;

    foreach (GameModeEntry entry, gameModeList) {
        list.append(entry.name);
    }

    return list;
}
