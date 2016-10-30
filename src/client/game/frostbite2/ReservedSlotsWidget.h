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

#ifndef RESERVEDSLOTSWIDGET_H
#define RESERVEDSLOTSWIDGET_H

#include "Frostbite2Widget.h"

class QMenu;
class QAction;
class QStringList;

class Frostbite2Client;

namespace Ui {
    class ReservedSlotsWidget;
}

class ReservedSlotsWidget : public Frostbite2Widget
{
    Q_OBJECT

public:
    ReservedSlotsWidget(Frostbite2Client *client, QWidget *parent = nullptr);
    ~ReservedSlotsWidget() final;

private:
    Ui::ReservedSlotsWidget *ui;
    Frostbite2Client *client;

    QMenu *menu_rs_reservedSlotsList;
    QAction *action_rs_reservedSlotsList_remove;

private slots:
    /* Commands */
    void onLoginHashedCommand(bool auth);
    void onReservedSlotsListListCommand(const QStringList &reservedSlotsList);

    /* User Interface */
    void listWidget_rs_reservedSlotsList_customContextMenuRequested(const QPoint &pos);
    void action_rs_reservedSlotsList_remove_triggered();
    void pushButton_rs_add_clicked();
    void pushButton_rs_load_clicked();
    void pushButton_rs_save_clicked();
    void pushButton_rs_clear_clicked();

};

#endif // RESERVEDSLOTSWIDGET_H
