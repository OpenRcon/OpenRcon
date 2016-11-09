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

#include "FrostbiteChatWidget.h"
#include "ui_FrostbiteChatWidget.h"

#include "BFBC2CommandHandler.h"
#include "Frostbite2CommandHandler.h"
#include "PlayerSubset.h"

FrostbiteChatWidget::FrostbiteChatWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::FrostbiteChatWidget)
{
    ui->setupUi(this);

    // Modify the initial size of the splitter.
    ui->splitter->setSizes({ 500, 100 });

    /* Client */
    connect(getClient(),                      &Client::onAuthenticated,                                               this, &FrostbiteChatWidget::onAuthenticated);

    /* Events */
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPlayerChatEvent,                            this, &FrostbiteChatWidget::onPlayerChatEvent);

    /* User Interface */
    connect(ui->comboBox_mode,                static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &FrostbiteChatWidget::comboBox_mode_currentIndexChanged);
    connect(ui->spinBox_duration,             static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),          this, &FrostbiteChatWidget::spinBox_duration_valueChanged);
    connect(ui->pushButton_send,              &QPushButton::clicked,                                                  this, &FrostbiteChatWidget::pushButton_send_clicked);
    connect(ui->lineEdit,                     &QLineEdit::editingFinished,                                            this, &FrostbiteChatWidget::pushButton_send_clicked);
}

FrostbiteChatWidget::~FrostbiteChatWidget()
{
    delete ui;
}

void FrostbiteChatWidget::logChat(const QString &sender, const QString &message, const QString &target)
{
    ui->textEdit->append(QString("[%1] <span style=\"color:#0000FF\">[%2] %3</span>: <span style=\"color:#008000\">%4</span>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"), target, sender, message));
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

/* User Interface */
void FrostbiteChatWidget::comboBox_mode_currentIndexChanged(int index)
{
    ui->spinBox_duration->setEnabled(index > 0);
}

void FrostbiteChatWidget::spinBox_duration_valueChanged(int index)
{
    ui->label_duration->setText(index > 1 ? tr("Seconds") : tr("Second"));
}

void FrostbiteChatWidget::pushButton_send_clicked()
{
    QString message = ui->lineEdit->text();
    int target = ui->comboBox_target->currentIndex();
    int type = ui->comboBox_mode->currentIndex();
    int duration = ui->spinBox_duration->value();

    if (!message.isEmpty()) {
        PlayerSubsetEnum playerSubset;
        int parameter = 0;

        switch (target) {
        case 0:
            playerSubset = PlayerSubsetEnum::All;
            break;

        case 1:
            playerSubset = PlayerSubsetEnum::Team;
            parameter = 0;
            break;

        case 2:
            playerSubset = PlayerSubsetEnum::Team;
            parameter = 1;
            break;
        }

        switch (type) {
        case 0:
            if (parameter) {
                getClient()->getCommandHandler()->sendAdminSayCommand(message, playerSubset, parameter);
            } else {
                getClient()->getCommandHandler()->sendAdminSayCommand(message, playerSubset);
            }
            break;

        case 1:
            if (parameter) {
                getClient()->getCommandHandler()->sendAdminYellCommand(message, duration, playerSubset, parameter);
            } else {
                getClient()->getCommandHandler()->sendAdminYellCommand(message, duration, playerSubset);
            }
            break;
        }

        ui->lineEdit->clear();
    }
}
