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

#include "BF4OptionsWidget.h"
#include "ui_BF4OptionsWidget.h"

#include "BF4ServerType.h"
#include "Frostbite2UnlockMode.h"
#include "BF4Preset.h"

BF4OptionsWidget::BF4OptionsWidget(BF4Client *client, QWidget *parent) :
    BF4Widget(client, parent),
    ui(new Ui::BF4OptionsWidget)
{
    ui->setupUi(this);

    // Initialize preset comboBox with preset types.
    ui->comboBox_gameplay_preset->addItems(BF4Preset::asList());

    // Initialize unlock mode comboBox with unlock modes.
    for (QString unlockModeName : Frostbite2UnlockMode::asList()) {
        ui->comboBox_gameplay_unlockMode->addItem(unlockModeName, QVariant::fromValue(Frostbite2UnlockMode::fromString(unlockModeName)));
    }

    /* Client */
    connect(getClient(),                      &Client::onAuthenticated,                        this, &BF4OptionsWidget::onAuthenticated);

    /* Commands */
    // Admin
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onAdminPasswordCommand,      this, &BF4OptionsWidget::onAdminPasswordCommand);

    // FairFight
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onFairFightIsActiveCommand,  this, &BF4OptionsWidget::onFairFightIsActiveCommand);

    // Player

    // Punkbuster
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onPunkBusterIsActiveCommand, this, &BF4OptionsWidget::onPunkBusterIsActiveCommand);

    // Variables
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVars3dSpottingCommand,                   this, &BF4OptionsWidget::onVars3dSpottingCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVars3pCamCommand,                        this, &BF4OptionsWidget::onVars3pCamCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsAlwaysAllowSpectatorsCommand,        this, &BF4OptionsWidget::onVarsAlwaysAllowSpectatorsCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsAutoBalanceCommand,                  this, &BF4OptionsWidget::onVarsAutoBalanceCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsBulletDamageCommand,                 this, &BF4OptionsWidget::onVarsBulletDamageCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsCommanderCommand,                    this, &BF4OptionsWidget::onVarsCommanderCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsForceReloadWholeMagsCommand,         this, &BF4OptionsWidget::onVarsForceReloadWholeMagsCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsFriendlyFireCommand,                 this, &BF4OptionsWidget::onVarsFriendlyFireCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsGameModeCounterCommand,              this, &BF4OptionsWidget::onVarsGameModeCounterCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsGamePasswordCommand,                 this, &BF4OptionsWidget::onVarsGamePasswordCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsHitIndicatorsEnabledCommand,         this, &BF4OptionsWidget::onVarsHitIndicatorsEnabledCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsHudCommand,                          this, &BF4OptionsWidget::onVarsHudCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsIdleBanRoundsCommand,                this, &BF4OptionsWidget::onVarsIdleBanRoundsCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsIdleTimeoutCommand,                  this, &BF4OptionsWidget::onVarsIdleTimeoutCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsKillCamCommand,                      this, &BF4OptionsWidget::onVarsKillCamCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsMaxPlayersCommand,                   this, &BF4OptionsWidget::onVarsMaxPlayersCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsMaxSpectatorsCommand,                this, &BF4OptionsWidget::onVarsMaxSpectatorsCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsMiniMapCommand,                      this, &BF4OptionsWidget::onVarsMiniMapCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsMiniMapSpottingCommand,              this, &BF4OptionsWidget::onVarsMiniMapSpottingCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsNameTagCommand,                      this, &BF4OptionsWidget::onVarsNameTagCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsOnlySquadLeaderSpawnCommand,         this, &BF4OptionsWidget::onVarsOnlySquadLeaderSpawnCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsPlayerRespawnTimeCommand,            this, &BF4OptionsWidget::onVarsPlayerRespawnTimeCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsPresetCommand,                       this, &BF4OptionsWidget::onVarsPresetCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRegenerateHealthCommand,             this, &BF4OptionsWidget::onVarsRegenerateHealthCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRoundLockdownCountdownCommand,       this, &BF4OptionsWidget::onVarsRoundLockdownCountdownCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRoundRestartPlayerCountCommand,      this, &BF4OptionsWidget::onVarsRoundRestartPlayerCountCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRoundStartPlayerCountCommand,        this, &BF4OptionsWidget::onVarsRoundStartPlayerCountCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRoundTimeLimitCommand,               this, &BF4OptionsWidget::onVarsRoundTimeLimitCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRoundWarmupTimeoutCommand,           this, &BF4OptionsWidget::onVarsRoundWarmupTimeoutCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsServerNameCommand,                   this, &BF4OptionsWidget::onVarsServerNameCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsServerDescriptionCommand,            this, &BF4OptionsWidget::onVarsServerDescriptionCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsServerMessageCommand,                this, &BF4OptionsWidget::onVarsServerMessageCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsServerTypeCommand,                   this, &BF4OptionsWidget::onVarsServerTypeCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsSoldierHealthCommand,                this, &BF4OptionsWidget::onVarsSoldierHealthCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsTicketBleedRateCommand,              this, &BF4OptionsWidget::onVarsTicketBleedRateCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsUnlockModeCommand,                   this, &BF4OptionsWidget::onVarsUnlockModeCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsVehicleSpawnAllowedCommand,          this, &BF4OptionsWidget::onVarsVehicleSpawnAllowedCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsVehicleSpawnDelayCommand,            this, &BF4OptionsWidget::onVarsVehicleSpawnDelayCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRoundPlayersReadyBypassTimerCommand, this, &BF4OptionsWidget::onVarsRoundPlayersReadyBypassTimerCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRoundPlayersReadyMinCountCommand,    this, &BF4OptionsWidget::onVarsRoundPlayersReadyMinCountCommand);
    connect(getClient()->getCommandHandler(), &BF4CommandHandler::onVarsRoundPlayersReadyPercentCommand,     this, &BF4OptionsWidget::onVarsRoundPlayersReadyPercentCommand);

    /* User Interface */
    // Options -> Details
    connect(ui->lineEdit_details_serverName,        &QLineEdit::editingFinished, this, &BF4OptionsWidget::lineEdit_details_serverName_editingFinished);
    connect(ui->textEdit_details_serverDescription, &QTextEdit::textChanged,     this, &BF4OptionsWidget::textEdit_details_serverDescription_textChanged);
    connect(ui->lineEdit_details_serverMessage,     &QLineEdit::editingFinished, this, &BF4OptionsWidget::lineEdit_details_serverMessage_editingFinished);


    // Options -> Configuration
    connect(ui->checkBox_configuration_punkBuster,            &QCheckBox::toggled,                                           this, &BF4OptionsWidget::checkBox_configuration_punkBuster_toggled);
    connect(ui->checkBox_configuration_fairFight,             &QCheckBox::toggled,                                           this, &BF4OptionsWidget::checkBox_configuration_fairFight_toggled);
    connect(ui->spinBox_configuration_maxPlayers,             static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4OptionsWidget::spinBox_configuration_maxPlayers_valueChanged);
    connect(ui->spinBox_configuration_maxSpectators,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4OptionsWidget::spinBox_configuration_maxSpectators_valueChanged);
    connect(ui->checkBox_configuration_alwaysAllowSpectators, &QCheckBox::toggled,                                           this, &BF4OptionsWidget::checkBox_configuration_alwaysAllowSpectators_toggled);
    connect(ui->lineEdit_configuration_gamePassword,          &QLineEdit::editingFinished,                                   this, &BF4OptionsWidget::lineEdit_configuration_gamePassword_editingFinished);
    connect(ui->lineEdit_configuration_adminPassword,         &QLineEdit::editingFinished,                                   this, &BF4OptionsWidget::lineEdit_configuration_adminPassword_editingFinished);
    connect(ui->checkBox_configuration_idleTimeout,           &QCheckBox::toggled,                                           this, &BF4OptionsWidget::checkBox_configuration_idleTimeout_toggled);
    connect(ui->spinBox_configuration_idleTimeout,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4OptionsWidget::spinBox_configuration_idleTimeout_valueChanged);
    connect(ui->checkBox_configuration_idleBanRounds,         &QCheckBox::toggled,                                           this, &BF4OptionsWidget::checkBox_configuration_idleBanRounds_toggled);
    connect(ui->spinBox_configuration_idleBanRounds,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4OptionsWidget::spinBox_configuration_idleBanRounds_valueChanged);
    connect(ui->checkBox_configuration_aggressiveJoin,        &QCheckBox::toggled,                                           this, &BF4OptionsWidget::checkBox_configuration_aggressiveJoin_toggled);
    connect(ui->checkBox_configuration_commander,             &QCheckBox::toggled,                                           this, &BF4OptionsWidget::checkBox_configuration_commander_toggled);

    // Options -> Gameplay
    connect(ui->checkBox_gameplay_friendlyFire,                &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_friendlyFire_toggled);
    connect(ui->checkBox_gameplay_autoBalance,                 &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_autoBalance_toggled);
    connect(ui->checkBox_gameplay_killCam,                     &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_killCam_toggled);
    connect(ui->checkBox_gameplay_miniMap,                     &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_miniMap_toggled);
    connect(ui->checkBox_gameplay_miniMapSpotting,             &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_miniMapSpotting_toggled);
    connect(ui->checkBox_gameplay_3dSpotting,                  &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_3dSpotting_toggled);
    connect(ui->checkBox_gameplay_nameTag,                     &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_nameTag_toggled);
    connect(ui->checkBox_gameplay_regenerateHealth,            &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_regenerateHealth_toggled);
    connect(ui->checkBox_gameplay_hud,                         &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_hud_toggled);
    connect(ui->checkBox_gameplay_onlySquadLeaderSpawn,        &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_onlySquadLeaderSpawn_toggled);
    connect(ui->checkBox_gameplay_vehicleSpawnAllowed,         &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_vehicleSpawnAllowed_toggled);
    connect(ui->checkBox_gameplay_hitIndicatorsEnabled,        &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_hitIndicatorsEnabled_toggled);
    connect(ui->checkBox_gameplay_thirdPersonVehicleCameras,   &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_thirdPersonVehicleCameras_toggled);
    connect(ui->checkBox_gameplay_forceReloadWholeMags,        &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_forceReloadWholeMags_toggled);
    connect(ui->spinBox_gameplay_bulletDamage,                 static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_bulletDamage_valueChanged);
    connect(ui->spinBox_gameplay_soldierHealth,                static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_soldierHealth_valueChanged);
    connect(ui->spinBox_gameplay_vehicleSpawnDelay,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_vehicleSpawnDelay_valueChanged);
    connect(ui->spinBox_gameplay_playerRespawnTime,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_playerRespawnTime_valueChanged);
    connect(ui->spinBox_gameplay_ticketBleedRate,              static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_ticketBleedRate_valueChanged);
    connect(ui->spinBox_gameplay_gameModeCounter,              static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_gameModeCounter_valueChanged);
    connect(ui->spinBox_gameplay_roundTimeLimit,               static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_roundTimeLimit_valueChanged);
    connect(ui->spinBox_gameplay_roundLockdownCountdown,       static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_roundLockdownCountdown_valueChanged);
    connect(ui->spinBox_gameplay_roundWarmupTimeout,           static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_roundWarmupTimeout_valueChanged);
    connect(ui->spinBox_gameplay_roundRestartPlayerCount,      static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_roundRestartPlayerCount_valueChanged);
    connect(ui->spinBox_gameplay_roundStartPlayerCount,        static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_roundStartPlayerCount_valueChanged);
    connect(ui->spinBox_gameplay_roundPlayersReadyBypassTimer, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_roundPlayersReadyBypassTimer);
    connect(ui->spinBox_gameplay_roundPlayersReadyMinCount,    static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_roundPlayersReadyMinCount);
    connect(ui->spinBox_gameplay_roundPlayersReadyPercent,     static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &BF4OptionsWidget::spinBox_gameplay_roundPlayersReadyPercent);
    connect(ui->comboBox_gameplay_preset,                      static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged), this, &BF4OptionsWidget::comboBox_gameplay_preset_currentIndexChanged);
    connect(ui->checkBox_gameplay_presetLockPresetSetting,     &QCheckBox::toggled,                                                              this, &BF4OptionsWidget::checkBox_gameplay_presetLockPresetSetting_toggled);
    connect(ui->comboBox_gameplay_unlockMode,                  static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),           this, &BF4OptionsWidget::comboBox_gameplay_unlockMode_currentIndexChanged);

    // Options -> Teamkilling

}

BF4OptionsWidget::~BF4OptionsWidget()
{
    delete ui;
}

/* Client */
void BF4OptionsWidget::onAuthenticated()
{
    // Admins
    getClient()->getCommandHandler()->sendAdminPasswordCommand();

    // Banning
    getClient()->getCommandHandler()->sendBanListListCommand();

    // FairFight
    getClient()->getCommandHandler()->sendFairFightIsActiveCommand();

    // Punkbuster
    getClient()->getCommandHandler()->sendPunkBusterIsActiveCommand();

    // Variables
    getClient()->getCommandHandler()->sendVars3dSpottingCommand();
    getClient()->getCommandHandler()->sendVars3pCamCommand();
    getClient()->getCommandHandler()->sendVarsAlwaysAllowSpectatorsCommand();
    getClient()->getCommandHandler()->sendVarsAutoBalanceCommand();
    getClient()->getCommandHandler()->sendVarsBulletDamageCommand();
    getClient()->getCommandHandler()->sendVarsCommanderCommand();
    getClient()->getCommandHandler()->sendVarsForceReloadWholeMagsCommand();
    getClient()->getCommandHandler()->sendVarsFriendlyFireCommand();
    getClient()->getCommandHandler()->sendVarsGameModeCounterCommand();
    getClient()->getCommandHandler()->sendVarsGamePasswordCommand();
    getClient()->getCommandHandler()->sendVarsHitIndicatorsEnabledCommand();
    getClient()->getCommandHandler()->sendVarsHudCommand();
    getClient()->getCommandHandler()->sendVarsIdleBanRoundsCommand();
    getClient()->getCommandHandler()->sendVarsIdleTimeoutCommand();
    getClient()->getCommandHandler()->sendVarsKillCamCommand();
    getClient()->getCommandHandler()->sendVarsMaxPlayersCommand();
    getClient()->getCommandHandler()->sendVarsMaxSpectatorsCommand();
    getClient()->getCommandHandler()->sendVarsMiniMapCommand();
    getClient()->getCommandHandler()->sendVarsMiniMapSpottingCommand();
    getClient()->getCommandHandler()->sendVarsNameTagCommand();
    getClient()->getCommandHandler()->sendVarsOnlySquadLeaderSpawnCommand();
    getClient()->getCommandHandler()->sendVarsPlayerRespawnTimeCommand();
    getClient()->getCommandHandler()->sendVarsPresetCommand();
    getClient()->getCommandHandler()->sendVarsRegenerateHealthCommand();
    getClient()->getCommandHandler()->sendVarsRoundLockdownCountdownCommand();
    getClient()->getCommandHandler()->sendVarsRoundRestartPlayerCountCommand();
    getClient()->getCommandHandler()->sendVarsRoundStartPlayerCountCommand();
    getClient()->getCommandHandler()->sendVarsRoundTimeLimitCommand();
    getClient()->getCommandHandler()->sendVarsRoundWarmupTimeoutCommand();
    getClient()->getCommandHandler()->sendVarsServerNameCommand();
    getClient()->getCommandHandler()->sendVarsServerDescriptionCommand();
    getClient()->getCommandHandler()->sendVarsServerMessageCommand();
    getClient()->getCommandHandler()->sendVarsServerTypeCommand();
    getClient()->getCommandHandler()->sendVarsSoldierHealthCommand();
    getClient()->getCommandHandler()->sendVarsTicketBleedRateCommand();
    getClient()->getCommandHandler()->sendVarsUnlockModeCommand();
    getClient()->getCommandHandler()->sendVarsVehicleSpawnAllowedCommand();
    getClient()->getCommandHandler()->sendVarsVehicleSpawnDelayCommand();
    getClient()->getCommandHandler()->sendVarsRoundPlayersReadyBypassTimerCommand();
    getClient()->getCommandHandler()->sendVarsRoundPlayersReadyMinCountCommand();
    getClient()->getCommandHandler()->sendVarsRoundPlayersReadyPercentCommand();
}

/* Commands */
// Admin
void BF4OptionsWidget::onAdminPasswordCommand(const QString &password)
{
    ui->lineEdit_configuration_adminPassword->setText(password);
}

// FairFight
void BF4OptionsWidget::onFairFightIsActiveCommand(bool isActive)
{
    ui->checkBox_configuration_fairFight->setChecked(isActive);
}

// Player

// Punkbuster
void BF4OptionsWidget::onPunkBusterIsActiveCommand(bool active)
{
    ui->checkBox_configuration_punkBuster->setEnabled(!active);
    ui->checkBox_configuration_punkBuster->setChecked(active);
}

// Reserved Slots
void BF4OptionsWidget::onReservedSlotsListAggressiveJoinCommand(bool enabled)
{
    ui->checkBox_configuration_aggressiveJoin->setChecked(enabled);
}

// Squad

// Variables
void BF4OptionsWidget::onVars3dSpottingCommand(bool enabled)
{
    ui->checkBox_gameplay_3dSpotting->setChecked(enabled);
}

void BF4OptionsWidget::onVars3pCamCommand(bool enabled)
{
    ui->checkBox_gameplay_thirdPersonVehicleCameras->setChecked(enabled);
}

void BF4OptionsWidget::onVarsAlwaysAllowSpectatorsCommand(bool enabled)
{
    ui->checkBox_configuration_alwaysAllowSpectators->setEnabled(false);
    ui->checkBox_configuration_alwaysAllowSpectators->setChecked(enabled);
}

void BF4OptionsWidget::onVarsAutoBalanceCommand(bool enabled)
{
    ui->checkBox_gameplay_autoBalance->setChecked(enabled);
}

void BF4OptionsWidget::onVarsBulletDamageCommand(int percent)
{
    ui->spinBox_gameplay_bulletDamage->setEnabled(false);
    ui->spinBox_gameplay_bulletDamage->setValue(percent);
}

void BF4OptionsWidget::onVarsCommanderCommand(bool enabled)
{
    ui->checkBox_configuration_commander->setChecked(enabled);
}

void BF4OptionsWidget::onVarsForceReloadWholeMagsCommand(bool enabled)
{
    ui->checkBox_gameplay_forceReloadWholeMags->setChecked(enabled);
}

void BF4OptionsWidget::onVarsFriendlyFireCommand(bool enabled)
{
    ui->checkBox_gameplay_friendlyFire->setChecked(enabled);
}

void BF4OptionsWidget::onVarsGameModeCounterCommand(int percent)
{
    ui->spinBox_gameplay_gameModeCounter->setValue(percent);
}

void BF4OptionsWidget::onVarsGamePasswordCommand(const QString &password)
{
    ui->lineEdit_configuration_gamePassword->setText(password);
}

void BF4OptionsWidget::onVarsHitIndicatorsEnabledCommand(bool enabled)
{
    ui->checkBox_gameplay_hitIndicatorsEnabled->setChecked(enabled);
}

void BF4OptionsWidget::onVarsHudCommand(bool enabled)
{
    ui->checkBox_gameplay_hud->setChecked(enabled);
}

void BF4OptionsWidget::onVarsIdleBanRoundsCommand(int rounds)
{
    if (rounds <= 0) {
        ui->checkBox_configuration_idleBanRounds->setChecked(true);
        ui->spinBox_configuration_idleBanRounds->setEnabled(false);
    } else {
        ui->checkBox_configuration_idleBanRounds->setChecked(false);
    }

    ui->spinBox_configuration_idleBanRounds->setValue(rounds);
}

void BF4OptionsWidget::onVarsIdleTimeoutCommand(int timeout)
{
    if (timeout >= 86400) {
        ui->checkBox_configuration_idleTimeout->setChecked(true);
        ui->spinBox_configuration_idleTimeout->setEnabled(false);
    } else {
        ui->checkBox_configuration_idleTimeout->setChecked(false);
    }

    ui->spinBox_configuration_idleTimeout->setValue(timeout);
}

void BF4OptionsWidget::onVarsKillCamCommand(bool enabled)
{
    ui->checkBox_gameplay_killCam->setChecked(enabled);
}

void BF4OptionsWidget::onVarsMaxPlayersCommand(int playerCount)
{
    ui->spinBox_configuration_maxPlayers->setValue(playerCount);
}

void BF4OptionsWidget::onVarsMaxSpectatorsCommand(int spectatorCount)
{
    ui->spinBox_configuration_maxSpectators->setValue(spectatorCount);
}

void BF4OptionsWidget::onVarsMiniMapCommand(bool enabled)
{
    ui->checkBox_gameplay_miniMap->setChecked(enabled);
}

void BF4OptionsWidget::onVarsMiniMapSpottingCommand(bool enabled)
{
    ui->checkBox_gameplay_miniMapSpotting->setEnabled(false);
    ui->checkBox_gameplay_miniMapSpotting->setChecked(enabled);
}

void BF4OptionsWidget::onVarsNameTagCommand(bool enabled)
{
    ui->checkBox_gameplay_nameTag->setChecked(enabled);
}

void BF4OptionsWidget::onVarsOnlySquadLeaderSpawnCommand(bool enabled)
{
    ui->checkBox_gameplay_onlySquadLeaderSpawn->setChecked(enabled);
}

void BF4OptionsWidget::onVarsPlayerRespawnTimeCommand(int respawnTime)
{
    ui->spinBox_gameplay_playerRespawnTime->setValue(respawnTime);
}

void BF4OptionsWidget::onVarsPresetCommand(const BF4PresetEnum &preset, bool lockPresetSetting)
{
    ui->comboBox_gameplay_preset->setCurrentIndex(BF4Preset::toInt(preset));
    ui->checkBox_gameplay_presetLockPresetSetting->setChecked(lockPresetSetting);
}

void BF4OptionsWidget::onVarsRegenerateHealthCommand(bool enabled)
{
    ui->checkBox_gameplay_regenerateHealth->setChecked(enabled);
}

void BF4OptionsWidget::onVarsRoundLockdownCountdownCommand(int seconds)
{
    ui->spinBox_gameplay_roundLockdownCountdown->setValue(seconds);
}

void BF4OptionsWidget::onVarsRoundRestartPlayerCountCommand(int players)
{
    ui->spinBox_gameplay_roundRestartPlayerCount->setValue(players);
}

void BF4OptionsWidget::onVarsRoundStartPlayerCountCommand(int players)
{
    ui->spinBox_gameplay_roundStartPlayerCount->setValue(players);
}

void BF4OptionsWidget::onVarsRoundTimeLimitCommand(int percentage)
{
    ui->spinBox_gameplay_roundTimeLimit->setValue(percentage);
}

void BF4OptionsWidget::onVarsRoundWarmupTimeoutCommand(int timeout)
{
    ui->spinBox_gameplay_roundWarmupTimeout->setValue(timeout);
}

void BF4OptionsWidget::onVarsServerNameCommand(const QString &serverName)
{
    ui->lineEdit_details_serverName->setText(serverName);
}

void BF4OptionsWidget::onVarsServerDescriptionCommand(const QString &serverDescription)
{
    ui->textEdit_details_serverDescription->setText(serverDescription);
}

void BF4OptionsWidget::onVarsServerMessageCommand(const QString &serverMessage)
{
    ui->lineEdit_details_serverMessage->setText(serverMessage);
}

void BF4OptionsWidget::onVarsServerTypeCommand(const BF4ServerTypeEnum &serverType)
{
    ui->label_configuration_serverType->setText("<b>" + BF4ServerType::toString(serverType) + "</b>");

    switch (serverType) {
    case BF4ServerTypeEnum::Official:
    case BF4ServerTypeEnum::Ranked:
        ui->checkBox_configuration_punkBuster->setEnabled(false);
        ui->checkBox_configuration_fairFight->setEnabled(false);
        ui->lineEdit_configuration_gamePassword->setEnabled(false);
        break;

    default:
        break;
    }
}

void BF4OptionsWidget::onVarsSoldierHealthCommand(int health)
{
    ui->spinBox_gameplay_soldierHealth->setValue(health);
}

void BF4OptionsWidget::onVarsTicketBleedRateCommand(int percent)
{
    ui->spinBox_gameplay_ticketBleedRate->setValue(percent);
}

void BF4OptionsWidget::onVarsUnlockModeCommand(const Frostbite2UnlockModeEnum &unlockMode)
{
    // TODO: Figure out what serverTypes does not accept different values here.

    for (int index = 0; index < ui->comboBox_gameplay_unlockMode->count(); index++) {
        if (unlockMode == ui->comboBox_gameplay_unlockMode->itemData(index).value<Frostbite2UnlockModeEnum>()) {
            ui->comboBox_gameplay_unlockMode->setCurrentIndex(index);
        }
    }
}

void BF4OptionsWidget::onVarsVehicleSpawnAllowedCommand(bool enabled)
{
    ui->checkBox_gameplay_vehicleSpawnAllowed->setChecked(enabled);
}

void BF4OptionsWidget::onVarsVehicleSpawnDelayCommand(int delay)
{
    ui->spinBox_gameplay_vehicleSpawnDelay->setValue(delay);
}

void BF4OptionsWidget::onVarsRoundPlayersReadyBypassTimerCommand(int timer)
{
    ui->spinBox_gameplay_roundPlayersReadyBypassTimer->setValue(timer);
}

void BF4OptionsWidget::onVarsRoundPlayersReadyMinCountCommand(int count)
{
    ui->spinBox_gameplay_roundPlayersReadyMinCount->setValue(count);
}

void BF4OptionsWidget::onVarsRoundPlayersReadyPercentCommand(int percent)
{
    ui->spinBox_gameplay_roundPlayersReadyPercent->setValue(percent);
}

/* User Interface */
// Options -> Details
void BF4OptionsWidget::lineEdit_details_serverName_editingFinished()
{
    QString serverName = ui->lineEdit_details_serverName->text();

    if (!serverName.isEmpty()) {
        getClient()->getCommandHandler()->sendVarsServerNameCommand(serverName);
    }
}

void BF4OptionsWidget::textEdit_details_serverDescription_textChanged()
{
    QString serverDescription = ui->textEdit_details_serverDescription->toPlainText();

    if (!serverDescription.isEmpty()) {
        getClient()->getCommandHandler()->sendVarsServerDescriptionCommand(serverDescription);
    }
}

void BF4OptionsWidget::lineEdit_details_serverMessage_editingFinished()
{
    QString serverMessage = ui->lineEdit_details_serverMessage->text();

    if (!serverMessage.isEmpty()) {
        getClient()->getCommandHandler()->sendVarsServerMessageCommand(serverMessage);
    }
}

// Options -> Configuration
void BF4OptionsWidget::checkBox_configuration_punkBuster_toggled(bool checked)
{
    if (checked) {
        getClient()->getCommandHandler()->sendPunkBusterActivateCommand();
    }
}

void BF4OptionsWidget::checkBox_configuration_fairFight_toggled(bool checked)
{
    if (checked) {
        getClient()->getCommandHandler()->sendFairFightActivateCommand();
    } else {
        getClient()->getCommandHandler()->sendFairFightDeactivateCommand();
    }

    getClient()->getCommandHandler()->sendFairFightIsActiveCommand();
}

void BF4OptionsWidget::spinBox_configuration_maxPlayers_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsMaxPlayersCommand(value);
}

void BF4OptionsWidget::spinBox_configuration_maxSpectators_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsMaxSpectatorsCommand(value);
}

void BF4OptionsWidget::checkBox_configuration_alwaysAllowSpectators_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsAlwaysAllowSpectatorsCommand(checked);
}

void BF4OptionsWidget::lineEdit_configuration_gamePassword_editingFinished()
{
    QString password = ui->lineEdit_configuration_gamePassword->text();

    if (!password.isEmpty()) {
        getClient()->getCommandHandler()->sendVarsGamePasswordCommand(password);
    }
}

void BF4OptionsWidget::lineEdit_configuration_adminPassword_editingFinished()
{
    QString password = ui->lineEdit_configuration_adminPassword->text();

    if (!password.isEmpty()) {
        getClient()->getCommandHandler()->sendAdminPasswordCommand(password);
    }
}

void BF4OptionsWidget::checkBox_configuration_idleTimeout_toggled(bool checked)
{
    int timeout = checked ? 86400 : 225;

    ui->spinBox_configuration_idleTimeout->setEnabled(!checked);
    ui->spinBox_configuration_idleTimeout->setValue(timeout);
    ui->checkBox_configuration_idleBanRounds->setEnabled(!checked);
    ui->checkBox_configuration_idleBanRounds->setChecked(checked);
    checkBox_configuration_idleBanRounds_toggled(checked);

    getClient()->getCommandHandler()->sendVarsIdleTimeoutCommand(timeout);
}

void BF4OptionsWidget::spinBox_configuration_idleTimeout_valueChanged(int value)
{
    if (value >= 225) {
        getClient()->getCommandHandler()->sendVarsIdleTimeoutCommand(value);
    }
}

void BF4OptionsWidget::checkBox_configuration_idleBanRounds_toggled(bool checked)
{
    int rounds = checked ? 0 : 2;

    ui->spinBox_configuration_idleBanRounds->setEnabled(!checked);
    ui->spinBox_configuration_idleBanRounds->setValue(rounds);

    getClient()->getCommandHandler()->sendVarsIdleBanRoundsCommand(rounds);
}

void BF4OptionsWidget::spinBox_configuration_idleBanRounds_valueChanged(int value)
{
    if (value > 0) {
        getClient()->getCommandHandler()->sendVarsIdleTimeoutCommand(value);
    }
}

void BF4OptionsWidget::checkBox_configuration_aggressiveJoin_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendReservedSlotsListAggressiveJoinCommand(checked);
}

void BF4OptionsWidget::checkBox_configuration_commander_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsCommanderCommand(checked);
}

// Options -> Gameplay
void BF4OptionsWidget::checkBox_gameplay_friendlyFire_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsFriendlyFireCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_autoBalance_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsAutoBalanceCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_killCam_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsKillCamCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_miniMap_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsMiniMapCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_miniMapSpotting_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsMiniMapSpottingCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_3dSpotting_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVars3dSpottingCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_nameTag_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsNameTagCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_regenerateHealth_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsRegenerateHealthCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_hud_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsHudCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_onlySquadLeaderSpawn_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsOnlySquadLeaderSpawnCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_vehicleSpawnAllowed_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsVehicleSpawnAllowedCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_hitIndicatorsEnabled_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsHitIndicatorsEnabledCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_thirdPersonVehicleCameras_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVars3pCamCommand(checked);
}

void BF4OptionsWidget::checkBox_gameplay_forceReloadWholeMags_toggled(bool checked)
{
    getClient()->getCommandHandler()->sendVarsForceReloadWholeMagsCommand(checked);
}

void BF4OptionsWidget::spinBox_gameplay_bulletDamage_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsBulletDamageCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_soldierHealth_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsSoldierHealthCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_vehicleSpawnDelay_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsVehicleSpawnDelayCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_playerRespawnTime_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsPlayerRespawnTimeCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_ticketBleedRate_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsTicketBleedRateCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_gameModeCounter_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsGameModeCounterCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_roundTimeLimit_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsRoundTimeLimitCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_roundLockdownCountdown_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsRoundLockdownCountdownCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_roundWarmupTimeout_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsRoundWarmupTimeoutCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_roundRestartPlayerCount_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsRoundRestartPlayerCountCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_roundStartPlayerCount_valueChanged(int value)
{
    getClient()->getCommandHandler()->sendVarsRoundStartPlayerCountCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_roundPlayersReadyBypassTimer(int value)
{
    getClient()->getCommandHandler()->sendVarsRoundPlayersReadyBypassTimerCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_roundPlayersReadyMinCount(int value)
{
    getClient()->getCommandHandler()->sendVarsRoundPlayersReadyMinCountCommand(value);
}

void BF4OptionsWidget::spinBox_gameplay_roundPlayersReadyPercent(int value)
{
    getClient()->getCommandHandler()->sendVarsRoundPlayersReadyPercentCommand(value);
}

void BF4OptionsWidget::comboBox_gameplay_preset_currentIndexChanged(const QString &text)
{
    bool presetLockPresetSetting = ui->checkBox_gameplay_presetLockPresetSetting->isChecked();

    // TODO: Do this more elegantly, using the enum.
    getClient()->getCommandHandler()->sendVarsPresetCommand(BF4Preset::fromString(text), presetLockPresetSetting);
}

void BF4OptionsWidget::checkBox_gameplay_presetLockPresetSetting_toggled(bool checked)
{
    QString presetName = ui->comboBox_gameplay_preset->currentText();

    // TODO: Do this more elegantly, using the enum.
    getClient()->getCommandHandler()->sendVarsPresetCommand(BF4Preset::fromString(presetName), checked);
}

void BF4OptionsWidget::comboBox_gameplay_unlockMode_currentIndexChanged(int index)
{
    QString unlockMode;

    switch (index) {
    case 0:
        unlockMode = "none";
        break;

    case 1:
        unlockMode = "all";
        break;

    case 2:
        unlockMode = "common";
        break;

    case 3:
        unlockMode = "stats";
        break;
    }

    getClient()->getCommandHandler()->sendVarsUnlockModeCommand(unlockMode);
}
