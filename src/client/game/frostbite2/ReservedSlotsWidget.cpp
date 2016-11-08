
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

#include "ReservedSlotsWidget.h"
#include "ui_ReservedSlotsWidget.h"

ReservedSlotsWidget::ReservedSlotsWidget(Frostbite2Client *client, QWidget *parent) :
    Frostbite2Widget(client, parent),
    ui(new Ui::ReservedSlotsWidget)
{
    ui->setupUi(this);

    // Create menu and actions.
    menu_rs_reservedSlotsList = new QMenu(ui->listWidget_rs_reservedSlotsList);
    action_rs_reservedSlotsList_remove = new QAction(tr("Remove"), menu_rs_reservedSlotsList);

    menu_rs_reservedSlotsList->addAction(action_rs_reservedSlotsList_remove);

    /* Client */
    connect(getClient(),                         &Frostbite2Client::onAuthenticated,                        this,                             &ReservedSlotsWidget::onAuthenticated);

    /* Commands */
    connect(getClient()->getCommandHandler(),    &Frostbite2CommandHandler::onReservedSlotsListListCommand, this,                             &ReservedSlotsWidget::onReservedSlotsListListCommand);

    /* User Interface */
    connect(ui->listWidget_rs_reservedSlotsList, &QListWidget::customContextMenuRequested,                  this,                             &ReservedSlotsWidget::listWidget_rs_reservedSlotsList_customContextMenuRequested);
    connect(action_rs_reservedSlotsList_remove,  &QAction::triggered,                                       this,                             &ReservedSlotsWidget::action_rs_reservedSlotsList_remove_triggered);
    connect(ui->lineEdit_rs_player,              &QLineEdit::returnPressed,                                 this,                             &ReservedSlotsWidget::pushButton_rs_add_clicked);
    connect(ui->pushButton_rs_add,               &QPushButton::clicked,                                     this,                             &ReservedSlotsWidget::pushButton_rs_add_clicked);
    connect(ui->pushButton_rs_load,              &QPushButton::clicked,                                     getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendReservedSlotsListLoadCommand);
    connect(ui->pushButton_rs_save,              &QPushButton::clicked,                                     getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendReservedSlotsListSaveCommand);
    connect(ui->pushButton_rs_clear,             &QPushButton::clicked,                                     getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendReservedSlotsListClearCommand);
}

ReservedSlotsWidget::~ReservedSlotsWidget()
{
    delete ui;
}

/* Client */
void ReservedSlotsWidget::onAuthenticated()
{
    getClient()->getCommandHandler()->sendReservedSlotsListListCommand();
}

/* Commands */
void ReservedSlotsWidget::onReservedSlotsListListCommand(const QStringList &reservedSlotsList)
{
    ui->pushButton_rs_clear->setEnabled(!reservedSlotsList.isEmpty());

    ui->listWidget_rs_reservedSlotsList->clear();
    ui->listWidget_rs_reservedSlotsList->addItems(reservedSlotsList);
}

/* User Interface */
void ReservedSlotsWidget::listWidget_rs_reservedSlotsList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget_rs_reservedSlotsList->itemAt(pos)) {
        menu_rs_reservedSlotsList->exec(QCursor::pos());
    }
}

void ReservedSlotsWidget::action_rs_reservedSlotsList_remove_triggered()
{
    QString player = ui->listWidget_rs_reservedSlotsList->currentItem()->text();

    if (!player.isEmpty()) {
        int index = ui->listWidget_rs_reservedSlotsList->currentRow();

        ui->listWidget_rs_reservedSlotsList->takeItem(index);
        ui->pushButton_rs_clear->setEnabled(ui->listWidget_rs_reservedSlotsList->count() > 0);
        getClient()->getCommandHandler()->sendReservedSlotsListRemoveCommand(player);
    }
}

void ReservedSlotsWidget::pushButton_rs_add_clicked()
{
    QString player = ui->lineEdit_rs_player->text();

    if (!player.isEmpty()) {
        ui->listWidget_rs_reservedSlotsList->addItem(player);
        ui->pushButton_rs_clear->setEnabled(true);
        ui->lineEdit_rs_player->clear();

        getClient()->getCommandHandler()->sendReservedSlotsListAddCommand(player);
    }
}
