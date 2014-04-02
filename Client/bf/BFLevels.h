#ifndef BFLEVELS_H
#define BFLEVELS_H

#include <QDebug>
#include <QHash>

#include "LevelEntry.h"
#include "GameModeEntry.h"

class BFLevels : public QObject
{
    Q_OBJECT

public:
    explicit BFLevels(QObject *parent = 0);
    ~BFLevels();

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

#endif // BFLEVELS_H
