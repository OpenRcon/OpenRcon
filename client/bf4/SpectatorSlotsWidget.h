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

#ifndef SPECTATORSLOTSWIDGET_H
#define SPECTATORSLOTSWIDGET_H

#include <QWidget>

class QMenu;
class QAction;
class FrostbiteConnection;
class BF4CommandHandler;

namespace Ui {
    class SpectatorSlotsWidget;
}

class SpectatorSlotsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpectatorSlotsWidget(FrostbiteConnection *connection, QWidget *parent = nullptr);
    ~SpectatorSlotsWidget();

private:
    Ui::SpectatorSlotsWidget *ui;
    FrostbiteConnection *m_connection;
    BF4CommandHandler *m_commandHandler;

    QMenu *menu_spectatorList;
    QAction *action_spectatorList_remove;

private slots:
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

#endif // SPECTATORSLOTSWIDGET_H
