/*
 * Copyright (C) 2010 The OpenRcon Project.
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

#include "Minecraft.h"

Minecraft::Minecraft(const QString &host, const int &port, const QString &password) : Game(host, port, password)
{
    widget = new MinecraftWidget(this);
    con = new MinecraftConnection(this);
    con->hostConnect(host, port);

    connect(con->tcpSocket, SIGNAL(connected()), this, SLOT(authenticate()));

    connect(con, SIGNAL(signalAuthenticated(bool)), this, SLOT(slotAuthenticated(bool)));
    connect(con, SIGNAL(signalPacket(QString)), this, SLOT(slotPacket(QString)));
}

Minecraft::~Minecraft()
{

}

void Minecraft::authenticate()
{
    con->sendPacket(3, password.toLatin1());
}

void Minecraft::slotAuthenticated(bool auth)
{
    if (auth) {
        widget->logMessage(0, "Successfully logged in!");
    } else {
        widget->logMessage(1, "Login failed!");
    }

    con->sendCommand("help 2");
}

void Minecraft::slotPacket(const QString &packet)
{
    widget->logMessage(2, packet);
}
