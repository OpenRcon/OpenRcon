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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QWidget>
#include <QPushButton>
#include <QFile>
#include <QString>

#include "ui_AboutDialog.h"
#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    // Sets application title
    setWindowTitle(tr("About") + " " + APP_NAME + " " + APP_VERSION);

    // About
    ui->label_ab_info->setText("<p>" + tr("A open-source cross-platform RCON administration tool, written in C++.") + "</p>");
    ui->label_ab_built->setText("<p>" + tr("Built on %2 at %3.").arg(__DATE__).arg(__TIME__) + "</p>");
    ui->label_ab_copyright->setText("<p>" + tr("Copyright") + " &copy; " + QString::number(APP_YEAR) + " " + APP_AUTHOR + "</p>");
    ui->label_ab_disclaimer->setText("<p>The program is provided AS IS with NO WARRANTY OF ANY KIND, <br />"
                                     "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND <br />"
                                     "FITNESS FOR A PARTICULAR PURPOSE.</p>");

    // Tabs with text files.
    ui->textBrowser_au->setText(getFile(":/AUTHORS"));
    ui->textBrowser_cb->setText(getFile(":/CONTRIBUTORS"));
    ui->textBrowser_tr->setText(getFile(":/TRANSLATORS"));
    ui->textBrowser_li->setText(getFile(":/COPYING"));

    // Thanks to
    ui->label_th->setText("<p>" + tr("We would like to thank Sourceforge.net for their services and support.") + "<br />" +
                          tr("A big thank to GitHub! For making a coders everyday easier.") + "</p>");

    connect(ui->pushButton_ab_close, &QPushButton::clicked, this, &QDialog::accept);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

QString AboutDialog::getFile(const QString &fileName) const
{   
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        return file.readAll();
    }

    return QString();
}
