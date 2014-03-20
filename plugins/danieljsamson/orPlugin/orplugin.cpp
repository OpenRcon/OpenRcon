/*
Copyright (C) 2010 The OpenRcon Project.

This file is part of OpenRcon.

OpenRcon is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenRcon is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "orplugin.h"
bool orPlugin::isPluginOR()
{
    // #include <QDebug>
    // qDebug() << "Hello World!";
    return true;
}
bool orPlugin::isUserAllowedToSetPortNumber()
{
    return false;
}
bool orPlugin::isUserAllowedToSetUsername()
{
    return false;
}
bool orPlugin::isUserAllowedToSetPassword()
{
    return false;
}

bool orPlugin::isSigned()
{
    return false;
}

bool orPlugin::isEnabled()
{
    return false;
}

bool orPlugin::isConnected()
{
    return false;
}

qint32 orPlugin::openConnection(QString hostURI, quint32 portNumber, QString username, QString password)
{
    return 0;
}

qint32 orPlugin::closeConnection()
{
    return 0;
}

qint32 orPlugin::enable()
{
    return 0;
}
qint32 orPlugin::disable()
{
    return 0;
}
QString orPlugin::getName()
{
    QString name = "orTestPlugin";
    return name;
}
QString orPlugin::getVersion()
{
    QString version = "1.0";
    return version;
}
QString orPlugin::getDescription()
{
    return "";
}
QString orPlugin::getDeveloper()
{
    return "";
}
QString orPlugin::getDeveloperWebsite()
{
    return "";
}
QString orPlugin::getDeveloperSupportLink()
{
    return "";
}
QString orPlugin::getPluginSystemVersion()
{
    return "";
}
QString orPlugin::getPluginSystemType()
{
    return "";
}
QString orPlugin::getSignature()
{
    return "";
}
QString orPlugin::getPluginDefaultPortNumber()
{
    return "";
}
QString orPlugin::getConnectionStatus()
{
    return "";
}
QIcon orPlugin::getIcon()
{
       QIcon pluginIcon;
    return pluginIcon;
}
//QWidget orPlugin::getWidget()
//{
//    QWidget widget;
//    return widget;
//}

// Q_EXPORT_PLUGIN2 ( PluginName, ClassName )
Q_EXPORT_PLUGIN2(orPlugin, orPlugin);
