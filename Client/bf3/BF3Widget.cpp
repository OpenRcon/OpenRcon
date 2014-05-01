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

BF3Widget::BF3Widget(ServerEntry *serverEntry) : BF3(serverEntry), ui(new Ui::BF3)
{
    ui->setupUi(this);

    /* Events */
    connect(con->getCommandHandler(), SIGNAL(onDataSentEvent(const QString&)), this, SLOT(onDataSentEvent(const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onDataReceivedEvent(const QString&)), this, SLOT(onDataSentEvent(const QString&)));

    /* User Interface */

    // Console
    connect(ui->pushButton_co_co, SIGNAL(clicked()), this, SLOT(pushButton_co_co_clicked()));
    connect(ui->lineEdit_co_co, SIGNAL(editingFinished()), this, SLOT(pushButton_co_co_clicked()));

    connect(ui->pushButton_co_pb, SIGNAL(clicked()), this, SLOT(pushButton_co_pb_clicked()));
    connect(ui->lineEdit_co_pb, SIGNAL(editingFinished()), this, SLOT(pushButton_co_pb_clicked()));
}

BF3Widget::~BF3Widget()
{
    delete ui;
}

void BF3Widget::startupCommands() {
    // Misc
    con->sendCommand("\"admin.eventsEnabled\" \"true\"");
    con->sendCommand("version");
    con->sendCommand("serverInfo");
}

void BF3Widget::logConsole(const int &type, const QString &message)
{
    QString time = QTime::currentTime().toString();

    switch (type) {
        case 0: // Server send
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 1: // Server receive
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;

        case 2: // Punkbuster send
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 3: // PunkBuster receive
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;
    }
}

/* Events */
void BF3Widget::onDataSentEvent(const QString &request)
{
    logConsole(0, request);
}

void BF3Widget::onDataReceivedEvent(const QString &response)
{
    logConsole(1, response);
}

/* Console */
void BF3Widget::pushButton_co_co_clicked()
{
    QString command = ui->lineEdit_co_co->text();
    ui->lineEdit_co_co->clear();

    con->sendCommand(command);
}

void BF3Widget::pushButton_co_pb_clicked()
{
    QString command = ui->lineEdit_co_pb->text();
    ui->lineEdit_co_pb->clear();

    con->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
}
