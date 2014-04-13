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

#include <QApplication>
#include <QSettings>
#include <QString>
#include <QTranslator>
#include <QLocale>

#include <OpenRcon.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Check for saved translation or use system default
    QSettings settings(APP_NAME, APP_NAME);
    QString locale = settings.value("Settings/General/Locale").toString();
    QTranslator translator;

    if (locale.isEmpty()) {
        locale = QLocale::system().name();
        settings.setValue("Settings/General/Locale", locale);
    }

    translator.load(":/locale/openrcon_" + locale);
    app.installTranslator(&translator);

    // Launch the app.
    OpenRcon *o = OpenRcon::getInstance();
    o->show();

    return app.exec();
}
