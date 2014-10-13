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

#include "OptionsWidget.h"
#include "ui_OptionsWidget.h"
#include "FrostbiteConnection.h"
#include "BF4CommandHandler.h"
#include "BF4Preset.h"

OptionsWidget::OptionsWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWidget),
    m_connection(connection),
    m_commandHandler(dynamic_cast<BF4CommandHandler *>(connection->getCommandHandler()))
{
    ui->setupUi(this);

    // Initialize comboBox with preset types.
    ui->comboBox_so_gp_preset->addItems(BF4Preset::getList());

    /* Commands */
    // Misc
    connect(m_commandHandler, static_cast<void (BF4CommandHandler::*)(bool)>(&BF4CommandHandler::onLoginHashedCommand),
            this, &OptionsWidget::onLoginHashedCommand);

    // Admin
    connect(m_commandHandler, &BF4CommandHandler::onAdminPasswordCommand,               this, &OptionsWidget::onAdminPasswordCommand);

    // FairFight
    connect(m_commandHandler, &BF4CommandHandler::onFairFightIsActiveCommand,           this, &OptionsWidget::onFairFightIsActiveCommand);

    // Player

    // Punkbuster
    connect(m_commandHandler, &BF4CommandHandler::onPunkBusterIsActiveCommand,          this, &OptionsWidget::onPunkBusterIsActiveCommand);

    // Variables
    connect(m_commandHandler, &BF4CommandHandler::onVars3dSpottingCommand,              this, &OptionsWidget::onVars3dSpottingCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVars3pCamCommand,                   this, &OptionsWidget::onVars3pCamCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsAlwaysAllowSpectatorsCommand,   this, &OptionsWidget::onVarsAlwaysAllowSpectatorsCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsAutoBalanceCommand,             this, &OptionsWidget::onVarsAutoBalanceCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsBulletDamageCommand,            this, &OptionsWidget::onVarsBulletDamageCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsCommanderCommand,               this, &OptionsWidget::onVarsCommanderCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsForceReloadWholeMagsCommand,    this, &OptionsWidget::onVarsForceReloadWholeMagsCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsFriendlyFireCommand,            this, &OptionsWidget::onVarsFriendlyFireCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsGameModeCounterCommand,         this, &OptionsWidget::onVarsGameModeCounterCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsGamePasswordCommand,            this, &OptionsWidget::onVarsGamePasswordCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsHitIndicatorsEnabledCommand,    this, &OptionsWidget::onVarsHitIndicatorsEnabledCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsHudCommand,                     this, &OptionsWidget::onVarsHudCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsIdleBanRoundsCommand,           this, &OptionsWidget::onVarsIdleBanRoundsCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsIdleTimeoutCommand,             this, &OptionsWidget::onVarsIdleTimeoutCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsKillCamCommand,                 this, &OptionsWidget::onVarsKillCamCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsMaxPlayersCommand,              this, &OptionsWidget::onVarsMaxPlayersCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsMaxSpectatorsCommand,           this, &OptionsWidget::onVarsMaxSpectatorsCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsMiniMapCommand,                 this, &OptionsWidget::onVarsMiniMapCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsMiniMapSpottingCommand,         this, &OptionsWidget::onVarsMiniMapSpottingCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsNameTagCommand,                 this, &OptionsWidget::onVarsNameTagCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsOnlySquadLeaderSpawnCommand,    this, &OptionsWidget::onVarsOnlySquadLeaderSpawnCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsPlayerRespawnTimeCommand,       this, &OptionsWidget::onVarsPlayerRespawnTimeCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsPresetCommand,                  this, &OptionsWidget::onVarsPresetCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsRegenerateHealthCommand,        this, &OptionsWidget::onVarsRegenerateHealthCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsRoundLockdownCountdownCommand,  this, &OptionsWidget::onVarsRoundLockdownCountdownCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsRoundRestartPlayerCountCommand, this, &OptionsWidget::onVarsRoundRestartPlayerCountCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsRoundStartPlayerCountCommand,   this, &OptionsWidget::onVarsRoundStartPlayerCountCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsRoundTimeLimitCommand,          this, &OptionsWidget::onVarsRoundTimeLimitCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsRoundWarmupTimeoutCommand,      this, &OptionsWidget::onVarsRoundWarmupTimeoutCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsServerNameCommand,              this, &OptionsWidget::onVarsServerNameCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsServerDescriptionCommand,       this, &OptionsWidget::onVarsServerDescriptionCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsServerMessageCommand,           this, &OptionsWidget::onVarsServerMessageCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsServerTypeCommand,              this, &OptionsWidget::onVarsServerTypeCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsSoldierHealthCommand,           this, &OptionsWidget::onVarsSoldierHealthCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsTicketBleedRateCommand,         this, &OptionsWidget::onVarsTicketBleedRateCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsUnlockModeCommand,              this, &OptionsWidget::onVarsUnlockModeCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsVehicleSpawnAllowedCommand,     this, &OptionsWidget::onVarsVehicleSpawnAllowedCommand);
    connect(m_commandHandler, &BF4CommandHandler::onVarsVehicleSpawnDelayCommand,       this, &OptionsWidget::onVarsVehicleSpawnDelayCommand);

    /* User Interface */
    // Options -> Details
    connect(ui->lineEdit_op_so_serverName,        &QLineEdit::editingFinished, this, &OptionsWidget::lineEdit_op_so_serverName_editingFinished);
    connect(ui->textEdit_op_so_serverDescription, &QTextEdit::textChanged,     this, &OptionsWidget::textEdit_op_so_serverDescription_textChanged);
    connect(ui->lineEdit_op_so_serverMessage,     &QLineEdit::editingFinished, this, &OptionsWidget::lineEdit_op_so_serverMessage_editingFinished);

    // Options -> Configuration
    connect(ui->checkBox_so_co_punkBuster,            &QCheckBox::toggled,                                           this, &OptionsWidget::checkBox_so_co_punkBuster_toggled);
    connect(ui->checkBox_so_co_fairFight,             &QCheckBox::toggled,                                           this, &OptionsWidget::checkBox_so_co_fairFight_toggled);
    connect(ui->checkBox_so_co_idleTimeout,           &QCheckBox::toggled,                                           this, &OptionsWidget::checkBox_so_co_idleTimeout_toggled);
    connect(ui->spinBox_so_co_idleTimeout,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &OptionsWidget::spinBox_so_co_idleTimeout_valueChanged);
    connect(ui->checkBox_so_co_idleBanRounds,         &QCheckBox::toggled,                                           this, &OptionsWidget::checkBox_so_co_idleBanRounds_toggled);
    connect(ui->spinBox_so_co_idleBanRounds,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &OptionsWidget::spinBox_so_co_idleBanRounds_valueChanged);
    connect(ui->checkBox_so_co_aggressiveJoin,        &QCheckBox::toggled,                                           this, &OptionsWidget::checkBox_so_co_aggressiveJoin_toggled);
    connect(ui->spinBox_so_co_maxPlayers,             static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &OptionsWidget::spinBox_so_co_maxPlayers_valueChanged);
    connect(ui->spinBox_so_co_maxSpectators,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &OptionsWidget::spinBox_so_co_maxSpectators_valueChanged);
    connect(ui->checkBox_so_co_alwaysAllowSpectators, &QCheckBox::toggled,                                           this, &OptionsWidget::checkBox_so_co_alwaysAllowSpectators_toggled);
    connect(ui->checkBox_so_co_commander,             &QCheckBox::toggled,                                           this, &OptionsWidget::checkBox_so_co_commander_toggled);

    // Options -> Gameplay
    connect(ui->checkBox_so_gp_friendlyFire,              &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_friendlyFire_toggled);
    connect(ui->checkBox_so_gp_autoBalance,               &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_autoBalance_toggled);
    connect(ui->checkBox_so_gp_killCam,                   &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_killCam_toggled);
    connect(ui->checkBox_so_gp_miniMap,                   &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_miniMap_toggled);
    connect(ui->checkBox_so_gp_miniMapSpotting,           &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_miniMapSpotting_toggled);
    connect(ui->checkBox_so_gp_3dSpotting,                &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_3dSpotting_toggled);
    connect(ui->checkBox_so_gp_nameTag,                   &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_nameTag_toggled);
    connect(ui->checkBox_so_gp_regenerateHealth,          &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_regenerateHealth_toggled);
    connect(ui->checkBox_so_gp_hud,                       &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_hud_toggled);
    connect(ui->checkBox_so_gp_onlySquadLeaderSpawn,      &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_onlySquadLeaderSpawn_toggled);
    connect(ui->checkBox_so_gp_vehicleSpawnAllowed,       &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_vehicleSpawnAllowed_toggled);
    connect(ui->checkBox_so_gp_hitIndicatorsEnabled,      &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_hitIndicatorsEnabled_toggled);
    connect(ui->checkBox_so_gp_thirdPersonVehicleCameras, &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_thirdPersonVehicleCameras_toggled);
    connect(ui->checkBox_so_gp_forceReloadWholeMags,      &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_forceReloadWholeMags_toggled);
    connect(ui->spinBox_so_gp_bulletDamage,               static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_bulletDamage_valueChanged);
    connect(ui->spinBox_so_gp_soldierHealth,              static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_soldierHealth_valueChanged);
    connect(ui->spinBox_so_gp_vehicleSpawnDelay,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_vehicleSpawnDelay_valueChanged);
    connect(ui->spinBox_so_gp_playerRespawnTime,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_playerRespawnTime_valueChanged);
    connect(ui->spinBox_so_gp_ticketBleedRate,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_ticketBleedRate_valueChanged);
    connect(ui->spinBox_so_gp_gameModeCounter,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_gameModeCounter_valueChanged);
    connect(ui->spinBox_so_gp_roundTimeLimit,             static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_roundTimeLimit_valueChanged);
    connect(ui->spinBox_so_gp_roundLockdownCountdown,     static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_roundLockdownCountdown_valueChanged);
    connect(ui->spinBox_so_gp_roundWarmupTimeout,         static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_roundWarmupTimeout_valueChanged);
    connect(ui->spinBox_so_gp_roundRestartPlayerCount,    static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_roundRestartPlayerCount_valueChanged);
    connect(ui->spinBox_so_gp_roundStartPlayerCount,      static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),                    this, &OptionsWidget::spinBox_so_gp_roundStartPlayerCount_valueChanged);
    connect(ui->comboBox_so_gp_preset,                    static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged), this, &OptionsWidget::comboBox_so_gp_preset_currentIndexChanged);
    connect(ui->checkBox_so_gp_presetLockPresetSetting,   &QCheckBox::toggled,                                                              this, &OptionsWidget::checkBox_so_gp_presetLockPresetSetting_toggled);
    connect(ui->comboBox_so_gp_unlockMode,                static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),           this, &OptionsWidget::comboBox_so_gp_unlockMode_currentIndexChanged);

    // Options -> Teamkilling

}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        // Admins
        m_commandHandler->sendAdminPasswordCommand();

        // Banning
        m_commandHandler->sendBanListListCommand();

        // FairFight
        m_commandHandler->sendFairFightIsActiveCommand();

        // Punkbuster
        m_commandHandler->sendPunkBusterIsActiveCommand();
        m_commandHandler->sendPunkBusterPbSvCommand("pb_sv_plist");

        // Variables
        m_commandHandler->sendVars3dSpottingCommand();
        m_commandHandler->sendVars3pCamCommand();
        m_commandHandler->sendVarsAlwaysAllowSpectatorsCommand();
        m_commandHandler->sendVarsAutoBalanceCommand();
        m_commandHandler->sendVarsBulletDamageCommand();
        m_commandHandler->sendVarsCommanderCommand();
        m_commandHandler->sendVarsForceReloadWholeMagsCommand();
        m_commandHandler->sendVarsFriendlyFireCommand();
        m_commandHandler->sendVarsGameModeCounterCommand();
        m_commandHandler->sendVarsGamePasswordCommand();
        m_commandHandler->sendVarsHitIndicatorsEnabledCommand();
        m_commandHandler->sendVarsHudCommand();
        m_commandHandler->sendVarsIdleBanRoundsCommand();
        m_commandHandler->sendVarsIdleTimeoutCommand();
        m_commandHandler->sendVarsKillCamCommand();
        m_commandHandler->sendVarsMaxPlayersCommand();
        m_commandHandler->sendVarsMaxSpectatorsCommand();
        m_commandHandler->sendVarsMiniMapCommand();
        m_commandHandler->sendVarsMiniMapSpottingCommand();
        m_commandHandler->sendVarsNameTagCommand();
        m_commandHandler->sendVarsOnlySquadLeaderSpawnCommand();
        m_commandHandler->sendVarsPlayerRespawnTimeCommand();
        m_commandHandler->sendVarsPresetCommand();
        m_commandHandler->sendVarsRegenerateHealthCommand();
        m_commandHandler->sendVarsRoundLockdownCountdownCommand();
        m_commandHandler->sendVarsRoundRestartPlayerCountCommand();
        m_commandHandler->sendVarsRoundStartPlayerCountCommand();
        m_commandHandler->sendVarsRoundTimeLimitCommand();
        m_commandHandler->sendVarsRoundWarmupTimeoutCommand();
        m_commandHandler->sendVarsServerNameCommand();
        m_commandHandler->sendVarsServerDescriptionCommand();
        m_commandHandler->sendVarsServerMessageCommand();
        m_commandHandler->sendVarsServerTypeCommand();
        m_commandHandler->sendVarsSoldierHealthCommand();
        m_commandHandler->sendVarsTicketBleedRateCommand();
        m_commandHandler->sendVarsUnlockModeCommand();
        m_commandHandler->sendVarsVehicleSpawnAllowedCommand();
        m_commandHandler->sendVarsVehicleSpawnDelayCommand();
    }
}

/* Commands */
// Admin
void OptionsWidget::onAdminPasswordCommand(const QString &password)
{
    ui->lineEdit_so_co_adminPassword->setText(password);
}

// FairFight
void OptionsWidget::onFairFightIsActiveCommand(bool isActive)
{
    ui->checkBox_so_co_fairFight->setChecked(isActive);
}

// Player

// Punkbuster
void OptionsWidget::onPunkBusterIsActiveCommand(bool active)
{
    ui->checkBox_so_co_punkBuster->setEnabled(!active);
    ui->checkBox_so_co_punkBuster->setChecked(active);
}

// Reserved Slots
void OptionsWidget::onReservedSlotsListAggressiveJoinCommand(bool enabled)
{
    ui->checkBox_so_co_aggressiveJoin->setChecked(enabled);
}

// Squad

// Variables
void OptionsWidget::onVars3dSpottingCommand(bool enabled)
{
    ui->checkBox_so_gp_3dSpotting->setChecked(enabled);
}

void OptionsWidget::onVars3pCamCommand(bool enabled)
{
    ui->checkBox_so_gp_thirdPersonVehicleCameras->setChecked(enabled);
}

void OptionsWidget::onVarsAlwaysAllowSpectatorsCommand(bool enabled)
{
    ui->checkBox_so_co_alwaysAllowSpectators->setEnabled(false);
    ui->checkBox_so_co_alwaysAllowSpectators->setChecked(enabled);
}

void OptionsWidget::onVarsAutoBalanceCommand(bool enabled)
{
    ui->checkBox_so_gp_autoBalance->setChecked(enabled);
}

void OptionsWidget::onVarsBulletDamageCommand(int percent)
{
    ui->spinBox_so_gp_bulletDamage->setEnabled(false);
    ui->spinBox_so_gp_bulletDamage->setValue(percent);
}

void OptionsWidget::onVarsCommanderCommand(bool enabled)
{
    ui->checkBox_so_co_commander->setChecked(enabled);
}

void OptionsWidget::onVarsForceReloadWholeMagsCommand(bool enabled)
{
    ui->checkBox_so_gp_forceReloadWholeMags->setChecked(enabled);
}

void OptionsWidget::onVarsFriendlyFireCommand(bool enabled)
{
    ui->checkBox_so_gp_friendlyFire->setChecked(enabled);
}

void OptionsWidget::onVarsGameModeCounterCommand(int percent)
{
    ui->spinBox_so_gp_gameModeCounter->setValue(percent);
}

void OptionsWidget::onVarsGamePasswordCommand(const QString &password)
{
    ui->lineEdit_so_co_gamePassword->setText(password);
}

void OptionsWidget::onVarsHitIndicatorsEnabledCommand(bool enabled)
{
    ui->checkBox_so_gp_hitIndicatorsEnabled->setChecked(enabled);
}

void OptionsWidget::onVarsHudCommand(bool enabled)
{
    ui->checkBox_so_gp_hud->setChecked(enabled);
}

void OptionsWidget::onVarsIdleBanRoundsCommand(int rounds)
{
    if (rounds <= 0) {
        ui->checkBox_so_co_idleBanRounds->setChecked(true);
        ui->spinBox_so_co_idleBanRounds->setEnabled(false);
    } else {
        ui->checkBox_so_co_idleBanRounds->setChecked(false);
    }

    ui->spinBox_so_co_idleBanRounds->setValue(rounds);
}

void OptionsWidget::onVarsIdleTimeoutCommand(int timeout)
{
    if (timeout >= 86400) {
        ui->checkBox_so_co_idleTimeout->setChecked(true);
        ui->spinBox_so_co_idleTimeout->setEnabled(false);
    } else {
        ui->checkBox_so_co_idleTimeout->setChecked(false);
    }

    ui->spinBox_so_co_idleTimeout->setValue(timeout);
}

void OptionsWidget::onVarsKillCamCommand(bool enabled)
{
    ui->checkBox_so_gp_killCam->setChecked(enabled);
}

void OptionsWidget::onVarsMaxPlayersCommand(int playerCount)
{
    ui->spinBox_so_co_maxPlayers->setValue(playerCount);
}

void OptionsWidget::onVarsMaxSpectatorsCommand(int spectatorCount)
{
    ui->spinBox_so_co_maxSpectators->setValue(spectatorCount);
}

void OptionsWidget::onVarsMiniMapCommand(bool enabled)
{
    ui->checkBox_so_gp_miniMap->setChecked(enabled);
}

void OptionsWidget::onVarsMiniMapSpottingCommand(bool enabled)
{
    ui->checkBox_so_gp_miniMapSpotting->setEnabled(false);
    ui->checkBox_so_gp_miniMapSpotting->setChecked(enabled);
}

void OptionsWidget::onVarsNameTagCommand(bool enabled)
{
    ui->checkBox_so_gp_nameTag->setChecked(enabled);
}

void OptionsWidget::onVarsOnlySquadLeaderSpawnCommand(bool enabled)
{
    ui->checkBox_so_gp_onlySquadLeaderSpawn->setChecked(enabled);
}

void OptionsWidget::onVarsPlayerRespawnTimeCommand(int respawnTime)
{
    ui->spinBox_so_gp_playerRespawnTime->setValue(respawnTime);
}

void OptionsWidget::onVarsPresetCommand(const BF4PresetType &presetType, bool lockPresetSetting)
{
    ui->comboBox_so_gp_preset->setCurrentIndex(BF4Preset::toInt(presetType));
    ui->checkBox_so_gp_presetLockPresetSetting->setChecked(lockPresetSetting);
}

void OptionsWidget::onVarsRegenerateHealthCommand(bool enabled)
{
    ui->checkBox_so_gp_regenerateHealth->setChecked(enabled);
}

void OptionsWidget::onVarsRoundLockdownCountdownCommand(int seconds)
{
    ui->spinBox_so_gp_roundLockdownCountdown->setValue(seconds);
}

void OptionsWidget::onVarsRoundRestartPlayerCountCommand(int players)
{
    ui->spinBox_so_gp_roundRestartPlayerCount->setValue(players);
}

void OptionsWidget::onVarsRoundStartPlayerCountCommand(int players)
{
    ui->spinBox_so_gp_roundStartPlayerCount->setValue(players);
}

void OptionsWidget::onVarsRoundTimeLimitCommand(int percentage)
{
    ui->spinBox_so_gp_roundTimeLimit->setValue(percentage);
}

void OptionsWidget::onVarsRoundWarmupTimeoutCommand(int timeout)
{
    ui->spinBox_so_gp_roundWarmupTimeout->setValue(timeout);
}

void OptionsWidget::onVarsServerNameCommand(const QString &serverName)
{
    ui->lineEdit_op_so_serverName->setText(serverName);
}

void OptionsWidget::onVarsServerDescriptionCommand(const QString &serverDescription)
{
    ui->textEdit_op_so_serverDescription->setText(serverDescription);
}

void OptionsWidget::onVarsServerMessageCommand(const QString &serverMessage)
{
    ui->lineEdit_op_so_serverMessage->setText(serverMessage);
}

void OptionsWidget::onVarsServerTypeCommand(const QString &type)
{
    ui->label_so_co_serverType->setText(type);

    if (type == "RANKED") {
        ui->lineEdit_so_co_gamePassword->setEnabled(false);
    }
}

void OptionsWidget::onVarsSoldierHealthCommand(int health)
{
    ui->spinBox_so_gp_soldierHealth->setValue(health);
}

void OptionsWidget::onVarsTicketBleedRateCommand(int percent)
{
    ui->spinBox_so_gp_ticketBleedRate->setValue(percent);
}

void OptionsWidget::onVarsUnlockModeCommand(const QString &type)
{
    int index = 0;

    if (type == "none") {
        index = 0;
    } else if (type == "all") {
        index = 1;
    } else if (type == "common") {
        index = 2;
    } else if (type == "stats") {
        index = 3;
    }

    ui->comboBox_so_gp_unlockMode->setCurrentIndex(index);
}

void OptionsWidget::onVarsVehicleSpawnAllowedCommand(bool enabled)
{
    ui->checkBox_so_gp_vehicleSpawnAllowed->setChecked(enabled);
}

void OptionsWidget::onVarsVehicleSpawnDelayCommand(int delay)
{
    ui->spinBox_so_gp_vehicleSpawnDelay->setValue(delay);
}

/* User Interface */
// Options -> Details
void OptionsWidget::lineEdit_op_so_serverName_editingFinished()
{
    QString serverName = ui->lineEdit_op_so_serverName->text();

    if (!serverName.isEmpty()) {
        m_commandHandler->sendVarsServerNameCommand(serverName);
    }
}

void OptionsWidget::textEdit_op_so_serverDescription_textChanged()
{
    QString serverDescription = ui->textEdit_op_so_serverDescription->toPlainText();

    if (!serverDescription.isEmpty()) {
        m_commandHandler->sendVarsServerDescriptionCommand(serverDescription);
    }
}

void OptionsWidget::lineEdit_op_so_serverMessage_editingFinished()
{
    QString serverMessage = ui->lineEdit_op_so_serverMessage->text();

    if (!serverMessage.isEmpty()) {
        m_commandHandler->sendVarsServerMessageCommand(serverMessage);
    }
}

// Options -> Configuration
void OptionsWidget::checkBox_so_co_punkBuster_toggled(bool checked)
{
    if (checked) {
        m_commandHandler->sendPunkBusterActivateCommand();
    }
}

void OptionsWidget::checkBox_so_co_fairFight_toggled(bool checked)
{
    if (checked) {
        m_commandHandler->sendFairFightActivateCommand();
    } else {
        m_commandHandler->sendFairFightDeactivateCommand();
    }

    m_commandHandler->sendFairFightIsActiveCommand();
}

void OptionsWidget::checkBox_so_co_idleTimeout_toggled(bool checked)
{
    int timeout = checked ? 86400 : 225;

    ui->spinBox_so_co_idleTimeout->setEnabled(!checked);
    ui->spinBox_so_co_idleTimeout->setValue(timeout);
    ui->checkBox_so_co_idleBanRounds->setEnabled(!checked);
    ui->checkBox_so_co_idleBanRounds->setChecked(checked);
    checkBox_so_co_idleBanRounds_toggled(checked);

    m_commandHandler->sendVarsIdleTimeoutCommand(timeout);
}

void OptionsWidget::spinBox_so_co_idleTimeout_valueChanged(int value)
{
    if (value >= 225) {
        m_commandHandler->sendVarsIdleTimeoutCommand(value);
    }
}

void OptionsWidget::checkBox_so_co_idleBanRounds_toggled(bool checked)
{
    int rounds = checked ? 0 : 2;

    ui->spinBox_so_co_idleBanRounds->setEnabled(!checked);
    ui->spinBox_so_co_idleBanRounds->setValue(rounds);

    m_commandHandler->sendVarsIdleBanRoundsCommand(rounds);
}

void OptionsWidget::spinBox_so_co_idleBanRounds_valueChanged(int value)
{
    if (value > 0) {
        m_commandHandler->sendVarsIdleTimeoutCommand(value);
    }
}

void OptionsWidget::checkBox_so_co_aggressiveJoin_toggled(bool checked)
{
    m_commandHandler->sendReservedSlotsListAggressiveJoinCommand(checked);
}

void OptionsWidget::spinBox_so_co_maxPlayers_valueChanged(int value)
{
    m_commandHandler->sendVarsMaxPlayersCommand(value);
}

void OptionsWidget::spinBox_so_co_maxSpectators_valueChanged(int value)
{
    m_commandHandler->sendVarsMaxSpectatorsCommand(value);
}

void OptionsWidget::checkBox_so_co_alwaysAllowSpectators_toggled(bool checked)
{
    m_commandHandler->sendVarsAlwaysAllowSpectatorsCommand(checked);
}

void OptionsWidget::checkBox_so_co_commander_toggled(bool checked)
{
    m_commandHandler->sendVarsCommanderCommand(checked);
}

// Options -> Gameplay
void OptionsWidget::checkBox_so_gp_friendlyFire_toggled(bool checked)
{
    m_commandHandler->sendVarsFriendlyFireCommand(checked);
}

void OptionsWidget::checkBox_so_gp_autoBalance_toggled(bool checked)
{
    m_commandHandler->sendVarsAutoBalanceCommand(checked);
}

void OptionsWidget::checkBox_so_gp_killCam_toggled(bool checked)
{
    m_commandHandler->sendVarsKillCamCommand(checked);
}

void OptionsWidget::checkBox_so_gp_miniMap_toggled(bool checked)
{
    m_commandHandler->sendVarsMiniMapCommand(checked);
}

void OptionsWidget::checkBox_so_gp_miniMapSpotting_toggled(bool checked)
{
    m_commandHandler->sendVarsMiniMapSpottingCommand(checked);
}

void OptionsWidget::checkBox_so_gp_3dSpotting_toggled(bool checked)
{
    m_commandHandler->sendVars3dSpottingCommand(checked);
}

void OptionsWidget::checkBox_so_gp_nameTag_toggled(bool checked)
{
    m_commandHandler->sendVarsNameTagCommand(checked);
}

void OptionsWidget::checkBox_so_gp_regenerateHealth_toggled(bool checked)
{
    m_commandHandler->sendVarsRegenerateHealthCommand(checked);
}

void OptionsWidget::checkBox_so_gp_hud_toggled(bool checked)
{
    m_commandHandler->sendVarsHudCommand(checked);
}

void OptionsWidget::checkBox_so_gp_onlySquadLeaderSpawn_toggled(bool checked)
{
    m_commandHandler->sendVarsOnlySquadLeaderSpawnCommand(checked);
}

void OptionsWidget::checkBox_so_gp_vehicleSpawnAllowed_toggled(bool checked)
{
    m_commandHandler->sendVarsVehicleSpawnAllowedCommand(checked);
}

void OptionsWidget::checkBox_so_gp_hitIndicatorsEnabled_toggled(bool checked)
{
    m_commandHandler->sendVarsHitIndicatorsEnabledCommand(checked);
}

void OptionsWidget::checkBox_so_gp_thirdPersonVehicleCameras_toggled(bool checked)
{
    m_commandHandler->sendVars3pCamCommand(checked);
}

void OptionsWidget::checkBox_so_gp_forceReloadWholeMags_toggled(bool checked)
{
    m_commandHandler->sendVarsForceReloadWholeMagsCommand(checked);
}

void OptionsWidget::spinBox_so_gp_bulletDamage_valueChanged(int value)
{
    m_commandHandler->sendVarsBulletDamageCommand(value);
}

void OptionsWidget::spinBox_so_gp_soldierHealth_valueChanged(int value)
{
    m_commandHandler->sendVarsSoldierHealthCommand(value);
}

void OptionsWidget::spinBox_so_gp_vehicleSpawnDelay_valueChanged(int value)
{
    m_commandHandler->sendVarsVehicleSpawnDelayCommand(value);
}

void OptionsWidget::spinBox_so_gp_playerRespawnTime_valueChanged(int value)
{
    m_commandHandler->sendVarsPlayerRespawnTimeCommand(value);
}

void OptionsWidget::spinBox_so_gp_ticketBleedRate_valueChanged(int value)
{
    m_commandHandler->sendVarsTicketBleedRateCommand(value);
}

void OptionsWidget::spinBox_so_gp_gameModeCounter_valueChanged(int value)
{
    m_commandHandler->sendVarsGameModeCounterCommand(value);
}

void OptionsWidget::spinBox_so_gp_roundTimeLimit_valueChanged(int value)
{
    m_commandHandler->sendVarsRoundTimeLimitCommand(value);
}

void OptionsWidget::spinBox_so_gp_roundLockdownCountdown_valueChanged(int value)
{
    m_commandHandler->sendVarsRoundLockdownCountdownCommand(value);
}

void OptionsWidget::spinBox_so_gp_roundWarmupTimeout_valueChanged(int value)
{
    m_commandHandler->sendVarsRoundWarmupTimeoutCommand(value);
}

void OptionsWidget::spinBox_so_gp_roundRestartPlayerCount_valueChanged(int value)
{
    m_commandHandler->sendVarsRoundRestartPlayerCountCommand(value);
}

void OptionsWidget::spinBox_so_gp_roundStartPlayerCount_valueChanged(int value)
{
    m_commandHandler->sendVarsRoundStartPlayerCountCommand(value);
}

void OptionsWidget::comboBox_so_gp_preset_currentIndexChanged(const QString &text)
{
    bool presetLockPresetSetting = ui->checkBox_so_gp_presetLockPresetSetting->isChecked();

    m_commandHandler->sendVarsPresetCommand(text.toLower(), presetLockPresetSetting);
}

void OptionsWidget::checkBox_so_gp_presetLockPresetSetting_toggled(bool checked)
{
    QString preset = ui->comboBox_so_gp_preset->currentText().toLower();

    m_commandHandler->sendVarsPresetCommand(preset, checked);
}

void OptionsWidget::comboBox_so_gp_unlockMode_currentIndexChanged(int index)
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

    m_commandHandler->sendVarsUnlockModeCommand(unlockMode);
}
