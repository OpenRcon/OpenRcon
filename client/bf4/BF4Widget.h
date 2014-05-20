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

#include <QMenu>
#include <QClipboard>
#include <QTimer>
#include <QCompleter>

#include "BF4.h"
#include "FrostbiteConnection.h"
#include "PlayerSubset.h"
#include "PlayerInfo.h"
#include "LevelEntry.h"
#include "BF4GameModeEntry.h"
#include "BF4ServerInfo.h"
#include "BanListEntry.h"
#include "MapListEntry.h"

namespace Ui {
    class BF4Widget;
}

class BF4Widget : public BF4
{
    Q_OBJECT

public:
    BF4Widget(ServerEntry *serverEntry);
    ~BF4Widget();

    virtual Connection *getConnection() { return con; }

private:
    Ui::BF4Widget *ui;

    /* User Interface */
    // ServerInfo
    QTimer *timerServerInfoRoundTime;
    QTimer *timerServerInfoUpTime;
    int roundTime;
    int serverUpTime;

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

    // Maplist
    QMenu *menu_ml_available;
    QAction *action_ml_available_add;

    QMenu *menu_ml_current;
    QAction *action_ml_current_remove;

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

    LevelEntry currentLevel;
    BF4GameModeEntry currentGameMode;

    void setAuthenticated(bool auth);
    void startupCommands(bool auth);
    void logEvent(const QString &event, const QString &message);
    void logChat(const QString &sender, const QString &message, const QString &target);
    void logConsole(int type, const QString &message);

    QIcon getRankIcon(int rank);

    // Events
    void addEvent(const QString &event, const QString &message);

private slots:
    /* Connection */
    void onConnected();
    void onDisconnected();

    /* Events */
    void onDataSentEvent(const QString &request);
    void onDataReceivedEvent(const QString &response);

    void onPlayerAuthenticatedEvent(const QString &player);
    void onPlayerDisconnectEvent(const QString &player);
    void onPlayerJoinEvent(const QString &player, const QString &guid);
    void onPlayerLeaveEvent(const QString &player, const QString &info);
    void onPlayerSpawnEvent(const QString &player, int teamdId);
    void onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot);
    void onPlayerChatEvent(const QString &sender, const QString &message, const QString &target);
    void onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId);
    void onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId);
    void onPunkBusterMessageEvent(const QString &message);
    void onServerMaxPlayerCountChangeEvent();
    void onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal);
    void onServerRoundOverEvent(int winningTeamId);
    void onServerRoundOverPlayersEvent(const QString &playerInfo);
    void onServerRoundOverTeamScoresEvent(const QString &teamScores);

    /* Commands */
    // Misc
    void onLoginHashedCommand(bool auth);
    void onVersionCommand(const QString &type, int build);
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);
    void onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);

    // Admin
    void onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);
    void onAdminPasswordCommand(const QString &password);

    // Banning
    void onBanListListCommand(const BanList &banList);

    // FairFight
    void onFairFightIsActiveCommand(bool isActive);

    // Maplist
    void onMapListListCommand(const MapList &mapList);

    // Player

    // Punkbuster
    void onPunkBusterIsActiveCommand(bool active);

    // Reserved Slots
    void onReservedSlotsListAggressiveJoinCommand(bool enabled);
    void onReservedSlotsListListCommand(const QStringList &reservedSlotsList);

    // Spectator list
    void onSpectatorListListCommand(const QStringList &spectatorList);

    // Squad

    // Variables
    void onVars3dSpottingCommand(bool enabled);
    void onVars3pCamCommand(bool enabled);
    void onVarsAlwaysAllowSpectatorsCommand(bool enabled);
    void onVarsAutoBalanceCommand(bool enabled);
    void onVarsBulletDamageCommand(int percent);
    void onVarsCommanderCommand(bool enabled);
    void onVarsForceReloadWholeMagsCommand(bool enabled);
    void onVarsFriendlyFireCommand(bool enabled);
    void onVarsGameModeCounterCommand(int percent);
    void onVarsGamePasswordCommand(const QString &password);
    void onVarsHitIndicatorsEnabledCommand(bool enabled);
    void onVarsHudCommand(bool enabled);
    void onVarsIdleBanRoundsCommand(int rounds);
    void onVarsIdleTimeoutCommand(int timeout);
    void onVarsKillCamCommand(bool enabled);
    void onVarsMaxPlayersCommand(int playerCount);
    void onVarsMaxSpectatorsCommand(int spectatorCount);
    void onVarsMiniMapCommand(bool enabled);
    void onVarsMiniMapSpottingCommand(bool enabled);
    void onVarsNameTagCommand(bool enabled);
    void onVarsOnlySquadLeaderSpawnCommand(bool enabled);
    void onVarsPlayerRespawnTimeCommand(int respawnTime);
    void onVarsRegenerateHealthCommand(bool enabled);
    void onVarsRoundLockdownCountdownCommand(int seconds);
    void onVarsRoundRestartPlayerCountCommand(int players);
    void onVarsRoundStartPlayerCountCommand(int players);
    void onVarsRoundTimeLimitCommand(int percentage);
    void onVarsRoundWarmupTimeoutCommand(int timeout);
    void onVarsServerNameCommand(const QString &serverName);
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsServerMessageCommand(const QString &serverMessage);
    void onVarsServerTypeCommand(const QString &type);
    void onVarsSoldierHealthCommand(int health);
    void onVarsTicketBleedRateCommand(int percent);
    void onVarsVehicleSpawnAllowedCommand(bool enabled);
    void onVarsVehicleSpawnDelayCommand(int delay);

    /* User Interface */
    // Server Information
    void pushButton_si_restartRound_clicked();
    void pushButton_si_runNextRound_clicked();
    void updateRoundTime();
    void updateUpTime();

    // Players
    void updatePlayerList();
    void listPlayers(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset);
    void treeWidget_pl_players_customContextMenuRequested(const QPoint &pos);
    void action_pl_players_kill_triggered();
    void action_pl_players_kick_triggered();
    void action_pl_players_ban_triggered();
    void action_pl_players_reserveSlot_triggered();
    void action_pl_players_copyTo_name_triggered();
    void action_pl_players_copyTo_guid_triggered();

    void menu_pl_players_move_triggered(QAction *action);

    // Chat
    void comboBox_ch_mode_currentIndexChanged(int index);
    void pushButton_ch_send_clicked();

    // Maplist
    void comboBox_ml_gameMode_currentIndexChanged(int);
    void treeWidget_ml_available_itemSelectionChanged();
    void treeWidget_ml_available_customContextMenuRequested(const QPoint &pos);
    void pushButton_ml_add_clicked();
    void pushButton_ml_remove_clicked();
    void treeWidget_ml_current_itemSelectionChanged();
    void treeWidget_ml_current_customContextMenuRequested(const QPoint &pos);

    void addAvailableMapListRow(const QString &name, const QString &gameMode);
    void setAvailableMaplist(int gameModeIndex);
    void addCurrentMapListRow(const QString &name, const QString &gameMode, int rounds);
    void setCurrentMaplist(const MapList &mapList);

    // BanList
    void tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos);
    void action_bl_banList_remove_triggered();
    void addBanListRow(const QString &idType, const QString &id, const QString &banType, int seconds, int rounds, const QString &reason);
    void setBanlist(const BanList &banList);

    // Reserved Slots
    void listWidget_rs_reservedSlotsList_customContextMenuRequested(const QPoint &pos);
    void action_rs_reservedSlotsList_remove_triggered();
    void pushButton_rs_add_clicked();
    void pushButton_rs_load_clicked();
    void pushButton_rs_save_clicked();
    void pushButton_rs_clear_clicked();

    // Spectator List
    void listWidget_ss_spectatorList_customContextMenuRequested(const QPoint &pos);
    void action_ss_spectatorList_remove_triggered();
    void pushButton_ss_add_clicked();
    void pushButton_ss_save_clicked();
    void pushButton_ss_clear_clicked();

    // Options -> Details
    void lineEdit_op_so_serverName_editingFinished();
    void textEdit_op_so_serverDescription_textChanged();
    void lineEdit_op_so_serverMessage_editingFinished();

    // Options -> Configuration
    void checkBox_so_co_punkBuster_toggled(bool checked);
    void checkBox_so_co_fairFight_toggled(bool checked);
    void checkBox_so_co_idleTimeout_toggled(bool checked);
    void spinBox_so_co_idleTimeout_valueChanged(int value);
    void checkBox_so_co_idleBanRounds_toggled(bool checked);
    void spinBox_so_co_idleBanRounds_valueChanged(int value);
    void checkBox_so_co_aggressiveJoin_toggled(bool checked);
    void spinBox_so_co_maxPlayers_valueChanged(int value);
    void spinBox_so_co_maxSpectators_valueChanged(int value);
    void checkBox_so_co_alwaysAllowSpectators_toggled(bool checked);
    void checkBox_so_co_commander_toggled(bool checked);

    // Options -> Gameplay
    void checkBox_so_gp_friendlyFire_toggled(bool checked);
    void checkBox_so_gp_autoBalance_toggled(bool checked);
    void checkBox_so_gp_killCam_toggled(bool checked);
    void checkBox_so_gp_miniMap_toggled(bool checked);
    void checkBox_so_gp_miniMapSpotting_toggled(bool checked);
    void checkBox_so_gp_3dSpotting_toggled(bool checked);
    void checkBox_so_gp_nameTag_toggled(bool checked);
    void checkBox_so_gp_regenerateHealth_toggled(bool checked);
    void checkBox_so_gp_hud_toggled(bool checked);
    void checkBox_so_gp_onlySquadLeaderSpawn_toggled(bool checked);
    void checkBox_so_gp_vehicleSpawnAllowed_toggled(bool checked);
    void checkBox_so_gp_hitIndicatorsEnabled_toggled(bool checked);
    void checkBox_so_gp_thirdPersonVehicleCameras_toggled(bool checked);
    void checkBox_so_gp_forceReloadWholeMags_toggled(bool checked);
    void spinBox_so_gp_bulletDamage_valueChanged(int value);
    void spinBox_so_gp_soldierHealth_valueChanged(int value);
    void spinBox_so_gp_vehicleSpawnDelay_valueChanged(int value);
    void spinBox_so_gp_playerRespawnTime_valueChanged(int value);
    void spinBox_so_gp_ticketBleedRate_valueChanged(int value);
    void spinBox_so_gp_gameModeCounter_valueChanged(int value);
    void spinBox_so_gp_roundTimeLimit_valueChanged(int value);
    void spinBox_so_gp_roundLockdownCountdown_valueChanged(int value);
    void spinBox_so_gp_roundWarmupTimeout_valueChanged(int value);
    void spinBox_so_gp_roundRestartPlayerCount_valueChanged(int value);
    void spinBox_so_gp_roundStartPlayerCount_valueChanged(int value);

    // Console
    void pushButton_co_co_clicked();
    void pushButton_co_pb_clicked();

};

#endif // BF3WIDGET_H
