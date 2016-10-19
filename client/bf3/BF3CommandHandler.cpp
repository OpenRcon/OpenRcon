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

#include "BF3CommandHandler.h"
#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"
#include "Frostbite2ServerInfo.h"

BF3CommandHandler::BF3CommandHandler(FrostbiteConnection *parent) : Frostbite2CommandHandler(parent)
{

}

BF3CommandHandler::~BF3CommandHandler()
{

}

bool BF3CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BF3CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responses = {
        /* Events */
        { "server.onMaxPlayerCountChange", &BF3CommandHandler::parseServerMaxPlayerCountChangeEvent },

        /* Commands */
        // Misc
        { "serverInfo",                    &BF3CommandHandler::parseServerInfoCommand },
        { "currentLevel",                  &BF3CommandHandler::parseCurrentLevelCommand },
        { "listPlayers",                   nullptr /*&BF3CommandHandler::parseListPlayersCommand*/ },

        // Admin
        { "admin.effectiveMaxPlayers",     &BF3CommandHandler::parseAdminEffectiveMaxPlayersCommand },
        { "admin.listPlayers",             nullptr /*&BF3CommandHandler::parseAdminListPlayersCommand*/ },

        // Vars
        { "vars.ranked",                   &BF3CommandHandler::parseVarsRankedCommand },
        { "vars.crossHair",                &BF3CommandHandler::parseVarsCrossHairCommand },
        { "vars.playerManDownTime",        &BF3CommandHandler::parseVarsPlayerManDownTimeCommand },
        { "vars.premiumStatus",            &BF3CommandHandler::parseVarsPremiumStatusCommand },
        { "vars.bannerUrl",                &BF3CommandHandler::parseVarsBannerUrlCommand },
        { "vars.roundsPerMap",             &BF3CommandHandler::parseVarsRoundsPerMapCommand },
        { "vars.gunMasterWeaponsPreset",   &BF3CommandHandler::parseVarsGunMasterWeaponsPresetCommand }
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
void BF3CommandHandler::sendServerInfoCommand()
{
    connection->sendCommand("serverInfo");
}

void BF3CommandHandler::sendCurrentLevelCommand()
{
    connection->sendCommand("currentLevel");
}

void BF3CommandHandler::sendListPlayersCommand(const PlayerSubsetType &playerSubsetType)
{
    if (playerSubsetType == PlayerSubsetType::All) {
        connection->sendCommand("\"listPlayers\" \"all\"");
    }
}

// Admin
void BF3CommandHandler::sendAdminEffectiveMaxPlayersCommand()
{
    connection->sendCommand("admin.effectiveMaxPlayers");
}

void BF3CommandHandler::sendAdminListPlayersCommand()
{

}

// Variables
void BF3CommandHandler::sendVarsRankedCommand()
{
    connection->sendCommand("vars.ranked");
}

void BF3CommandHandler::sendVarsRankedCommand(bool ranked)
{
    connection->sendCommand(QString("\"vars.ranked\" \"%1\"").arg(FrostbiteUtils::toString(ranked)));
}

void BF3CommandHandler::sendVarsCrossHairCommand()
{
    connection->sendCommand("vars.crossHair");
}

void BF3CommandHandler::sendVarsCrossHairCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.crossHair\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF3CommandHandler::sendVarsPlayerManDownTimeCommand(int percent)
{
    if (percent == -1) {
        connection->sendCommand("vars.playerManDownTime");
    } else {
        connection->sendCommand(QString("\"vars.playerManDownTime\" \"%1\"").arg(percent));
    }
}

void BF3CommandHandler::sendVarsPremiumStatusCommand()
{
     connection->sendCommand("vars.premiumStatus");
}

void BF3CommandHandler::sendVarsPremiumStatusCommand(bool enabled)
{
     connection->sendCommand(QString("\"vars.premiumStatus\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF3CommandHandler::sendVarsBannerUrlCommand(const QString &bannerUrl)
{
    if (bannerUrl.isEmpty()) {
        connection->sendCommand("vars.bannerUrl");
    } else {
        connection->sendCommand(QString("\"vars.bannerUrl\" \"%1\"").arg(bannerUrl));
    }
}

void BF3CommandHandler::sendVarsRoundsPerMapCommand(int rounds)
{
    if (rounds == -1) {
        connection->sendCommand("vars.roundsPerMap");
    } else {
        connection->sendCommand(QString("\"vars.roundsPerMap\" \"%1\"").arg(rounds));
    }
}

void BF3CommandHandler::sendVarsGunMasterWeaponsPresetCommand(int weaponPreset)
{
    if (weaponPreset == -1) {
        connection->sendCommand("vars.gunMasterWeaponsPreset");
    } else {
        connection->sendCommand(QString("\"vars.gunMasterWeaponsPreset\" \"%1\"").arg(weaponPreset));
    }
}

/* Parse events */
void BF3CommandHandler::parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    int count = FrostbiteUtils::toInt(packet.getWord(1).getContent());

    emit (onServerMaxPlayerCountChangeEvent(count));
}

/* Parse commands */
// Misc
void BF3CommandHandler::parseServerInfoCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
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

        bool matchMakingEnabled = FrostbiteUtils::toBool(packet.getWord(24).getContent());

        Frostbite2ServerInfo serverInfo(
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
                    matchMakingEnabled
        );

        emit (onServerInfoCommand(serverInfo));
    }
}

void BF3CommandHandler::parseCurrentLevelCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString currentLevel = packet.getWord(1).getContent();

        emit (onCurrentLevelCommand(currentLevel));
    }
}

//void BF3CommandHandler::parseListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket);
//}

// Admin
void BF3CommandHandler::parseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket)

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int effectiveMaxPlayers = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onAdminEffectiveMaxPlayersCommand(effectiveMaxPlayers));
    }
}

//void BF3CommandHandler::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
//{
//    Q_UNUSED(packet);
//    Q_UNUSED(lastSentPacket)
//}

// Vars
void BF3CommandHandler::parseVarsRankedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        bool ranked = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsRankedCommand(ranked));
    }
}

void BF3CommandHandler::parseVarsCrossHairCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsCrossHairCommand(enabled));
    }
}

void BF3CommandHandler::parseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsPlayerManDownTimeCommand(percent));
    }
}

void BF3CommandHandler::parseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsPremiumStatusCommand(enabled));
    }
}

void BF3CommandHandler::parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit (onVarsBannerUrlCommand(bannerUrl));
    }
}

void BF3CommandHandler::parseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        int rounds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundsPerMapCommand(rounds));
    }
}

void BF3CommandHandler::parseVarsGunMasterWeaponsPresetCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && lastSentPacket.getWordCount() > 1) {
        int weaponPreset = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsGunMasterWeaponsPresetCommand(weaponPreset));
    }
}
