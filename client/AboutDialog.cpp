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

#include <QDateTime>
#include <QFile>
#include <QTextStream>

#include "ui_AboutDialog.h"
#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    // Sets application title
    setWindowTitle(tr("About %1 %2").arg(APP_NAME, APP_VERSION));

    QDateTime current = QDateTime::currentDateTime();
    ui->label_ab_info->setText(tr("<p>A open-source cross-platform RCON administration tool, written in C++.</p>"));
    ui->label_ab_built->setText(tr("<p>Built on %2 at %3</p>").arg(current.toString("dd MMMM yyyy")).arg(current.toString("hh:mm:ss")));
    ui->label_ab_copyright->setText(tr("<p>Copyright &copy; %4 %5</p>").arg(APP_YEAR).arg(APP_AUTHOR));
    ui->label_ab_disclaimer->setText("<p>The program is provided AS IS with NO WARRANTY OF ANY KIND, <br />"
                                     "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND <br />"
                                     "FITNESS FOR A PARTICULAR PURPOSE.</p>");

    ui->textBrowser_au->setText(getFile(":/AUTHORS"));
    ui->textBrowser_cb->setText(getFile(":/CONTRIBUTORS"));
    ui->textBrowser_tr->setText(getFile(":/TRANSLATORS"));
    ui->textBrowser_li->setText(getFile(":/COPYING"));

    ui->label_th->setText(tr("<p>We would like to thank Sourceforge.net for their services and support.<br />"
                             "A big thank to GitHub! For making a coders everyday easier.</p>"));

    connect(ui->pushButton_ab_close, &QPushButton::clicked, this, &QDialog::accept);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

QString AboutDialog::getFile(const QString &fileName)
{   
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        return file.readAll();
    }

    return QString();
}
