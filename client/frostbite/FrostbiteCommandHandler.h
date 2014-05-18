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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FROSTBITECOMMANDHANDLER_H
#define FROSTBITECOMMANDHANDLER_H

#include <QCryptographicHash>

#include "CommandHandler.h"

class FrostbiteConnection;
class FrostbiteRconPacket;

class FrostbiteCommandHandler : public CommandHandler
{
    Q_OBJECT

public:
    FrostbiteCommandHandler(FrostbiteConnection *parent = nullptr);
    ~FrostbiteCommandHandler();

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Send commands */
    // Misc
    void sendLoginPlainTextCommand(const QString &password);
    void sendLoginHashedCommand(const QByteArray &salt = QByteArray(), const QString &password = QString());
    void sendLogoutCommand();
    void sendQuitCommand();
    void sendVersionCommand();

protected:
    FrostbiteConnection *con;

private:
    /* Parse events */

    /* Parse commands */
    // Misc
    void parseLoginPlainTextCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseQuitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVersionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

signals:
    /* Event signals */

    /* Command signals */
    // Misc
    void onLoginPlainTextCommand(bool auth);
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(bool auth);
    void onLogoutCommand();
    void onQuitCommand();
    void onVersionCommand(const QString &type, int build);

};

#endif // FROSTBITECOMMANDHANDLER_H
