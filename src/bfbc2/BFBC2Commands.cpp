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

#include "BFBC2Commands.h"

BFBC2CommandSignals::BFBC2CommandSignals(QObject *parent)
{
    Q_UNUSED(parent);
}

void BFBC2CommandSignals::signalRefresh()
{
    emit(refresh());
}

void BFBC2CommandSignals::signalLogMessage(const QString &type, const QString &msg)
{
    emit(logMessage(type, msg));
}

void BFBC2CommandSignals::signalLogEvents(const QString &event, const QString &msg)
{
    emit(logEvents(event, msg));
}

void BFBC2CommandSignals::signalIngameCommands(const QString &player, const QString &cmd)
{
    emit(ingameCommands(player, cmd));
}

void BFBC2CommandSignals::signalStartConnection()
{
    emit(startConnection());
}

void BFBC2CommandSignals::signalGotSalt(const QByteArray &salt)
{
    emit(gotSalt(salt));
}

void BFBC2CommandSignals::signalAuthenticated()
{
    emit(authenticated());
}

void BFBC2CommandSignals::signalPlayerListChange()
{
    emit(playerListChange());
}

void BFBC2CommandSignals::signalCommandServerInfo(QStringList si)
{
    emit(commandServerInfo(si));
}

void BFBC2CommandSignals::signalCommandVarsTextChatModerationMode(const QString &tcmm)
{
    emit(commandVarsTextChatModerationMode(tcmm));
}

void BFBC2CommandSignals::signalCommandVarsTextChatSpamTriggerCount(const QString &tcstc)
{
    emit(commandVarsTextChatSpamTriggerCount(tcstc));
}

void BFBC2CommandSignals::signalCommandVarsTextChatSpamDetectionTime(const QString &tcsdt)
{
    emit(commandVarsTextChatSpamDetectionTime(tcsdt));
}

void BFBC2CommandSignals::signalCommandVarsTextChatSpamCoolDownTime(const QString &tcscdt)
{
    emit(commandVarsTextChatSpamCoolDownTime(tcscdt));
}

void BFBC2CommandSignals::signalCommandBanListList(QStringList bl)
{
    emit(commandBanListList(bl));
}

void BFBC2CommandSignals::signalCommandReservedSlotsList(QStringList rl)
{
    emit(commandReservedSlotsList(rl));
}

void BFBC2CommandSignals::signalCommandMapListList(QStringList ml)
{
    emit(commandMapListList(ml));
}

void BFBC2CommandSignals::signalCommandMapListListRounds(QStringList ml)
{
    emit(commandMapListListRounds(ml));
}

void BFBC2CommandSignals::signalCommandMapListNextLevelIndex(int &mn)
{
    emit(commandMapListNextLevelIndex(mn));
}

void BFBC2CommandSignals::signalCommandVarsServerName(const QString &sn)
{
    emit(commandVarsServerName(sn));
}

void BFBC2CommandSignals::signalCommandVarsServerDescription(const QString &sd)
{
    emit(commandVarsServerDescription(sd));
}

void BFBC2CommandSignals::signalCommandVarsBannerUrl(const QString &bu)
{
    emit(commandVarsBannerUrl(bu));
}

void BFBC2CommandSignals::signalEventOnSpawn(const QString& player, const QString& kit)
{
    emit(eventOnSpawn(player, kit));
}

BFBC2Command::BFBC2Command(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet, const BFBC2RconPacket &lastSentPacket)
{
    mComSignals = comSignals;
    mPacket = packet;
    mLastSentPacket = lastSentPacket;
}

BFBC2LoginPlainTextCommand::BFBC2LoginPlainTextCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2LoginPlainTextCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK") {
        mComSignals->signalLogMessage("info", tr("You have successfully logged in."));
        mComSignals->signalAuthenticated();
    } else if (response == "InvalidPassword") {
        mComSignals->signalLogMessage("error", tr("Invalid password."));
    } else if (response == "PasswordNotSet") {
        mComSignals->signalLogMessage("error", tr("Password not set."));
    } else if (response == "InvalidArguments") {
        mComSignals->signalLogMessage("error", tr("Invalid arguments."));
    }
}

BFBC2LoginHashedCommand::BFBC2LoginHashedCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet, const BFBC2RconPacket &lastSentPacket) : BFBC2Command(comSignals, packet, lastSentPacket)
{
}

void BFBC2LoginHashedCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (mLastSentPacket.getWordCount() == 1) {
        if (response == "OK" && mPacket.getWordCount() == 2) {
            mComSignals->signalLogMessage("info", QString(tr("We got salt: %1")).arg(Qt::escape(mPacket.getWord(1).getContent())));
            QByteArray loginSalt = QByteArray::fromHex(QByteArray(mPacket.getWord(1).getContent()));
            mComSignals->signalGotSalt(loginSalt);
        }
    } else if (mLastSentPacket.getWordCount() == 2) {
        QString response(mPacket.getWord(0).getContent());
        if (response == "OK") {
            mComSignals->signalLogMessage("info", tr("You have successfully logged in."));
            mComSignals->signalAuthenticated();
        } else if (response == "InvalidPasswordHash") {
            mComSignals->signalLogMessage("error", tr("Invalid password."));
        }
    }

    if (response == "PasswordNotSet") {
        mComSignals->signalLogMessage("error", tr("Password not set."));
    } else if (response == "InvalidArguments") {
        mComSignals->signalLogMessage("error", tr("Invalid arguments."));
    }
}

BFBC2VersionCommand::BFBC2VersionCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2VersionCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() == 3) {
        QString version;
        QString versionNumber = Qt::escape(mPacket.getWord(2).getContent());

        QMap<QString, QString> versionMap;
        versionMap.insert("571287", "R21");
        versionMap.insert("581637", "R22");
        versionMap.insert("584642", "R23");
        versionMap.insert("593485", "R24");
        versionMap.insert("602833", "R25");
        versionMap.insert("609063", "R26");
        versionMap.insert("617877", "R27");
        versionMap.insert("621775", "R28");

        if (versionMap.contains(versionNumber)) {
            version = versionMap[versionNumber];
        } else {
            version = versionNumber;
        }
        mComSignals->signalLogMessage("info", QString("<b>%1</b> server version: <b>%2</b>.").arg(Qt::escape(mPacket.getWord(1).getContent()), version));
    } else if (response == "InvalidArguments") {
        mComSignals->signalLogMessage("error", tr("Invalid arguments."));
    }
}

BFBC2EventsEnabledCommand::BFBC2EventsEnabledCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2EventsEnabledCommand::exec()
{
}

BFBC2ServerInfoCommand::BFBC2ServerInfoCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2ServerInfoCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 0) {
        QStringList si;
        for (quint32 i = 1; i < mPacket.getWordCount(); i++) {
            si << mPacket.getWord(i).getContent();
        }
        mComSignals->signalCommandServerInfo(si);
    }
}

BFBC2AdminListPlayersAllCommand::BFBC2AdminListPlayersAllCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet, const BFBC2RconPacket &lastSentPacket, PlayerList &players) : BFBC2Command(comSignals, packet, lastSentPacket), mPlayers(players)
{
}

void BFBC2AdminListPlayersAllCommand::exec()
{
    qDebug() << "LISTPLAYERS!!!";
    qDebug() << QString(mLastSentPacket.getWord(1).getContent());

    if ((mLastSentPacket.getWordCount() > 0) && (QString(mLastSentPacket.getWord(1).getContent()) == "all")) {
        QString response(mPacket.getWord(0).getContent());
        if (response == "OK") {
            qDebug() << "HANDLING PLAYERS!";
            mPlayers.clear();
            PlayerListItem pli;
            quint32 paramcount = QString(mPacket.getWord(1).getContent()).toUInt();
            quint32 playercount = QString(mPacket.getWord(2 + paramcount).getContent()).toUInt();

            for (quint32 i = 0; i < playercount; i++) {
                pli.clear();
                for (quint32 j = 0; j < paramcount; j++) {
                    pli[mPacket.getWord(2 + j).getContent()] = mPacket.getWord(2 + paramcount + 1 + i * paramcount + j).getContent();
                }
                mPlayers.push_back(pli);
            }
            mComSignals->signalPlayerListChange();
        } else if (response == "InvalidArguments") {
            mComSignals->signalLogMessage("error", tr("Invalid arguments."));
        }
    }
}

BFBC2VarsTextChatModerationModeCommand::BFBC2VarsTextChatModerationModeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2VarsTextChatModerationModeCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 1) {
        QString tcmm = Qt::escape(mPacket.getWord(1).getContent());
        mComSignals->signalCommandVarsTextChatModerationMode(tcmm);
    }
}

BFBC2VarsTextChatSpamTriggerCountCommand::BFBC2VarsTextChatSpamTriggerCountCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2VarsTextChatSpamTriggerCountCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 1) {
        QString tcst = Qt::escape(mPacket.getWord(1).getContent());
        mComSignals->signalCommandVarsTextChatSpamTriggerCount(tcst);
    }
}

BFBC2VarsTextChatSpamDetectionTimeCommand::BFBC2VarsTextChatSpamDetectionTimeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2VarsTextChatSpamDetectionTimeCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 1) {
        QString tcsdt = Qt::escape(mPacket.getWord(1).getContent());
        mComSignals->signalCommandVarsTextChatModerationMode(tcsdt);
    }
}

BFBC2VarsTextChatSpamCoolDownTimeCommand::BFBC2VarsTextChatSpamCoolDownTimeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2VarsTextChatSpamCoolDownTimeCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 1) {
        QString tcscdt = Qt::escape(mPacket.getWord(1).getContent());
        mComSignals->signalCommandVarsTextChatModerationMode(tcscdt);
    }
}

BFBC2BanListListCommand::BFBC2BanListListCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2BanListListCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 0) {
        QStringList bl;
        for (quint32 i = 1; i < mPacket.getWordCount(); i++) {
            bl << mPacket.getWord(i).getContent();
        }
        mComSignals->signalCommandBanListList(bl);
    }
}

BFBC2ReservedSlotsListCommand::BFBC2ReservedSlotsListCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2ReservedSlotsListCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 0) {
        QStringList rl;
        for (quint32 i = 1; i < mPacket.getWordCount(); i++) {
            rl << mPacket.getWord(i).getContent();
        }
        mComSignals->signalCommandReservedSlotsList(rl);
    }
}

BFBC2MapListListCommand::BFBC2MapListListCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet, const BFBC2RconPacket &lastSentPacket) : BFBC2Command(comSignals, packet, lastSentPacket)
{
}

void BFBC2MapListListCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 0) {
        if ((mLastSentPacket.getWordCount() > 1) && (QString(mLastSentPacket.getWord(1).getContent()) == "rounds")) {
            QStringList ml;
            for (quint32 i = 1; i < mPacket.getWordCount(); i = i + 2) {
                ml << QString(mPacket.getWord(i).getContent()).toLower() << mPacket.getWord(i + 1).getContent();
            }
            mComSignals->signalCommandMapListListRounds(ml);
        } else {
            QStringList ml;
            for (quint32 i = 1; i < mPacket.getWordCount(); i++) {
                ml << mPacket.getWord(i).getContent();
            }
            mComSignals->signalCommandMapListList(ml);
        }
    }

}


BFBC2MapListNextLevelIndexCommand::BFBC2MapListNextLevelIndexCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2MapListNextLevelIndexCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 1) {
        int mn = Qt::escape(mPacket.getWord(1).getContent()).toInt();
        mComSignals->signalCommandMapListNextLevelIndex(mn);

    }
}

BFBC2VarsServerNameCommand::BFBC2VarsServerNameCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2VarsServerNameCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 1) {
        QString sn = Qt::escape(mPacket.getWord(1).getContent());
        mComSignals->signalCommandVarsServerName(sn);
    }
}

BFBC2VarsServerDescriptionCommand::BFBC2VarsServerDescriptionCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2VarsServerDescriptionCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());

    if (response == "OK" && mPacket.getWordCount() > 1) {
        QString sd = Qt::escape(mPacket.getWord(1).getContent());
        mComSignals->signalCommandVarsServerDescription(sd);
    }
}

BFBC2VarsBannerUrlCommand::BFBC2VarsBannerUrlCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2VarsBannerUrlCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());
    if (response == "OK" && mPacket.getWordCount() > 1) {
        QString bu = Qt::escape(mPacket.getWord(1).getContent());
        mComSignals->signalCommandVarsBannerUrl(bu);
    }
}

BFBC2PlayerOnJoinCommand::BFBC2PlayerOnJoinCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnJoinCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Player <b>%1</b> has joined the game.")).arg(Qt::escape(mPacket.getWord(1).getContent())));
    mComSignals->signalRefresh();
}

BFBC2PlayerOnAuthenticatedCommand::BFBC2PlayerOnAuthenticatedCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnAuthenticatedCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Player <b>%1</b> has just authenticated, and has the GUID: <b>%2</b>.")).arg(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent())));
}

BFBC2PlayerOnLeaveCommand::BFBC2PlayerOnLeaveCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnLeaveCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Player <b>%1</b> has left the game.")).arg(Qt::escape(mPacket.getWord(1).getContent())));
    mComSignals->signalRefresh();
}

BFBC2PlayerOnSpawnCommand::BFBC2PlayerOnSpawnCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnSpawnCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Player <b>%1</b> has spawned, with kit <b>%2</b> and with <b>%3</b>, <b>%4</b> and <b>%5</b> selected.")).arg(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent()), Qt::escape(mPacket.getWord(3).getContent()), Qt::escape(mPacket.getWord(4).getContent()), Qt::escape(mPacket.getWord(5).getContent())));
    mComSignals->signalEventOnSpawn(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent()) /*, Qt::escape(mPacket.getWord(3).getContent()), Qt::escape(mPacket.getWord(4).getContent())*/);
}

BFBC2PlayerOnKillCommand::BFBC2PlayerOnKillCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnKillCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Player <b>%1</b> has killed player <b>%2</b> with <b>%3</b>")).arg(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent()), Qt::escape(mPacket.getWord(3).getContent())));
    mComSignals->signalRefresh();
    mComSignals->signalLogEvents("Event", QString(Qt::escape(mPacket.getWord(1).getContent()) + Qt::escape(mPacket.getWord(2).getContent()) + Qt::escape(mPacket.getWord(3).getContent())));
}

BFBC2PlayerOnChatCommand::BFBC2PlayerOnChatCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnChatCommand::exec()
{
    mComSignals->signalLogMessage("chat", QString(tr("<b>%1</b>: %2")).arg(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent())));
    mComSignals->signalIngameCommands(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent()));
}

BFBC2PlayerOnKickedCommand::BFBC2PlayerOnKickedCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnKickedCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Player <b>%1</b> has been kicked from the game, reason: <b>%2</b>.")).arg(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent())));
    mComSignals->signalRefresh();
}

BFBC2PlayerOnSquadChangeCommand::BFBC2PlayerOnSquadChangeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnSquadChangeCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Player <b>%1</b> has changed squad to <b>%2</b>.")).arg(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent())));
    mComSignals->signalRefresh();
}

BFBC2PlayerOnTeamChangeCommand::BFBC2PlayerOnTeamChangeCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PlayerOnTeamChangeCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Player <b>%1</b> has changed team to <b>%2</b>.")).arg(Qt::escape(mPacket.getWord(1).getContent()), Qt::escape(mPacket.getWord(2).getContent())));
    mComSignals->signalRefresh();
}

BFBC2PunkBusterOnMessageCommand::BFBC2PunkBusterOnMessageCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2PunkBusterOnMessageCommand::exec()
{
    mComSignals->signalLogMessage("pb", Qt::escape(mPacket.getWord(1).getContent()));
}

BFBC2ServerOnLoadingLevelCommand::BFBC2ServerOnLoadingLevelCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2ServerOnLoadingLevelCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Loading level: <b>%1</b>")).arg(Qt::escape(mPacket.getWord(1).getContent())));
}

BFBC2ServerOnLevelStartedCommand::BFBC2ServerOnLevelStartedCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2ServerOnLevelStartedCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("Level started")));
}

BFBC2ServerOnRoundOverCommand::BFBC2ServerOnRoundOverCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2ServerOnRoundOverCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("The round has just ended, and <b>%1</b> won")).arg(Qt::escape(mPacket.getWord(1).getContent())));
}

BFBC2ServerOnRoundOverPlayersCommand::BFBC2ServerOnRoundOverPlayersCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2ServerOnRoundOverPlayersCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("The round has just ended, and <b>%1</b> is the final detailed player stats")).arg(Qt::escape(mPacket.getWord(1).getContent())));
}

BFBC2ServerOnRoundOverTeamScoresCommand::BFBC2ServerOnRoundOverTeamScoresCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2ServerOnRoundOverTeamScoresCommand::exec()
{
    mComSignals->signalLogMessage("info", QString(tr("The round has just ended, and <b>%1</b> is the final ticket/kill/life count for each team")).arg(Qt::escape(mPacket.getWord(1).getContent())));
}

BFBC2UnknownCommand::BFBC2UnknownCommand(BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet) : BFBC2Command(comSignals, packet)
{
}

void BFBC2UnknownCommand::exec()
{
    QString response(mPacket.getWord(0).getContent());
    if (response == "UnknownCommand") {
        mComSignals->signalLogMessage("error", tr("Unknown command."));
    }
}

BFBC2CommandWarper::BFBC2CommandWarper(const QString &command, BFBC2CommandSignals *comSignals, const BFBC2RconPacket &packet, const BFBC2RconPacket &lastSentPacket, PlayerList &players)
{
    if (command == "login.plainText") {
        mCommand = new BFBC2LoginPlainTextCommand(comSignals, packet);
    } else if (command == "login.hashed") {
        mCommand = new BFBC2LoginHashedCommand(comSignals, packet, lastSentPacket);
    } else if (command == "version") {
        mCommand = new BFBC2VersionCommand(comSignals, packet);
    } else if (command == "eventsEnabled") {
        mCommand = new BFBC2EventsEnabledCommand(comSignals, packet);
    } else if (command == "serverInfo") {
        mCommand = new BFBC2ServerInfoCommand(comSignals, packet);
    } else if (command == "admin.listPlayers") {
        mCommand = new BFBC2AdminListPlayersAllCommand(comSignals, packet, lastSentPacket, players);
    } else if (command == "vars.textChatModerationMode") {
        mCommand = new BFBC2VarsTextChatModerationModeCommand(comSignals, packet);
    } else if (command == "vars.textChatSpamTriggerCount") {
        mCommand = new BFBC2VarsTextChatSpamTriggerCountCommand(comSignals, packet);
    } else if (command == "vars.textChatSpamDetectionTime") {
        mCommand = new BFBC2VarsTextChatSpamDetectionTimeCommand(comSignals, packet);
    } else if (command == "vars.textChatSpamCoolDownTime") {
        mCommand = new BFBC2VarsTextChatSpamCoolDownTimeCommand(comSignals, packet);
    } else if (command == "banList.list") {
        mCommand = new BFBC2BanListListCommand(comSignals, packet);
    } else if (command == "reservedSlots.list") {
        mCommand = new BFBC2ReservedSlotsListCommand(comSignals, packet);
    } else if (command == "mapList.list") {
        mCommand = new BFBC2MapListListCommand(comSignals, packet, lastSentPacket);
    } else if (command == "mapList.nextLevelIndex") {
        mCommand = new BFBC2MapListNextLevelIndexCommand(comSignals, packet);
    } else if (command == "vars.serverName") {
        mCommand = new BFBC2VarsServerNameCommand(comSignals, packet);
    } else if (command == "vars.serverDescription") {
        mCommand = new BFBC2VarsServerDescriptionCommand(comSignals, packet);
    } else if (command == "vars.bannerUrl") {
        mCommand = new BFBC2VarsBannerUrlCommand(comSignals, packet);
    } else if (command == "player.onJoin") {
        mCommand = new BFBC2PlayerOnJoinCommand(comSignals, packet);
    } else if (command == "player.onAuthenticated") {
        mCommand = new BFBC2PlayerOnAuthenticatedCommand(comSignals, packet);
    } else if (command == "player.onLeave") {
        mCommand = new BFBC2PlayerOnLeaveCommand(comSignals, packet);
    } else if (command == "player.onSpawn") {
        mCommand = new BFBC2PlayerOnSpawnCommand(comSignals, packet);
    } else if (command == "player.onKill") {
        mCommand = new BFBC2PlayerOnKillCommand(comSignals, packet);
    } else if (command == "player.onChat") {
        mCommand = new BFBC2PlayerOnChatCommand(comSignals, packet);
    } else if (command == "player.onKicked") {
        mCommand = new BFBC2PlayerOnKickedCommand(comSignals, packet);
    } else if (command == "player.onSquadChange") {
        mCommand = new BFBC2PlayerOnSquadChangeCommand(comSignals, packet);
    } else if (command == "player.onTeamChange") {
        mCommand = new BFBC2PlayerOnTeamChangeCommand(comSignals, packet);
    } else if (command == "punkBuster.onMessage") {
        mCommand = new BFBC2PunkBusterOnMessageCommand(comSignals, packet);
    } else if (command == "server.onLoadingLevel") {
        mCommand = new BFBC2ServerOnLoadingLevelCommand(comSignals, packet);
    } else if (command == "server.onLevelStarted") {
        mCommand = new BFBC2ServerOnLevelStartedCommand(comSignals, packet);
    } else if (command == "server.onRoundOver") {
        mCommand = new BFBC2ServerOnRoundOverCommand(comSignals, packet);
    } else if (command == "server.onRoundOverPlayers") {
        mCommand = new BFBC2ServerOnRoundOverPlayersCommand(comSignals, packet);
    } else if (command == "server.onRoundOverTeamScores") {
        mCommand = new BFBC2ServerOnRoundOverTeamScoresCommand(comSignals, packet);
    } else {
        mCommand = new BFBC2UnknownCommand(comSignals, packet);
    }
}

void BFBC2CommandWarper::exec()
{
    mCommand->exec();
}
