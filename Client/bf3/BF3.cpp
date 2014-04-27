/*
 * Copyright (C) 2014 The OpenRcon Project.
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

#include "BF3.h"

BF3::BF3(const QString &host, const int &port, const QString &password) : FrostbiteGame(host, port, password)
{
    con = new BF3Connection(this);
    con->hostConnect(host, port);

    levels = new BF3Levels(this);

    versionMap.insert(872601, "OB-E");
    versionMap.insert(873274, "OB-F");
    versionMap.insert(879322, "R-3");
    versionMap.insert(879793, "R-4");
    versionMap.insert(881071, "R-5");
    versionMap.insert(882210, "R-6");
    versionMap.insert(883137, "R-7");
    versionMap.insert(883971, "R-8");
    versionMap.insert(886605, "R-9");
    versionMap.insert(888890, "R-10");
    versionMap.insert(892188, "R-11");
    versionMap.insert(893642, "R-12");
    versionMap.insert(894307, "R-13");
    versionMap.insert(894565, "R-14");
    versionMap.insert(895012, "R-15");
    versionMap.insert(895921, "R-16");
    versionMap.insert(896646, "R-17");
    versionMap.insert(903227, "R-19");
    versionMap.insert(926998, "R-20");
    versionMap.insert(933688, "R-21");
    versionMap.insert(940924, "R-22");
    versionMap.insert(948577, "R-23");
    versionMap.insert(951336, "R-24");
    versionMap.insert(951364, "R-25");
    versionMap.insert(964189, "R-26");
    versionMap.insert(972386, "R-27");
    versionMap.insert(981883, "R-28");
    versionMap.insert(1000930, "R-29");
    versionMap.insert(1009356, "R-30");
    versionMap.insert(1014305, "R-31");
    versionMap.insert(1028652, "R-32");
    versionMap.insert(1043704, "R-32 1/2");
    versionMap.insert(1055290, "R-33");
    versionMap.insert(1066226, "R-34");
    versionMap.insert(1075133, "R-34log");
    versionMap.insert(1097264, "R-35");
    versionMap.insert(1125745, "R-36");
    versionMap.insert(1139617, "R-37");
    versionMap.insert(1149977, "R-38");
}

BF3::~BF3()
{
    delete con;
    delete levels;
}
