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
    } else if (command == "player.onDisconnect") {
        eventOnPlayerDisconnect(packet);
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
    } else if (command == "serverinfo") {
        commandServerInfo(packet);
    } else if (command == "logout") {
        commandLogout(packet);
    } else if (command == "quit") {
        commandQuit(packet);
    } else if (command ==  "version") {
        commandVersion(packet);
    } else if (command ==  "currentLevel") {
        commandCurrentLevel(packet);
    } else if (command ==  "listPlayers") {
        commandListPlayers(packet);
    } else if (command == "admin.eventsEnabled") {
        commandAdminEventsEnabled(packet);
    } else if (command == "admin.help") {
        commandAdminHelp(packet);
    } else if (command == "admin.kickPlayer") {
        commandAdminKickPlayer(packet);
    } else if (command == "admin.killPlayer") {
        commandAdminKillPlayer(packet);
    } else if (command == "admin.listPlayers") {
        commandAdminListPlayers(packet);
    } else if (command == "admin.movePlayer") {
        commandAdminMovePlayer(packet);
    } else if (command == "admin.password") {
        commandAdminPassword(packet);
    } else if (command == "admin.say") {
        commandAdminSay(packet);
    } else if (command == "admin.shutDown") {
        commandAdminShutDown(packet);
    } else if (command == "admin.yell") {
        commandAdminYell(packet);
    } else if (command == "banList.add") {
        commandBanListAdd(packet);
    } else if (command == "banList.clear") {
        commandBanListClear(packet);
    } else if (command == "banList.list") {
        commandBanListList(packet);
    } else if (command == "banList.load") {
        commandBanListLoad(packet);
    } else if (command == "banList.remove") {
        commandBanListRemove(packet);
    } else if (command == "banList.save") {
        commandBanListSave(packet);
    } else if (command == "fairFight.activate") {
        commandFairFightActivate(packet);
    } else if (command == "fairFight.deactivate") {
        commandFairFightDeactivate(packet);
    } else if (command == "fairFight.isActive") {
        commandFairFightIsActive(packet);
    } else if (command == "mapList.add") {
        commandMapListAdd(packet);
    } else if (command == "mapList.availableMaps") {
        commandMapListAvailableMaps(packet);
    } else if (command == "mapList.clear") {
        commandMapListClear(packet);
    } else if (command == "mapList.endRound") {
        commandMapListEndRound(packet);
    } else if (command == "mapList.getMapIndices") {
        commandMapListGetMapIndices(packet);
    } else if (command == "mapList.getRounds") {
        commandMapListGetRounds(packet);
    } else if (command == "maplist.list") { // case sensetive?
        commandMapListList(packet);
    } else if (command == "mapList.load") {
        commandMapListLoad(packet);
    } else if (command == "mapList.remove") {
        commandMapListRemove(packet);
    } else if (command == "mapList.restartRound") {
        commandMapListRestartRound(packet);
    } else if (command == "mapList.runNextRound") {
        commandMapListRunNextRound(packet);
    } else if (command == "mapList.save") {
        commandMapListSave(packet);
    } else if (command == "mapList.setNextMapIndex") {
        commandMapListSetNextMapIndex(packet);
    } else if (command == "player.idleDuration") {
        commandPlayerIdleDuration(packet);
    } else if (command == "player.isAlive") {
        commandPlayerIsAlive(packet);
    } else if (command == "player.ping") {
        commandPlayerPing(packet);
    } else if (command == "punkBuster.activate") {
        commandPunkBusterActivate(packet);
    } else if (command == "punkBuster.isActive") {
        commandPunkBusterIsActive(packet);
    } else if (command == "punkBuster.pb_sv_command") {
        commandPunkBusterPbSvCommand(packet);
    } else if (command == "reservedSlotsList.add") {
        commandReservedSlotsListAdd(packet);
    } else if (command == "reservedSlotsList.aggressiveJoin") {
        commandReservedSlotsListAggressiveJoin(packet);
    } else if (command == "reservedSlotsList.clear") {
        commandReservedSlotsListClear(packet);
    } else if (command == "reservedSlotsList.list") {
        commandReservedSlotsListList(packet);
    } else if (command == "reservedSlotsList.load") {
        commandReservedSlotsListLoad(packet);
    } else if (command == "reservedSlotsList.remove") {
        commandReservedSlotsListRemove(packet);
    } else if (command == "reservedSlotsList.save") {
        commandReservedSlotsListSave(packet);
    } else if (command == "spectatorList.add") {
        commandSpectatorListAdd(packet);
    } else if (command == "spectatorList.clear") {
        commandSpectatorListClear(packet);
    } else if (command == "spectatorList.list") {
        commandSpectatorListList(packet);
    } else if (command == "spectatorList.remove") {
        commandSpectatorListRemove(packet);
    } else if (command == "spectatorList.save") {
        commandSpectatorListSave(packet);
    } else if (command == "squad.leader") {
        commandSquadLeader(packet);
    } else if (command == "squad.listActive") {
        commandSquadListActive(packet);
    } else if (command == "squad.listPlayers") {
        commandSquadListPlayers(packet);
    } else if (command == "squad.private") {
        commandSquadPrivate(packet);
    } else if (command == "vars.3dSpotting") {
        commandVars3dSpotting(packet);
    } else if (command == "vars.3pCam") {
        commandVars3pCam(packet);
    } else if (command == "vars.alwaysAllowSpectators") {
        commandVarsAlwaysAllowSpectators(packet);
    } else if (command == "vars.autoBalance") {
        commandVarsAutoBalance(packet);
    } else if (command == "vars.bulletDamage") {
        commandVarsBulletDamage(packet);
    } else if (command == "vars.commander") {
        commandVarsCommander(packet);
    } else if (command == "vars.crossHair") {
        commandVarsCrossHair(packet);
    } else if (command == "vars.forceReloadWholeMags") {
        commandVarsForceReloadWholeMags(packet);
    } else if (command == "vars.friendlyFire") {
        commandVarsFriendlyFire(packet);
    } else if (command == "vars.gameModeCounter") {
        commandVarsGameModeCounter(packet);
    } else if (command == "vars.gamePassword") {
        commandVarsGamePassword(packet);
    } else if (command == "vars.hitIndicatorsEnabled") {
        commandVarsHitIndicatorsEnabled(packet);
    } else if (command == "vars.hud") {
        commandVarsHud(packet);
    } else if (command == "vars.idleBanRounds") {
        commandVarsIdleBanRounds(packet);
    } else if (command == "vars.idleTimeout") {
        commandVarsIdleTimeout(packet);
    } else if (command == "vars.killCam") {
        commandVarsKillCam(packet);
    } else if (command == "vars.maxPlayers") {
        commandVarsMaxPlayers(packet);
    } else if (command == "vars.maxSpectators") {
        commandVarsMaxSpectators(packet);
    } else if (command == "vars.miniMap") {
        commandVarsMiniMap(packet);
    } else if (command == "vars.miniMapSpotting") {
        commandVarsMiniMapSpotting(packet);
    } else if (command == "vars.mpExperience") {
        commandVarsMpExperience(packet);
    } else if (command == "vars.nameTag") {
        commandVarsNameTag(packet);
    } else if (command == "vars.onlySquadLeaderSpawn") {
        commandVarsOnlySquadLeaderSpawn(packet);
    } else if (command == "vars.playerRespawnTime") {
        commandVarsPlayerRespawnTime(packet);
    } else if (command == "vars.preset") {
        commandVarsPreset(packet);
    } else if (command == "vars.regenerateHealth") {
        commandVarsRegenerateHealth(packet);
    } else if (command == "vars.roundLockdownCountdown") {
        commandVarsRoundLockdownCountdown(packet);
    } else if (command == "vars.roundRestartPlayerCount") {
        commandVarsRoundRestartPlayerCount(packet);
    } else if (command == "vars.roundStartPlayerCount") {
        commandVarsRoundStartPlayerCount(packet);
    } else if (command == "vars.roundTimeLimit") {
        commandVarsRoundTimeLimit(packet);
    } else if (command == "vars.roundWarmupTimeout") {
        commandVarsRoundWarmupTimeout(packet);
    } else if (command == "vars.serverDescription") {
        commandVarsServerDescription(packet);
    } else if (command == "vars.serverMessage") {
        commandVarsServerMessage(packet);
    } else if (command == "vars.serverName") {
        commandVarsServerName(packet);
    } else if (command == "vars.serverType") {
        commandVarsServerType(packet);
    } else if (command == "vars.soldierHealth") {
        commandVarsSoldierHealth(packet);
    } else if (command == "vars.team1FactionOverride") {
        commandVarsTeam1FactionOverride(packet);
    } else if (command == "vars.team2FactionOverride") {
        commandVarsTeam2FactionOverride(packet);
    } else if (command == "vars.team3FactionOverride") {
        commandVarsTeam3FactionOverride(packet);
    } else if (command == "vars.team4FactionOverride") {
        commandVarsTeam4FactionOverride(packet);
    } else if (command == "vars.teamKillCountForKick") {
        commandVarsTeamKillCountForKick(packet);
    } else if (command == "vars.teamKillKickForBan") {
        commandVarsTeamKillKickForBan(packet);
    } else if (command == "vars.teamKillValueDecreasePerSecond") {
        commandVarsTeamKillValueDecreasePerSecond(packet);
    } else if (command == "vars.teamKillValueForKick") {
        commandVarsTeamKillValueForKick(packet);
    } else if (command == "vars.teamKillValueIncrease") {
        commandVarsTeamKillValueIncrease(packet);
    } else if (command == "vars.ticketBleedRate") {
        commandVarsTicketBleedRate(packet);
    } else if (command == "vars.unlockMode") {
        commandVarsUnlockMode(packet);
    } else if (command == "vars.vehicleSpawnAllowed") {
        commandVarsVehicleSpawnAllowed(packet);
    } else if (command == "vars.vehicleSpawnDelay") {
        commandVarsVehicleSpawnDelay(packet);
    } else {
        commandUnknown();
    }
}

/* Events */
void BF4CommandHandler::eventOnPlayerAuthenticated(const FrostbiteRconPacket &packet)
{
    QString player = packet.getWord(1).getContent();
    QString guid = packet.getWord(2).getContent();

    emit(onPlayerAuthenticated(player, guid));
}

void BF4CommandHandler::eventOnPlayerDisconnect(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit(onPlayerDisconnect());
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
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandLoginHashed(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response = packet.getWord(0).getContent();

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            QByteArray salt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));

            emit(onLoginHashedCommand(salt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        if (response == "OK") {
            emit(onLoginHashedCommand());
        }
    }
}

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

void BF4CommandHandler::commandLogout(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandQuit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
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
        versionMap.insert(117719, "R31");

        if (versionMap.contains(buildId)) {
            version = versionMap.value(buildId);
        }

        emit(onVersionCommand(type, buildId, version));
    } else if (response == "InvalidArguments") {
        emit(onUnknownCommand());
    }
}

void BF4CommandHandler::commandCurrentLevel(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandListPlayers(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminEventsEnabled(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminHelp(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminKickPlayer(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminKillPlayer(const FrostbiteRconPacket &packet)
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

void BF4CommandHandler::commandAdminPassword(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminSay(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminShutDown(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandAdminYell(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListAdd(const FrostbiteRconPacket &packet)
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

void BF4CommandHandler::commandBanListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandBanListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandFairFightActivate(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandFairFightDeactivate(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandFairFightIsActive(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListAdd(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListAvailableMaps(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListEndRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListGetMapIndices(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListGetRounds(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListList(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        MapList mapList;
        unsigned int maps = QString(packet.getWord(1).getContent()).toUInt();
        unsigned int parameters = QString(packet.getWord(2).getContent()).toUInt();

        for (unsigned int i = 0; i < maps; i++) {
            QString level;
            QString gameMode;
            int rounds;

            for (unsigned int j = 0; j < parameters; j++) {
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

            MapListEntry entry = {
                level,
                gameMode,
                rounds,
            };

            mapList.append(entry);

            qDebug() << "Got level: " << level << gameMode << rounds;
        }

        emit(onMapListListCommand(mapList));
    }

    /*
    if (response == "OK" && packet.getWordCount() > 1) {
        QStringList mapList;

        for (unsigned int i = 3; i < packet.getWordCount(); i += 3) {
            mapList.append(packet.getWord(i).getContent());
        }

        emit(onMapListListCommand(mapList));
    }
    */
}

void BF4CommandHandler::commandMapListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListRestartRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListRunNextRound(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandMapListSetNextMapIndex(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandPlayerIdleDuration(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandPlayerIsAlive(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandPlayerPing(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandPunkBusterActivate(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandPunkBusterIsActive(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandPunkBusterPbSvCommand(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsListAdd(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsListAggressiveJoin(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsListList(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList reservedSlotList;

        for (unsigned int i = 1; i < packet.getWordCount(); i++) {
            reservedSlotList.append(packet.getWord(i).getContent());
        }

        emit(onReservedSlotsListListCommand(reservedSlotList));
    }
}

void BF4CommandHandler::commandReservedSlotsListLoad(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandReservedSlotsListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSpectatorListAdd(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSpectatorListClear(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSpectatorListList(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSpectatorListRemove(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSpectatorListSave(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSquadLeader(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSquadListActive(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSquadListPlayers(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandSquadPrivate(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVars3dSpotting(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVars3pCam(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsAlwaysAllowSpectators(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsAutoBalance(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsBulletDamage(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsCommander(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsCrossHair(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsForceReloadWholeMags(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsFriendlyFire(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsGameModeCounter(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsGamePassword(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsHitIndicatorsEnabled(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsHud(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsIdleBanRounds(const FrostbiteRconPacket &packet)
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

void BF4CommandHandler::commandVarsKillCam(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsMaxPlayers(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsMaxSpectators(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsMiniMap(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsMiniMapSpotting(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsMpExperience(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsNameTag(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsOnlySquadLeaderSpawn(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsPlayerRespawnTime(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsPreset(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsRegenerateHealth(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsRoundLockdownCountdown(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsRoundRestartPlayerCount(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsRoundStartPlayerCount(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsRoundTimeLimit(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsRoundWarmupTimeout(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsServerDescription(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverDescription = packet.getWord(1).getContent();

        emit(onVarsServerDescriptionCommand(serverDescription));
    }
}

void BF4CommandHandler::commandVarsServerMessage(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverMessage = packet.getWord(1).getContent();

        emit(onVarsServerMessageCommand(serverMessage));
    }
}

void BF4CommandHandler::commandVarsServerName(const FrostbiteRconPacket &packet)
{
    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() > 1) {
        QString serverName = packet.getWord(1).getContent();

        emit(onVarsServerNameCommand(serverName));
    }
}

void BF4CommandHandler::commandVarsServerType(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsSoldierHealth(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeam1FactionOverride(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeam2FactionOverride(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeam3FactionOverride(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeam4FactionOverride(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeamKillCountForKick(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeamKillKickForBan(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsTeamKillValueDecreasePerSecond(const FrostbiteRconPacket &packet)
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

void BF4CommandHandler::commandVarsTicketBleedRate(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsUnlockMode(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsVehicleSpawnAllowed(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BF4CommandHandler::commandVarsVehicleSpawnDelay(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}
