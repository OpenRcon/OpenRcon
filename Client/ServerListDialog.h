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

#include "OpenRcon.h"

#include "GameManager.h"
#include "ServerManager.h"
#include "ServerEditDialog.h"

using namespace Constants;

class ServerListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerListDialog(QWidget *parent = 0);
    ~ServerListDialog();

private:
    Ui::ServerListDialog *ui;

    GameManager *gameManager;
    ServerManager *serverManager;

    QMenu *menu_sld_serverEntry;

    void createTreeData();
    void deleteTreeData();

private slots:
    void treeWidget_customContextMenuRequested(QPoint pos);
    void treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem*);

    void addItem();
    void editItem();
    void removeItem();

    void accept();

};

#endif // SERVERLISTDIALOG_H
