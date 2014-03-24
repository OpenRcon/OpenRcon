#ifndef MINECRAFTCOMMANDHANDLER_H
#define MINECRAFTCOMMANDHANDLER_H

#include <QObject>
#include <QString>
#include <QStringList>

class MinecraftCommandHandler : public QObject
{
    Q_OBJECT

public:
    explicit MinecraftCommandHandler(QObject *parent = 0);
    ~MinecraftCommandHandler();

    void exec(const int &command, const QString &packet);
    int getRequestIdForCommand(const QString &command);

private:
    void helpCommand(const QString &packet);
    void listCommand(const QString &packet);
    void unknownCommand(const QString &packet);

signals:
    void onHelpCommand(const QString &packet);
    void onListCommand(const QStringList &packet);
    void onUnknownCommand();

};

#endif // MINECRAFTCOMMANDHANDLER_H
