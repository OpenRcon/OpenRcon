
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

#include <QMenu>
#include <QAction>
#include <QStringList>
#include <QPoint>

#include "Frostbite2ReservedSlotsWidget.h"
#include "ui_Frostbite2ReservedSlotsWidget.h"

Frostbite2ReservedSlotsWidget::Frostbite2ReservedSlotsWidget(Frostbite2Client *client, QWidget *parent) :
    Frostbite2Widget(client, parent),
    ui(new Ui::Frostbite2ReservedSlotsWidget)
{
    ui->setupUi(this);

    // Set listWidget and clear button disabled by default.
    ui->listWidget->setEnabled(false);
    ui->pushButton_clear->setEnabled(false);

    // Create menu and actions.
    menu = new QMenu(this);
    action_remove = new QAction(tr("Remove"), menu);

    menu->addAction(action_remove);

    /* Client */
    connect(getClient(),                         &Client::onAuthenticated,                                  getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendReservedSlotsListListCommand);

    /* Commands */
    connect(getClient()->getCommandHandler(),    &Frostbite2CommandHandler::onReservedSlotsListListCommand, this,                             &Frostbite2ReservedSlotsWidget::onReservedSlotsListListCommand);

    /* User Interface */
    connect(ui->listWidget,                      &QListWidget::customContextMenuRequested,                  this,                             &Frostbite2ReservedSlotsWidget::listWidget_customContextMenuRequested);
    connect(action_remove,                       &QAction::triggered,                                       this,                             &Frostbite2ReservedSlotsWidget::action_remove_triggered);
    connect(ui->lineEdit_player,                 &QLineEdit::returnPressed,                                 this,                             &Frostbite2ReservedSlotsWidget::pushButton_add_clicked);
    connect(ui->pushButton_add,                  &QPushButton::clicked,                                     this,                             &Frostbite2ReservedSlotsWidget::pushButton_add_clicked);
    connect(ui->pushButton_load,                 &QPushButton::clicked,                                     getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendReservedSlotsListLoadCommand);
    connect(ui->pushButton_save,                 &QPushButton::clicked,                                     getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendReservedSlotsListSaveCommand);
    connect(ui->pushButton_clear,                &QPushButton::clicked,                                     getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendReservedSlotsListClearCommand);
}

Frostbite2ReservedSlotsWidget::~Frostbite2ReservedSlotsWidget()
{
    delete ui;
}

/* Commands */
void Frostbite2ReservedSlotsWidget::onReservedSlotsListListCommand(const QStringList &reservedSlotsList)
{
    ui->listWidget->clear();
    ui->listWidget->setEnabled(!reservedSlotsList.isEmpty());
    ui->pushButton_clear->setEnabled(!reservedSlotsList.isEmpty());

    if (!reservedSlotsList.isEmpty()) {
        ui->listWidget->addItems(reservedSlotsList);
    }
}

/* User Interface */
void Frostbite2ReservedSlotsWidget::listWidget_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget->itemAt(pos)) {
        menu->exec(QCursor::pos());
    }
}

void Frostbite2ReservedSlotsWidget::action_remove_triggered()
{
    QString player = ui->listWidget->currentItem()->text();

    if (!player.isEmpty()) {
        int index = ui->listWidget->currentRow();

        ui->listWidget->takeItem(index);
        ui->pushButton_clear->setEnabled(ui->listWidget->count() > 0);
        getClient()->getCommandHandler()->sendReservedSlotsListRemoveCommand(player);
    }
}

void Frostbite2ReservedSlotsWidget::pushButton_add_clicked()
{
    QString player = ui->lineEdit_player->text();

    if (!player.isEmpty()) {
        ui->listWidget->addItem(player);
        ui->pushButton_clear->setEnabled(true);
        ui->lineEdit_player->clear();

        getClient()->getCommandHandler()->sendReservedSlotsListAddCommand(player);
    }
}
