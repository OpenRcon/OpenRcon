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
    ui->comboBox_gameMode->addItems(BF4LevelDictionary::getGameModeNames());
    ui->spinBox_rounds->setValue(2);
    setAvailableMaplist(0);

    // Add menus
    menu_available = new QMenu(ui->treeWidget_available);
    action_available_add = new QAction(tr("Add"), menu_available);
    menu_current = new QMenu(ui->treeWidget_current);
    action_current_remove = new QAction(tr("Remove"), menu_current);

    menu_available->addAction(action_available_add);
    menu_current->addAction(action_current_remove);

    /* Commands */
    // Misc
    connect(m_commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &MapListWidget::onLoginHashedCommand);
    connect(m_commandHandler, &BF4CommandHandler::onServerInfoCommand,                                                              this, &MapListWidget::onServerInfoCommand);

    // MapList
    connect(m_commandHandler, &BF4CommandHandler::onMapListListCommand,                                                             this, &MapListWidget::onMapListListCommand);

    /* User Interface */
    connect(ui->comboBox_gameMode,    static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MapListWidget::comboBox_gameMode_currentIndexChanged);
    connect(ui->treeWidget_available, &QTreeWidget::itemSelectionChanged,                                     this, &MapListWidget::treeWidget_available_itemSelectionChanged);
    connect(ui->treeWidget_available, &QTreeWidget::customContextMenuRequested,                               this, &MapListWidget::treeWidget_available_customContextMenuRequested);
    connect(action_available_add,     &QAction::triggered,                                                    this, &MapListWidget::pushButton_add_clicked);
    connect(ui->pushButton_load,      &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_load_clicked);
    connect(ui->pushButton_save,      &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_save_clicked);
    connect(ui->pushButton_clear,     &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_clear_clicked);
    connect(ui->pushButton_add,       &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_add_clicked);
    connect(ui->pushButton_remove,    &QPushButton::clicked,                                                  this, &MapListWidget::pushButton_remove_clicked);
    connect(ui->treeWidget_current,   &QTreeWidget::itemSelectionChanged,                                     this, &MapListWidget::treeWidget_current_itemSelectionChanged);
    connect(ui->treeWidget_current,   &QTreeWidget::customContextMenuRequested,                               this, &MapListWidget::treeWidget_current_customContextMenuRequested);
    connect(action_current_remove,    &QAction::triggered,                                                    this, &MapListWidget::pushButton_remove_clicked);

    connect(ui->treeWidget_available, static_cast<void (DragDropTreeWidget::*)(int)>(&DragDropTreeWidget::itemDrop),              this, &MapListWidget::treeWidget_available_itemDrop);
    connect(ui->treeWidget_current,   static_cast<void (DragDropTreeWidget::*)(QTreeWidgetItem*)>(&DragDropTreeWidget::itemDrop), this, &MapListWidget::treeWidget_current_itemDrop);
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
    LevelEntry level = BF4LevelDictionary::getLevel(serverInfo.getCurrentMap());
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(serverInfo.getGameMode());

    int gameModeIndex = BF4LevelDictionary::getGameModeNames().indexOf(gameMode.getName());

    ui->label_currentMapValue->setText(level.getName());
    ui->label_currentMapImage->setPixmap(level.getImage());

    ui->comboBox_gameMode->setCurrentIndex(gameModeIndex);
    setAvailableMaplist(gameModeIndex);
}

void MapListWidget::onMapListListCommand(const QList<MapListEntry> &mapList)
{   
    ui->pushButton_clear->setEnabled(!mapList.isEmpty());
    ui->pushButton_remove->setEnabled(!mapList.isEmpty());

    setCurrentMaplist(mapList);
}

void MapListWidget::comboBox_gameMode_currentIndexChanged(int index)
{
    setAvailableMaplist(index);
}

void MapListWidget::treeWidget_available_itemSelectionChanged()
{
    LevelEntry level = BF4LevelDictionary::getLevel(ui->treeWidget_available->currentItem()->text(0));

    ui->label_availableSelectedMapImage->setPixmap(level.getImage());
}

void MapListWidget::treeWidget_available_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_available->itemAt(pos)) {
        menu_available->exec(QCursor::pos());
    }
}

void MapListWidget::pushButton_load_clicked()
{
    m_commandHandler->sendMapListLoadCommand();
}

void MapListWidget::pushButton_save_clicked()
{
    m_commandHandler->sendMapListSaveCommand();
}

void MapListWidget::pushButton_clear_clicked()
{
    m_commandHandler->sendMapListClearCommand();
}

void MapListWidget::pushButton_add_clicked()
{
    // Make sure that treeWidget_available selected item count is greater than zero.
    if (ui->treeWidget_available->selectedItems().size() > 0) {
        QString name = ui->treeWidget_available->currentItem()->text(0);
        QString gameMode = ui->treeWidget_available->currentItem()->text(1);
        int rounds = ui->spinBox_rounds->value();

        addLevel(name, gameMode, rounds);
        ui->pushButton_clear->setEnabled(ui->treeWidget_current->topLevelItemCount() > 0);
        ui->pushButton_remove->setEnabled(ui->treeWidget_current->topLevelItemCount() > 0);
    }
}

void MapListWidget::pushButton_remove_clicked()
{
    // Make sure that treeWidget_current selected item count is greater than zero.
    if (ui->treeWidget_current->selectedItems().size() > 0) {
        int index = ui->treeWidget_current->currentIndex().row();

        removeLevel(index);
        ui->pushButton_clear->setEnabled(ui->treeWidget_current->topLevelItemCount() > 0);
        ui->pushButton_remove->setEnabled(ui->treeWidget_current->topLevelItemCount() > 0);
    }
}

void MapListWidget::addAvailableMapListItem(const QString &name, const QString &gameMode)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_available);
    item->setText(0, name);
    item->setText(1, gameMode);
}

void MapListWidget::setAvailableMaplist(int gameModeIndex)
{
    ui->treeWidget_available->clear();

    QList<LevelEntry> levelList = BF4LevelDictionary::getLevels(gameModeIndex);
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(gameModeIndex);

    ui->label_availableSelectedMapImage->setPixmap(levelList.first().getImage());

    for (LevelEntry level : levelList) {
        addAvailableMapListItem(level.getName(), gameMode.getName());
    }

    // Sort items.
    ui->treeWidget_available->sortItems(0, Qt::AscendingOrder);

    // Resize columns so that they fits the content.
    for (int i = 0; i < ui->treeWidget_available->columnCount(); i++) {
        ui->treeWidget_available->resizeColumnToContents(i);
    }
}

void MapListWidget::treeWidget_current_itemSelectionChanged()
{
    if (ui->treeWidget_current->topLevelItemCount() > 1) {
        LevelEntry level = BF4LevelDictionary::getLevel(ui->treeWidget_current->currentItem()->text(0));

        ui->label_currentSelectedMapImage->setPixmap(level.getImage());
    }
}

void MapListWidget::treeWidget_current_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_current->itemAt(pos)) {
        menu_current->exec(QCursor::pos());
    }
}

void MapListWidget::treeWidget_available_itemDrop(int index)
{
    removeLevel(index);
}

void MapListWidget::treeWidget_current_itemDrop(QTreeWidgetItem *item)
{
    addLevel(item->text(0), item->text(1), ui->spinBox_rounds->value());
}

void MapListWidget::addCurrentMapListItem(const QString &name, const QString &gameMode, int rounds)
{
    // Add the item to the QTreeWidget.
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_current);
    item->setText(0, name);
    item->setText(1, gameMode);
    item->setText(2, QString::number(rounds));
}

void MapListWidget::setCurrentMaplist(const QList<MapListEntry> &mapList)
{
    ui->treeWidget_current->clear();

    for (int i = 0; i < mapList.length(); i++) {
        MapListEntry mapListEntry = mapList.at(i);
        LevelEntry level = BF4LevelDictionary::getLevel(mapListEntry.getLevel());
        BF4GameModeEntry gameMode = BF4LevelDictionary::getGameMode(mapListEntry.getGameMode());

        if (i == 0) {
            ui->label_currentSelectedMapImage->setPixmap(level.getImage());
        }

        addCurrentMapListItem(level.getName(), gameMode.getName(), mapListEntry.getRounds());
    }

    // Resize columns so that they fits the content.
    for (int i = 0; i < ui->treeWidget_available->columnCount(); i++) {
        ui->treeWidget_current->resizeColumnToContents(i);
    }
}

void MapListWidget::addLevel(const QString &name, const QString &gameMode, int rounds)
{
    if (rounds > 0) {
        LevelEntry levelEntry = BF4LevelDictionary::getLevel(name);
        BF4GameModeEntry gameModeEntry = BF4LevelDictionary::getGameMode(gameMode);

        ui->label_currentSelectedMapImage->setPixmap(levelEntry.getImage());
        addCurrentMapListItem(name, gameMode, rounds);
        m_commandHandler->sendMapListAddCommand(levelEntry.getEngineName(), gameModeEntry.getEngineName(), rounds);
    }
}

void MapListWidget::removeLevel(int index)
{
    if (ui->treeWidget_current->topLevelItemCount() <= 1) {
        ui->label_currentSelectedMapImage->clear();
    }

    ui->treeWidget_current->takeTopLevelItem(index);
    m_commandHandler->sendMapListRemoveCommand(index);
}
