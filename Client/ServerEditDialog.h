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

#include <QObject>
#include <QDebug>
#include <QDialog>
#include <QPushButton>
#include <QHostAddress>

#include "ui_ServerEditDialog.h"

#include "Constants.h"
#include "OpenRcon.h"

using namespace Constants;

class ServerEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerEditDialog(QObject *parent = 0);
    explicit ServerEditDialog(const int &game, const QString &name, const QString &host, const int &port, const QString &password, QObject *parent = 0);
    ~ServerEditDialog();

    int getGame();
    QString getName();
    QString getHost();
    int getPort();
    QString getPassword();

private:
    Ui::ServerEditDialog *ui;

private slots:
    void validate();

};

#endif // SERVEREDITDIALOG_H
