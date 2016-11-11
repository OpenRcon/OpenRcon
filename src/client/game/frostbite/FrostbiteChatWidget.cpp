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
#include "BF3LevelDictionary.h"
#include "BF4LevelDictionary.h"
#include "FrostbiteUtils.h"

FrostbiteChatWidget::FrostbiteChatWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::FrostbiteChatWidget)
{
    ui->setupUi(this);

    // Modify the initial size of the splitter.
    ui->splitter->setSizes({ 500, 100 });

    // Hide player list by default.
    ui->listWidget->hide();

    // Populate the target comboBox.
    for (QString playerSubset : PlayerSubset::asList()) {
        ui->comboBox_target->addItem(playerSubset, QVariant::fromValue(PlayerSubset::fromString(playerSubset)));
    }

    /* Client */
    connect(getClient(),                      &Client::onAuthenticated,                                               this,                        &FrostbiteChatWidget::onAuthenticated);
    connect(getClient(),                      &Client::onAuthenticated,                                               client->getCommandHandler(), &FrostbiteCommandHandler::sendCurrentLevelCommand);

    /* Events */
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerChatEvent,                            this,                        &FrostbiteChatWidget::onPlayerChatEvent);

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(const QList<FrostbitePlayerEntry>&)>(&FrostbiteCommandHandler::onListPlayersCommand),
            this, &FrostbiteChatWidget::onListPlayersCommand);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onCurrentLevelCommand,                        this,                        &FrostbiteChatWidget::onCurrentLevelCommand);

    /* User Interface */
    connect(ui->comboBox_mode,                static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,                        &FrostbiteChatWidget::comboBox_mode_currentIndexChanged);
    connect(ui->comboBox_target,              static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,                        &FrostbiteChatWidget::comboBox_target_currentIndexChanged);
    connect(ui->spinBox_duration,             static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),          this,                        &FrostbiteChatWidget::spinBox_duration_valueChanged);
    connect(ui->pushButton_send,              &QPushButton::clicked,                                                  this,                        &FrostbiteChatWidget::pushButton_send_clicked);
    connect(ui->lineEdit,                     &QLineEdit::editingFinished,                                            this,                        &FrostbiteChatWidget::pushButton_send_clicked);
}

FrostbiteChatWidget::~FrostbiteChatWidget()
{
    delete ui;
}

void FrostbiteChatWidget::logChat(const QString &sender, const QString &message, const QString &target)
{
    PlayerSubsetEnum playerSubset = PlayerSubset::fromString(target);

    ui->textEdit->append(QString("[%1] <span style=\"color:#0000FF\">[%2] %3</span>: <span style=\"color:#008000\">%4</span>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"), PlayerSubset::toString(playerSubset), sender, message));
}

/* Client */
void FrostbiteChatWidget::onAuthenticated()
{
    BFBC2CommandHandler *bfbc2CommandHandler = dynamic_cast<BFBC2CommandHandler*>(getClient()->getCommandHandler());
    Frostbite2CommandHandler *frostbite2CommandHandler = dynamic_cast<Frostbite2CommandHandler*>(getClient()->getCommandHandler());

    if (bfbc2CommandHandler) {
        bfbc2CommandHandler->sendEventsEnabledCommand(true);
    } else if (frostbite2CommandHandler) {
        frostbite2CommandHandler->sendAdminEventsEnabledCommand(true);
    }
}

/* Events */
void FrostbiteChatWidget::onPlayerChatEvent(const QString &sender, const QString &message, const QString &target)
{
    logChat(sender, message, target);
}

/* Commands */
void FrostbiteChatWidget::onListPlayersCommand(const QList<FrostbitePlayerEntry> &playerList)
{
    ui->listWidget->clear();

    QSet<int> teamIdList;

    for (FrostbitePlayerEntry playerEntry : playerList) {
        ui->listWidget->addItem(playerEntry.getName());

        teamIdList.insert(playerEntry.getTeamId());
    }
}

void FrostbiteChatWidget::onCurrentLevelCommand(const QString &levelName)
{
    GameTypeEnum gameType = getClient()->getServerEntry()->getGameType();
    QList<TeamEntry> teamList;

    switch (gameType) {
    case GameTypeEnum::BF3:
        teamList = BF3LevelDictionary::getTeams(BF3LevelDictionary::getLevel(levelName).getTeamList());
        break;
    case GameTypeEnum::BF4:
        teamList = BF4LevelDictionary::getTeams(BF4LevelDictionary::getLevel(levelName).getTeamList());
        break;
    default:
        break;
    }

    for (TeamEntry teamEntry : teamList) {
        ui->comboBox_target->addItem(tr("Team %1").arg(teamEntry.getName()));
    }
}

/* User Interface */
void FrostbiteChatWidget::comboBox_mode_currentIndexChanged(int index)
{
    ui->spinBox_duration->setEnabled(index > 0);
}

void FrostbiteChatWidget::comboBox_target_currentIndexChanged(int index)
{
    ui->listWidget->hide();

    PlayerSubsetEnum playerSubset = ui->comboBox_target->itemData(index, Qt::UserRole).value<PlayerSubsetEnum>();

    switch (playerSubset) {
    case PlayerSubsetEnum::Player:
        ui->listWidget->show();
        break;

    default:
        break;
    }
}

void FrostbiteChatWidget::spinBox_duration_valueChanged(int index)
{
    ui->label_duration->setText(index > 1 ? tr("Seconds") : tr("Second"));
}

void FrostbiteChatWidget::pushButton_send_clicked()
{
    QString message = ui->lineEdit->text();
    int type = ui->comboBox_mode->currentIndex();
    int duration = ui->spinBox_duration->value();

    if (!message.isEmpty()) {
        PlayerSubsetEnum playerSubset = ui->comboBox_target->itemData(ui->comboBox_target->currentIndex(), Qt::UserRole).value<PlayerSubsetEnum>();
        QString player;

        switch (playerSubset) {
        case PlayerSubsetEnum::Player:
            player = ui->listWidget->currentItem()->text();
            break;

        default:
            break;
        }

        switch (type) {
        case 0:
            getClient()->getCommandHandler()->sendAdminSayCommand(message, playerSubset, player);
            break;

        case 1:
            getClient()->getCommandHandler()->sendAdminYellCommand(message, playerSubset, player, duration);
            break;
        }

        ui->lineEdit->clear();
    }
}
