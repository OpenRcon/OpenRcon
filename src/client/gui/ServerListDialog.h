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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SERVERLISTDIALOG_H
#define SERVERLISTDIALOG_H

#include <QDialog>
#include <QList>

#include "Constants.h"

using namespace Constants;

class QWidget;
class QMenu;
class QAction;
class QPoint;
class QTreeWidgetItem;

class ServerManager;
class SessionManager;
class ServerEntry;

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

    ServerManager *serverManager;
    SessionManager *sessionManager;

    QMenu *menu_gameEntry;
    QAction *action_gameEntry_add;

    QMenu *menu_serverEntry;
    QAction *action_serverEntry_edit;
    QAction *action_serverEntry_remove;

    QList<ServerEntry*> serverEntries;

    void createTreeData();

private slots:
    void onSessionOpened();
    void onSessionClosed();
    void treeWidget_customContextMenuRequested(const QPoint &pos);
    void treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void action_gameEntry_add_triggered();

    void addItem(int index = -1);
    void editItem();
    void removeItem();
    void connectToItem();

    void accept();

};

#endif // SERVERLISTDIALOG_H
