#ifndef GAMEMODEENTRY_H
#define GAMEMODEENTRY_H

#include <QString>

struct GameModeEntry {
    GameModeEntry() {

    }

    GameModeEntry(QString engineName, QString name, int players, int commanders, int spectators) : engineName(engineName), name(name), players(players), commanders(commanders), spectators(spectators)
    {

    }

    QString engineName;
    QString name;
    int players;
    int commanders;
    int spectators;
};

#endif // GAMEMODEENTRY_H
