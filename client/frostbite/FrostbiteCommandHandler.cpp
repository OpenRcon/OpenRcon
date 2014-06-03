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

#include <QCryptographicHash>

#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteCommandHandler.h"
#include "FrostbiteUtils.h"
#include "BanListEntry.h"

FrostbiteCommandHandler::FrostbiteCommandHandler(FrostbiteConnection *parent) : CommandHandler(parent), m_connection(parent)
{
    if (parent) {
        parent->setCommandHandler(this);
    }
}

FrostbiteCommandHandler::~FrostbiteCommandHandler()
{

}

bool FrostbiteCommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (FrostbiteCommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        /* Events */
        { "punkBuster.onMessage",     &FrostbiteCommandHandler::parsePunkBusterMessageEvent },

        /* Commands */
        // Misc
        { "login.plainText",          &FrostbiteCommandHandler::parseLoginPlainTextCommand },
        { "login.hashed",             &FrostbiteCommandHandler::parseLoginHashedCommand },
        { "logout",                   &FrostbiteCommandHandler::parseLogoutCommand },
        { "quit",                     &FrostbiteCommandHandler::parseQuitCommand },
        { "version",                  &FrostbiteCommandHandler::parseVersionCommand },

        // BanList
        { "banList.add",              nullptr /*&Frostbite2CommandHandler::parseBanListAddCommand*/ },
        { "banList.clear",            nullptr /*&Frostbite2CommandHandler::parseBanListClearCommand*/ },
        { "banList.list",             &FrostbiteCommandHandler::parseBanListListCommand },
        { "banList.load",             nullptr /*&Frostbite2CommandHandler::parseBanListLoadCommand*/ },
        { "banList.remove",           nullptr /*&Frostbite2CommandHandler::parseBanListRemoveCommand*/ },
        { "banList.save",             nullptr /*&Frostbite2CommandHandler::parseBanListSaveCommand*/ },

        // PunkBuster
        { "punkBuster.pb_sv_command", nullptr /*&Frostbite2CommandHandler::parsePunkBusterPbSvCommand*/ }
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
// Misc
void FrostbiteCommandHandler::sendLoginPlainTextCommand(const QString &password)
{
    m_connection->sendCommand(QString("\"login.plainText\" \"%1\"").arg(password));
}

void FrostbiteCommandHandler::sendLoginHashedCommand(const QByteArray &salt, const QString &password)
{
    if (salt.isNull() && password == 0) {
        m_connection->sendCommand("login.hashed");
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            m_connection->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void FrostbiteCommandHandler::sendLogoutCommand()
{
    m_connection->sendCommand("logout");
}

void FrostbiteCommandHandler::sendQuitCommand()
{
    m_connection->sendCommand("quit");
}

void FrostbiteCommandHandler::sendVersionCommand()
{
    m_connection->sendCommand("version");
}

// BanList
void FrostbiteCommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason)
{
    m_connection->sendCommand(QString("banList.add %1 %2 perm %4").arg(idType, id, reason));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason)
{
    QString timeoutType = useRounds ? "rounds" : "seconds";

    m_connection->sendCommand(QString("banList.add %1 %2 %3 %4 %5").arg(idType, id, timeoutType).arg(FrostbiteUtils::toString(timeout), reason));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListClearCommand()
{
    m_connection->sendCommand("banList.clear");
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListListCommand(int index)
{
    if (index == 0) {
        m_connection->sendCommand("banList.list");
    } else {
        m_connection->sendCommand(QString("\"banList.list\" \"%1\"").arg(index));
    }
}

void FrostbiteCommandHandler::sendBanListLoadCommand()
{
    m_connection->sendCommand("banList.load");
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListRemoveCommand(const QString &idType, const QString &id)
{
    m_connection->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, id));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListSaveCommand()
{
    m_connection->sendCommand("banList.save");
}

// PunkBuster
void FrostbiteCommandHandler::sendPunkBusterPbSvCommand(const QString &command)
{
    m_connection->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
}

/* Parse events */
void FrostbiteCommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

/* Parse commands */
// Misc
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
        int build = FrostbiteUtils::toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

// BanList
//void Frostbite2CommandHandler::parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void FrostbiteCommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QList<BanListEntry> banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i += 6) {
            QString idType = packet.getWord(i).getContent();
            QString id = packet.getWord(i + 1).getContent();
            QString banType = packet.getWord(i + 2).getContent();
            int seconds = FrostbiteUtils::toInt(packet.getWord(i + 3).getContent());
            int rounds = FrostbiteUtils::toInt(packet.getWord(i + 4).getContent());
            QString reason = packet.getWord(i + 5).getContent();

            banList.append(BanListEntry(idType, id, banType, seconds, rounds, reason));
        }

        emit (onBanListListCommand(banList));
    }
}

//void Frostbite2CommandHandler::parseBanListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseBanListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseBanListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

// PunkBuster
//void FrostbiteCommandHandler::parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}
