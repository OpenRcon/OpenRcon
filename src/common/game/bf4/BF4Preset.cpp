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

#include <QString>
#include <QStringList>

#include "BF4Preset.h"

QStringList BF4Preset::list = {
    "Normal",
    "Classic",
    "Hardcore",
    "Infantry",
    "Custom"
};

BF4PresetEnum BF4Preset::fromString(const QString &presetName)
{
    BF4PresetEnum preset = BF4PresetEnum::Normal;

    if (presetName == "Normal") {
        preset = BF4PresetEnum::Normal;
    } else if (presetName == "Classic") {
        preset = BF4PresetEnum::Classic;
    } else if (presetName == "Hardcore") {
        preset = BF4PresetEnum::Hardcore;
    } else if (presetName == "Infantry") {
        preset = BF4PresetEnum::Infantry;
    } else if (presetName == "Custom") {
        preset = BF4PresetEnum::Custom;
    }

    return preset;
}

QString BF4Preset::toString(const BF4PresetEnum &preset)
{
    return list.at(static_cast<int>(preset));
}

int BF4Preset::toInt(const BF4PresetEnum &preset)
{
    return static_cast<int>(preset);
}

QStringList BF4Preset::asList()
{
    return list;
}
