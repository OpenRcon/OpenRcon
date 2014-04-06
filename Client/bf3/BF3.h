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

#ifndef BF3_H
#define BF3_H

#include <QObject>
#include <QCompleter>
#include <QMenu>

#include "BFBaseGame.h"
#include "BF3Connection.h"

class BF3 : public BFBaseGame {
    Q_OBJECT

public:
    explicit BF3(const QString &host, const int &port, const QString &password);
    ~BF3();

    virtual Connection *getConnection() { return con; }

protected:
    BF3Connection *con;

};

#endif // BF3_H
