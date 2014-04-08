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
#include <QWidget>
#include <QDesktopServices>
#include <QStringList>
#include <QIcon>
#include <QEvent>
#include <QCloseEvent>
#include <QSettings>
#include <QTranslator>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QWebView>

#include "ui_OpenRcon.h"

#include "Constants.h"
#include "Directory.h"
#include "GameManager.h"
#include "ServerManager.h"
#include "Connection.h"
#include "ConnectionTabWidget.h"

#include "ServerListDialog.h"
#include "SettingsDialog.h"
#include "About.h"

using namespace Constants;

class OpenRcon : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenRcon(QWidget *parent = 0);
    ~OpenRcon();

    static OpenRcon* getInstance(QWidget* parent = 0) {
        if (!m_Instance) {
            m_Instance = new OpenRcon(parent);
        }

        return m_Instance;
    }

    void newTab(const int &game, const QString &name, const QString &host, const int port, const QString &password);
    GameManager* getGameManager();

protected:
    static OpenRcon* m_Instance;

private:
    Ui::OpenRcon *ui;

    Directory *dir;
    GameManager *gameManager;
    ServerManager *serverManager;

    QSettings *settings;

    SettingsDialog *settingsDialog;
    About *aboutDialog;

    // Actions
    QAction *actionAboutQt;
    QAction *actionAbout;

    // ServerManager
    QComboBox *comboBox_sm_server;
    QPushButton *pushButton_sm_connect;

    // Quick Connect
    QComboBox *comboBox_qc_game;
    QGridLayout *gridLayout_webView;
    QLabel *label_qc_host;
    QLabel *label_qc_port;
    QLabel *label_qc_password;
    QLineEdit *lineEdit_qc_host;
    QSpinBox *spinBox_qc_port;
    QLineEdit *lineEdit_qc_password;
    QPushButton *pushButton_qc_quickconnect;

    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);

    void readSettings();
    void writeSettings();

private slots:
    void closeTab(int index);

    // Application menu
    void actionServermanager_triggered();
    void actionDisconnect_triggered();

    // View menu
    void actionConnection_triggered();
    void actionQuickconnect_triggered();

    // Setting menu
    void actionSettings_triggered();

    // Help menu
    void actionReport_bug_triggered();
    void actionDocumentation_triggered();

    void connect_qc();

    // ServerManager
    void pushButton_sm_connect_clicked();

    void aboutQt();
    void about();

};

#endif // OPENRCON_H
