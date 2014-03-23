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

#ifndef MINECRAFT_H
#define MINECRAFT_H

#include <QObject>

#include "Constants.h"
#include "Game.h"

#include "MinecraftWidget.h"
#include "MinecraftConnection.h"

using namespace Constants;

class Minecraft : public Game
{
    Q_OBJECT

public:
    explicit Minecraft(const QString &host, const int &port, const QString &password);
    ~Minecraft();

    virtual Connection *getConnection() { return con; }

    MinecraftConnection *con;

private:
    MinecraftWidget *widget;

private slots:
    void authenticate();

    void slotAuthenticated(bool auth);
    void slotPacket(const QString &packet);
};

#endif // MINECRAFT_H
