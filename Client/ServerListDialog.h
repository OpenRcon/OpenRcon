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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SERVERLISTDIALOG_H
#define SERVERLISTDIALOG_H

#include <QDialog>
#include <QMenu>
#include <QMessageBox>
#include <QTreeWidgetItem>

#include "Constants.h"

using namespace Constants;

struct ServerEntry;

class OpenRcon;
class ServerManager;

namespace Ui {
    class ServerListDialog;
}

class ServerListDialog : public QDialog
{
    Q_OBJECT

public:
    ServerListDialog(QWidget *parent = nullptr);
    ~ServerListDialog();

private:
    Ui::ServerListDialog *ui;

    OpenRcon *openRcon;
    ServerManager *serverManager;

    QMenu *menu_gameEntry;
    QAction *action_gameEntry_add;

    QMenu *menu_serverEntry;
    QAction *action_serverEntry_edit;
    QAction *action_serverEntry_remove;

    QList<ServerEntry *> serverEntries;

    void createTreeData();

private slots:
    void treeWidget_customContextMenuRequested(const QPoint &pos);
    void treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void action_gameEntry_add_triggered();

    void addItem(int game = -1);
    void editItem();
    void removeItem();
    void connectToItem();

    void accept();

};

#endif // SERVERLISTDIALOG_H
