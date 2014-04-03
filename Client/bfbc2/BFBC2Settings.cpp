/*
 * Copyright (C) 2014 The OpenRcon Project.
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

#include "BFBC2Settings.h"

BFBC2Settings::BFBC2Settings(QObject *parent) : QObject(parent)
{
    settings = new QSettings(APP_NAME, APP_NAME, this);
}

BFBC2Settings::~BFBC2Settings()
{
    delete settings;
}

void BFBC2Settings::readSettings()
{

}

void BFBC2Settings::writeSettings()
{

}

/*
void ServerListDialog::loadServerEntries(QList<ServerEntry>& entries)
{
    settings->beginGroup(SETTINGS_SERVERMANAGER);
        int size = settings->beginReadArray(SETTINGS_SERVERENTRIES);
        for (int n = 0; n < size; n++) {
            settings->setArrayIndex(n);
            ServerEntry entry = {
                settings->value(SETTINGS_SERVERENTRY_GAME).toString(),
                settings->value(SETTINGS_SERVERENTRY_NAME).toString(),
                settings->value(SETTINGS_SERVERENTRY_HOST).toString(),
                settings->value(SETTINGS_SERVERENTRY_PORT).toString(),
                settings->value(SETTINGS_SERVERENTRY_PASSWORD).toString()
            };
            entries.append(entry);
        }
        settings->endArray();
    settings->endGroup();
}

void ServerListDialog::saveServerEntries(QList<ServerEntry>& entries)
{
    settings->beginGroup(SETTINGS_SERVERMANAGER);
        settings->remove(SETTINGS_SERVERENTRIES);
        const int size = entries.size();
        settings->beginWriteArray(SETTINGS_SERVERENTRIES);
            for (int n = 0; n < size; n++) {
                settings->setArrayIndex(n);
                    settings->setValue(SETTINGS_SERVERENTRY_GAME, entries.at(n).game);
                    settings->setValue(SETTINGS_SERVERENTRY_NAME, entries.at(n).name);
                    settings->setValue(SETTINGS_SERVERENTRY_HOST, entries.at(n).host);
                    settings->setValue(SETTINGS_SERVERENTRY_PORT, entries.at(n).port);
                    settings->setValue(SETTINGS_SERVERENTRY_PASSWORD, entries.at(n).password);
            }
        settings->endArray();
    settings->endGroup();
}


void BFBC2Widget::readSettings()
{
    QStringList users;
    settings->beginGroup(SETTINGS_INGAMECOMMANDS);
        int size = settings->beginReadArray(SETTINGS_INGAMECOMMANDS_USERS);
            for (int i = 0; i < size; i++) {
                settings->setArrayIndex(i);
                    users << settings->value("User").toString();
            }
        settings->endArray();
    settings->endGroup();

    qDebug() << "readSettings() got this:" << users;
    ui->listWidget_ic->addItems(users);
}

void BFBC2Widget::writeSettings()
{

}
*/
