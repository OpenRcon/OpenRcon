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

#include <QString>
#include <QStringList>

#include "BFBC2Mod.h"
#include "FrostbiteUtils.h"

QList<BFBC2ModEnum> BFBC2Mod::list = {
    BFBC2ModEnum::BC2,
    BFBC2ModEnum::VIETNAM
};

QStringList BFBC2Mod::stringList = {
    "BC2",
    "VIETNAM"
};

BFBC2ModEnum BFBC2Mod::fromString(const QString &modName)
{
    QString modNameUpperCase = modName.toUpper();
    BFBC2ModEnum mod = BFBC2ModEnum::BC2;

    if (modNameUpperCase == "VIETNAM") {
        mod = BFBC2ModEnum::VIETNAM;
    }

    return mod;
}

QString BFBC2Mod::toString(const BFBC2ModEnum &mod)
{
    return toString(toInt(mod));
}

QString BFBC2Mod::toString(int modId)
{
    return stringList.at(modId);
}

BFBC2ModEnum BFBC2Mod::fromInt(int modId)
{
    return static_cast<BFBC2ModEnum>(modId);
}

int BFBC2Mod::toInt(const BFBC2ModEnum &mod)
{
    return static_cast<int>(mod);
}

QList<BFBC2ModEnum> BFBC2Mod::asList()
{
    return list;
}

QStringList BFBC2Mod::asStringList()
{
    return stringList;
}
