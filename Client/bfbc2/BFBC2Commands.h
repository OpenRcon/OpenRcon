/*
 * Copyright (C) 2010 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BFBC2COMMANDS_H
#define BFBC2COMMANDS_H

#include <QObject>
#include <QStringList>
#include <QTextDocument>

#include "BFBC2RconPacket.h"

typedef QMap<QString, QString> PlayerListItem;
typedef QVector<PlayerListItem> PlayerList;


class BFBC2CommandSignals : public QObject
{
    Q_OBJECT

public:
    BFBC2CommandSignals(QObject *parent = 0);

    void signalRefresh();

    void signalLogMessage(const QString& type, const QString& msg);
    void signalLogEvents(const QString& event, const QString& msg);
    void signalIngameCommands(const QString& player, const QString& cmd);
    void signalStartConnection();
    void signalGotSalt(const QByteArray& salt);
    void signalAuthenticated();
    void signalPlayerListChange();

    void signalEventOnSpawn(const QString& player, const QString& kit);

    void signalCommandServerInfo(QStringList si);
    void signalCommandVarsTextChatModerationMode(const QString& tcmm);
    void signalCommandVarsTextChatSpamTriggerCount(const QString& tcstc);
    void signalCommandVarsTextChatSpamDetectionTime(const QString& tcsdt);
    void signalCommandVarsTextChatSpamCoolDownTime(const QString& tcscdt);
    void signalCommandBanListList(QStringList bl);
    void signalCommandReservedSlotsList(QStringList rl);
    void signalCommandMapListList(QStringList ml);
    void signalCommandMapListListRounds(QStringList ml);
    void signalCommandMapListNextLevelIndex(int& mn);
    void signalCommandVarsServerName(const QString& sn);
    void signalCommandVarsServerDescription(const QString& sd);
    void signalCommandVarsBannerUrl(const QString& bu);

signals:
    void refresh();

    void logMessage(const QString &type, const QString &msg);
    void logEvents(const QString &event, const QString &msg);
    void ingameCommands(const QString &player, const QString &cmd);
    void startConnection();
    void gotSalt(const QByteArray &salt);
    void authenticated();
    void playerListChange();

    void eventOnSpawn(const QString &player, const QString &kit);

    void commandServerInfo(QStringList si);
    void commandVarsTextChatModerationMode(const QString &tcmm);
    void commandVarsTextChatSpamTriggerCount(const QString &tcstc);
    void commandVarsTextChatSpamDetectionTime(const QString &tcsdt);
    void commandVarsTextChatSpamCoolDownTime(const QString &tcscdt);
    void commandBanListList(QStringList bl);
    void commandReservedSlotsList(QStringList rl);
    void commandMapListList(QStringList ml);
    void commandMapListListRounds(QStringList ml);
    void commandMapListNextLevelIndex(int &mn);
    void commandVarsServerName(const QString &sn);
    void commandVarsServerDescription(const QString &sd);
    void commandVarsBannerUrl(const QString &bu);

};

class BFBC2Command : public QObject {
    Q_OBJECT

public:
    BFBC2Command(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet, const BFBC2RconPacket& lastSentPacket = BFBC2RconPacket());
    virtual void exec() = 0;

protected:
    BFBC2CommandSignals *mComSignals;
    BFBC2RconPacket mPacket;
    BFBC2RconPacket mLastSentPacket;

};

class BFBC2LoginPlainTextCommand : public BFBC2Command {

public:
    BFBC2LoginPlainTextCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2LoginHashedCommand : public BFBC2Command {

public:
    BFBC2LoginHashedCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet, const BFBC2RconPacket& lastSentPacket);
    void exec();

};

class BFBC2VersionCommand : public BFBC2Command {

public:
    BFBC2VersionCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2EventsEnabledCommand : public BFBC2Command {

public:
    BFBC2EventsEnabledCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2ServerInfoCommand : public BFBC2Command {

public:
    BFBC2ServerInfoCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2AdminListPlayersAllCommand : public BFBC2Command {

public:
    BFBC2AdminListPlayersAllCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet, const BFBC2RconPacket& lastSentPacket, PlayerList &players);
    void exec();

private:
    PlayerList &mPlayers;

};

class BFBC2VarsTextChatModerationModeCommand : public BFBC2Command {

public:
    BFBC2VarsTextChatModerationModeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2VarsTextChatSpamTriggerCountCommand : public BFBC2Command {

public:
    BFBC2VarsTextChatSpamTriggerCountCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2VarsTextChatSpamDetectionTimeCommand : public BFBC2Command {

public:
    BFBC2VarsTextChatSpamDetectionTimeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2VarsTextChatSpamCoolDownTimeCommand : public BFBC2Command {

public:
    BFBC2VarsTextChatSpamCoolDownTimeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2BanListListCommand : public BFBC2Command {

public:
    BFBC2BanListListCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2ReservedSlotsListCommand : public BFBC2Command {

public:
    BFBC2ReservedSlotsListCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2MapListListCommand : public BFBC2Command {

public:
    BFBC2MapListListCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet,const BFBC2RconPacket& lastSentPacket);
    void exec();

};

class BFBC2MapListNextLevelIndexCommand : public BFBC2Command {

public:
    BFBC2MapListNextLevelIndexCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2VarsServerNameCommand : public BFBC2Command {

public:
    BFBC2VarsServerNameCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2VarsServerDescriptionCommand : public BFBC2Command {

public:
    BFBC2VarsServerDescriptionCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2VarsBannerUrlCommand : public BFBC2Command {

public:
    BFBC2VarsBannerUrlCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnJoinCommand : public BFBC2Command {

public:
    BFBC2PlayerOnJoinCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnAuthenticatedCommand : public BFBC2Command {

public:
    BFBC2PlayerOnAuthenticatedCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnLeaveCommand : public BFBC2Command {

public:
    BFBC2PlayerOnLeaveCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnSpawnCommand : public BFBC2Command {

public:
    BFBC2PlayerOnSpawnCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnKillCommand : public BFBC2Command {

public:
    BFBC2PlayerOnKillCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnChatCommand : public BFBC2Command {

public:
    BFBC2PlayerOnChatCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnKickedCommand : public BFBC2Command {

public:
    BFBC2PlayerOnKickedCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnSquadChangeCommand : public BFBC2Command {

public:
    BFBC2PlayerOnSquadChangeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PlayerOnTeamChangeCommand : public BFBC2Command {

public:
    BFBC2PlayerOnTeamChangeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2PunkBusterOnMessageCommand : public BFBC2Command {

public:
    BFBC2PunkBusterOnMessageCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2ServerOnLoadingLevelCommand : public BFBC2Command {

public:
    BFBC2ServerOnLoadingLevelCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2ServerOnLevelStartedCommand : public BFBC2Command {

public:
    BFBC2ServerOnLevelStartedCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2ServerOnRoundOverCommand : public BFBC2Command {

public:
    BFBC2ServerOnRoundOverCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2ServerOnRoundOverPlayersCommand : public BFBC2Command {

public:
    BFBC2ServerOnRoundOverPlayersCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2ServerOnRoundOverTeamScoresCommand : public BFBC2Command {

public:
    BFBC2ServerOnRoundOverTeamScoresCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2UnknownCommand : public BFBC2Command {

public:
    BFBC2UnknownCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket& packet);
    void exec();

};

class BFBC2CommandWarper {

public:
    BFBC2CommandWarper(const QString &command, BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet, const BFBC2RconPacket &lastSentPacket, PlayerList &players);
    void exec();

private:
    BFBC2Command *mCommand;

};

#endif // BFBC2COMMANDS_H
