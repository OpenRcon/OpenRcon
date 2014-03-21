/*
 * Copyright (C) 2010 The OpenRcon Project.
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

BFBC2Levels::BFBC2Levels(const QString& currentMod)
{
    int modIndex = 0;

    if (currentMod == "BC2") {
        modIndex = 0;
    } else if (currentMod == "VIETNAM") {
        modIndex = 1;
    }

    switch(modIndex) {
        case 0:
            // Battlefield: Bad Company 2
            rushLevel.append(new Level("BC2", "Valparaiso", "levels/mp_002", RESOURCE_IMAGE_LEVELS + "valparaiso.png"));
            rushLevel.append(new Level("BC2", "Isla Inocentes", "levels/mp_004", RESOURCE_IMAGE_LEVELS + "isla_inocentes.png"));
            rushLevel.append(new Level("BC2", "Atacama Desert", "levels/mp_005gr", RESOURCE_IMAGE_LEVELS + "atacama_desert.png"));
            rushLevel.append(new Level("BC2", "Arica Harbor", "levels/mp_006", RESOURCE_IMAGE_LEVELS + "arica_harbor.png"));
            rushLevel.append(new Level("BC2", "White Pass", "levels/mp_007gr", RESOURCE_IMAGE_LEVELS + "white_pass.png"));
            rushLevel.append(new Level("BC2", "Nelson Bay", "levels/mp_008", RESOURCE_IMAGE_LEVELS + "nelson_bay.png"));
            rushLevel.append(new Level("BC2", "Laguna Presa", "levels/mp_009gr", RESOURCE_IMAGE_LEVELS + "laguna_presa.png"));
            rushLevel.append(new Level("BC2", "Port Valdez", "levels/mp_012gr", RESOURCE_IMAGE_LEVELS + "port_valdez.png"));
            rushLevel.append(new Level("BC2", "Oasis", "levels/bc1_oasis_gr", RESOURCE_IMAGE_LEVELS + "oasis.png"));
            rushLevel.append(new Level("BC2", "Harvest Day", "levels/bc1_harvest_day_gr", RESOURCE_IMAGE_LEVELS + "harvest_day.png"));
            rushLevel.append(new Level("BC2", "Cold War", "levels/mp_sp_002gr", RESOURCE_IMAGE_LEVELS + "cold_war.png"));

            // Battlefield: Bad Company 2
            conquestLevel.append(new Level("BC2", "Panama Canal", "levels/mp_001", RESOURCE_IMAGE_LEVELS + "panama_canal.png"));
            conquestLevel.append(new Level("BC2", "Laguna Alta", "levels/mp_003", RESOURCE_IMAGE_LEVELS + "laguna_alta.png"));
            conquestLevel.append(new Level("BC2", "Atacama Desert", "levels/mp_005", RESOURCE_IMAGE_LEVELS + "atacama_desert.png"));
            conquestLevel.append(new Level("BC2", "Arica Harbor", "Levels/mp_006cq", RESOURCE_IMAGE_LEVELS + "arica_harbor.png"));
            conquestLevel.append(new Level("BC2", "White Pass", "levels/mp_007", RESOURCE_IMAGE_LEVELS + "white_pass.png"));
            conquestLevel.append(new Level("BC2", "Nelson Bay", "levels/mp_008cq", RESOURCE_IMAGE_LEVELS + "nelson_bay.png"));
            conquestLevel.append(new Level("BC2", "Laguna Presa", "levels/mp_009cq", RESOURCE_IMAGE_LEVELS + "laguna_presa.png"));
            conquestLevel.append(new Level("BC2", "Port Valdez", "levels/mp_012cq", RESOURCE_IMAGE_LEVELS + "port_valdez.png"));
            conquestLevel.append(new Level("BC2", "Oasis", "levels/bc1_oasis_cq", RESOURCE_IMAGE_LEVELS + "oasis.png"));
            conquestLevel.append(new Level("BC2", "Harvest Day", "levels/bc1_harvest_day_cq", RESOURCE_IMAGE_LEVELS + "harvest_day.png"));
            conquestLevel.append(new Level("BC2", "Heavy Metal", "levels/mp_sp_005cq", RESOURCE_IMAGE_LEVELS + "heavy_metal.png"));

            // Battlefield: Bad Company 2
            sqrushLevel.append(new Level("BC2", "Panama Canal", "levels/mp_001sr", RESOURCE_IMAGE_LEVELS + "panama_canal.png"));
            sqrushLevel.append(new Level("BC2", "Valparaiso", "levels/mp_002sr", RESOURCE_IMAGE_LEVELS + "valparaiso.png"));
            sqrushLevel.append(new Level("BC2", "Laguna Alta", "levels/mp_003sr", RESOURCE_IMAGE_LEVELS + "laguna_alta.png"));
            sqrushLevel.append(new Level("BC2", "Atacama Desert", "levels/mp_005sr", RESOURCE_IMAGE_LEVELS + "atacama_desert.png"));
            sqrushLevel.append(new Level("BC2", "Laguna Presa", "levels/mp_009sr", RESOURCE_IMAGE_LEVELS + "laguna_presa.png"));
            sqrushLevel.append(new Level("BC2", "Port Valdez", "levels/mp_012sr", RESOURCE_IMAGE_LEVELS + "port_valdez.png"));
            sqrushLevel.append(new Level("BC2", "Oasis", "levels/bc1_oasis_sr", RESOURCE_IMAGE_LEVELS + "oasis.png"));
            sqrushLevel.append(new Level("BC2", "Harvest Day", "levels/bc1_harvest_day_sr", RESOURCE_IMAGE_LEVELS + "harvest_day.png"));
            sqrushLevel.append(new Level("BC2", "Cold War", "levels/mp_sp_002sr", RESOURCE_IMAGE_LEVELS + "cold_war.png"));

            // Battlefield: Bad Company 2
            sqdmLevel.append(new Level("BC2", "Panama Canal", "levels/mp_001sdm", RESOURCE_IMAGE_LEVELS + "panama_canal.png"));
            sqdmLevel.append(new Level("BC2", "Isla Inocentes", "levels/mp_004sdm", RESOURCE_IMAGE_LEVELS + "isla_inocentes.png"));
            sqdmLevel.append(new Level("BC2", "Arica Harbor", "levels/mp_006sdm", RESOURCE_IMAGE_LEVELS + "arica_harbor.png"));
            sqdmLevel.append(new Level("BC2", "White Pass", "levels/mp_007sdm", RESOURCE_IMAGE_LEVELS + "white_pass.png"));
            sqdmLevel.append(new Level("BC2", "Nelson Bay", "levels/mp_008sdm", RESOURCE_IMAGE_LEVELS + "nelson_bay.png"));
            sqdmLevel.append(new Level("BC2", "Laguna Presa", "levels/mp_009sdm", RESOURCE_IMAGE_LEVELS + "laguna_presa.png"));
            sqdmLevel.append(new Level("BC2", "Oasis", "levels/bc1_oasis_sdm", RESOURCE_IMAGE_LEVELS + "oasis.png"));
            sqdmLevel.append(new Level("BC2", "Harvest Day", "levels/bc1_harvest_day_sdm", RESOURCE_IMAGE_LEVELS + "harvest_day.png"));
            sqdmLevel.append(new Level("BC2", "Cold War", "levels/mp_sp_002sdm", RESOURCE_IMAGE_LEVELS + "cold_war.png"));
            sqdmLevel.append(new Level("BC2", "Heavy Metal", "levels/mp_sp_005sdm", RESOURCE_IMAGE_LEVELS + "heavy_metal.png"));

            break;

        case 1:

            // Battlefield: Bad Company 2 Vietnam
            rushLevel.append(new Level("VIETNAM", "Vantage Point", "levels/nam_mp_002r", RESOURCE_IMAGE_LEVELS + "vantage_point.png"));
            rushLevel.append(new Level("VIETNAM", "Hill 137", "levels/nam_mp_003r", RESOURCE_IMAGE_LEVELS + "hill_137.png"));
            rushLevel.append(new Level("VIETNAM", "Cao Son Temple", "levels/nam_mp_005r", RESOURCE_IMAGE_LEVELS + "cao_son_temple.png"));
            rushLevel.append(new Level("VIETNAM", "Phu Bai Valley", "levels/nam_mp_006r", RESOURCE_IMAGE_LEVELS + "phu_bai_valley.png"));
            rushLevel.append(new Level("VIETNAM", "Operation Hastings", "levels/nam_mp_007r", RESOURCE_IMAGE_LEVELS + "operation_hastings.png"));

            // Battlefield: Bad Company 2 Vietnam
            conquestLevel.append(new Level("VIETNAM", "Vantage Point", "levels/nam_mp_002cq", RESOURCE_IMAGE_LEVELS + "vantage_point.png"));
            conquestLevel.append(new Level("VIETNAM", "Hill 137", "levels/nam_mp_003cq", RESOURCE_IMAGE_LEVELS + "hill_137.png"));
            conquestLevel.append(new Level("VIETNAM", "Cao Son Temple", "levels/nam_mp_005cq", RESOURCE_IMAGE_LEVELS + "cao_son_temple.png"));
            conquestLevel.append(new Level("VIETNAM", "Phu Bai Valley", "levels/nam_mp_006cq", RESOURCE_IMAGE_LEVELS + "phu_bai_valley.png"));
            conquestLevel.append(new Level("VIETNAM", "Operation Hastings", "levels/nam_mp_007cq", RESOURCE_IMAGE_LEVELS + "operation_hastings.png"));

            // Battlefield: Bad Company 2 Vietnam
            sqrushLevel.append(new Level("VIETNAM", "Vantage Point", "levels/nam_mp_002sr", RESOURCE_IMAGE_LEVELS + "vantage_point.png"));
            sqrushLevel.append(new Level("VIETNAM", "Hill 137", "levels/nam_mp_003sr", RESOURCE_IMAGE_LEVELS + "hill_137.png"));
            sqrushLevel.append(new Level("VIETNAM", "Cao Son Temple", "levels/nam_mp_005sr", RESOURCE_IMAGE_LEVELS + "cao_son_temple.png"));
            sqrushLevel.append(new Level("VIETNAM", "Phu Bai Valley", "levels/nam_mp_006sr", RESOURCE_IMAGE_LEVELS + "phu_bai_valley.png"));
            sqrushLevel.append(new Level("VIETNAM", "Operation Hastings", "levels/nam_mp_007sr", RESOURCE_IMAGE_LEVELS + "operation_hastings.png"));

            // Battlefield: Bad Company 2 Vietnam
            sqdmLevel.append(new Level("VIETNAM", "Vantage Point", "levels/nam_mp_002sdm", RESOURCE_IMAGE_LEVELS + "vantage_point.png"));
            sqdmLevel.append(new Level("VIETNAM", "Hill 137", "levels/nam_mp_003sdm", RESOURCE_IMAGE_LEVELS + "hill_137.png"));
            sqdmLevel.append(new Level("VIETNAM", "Cao Son Temple", "levels/nam_mp_005sdm", RESOURCE_IMAGE_LEVELS + "cao_son_temple.png"));
            sqdmLevel.append(new Level("VIETNAM", "Phu Bai Valley", "levels/nam_mp_006sdm", RESOURCE_IMAGE_LEVELS + "phu_bai_valley.png"));
            sqdmLevel.append(new Level("VIETNAM", "Operation Hastings", "levels/nam_mp_007sdm", RESOURCE_IMAGE_LEVELS + "operation_hastings.png"));

            break;
    }

    levellist << new LevelList(rushLevel);
    levellist << new LevelList(conquestLevel);
    levellist << new LevelList(sqrushLevel);
    levellist << new LevelList(sqdmLevel);
}
