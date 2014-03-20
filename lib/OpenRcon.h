/*
 * Copyright (C) 2011 The OpenRcon Project.
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

#ifndef OPENRCON_H
#define OPENRCON_H

#include "OpenRcon_global.h"

#include <QObject>
#include <QDebug>

class OPENRCON_EXPORT OpenRcon : QObject
{
    Q_OBJECT

public:
    explicit OpenRcon(QObject *parent = 0);
    ~OpenRcon();

    virtual void addWidget(QWidget *widget) = 0;
    virtual void removeWidget(QWidget *widget) = 0;

};

#endif // OPENRCON_H
