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
#include <QSettings>
#include <QListWidget>
#include <QDialogButtonBox>
#include <QList>
#include <QLocale>
#include <QVariant>
#include <QMessageBox>
#include <QProcess>
#include <QApplication>
#include <QListWidgetItem>


#include "ui_OptionsDialog.h"
#include "OptionsDialog.h"
#include "LanguageManager.h"
#include "LanguageEntry.h"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    settings = new QSettings(APP_NAME, APP_NAME, this);
    languageManager = new LanguageManager(this);

    loadSettings();

    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &OptionsDialog::listWidget_currentItemChanged);
    connect(ui->buttonBox,  &QDialogButtonBox::accepted,      this, &OptionsDialog::accept);
    connect(ui->buttonBox,  &QDialogButtonBox::rejected,      this, &QDialog::reject);
}

OptionsDialog::~OptionsDialog()
{
    saveSettings();

    delete ui;
    delete settings;
    delete languageManager;
}

void OptionsDialog::loadSettings()
{
    // Add languages to comboBox_ge_language.
    QList<LanguageEntry> languageList = languageManager->getLanguages();
    languageList.insert(0, LanguageEntry(tr("Detect automatically"), QLocale::system().name(), nullptr));

    for (LanguageEntry language : languageList) {
        ui->comboBox_be_language->addItem(language.getIcon(), language.getName(), QVariant::fromValue(language));
    }

    // Set index of combobox to selected language.
    LanguageEntry language = languageManager->getLanguage(settings->value("Settings/General/Locale").toString());
    int index = ui->comboBox_be_language->findData(QVariant::fromValue(language));

    if (index >= 0) {
        ui->comboBox_be_language->setCurrentIndex(index);
    }
}

void OptionsDialog::saveSettings()
{
    LanguageEntry previousLanguage = languageManager->getLanguage(settings->value("Settings/General/Locale").toString());
    LanguageEntry language = ui->comboBox_be_language->currentData().value<LanguageEntry>();

    if (previousLanguage.getCode() != language.getCode()) {
        settings->setValue("Settings/General/Locale", language.getCode());

        int answer = QMessageBox::question(this, tr("Language changed"), tr("In order for language to change on user interface, you'll have to restart %1. Do you want to restart it now?").arg(Constants::APP_NAME));

        if (answer == QMessageBox::Yes) {
            // Restart the application process.
            QProcess::startDetached(QApplication::applicationFilePath());
        }
    }
}

void OptionsDialog::listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous);

    if (current) {
        ui->stackedWidget->setCurrentIndex(ui->listWidget->row(current));
    }
}

void OptionsDialog::accept()
{
    saveSettings();

    QDialog::accept();
}
