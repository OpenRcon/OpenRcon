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

BF3LevelDictionary::BF3LevelDictionary(QObject *parent) : LevelDictionary(":/bf3/levels/", parent)
{
    /* List of all levels */
    levelList.append(LevelEntry("MP_001", "Grand Bazaar", 0, 0, imagePath + "grand_bazaar.png"));                 // 0
    levelList.append(LevelEntry("MP_003", "Teheran Highway", 0, 0, imagePath + "teheran_highway.png"));           // 1
    levelList.append(LevelEntry("MP_007", "Caspian Border", 0, 0, imagePath + "caspian_border.png"));             // 2
    levelList.append(LevelEntry("MP_011", "Seine Crossing", 0, 0, imagePath + "seine_crossing.png"));             // 3
    levelList.append(LevelEntry("MP_012", "Operation Firestorm", 0, 0, imagePath + "operation_firestorm.png"));   // 4
    levelList.append(LevelEntry("MP_013", "Damavand Peak", 0, 0, imagePath + "damavand_peak.png"));               // 5
    levelList.append(LevelEntry("MP_017", "Noshahr Canals", 0, 0, imagePath + "noshahr_canals.png"));             // 6
    levelList.append(LevelEntry("MP_018", "Kharg Island", 0, 0, imagePath + "kharg_island.png"));                 // 7
    levelList.append(LevelEntry("MP_Subway", "Operation Metro", 0, 0, imagePath + "operation_metro.png"));        // 8

    // XP1 (Back to Karkand)
    levelList.append(LevelEntry("XP1_001", "Strike at Karkand", 0, 0, imagePath + "strike_at_karkand.png"));      // 9
    levelList.append(LevelEntry("XP1_002", "Gulf of Oman", 0, 0, imagePath + "gulf_of_oman.png"));                // 10
    levelList.append(LevelEntry("XP1_003", "Sharqi Peninsula", 0, 0, imagePath + "sharqi_peninsula.png"));        // 11
    levelList.append(LevelEntry("XP1_004", "Wake Island", 0, 0, imagePath + "wake_island.png"));                  // 12

    // XP2 (Close Quarters)
    levelList.append(LevelEntry("XP2_Factory", "Scrapmetal", 0, 0, imagePath + "scrapmetal.png"));                // 13
    levelList.append(LevelEntry("XP2_Office", "Operation 925", 0, 0, imagePath + "operation_925.png"));           // 14
    levelList.append(LevelEntry("XP2_Palace", "Donya Fortress", 0, 0, imagePath + "donya_fortress.png"));         // 15
    levelList.append(LevelEntry("XP2_Skybar", "Ziba Tower", 0, 0, imagePath + "ziba_tower.png"));                 // 16

    // XP3 (Armored Kill)
    levelList.append(LevelEntry("XP3_Desert", "Bandar Desert", 0, 0, imagePath + "bandar_desert.png"));           // 17
    levelList.append(LevelEntry("XP3_Alborz", "Alborz Mountains", 0, 0, imagePath + "alborz_mountains.png"));     // 18
    levelList.append(LevelEntry("XP3_Shield", "Armored Shield", 0, 0, imagePath + "armored_shield.png"));         // 19
    levelList.append(LevelEntry("XP3_Valley", "Death Valley", 0, 0, imagePath + "death_valley.png"));             // 20

    // XP4 (Aftermath)
    levelList.append(LevelEntry("XP4_Quake", "Epicenter", 0, 0, imagePath + "epicenter.png"));                    // 21
    levelList.append(LevelEntry("XP4_FD", "Markaz Monolith", 0, 0, imagePath + "markaz_monolith.png"));           // 22
    levelList.append(LevelEntry("XP4_Parl", "Azadi Palace", 0, 0, imagePath + "azadi_palace.png"));               // 23
    levelList.append(LevelEntry("XP4_Rubble", "Talah Market", 0, 0, imagePath + "talah_market.png"));             // 24

    // XP5 (Endgame)
    levelList.append(LevelEntry("XP5_001", "Operation Riverside", 0, 0, imagePath + "operation_riverside.png"));  // 25
    levelList.append(LevelEntry("XP5_002", "Nebandan Flats", 0, 0, imagePath + "nebandan_flats.png"));            // 26
    levelList.append(LevelEntry("XP5_003", "Kiasar Railroad", 0, 0, imagePath + "kiasar_railroad.png"));          // 27
    levelList.append(LevelEntry("XP5_004", "Sabalan Pipeline", 0, 0, imagePath + "sabalan_pipeline.png"));        // 28

    /* List of all gamemodes */
    gameModeList.append(GameModeEntry("ConquestLarge0", "Conquest Large", 64));                 // 0
    gameModeList.append(GameModeEntry("ConquestSmall0", "Conquest Small", 32));                 // 1
    gameModeList.append(GameModeEntry("RushLarge0", "Rush", 32));                               // 2
    gameModeList.append(GameModeEntry("SquadRush0", "Squad Rush", 8));                          // 3
    gameModeList.append(GameModeEntry("SquadDeathMatch0", "Squad Deathmatch", 16));             // 4
    gameModeList.append(GameModeEntry("TeamDeathMatch0", "Team Deathmatch", 24));               // 5
    gameModeList.append(GameModeEntry("ConquestAssaultLarge0", "Conquest Assault Large", 64));  // 6
    gameModeList.append(GameModeEntry("ConquestAssaultSmall0", "Conquest Assault Small", 32));  // 7
    gameModeList.append(GameModeEntry("ConquestAssaultSmall1", "Conquest Assault Small", 32));  // 8
    gameModeList.append(GameModeEntry("Domination0", "Domination", 16));                        // 9
    gameModeList.append(GameModeEntry("GunMaster0", "Gun master", 16));                         // 10
    gameModeList.append(GameModeEntry("TeamDeathMatchC0", "TDM Close Quarters", 16));           // 11
    gameModeList.append(GameModeEntry("TankSuperiority0", "Tank Superiority", 24));             // 12
    gameModeList.append(GameModeEntry("Scavenger0", "Scavenger", 32));                          // 13
    gameModeList.append(GameModeEntry("CaptureTheFlag0", "Capture The Flag", 32));              // 14
    gameModeList.append(GameModeEntry("AirSuperiority0", "Air Superiority", 24));               // 15

    /* Levels and gamemodes combined */

    /* ConquestLarge0 */
    levelMap.insertMulti(0, 0);
    levelMap.insertMulti(0, 1);
    levelMap.insertMulti(0, 2);
    levelMap.insertMulti(0, 3);
    levelMap.insertMulti(0, 4);
    levelMap.insertMulti(0, 5);
    levelMap.insertMulti(0, 6);
    levelMap.insertMulti(0, 7);
    levelMap.insertMulti(0, 8);

    // XP1 (Back to Karkand)
    levelMap.insertMulti(0, 10);

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    levelMap.insertMulti(0, 17);
    levelMap.insertMulti(0, 18);
    levelMap.insertMulti(0, 19);
    levelMap.insertMulti(0, 20);

    // XP4 (Aftermath)
    levelMap.insertMulti(0, 21);
    levelMap.insertMulti(0, 22);
    levelMap.insertMulti(0, 23);
    levelMap.insertMulti(0, 24);

    // XP5 (Endgame)
    levelMap.insertMulti(0, 25);
    levelMap.insertMulti(0, 26);
    levelMap.insertMulti(0, 27);
    levelMap.insertMulti(0, 28);

    /* ConquestSmall0 */
    levelMap.insertMulti(1, 0);
    levelMap.insertMulti(1, 1);
    levelMap.insertMulti(1, 2);
    levelMap.insertMulti(1, 3);
    levelMap.insertMulti(1, 4);
    levelMap.insertMulti(1, 5);
    levelMap.insertMulti(1, 6);
    levelMap.insertMulti(1, 7);
    levelMap.insertMulti(1, 8);

    // XP1 (Back to Karkand)
    levelMap.insertMulti(1, 10);

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    levelMap.insertMulti(1, 17);
    levelMap.insertMulti(1, 18);
    levelMap.insertMulti(1, 19);
    levelMap.insertMulti(1, 20);

    // XP4 (Aftermath)
    levelMap.insertMulti(1, 21);
    levelMap.insertMulti(1, 22);
    levelMap.insertMulti(1, 23);
    levelMap.insertMulti(1, 24);

    // XP5 (Endgame)
    levelMap.insertMulti(1, 25);
    levelMap.insertMulti(1, 26);
    levelMap.insertMulti(1, 27);
    levelMap.insertMulti(1, 28);

    /* RushLarge0 */
    levelMap.insertMulti(2, 0);
    levelMap.insertMulti(2, 1);
    levelMap.insertMulti(2, 2);
    levelMap.insertMulti(2, 3);
    levelMap.insertMulti(2, 4);
    levelMap.insertMulti(2, 5);
    levelMap.insertMulti(2, 6);
    levelMap.insertMulti(2, 7);
    levelMap.insertMulti(2, 8);

    // XP1 (Back to Karkand)
    levelMap.insertMulti(2, 9);
    levelMap.insertMulti(2, 10);
    levelMap.insertMulti(2, 11);
    levelMap.insertMulti(2, 12);

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    levelMap.insertMulti(2, 17);
    levelMap.insertMulti(2, 18);
    levelMap.insertMulti(2, 19);
    levelMap.insertMulti(2, 20);

    // XP4 (Aftermath)
    levelMap.insertMulti(2, 21);
    levelMap.insertMulti(2, 22);
    levelMap.insertMulti(2, 23);
    levelMap.insertMulti(2, 24);

    // XP5 (Endgame)
    levelMap.insertMulti(2, 25);
    levelMap.insertMulti(2, 26);
    levelMap.insertMulti(2, 27);
    levelMap.insertMulti(2, 28);

    /* SquadRush0 */
    levelMap.insertMulti(3, 0);
    levelMap.insertMulti(3, 1);
    levelMap.insertMulti(3, 2);
    levelMap.insertMulti(3, 3);
    levelMap.insertMulti(3, 4);
    levelMap.insertMulti(3, 5);
    levelMap.insertMulti(3, 6);
    levelMap.insertMulti(3, 7);
    levelMap.insertMulti(3, 8);

    // XP1 (Back to Karkand)
    levelMap.insertMulti(3, 9);
    levelMap.insertMulti(3, 10);
    levelMap.insertMulti(3, 11);
    levelMap.insertMulti(3, 12);

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    levelMap.insertMulti(3, 17);
    levelMap.insertMulti(3, 18);
    levelMap.insertMulti(3, 19);
    levelMap.insertMulti(3, 20);

    // XP4 (Aftermath)
    levelMap.insertMulti(3, 21);
    levelMap.insertMulti(3, 22);
    levelMap.insertMulti(3, 23);
    levelMap.insertMulti(3, 24);

    // XP5 (Endgame)
    levelMap.insertMulti(3, 25);
    levelMap.insertMulti(3, 26);
    levelMap.insertMulti(3, 27);
    levelMap.insertMulti(3, 28);

    /* SquadDeathMatch0 */
    levelMap.insertMulti(4, 0);
    levelMap.insertMulti(4, 1);
    levelMap.insertMulti(4, 2);
    levelMap.insertMulti(4, 3);
    levelMap.insertMulti(4, 4);
    levelMap.insertMulti(4, 5);
    levelMap.insertMulti(4, 6);
    levelMap.insertMulti(4, 7);
    levelMap.insertMulti(4, 8);

    // XP1 (Back to Karkand)
    levelMap.insertMulti(4, 9);
    levelMap.insertMulti(4, 10);
    levelMap.insertMulti(4, 11);
    levelMap.insertMulti(4, 12);

    // XP2 (Close Quarters)
    levelMap.insertMulti(4, 13);
    levelMap.insertMulti(4, 14);
    levelMap.insertMulti(4, 15);
    levelMap.insertMulti(4, 16);

    // XP3 (Armored Kill)
    levelMap.insertMulti(4, 17);
    levelMap.insertMulti(4, 18);
    levelMap.insertMulti(4, 19);
    levelMap.insertMulti(4, 20);

    // XP4 (Aftermath)
    levelMap.insertMulti(4, 21);
    levelMap.insertMulti(4, 22);
    levelMap.insertMulti(4, 23);
    levelMap.insertMulti(4, 24);

    // XP5 (Endgame)
    levelMap.insertMulti(4, 25);
    levelMap.insertMulti(4, 26);
    levelMap.insertMulti(4, 27);
    levelMap.insertMulti(4, 28);

    /* TeamDeathMatch0 */
    levelMap.insertMulti(5, 0);
    levelMap.insertMulti(5, 1);
    levelMap.insertMulti(5, 2);
    levelMap.insertMulti(5, 3);
    levelMap.insertMulti(5, 4);
    levelMap.insertMulti(5, 5);
    levelMap.insertMulti(5, 6);
    levelMap.insertMulti(5, 7);
    levelMap.insertMulti(5, 8);

    // XP1 (Back to Karkand)
    levelMap.insertMulti(5, 9);
    levelMap.insertMulti(5, 10);
    levelMap.insertMulti(5, 11);
    levelMap.insertMulti(5, 12);

    // XP2 (Close Quarters)

    // XP3 (Armored Kill)
    levelMap.insertMulti(5, 17);
    levelMap.insertMulti(5, 18);
    levelMap.insertMulti(5, 19);
    levelMap.insertMulti(5, 20);

    // XP4 (Aftermath)
    levelMap.insertMulti(5, 21);
    levelMap.insertMulti(5, 22);
    levelMap.insertMulti(5, 23);
    levelMap.insertMulti(5, 24);

    // XP5 (Endgame)
    levelMap.insertMulti(5, 25);
    levelMap.insertMulti(5, 26);
    levelMap.insertMulti(5, 27);
    levelMap.insertMulti(5, 28);

    /* ConquestAssaultLarge0 */

    // XP1 (Back to Karkand)
    levelMap.insertMulti(6, 9);
    levelMap.insertMulti(6, 11);
    levelMap.insertMulti(6, 12);

    /* ConquestAssaultSmall0 */

    // XP1 (Back to Karkand)
    levelMap.insertMulti(7, 9);
    levelMap.insertMulti(7, 10);
    levelMap.insertMulti(7, 11);
    levelMap.insertMulti(7, 13);

    /* ConquestAssaultSmall1 */

    // XP1 (Back to Karkand)
    levelMap.insertMulti(8, 9);
    levelMap.insertMulti(8, 11);
    levelMap.insertMulti(8, 12);

    /* Domination0 */

    // XP1 (Close Quarters)
    levelMap.insertMulti(9, 13);
    levelMap.insertMulti(9, 14);
    levelMap.insertMulti(9, 15);
    levelMap.insertMulti(9, 16);

    /* GunMaster0 */

    // XP1 (Close Quarters)
    levelMap.insertMulti(10, 13);
    levelMap.insertMulti(10, 14);
    levelMap.insertMulti(10, 15);
    levelMap.insertMulti(10, 16);

    // XP4 (Aftermath)
    levelMap.insertMulti(10, 21);
    levelMap.insertMulti(10, 22);
    levelMap.insertMulti(10, 23);
    levelMap.insertMulti(10, 24);

    /* TeamDeathMatchC0 */

    // XP1 (Close Quarters)
    levelMap.insertMulti(11, 13);
    levelMap.insertMulti(11, 14);
    levelMap.insertMulti(11, 15);
    levelMap.insertMulti(11, 16);

    /* TankSuperiority0 */

    // XP3 (Armored Kill)
    levelMap.insertMulti(12, 17);
    levelMap.insertMulti(12, 18);
    levelMap.insertMulti(12, 19);
    levelMap.insertMulti(12, 20);

    /* Scavenger0 */

    // XP4 (Aftermath)
    levelMap.insertMulti(13, 21);
    levelMap.insertMulti(13, 22);
    levelMap.insertMulti(13, 23);
    levelMap.insertMulti(13, 24);

    /* CaptureTheFlag0 */

    // XP5 (Endgame)
    levelMap.insertMulti(14, 25);
    levelMap.insertMulti(14, 26);
    levelMap.insertMulti(14, 27);
    levelMap.insertMulti(14, 28);

    /* AirSuperiority0 */

    // XP5 (Endgame)
    levelMap.insertMulti(15, 25);
    levelMap.insertMulti(15, 26);
    levelMap.insertMulti(15, 27);
    levelMap.insertMulti(15, 28);
}

BF3LevelDictionary::~BF3LevelDictionary()
{

}
