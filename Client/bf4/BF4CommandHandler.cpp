#include "BF4CommandHandler.h"

BF4CommandHandler::BF4CommandHandler(QObject *parent) : FrostbiteCommandHandler(parent)
{

}

BF4CommandHandler::~BF4CommandHandler()
{

}

void BF4CommandHandler::exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    // Parse and call events.
    if (command == "player.onAuthenticated") {
            eventOnPlayerAuthenticated(packet);
    } else if (command == "player.onJoin") {
        eventOnPlayerJoin(packet);
    } else if (command == "player.onLeave") {
        eventOnPlayerLeave(packet);
    } else if (command == "player.onSpawn") {
        eventOnPlayerSpawn(packet);
    } else if (command == "player.onKill") {
        eventOnPlayerKill(packet);
    } else if (command == "player.onChat") {
        eventOnPlayerChat(packet);
    } else if (command == "server.onMaxPlayerCountChange") {
        eventOnServerMaxPlayerCountChange(packet);
    } else if (command == "player.onSquadChange") {
        eventOnPlayerSquadChange(packet);
    } else if (command == "player.onTeamChange") {
        eventOnPlayerTeamChange(packet);
    } else if (command == "punkBuster.onMessage") {
        eventOnPunkBusterMessage(packet);
    } else if (command == "server.onLevelLoaded") {
        eventOnServerLevelLoaded(packet);
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
    } else if (command == "listplayers") {
        commandListPlayers(packet);
    } else if (command == "admin.eventsenabled") {
        commandEventsEnabled(packet);
    } else if (command == "help") {
        commandHelp(packet);
    } else if (command == "admin.runscript") {
        commandAdminRunScript(packet);
    } else if (command == "punkbuster.pb_sv_command") {
        commandPunkBusterPbSvCommand(packet);
    } else if (command == "serverinfo") {
        commandServerInfo(packet);
    } else if (command == "admin.yell") {
        commandAdminYell(packet);
    } else if (command == "admin.say") {
        commandAdminSay(packet);
    } else if (command == "admin.runnextround") {
        commandAdminRunNextRound(packet);
    } else if (command == "admin.restartround") {
        commandAdminRestartRound(packet);
    } else if (command == "admin.endround") {
        commandAdminEndRound(packet);
    } else if (command == "admin.runnextlevel") {
        commandAdminRunNextLevel(packet);
    } else if (command == "admin.restartmap") {
        commandAdminRestartMap(packet);
    } else if (command == "admin.currentlevel") {
        commandAdminCurrentLevel(packet);
    } else if (command == "mapList.nextlevelindex") {
        commandMapListNextLevelIndex(packet);
    } else if (command == "admin.supportedmaps") {
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
        commandAdminListPlayers(packet);
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
    } else if (command == "banlist.save") {
        commandBanListSave(packet);
    } else if (command == "banlist.add") {
        commandBanListAdd(packet);
    } else if (command == "banlist.remove") {
        commandBanListRemove(packet);
    } else if (command == "banlist.clear") {
        commandBanListClear(packet);
    } else if (command == "banlist.list") {
        commandBanListList(packet);
    } else if (command == "reservedslots.load") {
        commandReservedSlotsLoad(packet);
    } else if (command == "reservedslots.save") {
        commandReservedSlotsSave(packet);
    } else if (command == "reservedslots.addPlayer") {
        commandReservedSlotsAddPlayer(packet);
    } else if (command == "reservedslots.removePlayer") {
        commandReservedSlotsRemovePlayer(packet);
    } else if (command == "reservedslots.clear") {
        commandReservedSlotsClear(packet);
    } else if (command == "reservedslots.list") {
        commandReservedSlotsList(packet);
    } else if (command == "maplist.load") {
        commandMapListLoad(packet);
    } else if (command == "maplist.save") {
        commandMapListSave(packet);
    } else if (command == "maplist.list") {
        commandMapListList(packet);
    } else if (command == "maplist.clear") {
        commandMapListClear(packet);
    } else if (command == "maplist.remove") {
        commandMapListRemove(packet);
    } else if (command == "maplist.append") {
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

/* Events */
void BF4CommandHandler::eventOnPlayerAuthenticated(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit(onPlayerAuthenticated(player, guid));
}

void BF4CommandHandler::eventOnPlayerJoin(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();

    emit(onPlayerJoin(player));
}

void BF4CommandHandler::eventOnPlayerLeave(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString info = packet.getWord(2).getContent();

    emit(onPlayerLeave(player, info));
}

void BF4CommandHandler::eventOnPlayerSpawn(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString kit = packet.getWord(2).getContent();
    QStringList weaponList;
    weaponList.append(packet.getWord(3).getContent());
    weaponList.append(packet.getWord(4).getContent());
    weaponList.append(packet.getWord(5).getContent());

    emit(onPlayerSpawn(player, kit, weaponList));
}

void BF4CommandHandler::eventOnPlayerKill(const FrostbiteRconPacket &packet)
{
    QString killer = packet.getWord(1).getContent();
    QString victim = packet.getWord(2).getContent();
    QString weapon = packet.getWord(3).getContent();
    bool headshot = packet.getWord(4).getContent();

    qDebug() << "Bool is: " << headshot;

    emit(onPlayerKill(killer, victim, weapon, headshot));
}

void BF4CommandHandler::eventOnPlayerChat(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString message = packet.getWord(2).getContent();
    QString target = packet.getWord(3).getContent();

    emit(onPlayerChat(player, message, target));
}

void BF4CommandHandler::eventOnPlayerSquadChange(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString(packet.getWord(2).getContent()).toInt();
    int squadId = QString(packet.getWord(3).getContent()).toInt();

    emit(onPlayerSquadChange(player, teamId, squadId));
}

void BF4CommandHandler::eventOnPlayerTeamChange(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    int teamId = QString::fromLatin1(packet.getWord(2).getContent()).toInt();
    int squadId = QString::fromLatin1(packet.getWord(3).getContent()).toInt();

    emit(onPlayerTeamChange(player, teamId, squadId));
}

void BF4CommandHandler::eventOnPunkBusterMessage(const FrostbiteRconPacket &packet)
{
    QString message = packet.getWord(1).getContent();

    emit(onPunkBusterMessage(message));
}

void BF4CommandHandler::eventOnServerMaxPlayerCountChange(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::eventOnServerLevelLoaded(const FrostbiteRconPacket &packet)
{
    QString levelName = packet.getWord(1).getContent();
    QString gameMode = packet.getWord(2).getContent();
    int roundsPlayed = QString(packet.getWord(3).getContent()).toInt();
    int roundsTotal = QString(packet.getWord(4).getContent()).toInt();

    emit(onServerLevelLoaded(levelName, gameMode, roundsPlayed, roundsTotal));
}

void BF4CommandHandler::eventOnServerRoundOver(const FrostbiteRconPacket &packet)
{
    int winningTeamId = QString(packet.getWord(1).getContent()).toInt();

    emit(onServerRoundOver(winningTeamId));
}

void BF4CommandHandler::eventOnServerRoundOverPlayers(const FrostbiteRconPacket &packet)
{
    QString playerInfo = packet.getWord(1).getContent();

    emit(onServerRoundOverPlayers(playerInfo));
}

void BF4CommandHandler::eventOnServerRoundOverTeamScores(const FrostbiteRconPacket &packet)
{
    QString teamScores = packet.getWord(1).getContent();

    emit(onServerRoundOverTeamScores(teamScores));
}

/* Commands */
void BF4CommandHandler::commandLoginPlainText(const FrostbiteRconPacket &packet)
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
void BF4CommandHandler::commandLoginHashed(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            emit(onDataReceived(tr("We got salt: %1").arg(packet.getWord(1).getContent())));

            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit(onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        // QString response = packet.getWord(0).getContent(); TODO: Isn't this redundant?

        qDebug() << "Logged in";

        if (response == "OK") {
            //emit(onLogMessage(0, tr("You have successfully logged in.")));
            emit(onAuthenticated());
        } else if (response == "InvalidPasswordHash") {
            //emit(onLogMessage(1, tr("Invalid password.")));
        }
    }

    if (response == "PasswordNotSet") {
        //emit(onLogMessage(1, tr("Password not set.")));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BF4CommandHandler::commandLogout(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onLogoutCommand(tr("You are now logged out.")));
    } else if (response == "InvalidArguments"){
        emit(onUnknownCommand());
    }
}

void BF4CommandHandler::commandQuit(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK") {
        emit(onQuitCommand(tr("Disconnected.")));
    } else if (response == "InvalidArguments"){
        emit(onUnknownCommand());
    }
}

void BF4CommandHandler::commandVersion(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() == 3) {
        QString type = packet.getWord(1).getContent();
        int buildId = QString(packet.getWord(2).getContent()).toInt();
        QString version;

        QMap<int, QString> versionMap;
        versionMap.insert(70517, "OB-R2");
        versionMap.insert(72879, "OB-R3");
        versionMap.insert(77582, "OB-R4");
        versionMap.insert(87884, "R4");
        versionMap.insert(88031, "R5");
        versionMap.insert(88058, "R6");
        versionMap.insert(88472, "R7");
        versionMap.insert(89702, "R8");
        versionMap.insert(90165, "R9");
        versionMap.insert(90519, "R10");
        versionMap.insert(91697, "R11");
        versionMap.insert(93111, "R12");
        versionMap.insert(94318, "R13");
        versionMap.insert(95851, "R14");
        versionMap.insert(96245, "R15");
        versionMap.insert(97870, "R16");
        versionMap.insert(99392, "R17");
        versionMap.insert(101684, "R18");
        versionMap.insert(102560, "R19");
        versionMap.insert(103064, "R20");
        versionMap.insert(106318, "R21");
        versionMap.insert(106533, "R22");
        versionMap.insert(107145, "R23");
        versionMap.insert(107436, "R24");
        versionMap.insert(108751, "R25");
        versionMap.insert(109758, "R26");
        versionMap.insert(111118, "R27");
        versionMap.insert(112943, "R28");
        versionMap.insert(114240, "R29");
        versionMap.insert(115397, "R30");

        if (versionMap.contains(buildId)) {
            version = versionMap.value(buildId);
        }

        emit(onVersionCommand(type, buildId, version));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BF4CommandHandler::commandListPlayers(const FrostbiteRconPacket &packet) // TODO: Implement this.
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK") {
        emit(onListPlayersCommand());
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BF4CommandHandler::commandEventsEnabled(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandHelp(const FrostbiteRconPacket &packet)
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

void BF4CommandHandler::commandAdminRunScript(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    // TODO: Implement this.
}

void BF4CommandHandler::commandPunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    // TODO: Implement this.
}

/* Query */
void BF4CommandHandler::commandServerInfo(const FrostbiteRconPacket &packet)
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

void BF4CommandHandler::commandAdminYell(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminSay(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminRunNextRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminRestartRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminEndRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminRunNextLevel(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminRestartMap(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminCurrentLevel(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListNextLevelIndex(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int index = QString(packet.getWord(1).getContent()).toInt();

        emit(onMapListNextLevelIndexCommand(index));
    }
}

void BF4CommandHandler::commandAdminSupportedMaps(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminSetPlaylist(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminGetPlaylist(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminGetPlaylists(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminKickPlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminListPlayers(const FrostbiteRconPacket &packet)
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

        emit(onAdminListPlayersCommand(playerList));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BF4CommandHandler::commandAdminMovePlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminKillPlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTextChatModerationMode(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString mode = packet.getWord(1).getContent();
        emit(onVarsTextChatModerationModeCommand(mode));
    }
}

void BF4CommandHandler::commandVarsTextChatSpamTriggerCount(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamTriggerCountCommand(count));
    }
}

void BF4CommandHandler::commandVarsTextChatSpamDetectionTime(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamDetectionTimeCommand(count));
    }
}

void BF4CommandHandler::commandVarsTextChatSpamCoolDownTime(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int count = QString(packet.getWord(1).getContent()).toInt();
        emit(onVarsTextChatSpamCoolDownTimeCommand(count));
    }
}

void BF4CommandHandler::commandTextChatModerationListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandTextChatModerationListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandTextChatModerationListAdd(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandTextChatModerationListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandTextChatModerationListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandTextChatModerationListList(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListAdd(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListList(const FrostbiteRconPacket &packet)
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

void BF4CommandHandler::commandReservedSlotsLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsAddPlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsRemovePlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsList(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList reservedSlotList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            reservedSlotList.append(packet.getWord(i).getContent());
        }

        emit(onReservedSlotsListCommand(reservedSlotList));
    }
}

void BF4CommandHandler::commandMapListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListList(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QStringList mapList;

        for (unsigned int i = 3; i < packet.getWordCount(); i += 3) {
            mapList.append(packet.getWord(i).getContent());
        }

//        unsigned int count = QString(packet.getWord(1).getContent()).toUInt();
//        unsigned int wordsCount = QString(packet.getWord(2).getContent()).toUInt();
//        QStringList mapList;

//        qDebug() << "Map count is: " << count;
//        qDebug() << "Word count is: " << wordsCount;

//        for (unsigned int i = 1; i < count + 1; i++) {
//            qDebug() << "Index i is: " << i;

//            for (unsigned int j = 3; j < i + 1 * wordsCount; j++) {
//                qDebug() << "Index j is: " << j;

//                mapList.append(packet.getWord(j).getContent());
//            }
//        }

        emit(onMapListListCommand(mapList));
    }
}

void BF4CommandHandler::commandMapListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListAppend(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMaplistInsert(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsServerName(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit(onVarsServerNameCommand(serverName));
    }
}

void BF4CommandHandler::commandVarsAdminPassword(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsGamePassword(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsPunkBuster(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsHardCore(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsRanked(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsRankLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeamBalance(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsFriendlyFire(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsCurrentPlayerLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsMaxPlayerLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsPlayerLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsBannerUrl(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit(onVarsBannerUrlCommand(bannerUrl));
    }
}

void BF4CommandHandler::commandVarsServerDescription(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit(onVarsServerDescriptionCommand(serverDescription));
    }
}

void BF4CommandHandler::commandVarsKillCam(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsMiniMap(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsCrossHair(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVars3dSpotting(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsMiniMapSpotting(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsThirdPersonVehicleCameras(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeamKillCountForKick(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeamKillValueForKick(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeamKillValueIncrease(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeamKillValueDecreasePerSecond(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsIdleTimeout(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        int timeout = QString(packet.getWord(1).getContent()).toInt();

        emit(onVarsIdleTimeoutCommand(timeout));
    }
}

void BF4CommandHandler::commandVarsProfanityFilter(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandLevelVarsSet(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandLevelVarsGet(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandLevelVarsEvaluate(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandLevelVarsClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandLevelVarsList(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandUnknown(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "UnknownCommand") {
        emit(onUnknownCommand());
    }
}
