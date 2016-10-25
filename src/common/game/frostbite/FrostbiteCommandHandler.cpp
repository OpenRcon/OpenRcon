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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCryptographicHash>

#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteCommandHandler.h"
#include "FrostbiteUtils.h"
#include "BanListEntry.h"

FrostbiteCommandHandler::FrostbiteCommandHandler(FrostbiteConnection *connection, QObject *parent) : CommandHandler(parent), connection(connection)
{
    qDebug() << "FrostbiteCommandHandler created.";

    if (connection) {
        qDebug() << "FrostbiteCommandHandler, connection exists.";

        connection->setCommandHandler(this);
    }

}

FrostbiteCommandHandler::~FrostbiteCommandHandler()
{

}

bool FrostbiteCommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (FrostbiteCommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responseList = {
        /* Events */

        /* Commands */
        // Misc

        // Admin

        // Banning

        // Maplist

        // Player

        // Punkbuster

        // Reserved Slots

        // Squad

        // Variables

        // PunkBuster

        // Variables
    };

    if (responseList.contains(request)) {
        ResponseFunction response = responseList[request];

        if (response) {
            (this->*response)(packet, lastSentPacket);
        }

        return true;
    }

    return false;
}

/* Send commands */
// Misc

// Admin

// Banning

// Maplist

// Player

// Punkbuster

// Reserved Slots

// Squad

// Variables

/* Parse events */

/* Parse commands */
// Misc

// Admin

// Banning

// Maplist

// Player

// Punkbuster

// Reserved Slots

// Squad

// Variables
