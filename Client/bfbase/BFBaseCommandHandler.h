#ifndef BFBASECOMMANDHANDLER_H
#define BFBASECOMMANDHANDLER_H

#include "FrostbiteCommandHandler.h"

class BFBaseCommandHandler : public FrostbiteCommandHandler
{

public:
    explicit BFBaseCommandHandler(QObject *parent = 0);
    ~BFBaseCommandHandler();

    void exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

};

#endif // BFBASECOMMANDHANDLER_H
