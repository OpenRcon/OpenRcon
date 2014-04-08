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

ServerEditDialog::ServerEditDialog(QObject *parent) : ui(new Ui::ServerEditDialog)
{
    Q_UNUSED(parent);

    ui->setupUi(this);

    setWindowTitle(tr("Server details"));
    setWindowIcon(QIcon(APP_ICON));

    ui->comboBox_sed_game->clear();

    foreach (GameEntry entry, OpenRcon::getInstance()->getGameManager()->getGames()) {
        ui->comboBox_sed_game->addItem(entry.icon, entry.name, entry.id);
    }

    ui->spinBox_sed_port->setRange(1, 65535);
    ui->lineEdit_sed_password->setEchoMode(QLineEdit::Password);

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

ServerEditDialog::ServerEditDialog(const int &game, const QString &name, const QString &host, const int &port, const QString &password, QObject *parent) : ServerEditDialog(parent)
{
    ui->comboBox_sed_game->setCurrentIndex(game);
    ui->lineEdit_sed_name->setText(name);
    ui->lineEdit_sed_host->setText(host);
    ui->spinBox_sed_port->setValue(port);
    ui->lineEdit_sed_password->setText(password);
}

ServerEditDialog::~ServerEditDialog()
{
    delete ui;
}

void ServerEditDialog::validate()
{   
    ui->pushButton_sed_ok->setEnabled(
    ui->comboBox_sed_game->currentIndex() != -1 &&
    !ui->lineEdit_sed_name->text().isEmpty() &&
    !ui->lineEdit_sed_host->text().isEmpty() &&
    !ui->spinBox_sed_port->text().isEmpty() &&
    !ui->lineEdit_sed_password->text().isEmpty());
}

int ServerEditDialog::getGame()
{
    return ui->comboBox_sed_game->currentIndex();
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
