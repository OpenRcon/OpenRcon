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

private slots:
    void slotLogMessage(const QString &type, const QString &msg);
    void slotLogEvents(const QString &event, const QString &msg);

    void slotMovePlayerTeam();
    void slotPlayerListChange();
    void slotAddMapToServer(const QString &map);
    void slotRemoveMapFromServer(const QString &map);
    void slotChangePlayerTeam(const QString &player, const QString &alTeam);
    void refreshPlayerList();
    void blockPlayerList();
    void playerListUpdate(int);

    // Commands
    void slotCommandServerInfo(QStringList si);
    void slotCommandVarsTextChatModerationMode(const QString &tcmm);
    void slotCommandVarsTextChatSpamTriggerCount(const QString &tcstc);
    void slotCommandVarsTextChatSpamDetectionTime(const QString &tcsdt);
    void slotCommandVarsTextChatSpamCoolDownTime(const QString &tcscdt);
    void slotCommandBanListList(QStringList bl);
    void slotCommandReservedSlotsList(QStringList rl);
    void slotCommandMapListList(QStringList ml);

    void slotCommandMapListNextLevelIndex(int &nm);
    void slotCommandVarsServerName(const QString &sn);
    void slotCommandVarsServerDescription(const QString &sd);
    void slotCommandVarsBannerUrl(const QString &bu);

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

#endif // BFBC2WIDGET_H
