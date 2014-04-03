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

#include "BFBC2Levels.h"

BFBC2Levels::BFBC2Levels(QObject *parent) : BFLevels(parent)
{
    /* List of all levels */
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_001", "Panama Canal", "BC2"));                 // 0
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_003", "Laguna Alta", "BC2"));                  // 1
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_005", "Atacama Desert", "BC2"));               // 2
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_006cq", "Arica Harbor", "BC2"));               // 3
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_007", "White Pass", "BC2"));                   // 4
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_008cq", "Nelson Bay", "BC2"));                 // 5
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_009cq", "Laguna Presa", "BC2"));               // 6
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_012cq", "Port Valdez", "BC2"));                // 7
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/bc1_oasis_cq", "Oasis", "BC2"));                  // 8
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/bc1_harvest_day_cq", "Harvest Day", "BC2"));      // 9
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/mp_sp_005cq", "Heavy Metal", "BC2"));             // 10

    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/nam_mp_002cq", "Vantage Point", "VIETNAM"));      // 11
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/nam_mp_003cq", "Hill 137", "VIETNAM"));           // 12
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/nam_mp_005cq", "Cao Son Temple", "VIETNAM"));     // 13
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/nam_mp_006cq", "Phu Bai Valley", "VIETNAM"));     // 14
    levelList.append(BFBC2LevelEntry("CONQUEST", "levels/nam_mp_007cq", "Operation Hastings", "VIETNAM")); // 15

    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_002", "Valparaíso", "BC2"));                       // 16
    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_004", "Isla Inocentes", "BC2"));                   // 17
    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_005gr", "Atacama Desert", "BC2"));         // 18
    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_006", "Arica Harbor", "BC2"));             // 19
    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_007gr", "White Pass", "BC2"));                     // 20
    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_008", "Nelson Bay", "BC2"));                       // 21
    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_009gr", "Laguna Presa", "BC2"));                   // 22
    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_012gr", "Port Valdez", "BC2"));                    // 23
    levelList.append(BFBC2LevelEntry("RUSH", "levels/bc1_oasis_gr", "Oasis", "BC2"));                      // 24
    levelList.append(BFBC2LevelEntry("RUSH", "levels/bc1_harvest_day_gr", "Harvest Day", "BC2"));          // 25
    levelList.append(BFBC2LevelEntry("RUSH", "levels/mp_sp_002gr", "Cold War", "BC2"));                    // 26

    levelList.append(BFBC2LevelEntry("RUSH", "levels/nam_mp_002r", "Vantage Point", "VIETNAM"));           // 27
    levelList.append(BFBC2LevelEntry("RUSH", "levels/nam_mp_003r", "Hill 137", "VIETNAM"));                // 28
    levelList.append(BFBC2LevelEntry("RUSH", "levels/nam_mp_005r", "Cao Son Temple", "VIETNAM"));          // 29
    levelList.append(BFBC2LevelEntry("RUSH", "levels/nam_mp_006r", "Phu Bai Valley", "VIETNAM"));          // 30
    levelList.append(BFBC2LevelEntry("RUSH", "levels/nam_mp_007r", "Operation Hastings", "VIETNAM"));      // 31

    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/mp_001sr", "Panama Canal", "BC2"));                 // 32
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/mp_002sr", "Valparaíso", "BC2"));                   // 33
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/mp_003sr", "Laguna Alta", "BC2"));                  // 34
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/mp_005sr", "Atacama Desert", "BC2"));               // 35
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/mp_009sr", "Laguna Presa", "BC2"));                 // 36
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/mp_012sr", "Port Valdez", "BC2"));                  // 37
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/bc1_oasis_sr", "Oasis", "BC2"));                    // 38
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/bc1_harvest_day_sr", "Harvest Day", "BC2"));        // 39
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/mp_sp_002sr", "Cold War", "BC2"));                  // 40

    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/nam_mp_002sr", "Vantage Point", "VIETNAM"));        // 41
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/nam_mp_003sr", "Hill 137", "VIETNAM"));             // 42
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/nam_mp_005sr", "Cao Son Temple", "VIETNAM"));       // 43
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/nam_mp_006sr", "Phu Bai Valley", "VIETNAM"));       // 44
    levelList.append(BFBC2LevelEntry("SQRUSH", "levels/nam_mp_007sr", "Operation Hastings", "VIETNAM"));   // 45

    levelList.append(BFBC2LevelEntry("SQDM", "levels/mp_001sdm", "Panama Canal", "BC2"));                  // 46
    levelList.append(BFBC2LevelEntry("SQDM", "levels/mp_004sdm", "Isla Inocentes", "BC2"));                // 47
    levelList.append(BFBC2LevelEntry("SQDM", "levels/mp_006sdm", "Arica Harbor", "BC2"));                  // 48
    levelList.append(BFBC2LevelEntry("SQDM", "levels/mp_007sdm", "White Pass", "BC2"));                    // 49
    levelList.append(BFBC2LevelEntry("SQDM", "levels/mp_008sdm", "Nelson Bay", "BC2"));                    // 50
    levelList.append(BFBC2LevelEntry("SQDM", "levels/mp_009sdm", "Laguna Presa", "BC2"));                  // 51
    levelList.append(BFBC2LevelEntry("SQDM", "levels/bc1_oasis_sdm", "Oasis", "BC2"));                     // 52
    levelList.append(BFBC2LevelEntry("SQDM", "levels/bc1_harvest_day_sdm", "Harvest Day", "BC2"));         // 53
    levelList.append(BFBC2LevelEntry("SQDM", "levels/mp_sp_002sdm", "Cold War", "BC2"));                   // 54
    levelList.append(BFBC2LevelEntry("SQDM", "levels/mp_sp_005sdm", "Heavy Metal", "BC2"));                // 55

    levelList.append(BFBC2LevelEntry("SQDM", "levels/nam_mp_002sdm", "Vantage Point", "VIETNAM"));         // 56
    levelList.append(BFBC2LevelEntry("SQDM", "levels/nam_mp_003sdm", "Hill 137", "VIETNAM"));              // 57
    levelList.append(BFBC2LevelEntry("SQDM", "levels/nam_mp_005sdm", "Cao Son Temple", "VIETNAM"));        // 58
    levelList.append(BFBC2LevelEntry("SQDM", "levels/nam_mp_006sdm", "Phu Bai Valley", "VIETNAM"));        // 59
    levelList.append(BFBC2LevelEntry("SQDM", "levels/nam_mp_007sdm", "Operation Hastings", "VIETNAM"));    // 60

    /* List of all gamemodes */
    gameModeList.append(GameModeEntry("CONQUEST", "Conquest", 32));
    gameModeList.append(GameModeEntry("RUSH", "Rush", 32));
    gameModeList.append(GameModeEntry("SQRUSH", "Squadrush", 32));
    gameModeList.append(GameModeEntry("SQDM", "Squad Deathmatch", 32));

    /* Levels and gamemodes combined */

    /* CONQUEST */
    levelMap.insertMulti(0, 0);
    levelMap.insertMulti(0, 1);
    levelMap.insertMulti(0, 2);
    levelMap.insertMulti(0, 3);
    levelMap.insertMulti(0, 4);
    levelMap.insertMulti(0, 5);
    levelMap.insertMulti(0, 6);
    levelMap.insertMulti(0, 7);
    levelMap.insertMulti(0, 8);
    levelMap.insertMulti(0, 9);
    levelMap.insertMulti(0, 10);

    // XP1 (Vietnam)
    levelMap.insertMulti(0, 11);
    levelMap.insertMulti(0, 12);
    levelMap.insertMulti(0, 13);
    levelMap.insertMulti(0, 14);
    levelMap.insertMulti(0, 15);

    /* RUSH */
    levelMap.insertMulti(1, 16);
    levelMap.insertMulti(1, 17);
    levelMap.insertMulti(1, 18);
    levelMap.insertMulti(1, 19);
    levelMap.insertMulti(1, 20);
    levelMap.insertMulti(1, 21);
    levelMap.insertMulti(1, 22);
    levelMap.insertMulti(1, 23);
    levelMap.insertMulti(1, 24);
    levelMap.insertMulti(1, 25);
    levelMap.insertMulti(1, 26);

    // XP1 (Vietnam)
    levelMap.insertMulti(1, 27);
    levelMap.insertMulti(1, 28);
    levelMap.insertMulti(1, 29);
    levelMap.insertMulti(1, 30);
    levelMap.insertMulti(1, 31);

    /* SQRUSH */
    levelMap.insertMulti(2, 32);
    levelMap.insertMulti(2, 33);
    levelMap.insertMulti(2, 34);
    levelMap.insertMulti(2, 35);
    levelMap.insertMulti(2, 36);
    levelMap.insertMulti(2, 37);
    levelMap.insertMulti(2, 38);
    levelMap.insertMulti(2, 39);
    levelMap.insertMulti(2, 40);

    // XP1 (Vietnam)
    levelMap.insertMulti(2, 41);
    levelMap.insertMulti(2, 42);
    levelMap.insertMulti(2, 43);
    levelMap.insertMulti(2, 44);
    levelMap.insertMulti(2, 45);

    /* SQDM */
    levelMap.insertMulti(3, 46);
    levelMap.insertMulti(3, 47);
    levelMap.insertMulti(3, 48);
    levelMap.insertMulti(3, 49);
    levelMap.insertMulti(3, 50);
    levelMap.insertMulti(3, 51);
    levelMap.insertMulti(3, 52);
    levelMap.insertMulti(3, 53);
    levelMap.insertMulti(3, 54);
    levelMap.insertMulti(3, 55);

    // XP1 (Vietnam)
    levelMap.insertMulti(3, 56);
    levelMap.insertMulti(3, 57);
    levelMap.insertMulti(3, 58);
    levelMap.insertMulti(3, 59);
    levelMap.insertMulti(3, 60);
}

BFBC2Levels::~BFBC2Levels()
{

}
