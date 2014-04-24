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

#include "MinecraftWidget.h"

MinecraftWidget::MinecraftWidget(const QString &host, const int &port, const QString &password) : Minecraft(host, port, password), ui(new Ui::Minecraft)
{
    ui->setupUi(this);

    /* Events */
    connect(con->commandHandler, SIGNAL(onDataSent(const QString&)), this, SLOT(onDataSent(const QString&)));
    connect(con->commandHandler, SIGNAL(onDataReceived(const QString&)), this, SLOT(onDataSent(const QString&)));

    connect(con->commandHandler, SIGNAL(onAuthenticated(const bool&)), this, SLOT(onAuthenticated(const bool&)));

    connect(ui->lineEdit_co_input, SIGNAL(returnPressed()), this, SLOT(on_pushButton_co_send_clicked()));
}

MinecraftWidget::~MinecraftWidget()
{
    delete ui;
}

void MinecraftWidget::logMessage(const int &type, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QTime::currentTime().toString());

    if (type == 0) { // Info
//        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 1) { // Error
//        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 2) { // Send
        ui->textEdit_co_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 3) { // Receive
        ui->textEdit_co_output->append(QString("%1 <span style=\"color:#0000FF\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 4) { // Chat
        ui->textEdit_ch_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    }
}

/* Events */
void MinecraftWidget::onDataSent(const QString &command)
{
    logMessage(2, command);
}

void MinecraftWidget::onDataReceived(const QString &response)
{
    logMessage(3, response);
}

void MinecraftWidget::onAuthenticated(const bool &auth)
{
    if (auth) {
        logMessage(0, "Successfully logged in!");
    } else {
        logMessage(1, "Login failed!");
    }
}

void MinecraftWidget::on_pushButton_co_send_clicked()
{
    QString command = ui->lineEdit_co_input->text();

    con->sendCommand(command);

    ui->lineEdit_co_input->clear();
}
