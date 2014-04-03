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

#include "BF4.h"

BF4::BF4(const QString &host, const int &port, const QString &password) : BFGame(host, port, password), auth(false)
{
    con = new BF4Connection(this);
    con->hostConnect(host, port);

    // Connection
    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));

    // Commands
    connect(con->commandHandler, SIGNAL(onLoginHashedCommand(const QByteArray&)), this, SLOT(onLoginHashedCommand(const QByteArray&)));
    connect(con->commandHandler, SIGNAL(onLoginHashedCommand()), this, SLOT(onLoginHashedCommand()));
}

BF4::~BF4()
{
    delete con;
}

void BF4::onConnected()
{
    if (!isAuthenticated()) {
        con->sendCommand("login.hashed");
    }
}

void BF4::onLoginHashedCommand()
{
    auth = true;
}

void BF4::onLoginHashedCommand(const QByteArray &salt)
{
    if (!isAuthenticated()) {
        if (!password.isEmpty()) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toUtf8().constData());

            con->sendCommand(QString("login.hashed %1").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

bool BF4::isAuthenticated()
{
    return auth;
}

void BF4::sendSayMessage(const QString &msg, const QString &group)
{
    if (!group.isEmpty()) {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(msg).arg(group));
    } else {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"all\"").arg(msg));
    }
}

void BF4::sendYellMessage(const QString &message, const int &duration, const QString &group)
{
    if (!group.isEmpty()) {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(group));
    } else {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"all\"").arg(message).arg(duration));
    }
}
