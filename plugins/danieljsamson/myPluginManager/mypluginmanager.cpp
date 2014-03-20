#include "mypluginmanager.h"
#include "ui_mypluginmanager.h"

myPluginManager::myPluginManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myPluginManager)
{
    ui->setupUi(this);

}

myPluginManager::~myPluginManager()
{
    delete ui;
}

void myPluginManager::installPlugin()
{
      QMessageBox::information(this, tr("It Works"), tr("Slot: installPlugin()"));
}
void myPluginManager::managePlugin()
{
    QMessageBox::information(this, tr("It Works"), tr("Slot: managePlugin()"));
}
