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

#include "BF4CommandHandler.h"
#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"
#include "TeamScores.h"
#include "OnlineState.h"
#include "BF4ServerInfo.h"
#include "PlayerInfo.h"
#include "BF4Preset.h"

BF4CommandHandler::BF4CommandHandler(FrostbiteConnection *parent) : Frostbite2CommandHandler(parent)
{

}

BF4CommandHandler::~BF4CommandHandler()
{

}

bool BF4CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BF4CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        /* Events */
        { "player.onDisconnect",               &BF4CommandHandler::parsePlayerDisconnectEvent },

        /* Commands */
        // Misc
        { "serverInfo",                        &BF4CommandHandler::parseServerInfoCommand },
        { "currentLevel",                      &BF4CommandHandler::parseCurrentLevelCommand },
        { "listPlayers",                       &BF4CommandHandler::parseListPlayersCommand },

        // Admin
        { "admin.listPlayers",                 &BF4CommandHandler::parseAdminListPlayersCommand },
        { "admin.shutDown",                    nullptr /*&BF4CommandHandler::parseAdminShutDownCommand*/ },

        // FairFight
        { "fairFight.activate",                nullptr /*&BF4CommandHandler::parseFairFightActivateCommand*/ },
        { "fairFight.deactivate",              nullptr /*&BF4CommandHandler::parseFairFightDeactivateCommand*/ },
        { "fairFight.isActive",                &BF4CommandHandler::parseFairFightIsActiveCommand },

        // Spectator List
        { "spectatorList.add",                 nullptr /*&BF4CommandHandler::parseSpectatorListAddCommand*/ },
        { "spectatorList.clear",               nullptr /*&BF4CommandHandler::parseSpectatorListClearCommand*/ },
        { "spectatorList.list",                &BF4CommandHandler::parseSpectatorListListCommand },
        { "spectatorList.remove",              nullptr /*&BF4CommandHandler::parseSpectatorListRemoveCommand*/ },
        { "spectatorList.save",                nullptr /*&BF4CommandHandler::parseSpectatorListSaveCommand*/ },

        // Variables
        { "vars.alwaysAllowSpectators",        &BF4CommandHandler::parseVarsAlwaysAllowSpectatorsCommand },
        { "vars.commander",                    &BF4CommandHandler::parseVarsCommanderCommand },
        { "vars.forceReloadWholeMags",         &BF4CommandHandler::parseVarsForceReloadWholeMagsCommand },
        { "vars.hitIndicatorsEnabled",         &BF4CommandHandler::parseVarsHitIndicatorsEnabledCommand },
        { "vars.maxSpectators",                &BF4CommandHandler::parseVarsMaxSpectatorsCommand },
        { "vars.mpExperience",                 &BF4CommandHandler::parseVarsMpExperienceCommand },
        { "vars.preset",                       &BF4CommandHandler::parseVarsPresetCommand },
        { "vars.roundTimeLimit",               &BF4CommandHandler::parseVarsRoundTimeLimitCommand },
        { "vars.roundWarmupTimeout",           &BF4CommandHandler::parseVarsRoundWarmupTimeoutCommand },
        { "vars.serverType",                   &BF4CommandHandler::parseVarsServerTypeCommand },
        { "vars.teamFactionOverride",          &BF4CommandHandler::parseVarsTeamFactionOverrideCommand },
        { "vars.ticketBleedRate",              &BF4CommandHandler::parseVarsTicketBleedRateCommand },
        { "vars.roundPlayersReadyBypassTimer", &BF4CommandHandler::parseVarsRoundPlayersReadyBypassTimerCommand },
        { "vars.roundPlayersReadyMinCount",    &BF4CommandHandler::parseVarsRoundPlayersReadyMinCountCommand },
        { "vars.roundPlayersReadyPercent",     &BF4CommandHandler::parseVarsRoundPlayersReadyPercentCommand }
    };

    if (responses.contains(request)) {
        ResponseFunction res = responses[request];

        if (res) {
            (this->*res)(packet, lastSentPacket);
        }

        return true;
    } else {
        return Frostbite2CommandHandler::parse(request, packet, lastSentPacket);
    }
}

/* Send commands */
// Misc
void BF4CommandHandler::sendServerInfoCommand()
{
    m_connection->sendCommand("serverInfo");
}

void BF4CommandHandler::sendCurrentLevelCommand()
{
    m_connection->sendCommand("currentLevel");
}

void BF4CommandHandler::sendListPlayersCommand(const PlayerSubsetType &playerSubsetType)
{
    if (playerSubsetType == PlayerSubsetType::All) {
        m_connection->sendCommand("\"listPlayers\" \"all\"");
    }
}

// Admin
void BF4CommandHandler::sendAdminListPlayersCommand(const PlayerSubsetType &playerSubsetType)
{
    if (playerSubsetType == PlayerSubsetType::All) {
        m_connection->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    }
}

void BF4CommandHandler::sendAdminShutdownCommand()
{
    m_connection->sendCommand("admin.shutDown");
}

void BF4CommandHandler::sendAdminShutdownCommand(bool graceful)
{
    m_connection->sendCommand(QString("\"admin.shutDown\" \"%1\"").arg(FrostbiteUtils::toString(graceful)));
}

void BF4CommandHandler::sendAdminShutdownCommand(bool graceful, int seconds)
{
    m_connection->sendCommand(QString("\"admin.shutDown\" \"%1\" \"%2\"").arg(FrostbiteUtils::toString(graceful)).arg(seconds));
}

// FairFight
void BF4CommandHandler::sendFairFightActivateCommand()
{
    m_connection->sendCommand("fairFight.activate");
}

void BF4CommandHandler::sendFairFightDeactivateCommand()
{
    m_connection->sendCommand("fairfight.deactivate");
}

void BF4CommandHandler::sendFairFightIsActiveCommand()
{
    m_connection->sendCommand("fairFight.isActive");
}

// Spectator list
void BF4CommandHandler::sendSpectatorListAddCommand(const QString &player)
{
    m_connection->sendCommand(QString("\"spectatorList.add\" \"%1\"").arg(player));
    sendSpectatorListListCommand();
}

void BF4CommandHandler::sendSpectatorListClearCommand()
{
    m_connection->sendCommand("spectatorList.clear");
    sendSpectatorListListCommand();
}

void BF4CommandHandler::sendSpectatorListListCommand(int index)
{
    if (index == 0) {
        m_connection->sendCommand("spectatorList.list");
    } else {
        m_connection->sendCommand(QString("\"spectatorList.list\" \"%1\"").arg(index));
    }
}

void BF4CommandHandler::sendSpectatorListRemoveCommand(const QString &player)
{
    m_connection->sendCommand(QString("\"spectatorList.remove\" \"%1\"").arg(player));
    sendSpectatorListListCommand();
}

void BF4CommandHandler::sendSpectatorListSaveCommand()
{
    m_connection->sendCommand("spectatorList.save");
    sendSpectatorListListCommand();
}

// Variables
void BF4CommandHandler::sendVarsAlwaysAllowSpectatorsCommand()
{
    m_connection->sendCommand("vars.alwaysAllowSpectators");
}

void BF4CommandHandler::sendVarsAlwaysAllowSpectatorsCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.alwaysAllowSpectators\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsCommanderCommand()
{
    m_connection->sendCommand("vars.commander");
}

void BF4CommandHandler::sendVarsCommanderCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.commander\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsForceReloadWholeMagsCommand()
{
    m_connection->sendCommand("vars.forceReloadWholeMags");
}

void BF4CommandHandler::sendVarsForceReloadWholeMagsCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.forceReloadWholeMags\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsHitIndicatorsEnabledCommand()
{
    m_connection->sendCommand("vars.hitIndicatorsEnabled");
}

void BF4CommandHandler::sendVarsHitIndicatorsEnabledCommand(bool enabled)
{
    m_connection->sendCommand(QString("\"vars.hitIndicatorsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsMaxSpectatorsCommand(int spectators)
{
    if (spectators == -1) {
        m_connection->sendCommand("vars.maxSpectators");
    } else {
        m_connection->sendCommand(QString("\"vars.maxSpectators\" \"%1\"").arg(spectators));
    }
}

void BF4CommandHandler::sendVarsMpExperienceCommand(const QString &experience)
{
    if (experience.isEmpty()) {
        m_connection->sendCommand("vars.mpExperience");
    } else {
        m_connection->sendCommand(QString("\"vars.mpExperience\" \"%1\"").arg(experience));
    }
}

void BF4CommandHandler::sendVarsPresetCommand(const QString &serverPreset, bool lockPresetSetting)
{
    if (serverPreset.isEmpty() && lockPresetSetting == 0) {
        m_connection->sendCommand("vars.preset");
    } else {
        m_connection->sendCommand(QString("\"vars.preset\" \"%1\" \"%2\"").arg(serverPreset, FrostbiteUtils::toString(lockPresetSetting)));
    }
}

void BF4CommandHandler::sendVarsRoundTimeLimitCommand(int percent)
{
    if (percent == -1) {
        m_connection->sendCommand("vars.roundTimeLimit");
    } else {
        m_connection->sendCommand(QString("\"vars.roundTimeLimit\" \"%1\"").arg(percent));
    }
}

void BF4CommandHandler::sendVarsRoundWarmupTimeoutCommand(int timeout)
{
    if (timeout == -1) {
        m_connection->sendCommand("vars.roundWarmupTimeout");
    } else {
        m_connection->sendCommand(QString("\"vars.roundWarmupTimeout\" \"%1\"").arg(timeout));
    }
}

void BF4CommandHandler::sendVarsServerTypeCommand(const QString &type)
{
    if (type.isEmpty()) {
        m_connection->sendCommand("vars.serverType");
    } else {
        m_connection->sendCommand(QString("\"vars.serverType\" \"%1\"").arg(type));
    }
}

void BF4CommandHandler::sendVarsTeamFactionOverrideCommand(int teamId, int factionId)
{
    if (teamId == -1 && factionId == -1) {
        m_connection->sendCommand("vars.teamFactionOverride");
    } else {
        m_connection->sendCommand(QString("\"vars.teamFactionOverride\" \"%1\" \"%1\"").arg(teamId, factionId));
    }
}

void BF4CommandHandler::sendVarsTicketBleedRateCommand(int percent)
{
    if (percent == -1) {
        m_connection->sendCommand("vars.ticketBleedRate");
    } else {
        m_connection->sendCommand(QString("\"vars.ticketBleedRate\" \"%1\"").arg(percent));
    }
}

void BF4CommandHandler::sendVarsRoundPlayersReadyBypassTimerCommand(int timer)
{
    if (timer == -1) {
        m_connection->sendCommand("vars.roundPlayersReadyBypassTimer");
    } else {
        m_connection->sendCommand(QString("\"vars.roundPlayersReadyBypassTimer\" \"%1\"").arg(timer));
    }
}

void BF4CommandHandler::sendVarsRoundPlayersReadyMinCountCommand(int count)
{
    if (count == -1) {
        m_connection->sendCommand("vars.roundPlayersReadyMinCount");
    } else {
        m_connection->sendCommand(QString("\"vars.roundPlayersReadyMinCount\" \"%1\"").arg(count));
    }
}

void BF4CommandHandler::sendVarsRoundPlayersReadyPercentCommand(int percent)
{
    if (percent == -1) {
        m_connection->sendCommand("vars.roundPlayersReadyPercent");
    } else {
        m_connection->sendCommand(QString("\"vars.roundPlayersReadyPercent\" \"%1\"").arg(percent));
    }
}

/* Parse events */
void BF4CommandHandler::parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString player = packet.getWord(1).getContent();

    emit (onPlayerDisconnectEvent(player));
}

/* Parse commands */
void BF4CommandHandler::parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();
        int playerCount = FrostbiteUtils::toInt(packet.getWord(2).getContent());
        int maxPlayerCount = FrostbiteUtils::toInt(packet.getWord(3).getContent());
        QString gamemode = packet.getWord(4).getContent();
        QString currentMap = packet.getWord(5).getContent();
        int roundsPlayed = FrostbiteUtils::toInt(packet.getWord(6).getContent());
        int roundsTotal = FrostbiteUtils::toInt(packet.getWord(7).getContent());

        // Parsing team scores.
        int entries = FrostbiteUtils::toInt(packet.getWord(8).getContent());
        QList<int> scoreList;
        int targetScore;

        for (int i = 9; i < entries; i++) {
            scoreList.append(FrostbiteUtils::toInt(packet.getWord(i).getContent()));

            if (i == entries) {
                targetScore = FrostbiteUtils::toInt(packet.getWord(i + 1).getContent());
            }
        }

        TeamScores scores(scoreList, targetScore);

        // Parsing online state.
        QString onlineStateString = packet.getWord(12).getContent();
        OnlineState onlineState;

        if (onlineStateString == "NotConnected") {
            onlineState = OnlineState::NotConnected;
        } else if (onlineStateString == "ConnectedToBackend") {
            onlineState = OnlineState::ConnectedToBackend;
        } else if (onlineStateString == "AcceptingPlayers") {
            onlineState = OnlineState::AcceptingPlayers;
        }

        bool ranked = FrostbiteUtils::toBool(packet.getWord(13).getContent());
        bool punkBuster = FrostbiteUtils::toBool(packet.getWord(14).getContent());
        bool hasGamePassword = FrostbiteUtils::toBool(packet.getWord(15).getContent());
        int serverUpTime = FrostbiteUtils::toInt(packet.getWord(16).getContent());
        int roundTime = FrostbiteUtils::toInt(packet.getWord(17).getContent());
        QString gameIpAndPort = packet.getWord(18).getContent();
        QString punkBusterVersion = packet.getWord(19).getContent();
        bool joinQueueEnabled = FrostbiteUtils::toBool(packet.getWord(20).getContent());
        QString region = packet.getWord(21).getContent();
        QString closestPingSite = packet.getWord(22).getContent();
        QString country = packet.getWord(23).getContent();

        bool matchMakingEnabled = FrostbiteUtils::toBool(packet.getWord(21).getContent());
        int blazePlayerCount = FrostbiteUtils::toInt(packet.getWord(22).getContent());
        QString blazeGameState = packet.getWord(23).getContent();

        BF4ServerInfo serverInfo(
                    serverName,
                    playerCount,
                    maxPlayerCount,
                    gamemode,
                    currentMap,
                    roundsPlayed,
                    roundsTotal,
                    scores,
                    onlineState,
                    ranked,
                    punkBuster,
                    hasGamePassword,
                    serverUpTime,
                    roundTime,
                    gameIpAndPort,
                    punkBusterVersion,
                    joinQueueEnabled,
                    region,
                    closestPingSite,
                    country,
                    matchMakingEnabled,
                    blazePlayerCount,
                    blazeGameState
        );

        emit (onServerInfoCommand(serverInfo));
    }
}

void BF4CommandHandler::parseCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString level = packet.getWord(1).getContent();

        emit (onCurrentLevelCommand(level));
    }
}

void BF4CommandHandler::parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QList<PlayerInfo> playerList = parsePlayerList(packet, lastSentPacket);
    PlayerSubsetType playerSubsetType = PlayerSubset::fromString(lastSentPacket.getWord(1).getContent());

    emit (onListPlayersCommand(playerList, playerSubsetType));
}

void BF4CommandHandler::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QList<PlayerInfo> playerList = parsePlayerList(packet, lastSentPacket);
    PlayerSubsetType playerSubsetType = PlayerSubset::fromString(lastSentPacket.getWord(1).getContent());

    emit (onAdminListPlayersCommand(playerList, playerSubsetType));
}

//void BF4CommandHandler::parseAdminShutDownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

// FairFight
//void BF4CommandHandler::parseFairFightActivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void BF4CommandHandler::parseFairFightDeactivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

void BF4CommandHandler::parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool isActive = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onFairFightIsActiveCommand(isActive));
    }
}

// Spectator List
//void BF4CommandHandler::parseSpectatorListAddCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void BF4CommandHandler::parseSpectatorListClearCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

void BF4CommandHandler::parseSpectatorListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList spectatorList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            spectatorList.append(packet.getWord(i).getContent());
        }

        emit (onSpectatorListListCommand(spectatorList));
    }
}

//void BF4CommandHandler::parseSpectatorListRemoveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

//void BF4CommandHandler::parseSpectatorListSaveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

// Variables
void BF4CommandHandler::parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsAlwaysAllowSpectatorsCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsCommanderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsCommanderCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsForceReloadWholeMagsCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsHitIndicatorsEnabledCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int spectatorCount = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsMaxSpectatorsCommand(spectatorCount));
    }
}

void BF4CommandHandler::parseVarsMpExperienceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString experience = packet.getWord(1).getContent();

        emit (onVarsMpExperienceCommand(experience));
    }
}

void BF4CommandHandler::parseVarsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverPreset = QString(packet.getWord(1).getContent()).toLower();
        serverPreset.replace(0, 1, serverPreset[0].toUpper());

        bool lockPresetSetting = FrostbiteUtils::toBool(packet.getWord(2).getContent());

        emit (onVarsPresetCommand(BF4Preset::fromString(serverPreset), lockPresetSetting));
    }
}

void BF4CommandHandler::parseVarsRoundTimeLimitCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percentage = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundTimeLimitCommand(percentage));
    }
}

void BF4CommandHandler::parseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundWarmupTimeoutCommand(timeout));
    }
}

void BF4CommandHandler::parseVarsServerTypeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();

        emit (onVarsServerTypeCommand(type));
    }
}

void BF4CommandHandler::parseVarsTeamFactionOverrideCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int team1 = FrostbiteUtils::toInt(packet.getWord(1).getContent());
        int team2 = FrostbiteUtils::toInt(packet.getWord(2).getContent());
        int team3 = FrostbiteUtils::toInt(packet.getWord(3).getContent());
        int team4 = FrostbiteUtils::toInt(packet.getWord(4).getContent());

        emit (onVarsTeamFactionOverrideCommand(team1, team2, team3, team4));
    }
}

void BF4CommandHandler::parseVarsTicketBleedRateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTicketBleedRateCommand(percent));
    }
}

void BF4CommandHandler::parseVarsRoundPlayersReadyBypassTimerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timer = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundPlayersReadyBypassTimerCommand(timer));
    }
}

void BF4CommandHandler::parseVarsRoundPlayersReadyMinCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundPlayersReadyMinCountCommand(count));
    }
}

void BF4CommandHandler::parseVarsRoundPlayersReadyPercentCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundPlayersReadyPercentCommand(percent));
    }
}

QList<PlayerInfo> BF4CommandHandler::parsePlayerList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();
    QList<PlayerInfo> playerList;

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        int parameters = QString(packet.getWord(1).getContent()).toInt();
        int players = QString(packet.getWord(2 + parameters).getContent()).toInt();

        for (int i = 0; i < players; i++) {
            QStringList list;

            for (int j = 0; j < parameters; j++) {
                list.append(packet.getWord(2 + parameters + 1 + i * parameters + j).getContent());
            }

            QString name = list.at(0);
            QString guid = list.at(1);
            int teamId = FrostbiteUtils::toInt(list.at(2));
            int squadId = FrostbiteUtils::toInt(list.at(3));
            int kills = FrostbiteUtils::toInt(list.at(4));
            int deaths = FrostbiteUtils::toInt(list.at(5));
            int score = FrostbiteUtils::toInt(list.at(6));
            int rank = FrostbiteUtils::toInt(list.at(7));
            int ping = FrostbiteUtils::toInt(list.at(8));

            playerList.append(PlayerInfo(name, guid, teamId, squadId, kills, deaths, score, rank, ping));
        }
    }

    return playerList;
}
