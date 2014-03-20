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

#ifndef ORBFBC2_H
#define ORBFBC2_H

#include "ORBFBC2_global.h"

#include <QTcpSocket>

#include "ORBFBC2Connection.h"

class OR_BFBC2_EXPORT ORBFBC2 : public QObject
{
    Q_OBJECT

public:
    explicit ORBFBC2(QTcpSocket *tcpSocket, QObject *parent = 0);
    ~ORBFBC2();

private:
    QTcpSocket *tcpSocket;

};

#endif // ORBFBC2_H
