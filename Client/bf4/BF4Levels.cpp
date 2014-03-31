#include "BF4Levels.h"

BF4Levels::BF4Levels(QObject *parent) : QObject(parent)
{
    /* ConquestLarge0 */
    QList<BF4Level *> list1;
    list1.append(new BF4Level("MP_Abandoned", "Zavod 311", "zavod_331.png"));
    list1.append(new BF4Level("MP_Damage", "Lancang Dam", "lancang_dam.png"));
    list1.append(new BF4Level("MP_Flooded", "Flood Zone", "flood_zone.png"));
    list1.append(new BF4Level("MP_Journey", "Golmud Railway", "golmud_railway.png"));
    list1.append(new BF4Level("MP_Naval", "Paracel Storm", "paracel_storm.png"));
    list1.append(new BF4Level("MP_Prison", "Operation Locker", "operation_locker.png"));
    list1.append(new BF4Level("MP_Resort", "Hainan Resort", "hainan_resort.png"));
    list1.append(new BF4Level("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));
    list1.append(new BF4Level("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));
    list1.append(new BF4Level("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));

    // XP1 (China Rising)
    list1.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list1.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list1.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list1.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    // XP2 (Second Assault)
    list1.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list1.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list1.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list1.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* ConquestSmall0 */
    QList<BF4Level *> list2;
    list2.append(new BF4Level("MP_Abandoned", "Zavod 311", "zavod_331.png"));
    list2.append(new BF4Level("MP_Damage", "Lancang Dam", "lancang_dam.png"));
    list2.append(new BF4Level("MP_Flooded", "Flood Zone", "flood_zone.png"));
    list2.append(new BF4Level("MP_Journey", "Golmud Railway", "golmud_railway.png"));
    list2.append(new BF4Level("MP_Naval", "Paracel Storm", "paracel_storm.png"));
    list2.append(new BF4Level("MP_Prison", "Operation Locker", "operation_locker.png"));
    list2.append(new BF4Level("MP_Resort", "Hainan Resort", "hainan_resort.png"));
    list2.append(new BF4Level("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));
    list2.append(new BF4Level("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));
    list2.append(new BF4Level("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));

    // XP1 (China Rising)
    list2.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list2.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list2.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list2.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    // XP2 (Second Assault)
    list2.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list2.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list2.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list2.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* Domination0 */
    QList<BF4Level *> list3;
    list3.append(new BF4Level("MP_Abandoned", "Zavod 311", "zavod_331.png"));
    list3.append(new BF4Level("MP_Damage", "Lancang Dam", "lancang_dam.png"));
    list3.append(new BF4Level("MP_Flooded", "Flood Zone", "flood_zone.png"));
    list3.append(new BF4Level("MP_Journey", "Golmud Railway", "golmud_railway.png"));
    list3.append(new BF4Level("MP_Naval", "Paracel Storm", "paracel_storm.png"));
    list3.append(new BF4Level("MP_Prison", "Operation Locker", "operation_locker.png"));
    list3.append(new BF4Level("MP_Resort", "Hainan Resort", "hainan_resort.png"));
    list3.append(new BF4Level("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));
    list3.append(new BF4Level("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));
    list3.append(new BF4Level("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));

    // XP1 (China Rising)
    list3.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list3.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list3.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list3.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    // XP2 (Second Assault)
    list3.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list3.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list3.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list3.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* Elemination0 */
    QList<BF4Level *> list4;
    list4.append(new BF4Level("MP_Abandoned", "Zavod 311", "zavod_331.png"));
    list4.append(new BF4Level("MP_Damage", "Lancang Dam", "lancang_dam.png"));
    list4.append(new BF4Level("MP_Flooded", "Flood Zone", "flood_zone.png"));
    list4.append(new BF4Level("MP_Journey", "Golmud Railway", "golmud_railway.png"));
    list4.append(new BF4Level("MP_Naval", "Paracel Storm", "paracel_storm.png"));
    list4.append(new BF4Level("MP_Prison", "Operation Locker", "operation_locker.png"));
    list4.append(new BF4Level("MP_Resort", "Hainan Resort", "hainan_resort.png"));
    list4.append(new BF4Level("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));
    list4.append(new BF4Level("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));
    list4.append(new BF4Level("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));

    // XP1 (China Rising)
    list4.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list4.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list4.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list4.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    // XP2 (Second Assault)
    list4.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list4.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list4.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list4.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* Obliteration */
    QList<BF4Level *> list5;
    list5.append(new BF4Level("MP_Abandoned", "Zavod 311", "zavod_331.png"));
    list5.append(new BF4Level("MP_Damage", "Lancang Dam", "lancang_dam.png"));
    list5.append(new BF4Level("MP_Flooded", "Flood Zone", "flood_zone.png"));
    list5.append(new BF4Level("MP_Journey", "Golmud Railway", "golmud_railway.png"));
    list5.append(new BF4Level("MP_Naval", "Paracel Storm", "paracel_storm.png"));
    list5.append(new BF4Level("MP_Prison", "Operation Locker", "operation_locker.png"));
    list5.append(new BF4Level("MP_Resort", "Hainan Resort", "hainan_resort.png"));
    list5.append(new BF4Level("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));
    list5.append(new BF4Level("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));
    list5.append(new BF4Level("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));

    // XP1 (China Rising)
    list5.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list5.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list5.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list5.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    // XP2 (Second Assault)
    list5.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list5.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list5.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list5.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* RushLarge0 */
    QList<BF4Level *> list6;
    list6.append(new BF4Level("MP_Abandoned", "Zavod 311", "zavod_331.png"));
    list6.append(new BF4Level("MP_Damage", "Lancang Dam", "lancang_dam.png"));
    list6.append(new BF4Level("MP_Flooded", "Flood Zone", "flood_zone.png"));
    list6.append(new BF4Level("MP_Journey", "Golmud Railway", "golmud_railway.png"));
    list6.append(new BF4Level("MP_Naval", "Paracel Storm", "paracel_storm.png"));
    list6.append(new BF4Level("MP_Prison", "Operation Locker", "operation_locker.png"));
    list6.append(new BF4Level("MP_Resort", "Hainan Resort", "hainan_resort.png"));
    list6.append(new BF4Level("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));
    list6.append(new BF4Level("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));
    list6.append(new BF4Level("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));

    // XP1 (China Rising)
    list6.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list6.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list6.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list6.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    // XP2 (Second Assault)
    list6.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list6.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list6.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list6.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* TeamDeathMatch0 */
    QList<BF4Level *> list7;
    list7.append(new BF4Level("MP_Abandoned", "Zavod 311", "zavod_331.png"));
    list7.append(new BF4Level("MP_Damage", "Lancang Dam", "lancang_dam.png"));
    list7.append(new BF4Level("MP_Flooded", "Flood Zone", "flood_zone.png"));
    list7.append(new BF4Level("MP_Journey", "Golmud Railway", "golmud_railway.png"));
    list7.append(new BF4Level("MP_Naval", "Paracel Storm", "paracel_storm.png"));
    list7.append(new BF4Level("MP_Prison", "Operation Locker", "operation_locker.png"));
    list7.append(new BF4Level("MP_Resort", "Hainan Resort", "hainan_resort.png"));
    list7.append(new BF4Level("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));
    list7.append(new BF4Level("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));
    list7.append(new BF4Level("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));

    // XP1 (China Rising)
    list7.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list7.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list7.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list7.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    // XP2 (Second Assault)
    list7.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list7.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list7.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list7.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* SquadDeathMatch0 */
    QList<BF4Level *> list8;
    list8.append(new BF4Level("MP_Abandoned", "Zavod 311", "zavod_331.png"));
    list8.append(new BF4Level("MP_Damage", "Lancang Dam", "lancang_dam.png"));
    list8.append(new BF4Level("MP_Flooded", "Flood Zone", "flood_zone.png"));
    list8.append(new BF4Level("MP_Journey", "Golmud Railway", "golmud_railway.png"));
    list8.append(new BF4Level("MP_Naval", "Paracel Storm", "paracel_storm.png"));
    list8.append(new BF4Level("MP_Prison", "Operation Locker", "operation_locker.png"));
    list8.append(new BF4Level("MP_Resort", "Hainan Resort", "hainan_resort.png"));
    list8.append(new BF4Level("MP_Siege", "Siege of Shanghai", "seige_of_shanghai.png"));
    list8.append(new BF4Level("MP_TheDish", "Rogue Transmission", "rogue_transmission.png"));
    list8.append(new BF4Level("MP_Tremors", "Dawnbreaker", "dawnbreaker.png"));

    // XP1 (China Rising)
    list8.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list8.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list8.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list8.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    // XP2 (Second Assault)
    list8.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list8.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list8.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list8.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* AirSuperiority0 */
    QList<BF4Level *> list9;

    // XP1 (China Rising)
    list9.append(new BF4Level("XP1_001", "Silk Road", "silk_road.png"));
    list9.append(new BF4Level("XP1_002", "Altai Range", "altai_range.png"));
    list9.append(new BF4Level("XP1_003", "Guilin Peaks", "guilin_peaks.png"));
    list9.append(new BF4Level("XP1_004", "Dragon Pass", "dragon_pass.png"));

    /* AirSuperiority0 */
    QList<BF4Level *> list10;

    // XP2 (Second Assault)
    list10.append(new BF4Level("XP0_Caspian", "Caspian Border 2014", "caspian_border_2014.png"));
    list10.append(new BF4Level("XP0_Firestorm", "Operation Firestorm 2014", "operation_firestorm_2014.png"));
    list10.append(new BF4Level("XP0_Metro", "Operation Metro 2014", "operation_metro_2014.png"));
    list10.append(new BF4Level("XP0_Oman", "Gulf of Oman 2014", "gulf_of_oman_2014.png"));

    /* Game modes */
    levelMap.insert(new BF4GameMode("ConquestLarge0", "Conquest", 64, 2, 4), list1);
    levelMap.insert(new BF4GameMode("ConquestSmall0", "Conquest", 32, 2, 4), list2);
    levelMap.insert(new BF4GameMode("Domination0", "Domination", 20, 0, 4), list3);
    levelMap.insert(new BF4GameMode("Elimination0", "Defuse", 10, 0, 4), list4);
    levelMap.insert(new BF4GameMode("Obliteration", "Obliteration", 32, 2, 4), list5);
    levelMap.insert(new BF4GameMode("RushLarge0", "Rush", 32, 2, 4), list6);
    levelMap.insert(new BF4GameMode("SquadDeathMatch0", "Squad Deathmatch", 20, 0, 4), list7);
    levelMap.insert(new BF4GameMode("TeamDeathMatch0", "Team Deathmatch", 20, 0, 4), list8);
    levelMap.insert(new BF4GameMode("AirSuperiority0", "Air Superiority", 24, 0, 4), list9);
    levelMap.insert(new BF4GameMode("CaptureTheFlag0", "Capture The Flag", 64, 2, 4), list10); // Check this when docs is avaliable.
}

BF4Levels::~BF4Levels()
{

}

BF4GameMode* BF4Levels::getGameMode(const int &index)
{
    return levelMap.keys().at(index);
}

QList<BF4GameMode *> BF4Levels::getGameModes()
{
    return levelMap.keys();
}

BF4Level* BF4Levels::getLevel(BF4GameMode *gameMode, const int &index)
{
    return levelMap.value(gameMode).at(index);
}

BF4Level* BF4Levels::getLevel(const int &gameModeIndex, const int &index)
{
    return getLevel(getGameMode(gameModeIndex), index);
}

QList<BF4Level *> BF4Levels::getLevels(BF4GameMode *gameMode)
{
    return levelMap.value(gameMode);
}

QList<BF4Level *> BF4Levels::getLevels(const int &index)
{
    return getLevels(getGameMode(index));
}
