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

#ifndef LEVELENTRY_H
#define LEVELENTRY_H

#include <QList>

class QString;
class QPixmap;

class LevelEntry
{
public:
    LevelEntry(const QString &engineName, const QString &name, const QList<int> &teamList, const QString &imagePath, const QString &imageFile);
    LevelEntry();
    ~LevelEntry();

    QString getEngineName();
    QString getName();
    QList<int> getTeamList();
    QPixmap getImage();
    QPixmap getIcon();

private:
    QString engineName;
    QString name;
    QList<int> teamList;
    QString imagePath;
    QString imageFile;

};

#endif // LEVELENTRY_H
