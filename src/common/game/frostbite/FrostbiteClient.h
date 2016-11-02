/*
 * Copyright (C) 2016 The OpenRcon Project.
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

#ifndef FROSTBITECLIENT_H
#define FROSTBITECLIENT_H

#include "Client.h"
#include "FrostbiteConnection.h"
#include "FrostbiteCommandHandler.h"

class QString;
class QByteArray;
template<class Key, class T>
class QMap;

class ServerEntry;

class FrostbiteClient : public Client
{
    Q_OBJECT

public:
    FrostbiteClient(ServerEntry *serverEntry, FrostbiteCommandHandler *commandHandler, QObject *parent = nullptr);
    virtual ~FrostbiteClient() override;

    FrostbiteConnection *getConnection() final {
        return connection;
    }

    virtual FrostbiteCommandHandler *getCommandHandler() override {
        return commandHandler;
    }

    void connectToHost() final;
    void disconnectFromHost() final;
    void reconnectToHost() final;

    QString getVersionFromBuild(int build) const;

protected:
    FrostbiteConnection *connection;
    FrostbiteCommandHandler *commandHandler;

    QMap<int, QString> versionMap;

public slots:
    void onConnected();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(bool auth);
    void onVersionCommand(const QString &type, int build);

};

#endif // FROSTBITECLIENT_H
