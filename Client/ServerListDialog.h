/*
 * Copyright (C) 2011 The OpenRcon Project.
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

#include <QDebug>
#include <QDialog>
#include <QMenu>
#include <QMessageBox>

#include "ui_ServerListDialog.h"

#include "ServerManager.h"
#include "ServerEditDialog.h"
#include "ServerTableModel.h"

using namespace Constants;

class ServerListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerListDialog(QObject *parent = 0);
    ~ServerListDialog();

private:
    Ui::ServerListDialog *ui;

    ServerManager *serverManager;

    QSettings *settings;
    QMap<int, QIcon> m_IconMap;
    QMap<int, QList<ServerEntry*>*> m_Data;
    QList<ServerEntry> m_ServerEntries;
    QList<QTreeWidgetItem*>* m_RootItems;

    QMenu *menu_sld_serverEntry;

    void createTreeData();
    void deleteTreeData();

private slots:
    void treeWidget_customContextMenuRequested(QPoint pos);
    void treeWidget_currentItemChanged(QTreeWidgetItem *item, QTreeWidgetItem*);

    void addItem();
    void editItem();
    void removeItem();

    void accept();
    void reject();

};

#endif // SERVERLISTDIALOG_H
