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

#ifndef FROSTBITE2UNLOCKMODE_H
#define FROSTBITE2UNLOCKMODE_H

#include <QMetaType>

class QString;
class QStringList;

enum class Frostbite2UnlockModeEnum {
    All,
    Common,
    Stats,
    None
};

class Frostbite2UnlockMode
{
public:
    static Frostbite2UnlockModeEnum fromString(const QString &unlockModeName);
    static QString toString(const Frostbite2UnlockModeEnum &unlockMode);
    static QString toString(int unlockModeId);
    static Frostbite2UnlockModeEnum fromInt(int unlockModeId);
    static int toInt(const Frostbite2UnlockModeEnum &unlockMode);
    static QStringList asList();

private:
    static QStringList list;

};

// For use with QVariant
Q_DECLARE_METATYPE(Frostbite2UnlockModeEnum)

#endif // FROSTBITE2UNLOCKMODE_H
