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

#ifndef FROSTBITEUTILS_H
#define FROSTBITEUTILS_H

#include <QObject>

class QString;
class QStringList;
class QIcon;

class Time;
enum class GameTypeEnum;
enum class SquadEnum;

class FrostbiteUtils : public QObject
{
    Q_OBJECT

public:
    static int toInt(const QString &value);
    static float toFloat(const QString &value);
    static bool toBool(const QString &value);
    static QString toString(bool value);
    static QString toString(const Time &time);
    static QString toCamelCase(const QString &value);

    static Time getTimeFromSeconds(int elapsedSeconds);

    static QIcon getRankIcon(GameTypeEnum gameType, int rank);
    static QString getSquadName(const SquadEnum &squad);
    static QString getSquadName(int squadId);

private:
    static QStringList squads;

};

#endif // FROSTBITEUTILS_H
