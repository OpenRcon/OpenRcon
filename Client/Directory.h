/*
 * Copyright (C) 2011 The OpenRcon Project.
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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QDir>

#include "Constants.h"

using namespace Constants;

class Directory : public QObject
{
    Q_OBJECT

public:
    explicit Directory(QObject *parent = 0);
    ~Directory();

    void cd(const QString &folder);

    QString getPath() const;
    QStringList getList() const;

private:
    QDir *appDir;

};

#endif // DIRECTORY_H
