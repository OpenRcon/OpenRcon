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

#include <QStringList>
#include <QCompleter>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QList>
#include <QPoint>
#include <QCursor>
#include <QString>
#include <QTableWidgetItem>

#include "BanListWidget.h"
#include "ui_BanListWidget.h"
#include "FrostbiteClient.h"
#include "BanListEntry.h"
#include "FrostbiteUtils.h"

BanListWidget::BanListWidget(FrostbiteClient *client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BanListWidget),
    client(client)
{
    ui->setupUi(this);

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

    /* Commands */
    // BanList
    connect(client->getCommandHandler(), &FrostbiteCommandHandler::onBanListListCommand, this, &BanListWidget::onBanListListCommand);

    /* User Interface */
    connect(ui->tableWidget_bl_banList, &QTableWidget::customContextMenuRequested,                              this, &BanListWidget::tableWidget_bl_banList_customContextMenuRequested);
    connect(action_bl_banList_remove,   &QAction::triggered,                                                    this, &BanListWidget::action_bl_banList_remove_triggered);
    connect(ui->pushButton_load,        &QPushButton::clicked,                                                  this, &BanListWidget::pushButton_load_clicked);
    connect(ui->pushButton_save,        &QPushButton::clicked,                                                  this, &BanListWidget::pushButton_save_clicked);
    connect(ui->pushButton_clear,       &QPushButton::clicked,                                                  this, &BanListWidget::pushButton_clear_clicked);
    connect(ui->lineEdit_value,         &QLineEdit::textChanged,                                                this, &BanListWidget::validate);
    connect(ui->lineEdit_reason,        &QLineEdit::textChanged,                                                this, &BanListWidget::validate);
    connect(ui->radioButton_permanent,  &QRadioButton::clicked,                                                 this, &BanListWidget::radioButton_permanent_clicked);
    connect(ui->radioButton_temporary,  &QRadioButton::clicked,                                                 this, &BanListWidget::radioButton_temporary_clicked);
    connect(ui->comboBox_by,            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &BanListWidget::comboBox_by_currentIndexChanged);
    connect(ui->pushButton_ban,         &QPushButton::clicked,                                                  this, &BanListWidget::pushButton_ban_clicked);
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
void BanListWidget::tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableWidget_bl_banList->itemAt(pos)) {
        menu_bl_banList->exec(QCursor::pos());
    }
}

void BanListWidget::action_bl_banList_remove_triggered()
{
    int row = ui->tableWidget_bl_banList->currentRow();
    QString idType = ui->tableWidget_bl_banList->item(row, 0)->text();
    QString player = ui->tableWidget_bl_banList->item(row, 1)->text();

    if (!idType.isEmpty() && !player.isEmpty()) {
        ui->tableWidget_bl_banList->removeRow(row);

        client->getCommandHandler()->sendBanListRemoveCommand(idType, player);
    }
}

void BanListWidget::addBanListItem(const QString &idType, const QString &id, const QString &banType, int seconds, int rounds, const QString &reason)
{
    int row = ui->tableWidget_bl_banList->rowCount();

    ui->tableWidget_bl_banList->insertRow(row);
    ui->tableWidget_bl_banList->setItem(row, 0, new QTableWidgetItem(idType));
    ui->tableWidget_bl_banList->setItem(row, 1, new QTableWidgetItem(id));
    QString remaining;

    if (banType == "perm") {
        remaining = tr("Permanent");
    } else if (banType == "rounds") {
        remaining = tr("%1 Rounds").arg(QString::number(rounds));
    } else if (banType == "seconds") {
        remaining = tr("%1 Seconds").arg(QString::number(seconds));
    }

    ui->tableWidget_bl_banList->setItem(row, 2, new QTableWidgetItem(remaining));
    ui->tableWidget_bl_banList->setItem(row, 3, new QTableWidgetItem(reason));
}

void BanListWidget::setBanlist(const QList<BanListEntry> &banList)
{
    ui->tableWidget_bl_banList->clearContents();
    ui->tableWidget_bl_banList->setRowCount(0);

    for (BanListEntry entry : banList) {
        addBanListItem(entry.idType, entry.id, entry.banType, entry.seconds, entry.rounds, entry.reason);
    }
}

void BanListWidget::pushButton_load_clicked()
{
    client->getCommandHandler()->sendBanListLoadCommand();
}

void BanListWidget::pushButton_save_clicked()
{
    client->getCommandHandler()->sendBanListSaveCommand();
}

void BanListWidget::pushButton_clear_clicked()
{
    ui->tableWidget_bl_banList->clearContents();
    ui->pushButton_clear->setEnabled(ui->tableWidget_bl_banList->rowCount() < 0);
    client->getCommandHandler()->sendBanListClearCommand();
}

void BanListWidget::validate()
{
    bool enabled = !ui->lineEdit_value->text().isEmpty() && !ui->lineEdit_reason->text().isEmpty();

    ui->radioButton_permanent->setEnabled(enabled);
    ui->radioButton_temporary->setEnabled(enabled);
    ui->pushButton_ban->setEnabled(enabled);
}

void BanListWidget::radioButton_permanent_clicked()
{
    setTemporaryEnabled(false);
}

void BanListWidget::radioButton_temporary_clicked()
{
    setTemporaryEnabled(true);
}

void BanListWidget::setTemporaryEnabled(bool enabled)
{
    ui->comboBox_by->setEnabled(enabled);
    ui->spinBox_timeout->setEnabled(enabled);
    ui->comboBox_timeUnit->setEnabled(enabled);
}

void BanListWidget::comboBox_by_currentIndexChanged(int index)
{
    ui->comboBox_timeUnit->setEnabled(index == 0);
}

void BanListWidget::pushButton_ban_clicked()
{
    QString idType = ui->comboBox_type->currentText().toLower();
    QString value = ui->lineEdit_value->text();
    QString reason = ui->lineEdit_reason->text();

    if (ui->radioButton_permanent->isChecked()) {
        client->getCommandHandler()->sendBanListAddCommand(idType, value, reason);
    } else {
        bool useRounds = ui->comboBox_by->currentIndex() > 0;
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

        client->getCommandHandler()->sendBanListAddCommand(idType, value, timeout, useRounds, reason);
    }
}
