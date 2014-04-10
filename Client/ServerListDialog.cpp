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
    Q_UNUSED(parent);

    ui->setupUi(this);

    gameManager = new GameManager(this);
    serverManager = new ServerManager(this);

    // Sets application title and icon
    setWindowTitle(QString(tr("Servermanager")));
    setWindowIcon(QIcon(APP_ICON));

    // Add a menu for the ServerItems
    menu_sld_serverEntry = new QMenu(ui->treeWidget);
    menu_sld_serverEntry->addAction(ui->actionEdit);
    menu_sld_serverEntry->addAction(ui->actionRemove);

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->pushButton_sld_connect->setEnabled(false);

    createTreeData();

    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_customContextMenuRequested(QPoint)));
    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(treeWidget_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(accept()));

    connect(ui->actionEdit, SIGNAL(triggered()), this, SLOT(editItem()));
    connect(ui->actionRemove, SIGNAL(triggered()), this, SLOT(removeItem()));

    connect(ui->pushButton_sld_add, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->pushButton_sld_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->pushButton_sld_connect, SIGNAL(clicked()), this, SLOT(accept()));
}

ServerListDialog::~ServerListDialog()
{
    deleteTreeData();

    delete ui;
}

void ServerListDialog::treeWidget_customContextMenuRequested(QPoint pos)
{
    if (ui->treeWidget->itemAt(pos) && ui->treeWidget->currentItem()->parent()) {
        menu_sld_serverEntry->exec(QCursor::pos());
    }
}

void ServerListDialog::treeWidget_currentItemChanged(QTreeWidgetItem *item, QTreeWidgetItem*)
{
    ui->pushButton_sld_connect->setEnabled(item && item->parent());
}

void ServerListDialog::createTreeData()
{
    QList<QTreeWidgetItem *> topLevelItems;

    foreach (GameEntry gameEntry, gameManager->getGames()) {
        QTreeWidgetItem *parentItem = new QTreeWidgetItem(ui->treeWidget);
        parentItem->setIcon(0, gameEntry.icon);
        parentItem->setText(0, gameEntry.name);

        foreach (ServerEntry serverEntry, serverManager->getServers(gameEntry.id)) {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, serverEntry.name);
            childItem->setText(1, serverEntry.host);
            childItem->setText(2, QString::number(serverEntry.port));
//            childItem->setData(3, Qt::UserRole, qVariantFromValue(serverEntry));

            parentItem->addChild(childItem);
        }

        topLevelItems.append(parentItem);
    }

    ui->treeWidget->addTopLevelItems(topLevelItems);
    ui->treeWidget->expandAll();

    for (int i = 0; i < ui->treeWidget->columnCount(); i++) {
        ui->treeWidget->resizeColumnToContents(i);
    }
}

void ServerListDialog::deleteTreeData()
{
    ui->treeWidget->clear();
}

void ServerListDialog::addItem()
{
    ServerEditDialog *sed = new ServerEditDialog(this);

    if (sed->exec() == QDialog::Accepted) {
        ServerEntry entry = ServerEntry(
            sed->getGame(),
            sed->getName(),
            sed->getHost(),
            sed->getPort(),
            sed->getPassword()
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
        QVariant v = item->data(3, Qt::UserRole);
        ServerEntry e = v.value<ServerEntry>();

        ServerEditDialog *sed = new ServerEditDialog(e.game, e.name, e.host, e.port, e.password, this);

        if (sed->exec() == QDialog::Accepted) {
            ServerEntry entry = ServerEntry(
                sed->getGame(),
                sed->getName(),
                sed->getHost(),
                sed->getPort(),
                sed->getPassword()
            );

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
            QVariant v = item->data(3, Qt::UserRole);
            ServerEntry e = v.value<ServerEntry>();

            // Could use indexOf instead, we're assuming no duplicates.
            //m_ServerEntries.removeAll(*e); TODO: Fix this.

            createTreeData();
        }
    }
}

void ServerListDialog::accept()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1 && ui->treeWidget->currentItem()->parent()) {
        QTreeWidgetItem* item = items[0];
        QVariant variant = item->data(3, Qt::UserRole);
        ServerEntry entry = variant.value<ServerEntry>();

        OpenRcon *openRcon = OpenRcon::getInstance();
        openRcon->newTab(entry.game, entry.name, entry.host, entry.port, entry.password);

        QDialog::accept();
    }
}

void ServerListDialog::reject()
{
    QDialog::reject();
}
