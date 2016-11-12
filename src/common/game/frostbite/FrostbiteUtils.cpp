/*
 * Copyright (C) 2010 The OpenRcon Project.
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

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QIcon>

#include "FrostbiteUtils.h"
#include "Time.h"
#include "GameType.h"
#include "Squad.h"

QStringList FrostbiteUtils::squads = {
    "None",
    "Alpha",
    "Bravo",
    "Charlie",
    "Delta",
    "Echo",
    "Foxtrot",
    "Golf",
    "Hotel",
    "India",
    "Juliet",
    "Kilo",
    "Lima",
    "Mike",
    "November",
    "Oscar",
    "Papa",
    "Quebec",
    "Romeo",
    "Sierra",
    "Tango",
    "Uniform",
    "Victor",
    "Whiskey",
    "X-Ray",
    "Yankee",
    "Zulu",
    "Haggard",
    "Sweetwater",
    "Preston",
    "Redford",
    "Faith",
    "Celeste"
};

int FrostbiteUtils::toInt(const QString &value)
{
    return value.toInt();
}

float FrostbiteUtils::toFloat(const QString &value)
{
    return value.toFloat();
}

bool FrostbiteUtils::toBool(const QString &value)
{
    return value == "true";
}

QString FrostbiteUtils::toString(bool value)
{
    return value ? "true" : "false";
}

QString FrostbiteUtils::toCamelCase(const QString &value)
{
    QString camelCaseValue = value.toLower();
    camelCaseValue.remove(0, 1);
    camelCaseValue.insert(0, value.at(0).toUpper());

    return camelCaseValue;
}


QIcon FrostbiteUtils::getRankIcon(GameTypeEnum gameType, int rank)
{
    QString path = QString(":/%1/ranks/rank_%2.png").arg(GameType::toString(gameType).toLower(), rank);
    QIcon icon = QIcon(path);

    if (!icon.isNull()) {
        return icon;
    } else {
        qDebug() << "Icon pixmap for rank" << rank << "is null." << "No file found at path: " << path;
    }

    return QIcon();
}
