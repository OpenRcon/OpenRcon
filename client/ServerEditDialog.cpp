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

#include "ui_ServerEditDialog.h"
#include "ServerEditDialog.h"

#include <QDebug>

#include "GameEntry.h"
#include "GameManager.h"

ServerEditDialog::ServerEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ServerEditDialog)
{
    ui->setupUi(this);

    for (GameEntry entry : GameManager::getGames()) {
        ui->comboBox_game->addItem(QIcon(entry.icon), entry.name);
    }

    ui->spinBox_port->setValue(GameManager::getGame(0).defaultPort);

    connect(ui->comboBox_game, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ServerEditDialog::comboBox_game_currentIndexChanged);
    connect(ui->lineEdit_host, &QLineEdit::editingFinished,                                            this, &ServerEditDialog::lineEdit_host_editingFinished);

    connect(ui->lineEdit_name, &QLineEdit::textChanged, this, &ServerEditDialog::detect);
    connect(ui->lineEdit_host, &QLineEdit::textChanged, this, &ServerEditDialog::detect);

    connect(ui->comboBox_game,     static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ServerEditDialog::validate);
    connect(ui->lineEdit_name,     &QLineEdit::textChanged,                                                this, &ServerEditDialog::validate);
    connect(ui->lineEdit_host,     &QLineEdit::textChanged,                                                this, &ServerEditDialog::validate);
    connect(ui->spinBox_port,      static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),          this, &ServerEditDialog::validate);
    connect(ui->lineEdit_password, &QLineEdit::textChanged,                                                this, &ServerEditDialog::validate);

    connect(ui->lineEdit_name,     &QLineEdit::returnPressed, this, &ServerEditDialog::accept);
    connect(ui->lineEdit_host,     &QLineEdit::returnPressed, this, &ServerEditDialog::accept);
    connect(ui->lineEdit_password, &QLineEdit::returnPressed, this, &ServerEditDialog::accept);

    connect(ui->pushButton_ok,     &QPushButton::clicked, this, &ServerEditDialog::accept);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &ServerEditDialog::reject);

    validate();
}

ServerEditDialog::ServerEditDialog(int index, QWidget *parent) : ServerEditDialog(parent)
{
    ui->comboBox_game->setCurrentIndex(index);
}

ServerEditDialog::ServerEditDialog(int index, const QString &name, const QString &host, int port, const QString &password, bool autoConnect, QWidget *parent) : ServerEditDialog(index, parent)
{
    ui->lineEdit_name->setText(name);
    ui->lineEdit_host->setText(host);
    ui->spinBox_port->setValue(port);
    ui->lineEdit_password->setText(password);
    ui->checkBox_autoConnect->setChecked(autoConnect);
}

ServerEditDialog::~ServerEditDialog()
{
    delete ui;
}

void ServerEditDialog::comboBox_game_currentIndexChanged(int index)
{
    ui->spinBox_port->setValue(GameManager::getGame(GameManager::toGameType(index)).defaultPort);
}

void ServerEditDialog::lineEdit_host_editingFinished()
{
    if (ui->lineEdit_name->text().isEmpty()) {
        ui->lineEdit_name->setText(ui->lineEdit_host->text());
    }
}

void ServerEditDialog::detect(const QString &value)
{
    for (GameEntry entry : GameManager::getGames()) {
        if (value.contains(entry.prefix, Qt::CaseInsensitive) || value.contains(entry.name, Qt::CaseInsensitive)) {
            ui->comboBox_game->setCurrentIndex(GameManager::toInt(entry.gameType));
        }
    }
}

void ServerEditDialog::validate()
{   
    ui->pushButton_ok->setEnabled(!ui->lineEdit_name->text().isEmpty() && !ui->lineEdit_host->text().isEmpty() && ui->spinBox_port->value() > 0);
}

void ServerEditDialog::accept()
{
    QString password = ui->lineEdit_password->text();

    if (password.isEmpty()) {
        int answer = QMessageBox::question(this, tr("Password not set"), tr("Are you sure you want to continue without a password? This may limit functionality."));

        if (answer == QMessageBox::No) {
            return;
        }
    }

    QDialog::accept();
}

GameType ServerEditDialog::getGameType()
{
    return GameManager::toGameType(ui->comboBox_game->currentIndex());
}

QString ServerEditDialog::getName()
{
    return ui->lineEdit_name->text();
}

QString ServerEditDialog::getHost()
{
    return ui->lineEdit_host->text();
}

int ServerEditDialog::getPort()
{
    return ui->spinBox_port->value();
}

QString ServerEditDialog::getPassword()
{
    return ui->lineEdit_password->text();
}

bool ServerEditDialog::getAutoConnect()
{
    return ui->checkBox_autoConnect->isChecked();
}
