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
#include "BF4CommandHandler.h"
#include "ServerInfo.h"
#include "LevelEntry.h"
#include "GameModeEntry.h"
#include "BF4LevelDictionary.h"

#include "MapListWidget.h"
#include "ui_MapListWidget.h"

MapListWidget::MapListWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapListWidget),
    connection(connection),
    commandHandler(dynamic_cast<BF4CommandHandler *>(connection->getCommandHandler()))
{
    ui->setupUi(this);

    // Set default values
    ui->comboBox_ml_gameMode->addItems(BF4LevelDictionary::getGameModeNames());
    ui->spinBox_ml_rounds->setValue(2);
    setAvailableMaplist(0);

    // Add menus
    menu_ml_available = new QMenu(ui->treeWidget_ml_available);
    action_ml_available_add = new QAction(tr("Add"), menu_ml_available);
    menu_ml_current = new QMenu(ui->treeWidget_ml_current);
    action_ml_current_remove = new QAction(tr("Remove"), menu_ml_current);

    menu_ml_available->addAction(action_ml_available_add);
    menu_ml_current->addAction(action_ml_current_remove);

    /* Commands */
    connect(commandHandler, SIGNAL(onLoginHashedCommand(bool)), this, SLOT(onLoginHashedCommand(bool)));
    connect(commandHandler, SIGNAL(onServerInfoCommand(ServerInfo)), this, SLOT(onServerInfoCommand(ServerInfo)));
    connect(commandHandler, SIGNAL(onMapListListCommand(MapList)), this, SLOT(onMapListListCommand(MapList)));

    /* User Interface */
    connect(ui->comboBox_ml_gameMode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ml_gameMode_currentIndexChanged(int)));
    connect(ui->treeWidget_ml_available, SIGNAL(itemSelectionChanged()), this, SLOT(treeWidget_ml_available_itemSelectionChanged()));
    connect(ui->treeWidget_ml_available, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_ml_available_customContextMenuRequested(QPoint)));
    connect(action_ml_available_add, SIGNAL(triggered()), this, SLOT(pushButton_ml_add_clicked()));
    connect(ui->pushButton_ml_add, SIGNAL(clicked()), this, SLOT(pushButton_ml_add_clicked()));
    connect(ui->pushButton_ml_remove, SIGNAL(clicked()), this, SLOT(pushButton_ml_remove_clicked()));
    connect(ui->treeWidget_ml_current, SIGNAL(itemSelectionChanged()), this, SLOT(treeWidget_ml_current_itemSelectionChanged()));
    connect(ui->treeWidget_ml_current, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_ml_current_customContextMenuRequested(QPoint)));
    connect(action_ml_current_remove, SIGNAL(triggered()), this, SLOT(pushButton_ml_remove_clicked()));
}

MapListWidget::~MapListWidget()
{
    delete ui;

    delete menu_ml_available;
    delete action_ml_available_add;
    delete menu_ml_current;
    delete action_ml_current_remove;
}

void MapListWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        commandHandler->sendServerInfoCommand();
        commandHandler->sendMapListListCommand();
    }
}

void MapListWidget::onServerInfoCommand(const ServerInfo &serverInfo)
{
    LevelEntry level = BF4LevelDictionary::getLevel(serverInfo.currentMap);
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(serverInfo.gameMode);

    int gameModeIndex = BF4LevelDictionary::getGameModeNames().indexOf(gameMode.name);

    ui->label_ml_currentMapValue->setText(level.name);
    ui->label_ml_currentMapImage->setPixmap(level.image());

    ui->comboBox_ml_gameMode->setCurrentIndex(gameModeIndex);
    setAvailableMaplist(gameModeIndex);
}

void MapListWidget::onMapListListCommand(const MapList &mapList)
{
    setCurrentMaplist(mapList);
}

void MapListWidget::comboBox_ml_gameMode_currentIndexChanged(int index)
{
    setAvailableMaplist(index);
}

void MapListWidget::treeWidget_ml_available_itemSelectionChanged()
{
    LevelEntry level = BF4LevelDictionary::getLevel(ui->treeWidget_ml_available->currentItem()->text(0));

    ui->label_ml_availableSelectedMapImage->setPixmap(level.image());
}

void MapListWidget::treeWidget_ml_available_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_ml_available->itemAt(pos)) {
        menu_ml_available->exec(QCursor::pos());
    }
}

void MapListWidget::pushButton_ml_add_clicked()
{
    // Make sure that treeWidget_ml_available selected item count is greater than zero.
    if (ui->treeWidget_ml_available->selectedItems().size() > 0) {
        int rounds = ui->spinBox_ml_rounds->value();

        if (rounds > 0) {
            LevelEntry level = BF4LevelDictionary::getLevel(ui->treeWidget_ml_available->currentItem()->text(0));
            GameModeEntry gameMode = BF4LevelDictionary::getGameMode(ui->treeWidget_ml_available->currentItem()->text(1));

            ui->label_ml_currentSelectedMapImage->setPixmap(level.image());

            addCurrentMapListRow(level.name, gameMode.name, rounds);
            commandHandler->sendMapListAddCommand(level.engineName, gameMode.engineName, rounds);
        }
    }
}

void MapListWidget::pushButton_ml_remove_clicked()
{
    // Make sure that treeWidget_ml_current selected item count is greater than zero.
    if (ui->treeWidget_ml_current->selectedItems().size() > 0) {
        if (ui->treeWidget_ml_current->topLevelItemCount() < 1) {
            ui->label_ml_currentSelectedMapImage->clear();
        }

        int index = ui->treeWidget_ml_current->currentIndex().row();

        ui->treeWidget_ml_current->takeTopLevelItem(index);
        commandHandler->sendMapListRemoveCommand(index);
    }
}

void MapListWidget::addAvailableMapListRow(const QString &name, const QString &gameMode)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, gameMode);

    ui->treeWidget_ml_available->addTopLevelItem(item);
}

void MapListWidget::setAvailableMaplist(int gameModeIndex)
{
    ui->treeWidget_ml_available->clear();

    QList<LevelEntry> levelList = BF4LevelDictionary::getLevels(gameModeIndex);
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(gameModeIndex);

    ui->label_ml_availableSelectedMapImage->setPixmap(levelList.first().image());

    for (LevelEntry level : levelList) {
        addAvailableMapListRow(level.name, gameMode.name);
    }

    ui->treeWidget_ml_available->sortItems(0, Qt::AscendingOrder);

    // Resize columns so that they fits the content.
    for (int i = 0; i < ui->treeWidget_ml_available->columnCount(); i++) {
        ui->treeWidget_ml_available->resizeColumnToContents(i);
    }
}

void MapListWidget::treeWidget_ml_current_itemSelectionChanged()
{
    if (ui->treeWidget_ml_current->topLevelItemCount() > 1) {
        LevelEntry level = BF4LevelDictionary::getLevel(ui->treeWidget_ml_current->currentItem()->text(0));

        ui->label_ml_currentSelectedMapImage->setPixmap(level.image());
    }
}

void MapListWidget::treeWidget_ml_current_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_ml_current->itemAt(pos)) {
        menu_ml_current->exec(QCursor::pos());
    }
}

void MapListWidget::addCurrentMapListRow(const QString &name, const QString &gameMode, int rounds)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, gameMode);
    item->setText(2, QString::number(rounds));

    ui->treeWidget_ml_current->addTopLevelItem(item);
}

void MapListWidget::setCurrentMaplist(const MapList &mapList)
{
    ui->treeWidget_ml_current->clear();

    for (int i = 0; i < mapList.length(); i++) {
        MapListEntry entry = mapList.at(i);
        LevelEntry level = BF4LevelDictionary::getLevel(entry.level);
        GameModeEntry gameMode = BF4LevelDictionary::getGameMode(entry.gameMode);

        if (i == 0) {
            ui->label_ml_currentSelectedMapImage->setPixmap(level.image());
        }

        addCurrentMapListRow(level.name, gameMode.name, entry.rounds);
    }

    ui->treeWidget_ml_current->sortItems(0, Qt::AscendingOrder);

    // Resize columns so that they fits the content.
    for (int i = 0; i < ui->treeWidget_ml_available->columnCount(); i++) {
        ui->treeWidget_ml_current->resizeColumnToContents(i);
    }
}
