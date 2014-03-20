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

OpenRcon *OpenRcon::m_Instance = 0;

OpenRcon::OpenRcon(QWidget *parent) : QMainWindow(parent), ui(new Ui::OpenRcon), m_comboBox_sm_connect(true)
{
    ui->setupUi(this);
    dir = new Directory(this);

    pluginDialog = new PluginDialog(this);
    settingsDialog = new SettingsDialog(this);
    aboutDialog = new About(this);

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    tab_webView = 0;

    // Sets application title and icon
    setWindowTitle(QString("%1 %2").arg(APP_NAME).arg(APP_VERSION));
    setWindowIcon(QIcon(APP_ICON));

    // Create and read settings
    settings = new QSettings(APP_NAME, APP_NAME, this);
    readSettings();

    // Set text for actionAbout
    ui->actionAbout->setText(QString(tr("About %1")).arg(APP_NAME));
    ui->actionAbout->setIcon(QIcon(APP_ICON));

    // Connect ui
    connect(ui->actionServermanager, SIGNAL(triggered()), this, SLOT(actionServermanager_triggered()));
    connect(ui->actionPluginmanager, SIGNAL(triggered()), this, SLOT(actionPluginmanager_triggered()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(actionDisconnect_triggered()));

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actionExit_triggered()));

    home();

/*!
  Fixes ugly toolBar on MacOS X
  */

#ifdef Q_OS_MAC
    ui->toolBar_qc->setMovable(false);
    ui->toolBar_sm->setMovable(false);
#endif

    // ServerManager
    comboBox_sm = new QComboBox(this);
    ui->toolBar_sm->addWidget(comboBox_sm);

    PopulateServerItems();

    // Quickconnect
    comboBox_qc_game = new QComboBox(this);
    comboBox_qc_game->addItem(QIcon(GAME_BF3_ICON), GAME_BF3_TEXT);
    comboBox_qc_game->addItem(QIcon(GAME_BFBC2_ICON), GAME_BFBC2_TEXT);

    label_qc_host = new QLabel(tr("Host:"), this);
    label_qc_port = new QLabel(tr("Port:"), this);
    label_qc_password = new QLabel(tr("Password:"), this);
    lineEdit_qc_host = new QLineEdit(this);
    lineEdit_qc_port = new QLineEdit(this);
    lineEdit_qc_port->setValidator(new QIntValidator(1, 65535, lineEdit_qc_port));
    lineEdit_qc_password = new QLineEdit(this);
    lineEdit_qc_password->setEchoMode(QLineEdit::Password);
    pushButton_qc_quickconnect = new QPushButton(tr("Quickconnect"), this);

    ui->toolBar_qc->addWidget(comboBox_qc_game);
    ui->toolBar_qc->addWidget(label_qc_host);
    ui->toolBar_qc->addWidget(lineEdit_qc_host);
    ui->toolBar_qc->addWidget(label_qc_port);
    ui->toolBar_qc->addWidget(lineEdit_qc_port);
    ui->toolBar_qc->addWidget(label_qc_password);
    ui->toolBar_qc->addWidget(lineEdit_qc_password);
    ui->toolBar_qc->addWidget(pushButton_qc_quickconnect);

    connect(comboBox_sm, SIGNAL(currentIndexChanged(int)), this, SLOT(connect_sm(int)));

    connect(lineEdit_qc_host, SIGNAL(returnPressed()), this, SLOT(connect_qc()));
    connect(lineEdit_qc_port, SIGNAL(returnPressed()), this, SLOT(connect_qc()));
    connect(lineEdit_qc_password, SIGNAL(returnPressed()), this, SLOT(connect_qc()));
    connect(pushButton_qc_quickconnect, SIGNAL(clicked()), this, SLOT(connect_qc()));
}

OpenRcon::~OpenRcon()
{
    delete ui;
    delete dir;
    delete settings;

    delete pluginDialog;
    delete settingsDialog;
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
    settings->beginGroup(SETTINGS_OPENRCON);
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
        if (settings->value("actionQuickconnect", true).toBool()) {
            ui->toolBar_qc->show();
            ui->actionQuickconnect->setChecked(true);
        } else {
            ui->toolBar_qc->hide();
            ui->actionQuickconnect->setChecked(false);
        }
    settings->endGroup();
}

void OpenRcon::writeSettings()
{
    settings->beginGroup(SETTINGS_OPENRCON);
        settings->setValue("IsMaximized", isMaximized());
        settings->setValue("Size", size());
        settings->setValue("Position", pos());
    settings->endGroup();
}

void OpenRcon::PopulateServerItems()
{
    // TODO: Make this work
}

void OpenRcon::newTab(const QString &name, const QString &host, const int port, const QString &password, const QString &game)
{
    if (game == GAME_BF3_TEXT) {
        BF3 *tab_bf3 = new BF3(host, port, password);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab_bf3, QIcon(GAME_BF3_ICON), QString("%1 [%2]").arg(name, GAME_BF3_TEXT)));
    } else if (game == GAME_BFBC2_TEXT) {
        BFBC2 *tab_bfbc2 = new BFBC2(host, port, password);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab_bfbc2, QIcon(GAME_BFBC2_ICON), QString("%1 [%2]").arg(name, GAME_BFBC2_TEXT)));
    }
}

void OpenRcon::closeTab(int index)
{
    if (ui->tabWidget->widget(index) == tab_webView) {
        tab_webView = 0;
    } else {
        QWidget *widget = ui->tabWidget->widget(index);
        ConnectionTabWidget *ctw = dynamic_cast<ConnectionTabWidget*>(widget);
        ctw->getConnection()->hostDisconnect();;
    }

    ui->tabWidget->removeTab(index);
}

void OpenRcon::connect_sm(int index)
{
    if (index != -1 && m_comboBox_sm_connect) {
        ServerEntry entry = m_serverEntries.at(index);
        //newTab(entry.name, entry.host, entry.port, entry.password, entry.game);
    }
}

void OpenRcon::connect_qc()
{
    if (!lineEdit_qc_host->text().isEmpty() | !lineEdit_qc_port->text().isEmpty() | !lineEdit_qc_password->text().isEmpty()) {
        QString host = lineEdit_qc_host->text();
        int port = lineEdit_qc_port->text().toInt();
        QString password = lineEdit_qc_password->text();
        QString game = comboBox_qc_game->currentText();

        newTab(QString("%1:%2").arg(host, port), host, port, password, game);
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("Check server, port and password settings."));
    }
}

void OpenRcon::webFrame(const QString &title, const QString &url)
{
    if (!tab_webView) {
        tab_webView = new QWebView(this);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab_webView, title));
    }

    tab_webView->load(url);    
}

void OpenRcon::home()
{
    webFrame(tr("Home"), APP_URL);
}

// Application menu
void OpenRcon::actionServermanager_triggered()
{
    ServerListDialog *dlg = new ServerListDialog(this);
    dlg->exec();

    delete dlg;
}

void OpenRcon::actionPluginmanager_triggered()
{
    pluginDialog->exec();
}

void OpenRcon::actionDisconnect_triggered()
{
    int index = ui->tabWidget->currentIndex();

    if (ui->tabWidget->currentWidget() != tab_webView) {
        closeTab(index);
    }
}

void OpenRcon::actionExit_triggered()
{
    close();
}

// View menu
void OpenRcon::on_actionConnection_triggered()
{
    settings->beginGroup(SETTINGS_OPENRCON);
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

void OpenRcon::on_actionQuickconnect_triggered()
{
    settings->beginGroup(SETTINGS_OPENRCON);
        if (ui->actionQuickconnect->isChecked()) {
            ui->toolBar_qc->show();
            settings->setValue("actionQuickconnect", true);
            ui->actionQuickconnect->setChecked(true);
        } else {
            ui->toolBar_qc->hide();
            settings->setValue("actionQuickconnect", false);
            ui->actionQuickconnect->setChecked(false);
        }
    settings->endGroup();
}

// Tools menu
void OpenRcon::actionSettings_triggered()
{
    settingsDialog->exec();
}

// Help menu
void OpenRcon::on_actionReport_bug_triggered()
{
    QDesktopServices::openUrl(QUrl(APP_BUG));
}

void OpenRcon::on_actionDocumentation_triggered()
{
    webFrame(tr("Documentation"), APP_DOC);
}

void OpenRcon::on_actionAbout_triggered()
{
    aboutDialog->exec();
}

void OpenRcon::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void OpenRcon::on_actionHome_triggered()
{
    home();
}
