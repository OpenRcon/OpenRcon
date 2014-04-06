#include "BFBaseCommandHandler.h"

BFBaseCommandHandler::BFBaseCommandHandler(QObject *parent) : FrostbiteCommandHandler(parent)
{

}

BFBaseCommandHandler::~BFBaseCommandHandler()
{

}

void BFBaseCommandHandler::exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(command);
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);

    // TODO: Commands that are common in Battlefield games should be terminated here.
}
