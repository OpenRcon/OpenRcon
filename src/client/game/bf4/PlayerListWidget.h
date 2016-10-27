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

#ifndef PLAYERLISTWIDGET_H
#define PLAYERLISTWIDGET_H

#include <QTreeWidget>

#include "LevelEntry.h"

class QClipboard;

class BF4Client;
class Frostbite2ServerInfo;
class PlayerInfo;
enum class PlayerSubsetEnum;

class PlayerListWidget : public QTreeWidget
{
    Q_OBJECT

public:
    PlayerListWidget(BF4Client *client, QWidget *game = 0);
    ~PlayerListWidget();

private:
    BF4Client *client;

    // Players
    QClipboard *clipboard;
    QMenu *menu_player;
    QAction *action_player_kill;
    QAction *action_player_kick;
    QAction *action_player_ban;
    QAction *action_player_reserveSlot;
    QMenu *menu_player_move;
    QAction *action_player_move_team;
    QAction *action_player_move_squad;
    QMenu *menu_player_copyTo;
    QAction *action_player_copyTo_name;
    QAction *action_player_copyTo_guid;

    LevelEntry currentLevel;

    QIcon getRankIcon(int rank);
    QString getSquadName(int squadId);

private slots:
    /* Events */

    /* Commands */
    void onLoginHashedCommand(bool auth);
    void onServerInfoCommand(const Frostbite2ServerInfo &serverInfo);

    /* User Interface */
    void listPlayers(const QList<PlayerInfo> &playerList, const PlayerSubsetEnum &playerSubset);
    void updatePlayerList();
    void customContextMenuRequested(const QPoint &pos);
    void action_player_kill_triggered();
    void action_player_kick_triggered();
    void action_player_ban_triggered();
    void action_player_reserveSlot_triggered();
    void action_player_copyTo_name_triggered();
    void action_player_copyTo_guid_triggered();
    void menu_player_move_triggered(QAction *action);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

};

#endif // PLAYERLISTWIDGET_H
