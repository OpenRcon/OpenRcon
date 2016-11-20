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
#include <QList>
#include <QStringList>

#include "Frostbite2UnlockMode.h"
#include "FrostbiteUtils.h"

QList<Frostbite2UnlockModeEnum> Frostbite2UnlockMode::list = {
    Frostbite2UnlockModeEnum::All,
    Frostbite2UnlockModeEnum::Common,
    Frostbite2UnlockModeEnum::Stats,
    Frostbite2UnlockModeEnum::None
};

QStringList Frostbite2UnlockMode::stringList = {
    "All",
    "Common",
    "Stats",
    "None"
};

Frostbite2UnlockModeEnum Frostbite2UnlockMode::fromString(const QString &unlockModeName)
{
    QString unlockModeNameCamelCase = FrostbiteUtils::toCamelCase(unlockModeName);
    Frostbite2UnlockModeEnum unlockMode = Frostbite2UnlockModeEnum::None;

    if (unlockModeNameCamelCase == "All") {
        unlockMode = Frostbite2UnlockModeEnum::All;
    } else if (unlockModeNameCamelCase == "Common") {
        unlockMode = Frostbite2UnlockModeEnum::Common;
    } else if (unlockModeNameCamelCase == "Stats") {
        unlockMode = Frostbite2UnlockModeEnum::Stats;
    }

    return unlockMode;
}

QString Frostbite2UnlockMode::toString(const Frostbite2UnlockModeEnum &unlockMode)
{
    return toString(toInt(unlockMode));
}

QString Frostbite2UnlockMode::toString(int unlockModeId)
{
    return stringList.at(unlockModeId);
}

Frostbite2UnlockModeEnum Frostbite2UnlockMode::fromInt(int unlockModeId)
{
    return static_cast<Frostbite2UnlockModeEnum>(unlockModeId);
}

int Frostbite2UnlockMode::toInt(const Frostbite2UnlockModeEnum &unlockMode)
{
    return static_cast<int>(unlockMode);
}

QList<Frostbite2UnlockModeEnum> Frostbite2UnlockMode::asList()
{
    return list;
}

QStringList Frostbite2UnlockMode::asStringList()
{
    return stringList;
}
