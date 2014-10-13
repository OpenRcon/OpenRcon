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

#include <QMainWindow>

#include "Constants.h"

using namespace Constants;

class QSettings;
class QComboBox;
class QPushButton;
struct ServerEntry;
class ServerManager;
class SessionManager;
class ServerListDialog;
class OptionsDialog;
class AboutDialog;
class Game;

class OpenRcon : public QMainWindow
{
    Q_OBJECT

public:
    OpenRcon(QWidget *parent = nullptr);
    ~OpenRcon();

    QTabWidget *getTabWidget();
    ServerManager *getServerManager();
    SessionManager *getSessionManager();

private:
    ServerManager *serverManager;
    SessionManager *sessionManager;
    ServerListDialog *serverListDialog;
    OptionsDialog *optionsDialog;
    AboutDialog *aboutDialog;

    QSettings *settings; 

    // Actions
    QAction *actionServerManager;
    QAction *actionQuit;
    QAction *actionQuickConnect;
    QAction *actionOptions;
    QAction *actionDocumentation;
    QAction *actionVisitWebsite;
    QAction *actionReportBug;
    QAction *actionAbout;
    QAction *actionAboutQt;

    QAction *actionTabReconnect;
    QAction *actionTabDisconnect;

    // Menubar
    QMenuBar *menuBar;
    QMenu *menuApplication;
    QMenu *menuView;
    QMenu *menuToolbars;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuTab;

    // Toolbar
    QToolBar *toolBar_quickConnect;
    QComboBox *comboBox_quickConnect_server;
    QPushButton *pushButton_quickConnect_connect;

    // TabWidget
    QTabWidget *tabWidget;

    // Statusbar
    QStatusBar *statusBar;

    void readSettings();
    void writeSettings();
    void autoConnect();

private slots:
    void updateServerList();
    void tabWidget_tabCloseRequested(int index);
    void tabWidget_customContextMenuRequested(const QPoint &pos);

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

    // Tab menu
    void actionTabReconnect_triggered();
    void actionTabDisconnect_triggered();

    // ServerManager
    void pushButton_quickConnect_connect_clicked();

};

#endif // OPENRCON_H
