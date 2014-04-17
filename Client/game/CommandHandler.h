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

#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QObject>

class CommandHandler : public QObject
{
    Q_OBJECT

public:
    explicit CommandHandler(QObject *parent = 0);
    ~CommandHandler();

    void eventOnDataSent(const QString &command);
    void eventOnDataReceived(const QString &response);

protected:
    void commandUnknown();

signals:
    void onDataSent(const QString &command);
    void onDataReceived(const QString &response);

    void onUnknownCommand();

};

#endif // COMMANDHANDLER_H
