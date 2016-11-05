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

#include <QTimer>
#include <QCompleter>
#include <QMenu>
#include <QAction>

#include "BanListWidget.h"
#include "ui_BanListWidget.h"
#include "BanListEntry.h"
#include "BanType.h"
#include "BanIdType.h"
#include "FrostbiteUtils.h"

BanListWidget::BanListWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::BanListWidget)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer, &QTimer::timeout, this, &BanListWidget::update);

    QStringList banIdTypeList = {
        tr("Name"),
        tr("IP"),
        tr("GUID")
    };

    ui->comboBox_type->addItems(banIdTypeList);

    QStringList reasonList = {
        tr("Hacking/Cheating"),
        tr("Admin abuse"),
        tr("Make room for reserved slots"),
        tr("Being disrespectful"),
        tr("Teamkilling"),
        tr("Spawnkilling"),
        tr("Camping"),
        tr("Team balance"),
        tr("Switching to winning team")
    };

    QCompleter *completer = new QCompleter(reasonList, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    ui->lineEdit_reason->setCompleter(completer);

    // Create actions and menus.
    menu_bl_banList = new QMenu(ui->tableWidget_bl_banList);
    action_bl_banList_remove = new QAction(tr("Remove"), menu_bl_banList);

    menu_bl_banList->addAction(action_bl_banList_remove);

    /* Events */
    // TODO: Connect event here so that list is update when runnig next round.

    /* Commands */
    // BanList
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onBanListListCommand,                         this, &BanListWidget::onBanListListCommand);

    /* User Interface */
    connect(ui->tableWidget_bl_banList,       &QTableWidget::customContextMenuRequested,                              this, &BanListWidget::tableWidget_bl_banList_customContextMenuRequested);
    connect(action_bl_banList_remove,         &QAction::triggered,                                                    this, &BanListWidget::action_bl_banList_remove_triggered);
    connect(ui->pushButton_load,              &QPushButton::clicked,                                                  this, &BanListWidget::pushButton_load_clicked);
    connect(ui->pushButton_save,              &QPushButton::clicked,                                                  this, &BanListWidget::pushButton_save_clicked);
    connect(ui->pushButton_clear,             &QPushButton::clicked,                                                  this, &BanListWidget::pushButton_clear_clicked);
    connect(ui->lineEdit_value,               &QLineEdit::textChanged,                                                this, &BanListWidget::validate);
    connect(ui->lineEdit_reason,              &QLineEdit::textChanged,                                                this, &BanListWidget::validate);
    connect(ui->radioButton_permanent,        &QRadioButton::clicked,                                                 this, &BanListWidget::radioButton_permanent_clicked);
    connect(ui->radioButton_temporary,        &QRadioButton::clicked,                                                 this, &BanListWidget::radioButton_temporary_clicked);
    connect(ui->comboBox_by,                  static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &BanListWidget::comboBox_by_currentIndexChanged);
    connect(ui->pushButton_ban,               &QPushButton::clicked,                                                  this, &BanListWidget::pushButton_ban_clicked);
}

BanListWidget::~BanListWidget()
{
    delete ui;
}

/* Commands */
void BanListWidget::onBanListListCommand(const QList<BanListEntry> &banList)
{
    ui->pushButton_clear->setEnabled(!banList.isEmpty());

    setBanlist(banList);
}

/* User Interface */
void BanListWidget::validate()
{
    bool enabled = !ui->lineEdit_value->text().isEmpty();

    ui->radioButton_permanent->setEnabled(enabled);
    ui->radioButton_temporary->setEnabled(enabled);
    ui->pushButton_ban->setEnabled(enabled);
}

void BanListWidget::update()
{
    // Loop thru all rows and update current duration.
    for (int row = 0; row < ui->tableWidget_bl_banList->rowCount(); row++) {
        QTableWidgetItem *tableWidgetItem = ui->tableWidget_bl_banList->item(row, 2);
        BanTypeEnum banType = tableWidgetItem->data(Qt::UserRole).value<BanTypeEnum>();

        if (banType == BanTypeEnum::Seconds) {
            int *seconds = tableWidgetItem->data(Qt::UserRole + 1).value<int*>();

            if (*seconds > 0) {
                tableWidgetItem->setText(tr("%1 Seconds").arg((*seconds)--));
            } else {
                ui->tableWidget_bl_banList->removeRow(row);
            }
        }
    }
}

void BanListWidget::tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableWidget_bl_banList->itemAt(pos)) {
        menu_bl_banList->exec(QCursor::pos());
    }
}

void BanListWidget::action_bl_banList_remove_triggered()
{
    int row = ui->tableWidget_bl_banList->currentRow();
    BanIdTypeEnum banIdType = ui->tableWidget_bl_banList->itemAt(row, 0)->data(Qt::UserRole).value<BanIdTypeEnum>();
    QString player = ui->tableWidget_bl_banList->item(row, 1)->text();

    if (!player.isEmpty()) {
        getClient()->getCommandHandler()->sendBanListRemoveCommand(banIdType, player);

        ui->tableWidget_bl_banList->removeRow(row);
    }
}

void BanListWidget::setBanlist(const QList<BanListEntry> &banList)
{
    ui->tableWidget_bl_banList->clearContents();
    ui->tableWidget_bl_banList->setRowCount(0);

    for (BanListEntry banListEntry : banList) {
        addBanListItem(banListEntry.getIdType(), banListEntry.getId(), banListEntry.getType(), banListEntry.getSeconds(), banListEntry.getRounds(), banListEntry.getReason());
    }
}

void BanListWidget::setTemporaryEnabled(bool enabled)
{
    ui->comboBox_by->setEnabled(enabled);
    ui->spinBox_timeout->setEnabled(enabled);
    ui->comboBox_timeUnit->setEnabled(enabled);
}

void BanListWidget::addBanListItem(const BanIdTypeEnum &banIdType, const QString &banId, const BanTypeEnum &banType, int seconds, int rounds, const QString &reason)
{
    int row = ui->tableWidget_bl_banList->rowCount();
    ui->tableWidget_bl_banList->insertRow(row);

    QTableWidgetItem *banIdTypeItem = new QTableWidgetItem();
    banIdTypeItem->setData(Qt::UserRole, QVariant::fromValue(banIdType));
    banIdTypeItem->setText(BanIdType::toString(banIdType));

    ui->tableWidget_bl_banList->setItem(row, 0, banIdTypeItem);
    ui->tableWidget_bl_banList->setItem(row, 1, new QTableWidgetItem(banId));

    QString remaining;

    switch (banType) {
    case BanTypeEnum::Perm:
        remaining = tr("Permanent");
        break;

    case BanTypeEnum::Rounds:
        remaining = rounds > 1 ? tr("%1 Rounds").arg(QString::number(rounds)) : tr("%1 Round").arg(QString::number(rounds));
        break;

    case BanTypeEnum::Seconds:
        remaining = seconds > 1 ? tr("%1 Seconds").arg(QString::number(seconds)) : tr("%1 Second").arg(QString::number(seconds));
        break;
    }

    QTableWidgetItem *banTypeItem = new QTableWidgetItem();
    banTypeItem->setData(Qt::UserRole, QVariant::fromValue(banType));

    if (banType == BanTypeEnum::Seconds) {
        int *secondsPointer = new int[1];
        *secondsPointer = seconds;
        banTypeItem->setData(Qt::UserRole + 1, QVariant::fromValue(secondsPointer));
    }

    banTypeItem->setText(remaining);

    ui->tableWidget_bl_banList->setItem(row, 2, banTypeItem);
    ui->tableWidget_bl_banList->setItem(row, 3, new QTableWidgetItem(reason));
}

void BanListWidget::pushButton_load_clicked()
{
    getClient()->getCommandHandler()->sendBanListLoadCommand();
}

void BanListWidget::pushButton_save_clicked()
{
    getClient()->getCommandHandler()->sendBanListSaveCommand();
}

void BanListWidget::pushButton_clear_clicked()
{
    ui->tableWidget_bl_banList->setRowCount(0);
    ui->pushButton_clear->setEnabled(ui->tableWidget_bl_banList->rowCount() < 0);
    getClient()->getCommandHandler()->sendBanListClearCommand();
}

void BanListWidget::radioButton_permanent_clicked()
{
    setTemporaryEnabled(false);
}

void BanListWidget::radioButton_temporary_clicked()
{
    setTemporaryEnabled(true);
}

void BanListWidget::comboBox_by_currentIndexChanged(int index)
{
    ui->comboBox_timeUnit->setEnabled(index == 0);
}

void BanListWidget::pushButton_ban_clicked()
{
    BanIdTypeEnum banIdType = BanIdType::fromString(ui->comboBox_type->currentText());
    QString value = ui->lineEdit_value->text();
    QString reason = ui->lineEdit_reason->text();

    if (ui->radioButton_permanent->isChecked()) {
        getClient()->getCommandHandler()->sendBanListAddCommand(banIdType, value, BanTypeEnum::Perm, reason);
    } else {
        BanTypeEnum banType = ui->comboBox_by->currentIndex() > 0 ? BanTypeEnum::Rounds : BanTypeEnum::Seconds;
        int timeout = ui->spinBox_timeout->value();

        if (ui->comboBox_timeUnit->isEnabled()) {
            int timeoutValue = timeout;

            switch (ui->comboBox_timeUnit->currentIndex()) {
            case 0:
                timeout = timeoutValue;
                break;

            case 1:
                timeout = timeoutValue * 60;
                break;

            case 2:
                timeout = timeoutValue * 60 * 60;
                break;

            case 3:
                timeout = timeoutValue * 60 * 60 * 24;
                break;

            case 4:
                timeout = timeoutValue * 60 * 60 * 24 * 7;
                break;
            }
        }

        getClient()->getCommandHandler()->sendBanListAddCommand(banIdType, value, banType, reason, timeout);
    }
}
