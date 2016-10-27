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

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QTreeWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QPoint>
#include <QTreeWidgetItem>
#include <QCursor>
#include <QVariant>
#include <QList>
#include <QString>
#include <QMessageBox>
#include <QIcon>

#include "ui_ServerListDialog.h"
#include "ServerListDialog.h"
#include "OpenRcon.h"
#include "ServerManager.h"
#include "SessionManager.h"
#include "ServerEntry.h"
#include "GameManager.h"
#include "GameEntry.h"

#include "ServerEditDialog.h"

ServerListDialog::ServerListDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ServerListDialog)
{
    ui->setupUi(this);

    serverManager = ServerManager::getInstance();
    sessionManager = SessionManager::getInstance();

    // Fetch ServerEntries from ServerManager.
    serverEntries = serverManager->getServers();

    // Menu showing when right-clicking an topLevelItem.
    menu_gameEntry = new QMenu(ui->treeWidget);
    action_gameEntry_add = new QAction(tr("Add"), menu_gameEntry);

    menu_gameEntry->addAction(action_gameEntry_add);

    // Menu showing when right-clicking an item.
    menu_serverEntry = new QMenu(ui->treeWidget);
    action_serverEntry_edit = new QAction(tr("Edit"), menu_serverEntry);
    action_serverEntry_remove = new QAction(tr("Remove"), menu_serverEntry);

    menu_serverEntry->addAction(action_serverEntry_edit);
    menu_serverEntry->addAction(action_serverEntry_remove);

    // Disable connect button, will be enabled when a valid ServerEntry is selected.
    ui->pushButton_sld_connect->setEnabled(false);

    // Load GameEnrties and ServerEntries from ServerManager and add them to the QTreeWidget.
    createTreeData();

    connect(sessionManager,             &SessionManager::onSessionOpened,           this, &ServerListDialog::onSessionOpened);
    connect(sessionManager,             &SessionManager::onSessionClosed,           this, &ServerListDialog::onSessionClosed);

    connect(ui->treeWidget,             &QTreeWidget::customContextMenuRequested,   this, &ServerListDialog::treeWidget_customContextMenuRequested);
    connect(ui->treeWidget,             &QTreeWidget::currentItemChanged,           this, &ServerListDialog::treeWidget_currentItemChanged);
    connect(ui->treeWidget,             &QTreeWidget::itemClicked,                  this, &ServerListDialog::treeWidget_itemClicked);
    connect(ui->treeWidget,             &QTreeWidget::itemDoubleClicked,            this, &ServerListDialog::connectToItem);

    connect(action_gameEntry_add,       &QAction::triggered,                        this, &ServerListDialog::action_gameEntry_add_triggered);
    connect(action_serverEntry_edit,    &QAction::triggered,                        this, &ServerListDialog::editItem);
    connect(action_serverEntry_remove,  &QAction::triggered,                        this, &ServerListDialog::removeItem);

    connect(ui->pushButton_sld_add,     &QPushButton::clicked,                      this, &ServerListDialog::addItem);
    connect(ui->pushButton_sld_connect, &QPushButton::clicked,                      this, &ServerListDialog::connectToItem);
    connect(ui->buttonBox,              &QDialogButtonBox::accepted,                this, &ServerListDialog::accept);
    connect(ui->buttonBox,              &QDialogButtonBox::rejected,                this, &ServerListDialog::reject);
}

ServerListDialog::~ServerListDialog()
{
    ui->treeWidget->clear();
    serverEntries.clear();

    delete ui;
}

void ServerListDialog::onSessionOpened()
{
    createTreeData();

    ui->pushButton_sld_connect->setEnabled(false);
}

void ServerListDialog::onSessionClosed()
{
    createTreeData();

    ui->pushButton_sld_connect->setEnabled(true);
}

void ServerListDialog::treeWidget_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget->itemAt(pos)) {
        QTreeWidgetItem *item = ui->treeWidget->currentItem();

        if (!item->parent()) {
            menu_gameEntry->exec(QCursor::pos());
        } else {
            menu_serverEntry->exec(QCursor::pos());
        }
    }
}

void ServerListDialog::treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);

    if (current) {
        QVariant variant = current->data(0, Qt::UserRole);
        ServerEntry *serverEntry = variant.value<ServerEntry*>();

        ui->pushButton_sld_connect->setEnabled(current->parent() && !sessionManager->isSessionConnected(serverEntry));
    }
}

void ServerListDialog::treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    // If item that changed is the checkBox area.
    if (item->parent() && column == 3) {
        QVariant variant = item->data(0, Qt::UserRole);
        ServerEntry *entry = variant.value<ServerEntry*>();

        // Sets the checked state of autoconnect.
        entry->setAutoConnect(item->checkState(column) == Qt::Checked ? true : false);
    }
}

void ServerListDialog::action_gameEntry_add_triggered()
{
    if (ui->treeWidget->selectedItems().count() > 0) {
        QTreeWidgetItem *item = ui->treeWidget->currentItem();

        if (!item->parent()) {
            addItem(GameManager::toInt(item->data(0, Qt::UserRole).value<GameType>()));
        }
    }
}

void ServerListDialog::createTreeData()
{
    ui->treeWidget->clear();

    for (GameEntry gameEntry : GameManager::getGames()) {
        QList<ServerEntry*> list;

        for (ServerEntry *serverEntry : serverEntries) {
            if (serverEntry->getGameType() == gameEntry.getGameType()) {
                list.append(serverEntry);
            }
        }

        if (!list.isEmpty()) {
            QTreeWidgetItem *parentItem = new QTreeWidgetItem(ui->treeWidget);
            parentItem->setData(0, Qt::UserRole, QVariant::fromValue(gameEntry.getGameType()));
            parentItem->setIcon(0, QIcon(gameEntry.getIcon()));
            parentItem->setText(0, gameEntry.getName());

            QFont font;
            font.setBold(true);
            parentItem->setFont(0, font);

            for (ServerEntry *serverEntry : list) {
                QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
                childItem->setData(0, Qt::UserRole, QVariant::fromValue(serverEntry));
                childItem->setText(0, serverEntry->getName());
                childItem->setText(1, serverEntry->getHost());
                childItem->setText(2, QString::number(serverEntry->getPort()));
                childItem->setFlags(childItem->flags() | Qt::ItemIsUserCheckable);
                childItem->setCheckState(3, serverEntry->getAutoConnect() ? Qt::Checked : Qt::Unchecked);
                childItem->setDisabled(sessionManager->isSessionConnected(serverEntry));
            }
        }
    }

    ui->treeWidget->expandAll();

    for (int i = 0; i < ui->treeWidget->columnCount(); i++) {
        ui->treeWidget->resizeColumnToContents(i);
    }
}

void ServerListDialog::addItem(int index)
{    
    ServerEditDialog *dialog = index < 0 ?  new ServerEditDialog(this) :  new ServerEditDialog(index, this);

    if (dialog->exec() == QDialog::Accepted) {
        ServerEntry *entry = new ServerEntry(
            dialog->getGameType(),
            dialog->getName(),
            dialog->getHost(),
            dialog->getPort(),
            dialog->getPassword().replace(" ", ""),
            dialog->getAutoConnect()
        );

        serverEntries.append(entry);
        createTreeData();
    }

    delete dialog;
}

void ServerListDialog::editItem()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1) {
        QTreeWidgetItem *item = items.at(0);

        if (!item->isDisabled()) {
            QVariant variant = item->data(0, Qt::UserRole);
            ServerEntry *entry = variant.value<ServerEntry*>();

            ServerEditDialog *sed = new ServerEditDialog(GameManager::toInt(entry->getGameType()),
                                                         entry->getName(),
                                                         entry->getHost(),
                                                         entry->getPort(),
                                                         entry->getPassword(),
                                                         entry->getAutoConnect(),
                                                         this);

            if (sed->exec() == QDialog::Accepted) {
                ServerEntry editEntry = ServerEntry(
                    sed->getGameType(),
                    sed->getName(),
                    sed->getHost(),
                    sed->getPort(),
                    sed->getPassword().replace(" ", ""),
                    sed->getAutoConnect()
                );

                // Set the server to the new values obtained by ServerEditDialog.
                *entry = editEntry;
                createTreeData();
            }

            delete sed;
        }
    }
}

void ServerListDialog::removeItem()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1) {
        int answer = QMessageBox::question(this, tr("Remove"), tr("Are you sure you want to remove this server?"), QMessageBox::Yes, QMessageBox::No);

        if (answer == QMessageBox::Yes) {
            QTreeWidgetItem *item = items.at(0);
            QVariant variant = item->data(0, Qt::UserRole);
            ServerEntry *entry = variant.value<ServerEntry*>();

            serverEntries.removeAt(serverEntries.indexOf(entry));
            createTreeData();
        }
    }
}

void ServerListDialog::connectToItem()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1 && ui->treeWidget->currentItem()->parent()) {
        QTreeWidgetItem *item = items.at(0);
        QVariant variant = item->data(0, Qt::UserRole);
        ServerEntry *entry = variant.value<ServerEntry*>();

        if (!sessionManager->isSessionConnected(entry)) {
            // Connect to the ServerEntry and add the tab to OpenRcon's QTabWidget.
            ui->pushButton_sld_connect->setEnabled(false);
            sessionManager->openSession(entry);
            accept();
        }
    }
}

void ServerListDialog::accept()
{
    serverManager->setServers(serverEntries);

    QDialog::accept();
}
