/*
 * Copyright (C) 2014 The OpenRcon Project.
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


#ifndef BANLISTWIDGET_H
#define BANLISTWIDGET_H

#include <QWidget>

#include "BanListEntry.h"

class QMenu;
class FrostbiteConnection;
class Frostbite2CommandHandler;

namespace Ui {
    class BanListWidget;
}

class BanListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BanListWidget(FrostbiteConnection *connection, QWidget *parent = nullptr);
    ~BanListWidget();

private:
    Ui::BanListWidget *ui;
    FrostbiteConnection *connection;
    Frostbite2CommandHandler *commandHandler;

    /* User Interface */
    // Banlist
    QMenu *menu_bl_banList;
    QAction *action_bl_banList_remove;

private slots:
    /* Commands */
    // Banning
    void onBanListListCommand(const QList<BanListEntry> &banList);

    /* User Interface */
    // BanList
    void tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos);
    void action_bl_banList_remove_triggered();
    void addBanListItem(const QString &idType, const QString &id, const QString &banType, int seconds, int rounds, const QString &reason);
    void setBanlist(const BanList &banList);

};

#endif // BANLISTWIDGET_H
