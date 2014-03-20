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

#ifndef SERVEREDITDIALOG_H
#define SERVEREDITDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QPushButton>
#include <QObject>

#include "ui_ServerEditDialog.h"

#include "Constants.h"

using namespace Constants;

class ServerEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerEditDialog(const QString &game, const QString &name, const QString &host, const QString &port, const QString &password, QObject *parent = 0);
    ~ServerEditDialog();

    QString getGame() const;
    QString getName() const;
    QString getHost() const;
    QString getPort() const;
    QString getPassword() const;

private:
    Ui::ServerEditDialog *ui;

private slots:
    void validate();

};

inline QString ServerEditDialog::getGame() const
{
    return ui->comboBox_sed_game->itemData(ui->comboBox_sed_game->currentIndex()).toString();
}

inline QString ServerEditDialog::getName() const
{
    return ui->lineEdit_sed_name->text();
}

inline QString ServerEditDialog::getHost() const
{
    return ui->lineEdit_sed_host->text();
}

inline QString ServerEditDialog::getPort() const
{
    return ui->lineEdit_sed_port->text();
}

inline QString ServerEditDialog::getPassword() const
{
    return ui->lineEdit_sed_password->text();
}

#endif // SERVEREDITDIALOG_H
