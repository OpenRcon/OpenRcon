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

#include "ui_OpenRcon.h"
#include "OpenRcon.h"

#include "GameEntry.h"
#include "GameManager.h"
#include "ServerEntry.h"
#include "ServerManager.h"
#include "ServerListDialog.h"
#include "OptionsDialog.h"
#include "AboutDialog.h"

#include "Game.h"

OpenRcon::OpenRcon(QWidget *parent) : QMainWindow(parent), ui(new Ui::OpenRcon)
{
    ui->setupUi(this);

    // Initialize the QSettings object.
    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Create ServerManager instances.
    serverManager = new ServerManager(this);

    // Create dialogs.
    serverListDialog = new ServerListDialog(this);
    optionsDialog = new OptionsDialog(this);
    aboutDialog = new AboutDialog(this);

    // Sets window title
    setWindowTitle(QString("%1 %2").arg(APP_NAME).arg(APP_VERSION));

    // Actions
    actionServerManager = new QAction(QIcon(":/icons/server-manager.png"), tr("&Server Manager"), this);
    actionServerManager->setShortcut(tr("Ctrl+S"));
    actionServerManager->setToolTip(tr("Opens the ServerManager."));
    actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setShortcut(tr("Ctrl+Q"));
    actionQuickConnect = new QAction(tr("Quickconnect"), this);
    actionQuickConnect->setCheckable(true);
    actionOptions = new QAction(QIcon(":/icons/options.png"), tr("&Options"), this);
    actionOptions->setShortcut(tr("Ctrl+O"));
    actionDocumentation = new QAction(tr("Documentation"), this);
    actionVisitWebsite = new QAction(QIcon(":/icons/internet.png"), tr("Visit website"), this);
    actionReportBug = new QAction(QIcon(":/icons/report-bug.png"), tr("Report bug"), this);
    actionAbout = new QAction(QIcon(APP_ICON), tr("&About %1").arg(APP_NAME), this);
    actionAbout->setShortcut(tr("Ctrl+A"));
    actionAboutQt = new QAction(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"), tr("About Qt"), this);
    actionAboutQt->setMenuRole(QAction::AboutQtRole);

    ui->menuApplication->addAction(actionServerManager);
    ui->menuApplication->addAction(actionQuit);
    ui->menuToolbars->addAction(actionQuickConnect);
    ui->menuTools->addAction(actionOptions);
    ui->menuHelp->addAction(actionDocumentation);
    ui->menuHelp->addAction(actionVisitWebsite);
    ui->menuHelp->addAction(actionReportBug);
    ui->menuHelp->addSeparator();
    ui->menuHelp->addAction(actionAbout);
    ui->menuHelp->addAction(actionAboutQt);

    // Create and read settings
    readSettings();

    // QuickConnect toolbar.
    comboBox_quickConnect_server = new QComboBox(ui->toolBar_quickConnect);
    comboBox_quickConnect_server->setToolTip(tr("Let's you select a prevously stored server."));
    pushButton_quickConnect_connect = new QPushButton(tr("Connect"), ui->toolBar_quickConnect);
    pushButton_quickConnect_connect->setToolTip(tr("Connect's to the server selected in the combobox."));

    ui->toolBar_quickConnect->addAction(actionServerManager);
    ui->toolBar_quickConnect->addWidget(comboBox_quickConnect_server);
    ui->toolBar_quickConnect->addWidget(pushButton_quickConnect_connect);

    // Loads the server list from ServerManager.
    updateServerList();

    // Autoconnect which has the autoconnect option set to true.
    QList<ServerEntry *> serverList = serverManager->getServers();

    for (ServerEntry *entry : serverList) {
        if (entry->autoConnect) {
            addTab(entry);
        }
    }

    // Actions
    connect(actionServerManager, SIGNAL(triggered()), this, SLOT(actionServerManager_triggered()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(actionQuickConnect, SIGNAL(triggered()), this, SLOT(actionQuickConnect_triggered()));
    connect(actionOptions, SIGNAL(triggered()), this, SLOT(actionOptions_triggered()));
    connect(actionDocumentation, SIGNAL(triggered()), this, SLOT(actionDocumentation_triggered()));
    connect(actionVisitWebsite, SIGNAL(triggered()), this, SLOT(actionVisitWebsite_triggered()));
    connect(actionReportBug, SIGNAL(triggered()), this, SLOT(actionReportBug_triggered()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(actionAbout_triggered()));
    connect(actionAboutQt, SIGNAL(triggered()), this, SLOT(actionAboutQt_triggered()));

    // Toolbars
    connect(pushButton_quickConnect_connect, SIGNAL(clicked()), this, SLOT(pushButton_quickConnect_connect_clicked()));
    connect(serverManager, SIGNAL(onServerUpdate()), this, SLOT(updateServerList()));

    // TabWidget
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

OpenRcon::~OpenRcon()
{
    writeSettings();

    delete ui;
    delete settings;
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

        if (settings->value("toolbarQuickConnect", true).toBool()) {
            ui->toolBar_quickConnect->show();
            actionQuickConnect->setChecked(true);
        } else {
            ui->toolBar_quickConnect->hide();
            actionQuickConnect->setChecked(false);
        }
    settings->endGroup();
}

void OpenRcon::writeSettings()
{
    settings->beginGroup(APP_NAME);
        settings->setValue("Size", size());
        settings->setValue("IsMaximized", isMaximized());
        settings->setValue("Position", pos());
    settings->endGroup();
}

void OpenRcon::addTab(ServerEntry *serverEntry)
{
    GameEntry gameEntry = GameManager::getGame(serverEntry->game);
    Game *gameObject = GameManager::getGameObject(serverEntry);
    int index = ui->tabWidget->addTab(gameObject, QIcon(gameEntry.icon), serverEntry->name);

    ui->tabWidget->setTabToolTip(index, QString("%1:%2").arg(serverEntry->host).arg(serverEntry->port));
    ui->tabWidget->setCurrentIndex(index);
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
    comboBox_quickConnect_server->clear();

    // Add the server to the comboBox only if it's not empty, otherwise disable it.
    QList<ServerEntry *> serverList = serverManager->getServers();

    if (!serverList.isEmpty()) {
        comboBox_quickConnect_server->setEnabled(true);
        pushButton_quickConnect_connect->setEnabled(true);

        for (ServerEntry *server : serverList) {
            GameEntry game = GameManager::getGame(server->game);

            comboBox_quickConnect_server->addItem(QIcon(game.icon), server->name);
        }
    } else {
        comboBox_quickConnect_server->setEnabled(false);
        pushButton_quickConnect_connect->setEnabled(false);

        comboBox_quickConnect_server->addItem(tr("No servers added yet."));
    }
}

// Application menu
void OpenRcon::actionServerManager_triggered()
{
    serverListDialog->exec();
}

// View menu
void OpenRcon::actionQuickConnect_triggered()
{
    settings->beginGroup(APP_NAME);
        if (actionQuickConnect->isChecked()) {
            ui->toolBar_quickConnect->show();
            settings->setValue("toolbarQuickConnect", true);
            actionQuickConnect->setChecked(true);
        } else {
            ui->toolBar_quickConnect->hide();
            settings->setValue("toolbarQuickConnect", false);
            actionQuickConnect->setChecked(false);
        }
    settings->endGroup();
}

// Tools menu
void OpenRcon::actionOptions_triggered()
{
    optionsDialog->exec();
}

// Help menu
void OpenRcon::actionDocumentation_triggered()
{
    QDesktopServices::openUrl(QUrl(APP_DOC));
}

void OpenRcon::actionVisitWebsite_triggered()
{
    QDesktopServices::openUrl(QUrl(APP_URL));
}

void OpenRcon::actionReportBug_triggered()
{
    QDesktopServices::openUrl(QUrl(APP_BUG));
}

void OpenRcon::actionAbout_triggered()
{
    aboutDialog->exec();
}

void OpenRcon::actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

// QuickConnect toolbar
void OpenRcon::pushButton_quickConnect_connect_clicked()
{
    ServerEntry *serverEntry = serverManager->getServer(comboBox_quickConnect_server->currentIndex());

    addTab(serverEntry);
}
