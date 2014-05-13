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

#ifndef LEVELENTRY_H
#define LEVELENTRY_H

#include <QString>
#include <QPixmap>

struct LevelEntry {
    LevelEntry()
    {

    }

    LevelEntry(const QString &engineName,
               const QString &name,
               int team1,
               int team2,
               const QString &image) :
        engineName(engineName),
        name(name),
        team1(team1),
        team2(team2),
        imagePath(image)
    {

    }

    QPixmap image() {
        return QPixmap(imagePath).scaled(QSize(320, 200), Qt::KeepAspectRatio);
    }

    QString engineName;
    QString name;
    int team1;
    int team2;
    QString imagePath;
    QString mod;

};

#endif // LEVELENTRY_H
