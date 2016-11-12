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

#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "FrostbiteWidget.h"
#include "LevelEntry.h"

class QString;
template<class T>
class QList;

class FrostbitePlayerEntry;

namespace Ui {
    class FrostbiteChatWidget;
}

class FrostbiteChatWidget : public FrostbiteWidget
{
    Q_OBJECT

public:
    FrostbiteChatWidget(FrostbiteClient *client, QWidget *parent = nullptr);
    ~FrostbiteChatWidget() final;

private:
    Ui::FrostbiteChatWidget *ui;
    LevelEntry currentLevel;

    void logChat(const QString &sender, const QString &target, const QString &message);

private slots:
    /* Client */
    void onAuthenticated();

    /* Events */
    void onPlayerChatEvent(const QString &sender, const QString &message, const PlayerSubsetEnum &playerSubset, QString player, int teamId, int squadId);

    /* Commands */
    void onListPlayersCommand(const QList<FrostbitePlayerEntry> &playerList);
    void onCurrentLevelCommand(const QString &levelName);

    /* User Interface */
    void lineEdit_textChanged(const QString &text);
    void comboBox_mode_currentIndexChanged(int index);
    void comboBox_target_currentIndexChanged(int index);
    void spinBox_duration_valueChanged(int index);
    void pushButton_send_clicked();
};

#endif // CHATWIDGET_H
