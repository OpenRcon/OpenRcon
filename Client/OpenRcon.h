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

#include <QObject>
#include <QDebug>
#include <QMainWindow>
#include <QDesktopServices>
#include <QIcon>
#include <QEvent>
#include <QCloseEvent>
#include <QSettings>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>

#include "ui_OpenRcon.h"

#include "Constants.h"
#include "GameManager.h"
#include "ServerManager.h"

#include "ConnectionTabWidget.h"

#include "ServerListDialog.h"
#include "OptionsDialog.h"
#include "AboutDialog.h"

using namespace Constants;

namespace Ui {
    class MainWindow;
}

class OpenRcon : public QMainWindow
{
    Q_OBJECT

public:
    OpenRcon(QWidget *parent = 0);
    ~OpenRcon();

    static OpenRcon* getInstance(QWidget *parent = 0) {
        if (!instance) {
            instance = new OpenRcon(parent);
        }

        return instance;
    }

    void addTab(ServerEntry *serverEntry);
    GameManager* getGameManager();

private:
    static OpenRcon *instance;

    Ui::OpenRcon *ui;

    GameManager *gameManager;
    ServerManager *serverManager;
    //ServerListDialog *serverListDialog;
    OptionsDialog *optionsDialog;
    AboutDialog *aboutDialog;

    QSettings *settings;

    QComboBox *comboBox_sm_server;
    QPushButton *pushButton_sm_connect;

    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);

    void readSettings();
    void writeSettings();

private slots:
    void closeTab(int index);

    // Application menu
    void actionServermanager_triggered();

    // View menu
    void actionServers_triggered();

    // Setting menu
    void actionOptions_triggered();

    // Help menu
    void actionReport_bug_triggered();
    void actionVisit_website_triggered();
    void actionDocumentation_triggered();
    void actionAbout_triggered();
    void actionAbout_Qt_triggered();

    // ServerManager
    void pushButton_sm_connect_clicked();
    void populateServers();

};

#endif // OPENRCON_H
