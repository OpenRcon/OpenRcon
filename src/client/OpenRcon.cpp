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

#include <QSettings>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QComboBox>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

#include "OpenRcon.h"
#include "ServerManager.h"
#include "SessionManager.h"
#include "ServerEntry.h"
#include "GameEntry.h"
#include "GameManager.h"
#include "TabWidget.h"

#include "ServerListDialog.h"
#include "OptionsDialog.h"
#include "AboutDialog.h"
#include "GameWidget.h"

#include "Client.h"
#include "Connection.h"

OpenRcon::OpenRcon(QWidget *parent) : QMainWindow(parent)
{
    // Initialize the QSettings object.
    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Create ServerManager instances.
    serverManager = ServerManager::getInstance(this);
    sessionManager = SessionManager::getInstance(this);

    // Create dialogs.
    serverListDialog = new ServerListDialog(this);
    optionsDialog = new OptionsDialog(this);
    aboutDialog = new AboutDialog(this);

    // Sets window title
    setWindowTitle(QString("%1 %2").arg(APP_NAME).arg(APP_VERSION));
    setWindowIcon(QIcon(":/icons/openrcon.png"));

    // Actions
    actionServerManager = new QAction(QIcon(":/icons/servermanager.png"), tr("&Servers"), this);
    actionServerManager->setShortcut(tr("Ctrl+S"));
    actionServerManager->setToolTip(tr("View and edit servers."));
    actionQuit = new QAction(QIcon(":/icons/quit.png"), tr("&Quit"), this);
    actionQuit->setShortcut(tr("Ctrl+Q"));
    actionQuickConnect = new QAction(tr("Quickconnect"), this);
    actionQuickConnect->setCheckable(true);
    actionStatusBar = new QAction(tr("Statusbar"), this);
    actionStatusBar->setCheckable(true);
    actionOptions = new QAction(QIcon(":/icons/options.png"), tr("&Options"), this);
    actionOptions->setShortcut(tr("Ctrl+O"));
    actionDocumentation = new QAction(QIcon(":/icons/documentation.png"), tr("Documentation"), this);
    actionVisitWebsite = new QAction(QIcon(":/icons/internet.png"), tr("Visit website"), this);
    actionReportBug = new QAction(QIcon(":/icons/report-bug.png"), tr("Report bug"), this);
    actionAbout = new QAction(QIcon(APP_ICON), tr("&About %1").arg(APP_NAME), this);
    actionAbout->setShortcut(tr("Ctrl+A"));
    actionAboutQt = new QAction(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"), tr("About Qt"), this);
    actionAboutQt->setMenuRole(QAction::AboutQtRole);

    actionTabReconnect = new QAction(tr("Reconnect"), this);
    actionTabDisconnect = new QAction(tr("Disconnect"), this);

    // Menubar
    menuBar = new QMenuBar(this);

    menuApplication = menuBar->addMenu(tr("Application"));
    menuApplication->addAction(actionServerManager);
    menuApplication->addSeparator();
    menuApplication->addAction(actionQuit);

    menuView = menuBar->addMenu(tr("View"));
    menuToolbars = menuView->addMenu(tr("Toolbars"));
    menuToolbars->addAction(actionQuickConnect);
    menuToolbars->addAction(actionStatusBar);

    menuTools = menuBar->addMenu(tr("Tools"));
    menuTools->addAction(actionOptions);

    menuHelp = menuBar->addMenu(tr("Help"));
    menuHelp->addAction(actionDocumentation);
    menuHelp->addAction(actionVisitWebsite);
    menuHelp->addAction(actionReportBug);
    menuHelp->addSeparator();
    menuHelp->addAction(actionAbout);
    menuHelp->addAction(actionAboutQt);
    setMenuBar(menuBar);

    // Toolbar
    toolBar_quickConnect = new QToolBar(tr("Quick Connect"), this);
    toolBar_quickConnect->setFloatable(false);

    comboBox_quickConnect_server = new QComboBox(toolBar_quickConnect);
    comboBox_quickConnect_server->setToolTip(tr("Let's you select a prevously stored server."));

    pushButton_quickConnect_connect = new QPushButton(tr("Connect"), toolBar_quickConnect);
    pushButton_quickConnect_connect->setToolTip(tr("Connect's to the server selected in the combobox."));

    toolBar_quickConnect->addAction(actionServerManager);
    toolBar_quickConnect->addWidget(comboBox_quickConnect_server);
    toolBar_quickConnect->addWidget(pushButton_quickConnect_connect);
    addToolBar(toolBar_quickConnect);

    // TabWidget
    tabWidget = TabWidget::getInstance(this);
    tabWidget->setDocumentMode(true);
    tabWidget->setMovable(true);
    tabWidget->setTabsClosable(true);
    tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    setCentralWidget(tabWidget);

    // Tab menu
    menuTab = new QMenu(this);
    menuTab->addAction(actionTabReconnect);
    menuTab->addAction(actionTabDisconnect);

    // Statusbar
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    // Create and read settings
    readSettings();

    // Autoconnect serverentries which has the autoconnect option set to true.
    autoConnect();

    // Loads the server list from ServerManager.
    updateServerList();

    // Actions
    connect(actionServerManager, &QAction::triggered, this, &OpenRcon::actionServerManager_triggered);
    connect(actionQuit,          &QAction::triggered, this, &OpenRcon::close);
    connect(actionQuickConnect,  &QAction::triggered, this, &OpenRcon::actionQuickConnect_triggered);
    connect(actionStatusBar,     &QAction::triggered, this, &OpenRcon::actionStatusBar_triggered);
    connect(actionOptions,       &QAction::triggered, this, &OpenRcon::actionOptions_triggered);
    connect(actionDocumentation, &QAction::triggered, this, &OpenRcon::actionDocumentation_triggered);
    connect(actionVisitWebsite,  &QAction::triggered, this, &OpenRcon::actionVisitWebsite_triggered);
    connect(actionReportBug,     &QAction::triggered, this, &OpenRcon::actionReportBug_triggered);
    connect(actionAbout,         &QAction::triggered, this, &OpenRcon::actionAbout_triggered);
    connect(actionAboutQt,       &QAction::triggered, this, &OpenRcon::actionAboutQt_triggered);
    connect(actionTabReconnect,  &QAction::triggered, this, &OpenRcon::actionTabReconnect_triggered);
    connect(actionTabDisconnect, &QAction::triggered, this, &OpenRcon::actionTabDisconnect_triggered);

    // Toolbars
    connect(pushButton_quickConnect_connect, &QPushButton::clicked,              this, &OpenRcon::pushButton_quickConnect_connect_clicked);
    connect(serverManager,                   &ServerManager::onServerUpdated,    this, &OpenRcon::updateServerList);
    connect(sessionManager,                  &SessionManager::onSessionOpened,   this, &OpenRcon::updateServerList);
    connect(sessionManager,                  &SessionManager::onSessionClosed,   this, &OpenRcon::updateServerList);

    // TabWidget
    connect(tabWidget, &QTabWidget::tabCloseRequested,          this, &OpenRcon::tabWidget_tabCloseRequested);
    connect(tabWidget, &QTabWidget::customContextMenuRequested, this, &OpenRcon::tabWidget_customContextMenuRequested);
}

OpenRcon::~OpenRcon()
{
    tabWidget->clear();

    writeSettings();

    delete settings;

    delete actionServerManager;
    delete actionQuit;
    delete actionQuickConnect;
    delete actionStatusBar;
    delete actionOptions;
    delete actionDocumentation;
    delete actionVisitWebsite;
    delete actionReportBug;
    delete actionAbout;
    delete actionAboutQt;
    delete actionTabReconnect;
    delete actionTabDisconnect;

    delete menuApplication;
    delete menuToolbars;
    delete menuView;
    delete menuTools;
    delete menuHelp;
    delete menuTab;

    delete comboBox_quickConnect_server;
    delete pushButton_quickConnect_connect;
    delete toolBar_quickConnect;

    delete menuBar;
    delete tabWidget;
    delete statusBar;

    delete serverManager;
    delete sessionManager;
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
            toolBar_quickConnect->show();
            actionQuickConnect->setChecked(true);
        } else {
            toolBar_quickConnect->hide();
            actionQuickConnect->setChecked(false);
        }

        if (settings->value("statusBar", true).toBool()) {
            statusBar->show();
            actionStatusBar->setChecked(true);
        } else {
            statusBar->hide();
            actionStatusBar->setChecked(false);
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

void OpenRcon::autoConnect()
{
    QList<ServerEntry*> serverList = serverManager->getServers();

    for (ServerEntry *entry : serverList) {
        if (entry->getAutoConnect()) {
            sessionManager->openSession(entry);
        }
    }
}

void OpenRcon::updateServerList()
{
    comboBox_quickConnect_server->clear();

    // Add the server to the comboBox only if it's not empty, otherwise disable it.
    QList<ServerEntry*> serverList = serverManager->getServers();

    if (!serverList.isEmpty()) {
        for (ServerEntry *serverEntry : serverList) {
            if (!sessionManager->isSessionConnected(serverEntry)) {
                GameEntry game = GameManager::getGame(serverEntry->getGameType());

                comboBox_quickConnect_server->addItem(game.getIcon(), serverEntry->getName(), QVariant::fromValue(serverEntry));
            }
        }

        // Enable quickConnect if servers are available or show an message in the disabled combobox that all the servers is connected if not.
        if (comboBox_quickConnect_server->count() >= 1) {
            comboBox_quickConnect_server->setEnabled(true);
            pushButton_quickConnect_connect->setEnabled(true);
        } else {
            comboBox_quickConnect_server->setEnabled(false);
            pushButton_quickConnect_connect->setEnabled(false);
            comboBox_quickConnect_server->addItem(tr("All servers connected."));
        }
    } else {
        // Show an message in the disabled comboBox that there is no servers added yet.
        comboBox_quickConnect_server->setEnabled(false);
        pushButton_quickConnect_connect->setEnabled(false);
        comboBox_quickConnect_server->addItem(tr("No servers added yet."));
    }
}

void OpenRcon::tabWidget_tabCloseRequested(int index)
{
    sessionManager->closeSession(index);
}

void OpenRcon::tabWidget_customContextMenuRequested(const QPoint &pos)
{
    if (tabWidget->tabBar()->tabAt(pos) >= 0) {
        menuTab->exec(QCursor::pos());
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
            toolBar_quickConnect->show();
            settings->setValue("toolbarQuickConnect", true);
            actionQuickConnect->setChecked(true);
        } else {
            toolBar_quickConnect->hide();
            settings->setValue("toolbarQuickConnect", false);
            actionQuickConnect->setChecked(false);
        }
    settings->endGroup();
}

void OpenRcon::actionStatusBar_triggered()
{
    settings->beginGroup(APP_NAME);
        if (actionStatusBar->isChecked()) {
            statusBar->show();
            settings->setValue("statusBar", true);
            actionStatusBar->setChecked(true);
        } else {
            statusBar->hide();
            settings->setValue("statusBar", false);
            actionStatusBar->setChecked(false);
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

// Tab menu
void OpenRcon::actionTabReconnect_triggered()
{
    GameWidget *gameWidget = dynamic_cast<GameWidget*>(tabWidget->currentWidget());
    Client *client = gameWidget->getClient();
    client->reconnectToHost();
}

void OpenRcon::actionTabDisconnect_triggered()
{
    GameWidget *gameWidget = dynamic_cast<GameWidget*>(tabWidget->currentWidget());
    Client *client = gameWidget->getClient();
    client->disconnectFromHost();
}

// QuickConnect toolbar
void OpenRcon::pushButton_quickConnect_connect_clicked()
{
    ServerEntry *serverEntry = comboBox_quickConnect_server->currentData(Qt::UserRole).value<ServerEntry*>();

    sessionManager->openSession(serverEntry);
}
