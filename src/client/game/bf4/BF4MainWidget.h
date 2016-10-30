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

#ifndef BF4MAINWIDGET_H
#define BF4MAINWIDGET_H

#include "BF4Widget.h"

class QTimer;
class QAbstractSocket;
class QString;

class ServerEntry;
class PlayerListWidget;
class EventsWidget;
class ChatWidget;
class BF4OptionsWidget;
class MapListWidget;
class BanListWidget;
class ReservedSlotsWidget;
class SpectatorSlotsWidget;
class ConsoleWidget;
class BF4ServerInfo;

namespace Ui {
    class BF4MainWidget;
}

class BF4MainWidget : public BF4Widget
{
    Q_OBJECT

public:
    BF4MainWidget(ServerEntry *serverEntry, QWidget *parent = nullptr);
    ~BF4MainWidget() final;

private:
    Ui::BF4MainWidget *ui;

    PlayerListWidget *playerListWidget;
    EventsWidget *eventsWidget;
    ChatWidget *chatWidget;
    BF4OptionsWidget *optionsWidget;
    MapListWidget *mapListWidget;
    BanListWidget *banListWidget;
    ReservedSlotsWidget *reservedSlotsWidget;
    SpectatorSlotsWidget *spectatorSlotsWidget;
    ConsoleWidget *consoleWidget;

    /* User Interface */
    // ServerInfo
    QTimer *timerServerInfoRoundTime;
    QTimer *timerServerInfoUpTime;
    int roundTime;
    int upTime;

    void setAuthenticated(bool auth);
    void startupCommands(bool auth);

private slots:
    /* Events */
    void onConnected(QAbstractSocket *socket);
    void onDisconnected(QAbstractSocket *socket);
    void onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal);

    /* Commands */
    // Misc
    void onLoginHashedCommand(bool auth);
    void onVersionCommand(const QString &type, int build);
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables
    void onVarsAlwaysAllowSpectatorsCommand(bool enabled);

    /* User Interface */
    // Server Information
    void pushButton_si_restartRound_clicked();
    void pushButton_si_runNextRound_clicked();
    void updateRoundTime();
    void updateUpTime();

};

#endif // BF4MAINWIDGET_H