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
class FrostbiteConnection;
class BF4CommandHandler;
struct BF4ServerInfo;
struct PlayerInfo;
enum class PlayerSubset;

class PlayerListWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit PlayerListWidget(FrostbiteConnection *connection, QWidget *parent = 0);
    ~PlayerListWidget();

private:
    FrostbiteConnection *m_connection;
    BF4CommandHandler *m_commandHandler;

    // Players
    QClipboard *clipboard;
    QMenu *menu_pl_players;
    QAction *action_pl_players_kill;
    QAction *action_pl_players_kick;
    QAction *action_pl_players_ban;
    QAction *action_pl_players_reserveSlot;
    QMenu *menu_pl_players_move;
    QAction *action_pl_players_move_team;
    QAction *action_pl_players_move_squad;
    QMenu *menu_pl_players_copyTo;
    QAction *action_pl_players_copyTo_name;
    QAction *action_pl_players_copyTo_guid;

    LevelEntry currentLevel;

    QIcon getRankIcon(int rank);
    QString getSquadName(int squadId);

private slots:
    /* Events */
    void updatePlayerList();

    /* Command slots */
    void onLoginHashedCommand(bool auth);
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);

    /* User Interface */
    void customContextMenuRequested(const QPoint &pos);
    void action_pl_players_kill_triggered();
    void action_pl_players_kick_triggered();
    void action_pl_players_ban_triggered();
    void action_pl_players_reserveSlot_triggered();
    void action_pl_players_copyTo_name_triggered();
    void action_pl_players_copyTo_guid_triggered();
    void menu_pl_players_move_triggered(QAction *action);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

};

#endif // PLAYERLISTWIDGET_H
