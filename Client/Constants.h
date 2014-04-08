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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace Constants {
    // Application
    const QString APP_NAME = "OpenRcon";
    const QString APP_VERSION = "0.2";
    const QString APP_ICON = ":/images/icons/openrcon.png";
    const QString APP_URL = "http://openrcon.org/";
    const QString APP_DIR = ".openrcon";
    const QString APP_AUTHOR = "The OpenRcon Project";
    const int APP_YEAR = 2011;
    const QString APP_BUG = "http://bugs.openrcon.org/";
    const QString APP_DOC = "http://doc.openrcon.org/";

    // Settings
    const QString SETTINGS_OPENRCON = "OpenRcon";
    const QString SETTINGS_SERVERMANAGER = "ServerManager";
    const QString SETTINGS_SERVERENTRIES = "ServerEntries";

    const QString SETTINGS_SERVERENTRY_GAME = "Game";
    const QString SETTINGS_SERVERENTRY_NAME = "Name";
    const QString SETTINGS_SERVERENTRY_HOST = "Host";
    const QString SETTINGS_SERVERENTRY_PORT = "Port";
    const QString SETTINGS_SERVERENTRY_PASSWORD = "Password";
}

#endif // CONSTANTS_H
