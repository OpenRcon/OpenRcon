#ifndef BF4PLAYERENTRY_H
#define BF4PLAYERENTRY_H

#include "Frostbite2PlayerEntry.h"

class BF4PlayerEntry : public Frostbite2PlayerEntry
{
public:
    BF4PlayerEntry(const QString &name,
                   const QString &guid,
                   int teamId,
                   int squadId,
                   int kills,
                   int deaths,
                   int score,
                   int rank,
                   int ping,
                   int type);
    ~BF4PlayerEntry();

    int getPing() const;
    int getType() const;

private:
    int ping;
    int type;

};

#endif // BF4PLAYERENTRY_H
