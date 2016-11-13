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

#include "BFBC2Client.h"

BFBC2Client::BFBC2Client(ServerEntry *serverEntry, QObject *parent) :
    FrostbiteClient(serverEntry, new BFBC2CommandHandler(), parent)
{
    versionMap = {
        { 571287, "R21" },
        { 581637, "R22" },
        { 584642, "R23" },
        { 593485, "R24" },
        { 602833, "R25" },
        { 609063, "R26" },
        { 617877, "R27" },
        { 621775, "R28" },
        { 638140, "R30" },
        { 720174, "R32" },
        { 851434, "R34" }
    };
}

BFBC2Client::~BFBC2Client()
{

}
