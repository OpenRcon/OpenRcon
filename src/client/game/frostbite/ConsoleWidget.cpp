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

#include <QCompleter>
#include <QDateTime>

#include "ConsoleWidget.h"
#include "ui_ConsoleWidget.h"
#include "FrostbiteClient.h"

ConsoleWidget::ConsoleWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::ConsoleWidget)
{
    ui->setupUi(this);

    /* Events */
    connect(getClient()->getConnection(), &Connection::onDisconnected, this, &ConsoleWidget::onDisconnected);
    connect(getClient()->getConnection(), &Connection::onDataSent,     this, &ConsoleWidget::onDataSent);
    connect(getClient()->getConnection(), &Connection::onDataReceived, this, &ConsoleWidget::onDataReceived);

    /* Commands */
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &ConsoleWidget::onLoginHashedCommand);
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPunkBusterMessageEvent, this, &ConsoleWidget::onPunkBusterMessageEvent);

    /* User Interface */
    connect(ui->lineEdit_co_co,   &QLineEdit::textChanged,      this, &ConsoleWidget::lineEdit_co_co_textChanged);
    connect(ui->pushButton_co_co, &QPushButton::clicked,        this, &ConsoleWidget::pushButton_co_co_clicked);
    connect(ui->lineEdit_co_co,   &QLineEdit::editingFinished,  this, &ConsoleWidget::pushButton_co_co_clicked);
    connect(ui->lineEdit_co_pb,   &QLineEdit::textChanged,      this, &ConsoleWidget::lineEdit_co_pb_textChanged);
    connect(ui->pushButton_co_pb, &QPushButton::clicked,        this, &ConsoleWidget::pushButton_co_pb_clicked);
    connect(ui->lineEdit_co_pb,   &QLineEdit::editingFinished,  this, &ConsoleWidget::pushButton_co_pb_clicked);
}

ConsoleWidget::ConsoleWidget(FrostbiteClient *client, const QStringList &commandList, QWidget *parent) :
    ConsoleWidget(client, parent)
{
    // Create completer and set commandList.
    ui->lineEdit_co_co->setCompleter(new QCompleter(commandList, this));
}

ConsoleWidget::~ConsoleWidget()
{
    delete ui;
}

void ConsoleWidget::clear()
{
    ui->textEdit_co_co->clear();
    ui->textEdit_co_pb->clear();
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

/* Event */
void ConsoleWidget::onDisconnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    clear();
}

void ConsoleWidget::onDataSent(const QString &request)
{
    logConsole(0, request);
}

void ConsoleWidget::onDataReceived(const QString &response)
{
    logConsole(1, response);
}

/* Commands */
void ConsoleWidget::onLoginHashedCommand(bool auth)
{
    ui->tab_co_pb->setEnabled(auth);
}

void ConsoleWidget::onPunkBusterMessageEvent(const QString &message)
{
    logConsole(2, message);
}

/* User Interface */
void ConsoleWidget::lineEdit_co_co_textChanged(const QString &text)
{
    ui->pushButton_co_co->setEnabled(!text.isEmpty());
}

void ConsoleWidget::pushButton_co_co_clicked()
{
    getClient()->getConnection()->sendCommand(ui->lineEdit_co_co->text());
    ui->lineEdit_co_co->clear();
}

void ConsoleWidget::lineEdit_co_pb_textChanged(const QString &text)
{
    ui->pushButton_co_pb->setEnabled(!text.isEmpty());
}

void ConsoleWidget::pushButton_co_pb_clicked()
{
    getClient()->getCommandHandler()->sendPunkBusterPbSvCommand(ui->lineEdit_co_pb->text());
    ui->lineEdit_co_pb->clear();
}
