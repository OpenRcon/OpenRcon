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

#include "PluginDialog.h"

PluginDialog::PluginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PluginDialog)
{
    ui->setupUi(this);

    // Sets application title and icon
    setWindowTitle(QString(tr("Pluginmanager")));
    setWindowIcon(QIcon(APP_ICON));

    connect(ui->pushButton_pd_install, SIGNAL(clicked()), this, SLOT(installPlugin()));
    connect(ui->pushButton_pd_manage, SIGNAL(clicked()), this, SLOT(managePlugin()));
    connect(ui->pushButton_pd_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->pushButton_pd_ok, SIGNAL(clicked()), this, SLOT(accept()));
}

PluginDialog::~PluginDialog()
{
    delete ui;
}

void PluginDialog::installPlugin()
{
    QFileDialog fileDialog;
    QFile pluginFile;
    QString pluginFilePath;
    QString pluginFileName;
    QString pluginDestinationFilePath;

    QDir pluginDirectory(qApp->applicationDirPath());
    pluginDirectory.mkdir("plugins");

    // Get Plugin Location
    pluginFilePath = fileDialog.getOpenFileName(this, tr("Select Plugin"), QDir::homePath(), tr("OpenRcon Plugin (*.dll *.so)"));

    if (pluginFilePath != QString::null) {
        // Prepare file paths (URI)
        QFileInfo pluginFileInfo(pluginFilePath);
        pluginFileName = pluginFileInfo.fileName();
        pluginDestinationFilePath = pluginDirectory.absolutePath();
        pluginDestinationFilePath.append("/plugins/");
        pluginDestinationFilePath.append(pluginFileName);

        // Copy file to "plugins" directory
        bool copiedSuccessfully = pluginFile.copy(pluginFilePath, pluginDestinationFilePath);

        if (!copiedSuccessfully) {
            QMessageBox::critical(this, tr("Problem"), tr("OpenRcon could not copy your plugin into the plugind folder."));
            return;
        }
    }
}

void PluginDialog::managePlugin()
    {

}
