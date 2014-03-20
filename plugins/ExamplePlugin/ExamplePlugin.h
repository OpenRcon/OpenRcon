#ifndef EXAMPLEPLUGIN_H
#define EXAMPLEPLUGIN_H

#include "ExamplePlugin_global.h"
#include "ExamplePluginInterface.h"
#include "ExamplePlugin.h"
#include "ExamplePluginWidget.h"


class EXAMPLEPLUGIN_EXPORT ExamplePlugin : public QObject, public ExamplePluginInterface
{
    Q_OBJECT
    Q_INTERFACES(ExamplePluginInterface)

public:
    QString getName();
    QString getVersion();
    QString getDescription();

private:
    QString name;
    QString version;
    QString description;
};

#endif // EXAMPLEPLUGIN_H
