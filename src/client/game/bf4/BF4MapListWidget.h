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

#ifndef BF4MAPLISTWIDGET_H
#define BF4MAPLISTWIDGET_H

#include "BF4Widget.h"

class QMenu;
class QAction;
class QTreeWidgetItem;

class Frostbite2ServerInfo;
class MapListEntry;

namespace Ui {
    class BF4MapListWidget;
}

class BF4MapListWidget : public BF4Widget
{
    Q_OBJECT

public:
    BF4MapListWidget(BF4Client *client, QWidget *parent = nullptr);
    ~BF4MapListWidget() final;

private:
    Ui::BF4MapListWidget *ui;

    void setAvailableMaplist(int gameModeIndex);
    void addAvailableMapListItem(const QString &name, const QString &gameMode);
    void setCurrentMaplist(const QList<MapListEntry> &mapList);
    void addCurrentMapListItem(const QString &name, const QString &gameMode, int rounds);
    void addLevel(const QString &name, const QString &gameMode, int rounds);
    void removeLevel(int index);

    /* User Interface */
    // Maplist
    QMenu *menu_available;
    QAction *action_available_add;
    QMenu *menu_current;
    QAction *action_current_remove;

private slots:
    /* Client */
    void onAuthenticated();

    /* Commands */
    void onServerInfoCommand(const Frostbite2ServerInfo &serverInfo);
    void onMapListListCommand(const QList<MapListEntry> &mapList);

    /* User Interface */
    void comboBox_gameMode_currentIndexChanged(int);
    void treeWidget_available_itemSelectionChanged();
    void treeWidget_available_customContextMenuRequested(const QPoint &pos);
    void pushButton_load_clicked();
    void pushButton_save_clicked();
    void pushButton_clear_clicked();
    void pushButton_add_clicked();
    void pushButton_remove_clicked();
    void treeWidget_current_itemSelectionChanged();
    void treeWidget_current_customContextMenuRequested(const QPoint &pos);
    void treeWidget_available_itemDrop(int index);
    void treeWidget_current_itemDrop(QTreeWidgetItem *item);

};

#endif // BF4MAPLISTWIDGET_H
