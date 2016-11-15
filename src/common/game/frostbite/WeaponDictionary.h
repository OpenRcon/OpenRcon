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

#ifndef WEAPONDICTIONARY_H
#define WEAPONDICTIONARY_H

class QString;
template<class T>
class QList;

enum class GameTypeEnum;
class WeaponEntry;

template<GameTypeEnum gameType, class WeaponEntryType>
class WeaponDictionary
{
public:
    WeaponDictionary() {
        static_assert(std::is_base_of<WeaponEntry, WeaponEntryType>::value, "WeaponEntryType must be a subclass of WeaponEntry.");
    }

    ~WeaponDictionary();

    static WeaponEntryType getWeapon(const QString &weaponName) {
        static WeaponEntryType empty;

        for (WeaponEntryType weaponEntry : weaponList) {
            if (weaponName == weaponEntry.getName()) {
                return weaponEntry;
            }
        }

        return empty;
    }

    static QList<WeaponEntryType> getWeapons() {
        return weaponList;
    }

private:
    static QList<WeaponEntryType> weaponList;

};

#endif // WEAPONDICTIONARY_H
