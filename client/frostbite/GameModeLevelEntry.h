#ifndef GAMEMODELEVELENTRY_H
#define GAMEMODELEVELENTRY_H

#include <QList>

class GameModeLevelEntry
{
public:
    GameModeLevelEntry(int gamemode, int level, QList<int> teamList);
    ~GameModeLevelEntry();

    int getGamemode();
    int getLevel();
    QList<int> getTeamList();

private:
    int gamemode;
    int level;
    QList<int> teamList;

};

#endif // GAMEMODELEVELENTRY_H
