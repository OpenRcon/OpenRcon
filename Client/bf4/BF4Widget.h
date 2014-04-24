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

#ifndef BF4WIDGET_H
#define BF4WIDGET_H

#include <QTime>
#include <QMenu>
#include <QCompleter>

#include "ui_BF4.h"
#include "BF4.h"

class BF4Widget : public BF4
{
    Q_OBJECT

public:
    explicit BF4Widget(const QString &host, const int &port, const QString &password);
    ~BF4Widget();

private:
    Ui::BF4 *ui;

    // Players
    QMenu *menu_pl_players;
    QAction *action_pl_players_kill;
    QMenu *menu_pl_players_move;

    // Banlist
    QMenu *menu_bl_banList;
    QAction *action_bl_banList_remove;

    // Reserved Slots
    QMenu *menu_rs_reservedSlotsList;
    QAction *action_rs_reservedSlotsList_remove;

    // Spectator List
    QMenu *menu_ss_spectatorList;
    QAction *action_ss_spectatorList_remove;

    // Console
    QCompleter *completer;

    void startupCommands();
    void logEvent(const QString &event, const QString &message);
    void logChat(const QString &sender, const QString &message);
    void logConsole(const int &type, const QString &message);

    // Players
    QIcon getRankIcon(const int &rank);

    // Events
    void addEvent(const QString &event, const QString &message);

private slots:
    void onDataSent(const QString &command);
    void onDataReceived(const QString &response);

    /* Events */
    void onPlayerAuthenticated(const QString &player, const QString &guid);
    void onPlayerJoin(const QString &player);
    void onPlayerLeave(const QString &player, const QString &info);
    void onPlayerSpawn(const QString &player, const int &teamdId);
    void onPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot);
    void onPlayerChat(const QString &sender, const QString &message, const QString &target);
    void onPlayerSquadChange(const QString &player, const int &teamId, const int &squadId);
    void onPlayerTeamChange(const QString &player, const int &teamId, const int &squadId);
    void onPunkBusterMessage(const QString &message);
    void onServerMaxPlayerCountChange();
    void onServerLevelLoaded(const QString &levelName, const QString &gameModeName, const int &roundsPlayed, const int &roundsTotal);
    void onServerRoundOver(const int &winningTeamId);
    void onServerRoundOverPlayers(const QString &playerInfo);
    void onServerRoundOverTeamScores(const QString &teamScores);

    /* Commands */
    // Misc
    void onLoginHashedCommand(const bool &auth);
    void onVersionCommand(const QString &type, const int &buildId, const QString &version);
    void onServerInfoCommand(const ServerInfo &serverInfo);

    // Admin
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList);

    // Banning
    void onBanListListCommand(const BanList &banList);
    void action_bl_banList_remove_triggered();

    // FairFight
    void onFairFightIsActiveCommand(const bool &isActive);

    // Maplist
    void onMapListListCommand(const MapList &mapList);

    // Player

    // Punkbuster
    void onPunkBusterIsActiveCommand(const bool &isActive);

    // Reserved Slots
    void onReservedSlotsListListCommand(const QStringList &reservedSlotsList);

    // Spectator list
    void onSpectatorListListCommand(const QStringList &spectatorList);

    // Squad

    // Variables
    void onVarsMaxPlayersCommand(const int &playerCount);
    void onVarsMaxSpectatorsCommand(const int &spectatorCount);
    void onVarsServerNameCommand(const QString &serverName);
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsServerMessageCommand(const QString &serverMessage);
    void onVarsServerTypeCommand(const QString &type);

    /* User Interface */

    /* Players */
    void updatePlayerList();
    void treeWidget_pl_players_customContextMenuRequested(const QPoint &pos);
    void action_pl_players_kill_triggered();

    /* Chat */
    void comboBox_ch_mode_currentIndexChanged(int index);
    void pushButton_ch_clicked();

    /* Maplist */
    void comboBox_ml_gameMode_currentIndexChanged(int);
    void tableWidget_ml_avaliable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void pushButton_ml_add_clicked();
    void pushButton_ml_remove_clicked();
    void tableWidget_ml_current_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void addAvaliableMapListRow(const QString &name, const QString &gameMode);
    void setAvaliableMaplist(const int &gameModeIndex);
    void addCurrentMapListRow(const QString &name, const QString &gameMode, const int &rounds);
    void setCurrentMaplist(const MapList &mapList);

    /* BanList */
    void tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos);

    void addBanListRow(const QString &idType, const QString &id, const QString &banType, const int &seconds, const int &rounds, const QString &reason);
    void setBanlist(const BanList &banList);

    /* Reserved Slots */
    void listWidget_rs_reservedSlotsList_customContextMenuRequested(const QPoint &pos);
    void action_rs_reservedSlotsList_remove_triggered();
    void pushButton_rs_add_clicked();
    void pushButton_rs_load_clicked();
    void pushButton_rs_save_clicked();
    void pushButton_rs_clear_clicked();

    /* Spectator List */
    void listWidget_ss_spectatorList_customContextMenuRequested(const QPoint &pos);
    void action_ss_spectatorList_remove_triggered();
    void pushButton_ss_add_clicked();
    void pushButton_ss_load_clicked();
    void pushButton_ss_save_clicked();
    void pushButton_ss_clear_clicked();

    /* Options */
    void lineEdit_op_so_serverName_editingFinished();
    void textEdit_op_so_serverDescription_textChanged();
    void lineEdit_op_so_serverMessage_editingFinished();

    void checkBox_so_co_punkBuster_toggled(bool checked);
    void checkBox_so_co_fairFight_toggled(bool checked);

    /* Console */
    void pushButton_co_co_clicked();
    void pushButton_co_pb_clicked();

};

#endif // BF3WIDGET_H
