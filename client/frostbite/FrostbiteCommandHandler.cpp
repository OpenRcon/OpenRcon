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

FrostbiteCommandHandler::FrostbiteCommandHandler(FrostbiteConnection *parent) : CommandHandler(parent), connection(parent)
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
        { "player.onLeave",                      &FrostbiteCommandHandler::parsePlayerLeaveEvent },
        { "player.onChat",                       &FrostbiteCommandHandler::parsePlayerChatEvent },
        { "player.onSquadChange",                &FrostbiteCommandHandler::parsePlayerSquadChangeEvent },
        { "player.onTeamChange",                 &FrostbiteCommandHandler::parsePlayerTeamChangeEvent },
        { "punkBuster.onMessage",                &FrostbiteCommandHandler::parsePunkBusterMessageEvent },
        { "server.onRoundOver",                  &FrostbiteCommandHandler::parseServerRoundOverEvent },
        { "server.onRoundOverPlayers",           &FrostbiteCommandHandler::parseServerRoundOverPlayersEvent },
        { "server.onRoundOverTeamScores",        &FrostbiteCommandHandler::parseServerRoundOverTeamScoresEvent },

        /* Commands */
        // Misc
        { "login.plainText",                     &FrostbiteCommandHandler::parseLoginPlainTextCommand },
        { "login.hashed",                        &FrostbiteCommandHandler::parseLoginHashedCommand },
        { "logout",                              &FrostbiteCommandHandler::parseLogoutCommand },
        { "quit",                                &FrostbiteCommandHandler::parseQuitCommand },
        { "version",                             &FrostbiteCommandHandler::parseVersionCommand },

        // BanList
        { "banList.add",                         nullptr /*&FrostbiteCommandHandler::parseBanListAddCommand*/ },
        { "banList.clear",                       nullptr /*&FrostbiteCommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                        &FrostbiteCommandHandler::parseBanListListCommand },
        { "banList.load",                        nullptr /*&FrostbiteCommandHandler::parseBanListLoadCommand*/ },
        { "banList.remove",                      nullptr /*&FrostbiteCommandHandler::parseBanListRemoveCommand*/ },
        { "banList.save",                        nullptr /*&FrostbiteCommandHandler::parseBanListSaveCommand*/ },

        // PunkBuster
        { "punkBuster.pb_sv_command",            nullptr /*&FrostbiteCommandHandler::parsePunkBusterPbSvCommand*/ },

        // Variables
        { "vars.3dSpotting",                     &FrostbiteCommandHandler::parseVars3dSpottingCommand },
        { "vars.friendlyFire",                   &FrostbiteCommandHandler::parseVarsFriendlyFireCommand },
        { "vars.gamePassword",                   &FrostbiteCommandHandler::parseVarsGamePasswordCommand },
        { "vars.idleTimeout",                    &FrostbiteCommandHandler::parseVarsIdleTimeoutCommand },
        { "vars.killCam",                        &FrostbiteCommandHandler::parseVarsKillCamCommand },
        { "vars.miniMap",                        &FrostbiteCommandHandler::parseVarsMiniMapCommand },
        { "vars.miniMapSpotting",                &FrostbiteCommandHandler::parseVarsMiniMapSpottingCommand },
        { "vars.serverDescription",              &FrostbiteCommandHandler::parseVarsServerDescriptionCommand },
        { "vars.serverName",                     &FrostbiteCommandHandler::parseVarsServerNameCommand },
        { "vars.teamKillCountForKick",           &FrostbiteCommandHandler::parseVarsTeamKillCountForKickCommand },
        { "vars.teamKillValueDecreasePerSecond", &FrostbiteCommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand },
        { "vars.teamKillValueForKick",           &FrostbiteCommandHandler::parseVarsTeamKillValueForKickCommand },
        { "vars.teamKillValueIncrease",          &FrostbiteCommandHandler::parseVarsTeamKillValueIncreaseCommand }
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
    connection->sendCommand(QString("\"login.plainText\" \"%1\"").arg(password));
}

void FrostbiteCommandHandler::sendLoginHashedCommand(const QByteArray &salt, const QString &password)
{
    if (salt.isNull() && password == 0) {
        connection->sendCommand("login.hashed");
    } else {
        if (!password.isEmpty() && password.length() <= 16) {
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(salt);
            hash.addData(password.toLatin1().constData());

            connection->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
        }
    }
}

void FrostbiteCommandHandler::sendLogoutCommand()
{
    connection->sendCommand("logout");
}

void FrostbiteCommandHandler::sendQuitCommand()
{
    connection->sendCommand("quit");
}

void FrostbiteCommandHandler::sendVersionCommand()
{
    connection->sendCommand("version");
}

// BanList
void FrostbiteCommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason)
{
//    banList.add <id-type: id-type> <id: string> <timeout: timeout> <reason: string>

    connection->sendCommand(QString("banList.add %1 %2 perm %4").arg(idType, id, reason));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason)
{
    QString timeoutString = useRounds ? "rounds" : "seconds";
    timeoutString += " " + QString::number(timeout);

    connection->sendCommand(QString("banList.add %1 %2 %3 %4").arg(idType, id, timeoutString, reason));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListClearCommand()
{
    connection->sendCommand("banList.clear");
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListListCommand(int index)
{
    if (index == 0) {
        connection->sendCommand("banList.list");
    } else {
        connection->sendCommand(QString("\"banList.list\" \"%1\"").arg(index));
    }
}

void FrostbiteCommandHandler::sendBanListLoadCommand()
{
    connection->sendCommand("banList.load");
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListRemoveCommand(const QString &idType, const QString &id)
{
    connection->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, id));
    sendBanListListCommand();
}

void FrostbiteCommandHandler::sendBanListSaveCommand()
{
    connection->sendCommand("banList.save");
}

// PunkBuster
void FrostbiteCommandHandler::sendPunkBusterPbSvCommand(const QString &command)
{
    connection->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
}

/* Parse events */
void FrostbiteCommandHandler::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void FrostbiteCommandHandler::parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void FrostbiteCommandHandler::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void FrostbiteCommandHandler::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());
    int squadId = FrostbiteUtils::toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void FrostbiteCommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void FrostbiteCommandHandler::parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit (onServerRoundOverEvent(winningTeamId));
}

void FrostbiteCommandHandler::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void FrostbiteCommandHandler::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
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
//void FrostbiteCommandHandler::parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void FrostbiteCommandHandler::parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

void FrostbiteCommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QList<BanListEntry> banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i += 6) {
            QString banIdType = packet.getWord(i).getContent();
            QString id = packet.getWord(i + 1).getContent();
            QString banType = packet.getWord(i + 2).getContent();
            int seconds = FrostbiteUtils::toInt(packet.getWord(i + 3).getContent());
            int rounds = FrostbiteUtils::toInt(packet.getWord(i + 4).getContent());
            QString reason = packet.getWord(i + 5).getContent();

            banList.append(BanListEntry(banIdType, id, banType, seconds, rounds, reason));
        }

        emit (onBanListListCommand(banList));
    }
}

//void FrostbiteCommandHandler::parseBanListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void FrostbiteCommandHandler::parseBanListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void FrostbiteCommandHandler::parseBanListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

// PunkBuster
//void FrostbiteCommandHandler::parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

// Variables
void FrostbiteCommandHandler::parseVars3dSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVars3dSpottingCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsFriendlyFireCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onVarsGamePasswordCommand(password));
    }
}

void FrostbiteCommandHandler::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int seconds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(seconds));
    }
}

void FrostbiteCommandHandler::parseVarsKillCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsKillCamCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsMiniMapSpottingCommand(enabled));
    }
}

void FrostbiteCommandHandler::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString description = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(description));
    }
}

void FrostbiteCommandHandler::parseVarsServerNameCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString name = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(name));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillCountForKickCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueDecreasePerSecondCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueForKickCommand(count));
    }
}

void FrostbiteCommandHandler::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTeamKillValueIncreaseCommand(count));
    }
}
