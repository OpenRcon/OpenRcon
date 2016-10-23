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

#ifndef FROSTBITE2WIDGET_H
#define FROSTBITE2WIDGET_H

#include <QWidget>

#include "FrostbiteWidget.h"

class Frostbite2Widget : public FrostbiteWidget
{
    Q_OBJECT

public:
    Frostbite2Widget(QWidget *parent = nullptr);
    ~Frostbite2Widget();

};

#endif // FROSTBITE2WIDGET_H
