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

#ifndef MAPLISTWIDGET_H
#define MAPLISTWIDGET_H

#include <QWidget>

class QMenu;
class QAction;
class QTreeWidgetItem;
class FrostbiteConnection;
class BF4CommandHandler;
struct BF4ServerInfo;
struct MapListEntry;

namespace Ui {
    class MapListWidget;
}

class MapListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapListWidget(FrostbiteConnection *connection, QWidget *parent = nullptr);
    ~MapListWidget();

private:
    Ui::MapListWidget *ui;
    FrostbiteConnection *connection;
    BF4CommandHandler *commandHandler;

    // Maplist
    QMenu *menu_ml_available;
    QAction *action_ml_available_add;
    QMenu *menu_ml_current;
    QAction *action_ml_current_remove;

private slots:
    /* Commands */
    void onLoginHashedCommand(bool auth);
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);
    void onMapListListCommand(const QList<MapListEntry> &mapList);

    /* User Interface */
    void comboBox_ml_gameMode_currentIndexChanged(int);
    void treeWidget_ml_available_itemSelectionChanged();
    void treeWidget_ml_available_customContextMenuRequested(const QPoint &pos);
    void pushButton_ml_load_clicked();
    void pushButton_ml_save_clicked();
    void pushButton_ml_clear_clicked();
    void pushButton_ml_add_clicked();
    void pushButton_ml_remove_clicked();
    void treeWidget_ml_current_itemSelectionChanged();
    void treeWidget_ml_current_customContextMenuRequested(const QPoint &pos);

    void addAvailableMapListItem(const QString &name, const QString &gameMode);
    void setAvailableMaplist(int gameModeIndex);
    void addCurrentMapListItem(const QString &name, const QString &gameMode, int rounds);
    void setCurrentMaplist(const QList<MapListEntry> &mapList);
    void addLevel(const QString &name, const QString &gameMode, int rounds);
    void removeLevel(int index);

    void treeWidget_ml_available_itemDrop(int index);
    void treeWidget_ml_current_itemDrop(const QTreeWidgetItem *item);

};

#endif // MAPLISTWIDGET_H
