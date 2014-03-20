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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BFBC2CommandList.h"

BFBC2CommandList::BFBC2CommandList(QObject *parent) : QObject(parent)
{
    commandList << "login.plainText";
    commandList << "login.hashed";
    commandList << "login.hashed ";
    commandList << "logout";
    commandList << "quit";
    commandList << "version";
    commandList << "listPlayers ";
    commandList << "eventsEnabled ";
    commandList << "help";
    commandList << "admin.runscript ";
    commandList << "punkBuster.pb_sv_command ";
    commandList << "serverInfo";
    commandList << "admin.yell ";
    commandList << "admin.say ";
    commandList << "admin.runNextRound";
    commandList << "admin.restartRound";
    commandList << "admin.endRound ";
    commandList << "admin.runNextLevel";
    commandList << "admin.restartMap";
    commandList << "admin.currentLevel";
    commandList << "mapList.nextLevelIndex ";
    commandList << "admin.supportedMaps ";
    commandList << "admin.setPlaylist ";
    commandList << "admin.getPlaylist";
    commandList << "admin.getPlaylists";
    commandList << "admin.kickPlayer ";
    commandList << "admin.listPlayers ";
    commandList << "admin.movePlayer ";
    commandList << "admin.killPlayer ";
    commandList << "vars.textChatSpamTriggerCount ";
    commandList << "vars.textChatSpamDetectionTime ";
    commandList << "vars.textChatSpamCoolDownTime ";
    commandList << "textChatModerationList.load";
    commandList << "textChatModerationList.save";
    commandList << "textChatModerationList.add ";
    commandList << "textChatModerationList.remove ";
    commandList << "textChatModerationList.clear";
    commandList << "textChatModerationList.list ";
    commandList << "banList.load";
    commandList << "banList.save";
    commandList << "banList.add ";
    commandList << "banList.remove ";
    commandList << "banList.clear";
    commandList << "banList.list ";
    commandList << "reservedSlots.load";
    commandList << "reservedSlots.save";
    commandList << "reservedSlots.addPlayer ";
    commandList << "reservedSlots.removePlayer ";
    commandList << "reservedSlots.clear";
    commandList << "reservedSlots.list";
    commandList << "mapList.load";
    commandList << "mapList.save";
    commandList << "mapList.list ";
    commandList << "mapList.clear";
    commandList << "mapList.remove ";
    commandList << "mapList.append ";
    commandList << "mapList.insert ";
    commandList << "vars.serverName ";
    commandList << "vars.adminPassword ";;
    commandList << "vars.gamePassword ";
    commandList << "vars.punkBuster ";
    commandList << "vars.hardCore";
    commandList << "vars.ranked";
    commandList << "vars.rankLimit ";
    commandList << "vars.teamBalance ";
    commandList << "vars.friendlyFire ";
    commandList << "vars.currentPlayerLimit";
    commandList << "vars.maxPlayerLimit";
    commandList << "vars.playerLimit ";
    commandList << "vars.bannerUrl ";
    commandList << "vars.serverDescription ";
    commandList << "vars.killCam ";
    commandList << "vars.miniMap ";
    commandList << "vars.crossHair ";
    commandList << "vars.3dSpotting ";
    commandList << "vars.miniMapSpotting ";
    commandList << "vars.thirdPersonVehicleCameras ";
    commandList << "vars.teamKillCountForKick ";
    commandList << "vars.teamKillValueForKick ";
    commandList << "vars.teamKillValueIncrease ";
    commandList << "vars.teamKillValueDecreasePerSecond ";
    commandList << "vars.idleTimeout ";
    commandList << "vars.profanityFilter ";
    commandList << "levelVars.set ";
    commandList << "levelVars.get ";
    commandList << "levelVars.evaluate ";
    commandList << "levelVars.clear ";
    commandList << "levelVars.list ";
}
