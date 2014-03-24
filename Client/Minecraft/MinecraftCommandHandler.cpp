#include "MinecraftCommandHandler.h"

MinecraftCommandHandler::MinecraftCommandHandler(QObject *parent) : QObject(parent)
{

}

MinecraftCommandHandler::~MinecraftCommandHandler()
{

}

void MinecraftCommandHandler::exec(const int &command, const QString &packet)
{
    switch (command) {
        case 2:
            helpCommand(packet);
            break;

        case 3:
            listCommand(packet);
            break;

        default:
            unknownCommand(packet);
    }
}

int MinecraftCommandHandler::getRequestIdForCommand(const QString &command)
{
    if (command == "help") {
        return 2;
    } else if (command == "list") {
        return 3;
    }

    return 0;
}

void MinecraftCommandHandler::helpCommand(const QString &packet)
{
//    emit (onHelpCommand(packet));
}

void MinecraftCommandHandler::listCommand(const QString &packet)
{
    QStringList playerList = packet.split(" ");

    emit (onListCommand(playerList));
}

void MinecraftCommandHandler::unknownCommand(const QString &packet)
{
    emit (onUnknownCommand());
}
