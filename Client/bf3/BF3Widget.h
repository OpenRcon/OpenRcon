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

#ifndef BF3WIDGET_H
#define BF3WIDGET_H

#include <QTime>

#include "ui_BF3.h"
#include "BF3.h"

class BF3Widget : public BF3
{
    Q_OBJECT

public:
    explicit BF3Widget(ServerEntry *serverEntry);
    ~BF3Widget();

private:
    Ui::BF3 *ui;

    void startupCommands();
    void logConsole(const int &type, const QString &message);

private slots:
    /* Events */
    void onDataSentEvent(const QString &request);
    void onDataReceivedEvent(const QString &response);

    /* Console */
    void pushButton_co_co_clicked();
    void pushButton_co_pb_clicked();

};

#endif // BF3WIDGET_H
