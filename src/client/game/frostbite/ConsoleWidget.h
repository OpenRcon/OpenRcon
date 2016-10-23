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

#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>

class QStringList;
class QString;

class Frostbite2Client;

namespace Ui {
    class ConsoleWidget;
}

class ConsoleWidget : public QWidget
{
    Q_OBJECT

public:
    ConsoleWidget(Frostbite2Client *client, QWidget *parent = nullptr);
    ConsoleWidget(Frostbite2Client *client, const QStringList &commandList, QWidget *parent = nullptr);
    ~ConsoleWidget();

private:
    Ui::ConsoleWidget *ui;
    Frostbite2Client *client;

    QStringList commandHistory;
    bool commandHistoryFirst;
    int commandHistoryIndex;

    void logConsole(int type, const QString &message);

private slots:
    /* Commands */
    void onLoginHashedCommand(bool auth);
    void onPunkBusterMessageEvent(const QString &message);

    /* Events */
    void onDataSent(const QString &request);
    void onDataReceived(const QString &response);

    /* User Interface */
    void pushButton_co_co_clicked();
    void pushButton_co_pb_clicked();

};

#endif // CONSOLEWIDGET_H
