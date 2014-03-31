#include "FrostbiteCommandHandler.h"

FrostbiteCommandHandler::FrostbiteCommandHandler(QObject *parent) : QObject(parent)
{

}

FrostbiteCommandHandler::~FrostbiteCommandHandler()
{

}

void FrostbiteCommandHandler::exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(command);
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);
}

/* These events is triggered everytime the client sends or receives data. */
void FrostbiteCommandHandler::eventOnDataSent(const QString &command)
{
    emit(onDataSent(command));
}

void FrostbiteCommandHandler::eventOnDataReceived(const QString &response)
{
    emit(onDataReceived(response));
}

void FrostbiteCommandHandler::commandUnknown()
{

}
