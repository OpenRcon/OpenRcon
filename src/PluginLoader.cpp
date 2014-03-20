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

#include "PluginLoader.h"

/**
  * PluginLoader constructor.
  */
PluginLoader::PluginLoader(QObject *parent) : QObject(parent)
{
    pluginLoader = new QPluginLoader(this);
}

/**
  * PluginLoader destructor.
  */
PluginLoader::~PluginLoader()
{
    delete pluginLoader;
}

/**
  * Load a specified plugin.
  */
void PluginLoader::loadPlugin(const QString &pluginName)
{
    qDebug() << "Trying to load: " << pluginName;

    pluginLoader->setFileName(pluginName);
    QObject *plugin = pluginLoader->instance();

    if (plugin) {
        pluginInterface = qobject_cast<PluginInterface *>(plugin);

        qDebug() << "plugin";

        qDebug() << pluginInterface->getName();

        if (pluginInterface) {
            qDebug() << "Loaded plugin: " << pluginInterface->getName();
        }
    } else {
        qDebug() << pluginLoader->errorString();
    }
}

/**
  * Unload a loaded plugin.
  */
void PluginLoader::unloadPlugin(const QString &plugin)
{

}

/**
  * Load a list of plugins.
  */
void PluginLoader::loadPlugins(QStringList plugins)
{
    for (int i = 0; i < plugins.size(); i++) {
        loadPlugin(plugins.at(i));
    }
}

/**
  * Unload a list of plugins.
  */
void PluginLoader::unloadPlugins(QStringList plugins)
{
    for (int i = 0; i < plugins.size(); i++) {
        unloadPlugin(plugins.at(i));
    }
}

/**
  * Find plugins in specified directory.
  *
  * @return QStringList
  */
QStringList PluginLoader::findPlugins(const QString &pluginsPath)
{
    QDir *pluginsDir = new QDir(pluginsPath);

    QStringList pluginsList;
    QStringList pluginsDirList = pluginsDir->entryList(QDir::Files);

    for (int i = 0; i < pluginsDirList.size(); i++) {
        QString plugin = pluginsDirList.at(i);

        if (QLibrary::isLibrary(plugin)) {
            pluginsList << plugin;
        }
    }

    return pluginsList;
}
