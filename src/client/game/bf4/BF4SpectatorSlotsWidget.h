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

#ifndef BF4SPECTATORSLOTSWIDGET_H
#define BF4SPECTATORSLOTSWIDGET_H

#include "BF4Widget.h"

class QMenu;
class QAction;

namespace Ui {
    class BF4SpectatorSlotsWidget;
}

class BF4SpectatorSlotsWidget : public BF4Widget
{
    Q_OBJECT

public:
    BF4SpectatorSlotsWidget(BF4Client *client, QWidget *parent = nullptr);
    ~BF4SpectatorSlotsWidget() final;

private:
    Ui::BF4SpectatorSlotsWidget *ui;

    /* User Interface */
    QMenu *menu_spectatorList;
    QAction *action_spectatorList_remove;

private slots:
    /* Events */

    /* Commands */
    void onLoginHashedCommand(bool auth);
    void onSpectatorListListCommand(const QStringList &spectatorList);

    /* User Interface */
    void listWidget_spectatorList_customContextMenuRequested(const QPoint &pos);
    void action_spectatorList_remove_triggered();
    void pushButton_add_clicked();
    void pushButton_save_clicked();
    void pushButton_clear_clicked();

};

#endif // BF4SPECTATORSLOTSWIDGET_H
