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

BFBC2Levels::BFBC2Levels(QObject *parent) : BFLevels(":/bfbc2/levels/", parent)
{
    /* List of all levels */
    levelList.append(BFBC2LevelEntry("levels/mp_001", "Panama Canal", imagePath + "panama_canal.png", "BC2"));                          // 0
    levelList.append(BFBC2LevelEntry("levels/mp_003", "Laguna Alta", imagePath + "laguna_alta.png", "BC2"));                            // 1
    levelList.append(BFBC2LevelEntry("levels/mp_005", "Atacama Desert", imagePath + "atacama_desert.png", "BC2"));                      // 2
    levelList.append(BFBC2LevelEntry("levels/mp_006cq", "Arica Harbor", imagePath + "arica_harbor.png", "BC2"));                        // 3
    levelList.append(BFBC2LevelEntry("levels/mp_007", "White Pass", imagePath + "white_pass.png", "BC2"));                              // 4
    levelList.append(BFBC2LevelEntry("levels/mp_008cq", "Nelson Bay", imagePath + "nelson_bay.png", "BC2"));                            // 5
    levelList.append(BFBC2LevelEntry("levels/mp_009cq", "Laguna Presa", imagePath + "laguna_presa.png", "BC2"));                        // 6
    levelList.append(BFBC2LevelEntry("levels/mp_012cq", "Port Valdez", imagePath + "port_valdez.png", "BC2"));                          // 7
    levelList.append(BFBC2LevelEntry("levels/bc1_oasis_cq", "Oasis", imagePath + "oasis.png", "BC2"));                                  // 8
    levelList.append(BFBC2LevelEntry("levels/bc1_harvest_day_cq", "Harvest Day", imagePath + "harvest_day.png", "BC2"));                // 9
    levelList.append(BFBC2LevelEntry("levels/mp_sp_005cq", "Heavy Metal", imagePath + "heavy_metal.png", "BC2"));                       // 10

    levelList.append(BFBC2LevelEntry("levels/nam_mp_002cq", "Vantage Point", imagePath + "vantage_point.png", "VIETNAM"));              // 11
    levelList.append(BFBC2LevelEntry("levels/nam_mp_003cq", "Hill 137", imagePath + "hill_137.png", "VIETNAM"));                        // 12
    levelList.append(BFBC2LevelEntry("levels/nam_mp_005cq", "Cao Son Temple", imagePath + "cao_son_temple.png", "VIETNAM"));            // 13
    levelList.append(BFBC2LevelEntry("levels/nam_mp_006cq", "Phu Bai Valley", imagePath + "phu_bai_valley.png", "VIETNAM"));            // 14
    levelList.append(BFBC2LevelEntry("levels/nam_mp_007cq", "Operation Hastings", imagePath + "operation_hastings.png", "VIETNAM"));    // 15

    levelList.append(BFBC2LevelEntry("levels/mp_002", "Valparaíso", imagePath + "valparaiso.png", "BC2"));                              // 16
    levelList.append(BFBC2LevelEntry("levels/mp_004", "Isla Inocentes", imagePath + "isla_inocentes.png", "BC2"));                      // 17
    levelList.append(BFBC2LevelEntry("levels/mp_005gr", "Atacama Desert", imagePath + "atacama_desert.png", "BC2"));                    // 18
    levelList.append(BFBC2LevelEntry("levels/mp_006", "Arica Harbor", imagePath + "arica_harbor.png", "BC2"));                          // 19
    levelList.append(BFBC2LevelEntry("levels/mp_007gr", "White Pass", imagePath + "white_pass.png", "BC2"));                            // 20
    levelList.append(BFBC2LevelEntry("levels/mp_008", "Nelson Bay", imagePath + "nelson_bay.png", "BC2"));                              // 21
    levelList.append(BFBC2LevelEntry("levels/mp_009gr", "Laguna Presa", imagePath + "laguna_presa.png", "BC2"));                        // 22
    levelList.append(BFBC2LevelEntry("levels/mp_012gr", "Port Valdez", imagePath + "port_valdez.png", "BC2"));                          // 23
    levelList.append(BFBC2LevelEntry("levels/bc1_oasis_gr", "Oasis", imagePath + "oasis.png", "BC2"));                                  // 24
    levelList.append(BFBC2LevelEntry("levels/bc1_harvest_day_gr", "Harvest Day", imagePath + "harvest_day.png", "BC2"));                // 25
    levelList.append(BFBC2LevelEntry("levels/mp_sp_002gr", "Cold War", imagePath + "cold_war.png", "BC2"));                             // 26

    levelList.append(BFBC2LevelEntry("levels/nam_mp_002r", "Vantage Point", imagePath + "vantage_point.png", "VIETNAM"));               // 27
    levelList.append(BFBC2LevelEntry("levels/nam_mp_003r", "Hill 137", imagePath + "hill_137.png", "VIETNAM"));                         // 28
    levelList.append(BFBC2LevelEntry("levels/nam_mp_005r", "Cao Son Temple", imagePath + "cao_son_temple.png", "VIETNAM"));             // 29
    levelList.append(BFBC2LevelEntry("levels/nam_mp_006r", "Phu Bai Valley", imagePath + "phi_bai_valley.png", "VIETNAM"));             // 30
    levelList.append(BFBC2LevelEntry("levels/nam_mp_007r", "Operation Hastings", imagePath + "operation_hastings.png", "VIETNAM"));     // 31

    levelList.append(BFBC2LevelEntry("levels/mp_001sr", "Panama Canal", imagePath + "panama_canal.png", "BC2"));                        // 32
    levelList.append(BFBC2LevelEntry("levels/mp_002sr", "Valparaíso", imagePath + "valparaiso.png", "BC2"));                            // 33
    levelList.append(BFBC2LevelEntry("levels/mp_003sr", "Laguna Alta", imagePath + "laguna_alta.png", "BC2"));                          // 34
    levelList.append(BFBC2LevelEntry("levels/mp_005sr", "Atacama Desert", imagePath + "atacama_desert.png", "BC2"));                    // 35
    levelList.append(BFBC2LevelEntry("levels/mp_009sr", "Laguna Presa", imagePath + "laguna_presa.png", "BC2"));                        // 36
    levelList.append(BFBC2LevelEntry("levels/mp_012sr", "Port Valdez", imagePath + "port_valdez.png", "BC2"));                          // 37
    levelList.append(BFBC2LevelEntry("levels/bc1_oasis_sr", "Oasis", imagePath + "oasis.png", "BC2"));                                  // 38
    levelList.append(BFBC2LevelEntry("levels/bc1_harvest_day_sr", "Harvest Day", imagePath + "harvest_day.png", "BC2"));                // 39
    levelList.append(BFBC2LevelEntry("levels/mp_sp_002sr", "Cold War", imagePath + "cold_war.png", "BC2"));                             // 40

    levelList.append(BFBC2LevelEntry("levels/nam_mp_002sr", "Vantage Point", imagePath + "vantage_point.png", "VIETNAM"));              // 41
    levelList.append(BFBC2LevelEntry("levels/nam_mp_003sr", "Hill 137", imagePath + "hill_137.png", "VIETNAM"));                        // 42
    levelList.append(BFBC2LevelEntry("levels/nam_mp_005sr", "Cao Son Temple", imagePath + "cao_son_temple.png", "VIETNAM"));            // 43
    levelList.append(BFBC2LevelEntry("levels/nam_mp_006sr", "Phu Bai Valley", imagePath + "phu_bai_valley.png", "VIETNAM"));            // 44
    levelList.append(BFBC2LevelEntry("levels/nam_mp_007sr", "Operation Hastings", imagePath + "operation_hastings.png", "VIETNAM"));    // 45

    levelList.append(BFBC2LevelEntry("levels/mp_001sdm", "Panama Canal", imagePath + "panama_canal.png", "BC2"));                       // 46
    levelList.append(BFBC2LevelEntry("levels/mp_004sdm", "Isla Inocentes", imagePath + "isla_inocentes.png", "BC2"));                   // 47
    levelList.append(BFBC2LevelEntry("levels/mp_006sdm", "Arica Harbor", imagePath + "arica_harbor.png", "BC2"));                       // 48
    levelList.append(BFBC2LevelEntry("levels/mp_007sdm", "White Pass", imagePath + "white_pass.png", "BC2"));                           // 49
    levelList.append(BFBC2LevelEntry("levels/mp_008sdm", "Nelson Bay", imagePath + "nelson_bay.png", "BC2"));                           // 50
    levelList.append(BFBC2LevelEntry("levels/mp_009sdm", "Laguna Presa", imagePath + "laguna_presa.png", "BC2"));                       // 51
    levelList.append(BFBC2LevelEntry("levels/bc1_oasis_sdm", "Oasis", imagePath + "oasis.png", "BC2"));                                 // 52
    levelList.append(BFBC2LevelEntry("levels/bc1_harvest_day_sdm", "Harvest Day", imagePath + "harvest_day.png", "BC2"));               // 53
    levelList.append(BFBC2LevelEntry("levels/mp_sp_002sdm", "Cold War", imagePath + "cold_war.png", "BC2"));                            // 54
    levelList.append(BFBC2LevelEntry("levels/mp_sp_005sdm", "Heavy Metal", imagePath + "heavy_metal.png", "BC2"));                      // 55

    levelList.append(BFBC2LevelEntry("levels/nam_mp_002sdm", "Vantage Point", imagePath + "vantage_point.png", "VIETNAM"));             // 56
    levelList.append(BFBC2LevelEntry("levels/nam_mp_003sdm", "Hill 137", imagePath + "hill_137.png", "VIETNAM"));                       // 57
    levelList.append(BFBC2LevelEntry("levels/nam_mp_005sdm", "Cao Son Temple", imagePath + "cao_son_temple.png", "VIETNAM"));           // 58
    levelList.append(BFBC2LevelEntry("levels/nam_mp_006sdm", "Phu Bai Valley", imagePath + "phu_bai_valley.png", "VIETNAM"));           // 59
    levelList.append(BFBC2LevelEntry("levels/nam_mp_007sdm", "Operation Hastings", imagePath + "operation_hastings.png", "VIETNAM"));   // 60

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
