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

#ifndef GAMETYPE_H
#define GAMETYPE_H

#include <QMetaType>

class QString;
class QStringList;

enum class GameType {
    BFBC2,
    BF3,
    BF4,
    Unsupported
};

class GameTypeUtils
{
public:
    static GameType fromString(const QString &game);
    static QString toString(const GameType &gameType);
    static int toInt(const GameType &gameType);
    static QStringList asList();

private:
    static QStringList list;

};

// For use with QVariant
Q_DECLARE_METATYPE(GameType)

#endif // GAMETYPE_H
