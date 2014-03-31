#ifndef FROSTBITECOMMANDHANDLER_H
#define FROSTBITECOMMANDHANDLER_H

#include <QDebug>

#include "FrostbiteRconPacket.h"

class FrostbiteCommandHandler : public QObject
{
    Q_OBJECT

public:
    explicit FrostbiteCommandHandler(QObject *parent = 0);
    ~FrostbiteCommandHandler();

    virtual void exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    void eventOnDataSent(const QString &command);
    void eventOnDataReceived(const QString &response);

    void commandUnknown();

signals:
    void onDataSent(const QString &command);
    void onDataReceived(const QString &response);

    void onUnknownCommand();

};

#endif // FROSTBITECOMMANDHANDLER_H
