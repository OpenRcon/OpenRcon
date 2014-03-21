/*
 * Copyright (C) 2010 The OpenRcon Project.
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

#ifndef BFBC2_H
#define BFBC2_H

#include <QObject>
#include <QCompleter>
#include <QInputDialog>
#include <QMenu>
#include <QTimer>
#include <QTime>
#include <QStringList>
#include <QMap>
#include <QSettings>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QTime>

#include "ui_BFBC2.h"

#include "Constants.h"
#include "ConnectionTabWidget.h"

#include "BFBC2Constants.h"
#include "BFBC2Connection.h"
#include "BFBC2Levels.h"
#include "BFBC2CommandList.h"

using namespace Constants;
using namespace BFBC2Constants;

class BFBC2 : public ConnectionTabWidget
{
    Q_OBJECT

public:
    BFBC2(const QString &host, const int &port, const QString &password);
    ~BFBC2();

    virtual Connection *getConnection() { return con; }

    QStringList mapListU;

private:
    Ui::BFBC2 *ui;

    BFBC2Connection *con;
    BFBC2Levels *levelsObject;
    BFBC2CommandList *comList;

    QSettings *settings;

    void readSettings();
    void writeSettings();

    bool auth;

    QHostAddress host;
    int port;
    QString password;

    QString currentMod;
    QString currentGamemode;
    QStringList gameModeCode;

    int nextLevelIndex;

    QString getMapName(const QString &mapPath, const QString &gamemode) const;
    QString getMapImage(const QString &mapPath, const QString &gamemode) const;

    void setMapList(const QString &gamemode);

    QCompleter *completer;
    QTimer *commandRefreshTimer;

    QAction *action_pl_sendmessage;
    QAction *action_pl_stats;
    QAction *action_pl_textchatmoderation_muted;
    QAction *action_pl_textchatmoderation_normal;
    QAction *action_pl_textchatmoderation_voice;
    QAction *action_pl_textchatmoderation_admin;
    QAction *action_pl_kill;
    QAction *action_pl_kick_custom;
    QAction *action_pl_ban_byname;
    QAction *action_pl_reservedslots;
    QAction *action_pl_admin;

    QAction *action_bl_remove;
    QAction *action_rs_remove;
    QAction *action_ic_remove;

    QMenu *menu_pl;
    QMenu *menu_pl_ban;
    QMenu *menu_pl_kick;
    QMenu *menu_pl_move;
    QMenu *menu_pl_textchatmoderation;
    QMenu *menu_bl;
    QMenu *menu_rs;
    QMenu *menu_ic;

    QStringList gamemodes;

private slots: 
    void slotLogMessage(const QString &type, const QString &msg);
    void slotLogEvents(const QString &event, const QString &msg);
    void slotIngameCommands(const QString &player, const QString &cmd);
    void slotStartConnection();
    void slotGotSalt(const QByteArray &salt);
    void slotAuthenticated();
    void slotMovePlayerTeam();
    void slotPlayerListChange();
    void slotAddMapToServer(const QString &map);
    void slotRemoveMapFromServer(const QString &map);
    void slotChangePlayerTeam(const QString &player, const QString &alTeam);
    void refreshPlayerList();
    void blockPlayerList();
    void playerListUpdate(int);

    void slotStartupCommands();
    void slotRefreshCommands();

    // Events
    void slotEventOnSpawn(const QString &player, const QString &kit);

    // Commands
    void slotCommandServerInfo(QStringList si);
    void slotCommandVarsTextChatModerationMode(const QString &tcmm);
    void slotCommandVarsTextChatSpamTriggerCount(const QString &tcstc);
    void slotCommandVarsTextChatSpamDetectionTime(const QString &tcsdt);
    void slotCommandVarsTextChatSpamCoolDownTime(const QString &tcscdt);
    void slotCommandBanListList(QStringList bl);
    void slotCommandReservedSlotsList(QStringList rl);
    void slotCommandMapListList(QStringList ml);
    void slotCommandMapListListRounds(QStringList ml);
    void slotCommandMapListNextLevelIndex(int &nm);
    void slotCommandVarsServerName(const QString &sn);
    void slotCommandVarsServerDescription(const QString &sd);
    void slotCommandVarsBannerUrl(const QString &bu);

    void authenticate(const QByteArray& pwd, const QByteArray& salt);

    void sendSayMessage(const QString &msg, const QString &group, const QString &target1, const QString &target2);
    void sendYellMessage(const QString &msg, const QString &duration, const QString &group, const QString &target1, const QString &target2);

    void killPlayer(const QString &player);
    void kickPlayer(const QString &player, const QString &reason);
    void banPlayer(const QString &type, const QString &id, const QString &timeout, const QString &reason);
    void unbanPlayer(const QString &type, const QString &id);
    void movePlayer(const QString &player, const QString &teamId, const QString &squadId, const QString &fk);
    void reservePlayer(const QString &player);
    void unReservePlayer(const QString &player);

    void treeWidget_pl_customContextMenuRequested(QPoint pos);

    void action_pl_sendmessage_triggered();
    void action_pl_textchatmoderation_muted_triggered();
    void action_pl_textchatmoderation_normal_triggered();
    void action_pl_textchatmoderation_voice_triggered();
    void action_pl_textchatmoderation_admin_triggered();
    void action_pl_stats_triggered();
    void action_pl_kill_triggered();
    void action_pl_kick_custom_triggered();
    void action_pl_ban_byname_triggered();
    void action_pl_reservedslots_triggered();

    void comboBox_ml_gamemode_currentIndexChanged(int index);
    void listWidget_ml_avaliablemaps_currentItemChanged(QListWidgetItem*, QListWidgetItem*);
    void listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem* current);
    void listWidget_bl_customContextMenuRequested(QPoint); 
    void comboBox_ch_type_currentIndexChanged(int index);
    void action_bl_remove_triggered();
    void listWidget_rs_customContextMenuRequested(QPoint);
    void action_rs_remove_triggered();
    void listWidget_ic_customContextMenuRequested(QPoint);
    void action_ic_remove_triggered();

    void on_pushButton_op_so_servername_apply_clicked();
    void on_pushButton_op_so_serverdescription_apply_clicked();
    void on_pushButton_op_so_bannerurl_apply_clicked();
    void on_pushButton_so_tcm_spamtriggercount_clicked();
    void on_pushButton_so_tcm_spamdetectiontime_clicked();
    void on_pushButton_so_tcm_spamcooldowntime_clicked();
    void on_pushButton_ml_add_clicked();
    void on_pushButton_ml_remove_clicked();
    void on_pushButton_ml_restart_clicked();
    void on_pushButton_ml_run_clicked();
    void on_pushButton_ml_clear_clicked();
    void on_pushButton_ml_save_clicked();
    void on_pushButton_bl_ban_clicked();
    void on_pushButton_bl_clear_clicked();
    void on_pushButton_bl_save_clicked();
    void on_pushButton_ch_send_clicked();
    void on_pushButton_rs_reserve_clicked();
    void on_pushButton_rs_clear_clicked();
    void on_pushButton_rs_save_clicked();
    void on_pushButton_ic_add_clicked();
    void on_pushButton_co_co_send_clicked();
    void on_pushButton_co_pb_send_clicked();

    void on_radioButton_op_tcm_free_clicked();
    void on_radioButton_op_tcm_moderated_clicked();
    void on_radioButton_op_tcm_muted_clicked();

    void on_checkbox_hardcore_mode();
    void on_checkbox_crosshair();
    void on_checkbox_team_auto_balance();
    void on_checkbox_3D_spotting();
    void on_checkbox_friendly_fire();
    void on_checkbox_minimap_spotting();
    void on_checkbox_killcam();
    void on_checkbox_3rd_person_vehicle_cameras();
    void on_checkbox_minimap();

};

#endif // BFBC2_H
