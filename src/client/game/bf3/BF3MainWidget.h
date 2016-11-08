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
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BF3MAINWIDGET_H
#define BF3MAINWIDGET_H

#include "BF3Widget.h"

class QTimer;
class QAbstractSocket;
class QString;

class FrostbiteEventsWidget;
class ChatWidget;
class BanListWidget;
class ReservedSlotsWidget;
class ConsoleWidget;

namespace Ui {
    class Frostbite2MainWidget;
}

class BF3MainWidget : public BF3Widget
{
    Q_OBJECT

public:
    BF3MainWidget(ServerEntry *serverEntry, QWidget *parent = nullptr);
    ~BF3MainWidget() final;

private:
    Ui::Frostbite2MainWidget *ui;

    FrostbiteEventsWidget *eventsWidget;
    ChatWidget *chatWidget;
    BanListWidget *banListWidget;
    ReservedSlotsWidget *reservedSlotsWidget;
    ConsoleWidget *consoleWidget;

    /* User Interface */
    // ServerInfo
    QTimer *timerServerInfoRoundTime;
    QTimer *timerServerInfoUpTime;
    int roundTime;
    int upTime;

    void setAuthenticated(bool auth);
    void startupCommands(bool auth);

private slots:
    /* Events */
    void onConnected(QAbstractSocket *socket);
    void onDisconnected(QAbstractSocket *socket);

    /* Commands */
    // Misc
    void onLoginHashedCommand(bool auth);
    void onVersionCommand(const QString &type, int build);
    void onServerInfoCommand(const BF3ServerInfo &serverInfo);


    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables

    /* User Interface */
    // Server Information
    void pushButton_si_restartRound_clicked();
    void pushButton_si_runNextRound_clicked();
    void updateRoundTime();
    void updateUpTime();

};

#endif // BF3MAINWIDGET_H
