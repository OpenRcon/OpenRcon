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

#ifndef BANLISTWIDGET_H
#define BANLISTWIDGET_H

#include <QWidget>

class QMenu;
class FrostbiteConnection;
class FrostbiteCommandHandler;
enum class BanIdType;
enum class BanType;
struct BanListEntry;

namespace Ui {
    class BanListWidget;
}

class BanListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BanListWidget(FrostbiteConnection *connection, QWidget *parent = nullptr);
    ~BanListWidget();

private:
    Ui::BanListWidget *ui;
    FrostbiteConnection *m_connection;
    FrostbiteCommandHandler *m_commandHandler;

    /* User Interface */
    QMenu *menu_bl_banList;
    QAction *action_bl_banList_remove;

    void addBanListItem(BanIdType idType, const QString &id, BanType banType, int seconds, int rounds, const QString &reason);
    void setBanlist(const QList<BanListEntry> &banList);
    void setTemporaryEnabled(bool enabled);

private slots:
    /* Commands */
    void onBanListListCommand(const QList<BanListEntry> &banList);

    /* User Interface */
    void tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos);
    void action_bl_banList_remove_triggered();
    void pushButton_load_clicked();
    void pushButton_save_clicked();
    void pushButton_clear_clicked();
    void validate();
    void radioButton_permanent_clicked();
    void radioButton_temporary_clicked();
    void comboBox_by_currentIndexChanged(int index);
    void pushButton_ban_clicked();

};

#endif // BANLISTWIDGET_H
