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

#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

class FrostbiteConnection;
class Frostbite2CommandHandler;

namespace Ui {
    class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    ChatWidget(FrostbiteConnection *connection, QWidget *parent = 0);
    ~ChatWidget();

private:
    Ui::ChatWidget *ui;
    FrostbiteConnection *m_connection;
    Frostbite2CommandHandler *m_commandHandler;

    void logChat(const QString &sender, const QString &message, const QString &target);

private slots:
    /* Events */
    void onPlayerChatEvent(const QString &sender, const QString &message, const QString &target);

    /* Commands */
    void onLoginHashedCommand(bool auth);

    /* User Interface */
    void comboBox_mode_currentIndexChanged(int index);
    void spinBox_duration_valueChanged(int index);
    void pushButton_send_clicked();
};

#endif // CHATWIDGET_H
