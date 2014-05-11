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

#include "OptionsDialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    settings = new QSettings(APP_NAME, APP_NAME, this);
    languageManager = new LanguageManager(this);

    // Add languages to comboBox_ge_language.
    ui->comboBox_be_language->addItem(tr("<System Language>"));

    for (LanguageEntry language : languageManager->getLanguages()) {
        ui->comboBox_be_language->addItem(language.icon, language.name);
    }

    readSettings();

    pushButton_ok = ui->buttonBox->button(QDialogButtonBox::Ok);
    pushButton_cancel = ui->buttonBox->button(QDialogButtonBox::Cancel);
    pushButton_apply = ui->buttonBox->button(QDialogButtonBox::Apply);

    connect(ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*)));
    connect(pushButton_ok, SIGNAL(clicked()), this, SLOT(pushButton_ok_clicked()));
    connect(pushButton_cancel , SIGNAL(clicked()), this, SLOT(reject()));
}

OptionsDialog::~OptionsDialog()
{
    writeSettings();

    delete ui;
    delete settings;
    delete languageManager;
}

void OptionsDialog::readSettings()
{
    QString locale = settings->value("Settings/General/Locale").toString();

    // TODO: Set the current language index here.
}

void OptionsDialog::writeSettings()
{

}

void OptionsDialog::listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current) {
        ui->stackedWidget->setCurrentIndex(ui->listWidget->row(current));
    } else {
        current = previous;
    }
}

void OptionsDialog::pushButton_ok_clicked()
{
    int index = ui->comboBox_be_language->currentIndex();
    QString language = index >= 1 ? languageManager->getLanguage(index - 1).code : language = QLocale::system().name();

    settings->setValue("Settings/General/Locale", language);

    QDialog::accept();
}
