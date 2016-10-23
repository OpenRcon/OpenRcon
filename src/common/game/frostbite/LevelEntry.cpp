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

#include "LevelEntry.h"

LevelEntry::LevelEntry(const QString &engineName, const QString &name, const QList<int> &teamList, const QString &imagePath, const QString &imageFile) :
    engineName(engineName),
    name(name),
    teamList(teamList),
    imagePath(imagePath),
    imageFile(imageFile)
{

}

LevelEntry::LevelEntry()
{

}

LevelEntry::~LevelEntry()
{

}

QString LevelEntry::getEngineName()
{
    return engineName;
}

QString LevelEntry::getName()
{
    return name;
}

QList<int> LevelEntry::getTeamList()
{
    return teamList;
}

QPixmap LevelEntry::getImage()
{
    return QPixmap(imagePath + "/" + imageFile).scaled(QSize(335, 160), Qt::KeepAspectRatio);
}

QPixmap LevelEntry::getIcon()
{
    return QPixmap(imagePath + "/thumbnails/" + imageFile).scaled(QSize(62, 42), Qt::KeepAspectRatio);
}