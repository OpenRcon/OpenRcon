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

#include <QDateTime>

#include "FrostbiteConnection.h"
#include "Frostbite2CommandHandler.h"
#include "PlayerSubset.h"

#include "ChatWidget.h"
#include "ui_ChatWidget.h"

ChatWidget::ChatWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget),
    connection(connection),
    commandHandler(dynamic_cast<Frostbite2CommandHandler *>(connection->getCommandHandler()))
{
    ui->setupUi(this);

    ui->comboBox_ch_target->addItem(tr("All"));

    /* Events */
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerChatEvent, this, &ChatWidget::onPlayerChatEvent);

    /* Commands */
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &ChatWidget::onLoginHashedCommand);

    /* User Interface */
    connect(ui->comboBox_ch_mode,   static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ChatWidget::comboBox_ch_mode_currentIndexChanged);
    connect(ui->pushButton_ch_send, &QPushButton::clicked,                                                  this, &ChatWidget::pushButton_ch_send_clicked);
    connect(ui->lineEdit_ch,        &QLineEdit::editingFinished,                                            this, &ChatWidget::pushButton_ch_send_clicked);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::logChat(const QString &sender, const QString &message, const QString &target)
{
    ui->textEdit_ch->append(QString("[%1] <span style=\"color:#0000FF\">[%2] %3</span>: <span style=\"color:#008000\">%4</span>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"), target, sender, message));
}

/* Events */
void ChatWidget::onPlayerChatEvent(const QString &sender, const QString &message, const QString &target)
{
    logChat(sender, message, target);
}

/* Commands */
void ChatWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        commandHandler->sendAdminEventsEnabledCommand(true);
    }
}

/* User Interface */
void ChatWidget::comboBox_ch_mode_currentIndexChanged(int index)
{
    ui->spinBox_ch_duration->setEnabled(index > 0);
}

void ChatWidget::pushButton_ch_send_clicked()
{
    QString message = ui->lineEdit_ch->text();
    int target = ui->comboBox_ch_target->currentIndex();
    int type = ui->comboBox_ch_mode->currentIndex();
    int duration = ui->spinBox_ch_duration->value();

    if (!message.isEmpty()) {
        PlayerSubset playerSubset;
        int parameter;

        switch (target) {
        case 0:
            playerSubset = PlayerSubset::All;
            break;

        case 1:
            playerSubset = PlayerSubset::Team;
            parameter = 0;
            break;

        case 2:
            playerSubset = PlayerSubset::Team;
            parameter = 1;
            break;
        }

        switch (type) {
        case 0:
            if (parameter) {
                commandHandler->sendAdminSayCommand(message, playerSubset, parameter);
            } else {
                commandHandler->sendAdminSayCommand(message, playerSubset);
            }
            break;

        case 1:
            if (parameter) {
                commandHandler->sendAdminYellCommand(message, duration, playerSubset, parameter);
            } else {
                commandHandler->sendAdminYellCommand(message, duration, playerSubset);
            }
            break;
        }

        ui->lineEdit_ch->clear();
    }
}
