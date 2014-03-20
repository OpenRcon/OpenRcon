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

#include "PluginManager.h"

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    pluginLoader = new PluginLoader(this);
}

PluginManager::~PluginManager()
{
    delete pluginLoader;
}

void PluginManager::loadPlugins(QStringList pluginsList)
{
    for (int i = 0; i < pluginsList.size(); i++) {
        pluginLoader->loadPlugin(pluginsList.at(i));
    }
}

void PluginManager::unloadPlugins(QStringList pluginList)
{
    for (int i = 0; i < pluginList.size(); i++) {
        pluginLoader->unloadPlugin(pluginList.at(i));
    }
}

QList<Plugin *> PluginManager::getPlugins()
{
    return plugins;
}

void PluginManager::setPlugins(QList<Plugin *> plugins)
{
    this->plugins = plugins;
}

Plugin PluginManager::getPlugin(const QString &plugin)
{
    for (int i = 0; i < plugins.size(); i++) {
        Plugin *p = plugins.at(i);

        if (p->getName() == plugin) {
            return *p;
        }
    }

    return Plugin();
}

void PluginManager::addPlugin(Plugin *plugin)
{
    plugins.append(plugin);
}

void PluginManager::removePlugin(Plugin *plugin)
{
    plugins.removeAt(plugins.indexOf(plugin));
}
