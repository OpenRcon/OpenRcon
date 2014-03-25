#ifndef BFBC2WIDGET_H
#define BFBC2WIDGET_H

#include <QSettings>
#include <QMenu>
#include <QCompleter>
#include <QTime>
#include <QInputDialog>
#include <QDesktopServices>

#include "Game.h"

#include "ui_BFBC2.h"
#include "BFBC2.h"
#include "BFBC2Constants.h"

using namespace BFBC2Constants;

class BFBC2Widget : public BFBC2
{
    Q_OBJECT

public:
    explicit BFBC2Widget(const QString &host, const int &port, const QString &password);
    ~BFBC2Widget();

private:
    Ui::BFBC2 *ui;

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

    QStringList commandList;
    QCompleter *completer;

    QMenu *menu_pl;
    QMenu *menu_pl_ban;
    QMenu *menu_pl_kick;
    QMenu *menu_pl_move;
    QMenu *menu_pl_textchatmoderation;
    QMenu *menu_bl;
    QMenu *menu_rs;
    QMenu *menu_ic;

    QSettings *settings;

    void readSettings();
    void writeSettings();

    void logMessage(const int &type, const QString &message);

private slots:
    void slotOnDataSent(const QString &command);
    void slotOnDataReceived(const QString &response);

    /* Event signals */
    void slotOnPlayerJoin(const QString &player);
    void slotOnPlayerAuthenticated(const QString &player, const QString &guid);
    void slotOnPlayerLeave(const QString &player, const QString &info);
    void slotOnPlayerSpawn(const QString &player, const QString &kit, const QStringList &weapons);
    void slotOnPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot);
    void slotOnPlayerChat(const QString &player, const QString &message, const QString &target);
    void slotOnPlayerKicked(const QString &player, const QString &reason);
    void slotOnPlayerSquadChange(const QString &player, const int &teamId, const int &squadId);
    void slotOnPlayerTeamChange(const QString &player, const int &teamId, const int &squadId);
    void slotOnPunkBusterMessage(const QString &message);
    void slotOnPunkBusterVersion(const QString &version);
    void slotOnServerLoadingLevel(const QString &levelName, const int &roundsPlayed, const int &roundsTotal);
    void slotOnServerLevelStarted();
    void slotOnServerRoundOver(const int &winningTeamId);
    void slotOnServerRoundOverPlayers(const QString &playerInfo);
    void slotOnServerRoundOverTeamScores(const QString &teamScores);

    // TODO: Look over this.
    void slotMovePlayerTeam();
    void slotPlayerListChange();
    void slotAddMapToServer(const QString &map);
    void slotRemoveMapFromServer(const QString &map);
    void slotChangePlayerTeam(const QString &player, const QString &alTeam);
    void refreshPlayerList();
    void blockPlayerList();
    void playerListUpdate(int);

    // Commands
    void slotServerInfoCommand(const QStringList &serverInfo);

    void slotVarsServerNameCommand(const QString &serverName);
    void slotVarsServerDescriptionCommand(const QString &serverDescription);
    void slotVarsBannerUrlCommand(const QString &bannerUrl);

    void slotMapListListCommand(const QStringList &mapList);
    void slotMapListNextLevelIndexCommand(const int &index);
    void slotBanListListCommand(const QStringList &banList);
    void slotReservedSlotsListCommand(const QStringList &reservedSlotList);

    void slotVarsTextChatModerationModeCommand(const QString &mode);
    void slotVarsTextChatSpamTriggerCountCommand(const int &count);
    void slotVarsTextChatSpamDetectionTimeCommand(const int &count);
    void slotVarsTextChatSpamCoolDownTimeCommand(const int &count);

    // Other stuff.
    void setMapList(const QString &gamemode);

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

    void on_checkbox_hardcore_mode_clicked();
    void on_checkbox_crosshair_clicked();
    void on_checkbox_team_auto_balance_clicked();
    void on_checkbox_3D_spotting_clicked();
    void on_checkbox_friendly_fire_clicked();
    void on_checkbox_minimap_spotting_clicked();
    void on_checkbox_killcam_clicked();
    void on_checkbox_3rd_person_vehicle_cameras_clicked();
    void on_checkbox_minimap_clicked();

};

#endif // BFBC2WIDGET_H
