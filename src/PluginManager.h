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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QDir>
#include <QStringList>

#include "Plugin.h"
#include "PluginLoader.h"
//#include "PluginInterface.h"

class PluginManager : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject *parent = 0);
    ~PluginManager();

    void loadPlugins(QStringList pluginList);
    void unloadPlugins(QStringList pluginList);

    QList<Plugin *> getPlugins();
    void setPlugins(QList<Plugin *> plugins);

    Plugin getPlugin(const QString &plugin);

    void addPlugin(Plugin *plugin);
    void removePlugin(Plugin *plugin);

private:
    QList<Plugin *> plugins;

    PluginLoader *pluginLoader;

    QDir *pluginsDir;

};

#endif // PLUGINMANAGER_H
