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
template<class T>
class QList;
class QStringList;

enum class BF4ServerTypeEnum {
    Official,
    Ranked,
    Unranked,
    Private,
    Unknown
};

class BF4ServerType
{
public:
    static BF4ServerTypeEnum fromString(const QString &serverTypeName);
    static QString toString(const BF4ServerTypeEnum &serverType);
    static BF4ServerTypeEnum fromInt(int serverTypeId);
    static int toInt(const BF4ServerTypeEnum &serverType);
    static QList<BF4ServerTypeEnum> asList();
    static QStringList asStringList();

private:
    static QList<BF4ServerTypeEnum> list;
    static QStringList stringList;

};

#endif // SERVERTYPE_H
