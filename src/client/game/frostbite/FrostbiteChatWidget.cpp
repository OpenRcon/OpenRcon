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

#include <QString>
#include <QDateTime>
#include <QSet>

#include "FrostbiteChatWidget.h"
#include "ui_FrostbiteChatWidget.h"

#include "BFBC2CommandHandler.h"
#include "Frostbite2CommandHandler.h"
#include "PlayerSubset.h"
#include "FrostbitePlayerEntry.h"

#include "GameType.h"
#include "ServerEntry.h"
#include "TeamEntry.h"
#include "LevelEntry.h"
#include "BFBC2LevelEntry.h"
#include "BFBC2LevelDictionary.h"
#include "BF3LevelDictionary.h"
#include "BF4LevelDictionary.h"
#include "FrostbiteUtils.h"

#include "Squad.h"

FrostbiteChatWidget::FrostbiteChatWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::FrostbiteChatWidget)
{
    ui->setupUi(this);

    // Populate the target comboBox.
    ui->comboBox_target->addItem(tr("All"), QVariant::fromValue(PlayerSubsetEnum::All));

    // Hide squad comboBox by default, and populate it.
    ui->comboBox_squad->setVisible(false);

    // Hide duration comboBox by default.
    ui->spinBox_duration->setVisible(false);

    // Hide duration label by default.
    ui->label_duration->setVisible(false);

    for (QString squadName : Squad::asList()) {
        ui->comboBox_squad->addItem(squadName, QVariant::fromValue(Squad::fromString(squadName)));
    }

    /* Client */
    connect(getClient(),                      &Client::onAuthenticated,                                               this,                        &FrostbiteChatWidget::onAuthenticated);
    connect(getClient(),                      &Client::onAuthenticated,                                               client->getCommandHandler(), &FrostbiteCommandHandler::sendCurrentLevelCommand);

    /* Events */
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerJoinEvent,                            this,                        &FrostbiteChatWidget::updatePlayerList);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerLeaveEvent,                           this,                        &FrostbiteChatWidget::updatePlayerList);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerChatEvent,                            this,                        &FrostbiteChatWidget::onPlayerChatEvent);

    Frostbite2CommandHandler *frostbite2CommandHandler = dynamic_cast<Frostbite2CommandHandler*>(getClient()->getCommandHandler());

    if (frostbite2CommandHandler) {
        connect(frostbite2CommandHandler,     &Frostbite2CommandHandler::onServerLevelLoadedEvent,                    this,                        &FrostbiteChatWidget::onCurrentLevelCommand);
    }

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(const QList<FrostbitePlayerEntry>&)>(&FrostbiteCommandHandler::onListPlayersCommand),
            this, &FrostbiteChatWidget::onListPlayersCommand);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onCurrentLevelCommand,                        this,                        &FrostbiteChatWidget::onCurrentLevelCommand);

    /* User Interface */
    connect(ui->lineEdit,                     &QLineEdit::textChanged,                                                this,                        &FrostbiteChatWidget::lineEdit_textChanged);
    connect(ui->comboBox_mode,                static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,                        &FrostbiteChatWidget::comboBox_mode_currentIndexChanged);
    connect(ui->comboBox_target,              static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,                        &FrostbiteChatWidget::comboBox_target_currentIndexChanged);
    connect(ui->spinBox_duration,             static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),          this,                        &FrostbiteChatWidget::spinBox_duration_valueChanged);
    connect(ui->pushButton_send,              &QPushButton::clicked,                                                  this,                        &FrostbiteChatWidget::pushButton_send_clicked);
    connect(ui->lineEdit,                     &QLineEdit::returnPressed,                                              this,                        &FrostbiteChatWidget::pushButton_send_clicked);
}

FrostbiteChatWidget::~FrostbiteChatWidget()
{
    delete ui;
}

void FrostbiteChatWidget::logChat(const QString &sender, const QString &target, const QString &message)
{
    ui->textEdit->append(QString("[%1] <span style=\"color:#ff9933\">%2</span> &rarr; <span style=\"color:#0000ff\">%3</span>: <span style=\"color:#008000\">%4</span>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"), sender, target, message));
}

void FrostbiteChatWidget::updatePlayerList()
{
    updateLock = false;

    getClient()->getCommandHandler()->sendAdminListPlayersCommand();
}

/* Client */
void FrostbiteChatWidget::onAuthenticated()
{
    getClient()->getCommandHandler()->sendAdminEventsEnabledCommand(true);
}

/* Events */
void FrostbiteChatWidget::onPlayerChatEvent(const QString &sender, const QString &message, const PlayerSubsetEnum &playerSubset, QString player, int teamId, int squadId)
{
    QString target;

    switch (playerSubset) {
    case PlayerSubsetEnum::Player:
        target = player;
        break;

    case PlayerSubsetEnum::Team:
        target = tr("Team %1").arg(teamList.at(teamId).getName());
        break;


    case PlayerSubsetEnum::Squad:
        target = tr("Team %1 - Squad %2").arg(teamList.at(teamId).getName()).arg(Squad::toString(squadId));
        break;

    default:
        target = PlayerSubset::toString(playerSubset);
        break;
    }

    logChat(sender, target, message);
}

/* Commands */
void FrostbiteChatWidget::onListPlayersCommand(const QList<FrostbitePlayerEntry> &playerList)
{
    if (!updateLock) {
        // Remove old player entries.
        for (int index = ui->comboBox_target->count(); index > 0; index--) {
            PlayerSubsetEnum playerSubset = ui->comboBox_target->itemData(index).value<PlayerSubsetEnum>();

            if (playerSubset == PlayerSubsetEnum::Player) {
                ui->comboBox_target->removeItem(index);
            }
        }

        // Add new player entries.
        for (FrostbitePlayerEntry playerEntry : playerList) {
            ui->comboBox_target->addItem(playerEntry.getName(), QVariant::fromValue(PlayerSubsetEnum::Player));
        }

        updateLock = true;
    }
}

void FrostbiteChatWidget::onCurrentLevelCommand(const QString &levelName)
{
    GameTypeEnum gameType = getClient()->getServerEntry()->getGameType();

    // Get the list of teams depending on game.
    switch (gameType) {
    case GameTypeEnum::BFBC2:
        teamList = BFBC2LevelDictionary::getTeams(BFBC2LevelDictionary::getLevel(levelName).getTeamList());
        break;

    case GameTypeEnum::BF3:
        teamList = BF3LevelDictionary::getTeams(BF3LevelDictionary::getLevel(levelName).getTeamList());
        break;

    case GameTypeEnum::BF4:
        teamList = BF4LevelDictionary::getTeams(BF4LevelDictionary::getLevel(levelName).getTeamList());
        break;

    default:
        break;
    }

    // Remove old team entries.
    for (int index = ui->comboBox_target->count(); index > 0; index--) {
        PlayerSubsetEnum playerSubset = ui->comboBox_target->itemData(index).value<PlayerSubsetEnum>();

        if (playerSubset == PlayerSubsetEnum::Team || playerSubset == PlayerSubsetEnum::Player) {
            ui->comboBox_target->removeItem(index);
        }

        if (playerSubset == PlayerSubsetEnum::Player) {
            updateLock = false;
        }
    }

    // Add new team entries for this level.
    for (int teamId = 0; teamId < teamList.length(); teamId++) {
        ui->comboBox_target->addItem(tr("Team %1").arg(teamList.at(teamId).getName()), QVariant::fromValue(PlayerSubsetEnum::Team));
    }
}

/* User Interface */
void FrostbiteChatWidget::lineEdit_textChanged(const QString &text)
{
    ui->pushButton_send->setEnabled(!text.isEmpty());
}

void FrostbiteChatWidget::comboBox_mode_currentIndexChanged(int index)
{
    ui->spinBox_duration->setEnabled(index > 0);
    ui->spinBox_duration->setVisible(index > 0);
    ui->label_duration->setVisible(index > 0);
}

void FrostbiteChatWidget::comboBox_target_currentIndexChanged(int index)
{
    PlayerSubsetEnum playerSubset = ui->comboBox_target->itemData(index, Qt::UserRole).value<PlayerSubsetEnum>();

    ui->comboBox_squad->setEnabled(playerSubset == PlayerSubsetEnum::Team);
    ui->comboBox_squad->setVisible(playerSubset == PlayerSubsetEnum::Team);
}

void FrostbiteChatWidget::spinBox_duration_valueChanged(int index)
{
    ui->label_duration->setText(index > 1 ? tr("Seconds") : tr("Second"));
}

void FrostbiteChatWidget::pushButton_send_clicked()
{
    QString message = ui->lineEdit->text();

    if (!message.isEmpty()) {
        int targetIndex = ui->comboBox_target->currentIndex();
        PlayerSubsetEnum playerSubset = ui->comboBox_target->itemData(targetIndex, Qt::UserRole).value<PlayerSubsetEnum>();
        QString player;
        int teamId = 0;
        int squadId = 0;

        switch (playerSubset) {
        case PlayerSubsetEnum::Player:
            player = ui->comboBox_target->itemText(targetIndex);
            break;

        case PlayerSubsetEnum::Team:
            teamId = ui->comboBox_target->currentIndex() - 1;
            squadId = ui->comboBox_squad->currentIndex();

            // If a squad is selected, set the player subset to squad.
            if (squadId > 0) {
                playerSubset = PlayerSubsetEnum::Squad;
            }
            break;

        default:
            break;
        }

        int modeIndex = ui->comboBox_mode->currentIndex();

        switch (modeIndex) {
        case 0:
            if (playerSubset == PlayerSubsetEnum::Team || playerSubset == PlayerSubsetEnum::Squad) {
                getClient()->getCommandHandler()->sendAdminSayCommand(message, playerSubset, teamId, squadId);
            } else {
                getClient()->getCommandHandler()->sendAdminSayCommand(message, playerSubset, player);
            }
            break;

        case 1:
            int duration = ui->spinBox_duration->value();

            if (playerSubset == PlayerSubsetEnum::Team || playerSubset == PlayerSubsetEnum::Squad) {
                getClient()->getCommandHandler()->sendAdminYellCommand(message, playerSubset, teamId, squadId, duration);
            } else {
                getClient()->getCommandHandler()->sendAdminYellCommand(message, playerSubset, player, duration);
            }
            break;
        }

        ui->lineEdit->clear();
    }
}
