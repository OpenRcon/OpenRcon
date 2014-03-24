#ifndef FROSTBITECOMMANDHANDLER_H
#define FROSTBITECOMMANDHANDLER_H

#include "FrostbiteRconPacket.h"

typedef QMap<QString, QString> PlayerListItem;
typedef QVector<PlayerListItem> PlayerList;

class FrostbiteCommandHandler : public QObject
{
    Q_OBJECT

public:
    explicit FrostbiteCommandHandler(QObject *parent = 0);
    ~FrostbiteCommandHandler();

    virtual void exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &playerList) = 0;

};

#endif // FROSTBITECOMMANDHANDLER_H
