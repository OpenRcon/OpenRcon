/*
 * Copyright (C) 2016 The OpenRcon Project.
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

#ifndef BF4OPTIONSWIDGET_H
#define BF4OPTIONSWIDGET_H

#include "BF4Widget.h"

enum class Frostbite2UnlockModeEnum;
enum class BF4PresetEnum;
enum class BF4ServerTypeEnum;

namespace Ui {
    class BF4OptionsWidget;
}

class BF4OptionsWidget : public BF4Widget
{
    Q_OBJECT

public:
    BF4OptionsWidget(BF4Client *client, QWidget *parent = nullptr);
    ~BF4OptionsWidget() final;

private:
    Ui::BF4OptionsWidget *ui;

private slots:
    /* Client */
    void onAuthenticated();

    /* Commands */
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
    void onVarsPresetCommand(const BF4PresetEnum &preset, bool lockPresetSetting);
    void onVarsRegenerateHealthCommand(bool enabled);
    void onVarsRoundLockdownCountdownCommand(int seconds);
    void onVarsRoundRestartPlayerCountCommand(int players);
    void onVarsRoundStartPlayerCountCommand(int players);
    void onVarsRoundTimeLimitCommand(int percentage);
    void onVarsRoundWarmupTimeoutCommand(int timeout);
    void onVarsServerNameCommand(const QString &serverName);
    void onVarsServerDescriptionCommand(const QString &serverDescription);
    void onVarsServerMessageCommand(const QString &serverMessage);
    void onVarsServerTypeCommand(const BF4ServerTypeEnum &serverType);
    void onVarsSoldierHealthCommand(int health);
    void onVarsTicketBleedRateCommand(int percent);
    void onVarsUnlockModeCommand(const Frostbite2UnlockModeEnum &unlockMode);
    void onVarsVehicleSpawnAllowedCommand(bool enabled);
    void onVarsVehicleSpawnDelayCommand(int delay);
    void onVarsRoundPlayersReadyBypassTimerCommand(int timer);
    void onVarsRoundPlayersReadyMinCountCommand(int count);
    void onVarsRoundPlayersReadyPercentCommand(int percent);

    /* User Interface */
    // Options -> Details
    void lineEdit_details_serverName_editingFinished();
    void textEdit_details_serverDescription_textChanged();
    void lineEdit_details_serverMessage_editingFinished();

    // Options -> Configuration
    void checkBox_configuration_punkBuster_toggled(bool checked);
    void checkBox_configuration_fairFight_toggled(bool checked);
    void spinBox_configuration_maxPlayers_valueChanged(int value);
    void spinBox_configuration_maxSpectators_valueChanged(int value);
    void checkBox_configuration_alwaysAllowSpectators_toggled(bool checked);
    void lineEdit_configuration_gamePassword_editingFinished();
    void lineEdit_configuration_adminPassword_editingFinished();
    void checkBox_configuration_idleTimeout_toggled(bool checked);
    void spinBox_configuration_idleTimeout_valueChanged(int value);
    void checkBox_configuration_idleBanRounds_toggled(bool checked);
    void spinBox_configuration_idleBanRounds_valueChanged(int value);
    void checkBox_configuration_aggressiveJoin_toggled(bool checked);
    void checkBox_configuration_commander_toggled(bool checked);

    // Options -> Gameplay
    void checkBox_gameplay_friendlyFire_toggled(bool checked);
    void checkBox_gameplay_autoBalance_toggled(bool checked);
    void checkBox_gameplay_killCam_toggled(bool checked);
    void checkBox_gameplay_miniMap_toggled(bool checked);
    void checkBox_gameplay_miniMapSpotting_toggled(bool checked);
    void checkBox_gameplay_3dSpotting_toggled(bool checked);
    void checkBox_gameplay_nameTag_toggled(bool checked);
    void checkBox_gameplay_regenerateHealth_toggled(bool checked);
    void checkBox_gameplay_hud_toggled(bool checked);
    void checkBox_gameplay_onlySquadLeaderSpawn_toggled(bool checked);
    void checkBox_gameplay_vehicleSpawnAllowed_toggled(bool checked);
    void checkBox_gameplay_hitIndicatorsEnabled_toggled(bool checked);
    void checkBox_gameplay_thirdPersonVehicleCameras_toggled(bool checked);
    void checkBox_gameplay_forceReloadWholeMags_toggled(bool checked);
    void spinBox_gameplay_bulletDamage_valueChanged(int value);
    void spinBox_gameplay_soldierHealth_valueChanged(int value);
    void spinBox_gameplay_vehicleSpawnDelay_valueChanged(int value);
    void spinBox_gameplay_playerRespawnTime_valueChanged(int value);
    void spinBox_gameplay_ticketBleedRate_valueChanged(int value);
    void spinBox_gameplay_gameModeCounter_valueChanged(int value);
    void spinBox_gameplay_roundTimeLimit_valueChanged(int value);
    void spinBox_gameplay_roundLockdownCountdown_valueChanged(int value);
    void spinBox_gameplay_roundWarmupTimeout_valueChanged(int value);
    void spinBox_gameplay_roundRestartPlayerCount_valueChanged(int value);
    void spinBox_gameplay_roundStartPlayerCount_valueChanged(int value);
    void spinBox_gameplay_roundPlayersReadyBypassTimer(int value);
    void spinBox_gameplay_roundPlayersReadyMinCount(int value);
    void spinBox_gameplay_roundPlayersReadyPercent(int value);
    void comboBox_gameplay_preset_currentIndexChanged(const QString &text);
    void checkBox_gameplay_presetLockPresetSetting_toggled(bool checked);
    void comboBox_gameplay_unlockMode_currentIndexChanged(int index);
};

#endif // BF4OPTIONSWIDGET_H
