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

#include <QCompleter>
#include <QDateTime>

#include "ConsoleWidget.h"
#include "ui_ConsoleWidget.h"
#include "FrostbiteConnection.h"
#include "FrostbiteCommandHandler.h"

ConsoleWidget::ConsoleWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleWidget),
    m_connection(connection),
    m_commandHandler(connection->getCommandHandler())
{
    ui->setupUi(this);

    /* Events */
    connect(m_connection, &Connection::onDataSentEvent,     this, &ConsoleWidget::onDataSentEvent);
    connect(m_connection, &Connection::onDataReceivedEvent, this, &ConsoleWidget::onDataReceivedEvent);

    /* Commands */
    connect(m_commandHandler, &FrostbiteCommandHandler::onPunkBusterMessageEvent, this, &ConsoleWidget::onPunkBusterMessageEvent);

    /* User Interface */
    connect(ui->pushButton_co_co, &QPushButton::clicked,        this, &ConsoleWidget::pushButton_co_co_clicked);
    connect(ui->lineEdit_co_co,   &QLineEdit::editingFinished,  this, &ConsoleWidget::pushButton_co_co_clicked);
    connect(ui->pushButton_co_pb, &QPushButton::clicked,        this, &ConsoleWidget::pushButton_co_pb_clicked);
    connect(ui->lineEdit_co_pb,   &QLineEdit::editingFinished,  this, &ConsoleWidget::pushButton_co_pb_clicked);
}

ConsoleWidget::ConsoleWidget(FrostbiteConnection *connection, const QStringList &commandList, QWidget *parent) :
    ConsoleWidget(connection, parent)
{
    // Create completer and set commandList.
    ui->lineEdit_co_co->setCompleter(new QCompleter(commandList, this));
}

ConsoleWidget::~ConsoleWidget()
{
    delete ui;
}

void ConsoleWidget::logConsole(int type, const QString &message)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    switch (type) {
        case 0: // Server send
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 1: // Server receive
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;

        case 2: // Punkbuster con->send
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 3: // PunkBuster receive
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;
    }
}

void ConsoleWidget::onDataSentEvent(const QString &request)
{
    logConsole(0, request);
}

void ConsoleWidget::onDataReceivedEvent(const QString &response)
{
    logConsole(1, response);
}

void ConsoleWidget::onPunkBusterMessageEvent(const QString &message)
{
    logConsole(2, message);
}

void ConsoleWidget::pushButton_co_co_clicked()
{
    QString command = ui->lineEdit_co_co->text();

    ui->lineEdit_co_co->clear();
    m_connection->sendCommand(command);
}

void ConsoleWidget::pushButton_co_pb_clicked()
{
    QString command = ui->lineEdit_co_pb->text();

    ui->lineEdit_co_pb->clear();
    m_commandHandler->sendPunkBusterPbSvCommand(command);
}
