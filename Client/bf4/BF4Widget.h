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
#include "BF4Level.h"
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

    QStringList squadNameList;
    QStringList commandList;
    QCompleter *completer;

    void logMessage(const int &type, const QString &message);
    void startupCommands();

    QIcon getRankIcon(const int &rank);
    QPixmap getLevelImage(BF4Level *level);
    QString getSquadName(const int &id);

private slots:
    void onDataSent(const QString &command);
    void onDataReceived(const QString &response);
    void onAuthenticated();

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
    void onVersionCommand(const QString &type, const int &buildId, const QString &version);
    void onAdminListPlayersCommand(const PlayerList &playerList);
    void onMapListListCommand(const QStringList &mapList);

    void onVarsServerNameCommand(const QString &serverName);
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsServerMessageCommand(const QString &serverMessage);

    void pushButton_ch_clicked();

    void comboBox_li_ml_gameMode_currentIndexChanged(int);
    void listWidget_li_ml_avaliable_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void pushButton_li_ml_add_clicked();
    void pushButton_li_ml_remove_clicked();

    void lineEdit_op_so_serverName_editingFinished();
    void textEdit_op_so_serverDescription_textChanged();
    void lineEdit_op_so_serverMessage_editingFinished();

    void pushButton_co_co_clicked();
    void pushButton_co_pb_clicked();

    void updatePlayerList();

};

#endif // BF3WIDGET_H