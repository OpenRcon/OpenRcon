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

#ifndef MINECRAFTWIDGET_H
#define MINECRAFTWIDGET_H

#include "GameWidget.h"
#include "MinecraftClient.h"

namespace Ui {
    class MinecraftWidget;
}

class MinecraftWidget : public GameWidget
{
    Q_OBJECT

public:
    MinecraftWidget(ServerEntry *serverEntry, QWidget *parent = nullptr);
    ~MinecraftWidget() final;

    MinecraftClient *getClient() final {
        return dynamic_cast<MinecraftClient*>(client);
    }

    void logMessage(int type, const QString &message);

private:
    Ui::MinecraftWidget *ui;

private slots:
    void onDataSent(const QString &command);
    void onDataReceived(const QString &response);
    void onAuthenticated(bool auth);

    void on_pushButton_co_send_clicked();

};

#endif // MINECRAFTWIDGET_H
