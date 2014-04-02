/*
 * Copyright (C) 2011 The OpenRcon Project.
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

#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
    con = new Connection(this);
}

ConnectionManager::~ConnectionManager()
{
    delete con;
}

void ConnectionManager::openConnection()
{
/*  Game *game;
    GameEntry *entry = gameList.at(game);

    if (game == 0) {
        game = new BFBC2Widget(host, port, password);
    } else if (game == 1) {
        game = new BF4Widget(host, port, password);
    } else if (game == 2) {
        game = new MinecraftWidget(host, port, password);
    }

    ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(game, entry->getIcon(), QString("%1 [%2]").arg(name).arg(entry->getName())));
*/
}

void ConnectionManager::closeConnection()
{

}
