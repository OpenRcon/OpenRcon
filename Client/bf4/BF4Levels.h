#ifndef BF4LEVELS_H
#define BF4LEVELS_H

#include <QDebug>
#include <QHash>

#include "LevelEntry.h"
#include "GameModeEntry.h"

class BF4Levels : public QObject
{
    Q_OBJECT

public:
    explicit BF4Levels(QObject *parent = 0);
    ~BF4Levels();

    LevelEntry getLevel(const int &index);
    LevelEntry getLevel(const QString &name);
    GameModeEntry getGameMode(const int &index);
    GameModeEntry getGameMode(const QString &name);

    QList<LevelEntry> getLevels();
    QList<LevelEntry> getLevels(const int &gameModeIndex);
    QList<GameModeEntry> getGameModes();

    QStringList getLevelNames();
    QStringList getGameModeNames();

private:
    QList<LevelEntry> levelList;
    QList<GameModeEntry> gameModeList;
    QHash<int, int> levelMap;

};

#endif // BF4LEVELS_H
