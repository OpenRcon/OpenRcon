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

#ifndef BFBC2CONNECTION_H
#define BFBC2CONNECTION_H

#include "FrostbiteConnection.h"

#include "BFBC2CommandHandler.h"

class BFBC2Connection : public FrostbiteConnection
{
    Q_OBJECT

public:
    explicit BFBC2Connection(QObject *parent = 0);
    ~BFBC2Connection();

    BFBC2CommandHandler *commandHandler;

private slots:
    void stateChanged(QAbstractSocket::SocketState state);

};

#endif // BFBC2CONNECTION_H
