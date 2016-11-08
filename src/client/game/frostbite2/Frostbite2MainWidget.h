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

#ifndef FROSTBITE2MAINWIDGET_H
#define FROSTBITE2MAINWIDGET_H

#include "Frostbite2Widget.h"

class QTimer;
class QAbstractSocket;
class QString;

class EventsWidget;
class ChatWidget;
class BanListWidget;
class ReservedSlotsWidget;
class ConsoleWidget;

namespace Ui {
    class Frostbite2MainWidget;
}

class Frostbite2MainWidget : public Frostbite2Widget
{
    Q_OBJECT

public:
    Frostbite2MainWidget(Frostbite2Client *client, QWidget *parent = nullptr);
    virtual ~Frostbite2MainWidget() override;

protected:
    Ui::Frostbite2MainWidget *ui;

    /* User Interface */
    // Server Information
    int roundTime;
    int upTime;

protected slots:
    /* User Interface */
    // Server Information
    void updateRoundTime();
    void updateUpTime();

private:
    EventsWidget *eventsWidget;
    ChatWidget *chatWidget;
    BanListWidget *banListWidget;
    ReservedSlotsWidget *reservedSlotsWidget;
    ConsoleWidget *consoleWidget;

    /* User Interface */
    // Server Information
    QTimer *timerServerInfoRoundTime;
    QTimer *timerServerInfoUpTime;

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

};

#endif // FROSTBITE2MAINWIDGET_H
