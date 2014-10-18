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
#include "GameModeLevelEntry.h"

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
QList<GameModeLevelEntry> BF3LevelDictionary::levelMap = {
    /* List of all levels and gamemodes combined */
    /* ConquestLarge0 */
    GameModeLevelEntry(0, 0,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 1,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 2,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 3,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 4,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 5,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 6,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 7,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevelEntry(0, 10, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevelEntry(0, 17, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 18, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 19, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevelEntry(0, 21, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 22, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 23, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevelEntry(0, 25, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 26, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 27, QList<int>({ 0, 0 })),
    GameModeLevelEntry(0, 28, QList<int>({ 0, 0 })),

    /* ConquestSmall0 */
    GameModeLevelEntry(1, 0,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 1,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 2,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 3,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 4,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 5,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 6,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 7,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevelEntry(1, 10, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevelEntry(1, 17, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 18, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 19, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevelEntry(1, 21, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 22, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 23, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevelEntry(1, 25, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 26, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 27, QList<int>({ 0, 0 })),
    GameModeLevelEntry(1, 28, QList<int>({ 0, 0 })),

    /* RushLarge0 */
    GameModeLevelEntry(2, 0,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 1,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 2,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 3,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 4,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 5,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 6,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 7,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevelEntry(2, 9,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 10, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 11, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 12, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevelEntry(2, 17, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 18, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 19, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevelEntry(2, 21, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 22, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 23, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevelEntry(2, 25, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 26, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 27, QList<int>({ 0, 0 })),
    GameModeLevelEntry(2, 28, QList<int>({ 0, 0 })),

    /* SquadRush0 */
    GameModeLevelEntry(3, 0,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 1,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 2,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 3,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 4,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 5,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 6,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 7,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevelEntry(3, 9,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 10, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 11, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 12, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevelEntry(3, 17, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 18, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 19, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevelEntry(3, 21, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 22, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 23, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevelEntry(3, 25, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 26, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 27, QList<int>({ 0, 0 })),
    GameModeLevelEntry(3, 28, QList<int>({ 0, 0 })),

    /* SquadDeathMatch0 */
    GameModeLevelEntry(4, 0,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 1,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 2,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 3,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 4,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 5,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 6,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 7,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevelEntry(4, 9,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 10, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 11, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 12, QList<int>({ 0, 0 })),

    // XP2 (Close Quarters)
    GameModeLevelEntry(4, 13, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 14, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 15, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 16, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevelEntry(4, 17, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 18, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 19, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevelEntry(4, 21, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 22, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 23, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevelEntry(4, 25, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 26, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 27, QList<int>({ 0, 0 })),
    GameModeLevelEntry(4, 28, QList<int>({ 0, 0 })),

    /* TeamDeathMatch0 */
    GameModeLevelEntry(5, 0,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 1,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 2,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 3,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 4,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 5,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 6,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 7,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 8,  QList<int>({ 0, 0 })),

    // XP1 (Back to Karkand)
    GameModeLevelEntry(5, 9,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 10, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 11, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 12, QList<int>({ 0, 0 })),

    // XP3 (Armored Kill)
    GameModeLevelEntry(5, 17, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 18, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 19, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 20, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevelEntry(5, 21, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 22, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 23, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 24, QList<int>({ 0, 0 })),

    // XP5 (Endgame)
    GameModeLevelEntry(5, 25, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 26, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 27, QList<int>({ 0, 0 })),
    GameModeLevelEntry(5, 28, QList<int>({ 0, 0 })),

    /* ConquestAssaultLarge0 */

    // XP1 (Back to Karkand)
    GameModeLevelEntry(6, 9,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(6, 11, QList<int>({ 0, 0 })),
    GameModeLevelEntry(6, 12, QList<int>({ 0, 0 })),

    /* ConquestAssaultSmall0 */

    // XP1 (Back to Karkand)
    GameModeLevelEntry(7, 9,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(7, 10, QList<int>({ 0, 0 })),
    GameModeLevelEntry(7, 11, QList<int>({ 0, 0 })),
    GameModeLevelEntry(7, 12, QList<int>({ 0, 0 })),

    /* ConquestAssaultSmall1 */

    // XP1 (Back to Karkand)
    GameModeLevelEntry(8, 9,  QList<int>({ 0, 0 })),
    GameModeLevelEntry(8, 11, QList<int>({ 0, 0 })),
    GameModeLevelEntry(8, 12, QList<int>({ 0, 0 })),

    /* Domination0 */

    // XP1 (Close Quarters)
    GameModeLevelEntry(9, 13, QList<int>({ 0, 0 })),
    GameModeLevelEntry(9, 14, QList<int>({ 0, 0 })),
    GameModeLevelEntry(9, 15, QList<int>({ 0, 0 })),
    GameModeLevelEntry(9, 16, QList<int>({ 0, 0 })),

    /* GunMaster0 */

    // XP1 (Close Quarters)
    GameModeLevelEntry(10, 13, QList<int>({ 0, 0 })),
    GameModeLevelEntry(10, 14, QList<int>({ 0, 0 })),
    GameModeLevelEntry(10, 15, QList<int>({ 0, 0 })),
    GameModeLevelEntry(10, 16, QList<int>({ 0, 0 })),

    // XP4 (Aftermath)
    GameModeLevelEntry(10, 21, QList<int>({ 0, 0 })),
    GameModeLevelEntry(10, 22, QList<int>({ 0, 0 })),
    GameModeLevelEntry(10, 23, QList<int>({ 0, 0 })),
    GameModeLevelEntry(10, 24, QList<int>({ 0, 0 })),

    /* TeamDeathMatchC0 */

    // XP1 (Close Quarters)
    GameModeLevelEntry(11, 13, QList<int>({ 0, 0 })),
    GameModeLevelEntry(11, 14, QList<int>({ 0, 0 })),
    GameModeLevelEntry(11, 15, QList<int>({ 0, 0 })),
    GameModeLevelEntry(11, 16, QList<int>({ 0, 0 })),

    /* TankSuperiority0 */

    // XP3 (Armored Kill)
    GameModeLevelEntry(12, 17, QList<int>({ 0, 0 })),
    GameModeLevelEntry(12, 18, QList<int>({ 0, 0 })),
    GameModeLevelEntry(12, 19, QList<int>({ 0, 0 })),
    GameModeLevelEntry(12, 20, QList<int>({ 0, 0 })),

    /* Scavenger0 */

    // XP4 (Aftermath)
    GameModeLevelEntry(13, 21, QList<int>({ 0, 0 })),
    GameModeLevelEntry(13, 22, QList<int>({ 0, 0 })),
    GameModeLevelEntry(13, 23, QList<int>({ 0, 0 })),
    GameModeLevelEntry(13, 24, QList<int>({ 0, 0 })),

    /* CaptureTheFlag0 */

    // XP5 (Endgame)
    GameModeLevelEntry(14, 25, QList<int>({ 0, 0 })),
    GameModeLevelEntry(14, 26, QList<int>({ 0, 0 })),
    GameModeLevelEntry(14, 27, QList<int>({ 0, 0 })),
    GameModeLevelEntry(14, 28, QList<int>({ 0, 0 })),

    /* AirSuperiority0 */

    // XP5 (Endgame)
    GameModeLevelEntry(15, 25, QList<int>({ 0, 0 })),
    GameModeLevelEntry(15, 26, QList<int>({ 0, 0 })),
    GameModeLevelEntry(15, 27, QList<int>({ 0, 0 })),
    GameModeLevelEntry(15, 28, QList<int>({ 0, 0 }))
};
