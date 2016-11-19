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

#ifndef FROSTBITEEVENTSWIDGET_H
#define FROSTBITEEVENTSWIDGET_H

#include "FrostbiteWidget.h"

#include "LevelEntry.h"

class QString;
class QAbstractSocket;

namespace Ui {
    class FrostbiteEventsWidget;
}

class FrostbiteEventsWidget : public FrostbiteWidget
{
    Q_OBJECT

public:
    FrostbiteEventsWidget(FrostbiteClient *client, QWidget *parent = nullptr);
    ~FrostbiteEventsWidget() final;

private:
    Ui::FrostbiteEventsWidget *ui;
    LevelEntry levelEntry;

    void logEvent(const QString &event, const QString &message);

private slots:
    /* Connection */
    void onConnected(QAbstractSocket *socket);
    void onDisconnected();

    /* Client */
    void onAuthenticated();

    /* Events */
    void onPlayerAuthenticatedEvent(const QString &player);
    void onPlayerDisconnectEvent(const QString &player);
    void onPlayerJoinEvent(const QString &player, const QString &guid);
    void onPlayerLeaveEvent(const QString &player, const QString &info);
    void onPlayerSpawnEvent(const QString &player, int teamdId);
    void onPlayerKillEvent(const QString &killerPlayer, const QString &victimPlayer, const QString &weapon, bool headshot);
    void onPlayerChatEvent(const QString &sender, const QString &message, const PlayerSubsetEnum &playerSubset);
    void onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId);
    void onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId);
    void onServerMaxPlayerCountChangeEvent();
    void onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal);
    void onServerRoundOverEvent(int winningTeamId);
    void onServerRoundOverPlayersEvent(const QString &playerInfo);
    void onServerRoundOverTeamScoresEvent(const QString &teamScores);

    /* Commands */
    void onCurrentLevelCommand(const QString &levelName);

};

#endif // FROSTBITEEVENTSWIDGET_H
