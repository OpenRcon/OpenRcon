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

#ifndef PLAYERLISTWIDGET_H
#define PLAYERLISTWIDGET_H

#include <QTreeWidget>

#include "LevelEntry.h"

class QTimer;
class QClipboard;
class QMenu;
class QAction;
class QIcon;
class QDragEnterEvent;
class QDragEvent;
template<class T>
class QList;
class QPoint;

class Frostbite2Client;
class Frostbite2ServerInfo;
class Player;

class PlayerListWidget : public QTreeWidget
{
    Q_OBJECT

public:
    PlayerListWidget(Frostbite2Client *client, QWidget *parent = nullptr);
    ~PlayerListWidget();

private:
    Frostbite2Client *client;

    /* User Interface */
    // Players
    QTimer *timer;
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

    QIcon getRankIcon(int rank) const;
    void resizeColumnsToContents();
    void dragEnterEvent(QDragEnterEvent *event) final;
    void dropEvent(QDropEvent *event) final;

private slots:
    /* Events */

    /* Commands */
    void onServerInfoCommand(const Frostbite2ServerInfo &serverInfo);

    /* User Interface */
    void listPlayers(const QList<Player> &playerList);
    void updatePlayerList();
    void customContextMenuRequested(const QPoint &pos);
    void action_player_kill_triggered();
    void action_player_kick_triggered();
    void action_player_ban_triggered();
    void action_player_reserveSlot_triggered();
    void action_player_copyTo_name_triggered();
    void action_player_copyTo_guid_triggered();
    void menu_player_move_triggered(QAction *action);

};

#endif // PLAYERLISTWIDGET_H
