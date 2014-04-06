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

#include <QCompleter>
#include <QTime>

#include "ui_BF4.h"

#include "BF4.h"
#include "BF4Levels.h"

class BF4Widget : public BF4
{
    Q_OBJECT

public:
    explicit BF4Widget(const QString &host, const int &port, const QString &password);
    ~BF4Widget();

private:
    Ui::BF4 *ui;
    BF4Levels *levels;

    QCompleter *completer;

    void logMessage(const int &type, const QString &message);
    void startupCommands();

private slots:
    void onDataSent(const QString &command);
    void onDataReceived(const QString &response);

    /* Events */
    void onPlayerAuthenticated(const QString &player, const QString &guid);
    void onPlayerJoin(const QString &player);
    void onPlayerLeave(const QString &player, const QString &info);
    void onPlayerSpawn(const QString &player, const QString &kit, const QStringList &weapons);
    void onPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot);
    void onPlayerChat(const QString &player, const QString &message, const QString &target);
    void onPlayerSquadChange(const QString &player, const int &teamId, const int &squadId);
    void onPlayerTeamChange(const QString &player, const int &teamId, const int &squadId);
    void onPunkBusterMessage(const QString &message);
    void onServerMaxPlayerCountChange();
    void onServerLevelLoaded(const QString &levelName, const QString &gameMode, const int &roundsPlayed, const int &roundsTotal);
    void onServerRoundOver(const int &winningTeamId);
    void onServerRoundOverPlayers(const QString &playerInfo);
    void onServerRoundOverTeamScores(const QString &teamScores);

    /* Commands */
    void onLoginHashedCommand();
    void onVersionCommand(const QString &type, const int &buildId, const QString &version);

    void onServerInfoCommand(const ServerInfo &serverInfo);

    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList);

    void onMapListListCommand(const MapList &mapList);

    void onVarsServerNameCommand(const QString &serverName);
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsServerMessageCommand(const QString &serverMessage);

    /* User Interface */

    /* Players */
    QIcon getRankIcon(const int &rank);
    void updatePlayerList();

    /* Event */
    void addEvent(const QString &message);

    /* Chat */
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

    /* Options */
    void lineEdit_op_so_serverName_editingFinished();
    void textEdit_op_so_serverDescription_textChanged();
    void lineEdit_op_so_serverMessage_editingFinished();

    /* Console */
    void pushButton_co_co_clicked();
    void pushButton_co_pb_clicked();

};

#endif // BF3WIDGET_H
