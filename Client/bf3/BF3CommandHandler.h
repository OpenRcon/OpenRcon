#ifndef BF3COMMANDHANDLER_H
#define BF3COMMANDHANDLER_H

#include "FrostbiteCommandHandler.h"

class BF3CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    explicit BF3CommandHandler(QObject *parent = 0);
    ~BF3CommandHandler();

    void exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

};

#endif // BF3COMMANDHANDLER_H
