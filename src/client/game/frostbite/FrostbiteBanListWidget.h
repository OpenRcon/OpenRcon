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

#ifndef FROSTBITEBANLISTWIDGET_H
#define FROSTBITEBANLISTWIDGET_H

#include "FrostbiteWidget.h"

class QString;
class QTimer;
class QMenu;
class QAction;
template<class T>
class QList;
class QPoint;

class BanListEntry;
enum class BanIdTypeEnum;
enum class BanTypeEnum;

namespace Ui {
    class FrostbiteBanListWidget;
}

class FrostbiteBanListWidget : public FrostbiteWidget
{
    Q_OBJECT

public:
    FrostbiteBanListWidget(FrostbiteClient *client, QWidget *parent = nullptr);
    ~FrostbiteBanListWidget() final;

private:
    Ui::FrostbiteBanListWidget *ui;

    void setBanlist(const QList<BanListEntry> &banList);
    void setTemporaryEnabled(bool enabled);
    void addBanListItem(const BanIdTypeEnum &banIdType, const QString &banId, const BanTypeEnum &banType, int seconds, int rounds, const QString &reason);

    /* User Interface */
    QTimer *timer;
    QMenu *menu_bl_banList;
    QAction *action_bl_banList_remove;

private slots:
    /* Client */
    void onAuthenticated();

    /* Commands */
    void onBanListListCommand(const QList<BanListEntry> &banList);

    /* User Interface */
    void validate();
    void update();
    void tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos);
    void action_bl_banList_remove_triggered();
    void pushButton_clear_clicked();
    void radioButton_permanent_clicked();
    void radioButton_temporary_clicked();
    void comboBox_by_currentIndexChanged(int index);
    void pushButton_ban_clicked();

};

#endif // FROSTBITEBANLISTWIDGET_H
