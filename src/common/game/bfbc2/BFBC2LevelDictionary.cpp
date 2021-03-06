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

#include "BFBC2LevelDictionary.h"
#include "TeamEntry.h"
#include "BFBC2LevelEntry.h"
#include "BFBC2Mod.h"
#include "GameModeEntry.h"

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
    BFBC2LevelEntry("Levels/MP_001",              "Panama Canal",       QList<int>({ 1, 2 }), imagePath, "panama_canal.png",       BFBC2ModEnum::BC2),     // 0
    BFBC2LevelEntry("Levels/MP_003",              "Laguna Alta",        QList<int>({ 1, 2 }), imagePath, "laguna_alta.png",        BFBC2ModEnum::BC2),     // 1
    BFBC2LevelEntry("Levels/MP_005",              "Atacama Desert",     QList<int>({ 1, 2 }), imagePath, "atacama_desert.png",     BFBC2ModEnum::BC2),     // 2
    BFBC2LevelEntry("Levels/MP_006CQ",            "Arica Harbor",       QList<int>({ 1, 2 }), imagePath, "arica_harbor.png",       BFBC2ModEnum::BC2),     // 3
    BFBC2LevelEntry("Levels/MP_007",              "White Pass",         QList<int>({ 1, 2 }), imagePath, "white_pass.png",         BFBC2ModEnum::BC2),     // 4
    BFBC2LevelEntry("Levels/MP_008CQ",            "Nelson Bay",         QList<int>({ 1, 2 }), imagePath, "nelson_bay.png",         BFBC2ModEnum::BC2),     // 5
    BFBC2LevelEntry("Levels/MP_009CQ",            "Laguna Presa",       QList<int>({ 1, 2 }), imagePath, "laguna_presa.png",       BFBC2ModEnum::BC2),     // 6
    BFBC2LevelEntry("Levels/MP_012CQ",            "Port Valdez",        QList<int>({ 1, 2 }), imagePath, "port_valdez.png",        BFBC2ModEnum::BC2),     // 7
    BFBC2LevelEntry("Levels/BC1_OASIS_CQ",        "Oasis",              QList<int>({ 1, 2 }), imagePath, "oasis.png",              BFBC2ModEnum::BC2),     // 8
    BFBC2LevelEntry("Levels/BC1_HARVEST_DAY_CQ",  "Harvest Day",        QList<int>({ 1, 2 }), imagePath, "harvest_day.png",        BFBC2ModEnum::BC2),     // 9
    BFBC2LevelEntry("Levels/MP_sp_005CQ",         "Heavy Metal",        QList<int>({ 1, 2 }), imagePath, "heavy_metal.png",        BFBC2ModEnum::BC2),     // 10

    BFBC2LevelEntry("Levels/NAM_MP_002CQ",        "Vantage Point",      QList<int>({ 1, 3 }), imagePath, "vantage_point.png",      BFBC2ModEnum::VIETNAM), // 11
    BFBC2LevelEntry("Levels/NAM_MP_003CQ",        "Hill 137",           QList<int>({ 1, 3 }), imagePath, "hill_137.png",           BFBC2ModEnum::VIETNAM), // 12
    BFBC2LevelEntry("Levels/NAM_MP_005CQ",        "Cao Son Temple",     QList<int>({ 1, 3 }), imagePath, "cao_son_temple.png",     BFBC2ModEnum::VIETNAM), // 13
    BFBC2LevelEntry("Levels/NAM_MP_006CQ",        "Phu Bai Valley",     QList<int>({ 1, 3 }), imagePath, "phu_bai_valley.png",     BFBC2ModEnum::VIETNAM), // 14
    BFBC2LevelEntry("Levels/NAM_MP_007CQ",        "Operation Hastings", QList<int>({ 1, 3 }), imagePath, "operation_hastings.png", BFBC2ModEnum::VIETNAM), // 15

    BFBC2LevelEntry("Levels/MP_002",              "Valparaíso",         QList<int>({ 1, 2 }), imagePath, "valparaiso.png",         BFBC2ModEnum::BC2),     // 16
    BFBC2LevelEntry("Levels/MP_004",              "Isla Inocentes",     QList<int>({ 1, 2 }), imagePath, "isla_inocentes.png",     BFBC2ModEnum::BC2),     // 17
    BFBC2LevelEntry("Levels/MP_005GR",            "Atacama Desert",     QList<int>({ 1, 2 }), imagePath, "atacama_desert.png",     BFBC2ModEnum::BC2),     // 18
    BFBC2LevelEntry("Levels/MP_006",              "Arica Harbor",       QList<int>({ 1, 2 }), imagePath, "arica_harbor.png",       BFBC2ModEnum::BC2),     // 19
    BFBC2LevelEntry("Levels/MP_007GR",            "White Pass",         QList<int>({ 1, 2 }), imagePath, "white_pass.png",         BFBC2ModEnum::BC2),     // 20
    BFBC2LevelEntry("Levels/MP_008",              "Nelson Bay",         QList<int>({ 1, 2 }), imagePath, "nelson_bay.png",         BFBC2ModEnum::BC2),     // 21
    BFBC2LevelEntry("Levels/MP_009GR",            "Laguna Presa",       QList<int>({ 1, 2 }), imagePath, "laguna_presa.png",       BFBC2ModEnum::BC2),     // 22
    BFBC2LevelEntry("Levels/MP_012GR",            "Port Valdez",        QList<int>({ 1, 2 }), imagePath, "port_valdez.png",        BFBC2ModEnum::BC2),     // 23
    BFBC2LevelEntry("Levels/BC1_OASIS_GR",        "Oasis",              QList<int>({ 1, 2 }), imagePath, "oasis.png",              BFBC2ModEnum::BC2),     // 24
    BFBC2LevelEntry("Levels/BC1_HARVEST_DAY_GR",  "Harvest Day",        QList<int>({ 1, 2 }), imagePath, "harvest_day.png",        BFBC2ModEnum::BC2),     // 25
    BFBC2LevelEntry("Levels/MP_sp_002GR",         "Cold War",           QList<int>({ 1, 2 }), imagePath, "cold_war.png",           BFBC2ModEnum::BC2),     // 26

    BFBC2LevelEntry("Levels/NAM_MP_002R",         "Vantage Point",      QList<int>({ 1, 3 }), imagePath, "vantage_point.png",      BFBC2ModEnum::VIETNAM), // 27
    BFBC2LevelEntry("Levels/NAM_MP_003R",         "Hill 137",           QList<int>({ 1, 3 }), imagePath, "hill_137.png",           BFBC2ModEnum::VIETNAM), // 28
    BFBC2LevelEntry("Levels/NAM_MP_005R",         "Cao Son Temple",     QList<int>({ 1, 3 }), imagePath, "cao_son_temple.png",     BFBC2ModEnum::VIETNAM), // 29
    BFBC2LevelEntry("Levels/NAM_MP_006R",         "Phu Bai Valley",     QList<int>({ 1, 3 }), imagePath, "phi_bai_valley.png",     BFBC2ModEnum::VIETNAM), // 30
    BFBC2LevelEntry("Levels/NAM_MP_007R",         "Operation Hastings", QList<int>({ 1, 3 }), imagePath, "operation_hastings.png", BFBC2ModEnum::VIETNAM), // 31

    BFBC2LevelEntry("Levels/MP_001SR",            "Panama Canal",       QList<int>({ 1, 2 }), imagePath, "panama_canal.png",       BFBC2ModEnum::BC2),     // 32
    BFBC2LevelEntry("Levels/MP_002SR",            "Valparaíso",         QList<int>({ 1, 2 }), imagePath, "valparaiso.png",         BFBC2ModEnum::BC2),     // 33
    BFBC2LevelEntry("Levels/MP_003SR",            "Laguna Alta",        QList<int>({ 1, 2 }), imagePath, "laguna_alta.png",        BFBC2ModEnum::BC2),     // 34
    BFBC2LevelEntry("Levels/MP_005SR",            "Atacama Desert",     QList<int>({ 1, 2 }), imagePath, "atacama_desert.png",     BFBC2ModEnum::BC2),     // 35
    BFBC2LevelEntry("Levels/MP_009SR",            "Laguna Presa",       QList<int>({ 1, 2 }), imagePath, "laguna_presa.png",       BFBC2ModEnum::BC2),     // 36
    BFBC2LevelEntry("Levels/MP_012SR",            "Port Valdez",        QList<int>({ 1, 2 }), imagePath, "port_valdez.png",        BFBC2ModEnum::BC2),     // 37
    BFBC2LevelEntry("Levels/BC1_OASIS_SR",        "Oasis",              QList<int>({ 1, 2 }), imagePath, "oasis.png",              BFBC2ModEnum::BC2),     // 38
    BFBC2LevelEntry("Levels/BC1_HARVEST_DAY_SR",  "Harvest Day",        QList<int>({ 1, 2 }), imagePath, "harvest_day.png",        BFBC2ModEnum::BC2),     // 39
    BFBC2LevelEntry("Levels/MP_SP_002SR",         "Cold War",           QList<int>({ 1, 2 }), imagePath, "cold_war.png",           BFBC2ModEnum::BC2),     // 40

    BFBC2LevelEntry("Levels/NAM_MP_002SR",        "Vantage Point",      QList<int>({ 1, 3 }), imagePath, "vantage_point.png",      BFBC2ModEnum::VIETNAM), // 41
    BFBC2LevelEntry("Levels/NAM_MP_003SR",        "Hill 137",           QList<int>({ 1, 3 }), imagePath, "hill_137.png",           BFBC2ModEnum::VIETNAM), // 42
    BFBC2LevelEntry("Levels/NAM_MP_005SR",        "Cao Son Temple",     QList<int>({ 1, 3 }), imagePath, "cao_son_temple.png",     BFBC2ModEnum::VIETNAM), // 43
    BFBC2LevelEntry("Levels/NAM_MP_006SR",        "Phu Bai Valley",     QList<int>({ 1, 3 }), imagePath, "phu_bai_valley.png",     BFBC2ModEnum::VIETNAM), // 44
    BFBC2LevelEntry("Levels/NAM_MP_007SR",        "Operation Hastings", QList<int>({ 1, 3 }), imagePath, "operation_hastings.png", BFBC2ModEnum::VIETNAM), // 45

    BFBC2LevelEntry("Levels/MP_001SDM",           "Panama Canal",       QList<int>({ 1, 2, 1, 2 }), imagePath, "panama_canal.png",       BFBC2ModEnum::BC2),     // 46
    BFBC2LevelEntry("Levels/MP_004SDM",           "Isla Inocentes",     QList<int>({ 1, 2, 1, 2 }), imagePath, "isla_inocentes.png",     BFBC2ModEnum::BC2),     // 47
    BFBC2LevelEntry("Levels/MP_006SDM",           "Arica Harbor",       QList<int>({ 1, 2, 1, 2 }), imagePath, "arica_harbor.png",       BFBC2ModEnum::BC2),     // 48
    BFBC2LevelEntry("Levels/MP_007SDM",           "White Pass",         QList<int>({ 1, 2, 1, 2 }), imagePath, "white_pass.png",         BFBC2ModEnum::BC2),     // 49
    BFBC2LevelEntry("Levels/MP_008SDM",           "Nelson Bay",         QList<int>({ 1, 2, 1, 2 }), imagePath, "nelson_bay.png",         BFBC2ModEnum::BC2),     // 50
    BFBC2LevelEntry("Levels/MP_009SDM",           "Laguna Presa",       QList<int>({ 1, 2, 1, 2 }), imagePath, "laguna_presa.png",       BFBC2ModEnum::BC2),     // 51
    BFBC2LevelEntry("Levels/BC1_OASIS_SDM",       "Oasis",              QList<int>({ 1, 2, 2, 2 }), imagePath, "oasis.png",              BFBC2ModEnum::BC2),     // 52
    BFBC2LevelEntry("Levels/BC1_HARVEST_DAY_SDM", "Harvest Day",        QList<int>({ 1, 2, 2, 2 }), imagePath, "harvest_day.png",        BFBC2ModEnum::BC2),     // 53
    BFBC2LevelEntry("Levels/MP_SP_002SDM",        "Cold War",           QList<int>({ 1, 2, 2, 2 }), imagePath, "cold_war.png",           BFBC2ModEnum::BC2),     // 54
    BFBC2LevelEntry("Levels/MP_SP_005SDM",        "Heavy Metal",        QList<int>({ 1, 2, 2, 2 }), imagePath, "heavy_metal.png",        BFBC2ModEnum::BC2),     // 55

    BFBC2LevelEntry("Levels/NAM_MP_002SDM",       "Vantage Point",      QList<int>({ 1, 3, 3, 3 }), imagePath, "vantage_point.png",      BFBC2ModEnum::VIETNAM), // 56
    BFBC2LevelEntry("Levels/NAM_MP_003SDM",       "Hill 137",           QList<int>({ 1, 3, 3, 3 }), imagePath, "hill_137.png",           BFBC2ModEnum::VIETNAM), // 57
    BFBC2LevelEntry("Levels/NAM_MP_005SDM",       "Cao Son Temple",     QList<int>({ 1, 3, 3, 3 }), imagePath, "cao_son_temple.png",     BFBC2ModEnum::VIETNAM), // 58
    BFBC2LevelEntry("Levels/NAM_MP_006SDM",       "Phu Bai Valley",     QList<int>({ 1, 3, 3, 3 }), imagePath, "phu_bai_valley.png",     BFBC2ModEnum::VIETNAM), // 59
    BFBC2LevelEntry("Levels/NAM_MP_007SDM",       "Operation Hastings", QList<int>({ 1, 3, 3, 3 }), imagePath, "operation_hastings.png", BFBC2ModEnum::VIETNAM)  // 60
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
