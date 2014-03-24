#ifndef MINECRAFTWIDGET_H
#define MINECRAFTWIDGET_H

#include <QTime>

#include "ui_Minecraft.h"
#include "Minecraft.h"

class MinecraftWidget : public Minecraft
{
    Q_OBJECT

public:
    explicit MinecraftWidget(const QString &host, const int &port, const QString &password);
    ~MinecraftWidget();

    void logMessage(const int &type, const QString &message);
    void logEvent(const int &event, const QString &message);

private slots:
    void slotAuthenticated(bool auth);
    void slotPacket(const QString &packet);
    void slotUnknownCommand();

    void on_pushButton_co_send_clicked();

private:
    Ui::Minecraft *ui;

};

#endif // MINECRAFTWIDGET_H
