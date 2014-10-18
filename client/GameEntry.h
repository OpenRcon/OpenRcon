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

#ifndef GAMEENTRY_H
#define GAMEENTRY_H

#include "GameType.h"

class QString;
class QIcon;

class GameEntry
{
public:
    GameEntry(GameType gameType,
              const QString &prefix,
              const QString &name,
              const QString &icon,
              int defaultPort);
    GameEntry();
    ~GameEntry();

    GameType getGameType();
    QString getPrefix();
    QString getName();
    QIcon getIcon();
    int getDefaultPort();

private:
    GameType gameType;
    QString prefix;
    QString name;
    QString icon;
    int defaultPort;

};

#endif // GAMEENTRY_H
