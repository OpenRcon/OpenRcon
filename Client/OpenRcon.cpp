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

OpenRcon* OpenRcon::instance = 0;

OpenRcon::OpenRcon(QWidget *parent) : QMainWindow(parent), ui(new Ui::OpenRcon)
{
    ui->setupUi(this);

    directory = new Directory(this);
    gameManager = new GameManager(this);
    serverManager = new ServerManager(this);

    //serverListDialog = new ServerListDialog(this);
    optionsDialog = new OptionsDialog(this);
    aboutDialog = new AboutDialog(this);

    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Sets application title and icon
    setWindowTitle(QString("%1 %2").arg(APP_NAME).arg(APP_VERSION));
    setWindowIcon(QIcon(APP_ICON));

    // Create and read settings
    readSettings();

    // Actions
    ui->actionAbout->setIcon(QIcon(APP_ICON));
    ui->actionAbout->setText(tr("About &%1").arg(APP_NAME));
    ui->actionAbout_Qt->setIcon(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));

    // ServerManager
    comboBox_sm_server = new QComboBox(ui->toolBar_sm);
    pushButton_sm_connect = new QPushButton(tr("Connect"), ui->toolBar_sm);

    populateServers();

    ui->toolBar_sm->addWidget(comboBox_sm_server);
    ui->toolBar_sm->addWidget(pushButton_sm_connect);

    // Actions
    connect(ui->actionServermanager, SIGNAL(triggered()), this, SLOT(actionServermanager_triggered()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->actionConnection, SIGNAL(triggered()), this, SLOT(actionConnection_triggered()));

    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(actionOptions_triggered()));

    connect(ui->actionDocumentation, SIGNAL(triggered()), this, SLOT(actionDocumentation_triggered()));
    connect(ui->actionVisit_website, SIGNAL(triggered()), this, SLOT(actionVisit_website_triggered()));
    connect(ui->actionReport_bug, SIGNAL(triggered()), this, SLOT(actionReport_bug_triggered()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(actionAbout_triggered()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(actionAbout_Qt_triggered()));

    // Toolbars
    connect(pushButton_sm_connect, SIGNAL(clicked()), this, SLOT(pushButton_sm_connect_clicked()));
    connect(serverManager, SIGNAL(onServerUpdate()), this, SLOT(populateServers()));

    // Tabwidget
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

OpenRcon::~OpenRcon()
{
    delete ui;

    delete directory;
    delete settings;
    delete gameManager;
    delete serverManager;

//    delete serverListDialog;
    delete optionsDialog;
    delete aboutDialog;
}

void OpenRcon::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);

    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void OpenRcon::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);

    writeSettings();
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
            ui->actionConnection->setChecked(true);
        } else {
            ui->toolBar_sm->hide();
            ui->actionConnection->setChecked(false);
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

void OpenRcon::addTab(const int &game, const QString &name, const QString &host, const int port, const QString &password)
{
    GameEntry entry = gameManager->getGame(game);

    if (game >= 0) {
        Game *gameObject;

        switch (game) {
            case 0:
                gameObject = new BFBC2Widget(host, port, password);
                break;

            case 1:
                gameObject = new BF3Widget(host, port, password);
                break;

            case 2:
                gameObject = new BF4Widget(host, port, password);
                break;

            case 3:
                gameObject = new MinecraftWidget(host, port, password);
                break;
        }

        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(gameObject, entry.icon, QString("%1 [%2:%3]").arg(name, host).arg(port)));
    } else {
        qDebug() << tr("Unknown game specified, the id was: %1.").arg(game);
    }
}

GameManager* OpenRcon::getGameManager()
{
    return gameManager;
}

void OpenRcon::closeTab(int index)
{
    QWidget *widget = ui->tabWidget->widget(index);
    ConnectionTabWidget *tabWidget = dynamic_cast<ConnectionTabWidget *>(widget);
    tabWidget->getConnection()->hostDisconnect();

    ui->tabWidget->removeTab(index);
}

// Application menu
void OpenRcon::actionServermanager_triggered()
{
    ServerListDialog *serverListDialog = new ServerListDialog(this);
    serverListDialog->exec();

    delete serverListDialog;
}

// View menu
void OpenRcon::actionConnection_triggered()
{
    settings->beginGroup("OpenRcon");
        if (ui->actionConnection->isChecked()) {
            ui->toolBar_sm->show();
            settings->setValue("actionConnection", true);
            ui->actionConnection->setChecked(true);
        } else {
            ui->toolBar_sm->hide();
            settings->setValue("actionConnection", false);
            ui->actionConnection->setChecked(false);
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

// ServerManager
void OpenRcon::pushButton_sm_connect_clicked()
{
    int index = comboBox_sm_server->currentIndex();
    ServerEntry *server = serverManager->getServer(index);

    addTab(server->game, server->name, server->host, server->port, server->password);
}

void OpenRcon::populateServers()
{
    qDebug() << "populateServers() called.";

    comboBox_sm_server->clear();

    // Add the server to the comboBox only if it's not empty, otherwhise disable it.
    QList<ServerEntry *> serverList = serverManager->getServers();

    if (!serverList.isEmpty()) {
        comboBox_sm_server->setEnabled(true);
        pushButton_sm_connect->setEnabled(true);

        foreach (ServerEntry *server, serverList) {
            GameEntry game = gameManager->getGame(server->game);

            comboBox_sm_server->addItem(game.icon, server->name);
        }
    } else {
        comboBox_sm_server->setEnabled(false);
        pushButton_sm_connect->setEnabled(false);

        comboBox_sm_server->addItem(tr("No servers added yet."));
    }
}
