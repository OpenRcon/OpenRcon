#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGlobal>
#include <QDir>
#include <QPluginLoader>
#include "orplugininterface.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QList>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    bool loadPlugins(); // Loads or Reload all plugins in the plugins folder.
    bool loadPlugin(QString path); // Loads or Reloads specific plugin from the path location.
    bool unloadPlugins(); // Unloads all plugins after it has sent a signal to kill all uses of the plugins.
    bool unloadPlugin(QString path); // Unloads specific plugin from the path location.
    bool verifyPlugins();
    bool verifyPlugin(QString path);

public slots:
    void installPlugin(); // Spawns User interface to install a plugin.
    void updateManageButton();
    void manageButtonClicked();
private:
    Ui::Dialog *ui;
    QList<orPluginInterface> pluginInterface;
    orPluginInterface *plugins;

};

#endif // DIALOG_H
