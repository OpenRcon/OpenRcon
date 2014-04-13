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

#include "Directory.h"

Directory::Directory(QObject *parent) : QObject(parent)
{
    appDir = new QDir(QDir::home().homePath());

    if (appDir->exists(APP_DIR)) {
        appDir->cd(APP_DIR);
        qDebug() << tr("Directory %1 exists.").arg(APP_DIR);
    } else {
        if (appDir->mkdir(APP_DIR)) {
            appDir->cd(APP_DIR);
            qDebug() << tr("Made directory %1.").arg(APP_DIR);
        } else {
            qDebug() << tr("Tried make directory %1, but failed.").arg(APP_DIR);
        }
    }

    qDebug() << tr("Directory path is: %1.").arg(getPath());
}

Directory::~Directory()
{
    delete appDir;
}

QString Directory::getPath()
{
    return appDir->path();
}
