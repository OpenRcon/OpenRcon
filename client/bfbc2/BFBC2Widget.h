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

#ifndef BFBC2WIDGET_H
#define BFBC2WIDGET_H

#include "BFBC2.h"
#include "BFBC2CommandHandler.h"

class QMenu;
class QCompleter;
class QSettings;
class QListWidgetItem;
class QAction;
class QTimer;

class ChatWidget;
class BanListWidget;
class ConsoleWidget;

namespace Ui {
    class BFBC2Widget;
}

class BFBC2Widget : public BFBC2
{
    Q_OBJECT

public:
    BFBC2Widget(ServerEntry *serverEntry);
    ~BFBC2Widget();

private:
    Ui::BFBC2Widget *ui;
    ChatWidget *chatWidget;
    BanListWidget *banListWidget;
    ConsoleWidget *consoleWidget;

    QAction *action_pl_sendmessage;
    QAction *action_pl_textchatmoderation_muted;
    QAction *action_pl_textchatmoderation_normal;
    QAction *action_pl_textchatmoderation_voice;
    QAction *action_pl_textchatmoderation_admin;
    QAction *action_pl_kill;
    QAction *action_pl_kick_custom;
    QAction *action_pl_ban_byname;
    QAction *action_pl_reservedslots;
    QAction *action_pl_admin;
    QAction *action_pl_move;

    QAction *action_bl_remove;
    QAction *action_rs_remove;
    QAction *action_ic_remove;

    QTimer *commandRefreshTimer;

    QMenu *menu_pl;
    QMenu *menu_pl_ban;
    QMenu *menu_pl_kick;
    QMenu *menu_pl_move;
    QMenu *menu_pl_textchatmoderation;
    QMenu *menu_bl;
    QMenu *menu_rs;
    QMenu *menu_ic;

    void setAuthenticated(bool authenticated);
    void startupCommands(bool authenticated);
//    void logEvent(const QString &event, const QString &message);

private slots:
    /* Connection */
    void onConnected();
    void onDisconnected();

    /* Events */
    void onPlayerJoinEvent(const QString &player);
    void onPlayerLeaveEvent(const QString &player, const QString &info);

    /* Commands */
    // Misc
    void onLoginHashedCommand(bool auth);
    void onServerInfoCommand(const QStringList &serverInfo);
    void onAdminListPlayersCommand(const PlayerList &playerList);
    void onVarsServerNameCommand(const QString &serverName);
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsBannerUrlCommand(const QString &bannerUrl);
    void onMapListListCommand(const QStringList &mapList);
    void onMapListNextLevelIndexCommand(int index);
    void onReservedSlotsListCommand(const QStringList &reservedSlotList);
    void onVarsTextChatModerationModeCommand(const QString &mode);
    void onVarsTextChatSpamTriggerCountCommand(int count);
    void onVarsTextChatSpamDetectionTimeCommand(int count);
    void onVarsTextChatSpamCoolDownTimeCommand(int count);
    void onVarsIdleTimeoutCommand(int seconds);

    /* User Interface */
    /* Players */
    void treeWidget_pl_players_customContextMenuRequested(const QPoint &pos);
    void action_pl_sendmessage_triggered();
    void action_pl_textchatmoderation_muted_triggered();
    void action_pl_textchatmoderation_normal_triggered();
    void action_pl_textchatmoderation_voice_triggered();
    void action_pl_textchatmoderation_admin_triggered();
    void action_pl_kill_triggered();
    void action_pl_kick_custom_triggered();
    void action_pl_ban_byname_triggered();
    void action_pl_reservedslots_triggered();

    /* Options Tab */
    void lineEdit_op_so_serverName_editingFinished();
    void lineEdit_op_so_serverDescription_editingFinished();
    void lineEdit_op_so_bannerUrl_editingFinished();

    void checkbox_op_go_hardcore_clicked();
    void checkbox_op_go_crossHair_clicked();
    void checkbox_op_go_teamBalance_clicked();
    void checkbox_op_go_3dSpotting_clicked();
    void checkbox_op_go_friendlyFire_clicked();
    void checkbox_op_go_miniMapSpotting_clicked();
    void checkbox_op_go_killCam_clicked();
    void checkbox_op_go_thirdPersonVehicleCameras_clicked();
    void checkbox_op_go_miniMap_clicked();

    void on_spinBox_op_gpo_idleTimeout_editingFinished();

    void on_radioButton_op_tcm_free_clicked();
    void on_radioButton_op_tcm_moderated_clicked();
    void on_radioButton_op_tcm_muted_clicked();

    /* Maplist */
    void comboBox_ml_gamemode_currentIndexChanged(int index);
    void listWidget_ml_avaliablemaps_currentItemChanged(QListWidgetItem*, QListWidgetItem*);
    void listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem* current);
    void on_pushButton_ml_add_clicked();
    void on_pushButton_ml_remove_clicked();
    void on_pushButton_ml_restart_clicked();
    void on_pushButton_ml_run_clicked();
    void on_pushButton_ml_clear_clicked();
    void on_pushButton_ml_save_clicked();

    /* Reserved Slots Tab */
    void listWidget_rs_customContextMenuRequested(const QPoint &pos);
    void action_rs_remove_triggered();
    void on_pushButton_rs_reserve_clicked();
    void on_pushButton_rs_load_clicked();
    void on_pushButton_rs_save_clicked();
    void on_pushButton_rs_clear_clicked();

    // TODO: Look over this.
    void slotMovePlayerTeam();
    void slotAddMapToServer(const QString &map);
    void slotRemoveMapFromServer(const QString &map);
    void slotChangePlayerTeam(const QString &player, const QString &alTeam);
    void refreshPlayerList();
    void playerListUpdate(int);

    // Other stuff.
    void setMapList(const QString &gamemode);

};

#endif // BFBC2WIDGET_H
