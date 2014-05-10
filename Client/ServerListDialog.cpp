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

#include "ServerListDialog.h"

ServerListDialog::ServerListDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ServerListDialog)
{
    ui->setupUi(this);

    gameManager = new GameManager(this);
    serverManager = new ServerManager(this);

    // Sets application icon
    setWindowIcon(QIcon(APP_ICON));

    // Add a menu for the ServerItems
    menu_serverEntry = new QMenu(ui->treeWidget);
    action_serverEntry_edit = new QAction(tr("Edit"), menu_serverEntry);
    action_serverEntry_remove = new QAction(tr("Remove"), menu_serverEntry);

    menu_serverEntry->addAction(action_serverEntry_edit);
    menu_serverEntry->addAction(action_serverEntry_remove);

    ui->pushButton_sld_connect->setEnabled(false);

    createTreeData();

    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_customContextMenuRequested(QPoint)));
    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(treeWidget_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeWidget_itemChanged(QTreeWidgetItem*, int)));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(accept()));

    connect(action_serverEntry_edit, SIGNAL(triggered()), this, SLOT(editItem()));
    connect(action_serverEntry_remove, SIGNAL(triggered()), this, SLOT(removeItem()));
    connect(ui->pushButton_sld_add, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->pushButton_sld_connect, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButton_sld_cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

ServerListDialog::~ServerListDialog()
{
    deleteTreeData();

    delete ui;
}

void ServerListDialog::treeWidget_customContextMenuRequested(QPoint pos)
{
    if (ui->treeWidget->itemAt(pos) && ui->treeWidget->currentItem()->parent()) {
        menu_serverEntry->exec(QCursor::pos());
    }
}

void ServerListDialog::treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);

    ui->pushButton_sld_connect->setEnabled(current && current->parent());
}

void ServerListDialog::treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    if (column == 3) {
        QVariant variant = item->data(0, Qt::UserRole);
        ServerEntry *entry = variant.value<ServerEntry *>();

        // Sets the checked state of autoconnect.
        entry->autoConnect = item->checkState(column) == Qt::Checked ? true : false;

        // Set the server to the new values obtained by ServerEditDialog.
        serverManager->setServers(serverEntries);
    }
}

void ServerListDialog::createTreeData()
{
    deleteTreeData();

    foreach (GameEntry gameEntry, gameManager->getGames()) {
        QList<ServerEntry *> list = serverManager->getServers(gameEntry.id);

        if (!list.isEmpty()) {
            QTreeWidgetItem *parentItem = new QTreeWidgetItem(ui->treeWidget);
            parentItem->setIcon(0, gameEntry.icon);
            parentItem->setText(0, gameEntry.name);

            foreach (ServerEntry *serverEntry, list) {
                if (serverEntry->game == gameEntry.id) {
                    serverEntries.append(serverEntry);

                    QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
                    childItem->setData(0, Qt::UserRole, qVariantFromValue(serverEntry));
                    childItem->setText(0, serverEntry->name);
                    childItem->setText(1, serverEntry->host);
                    childItem->setText(2, QString::number(serverEntry->port));
                    childItem->setFlags(childItem->flags() | Qt::ItemIsUserCheckable);
                    childItem->setCheckState(3, serverEntry->autoConnect ? Qt::Checked : Qt::Unchecked);
                }
            }
        }
    }

    ui->treeWidget->expandAll();

    for (int i = 0; i < ui->treeWidget->columnCount(); i++) {
        ui->treeWidget->resizeColumnToContents(i);
    }
}

void ServerListDialog::deleteTreeData()
{
    serverEntries.clear();
    ui->treeWidget->clear();
}

void ServerListDialog::addItem()
{
    ServerEditDialog *sed = new ServerEditDialog(this);

    if (sed->exec() == QDialog::Accepted) {
        ServerEntry *entry = new ServerEntry(
            sed->getGame(),
            sed->getName(),
            sed->getHost(),
            sed->getPort(),
            sed->getPassword().replace(" ", ""),
            sed->getAutoConnect()
        );

        serverManager->addServer(entry);

        createTreeData();
    }

    delete sed;
}

void ServerListDialog::editItem()
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1) {
        QTreeWidgetItem *item = items.at(0);
        QVariant variant = item->data(0, Qt::UserRole);
        ServerEntry *entry = variant.value<ServerEntry *>();

        ServerEditDialog *sed = new ServerEditDialog(entry->game, entry->name, entry->host, entry->port, entry->password, this);

        if (sed->exec() == QDialog::Accepted) {
            ServerEntry editEntry = ServerEntry(
                sed->getGame(),
                sed->getName(),
                sed->getHost(),
                sed->getPort(),
                sed->getPassword().replace(" ", ""),
                sed->getAutoConnect()
            );

            // Set the server to the new values obtained by ServerEditDialog.
            *entry = editEntry;
            serverManager->setServers(serverEntries);

            createTreeData();
        }

        delete sed;
    }
}

void ServerListDialog::removeItem()
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1) {
        int answer = QMessageBox::question(this, tr("Remove"), tr("Are you sure you want to remove this server?"), QMessageBox::Yes, QMessageBox::No);

        if (answer == QMessageBox::Yes) {
            QTreeWidgetItem *item = items.at(0);
            QVariant variant = item->data(0, Qt::UserRole);
            ServerEntry *entry = variant.value<ServerEntry *>();

            serverManager->removeServer(entry);

            createTreeData();
        }
    }
}

void ServerListDialog::accept()
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1 && ui->treeWidget->currentItem()->parent()) {
        QTreeWidgetItem *item = items.at(0);
        QVariant variant = item->data(0, Qt::UserRole);
        ServerEntry *entry = variant.value<ServerEntry *>();

        OpenRcon *openRcon = OpenRcon::getInstance();
        openRcon->addTab(entry);

        QDialog::accept();
    }
}
