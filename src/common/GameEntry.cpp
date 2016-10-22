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

#include <QString>
#include <QIcon>

#include "GameEntry.h"
#include "GameType.h"

GameEntry::GameEntry(GameType gameType,
          const QString &prefix,
          const QString &name,
          const QString &icon,
          int defaultPort) :
    gameType(gameType),
    prefix(prefix),
    name(name),
    icon(icon),
    defaultPort(defaultPort)
{

}

GameEntry::GameEntry()
{

}

GameEntry::~GameEntry()
{

}

GameType GameEntry::getGameType()
{
    return gameType;
}

QString GameEntry::getPrefix()
{
    return prefix;
}

QString GameEntry::getName()
{
    return name;
}

QIcon GameEntry::getIcon()
{
    return QIcon(icon);
}

int GameEntry::getDefaultPort()
{
    return defaultPort;
}
