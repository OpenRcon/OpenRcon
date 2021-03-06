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

#ifndef FROSTBITE2RESERVEDSLOTSWIDGET_H
#define FROSTBITE2RESERVEDSLOTSWIDGET_H

#include "Frostbite2Widget.h"

class QMenu;
class QAction;
class QStringList;
class QPoint;

class Frostbite2Client;

namespace Ui {
    class Frostbite2ReservedSlotsWidget;
}

class Frostbite2ReservedSlotsWidget : public Frostbite2Widget
{
    Q_OBJECT

public:
    Frostbite2ReservedSlotsWidget(Frostbite2Client *client, QWidget *parent = nullptr);
    ~Frostbite2ReservedSlotsWidget() final;

private:
    Ui::Frostbite2ReservedSlotsWidget *ui;
    Frostbite2Client *client;

    QMenu *menu;
    QAction *action_remove;

private slots:
    /* Commands */
    void onReservedSlotsListListCommand(const QStringList &reservedSlotsList);

    /* User Interface */
    void listWidget_customContextMenuRequested(const QPoint &pos);
    void action_remove_triggered();
    void pushButton_add_clicked();

};

#endif // FROSTBITE2RESERVEDSLOTSWIDGET_H
