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

#include "FrostbiteConnection.h"
#include "Frostbite2CommandHandler.h"

#include "ReservedSlotsWidget.h"
#include "ui_ReservedSlotsWidget.h"

ReservedSlotsWidget::ReservedSlotsWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReservedSlotsWidget),
    connection(connection),
    commandHandler(dynamic_cast<Frostbite2CommandHandler *>(connection->getCommandHandler()))
{
    ui->setupUi(this);

    menu_rs_reservedSlotsList = new QMenu(ui->listWidget_rs_reservedSlotsList);
    action_rs_reservedSlotsList_remove = new QAction(tr("Remove"), menu_rs_reservedSlotsList);

    menu_rs_reservedSlotsList->addAction(action_rs_reservedSlotsList_remove);

    /* Commands */
    connect(commandHandler, SIGNAL(onReservedSlotsListListCommand(QStringList)), this, SLOT(onReservedSlotsListListCommand(QStringList)));

    /* User Interface */
    connect(ui->listWidget_rs_reservedSlotsList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listWidget_rs_reservedSlotsList_customContextMenuRequested(QPoint)));
    connect(action_rs_reservedSlotsList_remove, SIGNAL(triggered()), this, SLOT(action_rs_reservedSlotsList_remove_triggered()));
    connect(ui->lineEdit_rs_player, SIGNAL(returnPressed()), this, SLOT(pushButton_rs_add_clicked()));
    connect(ui->pushButton_rs_add, SIGNAL(clicked()), this, SLOT(pushButton_rs_add_clicked()));
    connect(ui->pushButton_rs_load, SIGNAL(clicked()), this, SLOT(pushButton_rs_load_clicked()));
    connect(ui->pushButton_rs_save, SIGNAL(clicked()), this, SLOT(pushButton_rs_save_clicked()));
    connect(ui->pushButton_rs_clear, SIGNAL(clicked()), this, SLOT(pushButton_rs_clear_clicked()));
}

ReservedSlotsWidget::~ReservedSlotsWidget()
{
    delete ui;

    delete menu_rs_reservedSlotsList;
    delete action_rs_reservedSlotsList_remove;
}

void ReservedSlotsWidget::onReservedSlotsListListCommand(const QStringList &reservedSlotsList)
{
    ui->listWidget_rs_reservedSlotsList->clear();
    ui->listWidget_rs_reservedSlotsList->addItems(reservedSlotsList);
}

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
        delete ui->listWidget_rs_reservedSlotsList->currentItem();

        commandHandler->sendReservedSlotsListRemoveCommand(player);
    }
}

void ReservedSlotsWidget::pushButton_rs_add_clicked()
{
    QString player = ui->lineEdit_rs_player->text();

    if (!player.isEmpty()) {
        ui->lineEdit_rs_player->clear();
        ui->listWidget_rs_reservedSlotsList->addItem(player);

        commandHandler->sendReservedSlotsListAddCommand(player);
    }
}

void ReservedSlotsWidget::pushButton_rs_load_clicked()
{
    commandHandler->sendReservedSlotsListLoadCommand();
}

void ReservedSlotsWidget::pushButton_rs_save_clicked()
{
    commandHandler->sendReservedSlotsListSaveCommand();
}

void ReservedSlotsWidget::pushButton_rs_clear_clicked()
{
    commandHandler->sendReservedSlotsListClearCommand();
}
