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

#include "BF3LevelDictionary.h"
#include "TeamEntry.h"
#include "LevelEntry.h"
#include "GameModeEntry.h"
#include "GameModeLevel.h"

template<>
QList<TeamEntry> BF3LevelDictionary::teamList = {
    /* List of all teams */
    TeamEntry("Neutral"),                  // 0
    TeamEntry("US", ":/bf3/teams/RU.png"), // 1
    TeamEntry("RU", ":/bf3/teams/US.png")  // 2
};

template<>
QString BF3LevelDictionary::imagePath = ":/bf3/levels";

template<>
QList<LevelEntry> BF3LevelDictionary::levelList = {
    /* List of all levels */
    LevelEntry("MP_001",      "Grand Bazaar",        imagePath, "grand_bazaar.png"),        // 0
    LevelEntry("MP_003",      "Teheran Highway",     imagePath, "teheran_highway.png"),     // 1
    LevelEntry("MP_007",      "Caspian Border",      imagePath, "caspian_border.png"),      // 2
    LevelEntry("MP_011",      "Seine Crossing",      imagePath, "seine_crossing.png"),      // 3
    LevelEntry("MP_012",      "Operation Firestorm", imagePath, "operation_firestorm.png"), // 4
    LevelEntry("MP_013",      "Damavand Peak",       imagePath, "damavand_peak.png"),       // 5
    LevelEntry("MP_017",      "Noshahr Canals",      imagePath, "noshahr_canals.png"),      // 6
    LevelEntry("MP_018",      "Kharg Island",        imagePath, "kharg_island.png"),        // 7
    LevelEntry("MP_Subway",   "Operation Metro",     imagePath, "operation_metro.png"),     // 8

    // XP1 (Back to Karkand)
    LevelEntry("XP1_001",     "Strike at Karkand",   imagePath, "strike_at_karkand.png"),   // 9
    LevelEntry("XP1_002",     "Gulf of Oman",        imagePath, "gulf_of_oman.png"),        // 10
    LevelEntry("XP1_003",     "Sharqi Peninsula",    imagePath, "sharqi_peninsula.png"),    // 11
    LevelEntry("XP1_004",     "Wake Island",         imagePath, "wake_island.png"),         // 12

    // XP2 (Close Quarters)
    LevelEntry("XP2_Factory", "Scrapmetal",          imagePath, "scrapmetal.png"),          // 13
    LevelEntry("XP2_Office",  "Operation 925",       imagePath, "operation_925.png"),       // 14
    LevelEntry("XP2_Palace",  "Donya Fortress",      imagePath, "donya_fortress.png"),      // 15
    LevelEntry("XP2_Skybar",  "Ziba Tower",          imagePath, "ziba_tower.png"),          // 16

    // XP3 (Armored Kill)
    LevelEntry("XP3_Desert",  "Bandar Desert",       imagePath, "bandar_desert.png"),       // 17
    LevelEntry("XP3_Alborz",  "Alborz Mountains",    imagePath, "alborz_mountains.png"),    // 18
    LevelEntry("XP3_Shield",  "Armored Shield",      imagePath, "armored_shield.png"),      // 19
    LevelEntry("XP3_Valley",  "Death Valley",        imagePath, "death_valley.png"),        // 20

    // XP4 (Aftermath)
    LevelEntry("XP4_Quake",   "Epicenter",           imagePath, "epicenter.png"),           // 21
    LevelEntry("XP4_FD",      "Markaz Monolith",     imagePath, "markaz_monolith.png"),     // 22
    LevelEntry("XP4_Parl",    "Azadi Palace",        imagePath, "azadi_palace.png"),        // 23
    LevelEntry("XP4_Rubble",  "Talah Market",        imagePath, "talah_market.png"),        // 24

    // XP5 (Endgame)
    LevelEntry("XP5_001",     "Operation Riverside", imagePath, "operation_riverside.png"), // 25
    LevelEntry("XP5_002",     "Nebandan Flats",      imagePath, "nebandan_flats.png"),      // 26
    LevelEntry("XP5_003",     "Kiasar Railroad",     imagePath, "kiasar_railroad.png"),     // 27
    LevelEntry("XP5_004",     "Sabalan Pipeline",    imagePath, "sabalan_pipeline.png")     // 28
};

template<>
QList<GameModeEntry> BF3LevelDictionary::gameModeList = {
    /* List of all gamemodes */
    GameModeEntry("ConquestLarge0",        "Conquest Large",         64), // 0
    GameModeEntry("ConquestSmall0",        "Conquest Small",         32), // 1
    GameModeEntry("RushLarge0",            "Rush",                   32), // 2
    GameModeEntry("SquadRush0",            "Squad Rush",             8),  // 3
    GameModeEntry("SquadDeathMatch0",      "Squad Deathmatch",       16), // 4
    GameModeEntry("TeamDeathMatch0",       "Team Deathmatch",        24), // 5
    GameModeEntry("ConquestAssaultLarge0", "Conquest Assault Large", 64), // 6
    GameModeEntry("ConquestAssaultSmall0", "Conquest Assault Small", 32), // 7
    GameModeEntry("ConquestAssaultSmall1", "Conquest Assault Small", 32), // 8
    GameModeEntry("Domination0",           "Domination",             16), // 9
    GameModeEntry("GunMaster0",            "Gun master",             16), // 10
    GameModeEntry("TeamDeathMatchC0",      "TDM Close Quarters",     16), // 11
    GameModeEntry("TankSuperiority0",      "Tank Superiority",       24), // 12
    GameModeEntry("Scavenger0",            "Scavenger",              32), // 13
    GameModeEntry("CaptureTheFlag0",       "Capture The Flag",       32), // 14
    GameModeEntry("AirSuperiority0",       "Air Superiority",        24)  // 15
};

template<>
QList<GameModeLevel> BF3LevelDictionary::levelMap = {
    /* List of all levels and gamemodes combined */
    /* ConquestLarge0 */
    GameModeLevel(0, 0,  QList<int>({ 0, 0 })),
    GameModeLevel(0, 1,  QList<int>({ 0, 0 })),
    GameModeLevel(0, 2,  QList<int>({ 0, 0 })),
    GameModeLevel(0, 3,  QList<int>({ 0, 0 })),
    GameModeLevel(0, 4,  QList<int>({ 0, 0 })),
    GameModeLevel(0, 5,  QList<int>({ 0, 0 })),
    GameModeLevel(0, 6,  QList<int>({ 0, 0 })),
    GameModeLevel(0, 7,  QList<int>({ 0, 0 })),
    GameModeLevel(0, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevel(0, 10, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevel(0, 17, QList<int>({ 0, 0 })),
    GameModeLevel(0, 18, QList<int>({ 0, 0 })),
    GameModeLevel(0, 19, QList<int>({ 0, 0 })),
    GameModeLevel(0, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevel(0, 21, QList<int>({ 0, 0 })),
    GameModeLevel(0, 22, QList<int>({ 0, 0 })),
    GameModeLevel(0, 23, QList<int>({ 0, 0 })),
    GameModeLevel(0, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevel(0, 25, QList<int>({ 0, 0 })),
    GameModeLevel(0, 26, QList<int>({ 0, 0 })),
    GameModeLevel(0, 27, QList<int>({ 0, 0 })),
    GameModeLevel(0, 28, QList<int>({ 0, 0 })),

    /* ConquestSmall0 */
    GameModeLevel(1, 0,  QList<int>({ 0, 0 })),
    GameModeLevel(1, 1,  QList<int>({ 0, 0 })),
    GameModeLevel(1, 2,  QList<int>({ 0, 0 })),
    GameModeLevel(1, 3,  QList<int>({ 0, 0 })),
    GameModeLevel(1, 4,  QList<int>({ 0, 0 })),
    GameModeLevel(1, 5,  QList<int>({ 0, 0 })),
    GameModeLevel(1, 6,  QList<int>({ 0, 0 })),
    GameModeLevel(1, 7,  QList<int>({ 0, 0 })),
    GameModeLevel(1, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevel(1, 10, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevel(1, 17, QList<int>({ 0, 0 })),
    GameModeLevel(1, 18, QList<int>({ 0, 0 })),
    GameModeLevel(1, 19, QList<int>({ 0, 0 })),
    GameModeLevel(1, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevel(1, 21, QList<int>({ 0, 0 })),
    GameModeLevel(1, 22, QList<int>({ 0, 0 })),
    GameModeLevel(1, 23, QList<int>({ 0, 0 })),
    GameModeLevel(1, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevel(1, 25, QList<int>({ 0, 0 })),
    GameModeLevel(1, 26, QList<int>({ 0, 0 })),
    GameModeLevel(1, 27, QList<int>({ 0, 0 })),
    GameModeLevel(1, 28, QList<int>({ 0, 0 })),

    /* RushLarge0 */
    GameModeLevel(2, 0,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 1,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 2,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 3,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 4,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 5,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 6,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 7,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevel(2, 9,  QList<int>({ 0, 0 })),
    GameModeLevel(2, 10, QList<int>({ 0, 0 })),
    GameModeLevel(2, 11, QList<int>({ 0, 0 })),
    GameModeLevel(2, 12, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevel(2, 17, QList<int>({ 0, 0 })),
    GameModeLevel(2, 18, QList<int>({ 0, 0 })),
    GameModeLevel(2, 19, QList<int>({ 0, 0 })),
    GameModeLevel(2, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevel(2, 21, QList<int>({ 0, 0 })),
    GameModeLevel(2, 22, QList<int>({ 0, 0 })),
    GameModeLevel(2, 23, QList<int>({ 0, 0 })),
    GameModeLevel(2, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevel(2, 25, QList<int>({ 0, 0 })),
    GameModeLevel(2, 26, QList<int>({ 0, 0 })),
    GameModeLevel(2, 27, QList<int>({ 0, 0 })),
    GameModeLevel(2, 28, QList<int>({ 0, 0 })),

    /* SquadRush0 */
    GameModeLevel(3, 0,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 1,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 2,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 3,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 4,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 5,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 6,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 7,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevel(3, 9,  QList<int>({ 0, 0 })),
    GameModeLevel(3, 10, QList<int>({ 0, 0 })),
    GameModeLevel(3, 11, QList<int>({ 0, 0 })),
    GameModeLevel(3, 12, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevel(3, 17, QList<int>({ 0, 0 })),
    GameModeLevel(3, 18, QList<int>({ 0, 0 })),
    GameModeLevel(3, 19, QList<int>({ 0, 0 })),
    GameModeLevel(3, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevel(3, 21, QList<int>({ 0, 0 })),
    GameModeLevel(3, 22, QList<int>({ 0, 0 })),
    GameModeLevel(3, 23, QList<int>({ 0, 0 })),
    GameModeLevel(3, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevel(3, 25, QList<int>({ 0, 0 })),
    GameModeLevel(3, 26, QList<int>({ 0, 0 })),
    GameModeLevel(3, 27, QList<int>({ 0, 0 })),
    GameModeLevel(3, 28, QList<int>({ 0, 0 })),

    /* SquadDeathMatch0 */
    GameModeLevel(4, 0,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 1,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 2,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 3,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 4,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 5,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 6,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 7,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevel(4, 9,  QList<int>({ 0, 0 })),
    GameModeLevel(4, 10, QList<int>({ 0, 0 })),
    GameModeLevel(4, 11, QList<int>({ 0, 0 })),
    GameModeLevel(4, 12, QList<int>({ 0, 0 })),

    // XP2 (Close Quarters)
    GameModeLevel(4, 13, QList<int>({ 0, 0 })),
    GameModeLevel(4, 14, QList<int>({ 0, 0 })),
    GameModeLevel(4, 15, QList<int>({ 0, 0 })),
    GameModeLevel(4, 16, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevel(4, 17, QList<int>({ 0, 0 })),
    GameModeLevel(4, 18, QList<int>({ 0, 0 })),
    GameModeLevel(4, 19, QList<int>({ 0, 0 })),
    GameModeLevel(4, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevel(4, 21, QList<int>({ 0, 0 })),
    GameModeLevel(4, 22, QList<int>({ 0, 0 })),
    GameModeLevel(4, 23, QList<int>({ 0, 0 })),
    GameModeLevel(4, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevel(4, 25, QList<int>({ 0, 0 })),
    GameModeLevel(4, 26, QList<int>({ 0, 0 })),
    GameModeLevel(4, 27, QList<int>({ 0, 0 })),
    GameModeLevel(4, 28, QList<int>({ 0, 0 })),

    /* TeamDeathMatch0 */
    GameModeLevel(5, 0,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 1,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 2,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 3,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 4,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 5,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 6,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 7,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevel(5, 9,  QList<int>({ 0, 0 })),
    GameModeLevel(5, 10, QList<int>({ 0, 0 })),
    GameModeLevel(5, 11, QList<int>({ 0, 0 })),
    GameModeLevel(5, 12, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevel(5, 17, QList<int>({ 0, 0 })),
    GameModeLevel(5, 18, QList<int>({ 0, 0 })),
    GameModeLevel(5, 19, QList<int>({ 0, 0 })),
    GameModeLevel(5, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevel(5, 21, QList<int>({ 0, 0 })),
    GameModeLevel(5, 22, QList<int>({ 0, 0 })),
    GameModeLevel(5, 23, QList<int>({ 0, 0 })),
    GameModeLevel(5, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevel(5, 25, QList<int>({ 0, 0 })),
    GameModeLevel(5, 26, QList<int>({ 0, 0 })),
    GameModeLevel(5, 27, QList<int>({ 0, 0 })),
    GameModeLevel(5, 28, QList<int>({ 0, 0 })),

    /* ConquestAssaultLarge0 */

    // XP1 (Back to Karkand)
    GameModeLevel(6, 9,  QList<int>({ 0, 0 })),
    GameModeLevel(6, 11, QList<int>({ 0, 0 })),
    GameModeLevel(6, 12, QList<int>({ 0, 0 })),

    /* ConquestAssaultSmall0 */

    // XP1 (Back to Karkand)
    GameModeLevel(7, 9,  QList<int>({ 0, 0 })),
    GameModeLevel(7, 10, QList<int>({ 0, 0 })),
    GameModeLevel(7, 11, QList<int>({ 0, 0 })),
    GameModeLevel(7, 12, QList<int>({ 0, 0 })),

    /* ConquestAssaultSmall1 */

    // XP1 (Back to Karkand)
    GameModeLevel(8, 9,  QList<int>({ 0, 0 })),
    GameModeLevel(8, 11, QList<int>({ 0, 0 })),
    GameModeLevel(8, 12, QList<int>({ 0, 0 })),

    /* Domination0 */

    // XP1 (Close Quarters)
    GameModeLevel(9, 13, QList<int>({ 0, 0 })),
    GameModeLevel(9, 14, QList<int>({ 0, 0 })),
    GameModeLevel(9, 15, QList<int>({ 0, 0 })),
    GameModeLevel(9, 16, QList<int>({ 0, 0 })),

    /* GunMaster0 */

    // XP1 (Close Quarters)
    GameModeLevel(10, 13, QList<int>({ 0, 0 })),
    GameModeLevel(10, 14, QList<int>({ 0, 0 })),
    GameModeLevel(10, 15, QList<int>({ 0, 0 })),
    GameModeLevel(10, 16, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevel(10, 21, QList<int>({ 0, 0 })),
    GameModeLevel(10, 22, QList<int>({ 0, 0 })),
    GameModeLevel(10, 23, QList<int>({ 0, 0 })),
    GameModeLevel(10, 24, QList<int>({ 0, 0 })),

    /* TeamDeathMatchC0 */

    // XP1 (Close Quarters)
    GameModeLevel(11, 13, QList<int>({ 0, 0 })),
    GameModeLevel(11, 14, QList<int>({ 0, 0 })),
    GameModeLevel(11, 15, QList<int>({ 0, 0 })),
    GameModeLevel(11, 16, QList<int>({ 0, 0 })),

    /* TankSuperiority0 */

    // XP3 (Armored Kill)
    GameModeLevel(12, 17, QList<int>({ 0, 0 })),
    GameModeLevel(12, 18, QList<int>({ 0, 0 })),
    GameModeLevel(12, 19, QList<int>({ 0, 0 })),
    GameModeLevel(12, 20, QList<int>({ 0, 0 })),

    /* Scavenger0 */

    // XP4 (Aftermath)
    GameModeLevel(13, 21, QList<int>({ 0, 0 })),
    GameModeLevel(13, 22, QList<int>({ 0, 0 })),
    GameModeLevel(13, 23, QList<int>({ 0, 0 })),
    GameModeLevel(13, 24, QList<int>({ 0, 0 })),

    /* CaptureTheFlag0 */

    // XP5 (Endgame)
    GameModeLevel(14, 25, QList<int>({ 0, 0 })),
    GameModeLevel(14, 26, QList<int>({ 0, 0 })),
    GameModeLevel(14, 27, QList<int>({ 0, 0 })),
    GameModeLevel(14, 28, QList<int>({ 0, 0 })),

    /* AirSuperiority0 */

    // XP5 (Endgame)
    GameModeLevel(15, 25, QList<int>({ 0, 0 })),
    GameModeLevel(15, 26, QList<int>({ 0, 0 })),
    GameModeLevel(15, 27, QList<int>({ 0, 0 })),
    GameModeLevel(15, 28, QList<int>({ 0, 0 }))
};
