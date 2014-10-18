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
#include "BFBC2Mod.h"
#include "GameModeEntry.h"
#include "GameModeLevel.h"

template<>
QList<TeamEntry> BFBC2LevelDictionary::teamList = {
    /* List of all teams */
    TeamEntry("Neutral"),                     // 0
    TeamEntry("US",  ":/bfbc2/teams/RU.png"), // 1
    TeamEntry("RU",  ":/bfbc2/teams/US.png"), // 2
    TeamEntry("NVA", ":/bfbc2/teams/NVA.png") // 3
};

template<>
QString BFBC2LevelDictionary::imagePath = ":/bfbc2/levels";

template<>
QList<BFBC2LevelEntry> BFBC2LevelDictionary::levelList = {
    /* List of all levels */
    BFBC2LevelEntry("levels/mp_001",              "Panama Canal",       imagePath, "panama_canal.png",       BFBC2Mod::BC2),     // 0
    BFBC2LevelEntry("levels/mp_003",              "Laguna Alta",        imagePath, "laguna_alta.png",        BFBC2Mod::BC2),     // 1
    BFBC2LevelEntry("levels/mp_005",              "Atacama Desert",     imagePath, "atacama_desert.png",     BFBC2Mod::BC2),     // 2
    BFBC2LevelEntry("levels/mp_006cq",            "Arica Harbor",       imagePath, "arica_harbor.png",       BFBC2Mod::BC2),     // 3
    BFBC2LevelEntry("levels/mp_007",              "White Pass",         imagePath, "white_pass.png",         BFBC2Mod::BC2),     // 4
    BFBC2LevelEntry("levels/mp_008cq",            "Nelson Bay",         imagePath, "nelson_bay.png",         BFBC2Mod::BC2),     // 5
    BFBC2LevelEntry("levels/mp_009cq",            "Laguna Presa",       imagePath, "laguna_presa.png",       BFBC2Mod::BC2),     // 6
    BFBC2LevelEntry("levels/mp_012cq",            "Port Valdez",        imagePath, "port_valdez.png",        BFBC2Mod::BC2),     // 7
    BFBC2LevelEntry("levels/bc1_oasis_cq",        "Oasis",              imagePath, "oasis.png",              BFBC2Mod::BC2),     // 8
    BFBC2LevelEntry("levels/bc1_harvest_day_cq",  "Harvest Day",        imagePath, "harvest_day.png",        BFBC2Mod::BC2),     // 9
    BFBC2LevelEntry("levels/mp_sp_005cq",         "Heavy Metal",        imagePath, "heavy_metal.png",        BFBC2Mod::BC2),     // 10

    BFBC2LevelEntry("levels/nam_mp_002cq",        "Vantage Point",      imagePath, "vantage_point.png",      BFBC2Mod::VIETNAM), // 11
    BFBC2LevelEntry("levels/nam_mp_003cq",        "Hill 137",           imagePath, "hill_137.png",           BFBC2Mod::VIETNAM), // 12
    BFBC2LevelEntry("levels/nam_mp_005cq",        "Cao Son Temple",     imagePath, "cao_son_temple.png",     BFBC2Mod::VIETNAM), // 13
    BFBC2LevelEntry("levels/nam_mp_006cq",        "Phu Bai Valley",     imagePath, "phu_bai_valley.png",     BFBC2Mod::VIETNAM), // 14
    BFBC2LevelEntry("levels/nam_mp_007cq",        "Operation Hastings", imagePath, "operation_hastings.png", BFBC2Mod::VIETNAM), // 15

    BFBC2LevelEntry("levels/mp_002",              "Valparaíso",         imagePath, "valparaiso.png",         BFBC2Mod::BC2),     // 16
    BFBC2LevelEntry("levels/mp_004",              "Isla Inocentes",     imagePath, "isla_inocentes.png",     BFBC2Mod::BC2),     // 17
    BFBC2LevelEntry("levels/mp_005gr",            "Atacama Desert",     imagePath, "atacama_desert.png",     BFBC2Mod::BC2),     // 18
    BFBC2LevelEntry("levels/mp_006",              "Arica Harbor",       imagePath, "arica_harbor.png",       BFBC2Mod::BC2),     // 19
    BFBC2LevelEntry("levels/mp_007gr",            "White Pass",         imagePath, "white_pass.png",         BFBC2Mod::BC2),     // 20
    BFBC2LevelEntry("levels/mp_008",              "Nelson Bay",         imagePath, "nelson_bay.png",         BFBC2Mod::BC2),     // 21
    BFBC2LevelEntry("levels/mp_009gr",            "Laguna Presa",       imagePath, "laguna_presa.png",       BFBC2Mod::BC2),     // 22
    BFBC2LevelEntry("levels/mp_012gr",            "Port Valdez",        imagePath, "port_valdez.png",        BFBC2Mod::BC2),     // 23
    BFBC2LevelEntry("levels/bc1_oasis_gr",        "Oasis",              imagePath, "oasis.png",              BFBC2Mod::BC2),     // 24
    BFBC2LevelEntry("levels/bc1_harvest_day_gr",  "Harvest Day",        imagePath, "harvest_day.png",        BFBC2Mod::BC2),     // 25
    BFBC2LevelEntry("levels/mp_sp_002gr",         "Cold War",           imagePath, "cold_war.png",           BFBC2Mod::BC2),     // 26

    BFBC2LevelEntry("levels/nam_mp_002r",         "Vantage Point",      imagePath, "vantage_point.png",      BFBC2Mod::VIETNAM), // 27
    BFBC2LevelEntry("levels/nam_mp_003r",         "Hill 137",           imagePath, "hill_137.png",           BFBC2Mod::VIETNAM), // 28
    BFBC2LevelEntry("levels/nam_mp_005r",         "Cao Son Temple",     imagePath, "cao_son_temple.png",     BFBC2Mod::VIETNAM), // 29
    BFBC2LevelEntry("levels/nam_mp_006r",         "Phu Bai Valley",     imagePath, "phi_bai_valley.png",     BFBC2Mod::VIETNAM), // 30
    BFBC2LevelEntry("levels/nam_mp_007r",         "Operation Hastings", imagePath, "operation_hastings.png", BFBC2Mod::VIETNAM), // 31

    BFBC2LevelEntry("levels/mp_001sr",            "Panama Canal",       imagePath, "panama_canal.png",       BFBC2Mod::BC2),     // 32
    BFBC2LevelEntry("levels/mp_002sr",            "Valparaíso",         imagePath, "valparaiso.png",         BFBC2Mod::BC2),     // 33
    BFBC2LevelEntry("levels/mp_003sr",            "Laguna Alta",        imagePath, "laguna_alta.png",        BFBC2Mod::BC2),     // 34
    BFBC2LevelEntry("levels/mp_005sr",            "Atacama Desert",     imagePath, "atacama_desert.png",     BFBC2Mod::BC2),     // 35
    BFBC2LevelEntry("levels/mp_009sr",            "Laguna Presa",       imagePath, "laguna_presa.png",       BFBC2Mod::BC2),     // 36
    BFBC2LevelEntry("levels/mp_012sr",            "Port Valdez",        imagePath, "port_valdez.png",        BFBC2Mod::BC2),     // 37
    BFBC2LevelEntry("levels/bc1_oasis_sr",        "Oasis",              imagePath, "oasis.png",              BFBC2Mod::BC2),     // 38
    BFBC2LevelEntry("levels/bc1_harvest_day_sr",  "Harvest Day",        imagePath, "harvest_day.png",        BFBC2Mod::BC2),     // 39
    BFBC2LevelEntry("levels/mp_sp_002sr",         "Cold War",           imagePath, "cold_war.png",           BFBC2Mod::BC2),     // 40

    BFBC2LevelEntry("levels/nam_mp_002sr",        "Vantage Point",      imagePath, "vantage_point.png",      BFBC2Mod::VIETNAM), // 41
    BFBC2LevelEntry("levels/nam_mp_003sr",        "Hill 137",           imagePath, "hill_137.png",           BFBC2Mod::VIETNAM), // 42
    BFBC2LevelEntry("levels/nam_mp_005sr",        "Cao Son Temple",     imagePath, "cao_son_temple.png",     BFBC2Mod::VIETNAM), // 43
    BFBC2LevelEntry("levels/nam_mp_006sr",        "Phu Bai Valley",     imagePath, "phu_bai_valley.png",     BFBC2Mod::VIETNAM), // 44
    BFBC2LevelEntry("levels/nam_mp_007sr",        "Operation Hastings", imagePath, "operation_hastings.png", BFBC2Mod::VIETNAM), // 45

    BFBC2LevelEntry("levels/mp_001sdm",           "Panama Canal",       imagePath, "panama_canal.png",       BFBC2Mod::BC2),     // 46
    BFBC2LevelEntry("levels/mp_004sdm",           "Isla Inocentes",     imagePath, "isla_inocentes.png",     BFBC2Mod::BC2),     // 47
    BFBC2LevelEntry("levels/mp_006sdm",           "Arica Harbor",       imagePath, "arica_harbor.png",       BFBC2Mod::BC2),     // 48
    BFBC2LevelEntry("levels/mp_007sdm",           "White Pass",         imagePath, "white_pass.png",         BFBC2Mod::BC2),     // 49
    BFBC2LevelEntry("levels/mp_008sdm",           "Nelson Bay",         imagePath, "nelson_bay.png",         BFBC2Mod::BC2),     // 50
    BFBC2LevelEntry("levels/mp_009sdm",           "Laguna Presa",       imagePath, "laguna_presa.png",       BFBC2Mod::BC2),     // 51
    BFBC2LevelEntry("levels/bc1_oasis_sdm",       "Oasis",              imagePath, "oasis.png",              BFBC2Mod::BC2),     // 52
    BFBC2LevelEntry("levels/bc1_harvest_day_sdm", "Harvest Day",        imagePath, "harvest_day.png",        BFBC2Mod::BC2),     // 53
    BFBC2LevelEntry("levels/mp_sp_002sdm",        "Cold War",           imagePath, "cold_war.png",           BFBC2Mod::BC2),     // 54
    BFBC2LevelEntry("levels/mp_sp_005sdm",        "Heavy Metal",        imagePath, "heavy_metal.png",        BFBC2Mod::BC2),     // 55

    BFBC2LevelEntry("levels/nam_mp_002sdm",       "Vantage Point",      imagePath, "vantage_point.png",      BFBC2Mod::VIETNAM), // 56
    BFBC2LevelEntry("levels/nam_mp_003sdm",       "Hill 137",           imagePath, "hill_137.png",           BFBC2Mod::VIETNAM), // 57
    BFBC2LevelEntry("levels/nam_mp_005sdm",       "Cao Son Temple",     imagePath, "cao_son_temple.png",     BFBC2Mod::VIETNAM), // 58
    BFBC2LevelEntry("levels/nam_mp_006sdm",       "Phu Bai Valley",     imagePath, "phu_bai_valley.png",     BFBC2Mod::VIETNAM), // 59
    BFBC2LevelEntry("levels/nam_mp_007sdm",       "Operation Hastings", imagePath, "operation_hastings.png", BFBC2Mod::VIETNAM)  // 60
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
QList<GameModeLevel> BFBC2LevelDictionary::levelMap = {
    /* List of all levels and gamemodes combined */
    /* CONQUEST */
    GameModeLevel(0, 0,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 1,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 2,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 3,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 4,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 5,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 6,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 7,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 8,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 9,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 10, QList<int>({ 1, 2 })),

    // XP1 (Vietnam)
    GameModeLevel(0, 11, QList<int>({ 1, 3 })),
    GameModeLevel(0, 12, QList<int>({ 1, 3 })),
    GameModeLevel(0, 13, QList<int>({ 1, 3 })),
    GameModeLevel(0, 14, QList<int>({ 1, 3 })),
    GameModeLevel(0, 15, QList<int>({ 1, 3 })),

    /* RUSH */
    GameModeLevel(1, 16, QList<int>({ 1, 2 })),
    GameModeLevel(1, 17, QList<int>({ 1, 2 })),
    GameModeLevel(1, 18, QList<int>({ 1, 2 })),
    GameModeLevel(1, 19, QList<int>({ 1, 2 })),
    GameModeLevel(1, 20, QList<int>({ 1, 2 })),
    GameModeLevel(1, 21, QList<int>({ 1, 2 })),
    GameModeLevel(1, 22, QList<int>({ 1, 2 })),
    GameModeLevel(1, 23, QList<int>({ 1, 2 })),
    GameModeLevel(1, 24, QList<int>({ 1, 2 })),
    GameModeLevel(1, 25, QList<int>({ 1, 2 })),
    GameModeLevel(1, 26, QList<int>({ 1, 2 })),

    // XP1 (Vietnam)
    GameModeLevel(1, 27, QList<int>({ 1, 3 })),
    GameModeLevel(1, 28, QList<int>({ 1, 3 })),
    GameModeLevel(1, 29, QList<int>({ 1, 3 })),
    GameModeLevel(1, 30, QList<int>({ 1, 3 })),
    GameModeLevel(1, 31, QList<int>({ 1, 3 })),

    /* SQRUSH */
    GameModeLevel(2, 32, QList<int>({ 1, 2 })),
    GameModeLevel(2, 33, QList<int>({ 1, 2 })),
    GameModeLevel(2, 34, QList<int>({ 1, 2 })),
    GameModeLevel(2, 35, QList<int>({ 1, 2 })),
    GameModeLevel(2, 36, QList<int>({ 1, 2 })),
    GameModeLevel(2, 37, QList<int>({ 1, 2 })),
    GameModeLevel(2, 38, QList<int>({ 1, 2 })),
    GameModeLevel(2, 39, QList<int>({ 1, 2 })),
    GameModeLevel(2, 40, QList<int>({ 1, 2 })),

    // XP1 (Vietnam)
    GameModeLevel(2, 41, QList<int>({ 1, 3 })),
    GameModeLevel(2, 42, QList<int>({ 1, 3 })),
    GameModeLevel(2, 43, QList<int>({ 1, 3 })),
    GameModeLevel(2, 44, QList<int>({ 1, 3 })),
    GameModeLevel(2, 45, QList<int>({ 1, 3 })),

    /* SQDM */
    GameModeLevel(3, 46, QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(3, 47, QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(3, 48, QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(3, 49, QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(3, 50, QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(3, 51, QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(3, 52, QList<int>({ 1, 2, 2, 2 })),
    GameModeLevel(3, 53, QList<int>({ 1, 2, 2, 2 })),
    GameModeLevel(3, 54, QList<int>({ 1, 2, 2, 2 })),
    GameModeLevel(3, 55, QList<int>({ 1, 2, 2, 2 })),

    // XP1 (Vietnam)
    GameModeLevel(3, 56, QList<int>({ 1, 3, 3, 3 })),
    GameModeLevel(3, 57, QList<int>({ 1, 3, 3, 3 })),
    GameModeLevel(3, 58, QList<int>({ 1, 3, 3, 3 })),
    GameModeLevel(3, 59, QList<int>({ 1, 3, 3, 3 })),
    GameModeLevel(3, 60, QList<int>({ 1, 3, 3, 3 }))
};
