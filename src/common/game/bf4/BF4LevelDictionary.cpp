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

#include "BF4LevelDictionary.h"
#include "TeamEntry.h"
#include "LevelEntry.h"
#include "BF4GameModeEntry.h"

template<>
QList<TeamEntry> BF4LevelDictionary::teamList = {
    /* List of all teams */
    TeamEntry("Neutral"),                  // 0
    TeamEntry("RU", ":/bf4/teams/RU.png"), // 1
    TeamEntry("US", ":/bf4/teams/US.png"), // 2
    TeamEntry("CN", ":/bf4/teams/CN.png"), // 3
};

template<>
QString BF4LevelDictionary::imagePath = ":/bf4/levels";

template<>
QList<LevelEntry> BF4LevelDictionary::levelList = {
    /* List of all levels */
    LevelEntry("MP_Abandoned",  "Zavod 311",              QList<int>({ 1, 2 }), imagePath, "zavod_311.png"),              // 0
    LevelEntry("MP_Damage",     "Lancang Dam",            QList<int>({ 1, 3 }), imagePath, "lancang_dam.png"),            // 1
    LevelEntry("MP_Flooded",    "Flood Zone",             QList<int>({ 2, 3 }), imagePath, "flood_zone.png"),             // 2
    LevelEntry("MP_Journey",    "Golmud Railway",         QList<int>({ 1, 3 }), imagePath, "golmud_railway.png"),         // 3
    LevelEntry("MP_Naval",      "Paracel Storm",          QList<int>({ 2, 3 }), imagePath, "paracel_storm.png"),          // 4
    LevelEntry("MP_Prison",     "Operation Locker",       QList<int>({ 2, 1 }), imagePath, "operation_locker.png"),       // 5
    LevelEntry("MP_Resort",     "Hainan Resort",          QList<int>({ 2, 3 }), imagePath, "hainan_resort.png"),          // 6
    LevelEntry("MP_Siege",      "Siege of Shanghai",      QList<int>({ 2, 3 }), imagePath, "seige_of_shanghai.png"),      // 7
    LevelEntry("MP_TheDish",    "Rogue Transmission",     QList<int>({ 1, 3 }), imagePath, "rogue_transmission.png"),     // 8
    LevelEntry("MP_Tremors",    "Dawnbreaker",            QList<int>({ 2, 3 }), imagePath, "dawnbreaker.png"),            // 9

    // XP0 (Second Assault)
    LevelEntry("XP0_Caspian",   "Caspian Border 2014",    QList<int>({ 2, 1 }), imagePath, "caspian_border_2014.png"),    // 10
    LevelEntry("XP0_Firestorm", "Firestorm 2014",         QList<int>({ 2, 1 }), imagePath, "firestorm_2014.png"),         // 11
    LevelEntry("XP0_Metro",     "Operation Metro 2014",   QList<int>({ 2, 1 }), imagePath, "operation_metro_2014.png"),   // 12
    LevelEntry("XP0_Oman",      "Gulf of Oman 2014",      QList<int>({ 2, 1 }), imagePath, "gulf_of_oman_2014.png"),      // 13

    // XP1 (China Rising)
    LevelEntry("XP1_001",       "Silk Road",              QList<int>({ 2, 3 }), imagePath, "silk_road.png"),              // 14
    LevelEntry("XP1_002",       "Altai Range",            QList<int>({ 2, 3 }), imagePath, "altai_range.png"),            // 15
    LevelEntry("XP1_003",       "Guilin Peaks",           QList<int>({ 2, 3 }), imagePath, "guilin_peaks.png"),           // 16
    LevelEntry("XP1_004",       "Dragon Pass",            QList<int>({ 2, 3 }), imagePath, "dragon_pass.png"),            // 17

    // XP2 (Naval Strike)
    LevelEntry("XP2_001",       "Lost Islands",           QList<int>({ 2, 1 }), imagePath, "lost_islands.png"),           // 18
    LevelEntry("XP2_002",       "Nansha Strike",          QList<int>({ 2, 1 }), imagePath, "nansha_strike.png"),          // 19
    LevelEntry("XP2_003",       "Wave Breaker",           QList<int>({ 2, 1 }), imagePath, "wave_breaker.png"),           // 20
    LevelEntry("XP2_004",       "Operation Mortar",       QList<int>({ 2, 1 }), imagePath, "operation_mortar.png"),       // 21

    // XP3 (Dragon's Teeth)
    LevelEntry("XP3_MarketPl",  "Pearl Market",           QList<int>({ 2, 3 }), imagePath, "pearl_market.png"),           // 22
    LevelEntry("XP3_Prpganda",  "Propaganda",             QList<int>({ 2, 3 }), imagePath, "propaganda.png"),             // 23
    LevelEntry("XP3_UrbanGdn",  "Lumphini Garden",        QList<int>({ 2, 3 }), imagePath, "lumphini_garden.png"),        // 24
    LevelEntry("XP3_WtrFront",  "Sunken Dragon",          QList<int>({ 2, 3 }), imagePath, "sunken_dragon.png"),          // 25

    // XP4 (Final Stand)
    LevelEntry("XP4_Arctic",    "Operation Whiteout",     QList<int>({ 2, 1 }), imagePath, "operation_whiteout.png"),     // 26
    LevelEntry("XP4_SubBase",   "Hammerhead",             QList<int>({ 2, 1 }), imagePath, "hammerhead.png"),             // 27
    LevelEntry("XP4_Titan",     "Hangar 21",              QList<int>({ 2, 1 }), imagePath, "hangar_21.png"),              // 28
    LevelEntry("XP4_Wlkrftry",  "Giants of Karelia",      QList<int>({ 2, 1 }), imagePath, "giants_of_karelia.png"),      // 29

    // XP5 (Night Operations)
    LevelEntry("XP5_Night_01",  "Zavod:Graveyard Shift",  QList<int>({ 2, 1 }), imagePath, "zavod_graveyard_shift.png"),  // 30

    // XP6 (Community Operations)
    LevelEntry("XP6_CMP",       "Operation Outbreak",     QList<int>({ 2, 1 }), imagePath, "operation_outbreak.png"),     // 31

    // XP7 (Legacy Operations)
    LevelEntry("XP7_Valley",    "Dragon Valley 2015",     QList<int>({ 2, 1 }), imagePath, "dragon_valley_2015.png"),     // 32
};

template<>
QList<BF4GameModeEntry> BF4LevelDictionary::gameModeList = {
    /* List of all gamemodes */
    BF4GameModeEntry("ConquestLarge0",       "Conquest Large",        64, 2, 4), // 0
    BF4GameModeEntry("ConquestSmall0",       "Conquest Small",        32, 2, 4), // 1
    BF4GameModeEntry("Domination0",          "Domination",            20, 0, 4), // 2
    BF4GameModeEntry("Elimination0",         "Defuse",                10, 0, 4), // 3
    BF4GameModeEntry("Obliteration",         "Obliteration",          32, 2, 4), // 4
    BF4GameModeEntry("RushLarge0",           "Rush",                  32, 2, 4), // 5
    BF4GameModeEntry("SquadDeathMatch0",     "Squad Deathmatch",      20, 0, 4), // 6
    BF4GameModeEntry("SquadDeathMatch1",     "Squad Deathmatch",      20, 0, 4), // 7
    BF4GameModeEntry("TeamDeathMatch0",      "Team Deathmatch",       20, 0, 4), // 8
    BF4GameModeEntry("TeamDeathMatch1",      "Team Deathmatch",       20, 0, 4), // 9
    BF4GameModeEntry("AirSuperiority0",      "Air Superiority",       24, 0, 4), // 10
    BF4GameModeEntry("CarrierAssaultLarge0", "Carrier Assault Large", 64, 2, 4), // 11
    BF4GameModeEntry("CarrierAssaultSmall0", "Carrier Assault Small", 32, 2, 4), // 12
    BF4GameModeEntry("CaptureTheFlag0",      "Capture the flag",      32, 0, 4), // 13
    BF4GameModeEntry("Chainlink0",           "Chain Link",            32, 0, 4), // 14
    BF4GameModeEntry("SquadObliteration0",   "Squad Obliteration",    10, 0, 4), // 15
    BF4GameModeEntry("GunMaster0",           "Gun Master",            32, 0, 4), // 16
    BF4GameModeEntry("GunMaster1",           "Gun Master",            32, 0, 4)  // 17
};

template<>
QMultiHash<int, int> BF4LevelDictionary::levelMap = {
    /* List of all levels and gamemodes combined */
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
    { 0, 9 },

    // XP0 (Second Assault)
    { 0, 10 },
    { 0, 11 },
    { 0, 12 },
    { 0, 13 },

    // XP1 (China Rising)
    { 0, 14 },
    { 0, 15 },
    { 0, 16 },
    { 0, 17 },

    // XP2 (Naval Strike)
    { 0, 18 },
    { 0, 19 },
    { 0, 20 },
    { 0, 21 },

    // XP3 (Dragon's Teeth)
    { 0, 22 },
    { 0, 23 },
    { 0, 24 },
    { 0, 25 },

    // XP4 (Final Stand)
    { 0, 26 },
    { 0, 27 },
    { 0, 28 },
    { 0, 29 },

    // XP5 (Night Operations)
    { 0, 30 },

    // XP6 (Community Operations)
    { 0, 31 },

    // XP7 (Legacy Operations)
    { 0, 32 },

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
    { 1, 9 },

    // XP0 (Second Assault)
    { 1, 10 },
    { 1, 11 },
    { 1, 12 },
    { 1, 13 },

    // XP1 (China Rising)
    { 1, 14 },
    { 1, 15 },
    { 1, 16 },
    { 1, 17 },

    // XP2 (Naval Strike)
    { 1, 18 },
    { 1, 19 },
    { 1, 20 },
    { 1, 21 },

    // XP3 (Dragon's Teeth)
    { 1, 22 },
    { 1, 23 },
    { 1, 24 },
    { 1, 25 },

    // XP4 (Final Stand)
    { 1, 26 },
    { 1, 27 },
    { 1, 28 },
    { 1, 29 },

    // XP5 (Night Operations)
    { 1, 30 },

    // XP6 (Community Operations)
    { 1, 31 },

    // XP7 (Legacy Operations)
    { 1, 32 },

    /* Domination0 */
    { 2, 2 },
    { 2, 1 },
    { 2, 2 },
    { 2, 3 },
    { 2, 4 },
    { 2, 5 },
    { 2, 6 },
    { 2, 7 },
    { 2, 8 },
    { 2, 9 },

    // XP0 (Second Assault)
    { 2, 10 },
    { 2, 11 },
    { 2, 12 },
    { 2, 13 },

    // XP1 (China Rising)
    { 2, 14 },
    { 2, 15 },
    { 2, 16 },
    { 2, 17 },

    // XP2 (Naval Strike)
    { 2, 18 },
    { 2, 19 },
    { 2, 20 },
    { 2, 21 },

    // XP3 (Dragon's Teeth)
    { 2, 22 },
    { 2, 23 },
    { 2, 24 },
    { 2, 25 },

    // XP4 (Final Stand)
    { 2, 26 },
    { 2, 27 },
    { 2, 28 },
    { 2, 29 },

    // XP5 (Night Operations)
    { 2, 30 },

    // XP6 (Community Operations)
    { 2, 31 },

    // XP7 (Legacy Operations)
    { 2, 32 },

    /* Elemination0 */
    { 3, 0 },
    { 3, 1 },
    { 3, 2 },
    { 3, 3 },
    { 3, 4 },
    { 3, 5 },
    { 3, 6 },
    { 3, 7 },
    { 3, 8 },
    { 3, 9 },

    // XP0 (Second Assault)
    { 3, 10 },
    { 3, 11 },
    { 3, 12 },
    { 3, 13 },

    // XP1 (China Rising)
    { 3, 14 },
    { 3, 15 },
    { 3, 16 },
    { 3, 17 },

    // XP2 (Naval Strike)
    { 3, 18 },
    { 3, 19 },
    { 3, 20 },
    { 3, 21 },

    // XP3 (Dragon's Teeth)
    { 3, 22 },
    { 3, 23 },
    { 3, 24 },
    { 3, 25 },

    // XP4 (Final Stand)
    { 3, 26 },
    { 3, 27 },
    { 3, 28 },
    { 3, 29 },

    /* Obliteration */
    { 4, 0 },
    { 4, 1 },
    { 4, 2 },
    { 4, 3 },
    { 4, 4 },
    { 4, 5 },
    { 4, 6 },
    { 4, 7 },
    { 4, 8 },
    { 4, 9 },

    // XP0 (Second Assault)
    { 4, 10 },
    { 4, 11 },
    { 4, 12 },
    { 4, 13 },

    // XP1 (China Rising)
    { 4, 14 },
    { 4, 15 },
    { 4, 16 },
    { 4, 17 },

    // XP2 (Naval Strike)
    { 4, 18 },
    { 4, 19 },
    { 4, 20 },
    { 4, 21 },

    // XP3 (Dragon's Teeth)
    { 4, 22 },
    { 4, 23 },
    { 4, 24 },
    { 4, 25 },

    // XP4 (Final Stand)
    { 4, 26 },
    { 4, 27 },
    { 4, 28 },
    { 4, 29 },

    // XP5 (Night Operations)
    { 4, 30 },

    // XP6 (Community Operations)
    { 4, 31 },

    // XP7 (Legacy Operations)
    { 4, 32 },

    /* RushLarge0 */
    { 5, 0 },
    { 5, 1 },
    { 5, 2 },
    { 5, 3 },
    { 5, 4 },
    { 5, 5 },
    { 5, 6 },
    { 5, 7 },
    { 5, 8 },
    { 5, 9 },

    // XP0 (Second Assault)
    { 5, 10 },
    { 5, 11 },
    { 5, 12 },
    { 5, 13 },

    // XP1 (China Rising)
    { 5, 14 },
    { 5, 15 },
    { 5, 16 },
    { 5, 17 },

    // XP2 (Naval Strike)
    { 5, 18 },
    { 5, 19 },
    { 5, 20 },
    { 5, 21 },

    // XP3 (Dragon's Teeth)
    { 5, 22 },
    { 5, 23 },
    { 5, 24 },
    { 5, 25 },

    // XP4 (Final Stand)
    { 5, 26 },
    { 5, 27 },
    { 5, 28 },
    { 5, 29 },

    // XP5 (Night Operations)
    { 5, 30 },

    // XP6 (Community Operations)
    { 5, 31 },

    // XP7 (Legacy Operations)
    { 5, 32 },

    /* SquadDeathMatch0 */
    { 6, 0 },
    { 6, 1 },
    { 6, 2 },
    { 6, 3 },
    { 6, 4 },
    { 6, 5 },
    { 6, 6 },
    { 6, 7 },
    { 6, 8 },
    { 6, 9 },

    // XP0 (Second Assault)
    { 6, 10 },
    { 6, 11 },
    { 6, 12 },
    { 6, 13 },

    // XP1 (China Rising)
    { 6, 14 },
    { 6, 15 },
    { 6, 16 },
    { 6, 17 },

    // XP2 (Naval Strike)
    { 6, 18 },
    { 6, 19 },
    { 6, 20 },
    { 6, 21 },

    // XP3 (Dragon's Teeth)
    { 6, 22 },
    { 6, 23 },
    { 6, 24 },
    { 6, 25 },

    // XP4 (Final Stand)
    { 6, 26 },
    { 6, 27 },
    { 6, 28 },
    { 6, 29 },

    // XP6 (Community Operations)
    { 6, 31 },

    // XP7 (Legacy Operations)
    { 6, 32 },

    /* SquadDeathMatch1 */

    // XP6 (Community Operations)
    { 7, 31 },

    /* TeamDeathMatch0 */
    { 8, 0 },
    { 8, 1 },
    { 8, 2 },
    { 8, 3 },
    { 8, 4 },
    { 8, 5 },
    { 8, 6 },
    { 8, 7 },
    { 8, 8 },
    { 8, 9 },

    // XP0 (Second Assault)
    { 8, 10 },
    { 8, 11 },
    { 8, 12 },
    { 8, 13 },

    // XP1 (China Rising)
    { 8, 14 },
    { 8, 15 },
    { 8, 16 },
    { 8, 17 },

    // XP2 (Naval Strike)
    { 8, 18 },
    { 8, 19 },
    { 8, 20 },
    { 8, 21 },

    // XP3 (Dragon's Teeth)
    { 8, 22 },
    { 8, 23 },
    { 8, 24 },
    { 8, 25 },

    // XP4 (Final Stand)
    { 8, 26 },
    { 8, 27 },
    { 8, 28 },
    { 8, 29 },

    // XP5 (Night Operations)
    { 8, 30 },

    // XP6 (Community Operations)
    { 8, 31 },

    // XP7 (Legacy Operations)
    { 8, 32 },

    /* TeamDeathMatch1 */

    // XP6 (Community Operations)
    { 9, 31 },

    /* AirSuperiority0 */

    // XP1 (China Rising)
    { 10, 14 },
    { 10, 15 },
    { 10, 16 },
    { 10, 17 },

    // XP7 (Legacy Operations)
    { 10, 32 },

    /* CarrierAssaultLarge0 */

    // XP2 (Naval Strike)
    { 11, 18 },
    { 11, 19 },
    { 11, 20 },
    { 11, 21 },

    /* CarrierAssaultSmall0 */

    // XP2 (Naval Strike)
    { 12, 18 },
    { 12, 19 },
    { 12, 20 },
    { 12, 21 },

    /* CaptureTheFlag0 */

    // XP0 (Second Assault)
    { 13, 10 },
    { 13, 11 },
    { 13, 12 },
    { 13, 13 },

    // XP2 (Naval Strike)
    { 13, 18 },
    { 13, 19 },
    { 13, 20 },
    { 13, 21 },

    // XP3 (Dragon's Teeth)
    { 13, 22 },
    { 13, 23 },
    { 13, 24 },
    { 13, 25 },

    // XP4 (Final Stand)
    { 13, 26 },
    { 13, 27 },
    { 13, 28 },
    { 13, 29 },

    // XP6 (Community Operations)
    { 13, 31 },

    /* Chainlink0 */

    // XP3 (Dragon's Teeth)
    { 14, 22 },
    { 14, 23 },
    { 14, 24 },
    { 14, 25 },

    // XP6 (Community Operations)
    { 14, 31 },

    /* SquadObliteration0 */
    { 15, 0 },
    { 15, 3 },
    { 15, 4 },
    { 15, 5 },
    { 15, 6 },
    { 15, 7 },
    { 15, 9 },

    /* GunMaster0 */
    { 16, 0 },
    { 16, 1 },
    { 16, 2 },
    { 16, 3 },
    { 16, 4 },
    { 16, 5 },
    { 16, 6 },
    { 16, 7 },
    { 16, 8 },
    { 16, 9 },

    // XP5 (Night Operations)
    { 16, 30 },

    // XP6 (Community Operations)
    { 16, 31 },

    // XP7 (Legacy Operations)
    { 16, 32 },

    /* GunMaster1 */

    // XP5 (Night Operations)
    { 17, 30 },

    // XP6 (Community Operations)
    { 17, 31 }
};
