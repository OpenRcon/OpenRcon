#include "BF4Level.h"

BF4Level::BF4Level(const QString &engineName, const QString &name, const QString &image, QObject *parent) : QObject(parent), engineName(engineName), name(name), image(":/bf4/levels/" + image)
{

}

BF4Level::~BF4Level()
{

}

QString BF4Level::getEngineName()
{
    return engineName;
}

QString BF4Level::getName()
{
    return name;
}

QPixmap BF4Level::getImage()
{
    return image;
}
