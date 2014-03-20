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
#ifndef ORPLUGININTERFACE_H
#define ORPLUGININTERFACE_H
//
#include <QString>
#include <QIcon>
#include <QtGlobal>
#include <QtPlugin>
/*
 * Interface defined for the plugin system of openrcon.
 */
class orPluginInterface
{
public:
    /*
     * Plugin Manager checks this first to make sure that the plugin is designed for openrcon.
     * IF plugin returns false OR doesn't exist THEN the plugin is unloaded
     */
    virtual bool isPluginOR() =0;
    /*
     * The openrcon toolbar widgets are enabled/disabled based the return value of the following.
     * ****This allows the developer to specifiy the fields that the plugin uses.****
     */
    virtual bool isUserAllowedToSetPortNumber() = 0;
    virtual bool isUserAllowedToSetUsername() = 0;
    virtual bool isUserAllowedToSetPassword() = 0;
    // Allows Plugin Manager to check if plugin is enabled.
    virtual bool isEnabled() = 0;
    // Allows Plugin Manager to check if plugin has been (officially) signed by the openrcon.
    virtual bool isSigned() = 0;
    // Controls the connection and Enables/Disables the plugin.
    virtual bool isConnected() =0;
    virtual qint32 openConnection(QString hostURI, quint32 portNumber, QString username, QString password) =0;
    virtual qint32 closeConnection() =0;
    virtual qint32 enable() = 0;
    virtual qint32 disable() = 0;
    // Plugin details:
    virtual QString getName() = 0;
    virtual QString getVersion() = 0;
    virtual QString getDescription() = 0;
    virtual QString getDeveloper() = 0;
    virtual QString getDeveloperWebsite() = 0;
    virtual QString getDeveloperSupportLink()= 0;
    virtual QString getPluginSystemVersion()= 0;
    virtual QString getPluginSystemType()= 0; // Defines the type of functionality the plugin extends
    virtual QString getSignature()= 0;
    virtual QString getPluginDefaultPortNumber()= 0;
    virtual QString getConnectionStatus()= 0;
    virtual QIcon getIcon()= 0;
    QWidget pluginWidget;
};
// Q_DECLARE_INTERFACE ( ClassName, Identifier )
Q_DECLARE_INTERFACE(orPluginInterface, "com.orPluginInterface/1.0");
#endif // ORPLUGININTERFACE_H
