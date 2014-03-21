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

#include "Connection.h"
#include "ConnectionTabWidget.h"
#include "ServerListDialog.h"
#include "ServerEntry.h"
#include "Directory.h"

#include "About.h"
#include "SettingsDialog.h"

#include "BFBC2.h"

using namespace Constants;

class OpenRcon : public QMainWindow
{
    Q_OBJECT

protected:
    explicit OpenRcon(QWidget *parent = 0);
    static OpenRcon* m_Instance;

    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

public:
    static OpenRcon *getInstance(QWidget* parent = 0) {
        if (!m_Instance) {
            m_Instance = new OpenRcon(parent);
        }

        return m_Instance;
    }

    ~OpenRcon();

    void newTab(const QString &game, const QString &name, const QString &host, const int port, const QString &password);

    void PopulateServerItems();

private:
    Ui::OpenRcon *ui;

    Directory *dir;

    SettingsDialog *settingsDialog;
    About *aboutDialog;

    QSettings *settings;

    void readSettings();
    void writeSettings();

    void webFrame(const QString &title, const QString &url);

    bool m_comboBox_sm_connect;

    QList<ServerEntry> m_serverEntries;

    QComboBox *comboBox_sm;
    QComboBox *comboBox_qc_game;
    QGridLayout *gridLayout_webView;
    QLabel *label_qc_host;
    QLabel *label_qc_port;
    QLabel *label_qc_password;
    QLineEdit *lineEdit_qc_host;
    QLineEdit *lineEdit_qc_port;
    QLineEdit *lineEdit_qc_password;
    QPushButton *pushButton_qc_quickconnect;
    QWebView *tab_webView;

private slots:

    void closeTab(int);

    void connect_sm(int index);
    void connect_qc();

    void home();

    // Application menu
    void actionServermanager_triggered();
    void actionDisconnect_triggered();
    void actionExit_triggered();

    void actionSettings_triggered();

    void on_actionHome_triggered();

    void on_actionConnection_triggered();
    void on_actionQuickconnect_triggered();
    void on_actionReport_bug_triggered();
    void on_actionDocumentation_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();

};

#endif // OPENRCON_H
