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

    // TODO: Why is this crashing?
    virtual void exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &playerList);

protected:
    //void commandUnknown(const FrostbiteRconPacket &packet);

};

#endif // FROSTBITECOMMANDHANDLER_H
