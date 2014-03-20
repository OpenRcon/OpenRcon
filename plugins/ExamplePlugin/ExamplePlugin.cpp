#include "ExamplePlugin.h"

QString ExamplePlugin::getName()
{
    return name;
}

QString ExamplePlugin::getVersion()
{
    return version;
}

QString ExamplePlugin::getDescription()
{
    return "";
}

Q_EXPORT_PLUGIN2(ExamplePlugin, ExamplePlugin);
