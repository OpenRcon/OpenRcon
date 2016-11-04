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

#include "BFBC2Widget.h"

BFBC2Widget::BFBC2Widget(BFBC2Client *client, QWidget *parent) :
    FrostbiteWidget(client, parent)
{
    commandList += {
        "eventsEnabled",
        "help",
        "admin.runscript",
        "admin.runNextRound",
        "admin.restartRound",
        "admin.endRound",
        "admin.currentLevel",
        "admin.supportedMaps",
        "admin.setPlaylist",
        "admin.getPlaylist",
        "admin.getPlaylists",
        "mapList.append",
        "mapList.insert",
        "mapList.nextLevelIndex",
        "reservedSlots.load",
        "reservedSlots.save",
        "reservedSlots.addPlayer",
        "reservedSlots.removePlayer",
        "reservedSlots.clear",
        "reservedSlots.list",
        "vars.adminPassword",
        "vars.punkBuster",
        "vars.hardCore",
        "vars.ranked",
        "vars.rankLimit",
        "vars.teamBalance",
        "vars.currentPlayerLimit",
        "vars.maxPlayerLimit",
        "vars.playerLimit",
        "vars.bannerUrl",
        "vars.crossHair",
        "vars.thirdPersonVehicleCameras",
        "vars.profanityFilter",
        "vars.textChatModerationMode",
        "vars.textChatSpamTriggerCount",
        "vars.textChatSpamDetectionTime",
        "vars.textChatSpamCoolDownTime",
        "textChatModerationList.load",
        "textChatModerationList.save",
        "textChatModerationList.add",
        "textChatModerationList.remove",
        "textChatModerationList.clear",
        "textChatModerationList.list",
        "levelVars.set",
        "levelVars.get",
        "levelVars.evaluate",
        "levelVars.clear",
        "levelVars.list"
    };
}

BFBC2Widget::~BFBC2Widget()
{

}
