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

#include "BFBC2LevelDictionary.h"
#include "TeamEntry.h"
#include "BFBC2LevelEntry.h"
#include "GameModeEntry.h"

template<>
QList<TeamEntry> BFBC2LevelDictionary::teamList = {
    /* List of all teams */
    TeamEntry("Neutral",    ""),                    // 0
    TeamEntry("US",         ":/bf3/teams/RU.png"),  // 1
    TeamEntry("RU",         ":/bf3/teams/US.png")   // 2
};

template<>
QString BFBC2LevelDictionary::imagePath = ":/bfbc2/levels";

template<>
QList<BFBC2LevelEntry> BFBC2LevelDictionary::levelList = {
    /* List of all levels */
    BFBC2LevelEntry("levels/mp_001",              "Panama Canal",       QList<int>({ 0, 0 }), imagePath, "panama_canal.png",       BFBC2Mod::BC2),     // 0
    BFBC2LevelEntry("levels/mp_003",              "Laguna Alta",        QList<int>({ 0, 0 }), imagePath, "laguna_alta.png",        BFBC2Mod::BC2),     // 1
    BFBC2LevelEntry("levels/mp_005",              "Atacama Desert",     QList<int>({ 0, 0 }), imagePath, "atacama_desert.png",     BFBC2Mod::BC2),     // 2
    BFBC2LevelEntry("levels/mp_006cq",            "Arica Harbor",       QList<int>({ 0, 0 }), imagePath, "arica_harbor.png",       BFBC2Mod::BC2),     // 3
    BFBC2LevelEntry("levels/mp_007",              "White Pass",         QList<int>({ 0, 0 }), imagePath, "white_pass.png",         BFBC2Mod::BC2),     // 4
    BFBC2LevelEntry("levels/mp_008cq",            "Nelson Bay",         QList<int>({ 0, 0 }), imagePath, "nelson_bay.png",         BFBC2Mod::BC2),     // 5
    BFBC2LevelEntry("levels/mp_009cq",            "Laguna Presa",       QList<int>({ 0, 0 }), imagePath, "laguna_presa.png",       BFBC2Mod::BC2),     // 6
    BFBC2LevelEntry("levels/mp_012cq",            "Port Valdez",        QList<int>({ 0, 0 }), imagePath, "port_valdez.png",        BFBC2Mod::BC2),     // 7
    BFBC2LevelEntry("levels/bc1_oasis_cq",        "Oasis",              QList<int>({ 0, 0 }), imagePath, "oasis.png",              BFBC2Mod::BC2),     // 8
    BFBC2LevelEntry("levels/bc1_harvest_day_cq",  "Harvest Day",        QList<int>({ 0, 0 }), imagePath, "harvest_day.png",        BFBC2Mod::BC2),     // 9
    BFBC2LevelEntry("levels/mp_sp_005cq",         "Heavy Metal",        QList<int>({ 0, 0 }), imagePath, "heavy_metal.png",        BFBC2Mod::BC2),     // 10

    BFBC2LevelEntry("levels/nam_mp_002cq",        "Vantage Point",      QList<int>({ 0, 0 }), imagePath, "vantage_point.png",      BFBC2Mod::VIETNAM), // 11
    BFBC2LevelEntry("levels/nam_mp_003cq",        "Hill 137",           QList<int>({ 0, 0 }), imagePath, "hill_137.png",           BFBC2Mod::VIETNAM), // 12
    BFBC2LevelEntry("levels/nam_mp_005cq",        "Cao Son Temple",     QList<int>({ 0, 0 }), imagePath, "cao_son_temple.png",     BFBC2Mod::VIETNAM), // 13
    BFBC2LevelEntry("levels/nam_mp_006cq",        "Phu Bai Valley",     QList<int>({ 0, 0 }), imagePath, "phu_bai_valley.png",     BFBC2Mod::VIETNAM), // 14
    BFBC2LevelEntry("levels/nam_mp_007cq",        "Operation Hastings", QList<int>({ 0, 0 }), imagePath, "operation_hastings.png", BFBC2Mod::VIETNAM), // 15

    BFBC2LevelEntry("levels/mp_002",              "Valparaíso",         QList<int>({ 0, 0 }), imagePath, "valparaiso.png",         BFBC2Mod::BC2),     // 16
    BFBC2LevelEntry("levels/mp_004",              "Isla Inocentes",     QList<int>({ 0, 0 }), imagePath, "isla_inocentes.png",     BFBC2Mod::BC2),     // 17
    BFBC2LevelEntry("levels/mp_005gr",            "Atacama Desert",     QList<int>({ 0, 0 }), imagePath, "atacama_desert.png",     BFBC2Mod::BC2),     // 18
    BFBC2LevelEntry("levels/mp_006",              "Arica Harbor",       QList<int>({ 0, 0 }), imagePath, "arica_harbor.png",       BFBC2Mod::BC2),     // 19
    BFBC2LevelEntry("levels/mp_007gr",            "White Pass",         QList<int>({ 0, 0 }), imagePath, "white_pass.png",         BFBC2Mod::BC2),     // 20
    BFBC2LevelEntry("levels/mp_008",              "Nelson Bay",         QList<int>({ 0, 0 }), imagePath, "nelson_bay.png",         BFBC2Mod::BC2),     // 21
    BFBC2LevelEntry("levels/mp_009gr",            "Laguna Presa",       QList<int>({ 0, 0 }), imagePath, "laguna_presa.png",       BFBC2Mod::BC2),     // 22
    BFBC2LevelEntry("levels/mp_012gr",            "Port Valdez",        QList<int>({ 0, 0 }), imagePath, "port_valdez.png",        BFBC2Mod::BC2),     // 23
    BFBC2LevelEntry("levels/bc1_oasis_gr",        "Oasis",              QList<int>({ 0, 0 }), imagePath, "oasis.png",              BFBC2Mod::BC2),     // 24
    BFBC2LevelEntry("levels/bc1_harvest_day_gr",  "Harvest Day",        QList<int>({ 0, 0 }), imagePath, "harvest_day.png",        BFBC2Mod::BC2),     // 25
    BFBC2LevelEntry("levels/mp_sp_002gr",         "Cold War",           QList<int>({ 0, 0 }), imagePath, "cold_war.png",           BFBC2Mod::BC2),     // 26

    BFBC2LevelEntry("levels/nam_mp_002r",         "Vantage Point",      QList<int>({ 0, 0 }), imagePath, "vantage_point.png",      BFBC2Mod::VIETNAM), // 27
    BFBC2LevelEntry("levels/nam_mp_003r",         "Hill 137",           QList<int>({ 0, 0 }), imagePath, "hill_137.png",           BFBC2Mod::VIETNAM), // 28
    BFBC2LevelEntry("levels/nam_mp_005r",         "Cao Son Temple",     QList<int>({ 0, 0 }), imagePath, "cao_son_temple.png",     BFBC2Mod::VIETNAM), // 29
    BFBC2LevelEntry("levels/nam_mp_006r",         "Phu Bai Valley",     QList<int>({ 0, 0 }), imagePath, "phi_bai_valley.png",     BFBC2Mod::VIETNAM), // 30
    BFBC2LevelEntry("levels/nam_mp_007r",         "Operation Hastings", QList<int>({ 0, 0 }), imagePath, "operation_hastings.png", BFBC2Mod::VIETNAM), // 31

    BFBC2LevelEntry("levels/mp_001sr",            "Panama Canal",       QList<int>({ 0, 0 }), imagePath, "panama_canal.png",       BFBC2Mod::BC2),     // 32
    BFBC2LevelEntry("levels/mp_002sr",            "Valparaíso",         QList<int>({ 0, 0 }), imagePath, "valparaiso.png",         BFBC2Mod::BC2),     // 33
    BFBC2LevelEntry("levels/mp_003sr",            "Laguna Alta",        QList<int>({ 0, 0 }), imagePath, "laguna_alta.png",        BFBC2Mod::BC2),     // 34
    BFBC2LevelEntry("levels/mp_005sr",            "Atacama Desert",     QList<int>({ 0, 0 }), imagePath, "atacama_desert.png",     BFBC2Mod::BC2),     // 35
    BFBC2LevelEntry("levels/mp_009sr",            "Laguna Presa",       QList<int>({ 0, 0 }), imagePath, "laguna_presa.png",       BFBC2Mod::BC2),     // 36
    BFBC2LevelEntry("levels/mp_012sr",            "Port Valdez",        QList<int>({ 0, 0 }), imagePath, "port_valdez.png",        BFBC2Mod::BC2),     // 37
    BFBC2LevelEntry("levels/bc1_oasis_sr",        "Oasis",              QList<int>({ 0, 0 }), imagePath, "oasis.png",              BFBC2Mod::BC2),     // 38
    BFBC2LevelEntry("levels/bc1_harvest_day_sr",  "Harvest Day",        QList<int>({ 0, 0 }), imagePath, "harvest_day.png",        BFBC2Mod::BC2),     // 39
    BFBC2LevelEntry("levels/mp_sp_002sr",         "Cold War",           QList<int>({ 0, 0 }), imagePath, "cold_war.png",           BFBC2Mod::BC2),     // 40

    BFBC2LevelEntry("levels/nam_mp_002sr",        "Vantage Point",      QList<int>({ 0, 0 }), imagePath, "vantage_point.png",      BFBC2Mod::VIETNAM), // 41
    BFBC2LevelEntry("levels/nam_mp_003sr",        "Hill 137",           QList<int>({ 0, 0 }), imagePath, "hill_137.png",           BFBC2Mod::VIETNAM), // 42
    BFBC2LevelEntry("levels/nam_mp_005sr",        "Cao Son Temple",     QList<int>({ 0, 0 }), imagePath, "cao_son_temple.png",     BFBC2Mod::VIETNAM), // 43
    BFBC2LevelEntry("levels/nam_mp_006sr",        "Phu Bai Valley",     QList<int>({ 0, 0 }), imagePath, "phu_bai_valley.png",     BFBC2Mod::VIETNAM), // 44
    BFBC2LevelEntry("levels/nam_mp_007sr",        "Operation Hastings", QList<int>({ 0, 0 }), imagePath, "operation_hastings.png", BFBC2Mod::VIETNAM), // 45

    BFBC2LevelEntry("levels/mp_001sdm",           "Panama Canal",       QList<int>({ 0, 0 }), imagePath, "panama_canal.png",       BFBC2Mod::BC2),     // 46
    BFBC2LevelEntry("levels/mp_004sdm",           "Isla Inocentes",     QList<int>({ 0, 0 }), imagePath, "isla_inocentes.png",     BFBC2Mod::BC2),     // 47
    BFBC2LevelEntry("levels/mp_006sdm",           "Arica Harbor",       QList<int>({ 0, 0 }), imagePath, "arica_harbor.png",       BFBC2Mod::BC2),     // 48
    BFBC2LevelEntry("levels/mp_007sdm",           "White Pass",         QList<int>({ 0, 0 }), imagePath, "white_pass.png",         BFBC2Mod::BC2),     // 49
    BFBC2LevelEntry("levels/mp_008sdm",           "Nelson Bay",         QList<int>({ 0, 0 }), imagePath, "nelson_bay.png",         BFBC2Mod::BC2),     // 50
    BFBC2LevelEntry("levels/mp_009sdm",           "Laguna Presa",       QList<int>({ 0, 0 }), imagePath, "laguna_presa.png",       BFBC2Mod::BC2),     // 51
    BFBC2LevelEntry("levels/bc1_oasis_sdm",       "Oasis",              QList<int>({ 0, 0 }), imagePath, "oasis.png",              BFBC2Mod::BC2),     // 52
    BFBC2LevelEntry("levels/bc1_harvest_day_sdm", "Harvest Day",        QList<int>({ 0, 0 }), imagePath, "harvest_day.png",        BFBC2Mod::BC2),     // 53
    BFBC2LevelEntry("levels/mp_sp_002sdm",        "Cold War",           QList<int>({ 0, 0 }), imagePath, "cold_war.png",           BFBC2Mod::BC2),     // 54
    BFBC2LevelEntry("levels/mp_sp_005sdm",        "Heavy Metal",        QList<int>({ 0, 0 }), imagePath, "heavy_metal.png",        BFBC2Mod::BC2),     // 55

    BFBC2LevelEntry("levels/nam_mp_002sdm",       "Vantage Point",      QList<int>({ 0, 0 }), imagePath, "vantage_point.png",      BFBC2Mod::VIETNAM), // 56
    BFBC2LevelEntry("levels/nam_mp_003sdm",       "Hill 137",           QList<int>({ 0, 0 }), imagePath, "hill_137.png",           BFBC2Mod::VIETNAM), // 57
    BFBC2LevelEntry("levels/nam_mp_005sdm",       "Cao Son Temple",     QList<int>({ 0, 0 }), imagePath, "cao_son_temple.png",     BFBC2Mod::VIETNAM), // 58
    BFBC2LevelEntry("levels/nam_mp_006sdm",       "Phu Bai Valley",     QList<int>({ 0, 0 }), imagePath, "phu_bai_valley.png",     BFBC2Mod::VIETNAM), // 59
    BFBC2LevelEntry("levels/nam_mp_007sdm",       "Operation Hastings", QList<int>({ 0, 0 }), imagePath, "operation_hastings.png", BFBC2Mod::VIETNAM)  // 60
};

template<>
QList<GameModeEntry> BFBC2LevelDictionary::gameModeList = {
    /* List of all gamemodes */
    GameModeEntry("CONQUEST", "Conquest",         32),
    GameModeEntry("RUSH",     "Rush",             32),
    GameModeEntry("SQRUSH",   "Squadrush",        32),
    GameModeEntry("SQDM",     "Squad Deathmatch", 32)
};

template<>
QMultiHash<int, int> BFBC2LevelDictionary::levelMap = {
    /* List of all levels and gamemodes combined */
    /* CONQUEST */
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
    { 0, 10 },

    // XP1 (Vietnam)
    { 0, 11 },
    { 0, 12 },
    { 0, 13 },
    { 0, 14 },
    { 0, 15 },

    /* RUSH */
    { 1, 16 },
    { 1, 17 },
    { 1, 18 },
    { 1, 19 },
    { 1, 20 },
    { 1, 21 },
    { 1, 22 },
    { 1, 23 },
    { 1, 24 },
    { 1, 25 },
    { 1, 26 },

    // XP1 (Vietnam)
    { 1, 27 },
    { 1, 28 },
    { 1, 29 },
    { 1, 30 },
    { 1, 31 },

    /* SQRUSH */
    { 2, 32 },
    { 2, 33 },
    { 2, 34 },
    { 2, 35 },
    { 2, 36 },
    { 2, 37 },
    { 2, 38 },
    { 2, 39 },
    { 2, 40 },

    // XP1 (Vietnam)
    { 2, 41 },
    { 2, 42 },
    { 2, 43 },
    { 2, 44 },
    { 2, 45 },

    /* SQDM */
    { 3, 46 },
    { 3, 47 },
    { 3, 48 },
    { 3, 49 },
    { 3, 50 },
    { 3, 51 },
    { 3, 52 },
    { 3, 53 },
    { 3, 54 },
    { 3, 55 },

    // XP1 (Vietnam)
    { 3, 56 },
    { 3, 57 },
    { 3, 58 },
    { 3, 59 },
    { 3, 60 }
};
