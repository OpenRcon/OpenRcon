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

#include "BF4Client.h"
#include "ServerEntry.h"

BF4Client::BF4Client(ServerEntry *serverEntry, QObject *parent) :
    Frostbite2Client(serverEntry, new BF4CommandHandler(parent), parent)
{
    versionMap = {
        { 70517,  "OB-R2" },
        { 72879,  "OB-R3" },
        { 77582,  "OB-R4" },
        { 87884,  "R4" },
        { 88031,  "R5" },
        { 88058,  "R6" },
        { 88472,  "R7" },
        { 89702,  "R8" },
        { 90165,  "R9" },
        { 90519,  "R10" },
        { 91697,  "R11" },
        { 93111,  "R12" },
        { 94318,  "R13" },
        { 95851,  "R14" },
        { 96245,  "R15" },
        { 97870,  "R16" },
        { 99392,  "R17" },
        { 101684, "R18" },
        { 102560, "R19" },
        { 103064, "R20" },
        { 106318, "R21" },
        { 106533, "R22" },
        { 107145, "R23" },
        { 107436, "R24" },
        { 108751, "R25" },
        { 109758, "R26" },
        { 111118, "R27" },
        { 112943, "R28" },
        { 114240, "R29" },
        { 115397, "R30" },
        { 117719, "R31" },
        { 120511, "R32" },
        { 125871, "R33" },
        { 126936, "R34" },
        { 130790, "R35" },
        { 133337, "R36" },
        { 135082, "R37" },
        { 136921, "R38" },
        { 138571, "R39" },
        { 139796, "R40" },
        { 140136, "R41" },
        { 147837, "R42" },
        { 150767, "R43" },
        { 154100, "R44" },
        { 154793, "R45" },
        { 155011, "R46" },
        { 157186, "R48" },
        { 158113, "R49" },
        { 162016, "R50" },
        { 165241, "R51" },
        { 166185, "R52" },
        { 171730, "R53" },
        { 176744, "R55" },
        { 177035, "R56" },
        { 179171, "R58" }
    };
}


BF4Client::~BF4Client()
{

}
