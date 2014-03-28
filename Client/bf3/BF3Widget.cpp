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

#include "BF3Widget.h"

BF3Widget::BF3Widget(const QString &host, const int &port, const QString &password) : BF3(host, port, password), ui(new Ui::BF3)
{
    ui->setupUi(this);

    connect(ui->pushButton_co_send, SIGNAL(clicked()), this, SLOT(pushButton_co_send_clicked()));
    connect(ui->lineEdit_co_input, SIGNAL(editingFinished()), this, SLOT(pushButton_co_send_clicked()));
}

BF3Widget::~BF3Widget()
{
    delete ui;
}

void BF3Widget::pushButton_co_send_clicked()
{
    QString command = ui->lineEdit_co_input->text();
    ui->lineEdit_co_input->clear();

    con->sendCommand(command);
}
