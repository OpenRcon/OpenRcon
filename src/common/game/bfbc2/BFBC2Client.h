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

#ifndef BFBC2CLIENT_H
#define BFBC2CLIENT_H

#include "FrostbiteClient.h"
#include "BFBC2CommandHandler.h"

class BFBC2Client : public FrostbiteClient
{
    Q_OBJECT

public:
    BFBC2Client(ServerEntry *serverEntry, QObject *parent = nullptr);
    ~BFBC2Client() final;

    BFBC2CommandHandler *getCommandHandler() final {
        return dynamic_cast<BFBC2CommandHandler*>(commandHandler);
    }
};

#endif // BFBC2CLIENT_H
