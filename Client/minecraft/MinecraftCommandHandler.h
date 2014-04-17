/*
 * Copyright (C) 2014 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MINECRAFTCOMMANDHANDLER_H
#define MINECRAFTCOMMANDHANDLER_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "MinecraftRconPacket.h"

class MinecraftCommandHandler : public QObject
{
    Q_OBJECT

public:
    explicit MinecraftCommandHandler(QObject *parent = 0);
    ~MinecraftCommandHandler();

    void exec(MinecraftRconPacket &packet);
    void eventOnDataSent(const QString &command);
    void eventOnDataReceived(const QString &response);
    int getRequestIdForCommand(const QString &command);

private:
    void helpCommand(MinecraftRconPacket &packet);
    void listCommand(MinecraftRconPacket &packet);
    void unknownCommand(MinecraftRconPacket &packet);

signals:
    void onDataSent(const QString &command);
    void onDataReceived(const QString &response);

    void onHelpCommand(const QString &packet);
    void onListCommand(const QStringList &packet);
    void onUnknownCommand();

};

#endif // MINECRAFTCOMMANDHANDLER_H
