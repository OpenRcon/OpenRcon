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

#include "Frostbite2Widget.h"

Frostbite2Widget::Frostbite2Widget(Frostbite2Client *client, QWidget *parent) :
    FrostbiteWidget(client, parent)
{
    commandList += {
        "currentLevel",
        "admin.eventsEnabled",
        "admin.help",
        "admin.password",
        "mapList.add",
        "mapList.availableMaps",
        "mapList.endRound",
        "mapList.getMapIndices",
        "mapList.getRounds",
        "mapList.restartRound",
        "mapList.runNextRound",
        "mapList.setNextMapIndex",
        "player.idleDuration",
        "player.isAlive",
        "player.ping",
        "punkBuster.activate",
        "punkBuster.isActive",
        "reservedSlotsList.add",
        "reservedSlotsList.aggressiveJoin",
        "reservedSlotsList.clear",
        "reservedSlotsList.list",
        "reservedSlotsList.load",
        "reservedSlotsList.remove",
        "reservedSlotsList.save",
        "squad.leader",
        "squad.listActive",
        "squad.listPlayers",
        "squad.private",
        "vars.3pCam",
        "vars.autoBalance",
        "vars.bulletDamage",
        "vars.gameModeCounter",
        "vars.hud",
        "vars.idleBanRounds",
        "vars.maxPlayers",
        "vars.nameTag",
        "vars.onlySquadLeaderSpawn",
        "vars.playerRespawnTime",
        "vars.regenerateHealth",
        "vars.roundLockdownCountdown",
        "vars.roundRestartPlayerCount",
        "vars.roundStartPlayerCount",
        "vars.serverMessage",
        "vars.soldierHealth",
        "vars.teamKillKickForBan",
        "vars.unlockMode",
        "vars.vehicleSpawnAllowed",
        "vars.vehicleSpawnAllowed",
        "vars.vehicleSpawnDelay",
        "vars.gunMasterWeaponsPreset"
    };
}

Frostbite2Widget::~Frostbite2Widget()
{

}
