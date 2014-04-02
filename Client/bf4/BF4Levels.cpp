#include "BF4Levels.h"

BF4Levels::BF4Levels(QObject *parent) : QObject(parent)
{
    /* List of all levels */
    levelList.append(LevelEntry("MP_Abandoned", "Zavod 311", "zavod_331.png"));                                 // 0
    levelList.append(LevelEntry("MP_Damage", "Lancang Dam", "lancang_dam.png"));                                // 1
    levelList.append(LevelEntry("MP_Flooded", "Flood Zone", "flood_zone.png"));                                 // 2
    levelList.append(LevelEntry("MP_Journey", "Golmud Railway", "golmud_railway.png"));                         // 3
    levelList.append(LevelEntry("MP_Naval", "Paracel Storm", "paracel_storm.png"));                             // 4
    levelList.append(LevelEntry("MP_Prison", "Operation Locker", "operation_locker.png"));                      // 5
    levelList.append(LevelEntry("MP_Resort", "Hainan Resort", "hainan_resort.png"));                            // 6
    levelList.append(LevelEntry("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));                     // 7
    levelList.append(LevelEntry("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));                 // 8
    levelList.append(LevelEntry("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));                               // 9

    // XP1 (China Rising)
    levelList.append(LevelEntry("XP1_001", "Silk Road", "silk_road.png"));                                      // 10
    levelList.append(LevelEntry("XP1_002", "Altai Range", "altai_range.png"));                                  // 11
    levelList.append(LevelEntry("XP1_003", "Guilin Peaks", "guilin_peaks.png"));                                // 12
    levelList.append(LevelEntry("XP1_004", "Dragon Pass", "dragon_pass.png"));                                  // 13

    // XP2 (Second Assault)
    levelList.append(LevelEntry("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));              // 14
    levelList.append(LevelEntry("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));  // 15
    levelList.append(LevelEntry("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));              // 16
    levelList.append(LevelEntry("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));                     // 17

    // XP3 (Naval Strike)
    levelList.append(LevelEntry("XP2_001", "Lost Islands", "lost_islands.png"));                                // 18
    levelList.append(LevelEntry("XP2_002", "Nansha Strike", "nansha_strike.png"));                              // 19
    levelList.append(LevelEntry("XP2_003", "Wave Breaker", "wave_breaker.png"));                                // 20
    levelList.append(LevelEntry("XP2_004", "Operation Mortar", "operation_mortar.png"));                        // 21

    /* List of all gamemodes */
    gameModeList.append(GameModeEntry("ConquestLarge0", "Conquest Large", 64, 2, 4));               // 0
    gameModeList.append(GameModeEntry("ConquestSmall0", "Conquest Small", 32, 2, 4));               // 1
    gameModeList.append(GameModeEntry("Domination0", "Domination", 20, 0, 4));                      // 2
    gameModeList.append(GameModeEntry("Elimination0", "Defuse", 10, 0, 4));                         // 3
    gameModeList.append(GameModeEntry("Obliteration", "Obliteration", 32, 2, 4));                   // 4
    gameModeList.append(GameModeEntry("RushLarge0", "Rush", 32, 2, 4));                             // 5
    gameModeList.append(GameModeEntry("SquadDeathMatch0", "Squad Deathmatch", 20, 0, 4));           // 6
    gameModeList.append(GameModeEntry("TeamDeathMatch0", "Team Deathmatch", 20, 0, 4));             // 7
    gameModeList.append(GameModeEntry("AirSuperiority0", "Air Superiority", 24, 0, 4));             // 8
    gameModeList.append(GameModeEntry("CaptureTheFlag0", "Capture the flag", 32, 0, 4));            // 9
    gameModeList.append(GameModeEntry("CarrierAssaultLarge0", "Carrier Assault Large", 64, 0, 4));  // 10
    gameModeList.append(GameModeEntry("CarrierAssaultSmall0", "Carrier Assault Small", 64, 0, 4));  // 11 Check this when docs is avaliable.

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

BF4Levels::~BF4Levels()
{

}

LevelEntry BF4Levels::getLevel(const int &index)
{
    return levelList.at(index);
}

LevelEntry BF4Levels::getLevel(const QString &name)
{
    foreach (LevelEntry entry, levelList) {
        if (entry.engineName == name || entry.name == name) {
            return entry;
        }
    }

    return LevelEntry();
}

GameModeEntry BF4Levels::getGameMode(const int &index)
{
    return gameModeList.at(index);
}

GameModeEntry BF4Levels::getGameMode(const QString &name)
{
    foreach (GameModeEntry entry, gameModeList) {
        if (entry.engineName == name || entry.name == name) {
            return entry;
        }
    }

    return GameModeEntry("lol", "lol", 2, 2, 2);
}

QList<LevelEntry> BF4Levels::getLevels()
{
    return levelList;
}

QList<LevelEntry> BF4Levels::getLevels(const int &gameModeIndex)
{
    QList<LevelEntry> list;

    foreach (int index, levelMap.values(gameModeIndex)) {
        list.append(levelList.at(index));
    }

    return list;
}

QList<GameModeEntry> BF4Levels::getGameModes()
{
    return gameModeList;
}

QStringList BF4Levels::getLevelNames()
{
    QStringList list;

    foreach (LevelEntry entry, levelList) {
        list.append(entry.name);
    }

    return list;
}

QStringList BF4Levels::getGameModeNames()
{
    QStringList list;

    foreach (GameModeEntry entry, gameModeList) {
        list.append(entry.name);
    }

    return list;
}
