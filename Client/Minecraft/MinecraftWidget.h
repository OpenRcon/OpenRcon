#ifndef MINECRAFTWIDGET_H
#define MINECRAFTWIDGET_H

#include <QTime>

#include "ui_Minecraft.h"

class MinecraftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MinecraftWidget(QWidget *parent = 0);
    ~MinecraftWidget();

    void logMessage(const int &type, const QString &message);
    void logEvents(const int &event, const QString &message);

private slots:
    void on_pushButton_co_co_send_clicked();

private:
    Ui::Minecraft *ui;

};

#endif // MINECRAFTWIDGET_H
