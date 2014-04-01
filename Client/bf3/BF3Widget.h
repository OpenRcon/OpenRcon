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

#include "ui_BF3.h"
#include "BF3.h"

class BF3Widget : public BF3
{
    Q_OBJECT

public:
    explicit BF3Widget(const QString &host, const int &port, const QString &password);
    ~BF3Widget();

private slots:
    void pushButton_co_send_clicked();

private:
    Ui::BF3 *ui;

};

#endif // BF3WIDGET_H