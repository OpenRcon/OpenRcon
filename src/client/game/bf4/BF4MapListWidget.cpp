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

#include "BF4MapListWidget.h"
#include "ui_BF4MapListWidget.h"

#include "LevelEntry.h"
#include "BF4LevelDictionary.h"
#include "Frostbite2ServerInfo.h"
#include "BF4GameModeEntry.h"
#include "MapListEntry.h"

BF4MapListWidget::BF4MapListWidget(BF4Client *client, QWidget *parent) :
    BF4Widget(client, parent),
    ui(new Ui::BF4MapListWidget)
{
    ui->setupUi(this);

    // Set default values
    ui->comboBox_gameMode->addItems(BF4LevelDictionary::getGameModeNames());
    setAvailableMaplist(0);

    // Add menus
    menu_available = new QMenu(ui->treeWidget_available);
    action_available_add = new QAction(tr("Add"), menu_available);
    menu_current = new QMenu(ui->treeWidget_current);
    action_current_remove = new QAction(tr("Remove"), menu_current);

    menu_available->addAction(action_available_add);
    menu_current->addAction(action_current_remove);

    /* Client */
    connect(getClient(),                        &Client::onAuthenticated,                                                                   getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendServerInfoCommand);
    connect(getClient(),                        &Client::onAuthenticated,                                                                   this, &BF4MapListWidget::onAuthenticated);

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (Frostbite2CommandHandler::*)(const Frostbite2ServerInfo&)>(&Frostbite2CommandHandler::onServerInfoCommand),
            this, &BF4MapListWidget::onServerInfoCommand);

    // MapList
    connect(getClient()->getCommandHandler(),   &BF4CommandHandler::onMapListListCommand,                                                   this, &BF4MapListWidget::onMapListListCommand);

    /* User Interface */
    connect(action_available_add,               &QAction::triggered,                                                                        this, &BF4MapListWidget::pushButton_add_clicked);
    connect(action_current_remove,              &QAction::triggered,                                                                        this, &BF4MapListWidget::pushButton_remove_clicked);
    connect(ui->treeWidget_available,           &QTreeWidget::itemSelectionChanged,                                                         this, &BF4MapListWidget::treeWidget_available_itemSelectionChanged);
    connect(ui->treeWidget_available,           &QTreeWidget::customContextMenuRequested,                                                   this, &BF4MapListWidget::treeWidget_available_customContextMenuRequested);
    connect(ui->treeWidget_available,           static_cast<void (DragDropTreeWidget::*)(int)>(&DragDropTreeWidget::itemDrop),              this, &BF4MapListWidget::treeWidget_available_itemDrop);
    connect(ui->treeWidget_current,             &QTreeWidget::itemSelectionChanged,                                                         this, &BF4MapListWidget::treeWidget_current_itemSelectionChanged);
    connect(ui->treeWidget_current,             &QTreeWidget::customContextMenuRequested,                                                   this, &BF4MapListWidget::treeWidget_current_customContextMenuRequested);
    connect(ui->treeWidget_current,             static_cast<void (DragDropTreeWidget::*)(QTreeWidgetItem*)>(&DragDropTreeWidget::itemDrop), this, &BF4MapListWidget::treeWidget_current_itemDrop);
    connect(ui->comboBox_gameMode,              static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),                     this, &BF4MapListWidget::comboBox_gameMode_currentIndexChanged);
    connect(ui->pushButton_load,                &QPushButton::clicked,                                                                      this, &BF4MapListWidget::pushButton_load_clicked);
    connect(ui->pushButton_save,                &QPushButton::clicked,                                                                      this, &BF4MapListWidget::pushButton_save_clicked);
    connect(ui->pushButton_clear,               &QPushButton::clicked,                                                                      this, &BF4MapListWidget::pushButton_clear_clicked);
    connect(ui->pushButton_add,                 &QPushButton::clicked,                                                                      this, &BF4MapListWidget::pushButton_add_clicked);
    connect(ui->pushButton_remove,              &QPushButton::clicked,                                                                      this, &BF4MapListWidget::pushButton_remove_clicked);

    }

BF4MapListWidget::~BF4MapListWidget()
{
    delete ui;
}

void BF4MapListWidget::setAvailableMaplist(int gameModeIndex)
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

void BF4MapListWidget::addAvailableMapListItem(const QString &name, const QString &gameMode)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_available);
    item->setText(0, name);
    item->setText(1, gameMode);
}

void BF4MapListWidget::setCurrentMaplist(const QList<MapListEntry> &mapList)
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

void BF4MapListWidget::addCurrentMapListItem(const QString &name, const QString &gameMode, int rounds)
{
    // Add the item to the QTreeWidget.
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_current);
    item->setText(0, name);
    item->setText(1, gameMode);
    item->setText(2, QString::number(rounds));
}

void BF4MapListWidget::addLevel(const QString &name, const QString &gameMode, int rounds)
{
    if (rounds > 0) {
        LevelEntry levelEntry = BF4LevelDictionary::getLevel(name);
        BF4GameModeEntry gameModeEntry = BF4LevelDictionary::getGameMode(gameMode);

        ui->label_currentSelectedMapImage->setPixmap(levelEntry.getImage());
        addCurrentMapListItem(name, gameMode, rounds);
        getClient()->getCommandHandler()->sendMapListAddCommand(levelEntry.getEngineName(), gameModeEntry.getEngineName(), rounds);
    }
}

void BF4MapListWidget::removeLevel(int index)
{
    if (ui->treeWidget_current->topLevelItemCount() <= 1) {
        ui->label_currentSelectedMapImage->clear();
    }

    ui->treeWidget_current->takeTopLevelItem(index);
    getClient()->getCommandHandler()->sendMapListRemoveCommand(index);
}

/* Client */
void BF4MapListWidget::onAuthenticated()
{
    getClient()->getCommandHandler()->sendMapListListCommand();
}

/* Commands */
void BF4MapListWidget::onServerInfoCommand(const Frostbite2ServerInfo &serverInfo)
{
    LevelEntry level = BF4LevelDictionary::getLevel(serverInfo.getCurrentMap());
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(serverInfo.getGameMode());
    int gameModeIndex = BF4LevelDictionary::getGameModeNames().indexOf(gameMode.getName());

    ui->label_currentMapValue->setText(level.getName());
    ui->label_currentMapImage->setPixmap(level.getImage());

    ui->comboBox_gameMode->setCurrentIndex(gameModeIndex);
    setAvailableMaplist(gameModeIndex);
}

void BF4MapListWidget::onMapListListCommand(const QList<MapListEntry> &mapList)
{   
    ui->pushButton_clear->setEnabled(!mapList.isEmpty());
    ui->pushButton_remove->setEnabled(!mapList.isEmpty());

    setCurrentMaplist(mapList);
}

/* User Interface */
void BF4MapListWidget::comboBox_gameMode_currentIndexChanged(int index)
{
    setAvailableMaplist(index);
}

void BF4MapListWidget::treeWidget_available_itemSelectionChanged()
{
    LevelEntry level = BF4LevelDictionary::getLevel(ui->treeWidget_available->currentItem()->text(0));

    ui->label_availableSelectedMapImage->setPixmap(level.getImage());
}

void BF4MapListWidget::treeWidget_available_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_available->itemAt(pos)) {
        menu_available->exec(QCursor::pos());
    }
}

void BF4MapListWidget::pushButton_load_clicked()
{
    getClient()->getCommandHandler()->sendMapListLoadCommand();
}

void BF4MapListWidget::pushButton_save_clicked()
{
    getClient()->getCommandHandler()->sendMapListSaveCommand();
}

void BF4MapListWidget::pushButton_clear_clicked()
{
    getClient()->getCommandHandler()->sendMapListClearCommand();
}

void BF4MapListWidget::pushButton_add_clicked()
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

void BF4MapListWidget::pushButton_remove_clicked()
{
    // Make sure that treeWidget_current selected item count is greater than zero.
    if (ui->treeWidget_current->selectedItems().size() > 0) {
        int index = ui->treeWidget_current->currentIndex().row();

        removeLevel(index);
        ui->pushButton_clear->setEnabled(ui->treeWidget_current->topLevelItemCount() > 0);
        ui->pushButton_remove->setEnabled(ui->treeWidget_current->topLevelItemCount() > 0);
    }
}

void BF4MapListWidget::treeWidget_current_itemSelectionChanged()
{
    if (ui->treeWidget_current->topLevelItemCount() > 1) {
        LevelEntry level = BF4LevelDictionary::getLevel(ui->treeWidget_current->currentItem()->text(0));

        ui->label_currentSelectedMapImage->setPixmap(level.getImage());
    }
}

void BF4MapListWidget::treeWidget_current_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_current->itemAt(pos)) {
        menu_current->exec(QCursor::pos());
    }
}

void BF4MapListWidget::treeWidget_available_itemDrop(int index)
{
    removeLevel(index);
}

void BF4MapListWidget::treeWidget_current_itemDrop(QTreeWidgetItem *item)
{
    addLevel(item->text(0), item->text(1), ui->spinBox_rounds->value());
}
