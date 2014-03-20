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
    setWindowTitle(QString(tr("About %1")).arg(APP_NAME));
    setWindowIcon(QIcon(APP_ICON));

    ui->label_ab_logo->setPixmap(QPixmap(":/data/graphics/icons/openrcon.png"));
    ui->label_ab_name->setText(QString("<h3>%1 %2</h3>").arg(APP_NAME, APP_VERSION));

    QString description = QString(tr("%1 is a cross-platform RCON administration tool.<br />"
                            "<br />"
                            "Built on %2 at %3<br />"
                            "<br/>"
                            "Copyright &copy; %4 %5<br />"
                            "<br />"
                            "The program is provided AS IS with NO WARRANTY OF ANY KIND, <br />"
                            "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND <br />"
                            "FITNESS FOR A PARTICULAR PURPOSE.<br/>")).arg(APP_NAME, __DATE__, __TIME__, APP_YEAR, APP_AUTHOR);

    ui->label_ab->setText(description);

    ui->textBrowser_au->setText(getFile(":/AUTHORS"));
    ui->textBrowser_cb->setText(getFile(":/CONTRIBUTORS"));
    ui->textBrowser_tr->setText(getFile(":/TRANSLATORS"));
    ui->textBrowser_li->setText(getFile(":/COPYING"));

    QString thanksto = QString(tr("We would like to thanks sourceforge.net for their services and support.<br />"));
    ui->label_th->setText(thanksto);

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
