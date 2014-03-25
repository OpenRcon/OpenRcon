#include "FrostbiteCommandHandler.h"

FrostbiteCommandHandler::FrostbiteCommandHandler(QObject *parent) : QObject(parent)
{

}

FrostbiteCommandHandler::~FrostbiteCommandHandler()
{

}

void FrostbiteCommandHandler::exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &playerList)
{
    qDebug() << "FrostbiteCommandHandler:exec()";
}
