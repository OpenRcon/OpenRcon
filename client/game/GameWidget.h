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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GAME_H
#define GAME_H

#include <QWidget>

class ServerEntry;
class Connection;

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(ServerEntry *serverEntry, QWidget *parent = nullptr);
    ~GameWidget();

    ServerEntry *getServerEntry();
    virtual Connection *getConnection() = 0;

protected:
    ServerEntry *serverEntry;

};

#endif // GAME_H
