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

#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>

class FrostbiteConnection;
class BF4CommandHandler;
enum class BF4PresetType;

namespace Ui {
    class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    OptionsWidget(FrostbiteConnection *connection, QWidget *parent = nullptr);
    ~OptionsWidget();

private:
    Ui::OptionsWidget *ui;
    FrostbiteConnection *m_connection;
    BF4CommandHandler *m_commandHandler;

private slots:
    /* Commands */
    // Misc
    void onLoginHashedCommand(bool auth);

    // Admin
    void onAdminPasswordCommand(const QString &password);

    // FairFight
    void onFairFightIsActiveCommand(bool isActive);

    // Punkbuster
    void onPunkBusterIsActiveCommand(bool active);

    // Reserved Slots
    void onReservedSlotsListAggressiveJoinCommand(bool enabled);

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
    void onVarsPresetCommand(const BF4PresetType &presetType, bool lockPresetSetting);
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
    void onVarsUnlockModeCommand(const QString &type);
    void onVarsVehicleSpawnAllowedCommand(bool enabled);
    void onVarsVehicleSpawnDelayCommand(int delay);

    /* User Interface */
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
    void comboBox_so_gp_preset_currentIndexChanged(const QString &text);
    void checkBox_so_gp_presetLockPresetSetting_toggled(bool checked);
    void comboBox_so_gp_unlockMode_currentIndexChanged(int index);

};

#endif // OPTIONSWIDGET_H
