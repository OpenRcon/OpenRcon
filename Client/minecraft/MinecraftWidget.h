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

#ifndef MINECRAFTWIDGET_H
#define MINECRAFTWIDGET_H

#include <QTime>

#include "ui_Minecraft.h"
#include "Minecraft.h"

class MinecraftWidget : public Minecraft
{
    Q_OBJECT

public:
    explicit MinecraftWidget(ServerEntry *serverEntry);
    ~MinecraftWidget();

    void logMessage(const int &type, const QString &message);

private slots:
    void onDataSentEvent(const QString &command);
    void onDataReceivedEvent(const QString &response);

    void onAuthenticated(const bool &auth);

    void on_pushButton_co_send_clicked();

private:
    Ui::Minecraft *ui;

};

#endif // MINECRAFTWIDGET_H
