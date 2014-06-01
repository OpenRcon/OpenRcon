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

#ifndef EVENTSWIDGET_H
#define EVENTSWIDGET_H

#include <QWidget>

class FrostbiteConnection;
class BF4CommandHandler;

namespace Ui {
    class EventsWidget;
}

class EventsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EventsWidget(FrostbiteConnection *connection, QWidget *parent = nullptr);
    ~EventsWidget();

private:
    Ui::EventsWidget *ui;
    FrostbiteConnection *connection;
    BF4CommandHandler *commandHandler;

    // Events
    void logEvent(const QString &event, const QString &message);
    void addEvent(const QString &event, const QString &message);

private slots:
    /* Connection */
    void onConnected();
    void onDisconnected();

    /* Events */
    void onPlayerAuthenticatedEvent(const QString &player);
    void onPlayerDisconnectEvent(const QString &player);
    void onPlayerJoinEvent(const QString &player, const QString &guid);
    void onPlayerLeaveEvent(const QString &player, const QString &info);
    void onPlayerSpawnEvent(const QString &player, int teamdId);
    void onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot);
    void onPlayerChatEvent(const QString &sender, const QString &message, const QString &target);
    void onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId);
    void onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId);
    void onServerMaxPlayerCountChangeEvent();
    void onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal);
    void onServerRoundOverEvent(int winningTeamId);
    void onServerRoundOverPlayersEvent(const QString &playerInfo);
    void onServerRoundOverTeamScoresEvent(const QString &teamScores);

    /* Commands */
    // Misc
    void onLoginHashedCommand(bool auth);

    /* User Interface */
};

#endif // EVENTSWIDGET_H
