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

#include <QString>
#include <QStringList>

#include "BF4CommandHandler.h"
#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"
#include "BF4Preset.h"
#include "BF4ServerType.h"

BF4CommandHandler::BF4CommandHandler(QObject *parent) :
    Frostbite2CommandHandler(parent)
{

}

BF4CommandHandler::~BF4CommandHandler()
{

}

bool BF4CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BF4CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responseList = {
        /* Events */
        { "player.onDisconnect",                        &BF4CommandHandler::parsePlayerDisconnectEvent },

        /* Commands */
        // Admin
        { "admin.shutdown",                             nullptr /*&BF4CommandHandler::parseAdminShutdownCommand*/ },
        { "admin.teamSwitchPlayer",                     nullptr /*&BF4CommandHandler::parseAdminTeamSwitchPlayerCommand*/ },

        // FairFight
        { "fairFight.activate",                         nullptr /*&BF4CommandHandler::parseFairFightActivateCommand*/ },
        { "fairFight.deactivate",                       nullptr /*&BF4CommandHandler::parseFairFightDeactivateCommand*/ },
        { "fairFight.isActive",                         &BF4CommandHandler::parseFairFightIsActiveCommand },

        // Spectator List
        { "spectatorList.add",                          nullptr /*&BF4CommandHandler::parseSpectatorListAddCommand*/ },
        { "spectatorList.clear",                        nullptr /*&BF4CommandHandler::parseSpectatorListClearCommand*/ },
        { "spectatorList.list",                         &BF4CommandHandler::parseSpectatorListListCommand },
        { "spectatorList.remove",                       nullptr /*&BF4CommandHandler::parseSpectatorListRemoveCommand*/ },
        { "spectatorList.save",                         nullptr /*&BF4CommandHandler::parseSpectatorListSaveCommand*/ },

        // Variables
        { "vars.alwaysAllowSpectators",                 &BF4CommandHandler::parseVarsAlwaysAllowSpectatorsCommand },
        { "vars.commander",                             &BF4CommandHandler::parseVarsCommanderCommand },
        { "vars.forceReloadWholeMags",                  &BF4CommandHandler::parseVarsForceReloadWholeMagsCommand },
        { "vars.hitIndicatorsEnabled",                  &BF4CommandHandler::parseVarsHitIndicatorsEnabledCommand },
        { "vars.maxSpectators",                         &BF4CommandHandler::parseVarsMaxSpectatorsCommand },
        { "vars.mpExperience",                          &BF4CommandHandler::parseVarsMpExperienceCommand },
        { "vars.preset",                                &BF4CommandHandler::parseVarsPresetCommand },
        { "vars.roundTimeLimit",                        &BF4CommandHandler::parseVarsRoundTimeLimitCommand },
        { "vars.roundWarmupTimeout",                    &BF4CommandHandler::parseVarsRoundWarmupTimeoutCommand },
        { "vars.serverType",                            &BF4CommandHandler::parseVarsServerTypeCommand },
        { "vars.teamFactionOverride",                   &BF4CommandHandler::parseVarsTeamFactionOverrideCommand },
        { "vars.ticketBleedRate",                       &BF4CommandHandler::parseVarsTicketBleedRateCommand },
        { "vars.roundPlayersReadyBypassTimer",          &BF4CommandHandler::parseVarsRoundPlayersReadyBypassTimerCommand },
        { "vars.roundPlayersReadyMinCount",             &BF4CommandHandler::parseVarsRoundPlayersReadyMinCountCommand },
        { "vars.roundPlayersReadyPercent",              &BF4CommandHandler::parseVarsRoundPlayersReadyPercentCommand },
        { "vars.isNoobOnlyJoin",                        nullptr /*&BF4CommandHandler::parseVarsIsNoobOnlyJoinCommand*/ },
        { "vars.serverTickTime",                        nullptr /*&BF4CommandHandler::parseVarsServerTickTimeCommand*/ },
        { "vars.idleTimeoutActiveMinPlayersPercent",    nullptr /*&BF4CommandHandler::parseVarsIdleTimeoutActiveMinPlayersPercentCommand*/ },
        { "vars.isCompetitive",                         nullptr /*&BF4CommandHandler::parseVarsIsCompetitiveCommand*/ },
        { "vars.outHighFrequency",                      nullptr /*&BF4CommandHandler::parseVarsOutHighFrequencyCommand*/ },
        { "vars.outHighFrequencyRconCap",               nullptr /*&BF4CommandHandler::parseVarsOutHighFrequencyRconCapCommand*/ },
    };

    if (responseList.contains(request)) {
        ResponseFunction response = responseList[request];

        if (response) {
            (this->*response)(packet, lastSentPacket);
        }

        return true;
    }

    return Frostbite2CommandHandler::parse(request, packet, lastSentPacket);
}

/* Send commands */
// Admin
void BF4CommandHandler::sendAdminShutdownCommand()
{
    connection->sendCommand("admin.shutDown");
}

void BF4CommandHandler::sendAdminShutdownCommand(bool graceful, int seconds)
{
    if (seconds < 0) {
        connection->sendCommand(QString("\"admin.shutDown\" \"%1\"").arg(FrostbiteUtils::toString(graceful)));
    } else {
        connection->sendCommand(QString("\"admin.shutDown\" \"%1\" \"%2\"").arg(FrostbiteUtils::toString(graceful)).arg(seconds));
    }
}

// FairFight
void BF4CommandHandler::sendFairFightActivateCommand()
{
    connection->sendCommand("fairFight.activate");
}

void BF4CommandHandler::sendFairFightDeactivateCommand()
{
    connection->sendCommand("fairfight.deactivate");
}

void BF4CommandHandler::sendFairFightIsActiveCommand()
{
    connection->sendCommand("fairFight.isActive");
}

// Spectator list
void BF4CommandHandler::sendSpectatorListAddCommand(const QString &player)
{
    connection->sendCommand(QString("\"spectatorList.add\" \"%1\"").arg(player));
    sendSpectatorListListCommand();
}

void BF4CommandHandler::sendSpectatorListClearCommand()
{
    connection->sendCommand("spectatorList.clear");
    sendSpectatorListListCommand();
}

void BF4CommandHandler::sendSpectatorListListCommand(int index)
{
    if (index < 0) {
        connection->sendCommand("spectatorList.list");
    } else {
        connection->sendCommand(QString("\"spectatorList.list\" \"%1\"").arg(index));
    }
}

void BF4CommandHandler::sendSpectatorListRemoveCommand(const QString &player)
{
    connection->sendCommand(QString("\"spectatorList.remove\" \"%1\"").arg(player));
    sendSpectatorListListCommand();
}

void BF4CommandHandler::sendSpectatorListSaveCommand()
{
    connection->sendCommand("spectatorList.save");
    sendSpectatorListListCommand();
}

// Variables
void BF4CommandHandler::sendVarsAlwaysAllowSpectatorsCommand()
{
    connection->sendCommand("vars.alwaysAllowSpectators");
}

void BF4CommandHandler::sendVarsAlwaysAllowSpectatorsCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.alwaysAllowSpectators\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsCommanderCommand()
{
    connection->sendCommand("vars.commander");
}

void BF4CommandHandler::sendVarsCommanderCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.commander\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsForceReloadWholeMagsCommand()
{
    connection->sendCommand("vars.forceReloadWholeMags");
}

void BF4CommandHandler::sendVarsForceReloadWholeMagsCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.forceReloadWholeMags\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsHitIndicatorsEnabledCommand()
{
    connection->sendCommand("vars.hitIndicatorsEnabled");
}

void BF4CommandHandler::sendVarsHitIndicatorsEnabledCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.hitIndicatorsEnabled\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF4CommandHandler::sendVarsMaxSpectatorsCommand(int spectators)
{
    if (spectators < 0) {
        connection->sendCommand("vars.maxSpectators");
    } else {
        connection->sendCommand(QString("\"vars.maxSpectators\" \"%1\"").arg(spectators));
    }
}

void BF4CommandHandler::sendVarsMpExperienceCommand(const QString &experience)
{
    if (experience.isEmpty()) {
        connection->sendCommand("vars.mpExperience");
    } else {
        connection->sendCommand(QString("\"vars.mpExperience\" \"%1\"").arg(experience));
    }
}

void BF4CommandHandler::sendVarsPresetCommand()
{
    connection->sendCommand("vars.preset");
}

void BF4CommandHandler::sendVarsPresetCommand(const BF4PresetEnum &preset, bool lockPresetSetting)
{
    connection->sendCommand(QString("\"vars.preset\" \"%1\" \"%2\"").arg(BF4Preset::toString(preset).toLower(), FrostbiteUtils::toString(lockPresetSetting)));
}

void BF4CommandHandler::sendVarsRoundTimeLimitCommand(int percent)
{
    if (percent < 0) {
        connection->sendCommand("vars.roundTimeLimit");
    } else {
        connection->sendCommand(QString("\"vars.roundTimeLimit\" \"%1\"").arg(percent));
    }
}

void BF4CommandHandler::sendVarsRoundWarmupTimeoutCommand(int timeout)
{
    if (timeout < 0) {
        connection->sendCommand("vars.roundWarmupTimeout");
    } else {
        connection->sendCommand(QString("\"vars.roundWarmupTimeout\" \"%1\"").arg(timeout));
    }
}

void BF4CommandHandler::sendVarsServerTypeCommand()
{
    connection->sendCommand("vars.serverType");
}

void BF4CommandHandler::sendVarsServerTypeCommand(const BF4ServerTypeEnum &serverType)
{
    connection->sendCommand(QString("\"vars.serverType\" \"%1\"").arg(BF4ServerType::toString(serverType)));
}

void BF4CommandHandler::sendVarsTeamFactionOverrideCommand(int teamId, int factionId)
{
    if (teamId < 0 && factionId < 0) {
        connection->sendCommand("vars.teamFactionOverride");
    } else {
        connection->sendCommand(QString("\"vars.teamFactionOverride\" \"%1\" \"%1\"").arg(teamId, factionId));
    }
}

void BF4CommandHandler::sendVarsTicketBleedRateCommand(int percent)
{
    if (percent < 0) {
        connection->sendCommand("vars.ticketBleedRate");
    } else {
        connection->sendCommand(QString("\"vars.ticketBleedRate\" \"%1\"").arg(percent));
    }
}

void BF4CommandHandler::sendVarsRoundPlayersReadyBypassTimerCommand(int time)
{
    if (time < 0) {
        connection->sendCommand("vars.roundPlayersReadyBypassTimer");
    } else {
        connection->sendCommand(QString("\"vars.roundPlayersReadyBypassTimer\" \"%1\"").arg(time));
    }
}

void BF4CommandHandler::sendVarsRoundPlayersReadyMinCountCommand(int count)
{
    if (count < 0) {
        connection->sendCommand("vars.roundPlayersReadyMinCount");
    } else {
        connection->sendCommand(QString("\"vars.roundPlayersReadyMinCount\" \"%1\"").arg(count));
    }
}

void BF4CommandHandler::sendVarsRoundPlayersReadyPercentCommand(int percent)
{
    if (percent < 0) {
        connection->sendCommand("vars.roundPlayersReadyPercent");
    } else {
        connection->sendCommand(QString("\"vars.roundPlayersReadyPercent\" \"%1\"").arg(percent));
    }
}

void BF4CommandHandler::sendVarsIsNoobOnlyJoinCommand()
{
    connection->sendCommand("vars.isNoobOnlyJoin");
}

void BF4CommandHandler::sendVarsIsNoobOnlyJoinCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.isNoobOnlyJoin\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

/* Parse events */
void BF4CommandHandler::parsePlayerDisconnectEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    if (packet.getWordCount() >= 1) {
        QString player = packet.getWord(1).getContent();

        emit (onPlayerDisconnectEvent(player));
    }
}

/* Parse commands */
// FairFight
void BF4CommandHandler::parseFairFightIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1) {
        bool isActive = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onFairFightIsActiveCommand(isActive));
    }
}

// Spectator List
void BF4CommandHandler::parseSpectatorListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1) {
        QStringList spectatorList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            spectatorList.append(packet.getWord(i).getContent());
        }

        emit (onSpectatorListListCommand(spectatorList));
    }
}

// Variables
void BF4CommandHandler::parseVarsAlwaysAllowSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsAlwaysAllowSpectatorsCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsCommanderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsCommanderCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsForceReloadWholeMagsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsForceReloadWholeMagsCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsHitIndicatorsEnabledCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsHitIndicatorsEnabledCommand(enabled));
    }
}

void BF4CommandHandler::parseVarsMaxSpectatorsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int spectatorCount = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsMaxSpectatorsCommand(spectatorCount));
    }
}

void BF4CommandHandler::parseVarsMpExperienceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        QString experience = packet.getWord(1).getContent();

        emit (onVarsMpExperienceCommand(experience));
    }
}

void BF4CommandHandler::parseVarsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
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

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int percentage = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundTimeLimitCommand(percentage));
    }
}

void BF4CommandHandler::parseVarsRoundWarmupTimeoutCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int timeout = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundWarmupTimeoutCommand(timeout));
    }
}

void BF4CommandHandler::parseVarsServerTypeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        QString serverTypeName = FrostbiteUtils::toCamelCase(packet.getWord(1).getContent());
        BF4ServerTypeEnum serverType = BF4ServerType::fromString(serverTypeName);

        emit (onVarsServerTypeCommand(serverType));
    }
}

void BF4CommandHandler::parseVarsTeamFactionOverrideCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
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

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsTicketBleedRateCommand(percent));
    }
}

void BF4CommandHandler::parseVarsRoundPlayersReadyBypassTimerCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int timer = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundPlayersReadyBypassTimerCommand(timer));
    }
}

void BF4CommandHandler::parseVarsRoundPlayersReadyMinCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundPlayersReadyMinCountCommand(count));
    }
}

void BF4CommandHandler::parseVarsRoundPlayersReadyPercentCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundPlayersReadyPercentCommand(percent));
    }
}
