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

#include <QString>
#include <QList>

#include "BF3WeaponDictionary.h"
#include "WeaponEntry.h"

template<>
QList<WeaponEntry> BF3WeaponDictionary::weaponList = {
    /* List of all weapons */
    WeaponEntry("None",       "870MCS",                            "Secondary", "Shotgun"),
    WeaponEntry("Assault",    "AEK-971",                           "Primary",   "AssaultRifle"),
    WeaponEntry("Demolition", "AKS-74u",                           "Primary",   "SMG"),
    WeaponEntry("Assault",    "AN-94 Abakan",                      "Primary",   "AssaultRifle"),
    WeaponEntry("None",       "AS Val",                            "Primary",   "AssaultRifle"),
    WeaponEntry("None",       "DamageArea",                        "Primary",   "Suicide"),
    WeaponEntry("None",       "DAO-12",                            "Secondary", "Shotgun"),
    WeaponEntry("None",       "Death",                             "Primary",   "None"),
    WeaponEntry("Assault",    "Defib",                             "Secondary", "Melee"),
    WeaponEntry("Assault",    "F2000",                             "Primary",   "AssaultRifle"),
    WeaponEntry("Assault",    "FAMAS",                             "Primary",   "AssaultRifle"),
    WeaponEntry("Demolition", "FGM-148",                           "Secondary", "ProjectileExplosive"),
    WeaponEntry("Demolition", "FIM92",                             "Secondary", "ProjectileExplosive"),
    WeaponEntry("None",       "Glock18",                           "Auxiliary", "Handgun"),
    WeaponEntry("None",       "HK53",                              "Primary",   "AssaultRifle"),
    WeaponEntry("None",       "jackhammer",                        "Primary",   "Shotgun"),
    WeaponEntry("Recon",      "JNG90",                             "Primary",   "SniperRifle"),
    WeaponEntry("None",       "Knife_RazorBlade",                  "Secondary", "Melee"),
    WeaponEntry("Recon",      "L96",                               "Primary",   "SniperRifle"),
    WeaponEntry("Support",    "LSAT",                              "Primary",   "LMG"),
    WeaponEntry("Assault",    "M416",                              "Primary",   "AssaultRifle"),
    WeaponEntry("Recon",      "M417",                              "Primary",   "SniperRifle"),
    WeaponEntry("None",       "M1014",                             "Secondary", "Shotgun"),
    WeaponEntry("Demolition", "M15 AT Mine",                       "Secondary", "Explosive"),
    WeaponEntry("Assault",    "M16A4",                             "Primary",   "AssaultRifle"),
    WeaponEntry("None",       "M1911",                             "Auxiliary", "Handgun"),
    WeaponEntry("Support",    "M240",                              "Primary",   "LMG"),
    WeaponEntry("Support",    "M249",                              "Primary",   "LMG"),
    WeaponEntry("Assault",    "M26Mass",                           "Secondary", "Shotgun"),
    WeaponEntry("Support",    "M27IAR",                            "Primary",   "LMG"),
    WeaponEntry("Assault",    "M320",                              "Secondary", "ProjectileExplosive"),
    WeaponEntry("Recon",      "M39",                               "Primary",   "SniperRifle"),
    WeaponEntry("Recon",      "M40A5",                             "Primary",   "SniperRifle"),
    WeaponEntry("Demolition", "M4A1",                              "Primary",   "SMG"),
    WeaponEntry("Support",    "M60",                               "Primary",   "LMG"),
    WeaponEntry("None",       "M67",                               "Auxiliary", "Explosive"),
    WeaponEntry("None",       "M9",                                "Auxiliary", "Handgun"),
    WeaponEntry("None",       "M93R",                              "Auxiliary", "Handgun"),
    WeaponEntry("Assault",    "Medkit",                            "Auxiliary", "Nonlethal"),
    WeaponEntry("None",       "Melee",                             "Secondary", "Melee"),
    WeaponEntry("Support",    "MG36",                              "Primary",   "LMG"),
    WeaponEntry("Recon",      "Mk11",                              "Primary",   "SniperRifle"),
    WeaponEntry("Recon",      "Model98B",                          "Primary",   "SniperRifle"),
    WeaponEntry("None",       "MP7",                               "Primary",   "SMG"),
    WeaponEntry("Support",    "Pecheneg",                          "Primary",   "LMG"),
    WeaponEntry("None",       "PP-19",                             "Primary",   "LMG"),
    WeaponEntry("None",       "PP-2000",                           "Primary",   "SMG"),
    WeaponEntry("Support",    "QBB-95",                            "Primary",   "LMG"),
    WeaponEntry("Recon",      "QBU-88",                            "Primary",   "SniperRifle"),
    WeaponEntry("Demolition", "QBZ-95",                            "Primary",   "AssaultRifle"),
    WeaponEntry("Demolition", "Repair Tool",                       "Secondary", "Melee"),
    WeaponEntry("None",       "RoadKill",                          "Primary",   "None"),
    WeaponEntry("Demolition", "RPG-7",                             "Secondary", "ProjectileExplosive"),
    WeaponEntry("Support",    "RPK-74M",                           "Primary",   "LMG"),
    WeaponEntry("Assault",    "SCAR-L",                            "Primary",   "AssaultRifle"),
    WeaponEntry("Demolition", "SG 553 LB",                         "Primary",   "SMG"),
    WeaponEntry("None",       "Siaga20k",                          "Primary",   "Shotgun"),
    WeaponEntry("Recon",      "SKS",                               "Primary",   "SniperRifle"),
    WeaponEntry("Demolition", "SMAW",                              "Secondary", "ProjectileExplosive"),
    WeaponEntry("None",       "SoldierCollision",                  "Primary",   "Suicide"),
    WeaponEntry("None",       "SPAS-12",                           "Primary",   "Shotgun"),
    WeaponEntry("None",       "Suicide",                           "Primary",   "Suicide"),
    WeaponEntry("Recon",      "SV98",                              "Primary",   "SniperRifle"),
    WeaponEntry("Recon",      "SVD",                               "Primary",   "SniperRifle"),
    WeaponEntry("Assault",    "Steyr AUG",                         "Primary",   "AssaultRifle"),
    WeaponEntry("None",       "Taurus .44",                        "Auxiliary", "Handgun"),
    WeaponEntry("Support",    "Type88",                            "Primary",   "LMG"),
    WeaponEntry("None",       "USAS-12",                           "Secondary", "Shotgun"),
    WeaponEntry("Demolition", "Weapons/A91/A91",                   "Primary",   "SMG"),
    WeaponEntry("Assault",    "Weapons/AK74M/AK74",                "Primary",   "AssaultRifle"),
    WeaponEntry("Demolition", "Weapons/G36C/G36C",                 "Primary",   "SMG"),
    WeaponEntry("Assault",    "Weapons/G3A3/G3A3",                 "Primary",   "AssaultRifle"),
    WeaponEntry("Support",    "Weapons/Gadgets/C4/C4",             "Secondary", "Explosive"),
    WeaponEntry("Support",    "Weapons/Gadgets/Claymore/Claymore", "Secondary", "Explosive"),
    WeaponEntry("Assault",    "Weapons/KH2002/KH2002",             "Primary",   "AssaultRifle"),
    WeaponEntry("None",       "Weapons/Knife/Knife",               "Secondary", "Melee"),
    // outdated WeaponEntry("Assault", "Weapons/M416/M416",        "Primary",   "AssaultRifle"),
    WeaponEntry("None",       "Weapons/MagpulPDR/MagpulPDR",       "Primary",   "SMG"),
    WeaponEntry("None",       "Weapons/MP412Rex/MP412REX",         "Auxiliary", "Handgun"),
    WeaponEntry("None",       "Weapons/MP443/MP443",               "Auxiliary", "Handgun"),
    WeaponEntry("None",       "Weapons/MP443/MP443_GM",            "Primary",   "Handgun"),
    WeaponEntry("None",       "Weapons/P90/P90",                   "Primary",   "SMG"),
    WeaponEntry("None",       "Weapons/P90/P90_GM",                "Primary",   "SMG"),
    WeaponEntry("Demolition", "Weapons/Sa18IGLA/Sa18IGLA",         "Secondary", "ProjectileExplosive"),
    WeaponEntry("Demolition", "Weapons/SCAR-H/SCAR-H",             "Primary",   "SMG"),
    WeaponEntry("None",       "Weapons/UMP45/UMP45",               "Primary",   "SMG"),
    WeaponEntry("Assault",    "Weapons/XP1_L85A2/L85A2",           "Primary",   "AssaultRifle"),
    WeaponEntry("Demolition", "Weapons/XP2_ACR/ACR",               "Primary",   "AssaultRifle"),
    WeaponEntry("Demolition", "Weapons/XP2_L86/L86",               "Primary",   "LMG"),
    WeaponEntry("None",       "Weapons/XP2_MP5K/MP5K",             "Primary",   "SMG"),
    WeaponEntry("Demolition", "Weapons/XP2_MTAR/MTAR",             "Primary",   "AssaultRifle"),
    WeaponEntry("None",       "CrossBow",                          "Primary",   "None")
    // M82, "Primary",   "SniperRifle"
    // PDW-R, "Primary",   "SMG"
    // Saiga-12 , "Secondary", "Shotgun"
    // Glock17, "Auxiliary", "Handgun"
    // AT4 , "Secondary", "ProjectileExplosive"
    // Assault M16A3
    // Demolition EOD BOT
    // Demolition M4
    // Support M224 Mortar
    // Recon TUGS
    // Recon SOFLAM
    // Recon MAV
    //, "None" G17C SUPPRESSED, "Handgun"
    //, "None" M9 SUPPRESSED, "Handgun"
    //, "None" MP443 SUPPRESSED, "Handgun"
    //, "None" G18 SUPRESSED, "Handgun"
    //, "None" .44 Scoped, "Handgun"
};
