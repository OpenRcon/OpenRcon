#include "FrostbiteCommandHandler.h"

FrostbiteCommandHandler::FrostbiteCommandHandler(QObject *parent) : QObject(parent)
{

}

FrostbiteCommandHandler::~FrostbiteCommandHandler()
{

}

void FrostbiteCommandHandler::exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &playerList)
{
    Q_UNUSED(command);
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);
    Q_UNUSED(playerList);

    qDebug() << "FrostbiteCommandHandler:exec()";
}
