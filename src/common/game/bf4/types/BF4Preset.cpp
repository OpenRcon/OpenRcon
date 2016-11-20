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

#include "BF4Preset.h"

#include "FrostbiteUtils.h"

QList<BF4PresetEnum> BF4Preset::list = {
    BF4PresetEnum::Normal,
    BF4PresetEnum::Hardcore,
    BF4PresetEnum::Infantry,
    BF4PresetEnum::Noob,
    BF4PresetEnum::Classic,
    BF4PresetEnum::Custom
};

QStringList BF4Preset::stringList = {
    "Normal",
    "Hardcore",
    "Infantry",
    "Noob",
    "Classic",
    "Custom"
};

BF4PresetEnum BF4Preset::fromString(const QString &presetName)
{
    QString presetNameCamelCase = FrostbiteUtils::toCamelCase(presetName);
    BF4PresetEnum preset = BF4PresetEnum::Custom;

    if (presetNameCamelCase == "Normal") {
        preset = BF4PresetEnum::Normal;
    } else if (presetNameCamelCase == "Hardcore") {
        preset = BF4PresetEnum::Hardcore;
    } else if (presetNameCamelCase == "Infantry") {
        preset = BF4PresetEnum::Infantry;
    } else if (presetNameCamelCase == "Noob") {
        preset = BF4PresetEnum::Noob;
    } else if (presetNameCamelCase == "Classic") {
        preset = BF4PresetEnum::Classic;
    }

    return preset;
}

QString BF4Preset::toString(const BF4PresetEnum &preset)
{
    return stringList.at(toInt(preset));
}

BF4PresetEnum BF4Preset::fromInt(int presetId)
{
    return static_cast<BF4PresetEnum>(presetId);
}

int BF4Preset::toInt(const BF4PresetEnum &preset)
{
    return static_cast<int>(preset);
}

QList<BF4PresetEnum> BF4Preset::asList()
{
    return list;
}

QStringList BF4Preset::asStringList()
{
    return stringList;
}
