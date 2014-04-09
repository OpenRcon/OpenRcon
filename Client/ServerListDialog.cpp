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

ServerListDialog::ServerListDialog(QObject *parent) : ui(new Ui::ServerListDialog), m_RootItems(0)
{
    Q_UNUSED(parent);

    ui->setupUi(this);

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

    foreach (GameEntry entry, gameManager->getGames()) {
        m_IconMap.insert(entry.id, entry.icon);
    }

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

/* Some pointer fun below. The trick is that all the pointers in m_Data and m_RootItems point back to m_ServerEntries.
   The actual element is passed in the QTreeWidgetItem itself, in row 5 as a QVariant. */

void ServerListDialog::createTreeData()
{
    deleteTreeData();

    //loadServerEntries(m_ServerEntries);

    m_ServerEntries = serverManager->getServers();

    QSet<int> uniqueGames;
    for (QList<ServerEntry>::const_iterator it = m_ServerEntries.constBegin(); it != m_ServerEntries.constEnd(); it++) {
        uniqueGames.insert(it->game);
    }

    for (QSet<int>::const_iterator games_it = uniqueGames.constBegin(); games_it != uniqueGames.constEnd(); games_it++) {
        QList<ServerEntry*> *sen = new QList<ServerEntry*>();

        for (QList<ServerEntry>::iterator entries_it = m_ServerEntries.begin(); entries_it != m_ServerEntries.end(); entries_it++) {
            if (*games_it == entries_it->game) {
                sen->append(&(*entries_it));
            }
        }

        m_Data.insert(*games_it, sen);
    }

    m_RootItems = new QList<QTreeWidgetItem*>();

    QList<int> keys = m_Data.keys();

    for (QList<int>::const_iterator key_it = keys.constBegin(); key_it != keys.constEnd(); key_it++) {
        QTreeWidgetItem* parent = new QTreeWidgetItem(ui->treeWidget);
        parent->setText(0, gameManager->getGame(*key_it).name);

        if (m_IconMap.contains(*key_it)) {
            QIcon icon = m_IconMap.value(*key_it);
            parent->setIcon(0, icon);
        }

        ui->treeWidget->addTopLevelItem(parent);

        QList<ServerEntry*> *entries = m_Data[*key_it];
        for (QList<ServerEntry*>::iterator entries_it = entries->begin(); entries_it != entries->end(); entries_it++) {

            ServerEntry* sep = *entries_it;

            QTreeWidgetItem* child = new QTreeWidgetItem(parent);
            child->setText(0, sep->name);
            child->setText(1, sep->host);
            child->setText(2, QString::number(sep->port));
            child->setData(3, Qt::UserRole, qVariantFromValue(sep));

            parent->addChild(child);
        }

        m_RootItems->append(parent);
    }

    ui->treeWidget->expandAll();
    for (int n = 0; n < ui->treeWidget->columnCount(); n++) {
        ui->treeWidget->resizeColumnToContents(n);
    }
}

void ServerListDialog::deleteTreeData()
{
    if (m_RootItems) {
        for (QList<QTreeWidgetItem*>::iterator it = m_RootItems->begin(); it != m_RootItems->end(); it++) {
            for (int k = 0; k < (*it)->childCount(); k++) {
                delete (*it)->child(k);
            }
            delete *it;
        }

        delete m_RootItems;
        m_RootItems = 0;
    }

    QList<int> keys = m_Data.keys();
    for (QList<int>::const_iterator key_it = keys.constBegin(); key_it != keys.constEnd(); key_it++) {
        delete m_Data[*key_it];
    }
    m_Data.clear();
    //m_ServerEntries.clear();
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

        //m_ServerEntries.append(entry);
        serverManager->addServer(entry);

        //saveServerEntries(m_ServerEntries);

        createTreeData();

        //MainWindow *mw = MainWindow::getInstance();
        //mw->PopulateServerItems();
    }

    delete sed;
}

void ServerListDialog::editItem()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1) {
        QTreeWidgetItem* item = items[0];
        QVariant v = item->data(3, Qt::UserRole);
        ServerEntry* e = v.value<ServerEntry*>();

        ServerEditDialog *sed = new ServerEditDialog(e->game, e->name, e->host, e->port, e->password, this);

        if (sed->exec() == QDialog::Accepted) {
            ServerEntry entry = ServerEntry(
                sed->getGame(),
                sed->getName(),
                sed->getHost(),
                sed->getPort(),
                sed->getPassword()
            );

            *e = entry;

            //saveServerEntries(m_ServerEntries);

            createTreeData();

            //MainWindow *mw = MainWindow::getInstance();
            //mw->PopulateServerItems();
        }

        delete sed;
    }
}

void ServerListDialog::removeItem()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1) {
        const int answer = QMessageBox::question(this, tr("Remove"), tr("Are you sure you want to remove this server?"), QMessageBox::Yes, QMessageBox::No);
        if (answer != QMessageBox::Yes) {
            return;
        }

        QTreeWidgetItem* item = items[0];
        QVariant v = item->data(3, Qt::UserRole);
        ServerEntry* e = v.value<ServerEntry*>();

        // Could use indexOf instead, we're assuming no duplicates.
        m_ServerEntries.removeAll(*e);

        //saveServerEntries(m_ServerEntries);

        createTreeData();

        //MainWindow *mw = MainWindow::getInstance();
        //mw->PopulateServerItems();
    }
}

void ServerListDialog::accept()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
    Q_ASSERT(items.count() <= 1);

    if (items.count() == 1 && ui->treeWidget->currentItem()->parent()) {
        QTreeWidgetItem* item = items[0];
        QVariant variant = item->data(3, Qt::UserRole);
        ServerEntry* entry = variant.value<ServerEntry*>();

        OpenRcon *openRcon = OpenRcon::getInstance();
        openRcon->newTab(entry->game, entry->name, entry->host, entry->port, entry->password);

        QDialog::accept();
    }
}

void ServerListDialog::reject()
{
    QDialog::reject();
}
