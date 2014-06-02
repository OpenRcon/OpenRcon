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

#include "MapListWidget.h"
#include "ui_MapListWidget.h"
#include "FrostbiteConnection.h"
#include "BF4CommandHandler.h"
#include "LevelEntry.h"
#include "BF4LevelDictionary.h"
#include "BF4ServerInfo.h"
#include "BF4GameModeEntry.h"

MapListWidget::MapListWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapListWidget),
    m_connection(connection),
    m_commandHandler(dynamic_cast<BF4CommandHandler *>(connection->getCommandHandler()))
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
    // Misc
    connect(m_commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &MapListWidget::onLoginHashedCommand);
    connect(m_commandHandler, &BF4CommandHandler::onServerInfoCommand,                                                              this, &MapListWidget::onServerInfoCommand);

    // MapList
    connect(m_commandHandler, &BF4CommandHandler::onMapListListCommand,                                                             this, &MapListWidget::onMapListListCommand);

    /* User Interface */
    connect(ui->comboBox_ml_gameMode,    static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MapListWidget::comboBox_ml_gameMode_currentIndexChanged);
    connect(ui->treeWidget_ml_available, &QTreeWidget::itemSelectionChanged,                                     this, &MapListWidget::treeWidget_ml_available_itemSelectionChanged);
    connect(ui->treeWidget_ml_available, &QTreeWidget::customContextMenuRequested,                               this, &MapListWidget::treeWidget_ml_available_customContextMenuRequested);
    connect(action_ml_available_add,     &QAction::triggered,                                                    this, &MapListWidget::pushButton_ml_add_clicked);
    connect(ui->pushButton_ml_load,      &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_ml_load_clicked);
    connect(ui->pushButton_ml_save,      &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_ml_save_clicked);
    connect(ui->pushButton_ml_clear,     &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_ml_clear_clicked);
    connect(ui->pushButton_ml_add,       &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_ml_add_clicked);
    connect(ui->pushButton_ml_remove,    &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_ml_remove_clicked);
    connect(ui->treeWidget_ml_current,   &QTreeWidget::itemSelectionChanged,                                     this, &MapListWidget::treeWidget_ml_current_itemSelectionChanged);
    connect(ui->treeWidget_ml_current,   &QTreeWidget::customContextMenuRequested,                               this, &MapListWidget::treeWidget_ml_current_customContextMenuRequested);
    connect(action_ml_current_remove,    &QAction::triggered,                                                    this, &MapListWidget::pushButton_ml_remove_clicked);

    connect(ui->treeWidget_ml_available, static_cast<void (DragDropTreeWidget::*)(int)>(&DragDropTreeWidget::itemDrop),              this, &MapListWidget::treeWidget_ml_available_itemDrop);
    connect(ui->treeWidget_ml_current,   static_cast<void (DragDropTreeWidget::*)(QTreeWidgetItem*)>(&DragDropTreeWidget::itemDrop), this, &MapListWidget::treeWidget_ml_current_itemDrop);
}

MapListWidget::~MapListWidget()
{
    delete ui;
}

void MapListWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        m_commandHandler->sendServerInfoCommand();
        m_commandHandler->sendMapListListCommand();
    }
}

void MapListWidget::onServerInfoCommand(const BF4ServerInfo &serverInfo)
{
    LevelEntry level = BF4LevelDictionary::getLevel(serverInfo.currentMap);
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(serverInfo.gameMode);

    int gameModeIndex = BF4LevelDictionary::getGameModeNames().indexOf(gameMode.name);

    ui->label_ml_currentMapValue->setText(level.name);
    ui->label_ml_currentMapImage->setPixmap(level.image());

    ui->comboBox_ml_gameMode->setCurrentIndex(gameModeIndex);
    setAvailableMaplist(gameModeIndex);
}

void MapListWidget::onMapListListCommand(const QList<MapListEntry> &mapList)
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

void MapListWidget::pushButton_ml_load_clicked()
{
    m_commandHandler->sendMapListLoadCommand();
}

void MapListWidget::pushButton_ml_save_clicked()
{
    m_commandHandler->sendMapListSaveCommand();
}

void MapListWidget::pushButton_ml_clear_clicked()
{
    m_commandHandler->sendMapListClearCommand();
}

void MapListWidget::pushButton_ml_add_clicked()
{
    // Make sure that treeWidget_ml_available selected item count is greater than zero.
    if (ui->treeWidget_ml_available->selectedItems().size() > 0) {
        QString name = ui->treeWidget_ml_available->currentItem()->text(0);
        QString gameMode = ui->treeWidget_ml_available->currentItem()->text(1);
        int rounds = ui->spinBox_ml_rounds->value();

        addLevel(name, gameMode, rounds);
    }
}

void MapListWidget::pushButton_ml_remove_clicked()
{
    // Make sure that treeWidget_ml_current selected item count is greater than zero.
    if (ui->treeWidget_ml_current->selectedItems().size() > 0) {
        int index = ui->treeWidget_ml_current->currentIndex().row();

        removeLevel(index);
    }
}

void MapListWidget::addAvailableMapListItem(const QString &name, const QString &gameMode)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_ml_available);
    item->setText(0, name);
    item->setText(1, gameMode);
}

void MapListWidget::setAvailableMaplist(int gameModeIndex)
{
    ui->treeWidget_ml_available->clear();

    QList<LevelEntry> levelList = BF4LevelDictionary::getLevels(gameModeIndex);
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(gameModeIndex);

    ui->label_ml_availableSelectedMapImage->setPixmap(levelList.first().image());

    for (LevelEntry level : levelList) {
        addAvailableMapListItem(level.name, gameMode.name);
    }

    // Sort items.
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

void MapListWidget::treeWidget_ml_available_itemDrop(int index)
{
    removeLevel(index);
}

void MapListWidget::treeWidget_ml_current_itemDrop(QTreeWidgetItem *item)
{
    addLevel(item->text(0), item->text(1), ui->spinBox_ml_rounds->value());
}

void MapListWidget::addCurrentMapListItem(const QString &name, const QString &gameMode, int rounds)
{
    // Add the item to the QTreeWidget.
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_ml_current);
    item->setText(0, name);
    item->setText(1, gameMode);
    item->setText(2, QString::number(rounds));
}

void MapListWidget::setCurrentMaplist(const QList<MapListEntry> &mapList)
{
    ui->treeWidget_ml_current->clear();

    for (int i = 0; i < mapList.length(); i++) {
        MapListEntry entry = mapList.at(i);
        LevelEntry level = BF4LevelDictionary::getLevel(entry.level);
        BF4GameModeEntry gameMode = BF4LevelDictionary::getGameMode(entry.gameMode);

        if (i == 0) {
            ui->label_ml_currentSelectedMapImage->setPixmap(level.image());
        }

        addCurrentMapListItem(level.name, gameMode.name, entry.rounds);
    }

    // Resize columns so that they fits the content.
    for (int i = 0; i < ui->treeWidget_ml_available->columnCount(); i++) {
        ui->treeWidget_ml_current->resizeColumnToContents(i);
    }
}

void MapListWidget::addLevel(const QString &name, const QString &gameMode, int rounds)
{
    if (rounds > 0) {
        LevelEntry levelEntry = BF4LevelDictionary::getLevel(name);
        BF4GameModeEntry gameModeEntry = BF4LevelDictionary::getGameMode(gameMode);

        ui->label_ml_currentSelectedMapImage->setPixmap(levelEntry.image());
        addCurrentMapListItem(name, gameMode, rounds);
        m_commandHandler->sendMapListAddCommand(levelEntry.engineName, gameModeEntry.engineName, rounds);
    }
}

void MapListWidget::removeLevel(int index)
{
    if (ui->treeWidget_ml_current->topLevelItemCount() <= 1) {
        ui->label_ml_currentSelectedMapImage->clear();
    }

    ui->treeWidget_ml_current->takeTopLevelItem(index);
    m_commandHandler->sendMapListRemoveCommand(index);
}
