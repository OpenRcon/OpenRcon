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

#include "CommandHandler.h"

class FrostbiteConnection;
class FrostbiteRconPacket;
struct BanListEntry;

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

    // BanList
    void sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason);
    void sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason);
    void sendBanListClearCommand();
    void sendBanListListCommand(int index = 0);
    void sendBanListLoadCommand();
    void sendBanListRemoveCommand(const QString &idType, const QString &id);
    void sendBanListSaveCommand();

    // PunkBuster
    void sendPunkBusterPbSvCommand(const QString &command);

protected:
    FrostbiteConnection *m_connection;

private:
    /* Parse events */
    void parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse commands */
    // Misc
    void parseLoginPlainTextCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseQuitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVersionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // BanList
//    void parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseBanListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseBanListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
//    void parseBanListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // PunkBuster
//    void parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

signals:
    /* Event signals */
    void onPunkBusterMessageEvent(const QString &message);

    /* Command signals */
    // Misc
    void onLoginPlainTextCommand(bool auth);
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(bool auth);
    void onLogoutCommand();
    void onQuitCommand();
    void onVersionCommand(const QString &type, int build);

    // BanList
//    void onBanListAddCommand();
//    void onBanListClearCommand();
    void onBanListListCommand(const QList<BanListEntry> &banList);
//    void onBanListLoadCommand();
//    void onBanListRemoveCommand();
//    void onBanListSaveCommand();

    // Punkbuster
    void onPunkBusterPbSvCommand();

};

#endif // FROSTBITECOMMANDHANDLER_H
