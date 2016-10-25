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

#include "BF3Client.h"

BF3Client::BF3Client(ServerEntry *serverEntry, QObject *parent) :
    Frostbite2Client(serverEntry, parent)
{
    versionMap = {
        { 872601,  "OB-E" },
        { 873274,  "OB-F" },
        { 879322,  "R3" },
        { 879793,  "R4" },
        { 881071,  "R5" },
        { 882210,  "R6" },
        { 883137,  "R7" },
        { 883971,  "R8" },
        { 886605,  "R9" },
        { 888890,  "R10" },
        { 892188,  "R11" },
        { 893642,  "R12" },
        { 894307,  "R13" },
        { 894565,  "R14" },
        { 895012,  "R15" },
        { 895921,  "R16" },
        { 896646,  "R17" },
        { 903227,  "R19" },
        { 926998,  "R20" },
        { 933688,  "R21" },
        { 940924,  "R22" },
        { 948577,  "R23" },
        { 951336,  "R24" },
        { 951364,  "R25" },
        { 964189,  "R26" },
        { 972386,  "R27" },
        { 981883,  "R28" },
        { 1000930, "R29" },
        { 1009356, "R30" },
        { 1014305, "R31" },
        { 1028652, "R32" },
        { 1043704, "R32 1/2" },
        { 1055290, "R33" },
        { 1066226, "R34" },
        { 1075133, "R34log" },
        { 1097264, "R35" },
        { 1125745, "R36" },
        { 1139617, "R37" },
        { 1149977, "R38" }
    };
}

BF3Client::~BF3Client()
{
    //delete commandHandler;
}
