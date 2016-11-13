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

#include "Frostbite2MainWidget.h"
#include "BF3Client.h"

class BF3ServerInfo;

class BF3MainWidget : public Frostbite2MainWidget
{
    Q_OBJECT

public:
    BF3MainWidget(ServerEntry *serverEntry, QWidget *parent = nullptr);
    ~BF3MainWidget() final;

    BF3Client *getClient() final {
        return static_cast<BF3Client*>(client);
    }

private slots:
    /* Commands */
    // Misc
    void onServerInfoCommand(const BF3ServerInfo &serverInfo);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables

    /* User Interface */

};

#endif // BF3MAINWIDGET_H
