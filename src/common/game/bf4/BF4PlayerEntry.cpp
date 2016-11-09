#include "BF4PlayerEntry.h"

BF4PlayerEntry::BF4PlayerEntry(const QString &name,
                               const QString &guid,
                               int teamId,
                               int squadId,
                               int kills,
                               int deaths,
                               int score,
                               int rank,
                               int ping,
                               int type) :
    Frostbite2PlayerEntry(name,
                          guid,
                          teamId,
                          squadId,
                          kills,
                          deaths,
                          score,
                          rank),
    ping(ping),
    type(type)
{

}

BF4PlayerEntry::~BF4PlayerEntry()
{

}

int BF4PlayerEntry::getPing() const
{
    return ping;
}

int BF4PlayerEntry::getType() const
{
    return type;
}
