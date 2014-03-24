#ifndef BFBC2COMMANDHANDLER_H
#define BFBC2COMMANDHANDLER_H

#include "FrostbiteCommandHandler.h"

class BFBC2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    explicit BFBC2CommandHandler(QObject *parent = 0);
    ~BFBC2CommandHandler();

    void exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &players);

private:
    void startConnection();

    void commandLoginPlainText(const FrostbiteRconPacket &packet);
    void commandLoginHashed(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void commandVersion(const FrostbiteRconPacket &packet);
    void commandEventsEnabled(const FrostbiteRconPacket &packet);
    void commandServerInfo(const FrostbiteRconPacket &packet);
    void commandAdminListPlayersAll(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &players);
    void commandVarsTextChatModerationMode(const FrostbiteRconPacket &packet);
    void commandVarsTextChatSpamTriggerCount(const FrostbiteRconPacket &packet);
    void commandVarsTextChatSpamDetectionTime(const FrostbiteRconPacket &packet);
    void commandVarsTextChatSpamCoolDownTime(const FrostbiteRconPacket &packet);
    void commandBanListList(const FrostbiteRconPacket &packet);
    void commandReservedSlotsList(const FrostbiteRconPacket &packet);
    void commandMapListList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void commandMapListNextLevelIndex(const FrostbiteRconPacket &packet);
    void commandVarsServerName(const FrostbiteRconPacket &packet);
    void commandVarsServerDescription(const FrostbiteRconPacket &packet);
    void commandVarsBannerUrl(const FrostbiteRconPacket &packet);
    void commandPlayerOnJoin(const FrostbiteRconPacket &packet);
    void commandPlayerOnAuthenticated(const FrostbiteRconPacket &packet);
    void commandPlayerOnLeave(const FrostbiteRconPacket &packet);
    void commandPlayerOnSpawn(const FrostbiteRconPacket &packet);
    void commandPlayerOnKill(const FrostbiteRconPacket &packet);
    void commandPlayerOnChat(const FrostbiteRconPacket &packet);
    void commandPlayerOnKicked(const FrostbiteRconPacket &packet);
    void commandPlayerOnSquadChange(const FrostbiteRconPacket &packet);
    void commandPlayerOnTeamChange(const FrostbiteRconPacket &packet);
    void commandPunkBusterOnMessage(const FrostbiteRconPacket &packet);
    void commandServerOnLoadingLevel(const FrostbiteRconPacket &packet);
    void commandServerOnLevelStarted(const FrostbiteRconPacket &packet);
    void commandServerOnRoundOver(const FrostbiteRconPacket &packet);
    void commandServerOnRoundOverPlayers(const FrostbiteRconPacket &packet);
    void commandServerOnRoundOverTeamScores(const FrostbiteRconPacket &packet);
    void commandUnknown(const FrostbiteRconPacket &packet);

signals:
    void onStartConnection();

    void onLogMessage(const int &type, const QString &message);
    void onAuthenticated();
    void onGotSalt(QByteArray loginSalt);
    void onRefresh();
    void onLogEvent(const QString &event, const QString &message);
    void onIngameCommands(const QString &player, const QString &command);
    void onEventOnSpawn(const QString &player, const QString &kit);
    void onPlayerListChange();

    void onCommandServerInfo(QStringList si);
    void onCommandVarsTextChatModerationMode(const QString &tcmm);
    void onCommandVarsTextChatSpamTriggerCount(const QString &tcst);
    void onCommandBanListList(const QStringList &bl);
    void onCommandReservedSlotsList(const QStringList &rl);
    void onCommandMapListListRounds(const QStringList &ml);
    void onCommandMapListList(const QStringList &ml);
    void onCommandMapListNextLevelIndex(const int &mn);
    void onCommandVarsServerName(const QString &sn);
    void onCommandVarsServerDescription(const QString &sd);
    void onCommandVarsBannerUrl(const QString &bu);

};

#endif // BFBC2COMMANDHANDLER_H
