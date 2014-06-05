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

#ifndef BF3WIDGET_H
#define BF3WIDGET_H

#include "BF3.h"
#include "FrostbiteConnection.h"

class ChatWidget;
class ReservedSlotsWidget;
class ConsoleWidget;

struct Frostbite2ServerInfo;
struct PlayerInfo;
enum class PlayerSubset;

namespace Ui {
    class BF3Widget;
}

class BF3Widget : public BF3
{
    Q_OBJECT

public:
    BF3Widget(ServerEntry *serverEntry);
    ~BF3Widget();

    virtual Connection *getConnection() {
        return m_connection;
    }

private:
    Ui::BF3Widget *ui;
    ChatWidget *chatWidget;
    ReservedSlotsWidget *reservedSlotsWidget;
    ConsoleWidget *consoleWidget;

    /* User Interface */
    // ServerInfo

    // Players
    QTimer *timerPlayerList;

    // Banlist

    void setAuthenticated(bool auth);
    void startupCommands(bool authenticated);
//    void logEvent(const QString &event, const QString &message);

    QIcon getRankIcon(int rank);

private slots:
    /* Connection */
    void onConnected();
    void onDisconnected();

    /* Events */

    /* Commands */

    // Misc
    void onLoginHashedCommand(bool auth);
    void onServerInfoCommand(const Frostbite2ServerInfo &serverInfo);
    void onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);

    // Admin
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);

    // Banning

    // FairFight

    // Maplist

    // Player

    // Punkbuster

    // Squad

    // Variables

    /* User Interface */

    // ServerInfo

    // Players
    void updatePlayerList();
    void listPlayers(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);

    // Maplist

    // BanList

    // Options

};

#endif // BF3WIDGET_H
