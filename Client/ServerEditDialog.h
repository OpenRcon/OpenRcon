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

#include <QDialog>

#include "ui_ServerEditDialog.h"
#include "GameManager.h"

class ServerEditDialog : public QDialog
{
    Q_OBJECT

public:
    ServerEditDialog(QWidget *parent = nullptr);
    ServerEditDialog(int game, QWidget *parent = nullptr);
    ServerEditDialog(int game, const QString &name = 0, const QString &host = 0, int port = 0, const QString &password = 0, bool autoConnect = false, QWidget *parent = nullptr);
    ~ServerEditDialog();

    int getGame();
    QString getName();
    QString getHost();
    int getPort();
    QString getPassword();
    bool getAutoConnect();

private:
    Ui::ServerEditDialog *ui;

    GameManager *gameManager;

private slots:
    void lineEdit_sed_host_editingFinished();

    void detect(const QString &value);
    void validate();
    void accept();

};

#endif // SERVEREDITDIALOG_H
