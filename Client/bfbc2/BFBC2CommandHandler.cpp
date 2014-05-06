#include "BFBC2CommandHandler.h"

BFBC2CommandHandler::BFBC2CommandHandler(QObject *parent) : FrostbiteCommandHandler(parent)
{

}

BFBC2CommandHandler::~BFBC2CommandHandler()
{

}

void BFBC2CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    // Parse events.
    if (request == "player.onJoin") {
        parsePlayerJoinEvent(packet);
    } else if (request == "player.onAuthenticated") {
        parsePlayerAuthenticatedEvent(packet);
    } else if (request == "player.onLeave") {
        parsePlayerLeaveEvent(packet);
    } else if (request == "player.onSpawn") {
        parsePlayerSpawnEvent(packet);
    } else if (request == "player.onKill") {
        parsePlayerKillEvent(packet);
    } else if (request == "player.onChat") {
        parsePlayerChatEvent(packet);
    } else if (request == "player.onKicked") {
        parsePlayerKickedEvent(packet);
    } else if (request == "player.onSquadChange") {
        parsePlayerSquadChangeEvent(packet);
    } else if (request == "player.onTeamChange") {
        parsePlayerTeamChangeEvent(packet);
    } else if (request == "punkBuster.onMessage") {
        parsePunkBusterMessageEvent(packet);
    } else if (request == "punkBuster.onVersion") {
        parsePunkBusterVersionEvent(packet);
    } else if (request == "server.onLoadingLevel") {
        parseServerLoadingLevelEvent(packet);
    } else if (request == "server.onLevelStarted") {
        parseServerLevelStartedEvent(packet);
    } else if (request == "server.onRoundOver") {
        parseServerRoundOverEvent(packet);
    } else if (request == "server.onRoundOverPlayers") {
        parseServerRoundOverPlayersEvent(packet);
    } else if (request == "server.onRoundOverTeamScores") {
        parseServerRoundOverTeamScoresEvent(packet);
    }

    // Parse commands.
    if (request == "login.plainText") {
        parseLoginPlainTextCommand(packet);
    } else if (request == "login.hashed") {
        parseLoginHashedCommand(packet, lastSentPacket);
    } else if (request == "logout") {
        parseLogoutCommand(packet);
    } else if (request == "quit") {
        parseQuitCommand(packet);
    } else if (request == "version") {
        parseVersionCommand(packet);
    } else if (request == "listPlayers") {
        parseListPlayersCommand(packet);
    } else if (request == "eventsEnabled") {
        parseEventsEnabledCommand(packet);
    } else if (request == "help") {
        parseHelpCommand(packet);
    } else if (request == "admin.runscript") {
        parseAdminRunScriptCommand(packet);
    } else if (request == "punkBuster.pb_sv_command") {
        parsePunkBusterPbSvCommand(packet);
    } else if (request == "serverInfo") {
        parseServerInfoCommand(packet);
    } else if (request == "admin.yell") {
        parseAdminYellCommand(packet);
    } else if (request == "admin.say") {
        parseAdminSayCommand(packet);
    } else if (request == "admin.runNextRound") {
        parseAdminRunNextRoundCommand(packet);
    } else if (request == "admin.restartRound") {
        parseAdminRestartRoundCommand(packet);
    } else if (request == "admin.endRound") {
        parseAdminEndRoundCommand(packet);
    } else if (request == "admin.runNextLevel") {
        parseAdminRunNextLevelCommand(packet);
    } else if (request == "admin.restartMap") {
        parseAdminRestartMapCommand(packet);
    } else if (request == "admin.currentLevel") {
        parseAdminCurrentLevelCommand(packet);
    } else if (request == "mapList.nextLevelIndex") {
        parseMapListNextLevelIndexCommand(packet);
    } else if (request == "admin.supportedMaps") {
        parseAdminSupportedMapsCommand(packet);
    } else if (request == "admin.setPlaylist") {
        parseAdminSetPlaylistCommand(packet);
    } else if (request == "admin.getPlaylist") {
        parseAdminGetPlaylistCommand(packet);
    } else if (request == "admin.getPlaylists") {
        parseAdminGetPlaylistsCommand(packet);
    } else if (request == "admin.kickPlayer") {
        parseAdminKickPlayerCommand(packet);
    } else if (request == "admin.listPlayers") {
        parseAdminListPlayersCommand(packet);
    } else if (request == "admin.movePlayer") {
        parseAdminMovePlayerCommand(packet);
    } else if (request == "admin.killPlayer") {
        parseAdminKillPlayerCommand(packet);
    } else if (request == "vars.textChatModerationMode") {
        parseVarsTextChatModerationModeCommand(packet);
    } else if (request == "vars.textChatSpamTriggerCount") {
        parseVarsTextChatSpamTriggerCountCommand(packet);
    } else if (request == "vars.textChatSpamDetectionTime") {
        parseVarsTextChatSpamDetectionTimeCommand(packet);
    } else if (request == "vars.textChatSpamCoolDownTime") {
        parseVarsTextChatSpamCoolDownTimeCommand(packet);
    } else if (request == "textChatModerationList.load") {
        parseTextChatModerationListLoadCommand(packet);
    } else if (request == "textChatModerationList.save") {
        parseTextChatModerationListSaveCommand(packet);
    } else if (request == "textChatModerationList.add") {
        parseTextChatModerationListAddCommand(packet);
    } else if (request == "textChatModerationList.remove") {
        parseTextChatModerationListRemoveCommand(packet);
    } else if (request == "textChatModerationList.clear") {
        parseTextChatModerationListClearCommand(packet);
    } else if (request == "textChatModerationList.list") {
        parseTextChatModerationListListCommand(packet);
    } else if (request == "banList.load") {
        parseBanListLoadCommand(packet);
    } else if (request == "banList.save") {
        parseBanListSaveCommand(packet);
    } else if (request == "banList.add") {
        parseBanListAddCommand(packet);
    } else if (request == "banList.remove") {
        parseBanListRemoveCommand(packet);
    } else if (request == "banList.clear") {
        parseBanListClearCommand(packet);
    } else if (request == "banList.list") {
        parseBanListListCommand(packet);
    } else if (request == "reservedSlots.load") {
        parseReservedSlotsLoadCommand(packet);
    } else if (request == "reservedSlots.save") {
        parseReservedSlotsSaveCommand(packet);
    } else if (request == "reservedSlots.addPlayer") {
        parseReservedSlotsAddPlayerCommand(packet);
    } else if (request == "reservedSlots.removePlayer") {
        parseReservedSlotsRemovePlayerCommand(packet);
    } else if (request == "reservedSlots.clear") {
        parseReservedSlotsClearCommand(packet);
    } else if (request == "reservedSlots.list") {
        parseReservedSlotsListCommand(packet);
    } else if (request == "mapList.load") {
        parseMapListLoadCommand(packet);
    } else if (request == "mapList.save") {
        parseMapListSaveCommand(packet);
    } else if (request == "mapList.list") {
        parseMapListListCommand(packet, lastSentPacket);
    } else if (request == "mapList.clear") {
        parseMapListClearCommand(packet);
    } else if (request == "mapList.remove") {
        parseMapListRemoveCommand(packet);
    } else if (request == "mapList.append") {
        parseMapListAppendCommand(packet);
    } else if (request == "maplist mapList.insert") {
        parseMaplistInsertCommand(packet);
    } else if (request == "vars.serverName") {
        parseVarsServerNameCommand(packet);
    } else if (request == "vars.adminPassword") {
        parseVarsAdminPasswordCommand(packet);
    } else if (request == "vars.gamePassword") {
        parseVarsGamePasswordCommand(packet);
    } else if (request == "vars.punkBuster") {
        parseVarsPunkBusterCommand(packet);
    } else if (request == "vars.hardCore") {
        parseVarsHardCoreCommand(packet);
    } else if (request == "vars.ranked") {
        parseVarsRankedCommand(packet);
    } else if (request == "vars.rankLimit") {
        parseVarsRankLimitCommand(packet);
    } else if (request == "vars.teamBalance") {
        parseVarsTeamBalanceCommand(packet);
    } else if (request == "vars.friendlyFire") {
        parseVarsFriendlyFireCommand(packet);
    } else if (request == "vars.currentPlayerLimit") {
        parseVarsCurrentPlayerLimitCommand(packet);
    } else if (request == "vars.maxPlayerLimit") {
        parseVarsMaxPlayerLimitCommand(packet);
    } else if (request == "vars.playerLimit") {
        parseVarsPlayerLimitCommand(packet);
    } else if (request == "vars.bannerUrl") {
        parseVarsBannerUrlCommand(packet);
    } else if (request == "vars.serverDescription") {
        parseVarsServerDescriptionCommand(packet);
    } else if (request == "vars.killCam") {
        parseVarsKillCamCommand(packet);
    } else if (request == "vars.miniMap") {
        parseVarsMiniMapCommand(packet);
    } else if (request == "vars.crossHair") {
        parseVarsCrossHairCommand(packet);
    } else if (request == "vars.3dSpotting") {
        parseVars3dSpottingCommand(packet);
    } else if (request == "vars.miniMapSpotting") {
        parseVarsMiniMapSpottingCommand(packet);
    } else if (request == "vars.thirdPersonVehicleCameras") {
        parseVarsThirdPersonVehicleCamerasCommand(packet);
    } else if (request == "vars.teamKillCountForKick") {
        parseVarsTeamKillCountForKickCommand(packet);
    } else if (request == "vars.teamKillValueForKick") {
        parseVarsTeamKillValueForKickCommand(packet);
    } else if (request == "vars.teamKillValueIncrease") {
        parseVarsTeamKillValueIncreaseCommand(packet);
    } else if (request == "vars.teamKillValueDecreasePerSecond") {
        parseVarsTeamKillValueDecreasePerSecondCommand(packet);
    } else if (request == "vars.idleTimeout") {
        parseVarsIdleTimeoutCommand(packet);
    } else if (request == "vars.profanityFilter") {
        parseVarsProfanityFilterCommand(packet);
    } else if (request == "LevelVars.set") {
        parseLevelVarsSetCommand(packet);
    } else if (request == "LevelVars.get") {
        parseLevelVarsGetCommand(packet);
    } else if (request == "LevelVars.evaluate") {
        parseLevelVarsEvaluateCommand(packet);
    } else if (request == "LevelVars.clear") {
        parseLevelVarsClearCommand(packet);
    } else if (request == "LevelVars.list") {
        parseLevelVarsListCommand(packet);
    }
}

/* Events */
void BFBC2CommandHandler::parsePlayerJoinEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit (onPlayerJoinEvent(player));
}

void BFBC2CommandHandler::parsePlayerAuthenticatedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit (onPlayerAuthenticatedEvent(player, guid));
}

void BFBC2CommandHandler::parsePlayerLeaveEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit (onPlayerLeaveEvent(player, info));
}

void BFBC2CommandHandler::parsePlayerSpawnEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString kit = packet.getWord(2).getContent();
    QStringList weaponList;
    weaponList.append(packet.getWord(3).getContent());
    weaponList.append(packet.getWord(4).getContent());
    weaponList.append(packet.getWord(5).getContent());

    emit (onPlayerSpawnEvent(player, kit, weaponList));
}

void BFBC2CommandHandler::parsePlayerKillEvent(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = toBool(packet.getWord(4).getContent());

    emit (onPlayerKillEvent(killer, victim, weapon, headshot));
}

void BFBC2CommandHandler::parsePlayerChatEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit (onPlayerChatEvent(player, message, target));
}

void BFBC2CommandHandler::parsePlayerKickedEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString reason = packet.getWord(2).getContent();

    emit (onPlayerKickedEvent(player, reason));
}

void BFBC2CommandHandler::parsePlayerSquadChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerSquadChangeEvent(player, teamId, squadId));
}

void BFBC2CommandHandler::parsePlayerTeamChangeEvent(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = toInt(packet.getWord(2).getContent());
    int squadId = toInt(packet.getWord(3).getContent());

    emit (onPlayerTeamChangeEvent(player, teamId, squadId));
}

void BFBC2CommandHandler::parsePunkBusterMessageEvent(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit (onPunkBusterMessageEvent(message));
}

void BFBC2CommandHandler::parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet)
{
    QString version = packet.getWord(1).getContent();

    emit (onPunkBusterVersionEvent(version));
}

void BFBC2CommandHandler::parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    int roundsPlayed = toInt(packet.getWord(2).getContent());
    int roundsTotal = toInt(packet.getWord(3).getContent());

    emit (onServerLoadingLevelEvent(levelName, roundsPlayed, roundsTotal));
}

void BFBC2CommandHandler::parseServerLevelStartedEvent(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit (onServerLevelStartedEvent());
}

void BFBC2CommandHandler::parseServerRoundOverEvent(const FrostbiteRconPacket &packet)
{
    int winningTeamId = toInt(packet.getWord(1).getContent());

    emit (onServerRoundOverEvent(winningTeamId));
}

void BFBC2CommandHandler::parseServerRoundOverPlayersEvent(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit (onServerRoundOverPlayersEvent(playerInfo));
}

void BFBC2CommandHandler::parseServerRoundOverTeamScoresEvent(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit (onServerRoundOverTeamScoresEvent(teamScores));
}

/* Commands */
void BFBC2CommandHandler::parseLoginPlainTextCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLoginPlainTextCommand(tr("You have successfully logged in.")));
    }
}

/* Misc */
void BFBC2CommandHandler::parseLoginHashedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit (onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        if (response == "OK") {
            emit (onLoginHashedCommand());
        }
    }
}

void BFBC2CommandHandler::parseLogoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onLogoutCommand(tr("You are now logged out.")));
    }
}

void BFBC2CommandHandler::parseQuitCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onQuitCommand(tr("Disconnected.")));
    }
}

void BFBC2CommandHandler::parseVersionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString type = packet.getWord(1).getContent();
        int build = toInt(packet.getWord(2).getContent());

        emit (onVersionCommand(type, build));
    }
}

void BFBC2CommandHandler::parseListPlayersCommand(const FrostbiteRconPacket &packet) // TODO: Implement this.
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit (onListPlayersCommand());
    }
}

void BFBC2CommandHandler::parseEventsEnabledCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseHelpCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList helpList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            helpList.append(packet.getWord(i).getContent());
        }

        emit (onHelpCommand(helpList));
    }
}

void BFBC2CommandHandler::parseAdminRunScriptCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parsePunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

/* Query */
void BFBC2CommandHandler::parseServerInfoCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList serverInfo;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            serverInfo.append(packet.getWord(i).getContent());
        }

        emit (onServerInfoCommand(serverInfo));
    }
}

void BFBC2CommandHandler::parseAdminYellCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminSayCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminRunNextRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminRestartRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminEndRoundCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminRunNextLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminRestartMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminCurrentLevelCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListNextLevelIndexCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int index = QString(packet.getWord(1).getContent()).toInt();

        emit (onMapListNextLevelIndexCommand(index));
    }
}

void BFBC2CommandHandler::parseAdminSupportedMapsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminSetPlaylistCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminGetPlaylistCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminGetPlaylistsCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminKickPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminListPlayersCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        PlayerList playerList;
        unsigned int parameterCount = QString(packet.getWord(1).getContent()).toUInt();
        unsigned int playerCount = QString(packet.getWord(2 + parameterCount).getContent()).toUInt();

        for (unsigned int i = 0; i < playerCount; i++) {
            PlayerListItem player;

            for (unsigned int j = 0; j < parameterCount; j++) {
                player.insert(packet.getWord(2 + j).getContent(), packet.getWord(2 + parameterCount + 1 + i * parameterCount + j).getContent());
            }

            playerList.append(player);
        }

        emit (onAdminListPlayersCommand(playerList));
    }
}

void BFBC2CommandHandler::parseAdminMovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseAdminKillPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTextChatModerationModeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString mode = packet.getWord(1).getContent();
        emit (onVarsTextChatModerationModeCommand(mode));
    }
}

void BFBC2CommandHandler::parseVarsTextChatSpamTriggerCountCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamTriggerCountCommand(count));
    }
}

void BFBC2CommandHandler::parseVarsTextChatSpamDetectionTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamDetectionTimeCommand(count));
    }
}

void BFBC2CommandHandler::parseVarsTextChatSpamCoolDownTimeCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = toInt(packet.getWord(1).getContent());
        emit (onVarsTextChatSpamCoolDownTimeCommand(count));
    }
}

void BFBC2CommandHandler::parseTextChatModerationListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseTextChatModerationListListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListAddCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseBanListListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            banList.append(packet.getWord(i).getContent());
        }

        emit (onBanListListCommand(banList));
    }
}

void BFBC2CommandHandler::parseReservedSlotsLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsAddPlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsRemovePlayerCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseReservedSlotsListCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        QStringList list;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            list.append(packet.getWord(i).getContent());
        }

        emit (onReservedSlotsListCommand(list));
    }
}

void BFBC2CommandHandler::parseMapListLoadCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListSaveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) // TODO: Look over this.
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        if ((lastSentPacket.getWordCount() > 1) && (QString(lastSentPacket.getWord(1).getContent()) == "rounds")) {
            QStringList mapList;

            for (unsigned int i = 1; i < packet.getWordCount(); i = i + 2) {
                mapList << QString(packet.getWord(i).getContent()).toLower() << packet.getWord(i + 1).getContent();
            }

            //emit(onMapListListRoundsCommand(mapList));
        } else {
            QStringList mapList;

            for (unsigned int i = 1; i < packet.getWordCount(); i++) {
                mapList.append(packet.getWord(i).getContent());
            }

            emit (onMapListListCommand(mapList));
        }
    }

}

void BFBC2CommandHandler::parseMapListClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListRemoveCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMapListAppendCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseMaplistInsertCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsServerNameCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit (onVarsServerNameCommand(serverName));
    }
}

void BFBC2CommandHandler::parseVarsAdminPasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsGamePasswordCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsPunkBusterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsHardCoreCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsRankedCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsRankLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamBalanceCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsFriendlyFireCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsCurrentPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsMaxPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsPlayerLimitCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit (onVarsBannerUrlCommand(bannerUrl));
    }
}

void BFBC2CommandHandler::parseVarsServerDescriptionCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit (onVarsServerDescriptionCommand(serverDescription));
    }
}

void BFBC2CommandHandler::parseVarsKillCamCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsMiniMapCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsCrossHairCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVars3dSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsMiniMapSpottingCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsThirdPersonVehicleCamerasCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamKillCountForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamKillValueForKickCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamKillValueIncreaseCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsTeamKillValueDecreasePerSecondCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseVarsIdleTimeoutCommand(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = toInt(packet.getWord(1).getContent());

        emit (onVarsIdleTimeoutCommand(timeout));
    }
}

void BFBC2CommandHandler::parseVarsProfanityFilterCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsSetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsGetCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsEvaluateCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsClearCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::parseLevelVarsListCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
