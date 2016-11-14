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

#ifndef BF4PRESET_H
#define BF4PRESET_H

#include <QMetaType>

class QString;
class QStringList;

enum class BF4PresetEnum {
    Normal,
    Classic,
    Hardcore,
    Infantry,
    Custom
};

class BF4Preset
{
public:
    static BF4PresetEnum fromString(const QString &presetName);
    static QString toString(const BF4PresetEnum &preset);
    static BF4PresetEnum fromInt(int presetId);
    static int toInt(const BF4PresetEnum &preset);
    static QStringList asList();

private:
    static QStringList list;

};

// For use with QVariant
Q_DECLARE_METATYPE(BF4PresetEnum)

#endif // BF4PRESET_H
