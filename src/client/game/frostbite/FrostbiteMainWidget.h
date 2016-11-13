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

#ifndef FROSTBITEMAINWIDGET_H
#define FROSTBITEMAINWIDGET_H

#include "FrostbiteWidget.h"

class QTimer;
class QAbstractSocket;
class QString;

class FrostbiteEventsWidget;
class FrostbiteChatWidget;
class FrostbiteBanListWidget;
class FrostbiteConsoleWidget;
class FrostbiteServerInfo;

namespace Ui {
    class FrostbiteMainWidget;
}

class FrostbiteMainWidget : public FrostbiteWidget
{
    Q_OBJECT

public:
    FrostbiteMainWidget(FrostbiteClient *client, QWidget *parent = nullptr);
    virtual ~FrostbiteMainWidget() override;

protected:
    /* User Interface */
    Ui::FrostbiteMainWidget *ui;
    FrostbiteEventsWidget *eventsWidget;
    FrostbiteChatWidget *chatWidget;
    FrostbiteBanListWidget *banListWidget;
    FrostbiteConsoleWidget *consoleWidget;

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
    void onServerInfoCommand(const FrostbiteServerInfo &serverInfo);
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

#endif // FROSTBITEMAINWIDGET_H
