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

#include "BF4LevelDictionary.h"
#include "TeamEntry.h"
#include "LevelEntry.h"
#include "BF4GameModeEntry.h"

template<>
QList<TeamEntry> BF4LevelDictionary::teamList = {
    /* List of all teams */
    TeamEntry("Neutral",     ""),                   // 0
    TeamEntry("RU",         ":/bf4/teams/RU.png"),  // 1
    TeamEntry("US",         ":/bf4/teams/US.png"),  // 2
    TeamEntry("CN",         ":/bf4/teams/CN.png"),  // 3
};

template<>
QString BF4LevelDictionary::imagePath = ":/bf4/levels";

template<>
QList<LevelEntry> BF4LevelDictionary::levelList = {
    /* List of all levels */
    LevelEntry("MP_Abandoned",  "Zavod 311",            QList<int>({ 1, 2 }), imagePath, "zavod_311.png"),              // 0
    LevelEntry("MP_Damage",     "Lancang Dam",          QList<int>({ 1, 3 }), imagePath, "lancang_dam.png"),            // 1
    LevelEntry("MP_Flooded",    "Flood Zone",           QList<int>({ 2, 3 }), imagePath, "flood_zone.png"),             // 2
    LevelEntry("MP_Journey",    "Golmud Railway",       QList<int>({ 1, 3 }), imagePath, "golmud_railway.png"),         // 3
    LevelEntry("MP_Naval",      "Paracel Storm",        QList<int>({ 2, 3 }), imagePath, "paracel_storm.png"),          // 4
    LevelEntry("MP_Prison",     "Operation Locker",     QList<int>({ 2, 1 }), imagePath, "operation_locker.png"),       // 5
    LevelEntry("MP_Resort",     "Hainan Resort",        QList<int>({ 2, 3 }), imagePath, "hainan_resort.png"),          // 6
    LevelEntry("MP_Siege",      "Siege of Shanghai",    QList<int>({ 2, 3 }), imagePath, "seige_of_shanghai.png"),      // 7
    LevelEntry("MP_TheDish",    "Rogue Transmission",   QList<int>({ 1, 3 }), imagePath, "rogue_transmission.png"),     // 8
    LevelEntry("MP_Tremors",    "Dawnbreaker",          QList<int>({ 2, 3 }), imagePath, "dawnbreaker.png"),            // 9

    // XP1 (China Rising)
    LevelEntry("XP1_001",       "Silk Road",            QList<int>({ 2, 3 }), imagePath, "silk_road.png"),              // 10
    LevelEntry("XP1_002",       "Altai Range",          QList<int>({ 2, 3 }), imagePath, "altai_range.png"),            // 11
    LevelEntry("XP1_003",       "Guilin Peaks",         QList<int>({ 2, 3 }), imagePath, "guilin_peaks.png"),           // 12
    LevelEntry("XP1_004",       "Dragon Pass",          QList<int>({ 2, 3 }), imagePath, "dragon_pass.png"),            // 13

    // XP2 (Second Assault)
    LevelEntry("XP0_Caspian",   "Caspian Border 2014",  QList<int>({ 2, 1 }), imagePath, "caspian_border_2014.png"),    // 14
    LevelEntry("XP0_Firestorm", "Firestorm 2014",       QList<int>({ 2, 1 }), imagePath, "firestorm_2014.png"),         // 15
    LevelEntry("XP0_Metro",     "Operation Metro 2014", QList<int>({ 2, 1 }), imagePath, "operation_metro_2014.png"),   // 16
    LevelEntry("XP0_Oman",      "Gulf of Oman 2014",    QList<int>({ 2, 1 }), imagePath, "gulf_of_oman_2014.png"),      // 17

    // XP3 (Naval Strike)
    LevelEntry("XP2_001",       "Lost Islands",         QList<int>({ 2, 1 }), imagePath, "lost_islands.png"),           // 18
    LevelEntry("XP2_002",       "Nansha Strike",        QList<int>({ 2, 1 }), imagePath, "nansha_strike.png"),          // 19
    LevelEntry("XP2_003",       "Wave Breaker",         QList<int>({ 2, 1 }), imagePath, "wave_breaker.png"),           // 20
    LevelEntry("XP2_004",       "Operation Mortar",     QList<int>({ 2, 1 }), imagePath, "operation_mortar.png"),       // 21

    // XP4 (Dragon's Teeth)
    LevelEntry("XP3_MarketPl",  "Pearl Market",         QList<int>({ 2, 3 }), imagePath, "pearl_market.png"),           // 22
    LevelEntry("XP3_Prpganda",  "Propaganda",           QList<int>({ 2, 3 }), imagePath, "propaganda.png"),             // 23
    LevelEntry("XP3_UrbanGdn",  "Lumphini Garden",      QList<int>({ 2, 3 }), imagePath, "lumphini_garden.png"),        // 24
    LevelEntry("XP3_WtrFront",  "Sunken Dragon",        QList<int>({ 2, 3 }), imagePath, "sunken_dragon.png"),          // 25

    // XP5 (Final Stand)
    LevelEntry("XP4_Arctic",    "Operation Whiteout",   QList<int>({ 2, 1 }), imagePath, "operation_whiteout.png"),     // 26
    LevelEntry("XP4_SubBase",   "Hammerhead",           QList<int>({ 2, 1 }), imagePath, "hammerhead.png"),             // 27
    LevelEntry("XP4_Titan",     "Giants Of Karelia",    QList<int>({ 2, 1 }), imagePath, "giants_of_karelia.png"),      // 28
    LevelEntry("XP4_Wlkrftry",  "Hangar 21",            QList<int>({ 2, 1 }), imagePath, "hangar_21.png"),              // 29

};

template<>
QList<BF4GameModeEntry> BF4LevelDictionary::gameModeList = {
    /* List of all gamemodes */
    BF4GameModeEntry("ConquestLarge0",          "Conquest Large",           64, 2, 4), // 0
    BF4GameModeEntry("ConquestSmall0",          "Conquest Small",           32, 2, 4), // 1
    BF4GameModeEntry("Domination0",             "Domination",               20, 0, 4), // 2
    BF4GameModeEntry("Elimination0",            "Defuse",                   10, 0, 4), // 3
    BF4GameModeEntry("Obliteration",            "Obliteration",             32, 2, 4), // 4
    BF4GameModeEntry("RushLarge0",              "Rush",                     32, 2, 4), // 5
    BF4GameModeEntry("SquadDeathMatch0",        "Squad Deathmatch",         16, 0, 4), // 6
    BF4GameModeEntry("TeamDeathMatch0",         "Team Deathmatch",          24, 0, 4), // 7
    BF4GameModeEntry("AirSuperiority0",         "Air Superiority",          24, 0, 4), // 8
    BF4GameModeEntry("CaptureTheFlag0",         "Capture the flag",         32, 0, 4), // 9
    BF4GameModeEntry("CarrierAssaultSmall0",    "Carrier Assault Small",    32, 0, 4), // 10
    BF4GameModeEntry("CarrierAssaultLarge0",    "Carrier Assault Large",    64, 0, 4), // 11
    BF4GameModeEntry("Chainlink0",              "Chain Link",               64, 0, 4)  // 12 Check this when docs are available.
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

    // XP1 (China Rising)
    { 0, 10 },
    { 0, 11 },
    { 0, 12 },
    { 0, 13 },

    // XP2 (Second Assault)
    { 0, 14 },
    { 0, 15 },
    { 0, 16 },
    { 0, 17 },

    // XP3 (Naval Strike)
    { 0, 18 },
    { 0, 19 },
    { 0, 20 },
    { 0, 21 },

    // XP4 (Dragon's Teeth)
    { 0, 22 },
    { 0, 23 },
    { 0, 24 },
    { 0, 25 },

    // XP5 (Final Stand)
    { 0, 26 },
    { 0, 27 },
    { 0, 28 },
    { 0, 29 },

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

    // XP1 (China Rising)
    { 1, 10 },
    { 1, 11 },
    { 1, 12 },
    { 1, 13 },

    // XP2 (Second Assault)
    { 1, 14 },
    { 1, 15 },
    { 1, 16 },
    { 1, 17 },

    // XP3 (Naval Strike)
    { 1, 18 },
    { 1, 19 },
    { 1, 20 },
    { 1, 21 },

    // XP4 (Dragon's Teeth)
    { 1, 22 },
    { 1, 23 },
    { 1, 24 },
    { 1, 25 },

    // XP5 (Final Stand)
    { 1, 26 },
    { 1, 27 },
    { 1, 28 },
    { 1, 29 },

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

    // XP1 (China Rising)
    { 2, 10 },
    { 2, 11 },
    { 2, 12 },
    { 2, 13 },

    // XP2 (Second Assault)
    { 2, 14 },
    { 2, 15 },
    { 2, 16 },
    { 2, 17 },

    // XP3 (Naval Strike)
    { 2, 18 },
    { 2, 19 },
    { 2, 20 },
    { 2, 21 },

    // XP4 (Dragon's Teeth)
    { 2, 22 },
    { 2, 23 },
    { 2, 24 },
    { 2, 25 },

    // XP5 (Final Stand)
    { 2, 26 },
    { 2, 27 },
    { 2, 28 },
    { 2, 29 },

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

    // XP1 (China Rising)
    { 3, 10 },
    { 3, 11 },
    { 3, 12 },
    { 3, 13 },

    // XP2 (Second Assault)
    { 3, 14 },
    { 3, 15 },
    { 3, 16 },
    { 3, 17 },

    // XP3 (Naval Strike)
    { 3, 18 },
    { 3, 19 },
    { 3, 20 },
    { 3, 21 },

    // XP4 (Dragon's Teeth)
    { 3, 22 },
    { 3, 23 },
    { 3, 24 },
    { 3, 25 },

    // XP5 (Final Stand)
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

    // XP1 (China Rising)
    { 4, 10 },
    { 4, 11 },
    { 4, 12 },
    { 4, 13 },

    // XP2 (Second Assault)
    { 4, 14 },
    { 4, 15 },
    { 4, 16 },
    { 4, 17 },

    // XP3 (Naval Strike)
    { 4, 18 },
    { 4, 19 },
    { 4, 20 },
    { 4, 21 },

    // XP4 (Dragon's Teeth)
    { 4, 22 },
    { 4, 23 },
    { 4, 24 },
    { 4, 25 },

    // XP5 (Final Stand)
    { 4, 26 },
    { 4, 27 },
    { 4, 28 },
    { 4, 29 },

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

    // XP1 (China Rising)
    { 5, 10 },
    { 5, 11 },
    { 5, 12 },
    { 5, 13 },

    // XP2 (Second Assault)
    { 5, 14 },
    { 5, 15 },
    { 5, 16 },
    { 5, 17 },

    // XP3 (Naval Strike)
    { 5, 18 },
    { 5, 19 },
    { 5, 20 },
    { 5, 21 },

    // XP4 (Dragon's Teeth)
    { 5, 22 },
    { 5, 23 },
    { 5, 24 },
    { 5, 25 },

    // XP5 (Final Stand)
    { 5, 26 },
    { 5, 27 },
    { 5, 28 },
    { 5, 29 },

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

    // XP1 (China Rising)
    { 6, 10 },
    { 6, 11 },
    { 6, 12 },
    { 6, 13 },

    // XP2 (Second Assault)
    { 6, 14 },
    { 6, 15 },
    { 6, 16 },
    { 6, 17 },

    // XP3 (Naval Strike)
    { 6, 18 },
    { 6, 19 },
    { 6, 20 },
    { 6, 21 },

    // XP4 (Dragon's Teeth)
    { 6, 22 },
    { 6, 23 },
    { 6, 24 },
    { 6, 25 },

    // XP5 (Final Stand)
    { 6, 26 },
    { 6, 27 },
    { 6, 28 },
    { 6, 29 },

    /* TeamDeathMatch0 */
    { 7, 0 },
    { 7, 1 },
    { 7, 2 },
    { 7, 3 },
    { 7, 4 },
    { 7, 5 },
    { 7, 6 },
    { 7, 7 },
    { 7, 8 },
    { 7, 9 },

    // XP1 (China Rising)
    { 7, 10 },
    { 7, 11 },
    { 7, 12 },
    { 7, 13 },

    // XP2 (Second Assault)
    { 7, 14 },
    { 7, 15 },
    { 7, 16 },
    { 7, 17 },

    // XP3 (Naval Strike)
    { 7, 18 },
    { 7, 19 },
    { 7, 20 },
    { 7, 21 },

    // XP4 (Dragon's Teeth)
    { 7, 22 },
    { 7, 23 },
    { 7, 24 },
    { 7, 25 },

    // XP5 (Final Stand)
    { 7, 26 },
    { 7, 27 },
    { 7, 28 },
    { 7, 29 },

    /* AirSuperiority0 */

    // XP1 (China Rising)
    { 8, 10 },
    { 8, 11 },
    { 8, 12 },
    { 8, 13 },

    /* CaptureTheFlag0 */

    // XP2 (Second Assault)
    { 9, 14 },
    { 9, 15 },
    { 9, 16 },
    { 9, 17 },

    // XP3 (Naval Strike)
    { 9, 18 },
    { 9, 19 },
    { 9, 20 },
    { 9, 21 },

    // XP4 (Dragon's Teeth)
    { 9, 22 },
    { 9, 23 },
    { 9, 24 },
    { 9, 25 },

    // XP5 (Final Stand)
    { 9, 26 },
    { 9, 27 },
    { 9, 28 },
    { 9, 29 },

    /* Carrier Assault Small */

    // XP3 (Naval Strike)
    { 10, 18 },
    { 10, 19 },
    { 10, 20 },
    { 10, 21 },

    /* Carrier Assault Large */

    // XP3 (Naval Strike)
    { 11, 18 },
    { 11, 19 },
    { 11, 20 },
    { 11, 21 },

    /* Chainlink */

    // XP4 (Dragon's Teeth)
    { 12, 22 },
    { 12, 23 },
    { 12, 24 },
    { 12, 25 }
};
