#ifndef BF4LEVEL_H
#define BF4LEVEL_H

#include <QObject>
#include <QPixmap>

#include "BF4GameMode.h"

class BF4Level : public QObject
{
    Q_OBJECT

public:
    explicit BF4Level(const QString &engineName, const QString &name, const QString &image, QObject *parent = 0);
    ~BF4Level();

    QString getEngineName();
    QString getName();
    QPixmap getImage();

private:
    QString engineName;
    QString name;
    QPixmap image;

};

#endif // BF4LEVEL_H
