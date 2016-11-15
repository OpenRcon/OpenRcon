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

#include "FrostbiteMainWidget.h"
#include "Frostbite2Client.h"

class Frostbite2ReservedSlotsWidget;

namespace Ui {
    class Frostbite2MainWidget;
}

class Frostbite2MainWidget : public FrostbiteMainWidget
{
    Q_OBJECT

public:
    Frostbite2MainWidget(Frostbite2Client *client, QWidget *parent = nullptr);
    virtual ~Frostbite2MainWidget() override;

    virtual Frostbite2Client *getClient() const override {
        return static_cast<Frostbite2Client*>(client);
    }

protected:
    /* User Interface */
    Frostbite2ReservedSlotsWidget *reservedSlotsWidget;

protected slots:
    /* Connection */
    void onConnected() override;
    void onDisconnected() override;

    /* Client */
    void onAuthenticated() override;

    /* User Interface */

private slots:
    /* Commands */
    // Misc

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables

    /* User Interface */

};

#endif // FROSTBITE2MAINWIDGET_H
