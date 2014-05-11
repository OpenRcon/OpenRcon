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

#include "OpenRcon.h"

OpenRcon::OpenRcon(QWidget *parent) : QMainWindow(parent), ui(new Ui::OpenRcon)
{
    ui->setupUi(this);

    // Initialize the QSettings object.
    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Create GameManager and ServerManager instances.
    gameManager = new GameManager(this);
    serverManager = new ServerManager(this);

    // Create dialogs.
    serverListDialog = new ServerListDialog(this);
    optionsDialog = new OptionsDialog(this);
    aboutDialog = new AboutDialog(this);

    // Sets application title
    setWindowTitle(QString("%1 %2").arg(APP_NAME).arg(APP_VERSION));

    // Create and read settings
    readSettings();

    // Actions
    ui->actionAbout->setIcon(QIcon(APP_ICON));
    ui->actionAbout->setText(tr("About &%1").arg(APP_NAME));
    ui->actionAbout_Qt->setIcon(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));

    // ServerManager
    comboBox_sm_server = new QComboBox(ui->toolBar_sm);
    pushButton_sm_connect = new QPushButton(tr("Connect"), ui->toolBar_sm);

    ui->toolBar_sm->addWidget(comboBox_sm_server);
    ui->toolBar_sm->addWidget(pushButton_sm_connect);

    updateServerList();

    // Autoconnect which has the autoconnect option set to true.
    QList<ServerEntry *> serverList = serverManager->getServers();

    for (ServerEntry *entry : serverList) {
        if (entry->autoConnect) {
            addTab(entry);
        }
    }

    // Actions
    connect(ui->actionServermanager, SIGNAL(triggered()), this, SLOT(actionServermanager_triggered()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionServers, SIGNAL(triggered()), this, SLOT(actionServers_triggered()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(actionOptions_triggered()));
    connect(ui->actionDocumentation, SIGNAL(triggered()), this, SLOT(actionDocumentation_triggered()));
    connect(ui->actionVisit_website, SIGNAL(triggered()), this, SLOT(actionVisit_website_triggered()));
    connect(ui->actionReport_bug, SIGNAL(triggered()), this, SLOT(actionReport_bug_triggered()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(actionAbout_triggered()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(actionAbout_Qt_triggered()));

    // Toolbars
    connect(pushButton_sm_connect, SIGNAL(clicked()), this, SLOT(pushButton_sm_connect_clicked()));
    connect(serverManager, SIGNAL(onServerUpdate()), this, SLOT(updateServerList()));

    // TabWidget
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

OpenRcon::~OpenRcon()
{
    writeSettings();

    delete ui;
    delete settings;
    delete gameManager;
    delete serverManager;
    delete serverListDialog;
    delete optionsDialog;
    delete aboutDialog;
}

void OpenRcon::readSettings()
{
    settings->beginGroup(APP_NAME);
        resize(settings->value("Size", size()).toSize());
        move(settings->value("Position", pos()).toPoint());

        if (settings->value("IsMaximized", true).toBool()) {
            showMaximized();
        }

        if (settings->value("actionConnection", true).toBool()) {
            ui->toolBar_sm->show();
            ui->actionServers->setChecked(true);
        } else {
            ui->toolBar_sm->hide();
            ui->actionServers->setChecked(false);
        }
    settings->endGroup();
}

void OpenRcon::writeSettings()
{
    settings->beginGroup(APP_NAME);
        settings->setValue("IsMaximized", isMaximized());
        settings->setValue("Size", size());
        settings->setValue("Position", pos());
    settings->endGroup();
}

void OpenRcon::addTab(ServerEntry *serverEntry)
{
    GameEntry gameEntry = gameManager->getGame(serverEntry->game);
    Game *gameObject = gameManager->getGameObject(serverEntry);
    int index = ui->tabWidget->addTab(gameObject, gameEntry.icon, serverEntry->name);

    ui->tabWidget->setTabToolTip(index, QString("%1:%2").arg(serverEntry->host).arg(serverEntry->port));
    ui->tabWidget->setCurrentIndex(index);
}

GameManager *OpenRcon::getGameManager()
{
    return gameManager;
}

ServerManager *OpenRcon::getServerManager()
{
    return serverManager;
}

void OpenRcon::closeTab(int index)
{
    QWidget *widget = ui->tabWidget->widget(index);
    ConnectionTabWidget *tabWidget = dynamic_cast<ConnectionTabWidget *>(widget);
    tabWidget->getConnection()->hostDisconnect();

    ui->tabWidget->removeTab(index);
}

void OpenRcon::updateServerList()
{
    qDebug() << "ServerList updated!";

    comboBox_sm_server->clear();

    // Add the server to the comboBox only if it's not empty, otherwhise disable it.
    QList<ServerEntry *> serverList = serverManager->getServers();

    if (!serverList.isEmpty()) {
        comboBox_sm_server->setEnabled(true);
        pushButton_sm_connect->setEnabled(true);

        for (ServerEntry *server : serverList) {
            GameEntry game = gameManager->getGame(server->game);

            comboBox_sm_server->addItem(game.icon, server->name);
        }
    } else {
        comboBox_sm_server->setEnabled(false);
        pushButton_sm_connect->setEnabled(false);

        comboBox_sm_server->addItem(tr("No servers added yet."));
    }
}

// Application menu
void OpenRcon::actionServermanager_triggered()
{
    serverListDialog->exec();
}

// View menu
void OpenRcon::actionServers_triggered()
{
    settings->beginGroup("OpenRcon");
        if (ui->actionServers->isChecked()) {
            ui->toolBar_sm->show();
            settings->setValue("actionConnection", true);
            ui->actionServers->setChecked(true);
        } else {
            ui->toolBar_sm->hide();
            settings->setValue("actionConnection", false);
            ui->actionServers->setChecked(false);
        }
    settings->endGroup();
}

// Tools menu
void OpenRcon::actionOptions_triggered()
{
    optionsDialog->exec();
}

// Help menu
void OpenRcon::actionReport_bug_triggered()
{
    QDesktopServices::openUrl(QUrl(APP_BUG));
}

void OpenRcon::actionVisit_website_triggered()
{
    QDesktopServices::openUrl(QUrl(APP_URL));
}

void OpenRcon::actionDocumentation_triggered()
{
    QDesktopServices::openUrl(QUrl(APP_DOC));
}

void OpenRcon::actionAbout_triggered()
{
    aboutDialog->exec();
}

void OpenRcon::actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

// ServerManager toolbar
void OpenRcon::pushButton_sm_connect_clicked()
{
    ServerEntry *serverEntry = serverManager->getServer(comboBox_sm_server->currentIndex());

    addTab(serverEntry);
}
