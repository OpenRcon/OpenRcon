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

#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QApplication>
#include <QStringList>
#include <QString>

#include "Plugin.h"
#include "PluginInterface.h"

class PluginLoader : public QObject
{
    Q_OBJECT

public:
    explicit PluginLoader(QObject *parent = 0);
    ~PluginLoader();

    void loadPlugin(const QString &plugin);
    void unloadPlugin(const QString &plugin);

    void loadPlugins(QStringList plugins);
    void unloadPlugins(QStringList plugins);

    QStringList findPlugins(const QString &pluginsPath);

private:
    QPluginLoader *pluginLoader;

    PluginInterface *pluginInterface;

};

#endif // PLUGINLOADER_H
