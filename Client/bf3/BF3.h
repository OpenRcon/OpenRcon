/*
 * Copyright (C) 2010 The OpenRcon Project.
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

#ifndef BF3_H
#define BF3_H

#include <QObject>
#include <QCompleter>
#include <QMenu>

#include "ConnectionTabWidget.h"

#include "ui_BF3.h"

#include "BF3Connection.h"

class BF3 : public ConnectionTabWidget {
    Q_OBJECT

public:
    explicit BF3(const QString &host, const int &port, const QString &password);
    ~BF3();

    virtual Connection *getConnection() { return con; }

private:
    Ui::BF3 *ui;

    BF3Connection *con;

    QString host;
    QString port;
    QString password;

    QCompleter *completer;
    QMenu *menu_pl_playerBan;
    QMenu *menu_pl_playerKick;
    QMenu *menu_pl_playerMove;
    QMenu *menu_pl_player;

private slots:
    void slotLogMessage(const QString &type, const QString &msg);
    void treeWidget_pl_customContextMenuRequested(QPoint pos);
    void on_pushButton_co_send_clicked();
    void slotPlayerListChange();

};

#endif // BF3_H