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

#include "ServerEditDialog.h"

ServerEditDialog::ServerEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ServerEditDialog)
{
    ui->setupUi(this);

    ui->comboBox_sed_game->clear();

    for (GameEntry entry : GameManager::getGames()) {
        ui->comboBox_sed_game->addItem(entry.icon, entry.name, static_cast<int>(entry.gameType));
    }

    ui->spinBox_sed_port->setRange(1, 65535);
    ui->spinBox_sed_port->setValue(48888);
    ui->lineEdit_sed_password->setEchoMode(QLineEdit::Password);

    connect(ui->lineEdit_sed_name, SIGNAL(textChanged(QString)), this, SLOT(detect(QString)));
    connect(ui->lineEdit_sed_host, SIGNAL(textChanged(QString)), this, SLOT(detect(QString)));

    connect(ui->comboBox_sed_game, SIGNAL(currentIndexChanged(int)), this, SLOT(validate()));
    connect(ui->lineEdit_sed_name, SIGNAL(textChanged(QString)), this, SLOT(validate()));
    connect(ui->lineEdit_sed_host, SIGNAL(textChanged(QString)), this, SLOT(validate()));
    connect(ui->spinBox_sed_port, SIGNAL(valueChanged(int)), this, SLOT(validate()));
    connect(ui->lineEdit_sed_password, SIGNAL(textChanged(QString)), this, SLOT(validate()));

    connect(ui->lineEdit_sed_name, SIGNAL(returnPressed()), this, SLOT(accept()));
    connect(ui->lineEdit_sed_host, SIGNAL(returnPressed()), this, SLOT(accept()));
    connect(ui->lineEdit_sed_password, SIGNAL(returnPressed()), this, SLOT(accept()));

    connect(ui->pushButton_sed_ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButton_sed_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    validate();
}

ServerEditDialog::ServerEditDialog(GameType gameType, QWidget *parent) : ServerEditDialog(parent)
{
    ui->comboBox_sed_game->setCurrentIndex(static_cast<int>(gameType));
}

ServerEditDialog::ServerEditDialog(GameType gameType, const QString &name, const QString &host, int port, const QString &password, bool autoConnect, QWidget *parent) : ServerEditDialog(gameType, parent)
{
    ui->lineEdit_sed_name->setText(name);
    ui->lineEdit_sed_host->setText(host);
    ui->spinBox_sed_port->setValue(port);
    ui->lineEdit_sed_password->setText(password);
    ui->checkBox_sed_autoConnect->setChecked(autoConnect);
}

ServerEditDialog::~ServerEditDialog()
{
    delete ui;
}

void ServerEditDialog::detect(const QString &value)
{
    for (GameEntry entry : GameManager::getGames()) {
        if (value.contains(entry.prefix, Qt::CaseInsensitive) ||
            value.contains(entry.name, Qt::CaseInsensitive)) {
            ui->comboBox_sed_game->setCurrentIndex(static_cast<int>(entry.gameType));
        }
    }
}

void ServerEditDialog::validate()
{   
    ui->pushButton_sed_ok->setEnabled(
    ui->comboBox_sed_game->currentIndex() >= 0 &&
    !ui->lineEdit_sed_name->text().isEmpty() &&
    !ui->lineEdit_sed_host->text().isEmpty() &&
    ui->spinBox_sed_port->value() > 0);
}

void ServerEditDialog::accept()
{
    QString password = ui->lineEdit_sed_password->text();

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
    return static_cast<GameType>(ui->comboBox_sed_game->currentIndex());
}

QString ServerEditDialog::getName()
{
    return ui->lineEdit_sed_name->text();
}

QString ServerEditDialog::getHost()
{
    return ui->lineEdit_sed_host->text();
}

int ServerEditDialog::getPort()
{
    return ui->spinBox_sed_port->value();
}

QString ServerEditDialog::getPassword()
{
    return ui->lineEdit_sed_password->text();
}

bool ServerEditDialog::getAutoConnect()
{
    return ui->checkBox_sed_autoConnect->isChecked();
}
