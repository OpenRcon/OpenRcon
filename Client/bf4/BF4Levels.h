#ifndef BF4LEVELS_H
#define BF4LEVELS_H

#include <QObject>
#include <QMap>

#include "BF4GameMode.h"
#include "BF4Level.h"

class BF4Levels : public QObject
{
    Q_OBJECT

public:
    explicit BF4Levels(QObject *parent = 0);
    ~BF4Levels();

    BF4GameMode* getGameMode(const int &index);
    QList<BF4GameMode *> getGameModes();

    BF4Level* getLevel(BF4GameMode *gameMode, const int &index);
    BF4Level* getLevel(const int &gameModeIndex, const int &index);
    BF4Level* getLevel(BF4GameMode *gameMode, const QString &engineName);
    BF4Level* getLevel(const int &gameModeIndex, const QString &engineName);
    QList<BF4Level *> getLevels(BF4GameMode *gameMode);
    QList<BF4Level *> getLevels(const int &index);

private:
    QMap<BF4GameMode*, QList<BF4Level *> > levelMap;

};

#endif // BF4LEVELS_H
