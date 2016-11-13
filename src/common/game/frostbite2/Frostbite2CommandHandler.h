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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FROSTBITE2COMMANDHANDLER_H
#define FROSTBITE2COMMANDHANDLER_H

#include "FrostbiteCommandHandler.h"

class Frostbite2PlayerEntry;
class BF4PlayerEntry;
enum class Frostbite2UnlockModeEnum;

class Frostbite2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    Frostbite2CommandHandler(QObject *parent = nullptr);
    virtual ~Frostbite2CommandHandler() override;

    virtual bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) override;

public slots:
    /* Send commands */
    // Admin
    void sendAdminHelpCommand();
    void sendAdminPasswordCommand(const QString &password = QString());

    // Game Admin
    //gameAdmin.add
    //gameAdmin.clear
    //gameAdmin.list
    //gameAdmin.load
    //gameAdmin.remove
    //gameAdmin.save

    // Maplist
    void sendMapListAddCommand(const QString &level, const QString &gameMode, int rounds, int offSet = 0);
    void sendMapListAvailableMapsCommand(const QString &filter);
    void sendMapListEndRoundCommand(int teamId);
    void sendMapListGetMapIndicesCommand();
    void sendMapListGetRoundsCommand();
    void sendMapListSetNextMapIndexCommand(int index);

    // Player
    /// Differ from BF3?
    void sendPlayerIdleDurationCommand(const QString &player);
    void sendPlayerIsAliveCommand(const QString &player);
    void sendPlayerPingCommand(const QString &player);

    // Punkbuster
    void sendPunkBusterActivateCommand();
    void sendPunkBusterIsActiveCommand();

    // Reserved Slots
    void sendReservedSlotsListAddCommand(const QString &player);
    void sendReservedSlotsListAggressiveJoinCommand();
    void sendReservedSlotsListAggressiveJoinCommand(bool enabled);
    void sendReservedSlotsListClearCommand();
    void sendReservedSlotsListListCommand();
    void sendReservedSlotsListLoadCommand();
    void sendReservedSlotsListRemoveCommand(const QString &player);
    void sendReservedSlotsListSaveCommand();

    // Squad
    void sendSquadLeaderCommand();
    void sendSquadLeaderCommand(int teamId, int squadId, const QString &player);
    void sendSquadListActiveCommand(int teamId);
    void sendSquadListPlayersCommand(int teamId, int squadId);
    void sendSquadPrivateCommand();
    void sendSquadPrivateCommand(int teamId, int squadId, bool isPrivate);

    // Variables
    void sendVars3pCamCommand();
    void sendVars3pCamCommand(bool enabled);
    void sendVarsAutoBalanceCommand();
    void sendVarsAutoBalanceCommand(bool enabled);
    void sendVarsBulletDamageCommand(int damage = -1);
    void sendVarsGameModeCounterCommand(int scale = -1);
    void sendVarsHudCommand();
    void sendVarsHudCommand(bool enabled);
    void sendVarsIdleBanRoundsCommand(int rounds = -1);
    void sendVarsMaxPlayersCommand(int players = -1);
    void sendVarsNameTagCommand();
    void sendVarsNameTagCommand(bool enabled);
    void sendVarsOnlySquadLeaderSpawnCommand();
    void sendVarsOnlySquadLeaderSpawnCommand(bool enabled);
    void sendVarsPlayerRespawnTimeCommand(int respawnTime = -1);
    void sendVarsRegenerateHealthCommand();
    void sendVarsRegenerateHealthCommand(bool enabled);
    void sendVarsRoundLockdownCountdownCommand(int seconds = -1);
    void sendVarsRoundRestartPlayerCountCommand(int players = -1);
    void sendVarsRoundStartPlayerCountCommand(int players = -1);
    void sendVarsServerMessageCommand(const QString &message = QString());
    void sendVarsSoldierHealthCommand(int percent = -1);
    void sendVarsTeamKillKickForBanCommand(int count = -1);
    void sendVarsUnlockModeCommand(const QString &type = QString());
    void sendVarsVehicleSpawnAllowedCommand();
    void sendVarsVehicleSpawnAllowedCommand(bool enabled);
    void sendVarsVehicleSpawnDelayCommand(int percent = -1);
    //vars.gunMasterWeaponsPreset <index>

private:
    /* Parse events */
    void parseServerMaxPlayerCountChangeEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLevelLoadedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    /* Parse commands */
    // Admin
    void parseAdminHelpCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseAdminPasswordCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Game Admin
    //gameAdmin.add
    //gameAdmin.clear
    //gameAdmin.list
    //gameAdmin.load
    //gameAdmin.remove
    //gameAdmin.save

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    void parseMapListAvailableMapsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //mapList.endRound <teamId>
    void parseMapListGetMapIndicesCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseMapListGetRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF3?
    void parsePlayerIdleDurationCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerIsAliveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePlayerPingCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Punkbuster
    //punkBuster.activate
    void parsePunkBusterIsActiveCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Reserved Slots
    //reservedSlotsList.add <player name>
    void parseReservedSlotsListAggressiveJoinCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //reservedSlotsList.clear
    void parseReservedSlotsListListCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //reservedSlotsList.load
    //reservedSlotsList.remove <player name>
    //reservedSlotsList.save

    // Squad
    void parseSquadLeaderCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //squad.listActive <teamId>
    void parseSquadListPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseSquadPrivateCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    // Variables
    void parseVars3pCamCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsAutoBalanceCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsBulletDamageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsGameModeCounterCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsHudCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsIdleBanRoundsCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsNameTagCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsOnlySquadLeaderSpawnCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsPlayerRespawnTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRegenerateHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundLockdownCountdownCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundRestartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsRoundStartPlayerCountCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsServerMessageCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsSoldierHealthCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsTeamKillKickForBanCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsUnlockModeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsVehicleSpawnAllowedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseVarsVehicleSpawnDelayCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    //vars.gunMasterWeaponsPreset <index>

signals:
    /* Event signals */
    void onServerMaxPlayerCountChangeEvent(int count);
    void onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal);

    /* Command signals */
    // Admin
    void onAdminHelpCommand(const QStringList &commandList);
    void onAdminPasswordCommand(const QString &password);

    // Game Admin
    //gameAdmin.add
    //gameAdmin.clear
    //gameAdmin.list
    //gameAdmin.load
    //gameAdmin.remove
    //gameAdmin.save

    // Maplist
    //mapList.add <map> <gamemode> <rounds> <offset>
    void onMapListAvailableMapsCommand(const QString &value, const QStringList &list);
    //mapList.endRound <teamId>
    void onMapListGetMapIndicesCommand(int currentMapIndex, int nextMapIndex);
    void onMapListGetRoundsCommand(int currentRound, int totalRounds);
    //mapList.restartRound
    //mapList.runNextRound
    //mapList.setNextMapIndex <index>

    // Player
    /// Differ from BF3?
    void onPlayerIdleDurationCommand(float idleDuration);
    void onPlayerIsAliveCommand(bool alive);
    void onPlayerPingCommand(const QString &player, int ping);

    // Punkbuster
    //punkBuster.activate
    void onPunkBusterIsActiveCommand(bool active);

    // Reserved Slots
    //reservedSlotsList.add <player name>
    void onReservedSlotsListAggressiveJoinCommand(bool enabled);
    //reservedSlotsList.clear
    void onReservedSlotsListListCommand(const QStringList &reservedSlotList);
    //reservedSlotsList.load
    //reservedSlotsList.remove <player name>
    //reservedSlotsList.save

    // Squad
    void onSquadLeaderCommand(const QString &player);
    //squad.listActive <teamId>
    void onSquadListPlayersCommand(const QStringList &playerList);
    void onSquadPrivateCommand(bool isPrivate);

    // Variables
    void onVars3pCamCommand(bool enabled);
    void onVarsAutoBalanceCommand(bool enabled);
    void onVarsBulletDamageCommand(int percent);
    void onVarsGameModeCounterCommand(int percent);
    void onVarsHudCommand(bool enabled);
    void onVarsIdleBanRoundsCommand(int rounds);
    void onVarsMaxPlayersCommand(int playerCount);
    void onVarsNameTagCommand(bool enabled);
    void onVarsOnlySquadLeaderSpawnCommand(bool enabled);
    void onVarsPlayerRespawnTimeCommand(int respawnTime);
    void onVarsRegenerateHealthCommand(bool enabled);
    void onVarsRoundLockdownCountdownCommand(int seconds);
    void onVarsRoundRestartPlayerCountCommand(int players);
    void onVarsRoundStartPlayerCountCommand(int players);
    void onVarsServerMessageCommand(const QString &message);
    void onVarsSoldierHealthCommand(int health);
    void onVarsTeamKillKickForBanCommand(int count);
    void onVarsUnlockModeCommand(const Frostbite2UnlockModeEnum &unlockMode);
    void onVarsVehicleSpawnAllowedCommand(bool enabled);
    void onVarsVehicleSpawnDelayCommand(int delay);
    //vars.gunMasterWeaponsPreset <index>

};

#endif // FROSTBITE2COMMANDHANDLER_H
