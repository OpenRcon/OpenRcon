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

#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "Frostbite2CommandHandler.h"
#include "FrostbiteUtils.h"

Frostbite2CommandHandler::Frostbite2CommandHandler(FrostbiteConnection *parent) : FrostbiteCommandHandler(parent)
{

}

Frostbite2CommandHandler::~Frostbite2CommandHandler()
{

}

bool Frostbite2CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (Frostbite2CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        /* Events */
        { "player.onAuthenticated",             &Frostbite2CommandHandler::parsePlayerAuthenticatedEvent },
        { "player.onJoin",                      &Frostbite2CommandHandler::parsePlayerJoinEvent },
        { "player.onLeave",                     &Frostbite2CommandHandler::parsePlayerLeaveEvent },
        { "player.onSpawn",                     &Frostbite2CommandHandler::parsePlayerSpawnEvent },
        { "player.onKill",                      &Frostbite2CommandHandler::parsePlayerKillEvent },
        { "player.onChat",                      &Frostbite2CommandHandler::parsePlayerChatEvent },
        { "player.onSquadChange",               &Frostbite2CommandHandler::parsePlayerSquadChangeEvent },
        { "player.onTeamChange",                &Frostbite2CommandHandler::parsePlayerTeamChangeEvent },
        { "punkBuster.onMessage",               &Frostbite2CommandHandler::parsePunkBusterMessageEvent },
        { "server.onRoundOver",                 &Frostbite2CommandHandler::parseServerRoundOverEvent },
        { "server.onRoundOverPlayers",          &Frostbite2CommandHandler::parseServerRoundOverPlayersEvent },
        { "server.onRoundOverTeamScores",       &Frostbite2CommandHandler::parseServerRoundOverTeamScoresEvent },

        /* Commands */
        // Misc

        // Admin
        { "admin.eventsEnabled",                &Frostbite2CommandHandler::parseAdminEventsEnabledCommand },
        { "admin.help",                         &Frostbite2CommandHandler::parseAdminHelpCommand },
        { "admin.kickPlayer",                   nullptr /*&Frostbite2CommandHandler::parseAdminKickPlayerCommand*/ },
        { "admin.killPlayer",                   nullptr /*&Frostbite2CommandHandler::parseAdminKillPlayerCommand*/ },
        { "admin.movePlayer",                   nullptr /*&Frostbite2CommandHandler::parseAdminMovePlayerCommand*/ },
        { "admin.password",                     &Frostbite2CommandHandler::parseAdminPasswordCommand },
        { "admin.say",                          nullptr /*&Frostbite2CommandHandler::parseAdminSayCommand*/ },
        { "admin.yell",                         nullptr /*&Frostbite2CommandHandler::parseAdminYellCommand*/ },

        // BanList
        { "banList.add",                         nullptr /*&Frostbite2CommandHandler::parseBanListAddCommand*/ },
        { "banList.clear",                       nullptr /*&Frostbite2CommandHandler::parseBanListClearCommand*/ },
        { "banList.list",                        &Frostbite2CommandHandler::parseBanListListCommand },
        { "banList.load",                        nullptr /*&Frostbite2CommandHandler::parseBanListLoadCommand*/ },
        { "banList.remove",                      nullptr /*&Frostbite2CommandHandler::parseBanListRemoveCommand*/ },
        { "banList.save",                        nullptr /*&Frostbite2CommandHandler::parseBanListSaveCommand*/ },


        // FairFight

        // MapList
        { "mapList.add",                        nullptr /*&Frostbite2CommandHandler::parseMapListAddCommand*/ },
        { "mapList.availableMaps",              &Frostbite2CommandHandler::parseMapListAvailableMapsCommand },
        { "mapList.clear",                      nullptr /*&Frostbite2CommandHandler::parseMapListClearCommand*/ },
        { "mapList.endRound",                   nullptr /*&Frostbite2CommandHandler::parseMapListEndRoundCommand*/ },
        { "mapList.getMapIndices",              &Frostbite2CommandHandler::parseMapListGetMapIndicesCommand },
        { "mapList.getRounds",                  &Frostbite2CommandHandler::parseMapListGetRoundsCommand },
        { "mapList.list",                       &Frostbite2CommandHandler::parseMapListListCommand },
        { "mapList.load",                       nullptr /*&Frostbite2CommandHandler::parseMapListLoadCommand*/ },
        { "mapList.remove",                     nullptr /*&Frostbite2CommandHandler::parseMapListRemoveCommand*/ },
        { "mapList.restartRound",               nullptr /*&Frostbite2CommandHandler::parseMapListRestartRoundCommand*/ },
        { "mapList.runNextRound",               nullptr /*&Frostbite2CommandHandler::parseMapListRunNextRoundCommand*/ },
        { "mapList.save",                       nullptr /*&Frostbite2CommandHandler::parseMapListSaveCommand*/ },
        { "mapList.setNextMapIndex",            nullptr /*&Frostbite2CommandHandler::parseMapListSetNextMapIndexCommand*/ },

        // Player
        { "player.idleDuration",                &Frostbite2CommandHandler::parsePlayerIdleDurationCommand },
        { "player.isAlive",                     &Frostbite2CommandHandler::parsePlayerIsAliveCommand },
        { "player.ping",                        &Frostbite2CommandHandler::parsePlayerPingCommand },

        // PunkBuster
        { "punkBuster.activate",                nullptr /*&Frostbite2CommandHandler::parsePunkBusterActivateCommand*/ },
        { "punkBuster.isActive",                &Frostbite2CommandHandler::parsePunkBusterIsActiveCommand },
        { "punkBuster.pb_sv_command",           nullptr /*&Frostbite2CommandHandler::parsePunkBusterPbSvCommand*/ },

        // Reserved Slots
        { "reservedSlotsList.add",              nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListAddCommand*/ },
        { "reservedSlotsList.aggressiveJoin",   &Frostbite2CommandHandler::parseReservedSlotsListAggressiveJoinCommand },
        { "reservedSlotsList.clear",            nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListClearCommand*/ },
        { "reservedSlotsList.list",             &Frostbite2CommandHandler::parseReservedSlotsListListCommand },
        { "reservedSlotsList.load",             nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListLoadCommand*/ },
        { "reservedSlotsList.remove",           nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListRemoveCommand*/ },
        { "reservedSlotsList.save",             nullptr /*&Frostbite2CommandHandler::parseReservedSlotsListSaveCommand*/ },

        // Squad
        { "squad.leader",                       &Frostbite2CommandHandler::parseSquadLeaderCommand },
        { "squad.listActive",                   nullptr /*&Frostbite2CommandHandler::parseSquadListActiveCommand*/ },
        { "squad.listPlayers",                  &Frostbite2CommandHandler::parseSquadListPlayersCommand },
        { "squad.private",                      &Frostbite2CommandHandler::parseSquadPrivateCommand }

        // Vars
    };

    if (responses.contains(request)) {
        ResponseFunction res = responses[request];

        if (res) {
            (this->*res)(packet, lastSentPacket);
        }

        return true;
    } else {
        return FrostbiteCommandHandler::parse(request, packet, lastSentPacket);
    }
}

/* Send commands */
// Admin
void Frostbite2CommandHandler::sendAdminEventsEnabledCommand(bool enabled)
{
    con->sendCommand(QString("\"admin.eventsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendAdminHelpCommand()
{
    con->sendCommand("admin.help");
}

void Frostbite2CommandHandler::sendAdminKickPlayerCommand(const QString &player, const QString &reason)
{
    con->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player, reason));
}

void Frostbite2CommandHandler::sendAdminKillPlayerCommand(const QString &player)
{
    con->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendAdminMovePlayerCommand(const QString &player, int teamId, int squadId, bool forceKill)
{
    con->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player).arg(teamId, squadId).arg(FrostbiteUtils::toString(forceKill)));
}

void Frostbite2CommandHandler::sendAdminPasswordCommand()
{
    con->sendCommand("admin.password");
}

void Frostbite2CommandHandler::sendAdminPasswordCommand(const QString &password)
{
    con->sendCommand(QString("\"admin.password\" \"%1\"").arg(password));
}

void Frostbite2CommandHandler::sendAdminSayCommand(const QString &message, const PlayerSubset &playerSubset, int parameter)
{
    if (playerSubset == PlayerSubset::All) {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(message, getPlayerSubsetString(playerSubset)));
    } else {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\" \"%3\"").arg(message, getPlayerSubsetString(playerSubset)).arg(parameter));
    }
}

void Frostbite2CommandHandler::sendAdminYellCommand(const QString &message, const PlayerSubset &playerSubset, int parameter)
{
    sendAdminYellCommand(message, 10, playerSubset, parameter);
}

void Frostbite2CommandHandler::sendAdminYellCommand(const QString &message, int duration, const PlayerSubset &playerSubset, int parameter)
{
    if (message.length() <= 256) {
        if (playerSubset == PlayerSubset::All) {
            con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(message).arg(duration).arg(getPlayerSubsetString(playerSubset)));
        } else {
            con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(message).arg(duration).arg(getPlayerSubsetString(playerSubset)).arg(parameter));
        }
    }
}

// BanList
void Frostbite2CommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, const QString &reason)
{
    con->sendCommand(QString("banList.add %1 %2 perm %4").arg(idType, id, reason));
    sendBanListListCommand();
}

void Frostbite2CommandHandler::sendBanListAddCommand(const QString &idType, const QString &id, int timeout, bool useRounds, const QString &reason)
{
    QString timeoutType = useRounds ? "rounds" : "seconds";

    con->sendCommand(QString("banList.add %1 %2 %3 %4 %5").arg(idType, id, timeoutType).arg(FrostbiteUtils::toString(timeout), reason));
    sendBanListListCommand();
}

void Frostbite2CommandHandler::sendBanListClearCommand()
{
    con->sendCommand("banList.clear");
}

void Frostbite2CommandHandler::sendBanListListCommand(int index)
{
    if (index == 0) {
        con->sendCommand("banList.list");
    } else {
        con->sendCommand(QString("\"banList.list\" \"%1\"").arg(index));
    }
}

void Frostbite2CommandHandler::sendBanListLoadCommand()
{
    con->sendCommand("banList.load");
}

void Frostbite2CommandHandler::sendBanListRemoveCommand(const QString &idType, const QString &id)
{
    con->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, id));
    sendBanListListCommand();
}

void Frostbite2CommandHandler::sendBanListSaveCommand()
{
    con->sendCommand("banList.save");
}

// Maplist
void Frostbite2CommandHandler::sendMapListAddCommand(const QString &level, const QString &gameMode, int rounds, int offSet)
{
    con->sendCommand(QString("\"mapList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(level).arg(gameMode).arg(rounds).arg(offSet));
    sendMapListListCommand();
}

void Frostbite2CommandHandler::sendMapListAvailableMapsCommand(const QString &filter)
{
    con->sendCommand(QString("\"mapList.availableMaps\" \"%1\"").arg(filter));
}

void Frostbite2CommandHandler::sendMapListClearCommand()
{
    con->sendCommand("mapList.clear");
}

void Frostbite2CommandHandler::sendMapListEndRoundCommand(int teamId)
{
    con->sendCommand(QString("\"mapList.endRound\" \"%1\"").arg(teamId));
}

void Frostbite2CommandHandler::sendMapListGetMapIndicesCommand()
{
    con->sendCommand("mapList.getMapIndices");
}

void Frostbite2CommandHandler::sendMapListGetRoundsCommand()
{
    con->sendCommand("mapList.getRounds");
}

void Frostbite2CommandHandler::sendMapListListCommand(int index)
{
    if (index == 0) {
        con->sendCommand("mapList.list");
    } else {
        con->sendCommand(QString("\"mapList.list\" \"%1\"").arg(index));
    }
}

void Frostbite2CommandHandler::sendMapListLoadCommand()
{
    con->sendCommand("mapList.load");
}

void Frostbite2CommandHandler::sendMapListRemoveCommand(int index)
{
    con->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(index));
}

void Frostbite2CommandHandler::sendMapListRestartRoundCommand()
{
    con->sendCommand("mapList.restartRound");
}

void Frostbite2CommandHandler::sendMapListRunNextRoundCommand()
{
    con->sendCommand("mapList.runNextRound");
}

void Frostbite2CommandHandler::sendMapListSaveCommand()
{
    con->sendCommand("mapList.save");
}

void Frostbite2CommandHandler::sendMapListSetNextMapIndexCommand(int index)
{
    con->sendCommand(QString("\"mapList.setNextMapIndex\" \"%1\"").arg(index));
}

// Player
void Frostbite2CommandHandler::sendPlayerIdleDurationCommand(const QString &player)
{
    con->sendCommand(QString("\"player.idleDuration\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendPlayerIsAliveCommand(const QString &player)
{
    con->sendCommand(QString("\"player.isAlive\" \"%1\"").arg(player));
}

void Frostbite2CommandHandler::sendPlayerPingCommand(const QString &player)
{
    con->sendCommand(QString("\"player.ping\" \"%1\"").arg(player));
}

// PunkBuster
void Frostbite2CommandHandler::sendPunkBusterActivateCommand()
{
    con->sendCommand("punkBuster.activate");
}

void Frostbite2CommandHandler::sendPunkBusterIsActiveCommand()
{
    con->sendCommand("punkBuster.isActive");
}

void Frostbite2CommandHandler::sendPunkBusterPbSvCommand(const QString &command)
{
    con->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
}

// Reserved Slots
void Frostbite2CommandHandler::sendReservedSlotsListAddCommand(const QString &player)
{
    con->sendCommand(QString("\"reservedSlotsList.add\" \"%1\"").arg(player));
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListAggressiveJoinCommand()
{
    con->sendCommand("reservedSlotsList.aggressiveJoin");
}

void Frostbite2CommandHandler::sendReservedSlotsListAggressiveJoinCommand(bool enabled)
{
    con->sendCommand(QString("\"reservedSlotsList.aggressiveJoin\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void Frostbite2CommandHandler::sendReservedSlotsListClearCommand()
{
    con->sendCommand("reservedSlotsList.clear");
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListListCommand()
{
    con->sendCommand("reservedSlotsList.list");
}

void Frostbite2CommandHandler::sendReservedSlotsListLoadCommand()
{
    con->sendCommand("reservedSlotsList.load");
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListRemoveCommand(const QString &player)
{
    con->sendCommand(QString("\"reservedSlotsList.remove\" \"%1\"").arg(player));
    sendReservedSlotsListListCommand();
}

void Frostbite2CommandHandler::sendReservedSlotsListSaveCommand()
{
    con->sendCommand("reservedSlotsList.save");
    sendReservedSlotsListListCommand();
}

// Squad
void Frostbite2CommandHandler::sendSquadLeaderCommand(int teamId, int squadId, const QString &player)
{
    con->sendCommand(QString("\"squad.leader\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(player));
}

void Frostbite2CommandHandler::sendSquadListActiveCommand(int teamId)
{
    con->sendCommand(QString("\"squad.listActive\" \"%1\"").arg(teamId));
}

void Frostbite2CommandHandler::sendSquadListPlayersCommand(int teamId, int squadId)
{
    con->sendCommand(QString("\"squad.listPlayers\" \"%1\" \"%2\"").arg(teamId).arg(squadId));
}

void Frostbite2CommandHandler::sendSquadPrivateCommand(int teamId, int squadId, bool isPrivate)
{
    con->sendCommand(QString("\"squad.private\" \"%1\" \"%2\" \"%3\"").arg(teamId).arg(squadId).arg(FrostbiteUtils::toString(isPrivate)));
}


/* Parse events */
void Frostbite2CommandHandler::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();

    emit (onPlayerAuthenticatedEvent(player));
}

void Frostbite2CommandHandler::parsePlayerJoinEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerJoinEvent(player, guid));
}

void Frostbite2CommandHandler::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void Frostbite2CommandHandler::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = FrostbiteUtils::toInt(packet.getWord(2).getContent());

    emit (onPlayerSpawnEvent(player, teamId));
}

void Frostbite2CommandHandler::parsePlayerKillEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void Frostbite2CommandHandler::parsePlayerChatEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void Frostbite2CommandHandler::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void Frostbite2CommandHandler::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void Frostbite2CommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void Frostbite2CommandHandler::parseServerRoundOverEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit (onServerRoundOverEvent(winningTeamId));
}

void Frostbite2CommandHandler::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void Frostbite2CommandHandler::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

/* Parse commands */
// Admin
void Frostbite2CommandHandler::parseAdminEventsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onAdminEventsEnabledCommand(enabled));
    }
}

void Frostbite2CommandHandler::parseAdminHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList commandList;

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            commandList.append(packet.getWord(i).getContent());
        }

        emit (onAdminHelpCommand(commandList));
    }
}

//void Frostbite2CommandHandler::parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void Frostbite2CommandHandler::parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void Frostbite2CommandHandler::parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString password = packet.getWord(1).getContent();

        emit (onAdminPasswordCommand(password));
    }
}

//void Frostbite2CommandHandler::parseAdminSayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseAdminYellCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

// BanList
//void Frostbite2CommandHandler::parseBanListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseBanListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        BanList banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i += 6) {
            QString idType = packet.getWord(i).getContent();
            QString id = packet.getWord(i + 1).getContent();
            QString banType = packet.getWord(i + 2).getContent();
            int seconds = toInt(packet.getWord(i + 3).getContent());
            int rounds = toInt(packet.getWord(i + 4).getContent());
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


// MapList
//void Frostbite2CommandHandler::parseMapListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString value = packet.getWord(1).getContent();
        QStringList list;

        for (unsigned int i = 2; i < packet.getWordCount(); i++) {
            list.append(packet.getWord(i).getContent());
        }

        emit (onMapListAvailableMapsCommand(value, list));
    }
}

//void Frostbite2CommandHandler::parseMapListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListEndRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentMapIndex = toInt(packet.getWord(1).getContent());
        int nextMapIndex = toInt(packet.getWord(2).getContent());

        emit (onMapListGetMapIndicesCommand(currentMapIndex, nextMapIndex));
    }
}

void Frostbite2CommandHandler::parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int currentRound = toInt(packet.getWord(1).getContent());
        int totalRounds = toInt(packet.getWord(2).getContent());

        emit (onMapListGetRoundsCommand(currentRound, totalRounds));
    }
}

void Frostbite2CommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        MapList mapList;
        int maps = QString(packet.getWord(1).getContent()).toInt();
        int parameters = QString(packet.getWord(2).getContent()).toInt();

        for (int i = 0; i < maps; i++) {
            QString level;
            QString gameMode;
            int rounds;

            for (int j = 0; j < parameters; j++) {
                QString data = packet.getWord(3 + (i * parameters) + j).getContent();

                switch (j) {
                    case 0:
                        level = data;
                        break;
                    case 1:
                        gameMode = data;
                        break;
                    case 2:
                        rounds = data.toInt();
                        break;
                }
            }

            mapList.append(MapListEntry(level, gameMode, rounds));
        }

        emit (onMapListListCommand(mapList));
    }
}

//void Frostbite2CommandHandler::parseMapListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListRestartRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListRunNextRoundCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseMapListSetNextMapIndexCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}


// Player
void Frostbite2CommandHandler::parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        float idleDuration = toFloat(packet.getWord(1).getContent());

        emit (onPlayerIdleDurationCommand(idleDuration));
    }
}

void Frostbite2CommandHandler::parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool alive = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onPlayerIsAliveCommand(alive));
    }
}

void Frostbite2CommandHandler::parsePlayerPingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 3) {
        QString player = packet.getWord(1).getContent();
        int ping = toInt(packet.getWord(2).getContent());

        emit (onPlayerPingCommand(player, ping));
    }
}

// PunkBuster
//void Frostbite2CommandHandler::parsePunkBusterActivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool active = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onPunkBusterIsActiveCommand(active));
    }
}

//void Frostbite2CommandHandler::parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

// Reserved Slots
//void Frostbite2CommandHandler::parseReservedSlotsListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 2) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onReservedSlotsListAggressiveJoinCommand(enabled));
    }
}

//void Frostbite2CommandHandler::parseReservedSlotsListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList reservedSlotList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            reservedSlotList.append(packet.getWord(i).getContent());
        }

        emit (onReservedSlotsListListCommand(reservedSlotList));
    }
}

//void Frostbite2CommandHandler::parseReservedSlotsListLoadCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseReservedSlotsListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

//void Frostbite2CommandHandler::parseReservedSlotsListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

// Squad
void Frostbite2CommandHandler::parseSquadLeaderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString player = packet.getWord(1).getContent();

        emit (onSquadLeaderCommand(player));
    }
}

//void Frostbite2CommandHandler::parseSquadListActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//}

void Frostbite2CommandHandler::parseSquadListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int playerCount = toInt(packet.getWord(1).getContent());
        QStringList playerList;

        for (int i = 2; i < playerCount; i++) {
            playerList.append(packet.getWord(i).getContent());
        }

        emit (onSquadListPlayersCommand(playerList));
    }
}

void Frostbite2CommandHandler::parseSquadPrivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isPrivate = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onSquadPrivateCommand(isPrivate));
    }
}

PlayerSubset Frostbite2CommandHandler::getPlayerSubset(const QString &playerSubsetString)
{
    PlayerSubset playerSubset;

    if (playerSubsetString == "all") {
        playerSubset = PlayerSubset::All;
    } else if (playerSubsetString == "team") {
        playerSubset = PlayerSubset::Team;
    } else if (playerSubsetString == "squad") {
        playerSubset = PlayerSubset::Squad;
    } else if (playerSubsetString == "player") {
        playerSubset = PlayerSubset::Player;
    }

    return playerSubset;
}

QString Frostbite2CommandHandler::getPlayerSubsetString(const PlayerSubset &playerSubset)
{
    QString playerSubsetString;

    switch (playerSubset) {
    case PlayerSubset::All:
        playerSubsetString = "all";
        break;

    case PlayerSubset::Team:
        playerSubsetString = "team";
        break;

    case PlayerSubset::Squad:
        playerSubsetString = "squad";
        break;

    case PlayerSubset::Player:
        playerSubsetString = "player";
        break;
    }

    return playerSubsetString;
}