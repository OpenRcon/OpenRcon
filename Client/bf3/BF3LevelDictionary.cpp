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

template<>
QList<LevelEntry> BF3LevelDictionary::levelList = {
    /* List of all levels */
    LevelEntry("MP_001", "Grand Bazaar", 0, 0, ":/bf3/levels/grand_bazaar.png"),                  // 0
    LevelEntry("MP_003", "Teheran Highway", 0, 0, ":/bf3/levels/teheran_highway.png"),            // 1
    LevelEntry("MP_007", "Caspian Border", 0, 0, ":/bf3/levels/caspian_border.png"),              // 2
    LevelEntry("MP_011", "Seine Crossing", 0, 0, ":/bf3/levels/seine_crossing.png"),              // 3
    LevelEntry("MP_012", "Operation Firestorm", 0, 0, ":/bf3/levels/operation_firestorm.png"),    // 4
    LevelEntry("MP_013", "Damavand Peak", 0, 0, ":/bf3/levels/damavand_peak.png"),                // 5
    LevelEntry("MP_017", "Noshahr Canals", 0, 0, ":/bf3/levels/noshahr_canals.png"),              // 6
    LevelEntry("MP_018", "Kharg Island", 0, 0, ":/bf3/levels/kharg_island.png"),                  // 7
    LevelEntry("MP_Subway", "Operation Metro", 0, 0, ":/bf3/levels/operation_metro.png"),         // 8

    // XP1 (Back to Karkand)
    LevelEntry("XP1_001", "Strike at Karkand", 0, 0, ":/bf3/levels/strike_at_karkand.png"),       // 9
    LevelEntry("XP1_002", "Gulf of Oman", 0, 0, ":/bf3/levels/gulf_of_oman.png"),                 // 10
    LevelEntry("XP1_003", "Sharqi Peninsula", 0, 0, ":/bf3/levels/sharqi_peninsula.png"),         // 11
    LevelEntry("XP1_004", "Wake Island", 0, 0, ":/bf3/levels/wake_island.png"),                   // 12

    // XP2 (Close Quarters)
    LevelEntry("XP2_Factory", "Scrapmetal", 0, 0, ":/bf3/levels/scrapmetal.png"),                 // 13
    LevelEntry("XP2_Office", "Operation 925", 0, 0, ":/bf3/levels/operation_925.png"),            // 14
    LevelEntry("XP2_Palace", "Donya Fortress", 0, 0, ":/bf3/levels/donya_fortress.png"),          // 15
    LevelEntry("XP2_Skybar", "Ziba Tower", 0, 0, ":/bf3/levels/ziba_tower.png"),                  // 16

    // XP3 (Armored Kill)
    LevelEntry("XP3_Desert", "Bandar Desert", 0, 0, ":/bf3/levels/bandar_desert.png"),            // 17
    LevelEntry("XP3_Alborz", "Alborz Mountains", 0, 0, ":/bf3/levels/alborz_mountains.png"),      // 18
    LevelEntry("XP3_Shield", "Armored Shield", 0, 0, ":/bf3/levels/armored_shield.png"),          // 19
    LevelEntry("XP3_Valley", "Death Valley", 0, 0, ":/bf3/levels/death_valley.png"),              // 20

    // XP4 (Aftermath)
    LevelEntry("XP4_Quake", "Epicenter", 0, 0, ":/bf3/levels/epicenter.png"),                     // 21
    LevelEntry("XP4_FD", "Markaz Monolith", 0, 0, ":/bf3/levels/markaz_monolith.png"),            // 22
    LevelEntry("XP4_Parl", "Azadi Palace", 0, 0, ":/bf3/levels/azadi_palace.png"),                // 23
    LevelEntry("XP4_Rubble", "Talah Market", 0, 0, ":/bf3/levels/talah_market.png"),              // 24

    // XP5 (Endgame)
    LevelEntry("XP5_001", "Operation Riverside", 0, 0, ":/bf3/levels/operation_riverside.png"),   // 25
    LevelEntry("XP5_002", "Nebandan Flats", 0, 0, ":/bf3/levels/nebandan_flats.png"),             // 26
    LevelEntry("XP5_003", "Kiasar Railroad", 0, 0, ":/bf3/levels/kiasar_railroad.png"),           // 27
    LevelEntry("XP5_004", "Sabalan Pipeline", 0, 0, ":/bf3/levels/sabalan_pipeline.png")          // 28
};

template<>
QList<GameModeEntry> BF3LevelDictionary::gameModeList = {
    /* List of all gamemodes */
    GameModeEntry("ConquestLarge0", "Conquest Large", 64),                // 0
    GameModeEntry("ConquestSmall0", "Conquest Small", 32),                // 1
    GameModeEntry("RushLarge0", "Rush", 32),                              // 2
    GameModeEntry("SquadRush0", "Squad Rush", 8),                         // 3
    GameModeEntry("SquadDeathMatch0", "Squad Deathmatch", 16),            // 4
    GameModeEntry("TeamDeathMatch0", "Team Deathmatch", 24),              // 5
    GameModeEntry("ConquestAssaultLarge0", "Conquest Assault Large", 64), // 6
    GameModeEntry("ConquestAssaultSmall0", "Conquest Assault Small", 32), // 7
    GameModeEntry("ConquestAssaultSmall1", "Conquest Assault Small", 32), // 8
    GameModeEntry("Domination0", "Domination", 16),                       // 9
    GameModeEntry("GunMaster0", "Gun master", 16),                        // 10
    GameModeEntry("TeamDeathMatchC0", "TDM Close Quarters", 16),          // 11
    GameModeEntry("TankSuperiority0", "Tank Superiority", 24),            // 12
    GameModeEntry("Scavenger0", "Scavenger", 32),                         // 13
    GameModeEntry("CaptureTheFlag0", "Capture The Flag", 32),             // 14
    GameModeEntry("AirSuperiority0", "Air Superiority", 24)               // 15
};

// TODO: More teams here?
template<>
QStringList BF3LevelDictionary::teamList = {
    "US",
    "RU"
};

template<>
QHash<int, int> BF3LevelDictionary::levelMap = {
    /* Levels and gamemodes combined */

    /* ConquestLarge0 */
    { 0, 0 },
    { 0, 1 },
    { 0, 2 },
    { 0, 3 },
    { 0, 4 },
    { 0, 5 },
    { 0, 6 },
    { 0, 7 },
    { 0, 8 },

    // XP1 (Back to Karkand)
    { 0, 10 },

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    { 0, 17 },
    { 0, 18 },
    { 0, 19 },
    { 0, 20 },

    // XP4 (Aftermath)
    { 0, 21 },
    { 0, 22 },
    { 0, 23 },
    { 0, 24 },

    // XP5 (Endgame)
    { 0, 25 },
    { 0, 26 },
    { 0, 27 },
    { 0, 28 },

    /* ConquestSmall0 */
    { 1, 0 },
    { 1, 1 },
    { 1, 2 },
    { 1, 3 },
    { 1, 4 },
    { 1, 5 },
    { 1, 6 },
    { 1, 7 },
    { 1, 8 },

    // XP1 (Back to Karkand)
    { 1, 10 },

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    { 1, 17 },
    { 1, 18 },
    { 1, 19 },
    { 1, 20 },

    // XP4 (Aftermath)
    { 1, 21 },
    { 1, 22 },
    { 1, 23 },
    { 1, 24 },

    // XP5 (Endgame)
    { 1, 25 },
    { 1, 26 },
    { 1, 27 },
    { 1, 28 },

    /* RushLarge0 */
    { 2, 0 },
    { 2, 1 },
    { 2, 2 },
    { 2, 3 },
    { 2, 4 },
    { 2, 5 },
    { 2, 6 },
    { 2, 7 },
    { 2, 8 },

    // XP1 (Back to Karkand)
    { 2, 9 },
    { 2, 10 },
    { 2, 11 },
    { 2, 12 },

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    { 2, 17 },
    { 2, 18 },
    { 2, 19 },
    { 2, 20 },

    // XP4 (Aftermath)
    { 2, 21 },
    { 2, 22 },
    { 2, 23 },
    { 2, 24 },

    // XP5 (Endgame)
    { 2, 25 },
    { 2, 26 },
    { 2, 27 },
    { 2, 28 },

    /* SquadRush0 */
    { 3, 0 },
    { 3, 1 },
    { 3, 2 },
    { 3, 3 },
    { 3, 4 },
    { 3, 5 },
    { 3, 6 },
    { 3, 7 },
    { 3, 8 },

    // XP1 (Back to Karkand)
    { 3, 9 },
    { 3, 10 },
    { 3, 11 },
    { 3, 12 },

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    { 3, 17 },
    { 3, 18 },
    { 3, 19 },
    { 3, 20 },

    // XP4 (Aftermath)
    { 3, 21 },
    { 3, 22 },
    { 3, 23 },
    { 3, 24 },

    // XP5 (Endgame)
    { 3, 25 },
    { 3, 26 },
    { 3, 27 },
    { 3, 28 },

    /* SquadDeathMatch0 */
    { 4, 0 },
    { 4, 1 },
    { 4, 2 },
    { 4, 3 },
    { 4, 4 },
    { 4, 5 },
    { 4, 6 },
    { 4, 7 },
    { 4, 8 },

    // XP1 (Back to Karkand)
    { 4, 9 },
    { 4, 10 },
    { 4, 11 },
    { 4, 12 },

    // XP2 (Close Quarters)
    { 4, 13 },
    { 4, 14 },
    { 4, 15 },
    { 4, 16 },

    // XP3 (Armored Kill)
    { 4, 17 },
    { 4, 18 },
    { 4, 19 },
    { 4, 20 },

    // XP4 (Aftermath)
    { 4, 21 },
    { 4, 22 },
    { 4, 23 },
    { 4, 24 },

    // XP5 (Endgame)
    { 4, 25 },
    { 4, 26 },
    { 4, 27 },
    { 4, 28 },

    /* TeamDeathMatch0 */
    { 5, 0 },
    { 5, 1 },
    { 5, 2 },
    { 5, 3 },
    { 5, 4 },
    { 5, 5 },
    { 5, 6 },
    { 5, 7 },
    { 5, 8 },

    // XP1 (Back to Karkand)
    { 5, 9 },
    { 5, 10 },
    { 5, 11 },
    { 5, 12 },

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    { 5, 17 },
    { 5, 18 },
    { 5, 19 },
    { 5, 20 },

    // XP4 (Aftermath)
    { 5, 21 },
    { 5, 22 },
    { 5, 23 },
    { 5, 24 },

    // XP5 (Endgame)
    { 5, 25 },
    { 5, 26 },
    { 5, 27 },
    { 5, 28 },

    /* ConquestAssaultLarge0 */

    // XP1 (Back to Karkand)
    { 6, 9 },
    { 6, 11 },
    { 6, 12 },

    /* ConquestAssaultSmall0 */

    // XP1 (Back to Karkand)
    { 7, 9 },
    { 7, 10 },
    { 7, 11 },
    { 7, 13 },

    /* ConquestAssaultSmall1 */

    // XP1 (Back to Karkand)
    { 8, 9 },
    { 8, 11 },
    { 8, 12 },

    /* Domination0 */

    // XP1 (Close Quarters)
    { 9, 13 },
    { 9, 14 },
    { 9, 15 },
    { 9, 16 },

    /* GunMaster0 */

    // XP1 (Close Quarters)
    { 10, 13 },
    { 10, 14 },
    { 10, 15 },
    { 10, 16 },

    // XP4 (Aftermath)
    { 10, 21 },
    { 10, 22 },
    { 10, 23 },
    { 10, 24 },

    /* TeamDeathMatchC0 */

    // XP1 (Close Quarters)
    { 11, 13 },
    { 11, 14 },
    { 11, 15 },
    { 11, 16 },

    /* TankSuperiority0 */

    // XP3 (Armored Kill)
    { 12, 17 },
    { 12, 18 },
    { 12, 19 },
    { 12, 20 },

    /* Scavenger0 */

    // XP4 (Aftermath)
    { 13, 21 },
    { 13, 22 },
    { 13, 23 },
    { 13, 24 },

    /* CaptureTheFlag0 */

    // XP5 (Endgame)
    { 14, 25 },
    { 14, 26 },
    { 14, 27 },
    { 14, 28 },

    /* AirSuperiority0 */

    // XP5 (Endgame)
    { 15, 25 },
    { 15, 26 },
    { 15, 27 },
    { 15, 28 }
};
