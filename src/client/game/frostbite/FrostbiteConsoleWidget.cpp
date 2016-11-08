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
#include <QString>
#include <QDateTime>

#include "FrostbiteConsoleWidget.h"
#include "ui_FrostbiteConsoleWidget.h"

FrostbiteConsoleWidget::FrostbiteConsoleWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::FrostbiteConsoleWidget)
{
    ui->setupUi(this);

    // Set Punkbuster tab to disabled by default.
    ui->tabWidget_co->setTabEnabled(ui->tabWidget_co->indexOf(ui->tab_co_pb), false);

    /* Connection */
    connect(getClient()->getConnection(),     &Connection::onDisconnected,                        this, &FrostbiteConsoleWidget::onDisconnected);
    connect(getClient()->getConnection(),     &Connection::onDataSent,                            this, &FrostbiteConsoleWidget::onDataSent);
    connect(getClient()->getConnection(),     &Connection::onDataReceived,                        this, &FrostbiteConsoleWidget::onDataReceived);

    /* Client */
    connect(getClient(),                      &FrostbiteClient::onAuthenticated,                  this, &FrostbiteConsoleWidget::onAuthenticated);

    /* Events */
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onPunkBusterMessageEvent, this, &FrostbiteConsoleWidget::onPunkBusterMessageEvent);

    /* User Interface */
    connect(ui->lineEdit_co_co,               &QLineEdit::textChanged,                            this, &FrostbiteConsoleWidget::lineEdit_co_co_textChanged);
    connect(ui->pushButton_co_co,             &QPushButton::clicked,                              this, &FrostbiteConsoleWidget::pushButton_co_co_clicked);
    connect(ui->lineEdit_co_co,               &QLineEdit::editingFinished,                        this, &FrostbiteConsoleWidget::pushButton_co_co_clicked);
    connect(ui->lineEdit_co_pb,               &QLineEdit::textChanged,                            this, &FrostbiteConsoleWidget::lineEdit_co_pb_textChanged);
    connect(ui->pushButton_co_pb,             &QPushButton::clicked,                              this, &FrostbiteConsoleWidget::pushButton_co_pb_clicked);
    connect(ui->lineEdit_co_pb,               &QLineEdit::editingFinished,                        this, &FrostbiteConsoleWidget::pushButton_co_pb_clicked);
}

FrostbiteConsoleWidget::FrostbiteConsoleWidget(FrostbiteClient *client, const QStringList &commandList, QWidget *parent) :
    FrostbiteConsoleWidget(client, parent)
{
    // Create completer and set commandList.
    ui->lineEdit_co_co->setCompleter(new QCompleter(commandList, this));
}

FrostbiteConsoleWidget::~FrostbiteConsoleWidget()
{
    delete ui;
}

void FrostbiteConsoleWidget::clear()
{
    ui->textEdit_co_co->clear();
    ui->textEdit_co_pb->clear();
}

void FrostbiteConsoleWidget::logConsole(int type, const QString &message)
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

/* Connection */
void FrostbiteConsoleWidget::onDisconnected()
{
    clear();

    ui->tabWidget_co->setTabEnabled(ui->tabWidget_co->indexOf(ui->tab_co_pb), false);
}

void FrostbiteConsoleWidget::onDataSent(const QString &request)
{
    logConsole(0, request);
}

void FrostbiteConsoleWidget::onDataReceived(const QString &response)
{
    logConsole(1, response);
}

/* Client */
void FrostbiteConsoleWidget::onAuthenticated()
{
    ui->tabWidget_co->setTabEnabled(ui->tabWidget_co->indexOf(ui->tab_co_pb), true);
}

/* Events */
void FrostbiteConsoleWidget::onPunkBusterMessageEvent(const QString &message)
{
    logConsole(2, message);
}

/* User Interface */
void FrostbiteConsoleWidget::lineEdit_co_co_textChanged(const QString &text)
{
    ui->pushButton_co_co->setEnabled(!text.isEmpty());
}

void FrostbiteConsoleWidget::pushButton_co_co_clicked()
{
    getClient()->getConnection()->sendCommand(ui->lineEdit_co_co->text());
    ui->lineEdit_co_co->clear();
}

void FrostbiteConsoleWidget::lineEdit_co_pb_textChanged(const QString &text)
{
    ui->pushButton_co_pb->setEnabled(!text.isEmpty());
}

void FrostbiteConsoleWidget::pushButton_co_pb_clicked()
{
    getClient()->getCommandHandler()->sendPunkBusterPbSvCommand(ui->lineEdit_co_pb->text());
    ui->lineEdit_co_pb->clear();
}
