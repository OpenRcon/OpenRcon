/*
 * Copyright (C) 2014 The OpenRcon Project.
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

#include "BF4Preset.h"

QStringList BF4Preset::list = {
    "Normal",
    "Classic",
    "Hardcore",
    "Infantry",
    "Custom"
};

BF4PresetType BF4Preset::fromString(const QString &preset)
{
    BF4PresetType presetType;

    if (preset == "Normal") {
        presetType = BF4PresetType::Normal;
    } else if (preset == "Classic") {
        presetType = BF4PresetType::Classic;
    } else if (preset == "Hardcore") {
        presetType = BF4PresetType::Hardcore;
    } else if (preset == "Infantry") {
        presetType = BF4PresetType::Infantry;
    } else if (preset == "Custom") {
        presetType = BF4PresetType::Custom;
    }

    return presetType;
}

QString BF4Preset::toString(const BF4PresetType &presetType)
{
    return list.at(static_cast<int>(presetType));
}

int BF4Preset::toInt(const BF4PresetType &presetType)
{
    return static_cast<int>(presetType);
}

QStringList BF4Preset::asList()
{
    return list;
}
