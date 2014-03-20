#ifndef EXAMPLEPLUGININTERFACE_H
#define EXAMPLEPLUGININTERFACE_H

#include <QtGlobal>
#include <QtPlugin>

#include <QString>

#include "ExamplePluginWidget.h"

class ExamplePluginInterface
{
public:
    virtual QString getName() = 0;
    virtual QString getVersion() = 0;
    virtual QString getDescription() = 0;

};

Q_DECLARE_INTERFACE(ExamplePluginInterface, "org.ExamplePluginInterface/1.0");

#endif // EXAMPLEPLUGININTERFACE_H
