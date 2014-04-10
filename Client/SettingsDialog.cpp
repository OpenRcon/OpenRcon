/*
 * Copyright (C) 2011 The OpenRcon Project.
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

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
    Q_UNUSED(parent);

    ui->setupUi(this);

    // Sets application title and icon
    setWindowTitle(tr("Settings"));
    setWindowIcon(QIcon(APP_ICON));

    // Create and load settings.
    settings = new QSettings(APP_NAME, APP_NAME);
    readSettings();

    pushButton_ok = ui->buttonBox_st->button(QDialogButtonBox::Ok);
    pushButton_cancel = ui->buttonBox_st->button(QDialogButtonBox::Cancel);
    pushButton_apply = ui->buttonBox_st->button(QDialogButtonBox::Apply);

    connect(ui->listWidget_st, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listWidget_st_currentItemChanged(QListWidgetItem*, QListWidgetItem*)));

    connect(pushButton_ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(pushButton_cancel , SIGNAL(clicked()), this, SLOT(reject()));
}

void SettingsDialog::listWidget_st_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current) {
        ui->stackedWidget_st->setCurrentIndex(ui->listWidget_st->row(current));
    } else {
        current = previous;
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
    delete settings;
}

void SettingsDialog::readSettings()
{
    settings->beginGroup("Settings");
    settings->endGroup();
}

void SettingsDialog::writeSettings()
{
    settings->beginGroup("Settings");
    settings->endGroup();
}
