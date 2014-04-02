#ifndef LEVELENTRY_H
#define LEVELENTRY_H

#include <QString>
#include <QPixmap>

struct LevelEntry {
    LevelEntry()
    {

    }

    LevelEntry(QString engineName, QString name, QString image) : engineName(engineName), name(name), image(QPixmap(image))
    {

    }

    QString engineName;
    QString name;
    QPixmap image;

};

#endif // LEVELENTRY_H
