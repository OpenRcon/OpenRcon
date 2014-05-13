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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "FrostbiteCommandHandler.h"
#include "FrostbiteConnection.h"

FrostbiteCommandHandler::FrostbiteCommandHandler(FrostbiteConnection *parent) : CommandHandler(parent), con(parent)
{
    if (parent) {
        parent->setCommandHandler(this);
    }
}

FrostbiteCommandHandler::~FrostbiteCommandHandler()
{

}

bool FrostbiteCommandHandler::parse(const QString & request, const FrostbiteRconPacket & packet, const FrostbiteRconPacket & lastSentPacket)
{
    typedef void (FrostbiteCommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        { "login.plainText", &FrostbiteCommandHandler::parseLoginPlainTextCommand },
        { "login.hashed",    &FrostbiteCommandHandler::parseLoginHashedCommand },
        { "logout",          &FrostbiteCommandHandler::parseLogoutCommand },
        { "quit",            &FrostbiteCommandHandler::parseQuitCommand },
        { "version",         &FrostbiteCommandHandler::parseVersionCommand }
    };

    if (responses.contains(request)) {
        ResponseFunction res = responses[request];

        if (res) {
            (this->*res)(packet, lastSentPacket);
        }

        return true;
    }

    return false;
}

/* Send commands */
void FrostbiteCommandHandler::sendLoginPlainTextCommand(const QString &password)
{
    con->sendCommand(QString("\"login.plainText\" \"%1\"").arg(password));
}

void FrostbiteCommandHandler::sendLoginHashedCommand(const QByteArray &salt, const QString &password)
{
    if (salt.isNull() && password == 0) {
        con->sendCommand("login.hashed");
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            con->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void FrostbiteCommandHandler::sendLogoutCommand()
{
    con->sendCommand("logout");
}

void FrostbiteCommandHandler::sendQuitCommand()
{
    con->sendCommand("quit");
}

void FrostbiteCommandHandler::sendVersionCommand()
{
    con->sendCommand("version");
}

/* Parse commands */
void FrostbiteCommandHandler::parseLoginPlainTextCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLoginPlainTextCommand(true));
    } else {
        emit (onLoginPlainTextCommand(false));
    }
}

void FrostbiteCommandHandler::parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit (onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        if (response == "OK") {
            emit (onLoginHashedCommand(true));
        } else { // if (response == "InvalidPasswordHash")
            emit (onLoginHashedCommand(false));
        }
    }
}

void FrostbiteCommandHandler::parseLogoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLogoutCommand());
    }
}

void FrostbiteCommandHandler::parseQuitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onQuitCommand());
    }
}

void FrostbiteCommandHandler::parseVersionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}
