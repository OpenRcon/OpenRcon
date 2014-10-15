#ifndef GAMEMODELEVEL_H
#define GAMEMODELEVEL_H

#include <QList>

class GameModeLevel
{
public:
    GameModeLevel(int gamemode, int level, QList<int> teamList);
    ~GameModeLevel();

    int getGamemode() const;
    int getLevel() const;
    QList<int> getTeamList() const;

private:
    int gamemode;
    int level;
    QList<int> teamList;

};

#endif // GAMEMODELEVEL_H
