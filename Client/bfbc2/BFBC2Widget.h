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
    QAction *action_pl_move;

    QAction *action_bl_remove;
    QAction *action_rs_remove;
    QAction *action_ic_remove;

    QStringList squadNameList;
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
    void onDataSent(const QString &command);
    void onDataReceived(const QString &response);
    void onAuthenticated();

    /* Event signals */
    void onPlayerJoin(const QString &player);
    void onPlayerAuthenticated(const QString &player, const QString &guid);
    void onPlayerLeave(const QString &player, const QString &info);
    void onPlayerSpawn(const QString &player, const QString &kit, const QStringList &weapons);
    void onPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot);
    void onPlayerChat(const QString &player, const QString &message, const QString &target);
    void onPlayerKicked(const QString &player, const QString &reason);
    void onPlayerSquadChange(const QString &player, const int &teamId, const int &squadId);
    void onPlayerTeamChange(const QString &player, const int &teamId, const int &squadId);
    void onPunkBusterMessage(const QString &message);
    void onPunkBusterVersion(const QString &version);
    void onServerLoadingLevel(const QString &levelName, const int &roundsPlayed, const int &roundsTotal);
    void onServerLevelStarted();
    void onServerRoundOver(const int &winningTeamId);
    void onServerRoundOverPlayers(const QString &playerInfo);
    void onServerRoundOverTeamScores(const QString &teamScores);

    // Commands
    void onServerInfoCommand(const QStringList &serverInfo);
    void onAdminListPlayersCommand(const PlayerList &playerList);
    void onVarsServerNameCommand(const QString &serverName);
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsBannerUrlCommand(const QString &bannerUrl);
    void onMapListListCommand(const QStringList &mapList);
    void onMapListNextLevelIndexCommand(const int &index);
    void onBanListListCommand(const QStringList &banList);
    void onReservedSlotsListCommand(const QStringList &reservedSlotList);
    void onVarsTextChatModerationModeCommand(const QString &mode);
    void onVarsTextChatSpamTriggerCountCommand(const int &count);
    void onVarsTextChatSpamDetectionTimeCommand(const int &count);
    void onVarsTextChatSpamCoolDownTimeCommand(const int &count);
    void onVarsIdleTimeoutCommand(const int &seconds);

    QString getSquadName(const int &id);

    void startupCommands();
    // TODO: Look over this.
    void slotMovePlayerTeam();
    void slotAddMapToServer(const QString &map);
    void slotRemoveMapFromServer(const QString &map);
    void slotChangePlayerTeam(const QString &player, const QString &alTeam);
    void refreshPlayerList();
    void playerListUpdate(int);

    // Other stuff.
    void setMapList(const QString &gamemode);

    /* User Interface */

    /* Options Tab */

    /* Server Options */
    void lineEdit_op_so_serverName_editingFinished();
    void lineEdit_op_so_serverDescription_editingFinished();
    void lineEdit_op_so_bannerUrl_editingFinished();

    /* Game Options */
    void checkbox_op_go_hardcore_clicked();
    void checkbox_op_go_crossHair_clicked();
    void checkbox_op_go_teamBalance_clicked();
    void checkbox_op_go_3dSpotting_clicked();
    void checkbox_op_go_friendlyFire_clicked();
    void checkbox_op_go_miniMapSpotting_clicked();
    void checkbox_op_go_killCam_clicked();
    void checkbox_op_go_thirdPersonVehicleCameras_clicked();
    void checkbox_op_go_miniMap_clicked();

    /* Gameplay Options */
    void on_spinBox_op_gpo_idleTimeout_editingFinished();

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

};

#endif // BFBC2WIDGET_H
