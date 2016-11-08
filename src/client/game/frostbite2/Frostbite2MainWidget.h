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

class FrostbiteEventsWidget;
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
    /* User Interface */
    Ui::Frostbite2MainWidget *ui;
    FrostbiteEventsWidget *eventsWidget;
    ChatWidget *chatWidget;
    BanListWidget *banListWidget;
    ReservedSlotsWidget *reservedSlotsWidget;
    ConsoleWidget *consoleWidget;

    // Server Information
    int roundTime;
    int upTime;

protected slots:
    /* Connection */
    virtual void onConnected();
    virtual void onDisconnected();

    /* Client */
    virtual void onAuthenticated();

    /* User Interface */
    // Server Information
    void updateRoundTime();
    void updateUpTime();

private:
    /* User Interface */
    // Server Information
    QTimer *timerServerInfoRoundTime;
    QTimer *timerServerInfoUpTime;

private slots:
    /* Commands */
    // Misc
    void onLoginHashedCommand(bool authenticated);
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
