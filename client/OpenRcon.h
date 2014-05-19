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

#ifndef OPENRCON_H
#define OPENRCON_H

#include <QDebug>
#include <QMainWindow>
#include <QDesktopServices>
#include <QIcon>
#include <QSettings>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QUrl>

#include "Constants.h"

struct ServerEntry;
class ServerManager;
class ServerListDialog;
class OptionsDialog;
class AboutDialog;
class Game;

using namespace Constants;

namespace Ui {
    class OpenRcon;
}

class OpenRcon : public QMainWindow
{
    Q_OBJECT

public:
    OpenRcon(QWidget *parent = nullptr);
    ~OpenRcon();

    static OpenRcon *getInstance();

    QTabWidget *getTabWidget();
    ServerManager *getServerManager();

private:
    static OpenRcon *m_Instance;

    Ui::OpenRcon *ui;
    ServerManager *serverManager;
    ServerListDialog *serverListDialog;
    OptionsDialog *optionsDialog;
    AboutDialog *aboutDialog;

    QSettings *settings;

    QAction *actionServerManager;
    QAction *actionQuit;
    QAction *actionQuickConnect;
    QAction *actionOptions;
    QAction *actionDocumentation;
    QAction *actionVisitWebsite;
    QAction *actionReportBug;
    QAction *actionAbout;
    QAction *actionAboutQt;

    QComboBox *comboBox_quickConnect_server;
    QPushButton *pushButton_quickConnect_connect;

    void readSettings();
    void writeSettings();

private slots:
    void updateServerList();
    void closeTab(int index);

    // Application menu
    void actionServerManager_triggered();

    // View menu
    void actionQuickConnect_triggered();

    // Setting menu
    void actionOptions_triggered();

    // Help menu
    void actionDocumentation_triggered();
    void actionVisitWebsite_triggered();
    void actionReportBug_triggered();
    void actionAbout_triggered();
    void actionAboutQt_triggered();

    // ServerManager
    void pushButton_quickConnect_connect_clicked();

};

#endif // OPENRCON_H
