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

#ifndef BF4MAINWIDGET_H
#define BF4MAINWIDGET_H

#include "Frostbite2MainWidget.h"
#include "BF4Client.h"

class BF4PlayerListWidget;
class BF4OptionsWidget;
class BF4MapListWidget;
class BF4SpectatorSlotsWidget;
class BF4ServerInfo;

class BF4MainWidget : public Frostbite2MainWidget
{
    Q_OBJECT

public:
    BF4MainWidget(ServerEntry *serverEntry, QWidget *parent = nullptr);
    ~BF4MainWidget() final;

    BF4Client *getClient() const final {
        return static_cast<BF4Client*>(client);
    }

private:
    /* User Interface */
    BF4PlayerListWidget *playerListWidget;
    BF4OptionsWidget *optionsWidget;
    BF4MapListWidget *mapListWidget;
    BF4SpectatorSlotsWidget *spectatorSlotsWidget;

private slots:
    /* Connection */
    void onConnected() final;
    void onDisconnected() final;

    /* Client */
    void onAuthenticated() final;

    /* Commands */
    // Misc
    void onServerInfoCommand(const BF4ServerInfo &serverInfo);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables
    void onVarsAlwaysAllowSpectatorsCommand(bool enabled);

    /* User Interface */

};

#endif // BF4MAINWIDGET_H
