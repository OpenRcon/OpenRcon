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

#include "WeaponEntry.h"

WeaponEntry::WeaponEntry()
{

}

WeaponEntry::WeaponEntry(const QString &className, const QString &name, const QString &priority, const QString &type) :
    className(className),
    name(name),
    priority(priority),
    type(type)
{

}

WeaponEntry::~WeaponEntry()
{

}

QString WeaponEntry::getClassName() const
{
    return className;
}

QString WeaponEntry::getName() const
{
    return name;
}

QString WeaponEntry::getPriority() const
{
    return priority;
}

QString WeaponEntry::getType() const
{
    return type;
}
