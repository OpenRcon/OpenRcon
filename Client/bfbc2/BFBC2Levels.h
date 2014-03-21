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

#ifndef BFBC2LEVELS_H
#define BFBC2LEVELS_H

#include <QStringList>

#include "BFBC2Constants.h"
#include "Constants.h"

using namespace Constants;
using namespace BFBC2Constants;

class LevelList;

class BFBC2Levels
{

public:
    BFBC2Levels(const QString &currentMod);

    QList<LevelList*> levels()
    {
        return levellist;
    }

private:
    QList<LevelList*> levellist;

};

struct Level {
    QString mod;
    QString name;
    QString path;
    QString image;

    Level(const QString &mod ,const QString &name, const QString &path, const QString &img) : mod(mod), name(name), path(path), image(img) {
    }

};

class LevelList {

public:
    LevelList(QList<Level *> lvs) : levels(lvs) {
    }

    QStringList mapMods() {
        QStringList mods;
        foreach(Level *l, levels) {
            mods << l->mod;
        }
        return mods;
    }

    QStringList mapNames() {
        QStringList names;
        foreach(Level *l, levels) {
            names << l->name;
        }
        return names;
    }

    QStringList mapPaths() {
        QStringList paths;
        foreach(Level *l, levels) {
            paths << l->path;
        }
        return paths;
    }

    QStringList mapImages() {
        QStringList images;
        foreach (Level *l, levels) {
            images << l->image;
        }
        return images;
    }

private:
    QList<Level *> levels;

};

#endif // BFBC2LEVELS_H
