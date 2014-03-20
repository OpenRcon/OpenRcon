#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QListWidget>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    loadPlugins();
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::loadPlugins()
{
    ui->listWidgetPlugins->clear();
    QDir pluginsDir(qApp->applicationDirPath());
     #if defined(Q_OS_WIN)
         if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
            // pluginsDir.cdUp();
     #elif defined(Q_OS_MAC)
         if (pluginsDir.dirName() == "MacOS") {
             pluginsDir.cdUp();
             pluginsDir.cdUp();
             pluginsDir.cdUp();
         }
     #endif
         pluginsDir.cd("plugins");
         foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
             QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
             QObject *plugin = pluginLoader.instance();
             if (plugin) {
                 plugins = qobject_cast<orPluginInterface *>(plugin);

                 if (plugins)
                     ui->listWidgetPlugins->addItem(plugins->getName());


                     return true;
             }
         }

         return false;

}

bool Dialog::unloadPlugins()
{
    return false;
}

bool Dialog::unloadPlugin(QString path)
{
    return false;
}

void Dialog::installPlugin()
{
    QFileDialog fileDialog;
    QFile pluginFile;
    QString pluginFilePath;
    QString pluginFileName;
    QString pluginDestinationFilePath;
    QDir pluginDirectory(qApp->applicationDirPath());
    pluginDirectory.mkdir("plugins");

    // Get Plugin Location
    pluginFilePath = fileDialog.getOpenFileName(this,tr("Select Plug-in"), QDir::homePath(), tr("OpenRCON Plugins (*.dll *.so)"));

    if(pluginFilePath != QString::null)
    {
        // Prepare file paths (URI)
        QFileInfo pluginFileInfo(pluginFilePath);
        pluginFileName = pluginFileInfo.fileName();
        pluginDestinationFilePath = pluginDirectory.absolutePath();
        pluginDestinationFilePath.append("/plugins/");
        pluginDestinationFilePath.append(pluginFileName);

        // Copy file to "plugins" directory
        bool copiedSuccessfully = pluginFile.copy(pluginFilePath, pluginDestinationFilePath);
        //
        if(!copiedSuccessfully)
        {
            QMessageBox::critical(this, tr("Problem"), tr("OpenRCON could not copy your plugin into the plugin folder"));
            return;
        }
        // Reload plugins
        if(this->loadPlugins())
        {
         // Test plugin

        }
        else
        {
            QMessageBox::critical(this, tr("Problem"), tr("OpenRCON load plugin."));
            return;
        }

    }

    //QMessageBox::information(this,"installPlugin","slot: installPlugin Works!!!!", QMessageBox::Ok);
}
void Dialog::updateManageButton()
{
    ui->pushButtonManage->setEnabled(true);
}
void Dialog::manageButtonClicked()
{
    QMessageBox::information(this,"managePlugin","slot: managePlugin Works!!!!", QMessageBox::Ok);

}
