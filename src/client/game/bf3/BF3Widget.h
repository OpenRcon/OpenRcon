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

#ifndef BF3WIDGET_H
#define BF3WIDGET_H

#include "Frostbite2Widget.h"
#include "BF3Client.h"

class BF3Widget : public Frostbite2Widget
{
    Q_OBJECT

public:
    BF3Widget(BF3Client *client, QWidget *parent = nullptr);
    virtual ~BF3Widget() override;

    BF3Client *getClient() const final {
        return static_cast<BF3Client*>(client);
    }
};

#endif // BF3WIDGET_H
