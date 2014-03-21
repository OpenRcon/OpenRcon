/*
 * Copyright (C) 2010 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY); without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BFBC2CommandList.h"

BFBC2CommandList::BFBC2CommandList(QObject *parent) : QObject(parent)
{
    commandList.append("login.plainText");
    commandList.append("login.hashed");
    commandList.append("login.hashed ");
    commandList.append("logout");
    commandList.append("quit");
    commandList.append("version");
    commandList.append("listPlayers ");
    commandList.append("eventsEnabled ");
    commandList.append("help");
    commandList.append("admin.runscript ");
    commandList.append("punkBuster.pb_sv_command ");
    commandList.append("serverInfo");
    commandList.append("admin.yell ");
    commandList.append("admin.say ");
    commandList.append("admin.runNextRound");
    commandList.append("admin.restartRound");
    commandList.append("admin.endRound ");
    commandList.append("admin.runNextLevel");
    commandList.append("admin.restartMap");
    commandList.append("admin.currentLevel");
    commandList.append("mapList.nextLevelIndex ");
    commandList.append("admin.supportedMaps ");
    commandList.append("admin.setPlaylist ");
    commandList.append("admin.getPlaylist");
    commandList.append("admin.getPlaylists");
    commandList.append("admin.kickPlayer ");
    commandList.append("admin.listPlayers ");
    commandList.append("admin.movePlayer ");
    commandList.append("admin.killPlayer ");
    commandList.append("vars.textChatSpamTriggerCount ");
    commandList.append("vars.textChatSpamDetectionTime ");
    commandList.append("vars.textChatSpamCoolDownTime ");
    commandList.append("textChatModerationList.load");
    commandList.append("textChatModerationList.save");
    commandList.append("textChatModerationList.add ");
    commandList.append("textChatModerationList.remove ");
    commandList.append("textChatModerationList.clear");
    commandList.append("textChatModerationList.list ");
    commandList.append("banList.load");
    commandList.append("banList.save");
    commandList.append("banList.add ");
    commandList.append("banList.remove ");
    commandList.append("banList.clear");
    commandList.append("banList.list ");
    commandList.append("reservedSlots.load");
    commandList.append("reservedSlots.save");
    commandList.append("reservedSlots.addPlayer ");
    commandList.append("reservedSlots.removePlayer ");
    commandList.append("reservedSlots.clear");
    commandList.append("reservedSlots.list");
    commandList.append("mapList.load");
    commandList.append("mapList.save");
    commandList.append("mapList.list ");
    commandList.append("mapList.clear");
    commandList.append("mapList.remove ");
    commandList.append("mapList.append ");
    commandList.append("mapList.insert ");
    commandList.append("vars.serverName ");
    commandList.append("vars.adminPassword ");
    commandList.append("vars.gamePassword ");
    commandList.append("vars.punkBuster ");
    commandList.append("vars.hardCore");
    commandList.append("vars.ranked");
    commandList.append("vars.rankLimit ");
    commandList.append("vars.teamBalance ");
    commandList.append("vars.friendlyFire ");
    commandList.append("vars.currentPlayerLimit");
    commandList.append("vars.maxPlayerLimit");
    commandList.append("vars.playerLimit ");
    commandList.append("vars.bannerUrl ");
    commandList.append("vars.serverDescription ");
    commandList.append("vars.killCam ");
    commandList.append("vars.miniMap ");
    commandList.append("vars.crossHair ");
    commandList.append("vars.3dSpotting ");
    commandList.append("vars.miniMapSpotting ");
    commandList.append("vars.thirdPersonVehicleCameras ");
    commandList.append("vars.teamKillCountForKick ");
    commandList.append("vars.teamKillValueForKick ");
    commandList.append("vars.teamKillValueIncrease ");
    commandList.append("vars.teamKillValueDecreasePerSecond ");
    commandList.append("vars.idleTimeout ");
    commandList.append("vars.profanityFilter ");
    commandList.append("levelVars.set ");
    commandList.append("levelVars.get ");
    commandList.append("levelVars.evaluate ");
    commandList.append("levelVars.clear ");
    commandList.append("levelVars.list ");
}
