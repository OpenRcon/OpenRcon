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

#include "About.h"

About::About(QObject *parent) : ui(new Ui::About)
{
    Q_UNUSED(parent);

    ui->setupUi(this);

    // Sets application title and icon
    setWindowTitle(tr("About %1 %2").arg(APP_NAME, APP_VERSION));
    setWindowIcon(QIcon(APP_ICON));

    QDateTime current = QDateTime::currentDateTime();
    QString description = tr("<p>%1 is a cross-platform RCON administration tool.</p>"
                             "<p>Built on %2 at %3</p>"
                             "Copyright &copy; %4 %5</p>"

                             "<p>The program is provided AS IS with NO WARRANTY OF ANY KIND, <br />"
                             "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND <br />"
                             "FITNESS FOR A PARTICULAR PURPOSE.</p>"
                             ).arg(APP_NAME)
                              .arg(current.toString("dd MMMM yyyy"))
                              .arg(current.toString("hh:mm:ss"))
                              .arg(APP_YEAR)
                              .arg(APP_AUTHOR);

    ui->label_ab->setText(description);

    ui->textBrowser_au->setText(getFile(":/AUTHORS"));
    ui->textBrowser_cb->setText(getFile(":/CONTRIBUTORS"));
    ui->textBrowser_tr->setText(getFile(":/TRANSLATORS"));
    ui->textBrowser_li->setText(getFile(":/COPYING"));

    QString thanksTo = QString(tr("<p>We would like to thanks sourceforge.net for their services and support.</p>"));
    ui->label_th->setText(thanksTo);

    connect(ui->pushButton_ab_close, SIGNAL(clicked()), this, SLOT(reject()));
}

About::~About()
{
    delete ui;
}

QString About::getFile(const QString &fileName)
{
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString text = stream.readAll();

        return text;
    }

    return QString();
}
