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

#include "FrostbiteWidget.h"

FrostbiteWidget::FrostbiteWidget(FrostbiteClient *client, QWidget *parent) :
    GameWidget(client, parent)
{
    commandList += {
        "login.plainText",
        "login.hashed",
        "serverInfo",
        "logout",
        "quit",
        "version",
        "listPlayers",
        "admin.kickPlayer",
        "admin.killPlayer",
        "admin.listPlayers",
        "admin.movePlayer",
        "admin.say",
        "admin.yell",
        "banList.add",
        "banList.clear",
        "banList.list",
        "banList.load",
        "banList.remove",
        "banList.save",
        "mapList.clear",
        "mapList.list",
        "mapList.load",
        "mapList.remove",
        "mapList.save",
        "punkBuster.pb_sv_command",
        "vars.3dSpotting",
        "vars.friendlyFire",
        "vars.gamePassword",
        "vars.idleTimeout",
        "vars.killCam",
        "vars.miniMap",
        "vars.miniMapSpotting",
        "vars.serverDescription",
        "vars.serverName",
        "vars.teamKillCountForKick",
        "vars.teamKillValueDecreasePerSecond",
        "vars.teamKillValueForKick",
        "vars.teamKillValueIncrease"
    };
}

FrostbiteWidget::~FrostbiteWidget()
{

}
