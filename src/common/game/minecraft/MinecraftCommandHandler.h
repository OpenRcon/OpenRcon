/*
 * Copyright (C) 2016 The OpenRcon Project.
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

#include "CommandHandler.h"

class MinecraftConnection;
class MinecraftRconPacket;

class MinecraftCommandHandler : public CommandHandler
{
    Q_OBJECT

public:
    MinecraftCommandHandler(QObject *parent = nullptr);
    ~MinecraftCommandHandler() final;

    void setConnection(MinecraftConnection *connection);

    bool parse(const MinecraftRconPacket &packet);

protected:
    MinecraftConnection *connection;

private:
    void parseListCommand(MinecraftRconPacket &packet);

signals:
    void onListCommand(const QStringList &list);

};

#endif // MINECRAFTCOMMANDHANDLER_H
