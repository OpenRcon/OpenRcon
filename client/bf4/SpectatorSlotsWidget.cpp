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

#include <QMenu>
#include <QAction>

#include "SpectatorSlotsWidget.h"
#include "ui_SpectatorSlotsWidget.h"
#include "FrostbiteConnection.h"
#include "BF4CommandHandler.h"

SpectatorSlotsWidget::SpectatorSlotsWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpectatorSlotsWidget),
    m_connection(connection),
    m_commandHandler(dynamic_cast<BF4CommandHandler *>(connection->getCommandHandler()))
{
    ui->setupUi(this);

    menu_ss_spectatorList = new QMenu(ui->listWidget_ss_spectatorList);
    action_ss_spectatorList_remove = new QAction(tr("Remove"), menu_ss_spectatorList);

    menu_ss_spectatorList->addAction(action_ss_spectatorList_remove);

    /* Commands */
    connect(m_commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &SpectatorSlotsWidget::onLoginHashedCommand);
    connect(m_commandHandler, &BF4CommandHandler::onSpectatorListListCommand,                                           this, &SpectatorSlotsWidget::onSpectatorListListCommand);

    /* User Interface */
    connect(ui->listWidget_ss_spectatorList, &QListWidget::customContextMenuRequested, this, &SpectatorSlotsWidget::listWidget_ss_spectatorList_customContextMenuRequested);
    connect(action_ss_spectatorList_remove,  &QAction::triggered,                      this, &SpectatorSlotsWidget::action_ss_spectatorList_remove_triggered);
    connect(ui->lineEdit_ss_player,          &QLineEdit::returnPressed,                this, &SpectatorSlotsWidget::pushButton_ss_add_clicked);
    connect(ui->pushButton_ss_add,           &QPushButton::clicked,                    this, &SpectatorSlotsWidget::pushButton_ss_add_clicked);
    connect(ui->pushButton_ss_save,          &QPushButton::clicked,                    this, &SpectatorSlotsWidget::pushButton_ss_save_clicked);
    connect(ui->pushButton_ss_clear,         &QPushButton::clicked,                    this, &SpectatorSlotsWidget::pushButton_ss_clear_clicked);
}

SpectatorSlotsWidget::~SpectatorSlotsWidget()
{
    delete ui;
}

void SpectatorSlotsWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        m_commandHandler->sendSpectatorListListCommand();
    }
}

void SpectatorSlotsWidget::onSpectatorListListCommand(const QStringList &spectatorList)
{
    ui->listWidget_ss_spectatorList->clear();
    ui->listWidget_ss_spectatorList->addItems(spectatorList);
}

void SpectatorSlotsWidget::listWidget_ss_spectatorList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget_ss_spectatorList->itemAt(pos)) {
        menu_ss_spectatorList->exec(QCursor::pos());
    }
}

void SpectatorSlotsWidget::action_ss_spectatorList_remove_triggered()
{
    QString player = ui->listWidget_ss_spectatorList->currentItem()->text();

    if (!player.isEmpty()) {
        int row = ui->listWidget_ss_spectatorList->currentRow();

        ui->listWidget_ss_spectatorList->takeItem(row);
        m_commandHandler->sendSpectatorListRemoveCommand(player);
    }
}

void SpectatorSlotsWidget::pushButton_ss_add_clicked()
{
    QString player = ui->lineEdit_ss_player->text();

    if (!player.isEmpty()) {
        ui->lineEdit_ss_player->clear();
        ui->listWidget_ss_spectatorList->addItem(player);

        m_commandHandler->sendSpectatorListAddCommand(player);
    }
}

void SpectatorSlotsWidget::pushButton_ss_save_clicked()
{
    m_commandHandler->sendSpectatorListSaveCommand();
}

void SpectatorSlotsWidget::pushButton_ss_clear_clicked()
{
    m_commandHandler->sendSpectatorListClearCommand();
}
