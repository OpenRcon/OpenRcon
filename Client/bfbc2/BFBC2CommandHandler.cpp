#include "BFBC2CommandHandler.h"

BFBC2CommandHandler::BFBC2CommandHandler(QObject *parent) : QObject(parent)
{

}

BFBC2CommandHandler::~BFBC2CommandHandler()
{

}

void BFBC2CommandHandler::exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &playerList)
{
	// Parse and call events.
	if (command == "player.onJoin") {
		eventOnPlayerJoin(packet);
	} else if (command == "player.onAuthenticated") {
	    eventOnPlayerAuthenticated(packet);
	} else if (command == "player.onLeave") {
	    eventOnPlayerLeave(packet);
	} else if (command == "player.onSpawn") { 
	    eventOnPlayerSpawn(packet);
	} else if (command == "player.onKill") {
	    eventOnPlayerKill(packet);
	} else if (command == "player.onChat") {
	    eventOnPlayerChat(packet);
	} else if (command == "player.onKicked") {
	    eventOnPlayerKicked(packet);
	} else if (command == "player.onSquadChange") {
	    eventOnPlayerSquadChange(packet);
	} else if (command == "player.onTeamChange") {
	    eventOnPlayerTeamChange(packet);
	} else if (command == "punkBuster.onMessage") {
	    eventOnPunkBusterMessage(packet);
	} else if (command == "punkBuster.onVersion") {
	    eventOnPunkBusterVersion(packet);
	} else if (command == "server.onLoadingLevel") {
	    eventOnServerLoadingLevel(packet);
	} else if (command == "server.onLevelStarted") {
        eventOnServerLevelStarted(packet);
	} else if (command == "server.onRoundOver") {
        eventOnServerRoundOver(packet);
	} else if (command == "server.onRoundOverPlayers") {
        eventOnServerRoundOverPlayers(packet);
	} else if (command == "server.onRoundOverTeamScores") {
        eventOnServerRoundOverTeamScores(packet);
	}
	
	// Parse and call commands.
    if (command == "login.plainText") {
		commandLoginPlainText(packet);
    } else if (command == "login.hashed") {
		commandLoginHashed(packet, lastSentPacket);
    } else if (command == "logout") {
		commandLogout(packet);
    } else if (command == "quit") {
		commandQuit(packet);
    } else if (command == "version") {
		commandVersion(packet);
    } else if (command == "listPlayers") {
		commandListPlayers(packet);
    } else if (command == "eventsEnabled") {
		commandEventsEnabled(packet);
    } else if (command == "help") {
		commandHelp(packet);
    } else if (command == "admin.runscript") {
        commandAdminRunScript(packet);
    } else if (command == "punkBuster.pb_sv_command") {
		commandPunkBusterPbSvCommand(packet);
    } else if (command == "serverInfo") {
		commandServerInfo(packet);
    } else if (command == "admin.yell") {
		commandAdminYell(packet);
    } else if (command == "admin.say") {
		commandAdminSay(packet);
    } else if (command == "admin.runNextRound") {
		commandAdminRunNextRound(packet);
    } else if (command == "admin.restartRound") {
		commandAdminRestartRound(packet);
    } else if (command == "admin.endRound") {
		commandAdminEndRound(packet);
    } else if (command == "admin.runNextLevel") {
		commandAdminRunNextLevel(packet);
    } else if (command == "admin.restartMap") {
		commandAdminRestartMap(packet);
    } else if (command == "admin.currentLevel") {
		commandAdminCurrentLevel(packet);
    } else if (command == "mapList.nextLevelIndex") {
		commandMapListNextLevelIndex(packet);
    } else if (command == "admin.supportedMaps") {
		commandAdminSupportedMaps(packet);
    } else if (command == "admin.setPlaylist") {
		commandAdminSetPlaylist(packet);
    } else if (command == "admin.getPlaylist") {
		commandAdminGetPlaylist(packet);
    } else if (command == "admin.getPlaylists") {
		commandAdminGetPlaylists(packet);
    } else if (command == "admin.kickPlayer") {
		commandAdminKickPlayer(packet);
    } else if (command == "admin.listPlayers") {
        commandAdminListPlayers(packet, lastSentPacket, playerList);
    } else if (command == "admin.movePlayer") {
		commandAdminMovePlayer(packet);
    } else if (command == "admin.killPlayer") {
		commandAdminKillPlayer(packet);
    } else if (command == "vars.textChatModerationMode") {
		commandVarsTextChatModerationMode(packet);
    } else if (command == "vars.textChatSpamTriggerCount") {
		commandVarsTextChatSpamTriggerCount(packet);
    } else if (command == "vars.textChatSpamDetectionTime") {
		commandVarsTextChatSpamDetectionTime(packet);
    } else if (command == "vars.textChatSpamCoolDownTime") {
		commandVarsTextChatSpamCoolDownTime(packet);
    } else if (command == "textChatModerationList.load") {
		commandTextChatModerationListLoad(packet);
    } else if (command == "textChatModerationList.save") {
		commandTextChatModerationListSave(packet);
    } else if (command == "textChatModerationList.add") {
		commandTextChatModerationListAdd(packet);
    } else if (command == "textChatModerationList.remove") {
		commandTextChatModerationListRemove(packet);
    } else if (command == "textChatModerationList.clear") {
		commandTextChatModerationListClear(packet);
    } else if (command == "textChatModerationList.list") {
		commandTextChatModerationListList(packet);
    } else if (command == "banList.load") {
		commandBanListLoad(packet);
    } else if (command == "banList.save") {
		commandBanListSave(packet);
    } else if (command == "banList.add") {
		commandBanListAdd(packet);
    } else if (command == "banList.remove") {
		commandBanListRemove(packet);
    } else if (command == "banList.clear") {
		commandBanListClear(packet);
    } else if (command == "banList.list") {
		commandBanListList(packet);
    } else if (command == "reservedSlots.load") {
		commandReservedSlotsLoad(packet);
    } else if (command == "reservedSlots.save") {
		commandReservedSlotsSave(packet);
    } else if (command == "reservedSlots.addPlayer") {
		commandReservedSlotsAddPlayer(packet);
    } else if (command == "reservedSlots.removePlayer") {
		commandReservedSlotsRemovePlayer(packet);
    } else if (command == "reservedSlots.clear") {
		commandReservedSlotsClear(packet);
    } else if (command == "reservedSlots.list") {
		commandReservedSlotsList(packet);
    } else if (command == "mapList.load") {
		commandMapListLoad(packet);
    } else if (command == "mapList.save") {
		commandMapListSave(packet);
    } else if (command == "mapList.list") {
		commandMapListList(packet, lastSentPacket);
    } else if (command == "mapList.clear") {
		commandMapListClear(packet);
    } else if (command == "mapList.remove") {
		commandMapListRemove(packet);
    } else if (command == "mapList.append") {
		commandMapListAppend(packet);
    } else if (command == "maplist mapList.insert") {
		commandMaplistInsert(packet);
    } else if (command == "vars.serverName") {
		commandVarsServerName(packet);
    } else if (command == "vars.adminPassword") {
		commandVarsAdminPassword(packet);
    } else if (command == "vars.gamePassword") {
		commandVarsGamePassword(packet);
    } else if (command == "vars.punkBuster") {
		commandVarsPunkBuster(packet);
    } else if (command == "vars.hardCore") {
		commandVarsHardCore(packet);
    } else if (command == "vars.ranked") {
		commandVarsRanked(packet);
    } else if (command == "vars.rankLimit") {
		commandVarsRankLimit(packet);
    } else if (command == "vars.teamBalance") {
		commandVarsTeamBalance(packet);
    } else if (command == "vars.friendlyFire") {
		commandVarsFriendlyFire(packet);
    } else if (command == "vars.currentPlayerLimit") {
		commandVarsCurrentPlayerLimit(packet);
    } else if (command == "vars.maxPlayerLimit") {
		commandVarsMaxPlayerLimit(packet);
    } else if (command == "vars.playerLimit") {
		commandVarsPlayerLimit(packet);
    } else if (command == "vars.bannerUrl") {
		commandVarsBannerUrl(packet);
    } else if (command == "vars.serverDescription") {
		commandVarsServerDescription(packet);
    } else if (command == "vars.killCam") {
		commandVarsKillCam(packet);
    } else if (command == "vars.miniMap") {
		commandVarsMiniMap(packet);
    } else if (command == "vars.crossHair") {
		commandVarsCrossHair(packet);
    } else if (command == "vars.3dSpotting") {
		commandVars3dSpotting(packet);
    } else if (command == "vars.miniMapSpotting") {
		commandVarsMiniMapSpotting(packet);
    } else if (command == "vars.thirdPersonVehicleCameras") {
		commandVarsThirdPersonVehicleCameras(packet);
    } else if (command == "vars.teamKillCountForKick") {
		commandVarsTeamKillCountForKick(packet);
    } else if (command == "vars.teamKillValueForKick") {
		commandVarsTeamKillValueForKick(packet);
    } else if (command == "vars.teamKillValueIncrease") {
		commandVarsTeamKillValueIncrease(packet);
    } else if (command == "vars.teamKillValueDecreasePerSecond") {
		commandVarsTeamKillValueDecreasePerSecond(packet);
    } else if (command == "vars.idleTimeout") {
		commandVarsIdleTimeout(packet);
    } else if (command == "vars.profanityFilter") {
		commandVarsProfanityFilter(packet);
    } else if (command == "LevelVars.set") {
		commandLevelVarsSet(packet);
    } else if (command == "LevelVars.get") {
		commandLevelVarsGet(packet);
    } else if (command == "LevelVars.evaluate") {
		commandLevelVarsEvaluate(packet);
    } else if (command == "LevelVars.clear") {
		commandLevelVarsClear(packet);
    } else if (command == "LevelVars.list") {
		commandLevelVarsList(packet);
    } else {
        commandUnknown(packet);
    }
}

/* These events is triggered everytime the client sends or receives data. */
void BFBC2CommandHandler::eventOnDataSent(const QString &command)
{
    emit(onDataSent(command));
}

void BFBC2CommandHandler::eventOnDataReceived(const QString &response)
{
    emit(onDataReceived(response));
}

/* Events */
void BFBC2CommandHandler::eventOnPlayerJoin(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit(onPlayerJoin(player));

    emit(onLogMessage(0, tr("Player <b>%1</b> has joined the game.").arg(player)));
    emit(onRefresh());
}

void BFBC2CommandHandler::eventOnPlayerAuthenticated(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit(onPlayerAuthenticated(player, guid));

    emit(onLogMessage(0, tr("Player <b>%1</b> has just authenticated (GUID: <b>%2</b>).").arg(player).arg(guid)));
}

void BFBC2CommandHandler::eventOnPlayerLeave(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit(onPlayerLeave(player, info));

    emit(onLogMessage(0, tr("Player <b>%1</b> has left the game.").arg(packet.getWord(1).getContent()))); // TODO: Impelment score stuffs here?
    emit(onRefresh());
}

void BFBC2CommandHandler::eventOnPlayerSpawn(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString kit = packet.getWord(2).getContent();
    QStringList weaponList;
    weaponList.append(packet.getWord(3).getContent());
    weaponList.append(packet.getWord(4).getContent());
    weaponList.append(packet.getWord(5).getContent());

    emit(onPlayerSpawn(player, kit, weaponList));

    emit(onLogMessage(0, tr("Player <b>%1</b> has spawned as <b>%2</b> and with <b>%3</b>, <b>%4</b> and <b>%5</b> selected.").arg(packet.getWord(1).getContent(), packet.getWord(2).getContent(), packet.getWord(3).getContent(), packet.getWord(4).getContent(), packet.getWord(5).getContent()))); // TODO: Implement dynamic length on selected weapons.
}

void BFBC2CommandHandler::eventOnPlayerKill(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    emit(onPlayerKill(killer, victim, weapon, headshot));

    if (headshot) {
        emit(onLogMessage(0, tr("Player <b>%1</b> got a headshot on player <b>%2</b> using <b>%3</b>").arg(killer).arg(victim).arg(weapon)));
    } else {
        emit(onLogMessage(0, tr("Player <b>%1</b> has killed player <b>%2</b> with <b>%3</b>").arg(killer).arg(victim).arg(weapon)));
    }

    emit(onRefresh());
}

void BFBC2CommandHandler::eventOnPlayerChat(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit(onPlayerChat(player, message, target));

    emit(onLogMessage(4, tr("<b>%1</b>: %2").arg(player).arg(message)));
    emit(onIngameCommands(player, message));
}

void BFBC2CommandHandler::eventOnPlayerKicked(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString reason = packet.getWord(2).getContent();

    emit(onPlayerKicked(player, reason));

    emit(onLogMessage(0, tr("Player <b>%1</b> has been kicked from the game, reason: <b>%2</b>.").arg(player).arg(reason)));
    emit(onRefresh());
}

void BFBC2CommandHandler::eventOnPlayerSquadChange(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit(onPlayerSquadChange(player, teamId, squadId));

    emit(onLogMessage(0, tr("Player <b>%1</b> has changed squad to <b>%3</b>.").arg(player).arg(squadId)));
    emit(onRefresh());
}

void BFBC2CommandHandler::eventOnPlayerTeamChange(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString::fromLatin1(packet.getWord(2).getContent()).toInt();
    int squadId = QString::fromLatin1(packet.getWord(3).getContent()).toInt();

    emit(onPlayerTeamChange(player, teamId, squadId));

    emit(onLogMessage(0, tr("Player <b>%1</b> has changed team to <b>%2</b>.").arg(player, teamId)));
    emit(onRefresh());
}

void BFBC2CommandHandler::eventOnPunkBusterMessage(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit(onPunkBusterMessage(message));

    emit(onLogMessage(5, message));
}

void BFBC2CommandHandler::eventOnPunkBusterVersion(const FrostbiteRconPacket &packet)
{
    QString version = packet.getWord(1).getContent();

    emit(onPunkBusterVersion(version));

    emit(onLogMessage(5, packet.getWord(1).getContent()));
}

void BFBC2CommandHandler::eventOnServerLoadingLevel(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    int roundsPlayed = QString(packet.getWord(2).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(3).getContent()).toInt();

    emit(onServerLoadingLevel(levelName, roundsPlayed, roundsTotal));

    emit(onLogMessage(0, tr("Loading level: <b>%1</b>").arg(levelName)));
}

void BFBC2CommandHandler::eventOnServerLevelStarted(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit(onServerLevelStarted());

    emit(onLogMessage(0, tr("Level started")));
}

void BFBC2CommandHandler::eventOnServerRoundOver(const FrostbiteRconPacket &packet)
{
    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit(onServerRoundOver(winningTeamId));

    emit(onLogMessage(0, tr("The round has just ended, and <b>%1</b> won").arg(winningTeamId)));
}

void BFBC2CommandHandler::eventOnServerRoundOverPlayers(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit(onServerRoundOverPlayers(playerInfo));

    emit(onLogMessage(0, tr("The round has just ended, and <b>%1</b> is the final detailed player stats").arg(packet.getWord(1).getContent()))); // TODO: Check what this actually outputs.
}

void BFBC2CommandHandler::eventOnServerRoundOverTeamScores(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit(onServerRoundOverTeamScores(teamScores));

    emit(onLogMessage(0, tr("The round has just ended, and <b>%1</b> is the final ticket/kill/life count for each team").arg(teamScores)));
}

/* Commands */
void BFBC2CommandHandler::commandLoginPlainText(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onLoginPlainTextCommand(tr("You have successfully logged in.")));

        emit(onAuthenticated()); // TODO: Check this.
    } else if (response == "InvalidPassword") {
        emit(onLoginPlainTextCommand(tr("Invalid password.")));
    } else if (response == "PasswordNotSet") {
        emit(onLoginPlainTextCommand(tr("Password not set.")));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

/* Misc */
void BFBC2CommandHandler::commandLoginHashed(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            emit(onLogMessage(0, (tr("We got salt: %1").arg(packet.getWord(1).getContent()))));

            QByteArray loginSalt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));
            emit(onGotSalt(loginSalt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        // QString response = packet.getWord(0).getContent(); TODO: Isn't this redundant?

        if (response == "OK") {
            emit(onLogMessage(0, tr("You have successfully logged in.")));
            emit(onAuthenticated());
        } else if (response == "InvalidPasswordHash") {
            emit(onLogMessage(1, tr("Invalid password.")));
        }
    }

    if (response == "PasswordNotSet") {
        emit(onLogMessage(1, tr("Password not set.")));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::commandLogout(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onLogoutCommand(tr("You are now logged out.")));
    } else if (response == "InvalidArguments"){
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::commandQuit(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onQuitCommand(tr("Disconnected.")));
    } else if (response == "InvalidArguments"){
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::commandVersion(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 3) {
        QString type = packet.getWord(1).getContent();
        int buildId = QString(packet.getWord(2).getContent()).toInt();
        QString version;

        QMap<int, QString> versionMap;
        versionMap.insert(571287, "R21");
        versionMap.insert(581637, "R22");
        versionMap.insert(584642, "R23");
        versionMap.insert(593485, "R24");
        versionMap.insert(602833, "R25");
        versionMap.insert(609063, "R26");
        versionMap.insert(617877, "R27");
        versionMap.insert(621775, "R28");
        versionMap.insert(638140, "R30");
        versionMap.insert(720174, "R32");
        versionMap.insert(851434, "R34");

        if (versionMap.contains(buildId)) {
            version = versionMap.value(buildId);
        }

        emit(onVersionCommand(type, buildId, version));

        emit(onLogMessage(0,tr("<b>%1</b> server version: <b>%2</b>.").arg(type, version)));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::commandListPlayers(const FrostbiteRconPacket &packet) // TODO: Implement this.
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK") {
        emit(onListPlayersCommand());
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BFBC2CommandHandler::commandEventsEnabled(const FrostbiteRconPacket &packet)
{

}

void BFBC2CommandHandler::commandHelp(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList helpList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            helpList.append(packet.getWord(i).getContent());
        }

        emit(onHelpCommand(helpList));
    }
}

void BFBC2CommandHandler::commandAdminRunScript(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    // TODO: Implement this.
}

void BFBC2CommandHandler::commandPunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    // TODO: Implement this.
}

/* Query */
void BFBC2CommandHandler::commandServerInfo(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList serverInfo;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            serverInfo.append(packet.getWord(i).getContent());
        }

        emit(onServerInfoCommand(serverInfo));
    }
}

void BFBC2CommandHandler::commandAdminYell(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminSay(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminRunNextRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminRestartRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminEndRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminRunNextLevel(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminRestartMap(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminCurrentLevel(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandMapListNextLevelIndex(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int index = QString(packet.getWord(1).getContent()).toInt();

        emit(onMapListNextLevelIndexCommand(index));
    }
}

void BFBC2CommandHandler::commandAdminSupportedMaps(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminSetPlaylist(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminGetPlaylist(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminGetPlaylists(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminKickPlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminListPlayers(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &playerList) // TODO: Check if subset group is correct.
{
    qDebug() << "LISTPLAYERS!!!";
    qDebug() << QString(lastSentPacket.getWord(1).getContent());

    if ((lastSentPacket.getWordCount() > 0) && (QString(lastSentPacket.getWord(1).getContent()) == "all")) {
        QString response(packet.getWord(0).getContent());
        if (response == "OK") {
            qDebug() << "HANDLING PLAYERS!";
            playerList.clear();
            PlayerListItem pli;
            quint32 paramcount = QString(packet.getWord(1).getContent()).toUInt();
            quint32 playercount = QString(packet.getWord(2 + paramcount).getContent()).toUInt();

            for (quint32 i = 0; i < playercount; i++) {
                pli.clear();
                for (quint32 j = 0; j < paramcount; j++) {
                    pli[packet.getWord(2 + j).getContent()] = packet.getWord(2 + paramcount + 1 + i * paramcount + j).getContent();
                }

                playerList.push_back(pli);
            }
            emit(onPlayerListChange());
        } else if (response == "InvalidArguments") {
            emit(onLogMessage(1, tr("Invalid arguments.")));
        }
    }
}

void BFBC2CommandHandler::commandAdminMovePlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandAdminKillPlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsTextChatModerationMode(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString mode = packet.getWord(1).getContent();
        emit(onVarsTextChatModerationModeCommand(mode));
    }
}

void BFBC2CommandHandler::commandVarsTextChatSpamTriggerCount(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamTriggerCountCommand(count));
    }
}

void BFBC2CommandHandler::commandVarsTextChatSpamDetectionTime(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamDetectionTimeCommand(count));
    }
}

void BFBC2CommandHandler::commandVarsTextChatSpamCoolDownTime(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamCoolDownTimeCommand(count));
    }
}

void BFBC2CommandHandler::commandTextChatModerationListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandTextChatModerationListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandTextChatModerationListAdd(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandTextChatModerationListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandTextChatModerationListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandTextChatModerationListList(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandBanListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandBanListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandBanListAdd(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandBanListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandBanListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandBanListList(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList banList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            banList.append(packet.getWord(i).getContent());
        }

        emit(onBanListListCommand(banList));
    }
}

void BFBC2CommandHandler::commandReservedSlotsLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandReservedSlotsSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandReservedSlotsAddPlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandReservedSlotsRemovePlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandReservedSlotsClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandReservedSlotsList(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList reservedSlotList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            reservedSlotList.append(packet.getWord(i).getContent());
        }

        emit(onReservedSlotsListCommand(reservedSlotList));
    }
}

void BFBC2CommandHandler::commandMapListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandMapListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandMapListList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) // TODO: Look over this.
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        if ((lastSentPacket.getWordCount() > 1) && (QString(lastSentPacket.getWord(1).getContent()) == "rounds")) {
            QStringList mapList;

            for (quint32 i = 1; i < packet.getWordCount(); i = i + 2) {
                mapList << QString(packet.getWord(i).getContent()).toLower() << packet.getWord(i + 1).getContent();
            }

            //emit(onMapListListRoundsCommand(mapList));
        } else {
            QStringList mapList;

            for (quint32 i = 1; i < packet.getWordCount(); i++) {
                mapList.append(packet.getWord(i).getContent());
            }

            emit(onMapListListCommand(mapList));
        }
    }

}

void BFBC2CommandHandler::commandMapListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandMapListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandMapListAppend(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandMaplistInsert(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsServerName(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit(onVarsServerNameCommand(serverName));
    }
}

void BFBC2CommandHandler::commandVarsAdminPassword(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsGamePassword(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsPunkBuster(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsHardCore(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsRanked(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsRankLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsTeamBalance(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsFriendlyFire(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsCurrentPlayerLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsMaxPlayerLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsPlayerLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsBannerUrl(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit(onVarsBannerUrlCommand(bannerUrl));
    }
}

void BFBC2CommandHandler::commandVarsServerDescription(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit(onVarsServerDescriptionCommand(serverDescription));
    }
}

void BFBC2CommandHandler::commandVarsKillCam(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsMiniMap(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsCrossHair(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVars3dSpotting(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsMiniMapSpotting(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsThirdPersonVehicleCameras(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsTeamKillCountForKick(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsTeamKillValueForKick(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsTeamKillValueIncrease(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsTeamKillValueDecreasePerSecond(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsIdleTimeout(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandVarsProfanityFilter(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandLevelVarsSet(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandLevelVarsGet(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandLevelVarsEvaluate(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandLevelVarsClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandLevelVarsList(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandUnknown(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "UnknownCommand") {
        emit(onUnknownCommand());
    }
}
