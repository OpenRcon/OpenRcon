#include "BFBC2CommandHandler.h"

BFBC2CommandHandler::BFBC2CommandHandler(QObject *parent) : FrostbiteCommandHandler(parent)
{

}

BFBC2CommandHandler::~BFBC2CommandHandler()
{

}

void BFBC2CommandHandler::exec(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &players)
{
    if (command == "login.plainText") {
        commandLoginPlainText(packet);
    } else if (command == "login.hashed") {
        commandLoginHashed(packet, lastSentPacket);
    } else if (command == "version") {
        commandVersion(packet);
    } else if (command == "eventsEnabled") {
        commandEventsEnabled(packet);
    } else if (command == "serverInfo") {
        commandServerInfo(packet);
    } else if (command == "admin.listPlayers") {
        commandAdminListPlayersAll(packet, lastSentPacket, players);
    } else if (command == "vars.textChatModerationMode") {
        commandVarsTextChatModerationMode(packet);
    } else if (command == "vars.textChatSpamTriggerCount") {
        commandVarsTextChatSpamTriggerCount(packet);
    } else if (command == "vars.textChatSpamDetectionTime") {
        commandVarsTextChatSpamDetectionTime(packet);
    } else if (command == "vars.textChatSpamCoolDownTime") {
        commandVarsTextChatSpamCoolDownTime(packet);
    } else if (command == "banList.list") {
        commandBanListList(packet);
    } else if (command == "reservedSlots.list") {
        commandReservedSlotsList(packet);
    } else if (command == "mapList.list") {
        commandMapListList(packet, lastSentPacket);
    } else if (command == "mapList.nextLevelIndex") {
        commandMapListNextLevelIndex(packet);
    } else if (command == "vars.serverName") {
        commandVarsServerName(packet);
    } else if (command == "vars.serverDescription") {
        commandVarsServerDescription(packet);
    } else if (command == "vars.bannerUrl") {
        commandVarsBannerUrl(packet);
    } else if (command == "player.onJoin") {
        commandPlayerOnJoin(packet);
    } else if (command == "player.onAuthenticated") {
        commandPlayerOnAuthenticated(packet);
    } else if (command == "player.onLeave") {
        commandPlayerOnLeave(packet);
    } else if (command == "player.onSpawn") {
        commandPlayerOnSpawn(packet);
    } else if (command == "player.onKill") {
        commandPlayerOnKill(packet);
    } else if (command == "player.onChat") {
        commandPlayerOnChat(packet);
    } else if (command == "player.onKicked") {
        commandPlayerOnKicked(packet);
    } else if (command == "player.onSquadChange") {
        commandPlayerOnSquadChange(packet);
    } else if (command == "player.onTeamChange") {
        commandPlayerOnTeamChange(packet);
    } else if (command == "punkBuster.onMessage") {
        commandPunkBusterOnMessage(packet);
    } else if (command == "server.onLoadingLevel") {
        commandServerOnLoadingLevel(packet);
    } else if (command == "server.onLevelStarted") {
        commandServerOnLevelStarted(packet);
    } else if (command == "server.onRoundOver") {
        commandServerOnRoundOver(packet);
    } else if (command == "server.onRoundOverPlayers") {
        commandServerOnRoundOverPlayers(packet);
    } else if (command == "server.onRoundOverTeamScores") {
        commandServerOnRoundOverTeamScores(packet);
    } else {
        commandUnknown(packet);
    }

    qDebug() << "BFBC2CommandHandler::exec()";
}

void BFBC2CommandHandler::startConnection()
{
    emit(onStartConnection());
}

void BFBC2CommandHandler::commandLoginPlainText(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK") {
        emit(onLogMessage(0, tr("You have successfully logged in.")));
        emit(onAuthenticated());
    } else if (response == "InvalidPassword") {
        emit(onLogMessage(1, tr("Invalid password.")));
    } else if (response == "PasswordNotSet") {
        emit(onLogMessage(1, tr("Password not set.")));
    } else if (response == "InvalidArguments") {
        emit(onLogMessage(1, tr("Invalid arguments.")));
    }
}

void BFBC2CommandHandler::commandLoginHashed(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response(packet.getWord(0).getContent());

    if (lastSentPacket.getWordCount() == 1) {
        if (response == "OK" && packet.getWordCount() == 2) {
            emit(onLogMessage(0, QString(tr("We got salt: %1")).arg(packet.getWord(1).getContent()).toHtmlEscaped()));
            QByteArray loginSalt = QByteArray::fromHex(QByteArray(packet.getWord(1).getContent()));
            emit(onGotSalt(loginSalt));
        }
    } else if (lastSentPacket.getWordCount() == 2) {
        QString response(packet.getWord(0).getContent());

        if (response == "OK") {
            emit(onLogMessage(0, tr("You have successfully logged in.")));
            emit(onAuthenticated());
        } else if (response == "InvalidPasswordHash") {
            emit(onLogMessage(1, tr("Invalid password.")));
        }
    }

    if (response == "PasswordNotSet") {
        emit(onLogMessage(1, tr("Password not set.")));
    } else if (response == "InvalidArguments") {
        emit(onLogMessage(1, tr("Invalid arguments.")));
    }
}

void BFBC2CommandHandler::commandVersion(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() == 3) {
        QString version = packet.getWord(2).getContent();
        QString release;

        QMap<QString, QString> versionMap;
        versionMap.insert("571287", "R21");
        versionMap.insert("581637", "R22");
        versionMap.insert("584642", "R23");
        versionMap.insert("593485", "R24");
        versionMap.insert("602833", "R25");
        versionMap.insert("609063", "R26");
        versionMap.insert("617877", "R27");
        versionMap.insert("621775", "R28");
        versionMap.insert("638140", "R30");
        versionMap.insert("720174", "R32");
        versionMap.insert("851434", "R34");

        if (versionMap.contains(version)) {
            release = versionMap.value(version);
        } else {
            release = version;
        }

        emit(onLogMessage(0, QString("<b>%1</b> server version: <b>%2</b>.").arg(packet.getWord(1).getContent(), release)));
    } else if (response == "InvalidArguments") {
        emit(onLogMessage(1, "Invalid arguments."));
    }
}

void BFBC2CommandHandler::commandEventsEnabled(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);
}

void BFBC2CommandHandler::commandServerInfo(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList si;

        for (quint32 i = 1; i < packet.getWordCount(); i++) {
            si << packet.getWord(i).getContent();
        }

        emit(onCommandServerInfo(si));
    }
}

void BFBC2CommandHandler::commandAdminListPlayersAll(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket, PlayerList &players)
{
    qDebug() << "LISTPLAYERS!!!";
    qDebug() << QString(lastSentPacket.getWord(1).getContent());

    if ((lastSentPacket.getWordCount() > 0) && (QString(lastSentPacket.getWord(1).getContent()) == "all")) {
        QString response(packet.getWord(0).getContent());
        if (response == "OK") {
            qDebug() << "HANDLING PLAYERS!";
            players.clear();
            PlayerListItem pli;
            quint32 paramcount = QString(packet.getWord(1).getContent()).toUInt();
            quint32 playercount = QString(packet.getWord(2 + paramcount).getContent()).toUInt();

            for (quint32 i = 0; i < playercount; i++) {
                pli.clear();
                for (quint32 j = 0; j < paramcount; j++) {
                    pli[packet.getWord(2 + j).getContent()] = packet.getWord(2 + paramcount + 1 + i * paramcount + j).getContent();
                }

                players.push_back(pli);
            }
            emit(onPlayerListChange());
        } else if (response == "InvalidArguments") {
            emit(onLogMessage(1, tr("Invalid arguments.")));
        }
    }
}

void BFBC2CommandHandler::commandVarsTextChatModerationMode(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString tcmm = packet.getWord(1).getContent();
        emit(onCommandVarsTextChatModerationMode(tcmm));
    }
}

void BFBC2CommandHandler::commandVarsTextChatSpamTriggerCount(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString tcst = packet.getWord(1).getContent();
        emit(onCommandVarsTextChatSpamTriggerCount(tcst));
    }
}

void BFBC2CommandHandler::commandVarsTextChatSpamDetectionTime(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString tcsdt = QString(packet.getWord(1).getContent()).toHtmlEscaped();
        emit(onCommandVarsTextChatModerationMode(tcsdt));
    }
}

void BFBC2CommandHandler::commandVarsTextChatSpamCoolDownTime(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString tcscdt = QString(packet.getWord(1).getContent()).toHtmlEscaped();
        emit(onCommandVarsTextChatModerationMode(tcscdt));
    }
}

void BFBC2CommandHandler::commandBanListList(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList bl;
        for (quint32 i = 1; i < packet.getWordCount(); i++) {
            bl << packet.getWord(i).getContent();
        }
        emit(onCommandBanListList(bl));
    }
}

void BFBC2CommandHandler::commandReservedSlotsList(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        QStringList rl;
        for (quint32 i = 1; i < packet.getWordCount(); i++) {
            rl << packet.getWord(i).getContent();
        }
        emit(onCommandReservedSlotsList(rl));
    }
}

void BFBC2CommandHandler::commandMapListList(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 0) {
        if ((lastSentPacket.getWordCount() > 1) && (QString(lastSentPacket.getWord(1).getContent()) == "rounds")) {
            QStringList ml;
            for (quint32 i = 1; i < packet.getWordCount(); i = i + 2) {
                ml << QString(packet.getWord(i).getContent()).toLower() << packet.getWord(i + 1).getContent();
            }
            emit(onCommandMapListListRounds(ml));
        } else {
            QStringList ml;
            for (quint32 i = 1; i < packet.getWordCount(); i++) {
                ml << packet.getWord(i).getContent();
            }
            emit(onCommandMapListList(ml));
        }
    }

}

void BFBC2CommandHandler::commandMapListNextLevelIndex(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        int mn = QString(packet.getWord(1).getContent()).toHtmlEscaped().toInt();

        emit(onCommandMapListNextLevelIndex(mn));
    }
}

void BFBC2CommandHandler::commandVarsServerName(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString sn = packet.getWord(1).getContent();
        emit(onCommandVarsServerName(sn));
    }
}

void BFBC2CommandHandler::commandVarsServerDescription(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString sd = packet.getWord(1).getContent();
        emit(onCommandVarsServerDescription(sd));
    }
}

void BFBC2CommandHandler::commandVarsBannerUrl(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "OK" && packet.getWordCount() > 1) {
        QString bu = packet.getWord(1).getContent();
        emit(onCommandVarsBannerUrl(bu));
    }
}

void BFBC2CommandHandler::commandPlayerOnJoin(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Player <b>%1</b> has joined the game.")).arg(packet.getWord(1).getContent())));
    emit(onRefresh());
}

void BFBC2CommandHandler::commandPlayerOnAuthenticated(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Player <b>%1</b> has just authenticated, and has the GUID: <b>%2</b>.")).arg(packet.getWord(1).getContent(), packet.getWord(2).getContent())));
}

void BFBC2CommandHandler::commandPlayerOnLeave(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Player <b>%1</b> has left the game.")).arg(packet.getWord(1).getContent())));
    emit(onRefresh());
}

void BFBC2CommandHandler::commandPlayerOnSpawn(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Player <b>%1</b> has spawned, with kit <b>%2</b> and with <b>%3</b>, <b>%4</b> and <b>%5</b> selected.")).arg(packet.getWord(1).getContent(), packet.getWord(2).getContent(), packet.getWord(3).getContent(), packet.getWord(4).getContent(), packet.getWord(5).getContent())));
    emit(onEventOnSpawn(packet.getWord(1).getContent(), packet.getWord(2).getContent())); /*, Qt::escape(packet.getWord(3).getContent()), Qt::escape(packet.getWord(4).getContent())*/

}

void BFBC2CommandHandler::commandPlayerOnKill(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Player <b>%1</b> has killed player <b>%2</b> with <b>%3</b>")).arg(packet.getWord(1).getContent(), packet.getWord(2).getContent(), packet.getWord(3).getContent())));
    emit(onRefresh());
    emit(onLogEvent("Event", QString("%1 %2 %3").arg(packet.getWord(1).getContent(), packet.getWord(2).getContent(), packet.getWord(3).getContent()))); // TODO: Better way to do this?
}

void BFBC2CommandHandler::commandPlayerOnChat(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(4, QString(tr("<b>%1</b>: %2")).arg(packet.getWord(1).getContent(), packet.getWord(2).getContent())));
    emit(onIngameCommands(packet.getWord(1).getContent(), packet.getWord(2).getContent()));
}

void BFBC2CommandHandler::commandPlayerOnKicked(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Player <b>%1</b> has been kicked from the game, reason: <b>%2</b>.")).arg(packet.getWord(1).getContent(), packet.getWord(2).getContent())));
    emit(onRefresh());
}

void BFBC2CommandHandler::commandPlayerOnSquadChange(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Player <b>%1</b> has changed squad to <b>%2</b>.")).arg(packet.getWord(1).getContent(), packet.getWord(2).getContent())));
    emit(onRefresh());
}

void BFBC2CommandHandler::commandPlayerOnTeamChange(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Player <b>%1</b> has changed team to <b>%2</b>.")).arg(packet.getWord(1).getContent(), packet.getWord(2).getContent())));
    emit(onRefresh());
}

void BFBC2CommandHandler::commandPunkBusterOnMessage(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(5, packet.getWord(1).getContent()));
}

void BFBC2CommandHandler::commandServerOnLoadingLevel(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("Loading level: <b>%1</b>")).arg(packet.getWord(1).getContent())));
}

void BFBC2CommandHandler::commandServerOnLevelStarted(const FrostbiteRconPacket &packet)
{
    Q_UNUSED(packet);

    emit(onLogMessage(0, QString(tr("Level started"))));
}

void BFBC2CommandHandler::commandServerOnRoundOver(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("The round has just ended, and <b>%1</b> won")).arg(packet.getWord(1).getContent())));
}

void BFBC2CommandHandler::commandServerOnRoundOverPlayers(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("The round has just ended, and <b>%1</b> is the final detailed player stats")).arg(packet.getWord(1).getContent())));
}

void BFBC2CommandHandler::commandServerOnRoundOverTeamScores(const FrostbiteRconPacket &packet)
{
    emit(onLogMessage(0, QString(tr("The round has just ended, and <b>%1</b> is the final ticket/kill/life count for each team")).arg(packet.getWord(1).getContent())));
}

void BFBC2CommandHandler::commandUnknown(const FrostbiteRconPacket &packet)
{
    QString response(packet.getWord(0).getContent());

    if (response == "UnknownCommand") {
        emit(onLogMessage(1, tr("Unknown command.")));
    }
}
