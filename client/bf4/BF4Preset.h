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

#ifndef BF4PRESET_H
#define BF4PRESET_H

#include <QString>
#include <QStringList>

enum class BF4PresetType {
    Normal,
    Classic,
    Hardcore,
    Infantry,
    Custom
};

class BF4Preset
{
public:
    static BF4PresetType fromString(const QString &preset);
    static QString toString(const BF4PresetType &presetType);
    static int toInt(const BF4PresetType &presetType);
    static QStringList getList();

private:
    static QStringList list;

};

#endif // BF4PRESET_H
