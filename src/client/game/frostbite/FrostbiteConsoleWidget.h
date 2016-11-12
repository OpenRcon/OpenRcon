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

#ifndef FROSTBITECONSOLEWIDGET_H
#define FROSTBITECONSOLEWIDGET_H

#include "FrostbiteWidget.h"

class QStringList;
class QString;

namespace Ui {
    class FrostbiteConsoleWidget;
}

enum class ConsoleTypeEnum {
    Send,
    Receive,
    PunkbusterSend,
    PunkBusterReceive
};

class FrostbiteConsoleWidget : public FrostbiteWidget
{
    Q_OBJECT

public:
    FrostbiteConsoleWidget(FrostbiteClient *client, QWidget *parent = nullptr);
    FrostbiteConsoleWidget(FrostbiteClient *client, const QStringList &commandList, QWidget *parent = nullptr);
    ~FrostbiteConsoleWidget() final;

private:
    Ui::FrostbiteConsoleWidget *ui;

    QStringList commandHistory;
    bool commandHistoryFirst;
    int commandHistoryIndex;

    void clear();
    void logConsole(ConsoleTypeEnum consoleType, const QString &message);

private slots:
    /* Connection */
    void onDisconnected();
    void onDataSent(const QString &request);
    void onDataReceived(const QString &response);

    /* Client */
    void onAuthenticated();

    /* Events */
    void onPunkBusterMessageEvent(const QString &message);

    /* User Interface */
    void lineEdit_co_co_textChanged(const QString &text);
    void pushButton_co_co_clicked();
    void lineEdit_co_pb_textChanged(const QString &text);
    void pushButton_co_pb_clicked();

};

#endif // FROSTBITECONSOLEWIDGET_H
