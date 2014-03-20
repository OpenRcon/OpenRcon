#ifndef MYPLUGINMANAGER_H
#define MYPLUGINMANAGER_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
    class myPluginManager;
}

class myPluginManager : public QWidget
{
    Q_OBJECT

public:
    explicit myPluginManager(QWidget *parent = 0);
    ~myPluginManager();
public slots:
    void installPlugin();
    void managePlugin();
private:
    Ui::myPluginManager *ui;
};

#endif // MYPLUGINMANAGER_H
