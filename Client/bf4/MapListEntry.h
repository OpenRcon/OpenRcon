#ifndef MAPLISTENTRY_H
#define MAPLISTENTRY_H

#include <QString>

struct MapListEntry {
    MapListEntry(const QString &level, const QString &gameMode, const int &rounds) : level(level), gameMode(gameMode), rounds(rounds)
    {

    }

    QString level;
    QString gameMode;
    int rounds;
};

#endif // MAPLISTENTRY_H
