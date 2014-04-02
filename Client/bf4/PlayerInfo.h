#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QString>

struct PlayerInfo {
    PlayerInfo(const QString &name,
               const QString &guid,
               const int &teamId,
               const int &squadId,
               const int &kills,
               const int &deaths,
               const int &score,
               const int &rank,
               const int &ping) :
               name(name),
               guid(guid),
               teamId(teamId),
               squadId(squadId),
               kills(kills),
               deaths(deaths),
               score(score),
               rank(rank),
               ping(ping)
    {

    }

    QString name;
    QString guid;
    int teamId;
    int squadId;
    int kills;
    int deaths;
    int score;
    int rank;
    int ping;

}

#endif // PLAYERINFO_H
