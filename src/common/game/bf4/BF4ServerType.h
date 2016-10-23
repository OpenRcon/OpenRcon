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

#ifndef SERVERTYPE_H
#define SERVERTYPE_H

class QString;
class QStringList;

enum class BF4ServerType {
    Official,
    Ranked,
    Unranked,
    Private
};

class BF4Server
{
public:
    static BF4ServerType fromString(const QString &server);
    static QString toString(const BF4ServerType &serverType);
    static int toInt(const BF4ServerType &serverType);
    static QStringList asList();

private:
    static QStringList list;

};

#endif // SERVERTYPE_H
