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

BF4LevelDictionary::BF4LevelDictionary(QObject *parent) : LevelDictionary(":/bf4/levels/", parent)
{
    /* List of all levels */
    levelList.append(LevelEntry("MP_Abandoned", "Zavod 311", 0, 1, imagePath + "zavod_311.png"));                                 // 0
    levelList.append(LevelEntry("MP_Damage", "Lancang Dam", 0, 2, imagePath + "lancang_dam.png"));                                // 1
    levelList.append(LevelEntry("MP_Flooded", "Flood Zone", 1, 2, imagePath + "flood_zone.png"));                                 // 2
    levelList.append(LevelEntry("MP_Journey", "Golmud Railway", 0, 2, imagePath + "golmud_railway.png"));                         // 3
    levelList.append(LevelEntry("MP_Naval", "Paracel Storm", 1, 2, imagePath + "paracel_storm.png"));                             // 4
    levelList.append(LevelEntry("MP_Prison", "Operation Locker", 1, 0, imagePath + "operation_locker.png"));                      // 5
    levelList.append(LevelEntry("MP_Resort", "Hainan Resort", 1, 2, imagePath + "hainan_resort.png"));                            // 6
    levelList.append(LevelEntry("MP_Siege", "Siege of Shanghai", 1, 2, imagePath + "seige_of_shanghai.png"));                     // 7
    levelList.append(LevelEntry("MP_TheDish", "Rogue Transmission", 0, 2, imagePath + "rogue_transmission.png"));                 // 8
    levelList.append(LevelEntry("MP_Tremors", "Dawnbreaker", 1, 2, imagePath + "dawnbreaker.png"));                               // 9

    // XP1 (China Rising)
    levelList.append(LevelEntry("XP1_001", "Silk Road", 1, 2, imagePath + "silk_road.png"));                                      // 10
    levelList.append(LevelEntry("XP1_002", "Altai Range", 1, 2, imagePath + "altai_range.png"));                                  // 11
    levelList.append(LevelEntry("XP1_003", "Guilin Peaks", 1, 2, imagePath + "guilin_peaks.png"));                                // 12
    levelList.append(LevelEntry("XP1_004", "Dragon Pass", 1, 2, imagePath + "dragon_pass.png"));                                  // 13

    // XP2 (Second Assault)
    levelList.append(LevelEntry("XP0_Caspian", "Caspian Border 2014", 1, 0, imagePath + "caspian_border_2014.png"));              // 14
    levelList.append(LevelEntry("XP0_Firestorm", "Firestorm 2014", 1, 0, imagePath + "firestorm_2014.png"));                      // 15
    levelList.append(LevelEntry("XP0_Metro", "Operation Metro 2014", 1, 0, imagePath + "operation_metro_2014.png"));              // 16
    levelList.append(LevelEntry("XP0_Oman", "Gulf of Oman 2014", 1, 0, imagePath + "gulf_of_oman_2014.png"));                     // 17

    // XP3 (Naval Strike)
    levelList.append(LevelEntry("XP2_001", "Lost Islands", 1, 3, imagePath + "lost_islands.png"));                                // 18
    levelList.append(LevelEntry("XP2_002", "Nansha Strike", 1, 3, imagePath + "nansha_strike.png"));                              // 19
    levelList.append(LevelEntry("XP2_003", "Wave Breaker", 1, 3, imagePath + "wave_breaker.png"));                                // 20
    levelList.append(LevelEntry("XP2_004", "Operation Mortar", 1, 3, imagePath + "operation_mortar.png"));                        // 21

    // XP4 (Dragon's Teeth)

    // XP5 (Final Stand)

    /* List of all gamemodes */
    gameModeList.append(BF4GameModeEntry("ConquestLarge0", "Conquest Large", 64, 2, 4));               // 0
    gameModeList.append(BF4GameModeEntry("ConquestSmall0", "Conquest Small", 32, 2, 4));               // 1
    gameModeList.append(BF4GameModeEntry("Domination0", "Domination", 20, 0, 4));                      // 2
    gameModeList.append(BF4GameModeEntry("Elimination0", "Defuse", 10, 0, 4));                         // 3
    gameModeList.append(BF4GameModeEntry("Obliteration", "Obliteration", 32, 2, 4));                   // 4
    gameModeList.append(BF4GameModeEntry("RushLarge0", "Rush", 32, 2, 4));                             // 5
    gameModeList.append(BF4GameModeEntry("SquadDeathMatch0", "Squad Deathmatch", 20, 0, 4));           // 6
    gameModeList.append(BF4GameModeEntry("TeamDeathMatch0", "Team Deathmatch", 20, 0, 4));             // 7
    gameModeList.append(BF4GameModeEntry("AirSuperiority0", "Air Superiority", 24, 0, 4));             // 8
    gameModeList.append(BF4GameModeEntry("CaptureTheFlag0", "Capture the flag", 32, 0, 4));            // 9
    gameModeList.append(BF4GameModeEntry("CarrierAssaultLarge0", "Carrier Assault Large", 64, 0, 4));  // 10
    gameModeList.append(BF4GameModeEntry("CarrierAssaultSmall0", "Carrier Assault Small", 64, 0, 4));  // 11 Check this when docs is avaliable.

    /* List of all teams */
    teamList.append("RU");
    teamList.append("US");
    teamList.append("CN");
    teamList.append("CH");

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
    levelMap.insertMulti(0, 9);

    // XP1 (China Rising)
    levelMap.insertMulti(0, 10);
    levelMap.insertMulti(0, 11);
    levelMap.insertMulti(0, 12);
    levelMap.insertMulti(0, 13);

    // XP2 (Second Assault)
    levelMap.insertMulti(0, 14);
    levelMap.insertMulti(0, 15);
    levelMap.insertMulti(0, 16);
    levelMap.insertMulti(0, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(0, 18);
    levelMap.insertMulti(0, 19);
    levelMap.insertMulti(0, 20);
    levelMap.insertMulti(0, 21);

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
    levelMap.insertMulti(1, 9);

    // XP1 (China Rising)
    levelMap.insertMulti(1, 10);
    levelMap.insertMulti(1, 11);
    levelMap.insertMulti(1, 12);
    levelMap.insertMulti(1, 13);

    // XP2 (Second Assault)
    levelMap.insertMulti(1, 14);
    levelMap.insertMulti(1, 15);
    levelMap.insertMulti(1, 16);
    levelMap.insertMulti(1, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(1, 18);
    levelMap.insertMulti(1, 19);
    levelMap.insertMulti(1, 20);
    levelMap.insertMulti(1, 21);

    /* Domination0 */
    levelMap.insertMulti(2, 2);
    levelMap.insertMulti(2, 1);
    levelMap.insertMulti(2, 2);
    levelMap.insertMulti(2, 3);
    levelMap.insertMulti(2, 4);
    levelMap.insertMulti(2, 5);
    levelMap.insertMulti(2, 6);
    levelMap.insertMulti(2, 7);
    levelMap.insertMulti(2, 8);
    levelMap.insertMulti(2, 9);

    // XP1 (China Rising)
    levelMap.insertMulti(2, 10);
    levelMap.insertMulti(2, 11);
    levelMap.insertMulti(2, 12);
    levelMap.insertMulti(2, 13);

    // XP2 (Second Assault)
    levelMap.insertMulti(2, 14);
    levelMap.insertMulti(2, 15);
    levelMap.insertMulti(2, 16);
    levelMap.insertMulti(2, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(2, 18);
    levelMap.insertMulti(2, 19);
    levelMap.insertMulti(2, 20);
    levelMap.insertMulti(2, 21);

    /* Elemination0 */
    levelMap.insertMulti(3, 0);
    levelMap.insertMulti(3, 1);
    levelMap.insertMulti(3, 2);
    levelMap.insertMulti(3, 3);
    levelMap.insertMulti(3, 4);
    levelMap.insertMulti(3, 5);
    levelMap.insertMulti(3, 6);
    levelMap.insertMulti(3, 7);
    levelMap.insertMulti(3, 8);
    levelMap.insertMulti(3, 9);

    // XP1 (China Rising)
    levelMap.insertMulti(3, 10);
    levelMap.insertMulti(3, 11);
    levelMap.insertMulti(3, 12);
    levelMap.insertMulti(3, 13);

    // XP2 (Second Assault)
    levelMap.insertMulti(3, 14);
    levelMap.insertMulti(3, 15);
    levelMap.insertMulti(3, 16);
    levelMap.insertMulti(3, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(3, 18);
    levelMap.insertMulti(3, 19);
    levelMap.insertMulti(3, 20);
    levelMap.insertMulti(3, 21);

    /* Obliteration */
    levelMap.insertMulti(4, 0);
    levelMap.insertMulti(4, 1);
    levelMap.insertMulti(4, 2);
    levelMap.insertMulti(4, 3);
    levelMap.insertMulti(4, 4);
    levelMap.insertMulti(4, 5);
    levelMap.insertMulti(4, 6);
    levelMap.insertMulti(4, 7);
    levelMap.insertMulti(4, 8);
    levelMap.insertMulti(4, 9);

    // XP1 (China Rising)
    levelMap.insertMulti(4, 10);
    levelMap.insertMulti(4, 11);
    levelMap.insertMulti(4, 12);
    levelMap.insertMulti(4, 13);

    // XP2 (Second Assault)
    levelMap.insertMulti(4, 14);
    levelMap.insertMulti(4, 15);
    levelMap.insertMulti(4, 16);
    levelMap.insertMulti(4, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(4, 18);
    levelMap.insertMulti(4, 19);
    levelMap.insertMulti(4, 20);
    levelMap.insertMulti(4, 21);

    /* RushLarge0 */
    levelMap.insertMulti(5, 0);
    levelMap.insertMulti(5, 1);
    levelMap.insertMulti(5, 2);
    levelMap.insertMulti(5, 3);
    levelMap.insertMulti(5, 4);
    levelMap.insertMulti(5, 5);
    levelMap.insertMulti(5, 6);
    levelMap.insertMulti(5, 7);
    levelMap.insertMulti(5, 8);
    levelMap.insertMulti(5, 9);

    // XP1 (China Rising)
    levelMap.insertMulti(5, 10);
    levelMap.insertMulti(5, 11);
    levelMap.insertMulti(5, 12);
    levelMap.insertMulti(5, 13);

    // XP2 (Second Assault)
    levelMap.insertMulti(5, 14);
    levelMap.insertMulti(5, 15);
    levelMap.insertMulti(5, 16);
    levelMap.insertMulti(5, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(5, 18);
    levelMap.insertMulti(5, 19);
    levelMap.insertMulti(5, 20);
    levelMap.insertMulti(5, 21);

    /* TeamDeathMatch0 */
    levelMap.insertMulti(6, 0);
    levelMap.insertMulti(6, 1);
    levelMap.insertMulti(6, 2);
    levelMap.insertMulti(6, 3);
    levelMap.insertMulti(6, 4);
    levelMap.insertMulti(6, 5);
    levelMap.insertMulti(6, 6);
    levelMap.insertMulti(6, 7);
    levelMap.insertMulti(6, 8);
    levelMap.insertMulti(6, 9);

    // XP1 (China Rising)
    levelMap.insertMulti(6, 10);
    levelMap.insertMulti(6, 11);
    levelMap.insertMulti(6, 12);
    levelMap.insertMulti(6, 13);

    // XP2 (Second Assault)
    levelMap.insertMulti(6, 14);
    levelMap.insertMulti(6, 15);
    levelMap.insertMulti(6, 16);
    levelMap.insertMulti(6, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(6, 18);
    levelMap.insertMulti(6, 19);
    levelMap.insertMulti(6, 20);
    levelMap.insertMulti(6, 21);

    /* SquadDeathMatch0 */
    levelMap.insertMulti(7, 0);
    levelMap.insertMulti(7, 1);
    levelMap.insertMulti(7, 2);
    levelMap.insertMulti(7, 3);
    levelMap.insertMulti(7, 4);
    levelMap.insertMulti(7, 5);
    levelMap.insertMulti(7, 6);
    levelMap.insertMulti(7, 7);
    levelMap.insertMulti(7, 8);
    levelMap.insertMulti(7, 9);

    // XP1 (China Rising)
    levelMap.insertMulti(7, 10);
    levelMap.insertMulti(7, 11);
    levelMap.insertMulti(7, 12);
    levelMap.insertMulti(7, 13);

    // XP2 (Second Assault)
    levelMap.insertMulti(7, 14);
    levelMap.insertMulti(7, 15);
    levelMap.insertMulti(7, 16);
    levelMap.insertMulti(7, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(7, 18);
    levelMap.insertMulti(7, 19);
    levelMap.insertMulti(7, 20);
    levelMap.insertMulti(7, 21);

    /* AirSuperiority0 */

    // XP1 (China Rising)
    levelMap.insertMulti(8, 10);
    levelMap.insertMulti(8, 11);
    levelMap.insertMulti(8, 12);
    levelMap.insertMulti(8, 13);

    /* CaptureTheFlag0 */

    // XP2 (Second Assault)
    levelMap.insertMulti(9, 14);
    levelMap.insertMulti(9, 15);
    levelMap.insertMulti(9, 16);
    levelMap.insertMulti(9, 17);

    // XP3 (Naval Strike)
    levelMap.insertMulti(9, 18);
    levelMap.insertMulti(9, 19);
    levelMap.insertMulti(9, 20);
    levelMap.insertMulti(9, 21);

    /* Carrier Assault Large */

    // XP3 (Naval Strike)
    levelMap.insertMulti(10, 18);
    levelMap.insertMulti(10, 19);
    levelMap.insertMulti(10, 20);
    levelMap.insertMulti(10, 21);

    /* Carrier Assault Small */

    // XP3 (Naval Strike)
    levelMap.insertMulti(11, 18);
    levelMap.insertMulti(11, 19);
    levelMap.insertMulti(11, 20);
    levelMap.insertMulti(11, 21);
}

BF4LevelDictionary::~BF4LevelDictionary()
{

}
