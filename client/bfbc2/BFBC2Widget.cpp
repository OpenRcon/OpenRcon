/*
 * Copyright (C) 2014 The OpenRcon Project.
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

#include <QMenu>
#include <QCompleter>
#include <QDateTime>
#include <QMessageBox>
#include <QInputDialog>
#include <QTimer>

#include "ui_BFBC2Widget.h"
#include "BFBC2Widget.h"
#include "FrostbiteUtils.h"
#include "BFBC2LevelEntry.h"
#include "GameModeEntry.h"
#include "BFBC2LevelDictionary.h"

BFBC2Widget::BFBC2Widget(ServerEntry *serverEntry) : BFBC2(serverEntry), ui(new Ui::BFBC2Widget)
{
    ui->setupUi(this);

    ui->label_op_so_bannerImage->hide();
    ui->spinBox_ch_duration->hide();

    action_pl_sendmessage = new QAction(tr("Send message"), this);
    action_pl_textchatmoderation_muted = new QAction(tr("Muted"), this);
    action_pl_textchatmoderation_normal = new QAction(tr("Normal"), this);
    action_pl_textchatmoderation_voice = new QAction(tr("Voice"), this);
    action_pl_textchatmoderation_admin = new QAction(tr("Admin"), this);
    action_pl_kill = new QAction(tr("Kill"), this);
    action_pl_kick_custom = new QAction(tr("Custom"), this);
    action_pl_ban_byname = new QAction(tr("By name"), this);
    action_pl_reservedslots = new QAction(tr("Reserved Slots"), this);
    action_pl_admin = new QAction(tr("Admin"), this);
    action_pl_move = new QAction("Switch Sides", this);

    action_bl_remove = new QAction(tr("Remove"), this);
    action_rs_remove = new QAction(tr("Remove"), this);
    action_ic_remove = new QAction(tr("Remove"), this);

    menu_pl = new QMenu(tr("Players"), this);
    menu_pl->addAction(action_pl_sendmessage);
    menu_pl_textchatmoderation = new QMenu(tr("Text Chat Moderation"), this);
    menu_pl_textchatmoderation->addAction(action_pl_textchatmoderation_muted);
    menu_pl_textchatmoderation->addAction(action_pl_textchatmoderation_normal);
    menu_pl_textchatmoderation->addAction(action_pl_textchatmoderation_voice);
    menu_pl_textchatmoderation->addAction(action_pl_textchatmoderation_admin);
    menu_pl->addMenu(menu_pl_textchatmoderation);
    menu_pl->addAction(action_pl_kill);
    menu_pl_move = new QMenu(tr("Move"), this);
    menu_pl_move->addAction(action_pl_move);
    menu_pl->addMenu(menu_pl_move);
    menu_pl_kick = new QMenu(tr("Kick"), this);
    menu_pl_kick->addAction(action_pl_kick_custom);
    menu_pl->addMenu(menu_pl_kick);
    menu_pl_ban = new QMenu(tr("Ban"), this);
    menu_pl_ban->addAction(action_pl_ban_byname);
    menu_pl->addMenu(menu_pl_ban);
    menu_pl->addAction(action_pl_reservedslots);
    menu_pl->addAction(action_pl_admin);

    menu_bl = new QMenu(tr("Banlist"), this);
    menu_bl->addAction(action_bl_remove);

    menu_rs = new QMenu(tr("Reserved Slots"), this);
    menu_rs->addAction(action_rs_remove);

    menu_ic = new QMenu(tr("Ingame Commands"), this);
    menu_ic->addAction(action_ic_remove);

    completer = new QCompleter(commandList, this);
    ui->lineEdit_co_co->setCompleter(completer);

    /* Connection */
    connect(m_connection, &Connection::onConnected,    this, &BFBC2Widget::onConnected);
    connect(m_connection, &Connection::onDisconnected, this, &BFBC2Widget::onDisconnected);

    /* Events */
    connect(m_connection, &Connection::onDataSentEvent,     this, &BFBC2Widget::onDataSentEvent);
    connect(m_connection, &Connection::onDataReceivedEvent, this, &BFBC2Widget::onDataReceivedEvent);

    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerJoinEvent, this, &BFBC2Widget::onPlayerJoinEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerAuthenticatedEvent, this, &BFBC2Widget::onPlayerAuthenticatedEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerLeaveEvent, this, &BFBC2Widget::onPlayerLeaveEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerSpawnEvent, this, &BFBC2Widget::onPlayerSpawnEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerKillEvent, this, &BFBC2Widget::onPlayerKillEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerChatEvent, this, &BFBC2Widget::onPlayerChatEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerKickedEvent, this, &BFBC2Widget::onPlayerKickedEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerSquadChangeEvent, this, &BFBC2Widget::onPlayerSquadChangeEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onPlayerTeamChangeEvent, this, &BFBC2Widget::onPlayerTeamChangeEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onServerLoadingLevelEvent, this, &BFBC2Widget::onServerLoadingLevelEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onServerLevelStartedEvent, this, &BFBC2Widget::onServerLevelStartedEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onServerRoundOverEvent, this, &BFBC2Widget::onServerRoundOverEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onServerRoundOverPlayersEvent, this, &BFBC2Widget::onServerRoundOverPlayersEvent);
    connect(m_commandHandler, &BFBC2CommandHandler::onServerRoundOverTeamScoresEvent, this, &BFBC2Widget::onServerRoundOverTeamScoresEvent);

    /* Commands */
    // Misc
    connect(m_commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &BFBC2Widget::onLoginHashedCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onServerInfoCommand,                                                            this, &BFBC2Widget::onServerInfoCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onAdminListPlayersCommand,                                                      this, &BFBC2Widget::onAdminListPlayersCommand);

    connect(m_commandHandler, &BFBC2CommandHandler::onVarsServerNameCommand, this, &BFBC2Widget::onVarsServerNameCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onVarsServerDescriptionCommand, this, &BFBC2Widget::onVarsServerDescriptionCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onVarsBannerUrlCommand, this, &BFBC2Widget::onVarsBannerUrlCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onVarsTextChatModerationModeCommand, this, &BFBC2Widget::onVarsTextChatModerationModeCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onVarsTextChatSpamTriggerCountCommand, this, &BFBC2Widget::onVarsTextChatSpamTriggerCountCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onVarsTextChatSpamDetectionTimeCommand, this, &BFBC2Widget::onVarsTextChatSpamDetectionTimeCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onVarsTextChatSpamCoolDownTimeCommand, this, &BFBC2Widget::onVarsTextChatSpamCoolDownTimeCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onMapListListCommand, this, &BFBC2Widget::onMapListListCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onMapListNextLevelIndexCommand, this, &BFBC2Widget::onMapListNextLevelIndexCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onBanListListCommand, this, &BFBC2Widget::onBanListListCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onReservedSlotsListCommand, this, &BFBC2Widget::onReservedSlotsListCommand);
    connect(m_commandHandler, &BFBC2CommandHandler::onVarsIdleTimeoutCommand, this, &BFBC2Widget::onVarsIdleTimeoutCommand);

    /* User Interface */

    /* Options Tab */

    /* Server Options */
    connect(ui->lineEdit_op_so_serverName,        &QLineEdit::editingFinished, this, &BFBC2Widget::lineEdit_op_so_serverName_editingFinished);
    connect(ui->lineEdit_op_so_serverDescription, &QLineEdit::editingFinished, this, &BFBC2Widget::lineEdit_op_so_serverDescription_editingFinished);
    connect(ui->lineEdit_op_so_bannerUrl,         &QLineEdit::editingFinished, this, &BFBC2Widget::lineEdit_op_so_bannerUrl_editingFinished);

    /* Game Options */
    connect(ui->checkBox_op_go_3dSpotting,                &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_3dSpotting_clicked);
    connect(ui->checkBox_op_go_crossHair,                 &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_crossHair_clicked);
    connect(ui->checkBox_op_go_friendlyFire,              &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_friendlyFire_clicked);
    connect(ui->checkBox_op_go_hardcore,                  &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_hardcore_clicked);
    connect(ui->checkBox_op_go_killCam,                   &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_killCam_clicked);
    connect(ui->checkBox_op_go_miniMap,                   &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_miniMap_clicked);
    connect(ui->checkBox_op_go_miniMapSpotting,           &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_miniMapSpotting_clicked);
    connect(ui->checkBox_op_go_teamBalance,               &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_teamBalance_clicked);
    connect(ui->checkBox_op_go_thirdPersonVehicleCameras, &QCheckBox::clicked, this, &BFBC2Widget::checkbox_op_go_thirdPersonVehicleCameras_clicked);

    // Old.
    connect(ui->treeWidget_pl_players, &QTreeWidget::customContextMenuRequested, this, &BFBC2Widget::treeWidget_pl_players_customContextMenuRequested);
//    connect(ui->treeWidget_pl_players, &QTreeWidget::dragEvent, this, &BFBC2Widget::blockPlayerList);
//    connect(ui->treeWidget_pl_players, &QTreeWidget::dropEvent, this, &BFBC2Widget::slotChangePlayerTeam);
//    connect(ui->treeWidget_pl_players, &QTreeWidget::refresh, this, &BFBC2Widget::refreshPlayerList);

    connect(action_pl_sendmessage,               &QAction::triggered, this, &BFBC2Widget::action_pl_sendmessage_triggered);
    connect(action_pl_textchatmoderation_muted,  &QAction::triggered, this, &BFBC2Widget::action_pl_textchatmoderation_muted_triggered);
    connect(action_pl_textchatmoderation_normal, &QAction::triggered, this, &BFBC2Widget::action_pl_textchatmoderation_normal_triggered);
    connect(action_pl_textchatmoderation_voice,  &QAction::triggered, this, &BFBC2Widget::action_pl_textchatmoderation_voice_triggered);
    connect(action_pl_textchatmoderation_admin,  &QAction::triggered, this, &BFBC2Widget::action_pl_textchatmoderation_admin_triggered);
    connect(action_pl_kill,                      &QAction::triggered, this, &BFBC2Widget::action_pl_kill_triggered);
    connect(action_pl_kick_custom,               &QAction::triggered, this, &BFBC2Widget::action_pl_kick_custom_triggered);
    connect(action_pl_ban_byname,                &QAction::triggered, this, &BFBC2Widget::action_pl_ban_byname_triggered);
    connect(action_pl_reservedslots,             &QAction::triggered, this, &BFBC2Widget::action_pl_reservedslots_triggered);
    connect(action_pl_move,                      &QAction::triggered, this, &BFBC2Widget::slotMovePlayerTeam);


    connect(ui->listWidget_ml_avaliablemaps, &QListWidget::currentItemChanged,                                       this, &BFBC2Widget::listWidget_ml_avaliablemaps_currentItemChanged);
    connect(ui->listWidget_ml_currentmaps,   &QListWidget::currentItemChanged,                                       this, &BFBC2Widget::listWidget_ml_currentmaps_currentItemChanged);
    connect(ui->listWidget_ml_currentmaps,   &QListWidget::itemClicked,                                              this, &BFBC2Widget::listWidget_ml_currentmaps_currentItemChanged);
    connect(ui->comboBox_ml_gamemode,        static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &BFBC2Widget::comboBox_ml_gamemode_currentIndexChanged);
//    connect(ui->listWidget_ml_currentmaps,   &QListWidget::dropEvent,                                                this, &BFBC2Widget::slotAddMapToServer);
//    connect(ui->listWidget_ml_avaliablemaps, &QListWidget::dropEvent,                                                this, &BFBC2Widget::slotRemoveMapFromServer);
//    connect(ui->listWidget_ml_currentmaps,   &QListWidget::sameDropEvent,                                            this, &BFBC2Widget::playerListUpdate);

    connect(ui->tableWidget_bl, &QTableWidget::customContextMenuRequested, this, &BFBC2Widget::listWidget_bl_customContextMenuRequested);
    connect(action_bl_remove,   &QAction::triggered,                       this, &BFBC2Widget::action_bl_remove_triggered);

    connect(ui->lineEdit_ch,      &QLineEdit::returnPressed,                                              this, &BFBC2Widget::pushButton_ch_send_clicked);
    connect(ui->comboBox_ch_type, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &BFBC2Widget::comboBox_ch_type_currentIndexChanged);

    connect(action_rs_remove,       &QAction::triggered,                      this, &BFBC2Widget::action_rs_remove_triggered);
    connect(ui->listWidget_rs,      &QListWidget::customContextMenuRequested, this, &BFBC2Widget::listWidget_rs_customContextMenuRequested);
    connect(ui->lineEdit_rs_player, &QLineEdit::returnPressed,                this, &BFBC2Widget::on_pushButton_rs_reserve_clicked);

    connect(ui->lineEdit_co_co, &QLineEdit::returnPressed, this, &BFBC2Widget::on_pushButton_co_co_send_clicked);
    connect(ui->lineEdit_co_pb, &QLineEdit::returnPressed, this, &BFBC2Widget::on_pushButton_co_pb_send_clicked);

}

BFBC2Widget::~BFBC2Widget()
{
    delete ui;
}

void BFBC2Widget::setAuthenticated(bool authenticated)
{
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ch), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_op), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ml), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_bl), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_rs), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ss), authenticated);

    startupCommands(authenticated);
}

void BFBC2Widget::startupCommands(bool authenticated)
{
    // Misc
    m_connection->sendCommand("version");
    m_connection->sendCommand("serverInfo");

    if (authenticated) {
        m_connection->sendCommand("\"eventsEnabled\" \"true\"");
        m_connection->sendCommand("\"admin.listPlayers\" \"all\"");

        m_connection->sendCommand("vars.serverName");
        m_connection->sendCommand("vars.serverDescription");
        m_connection->sendCommand("vars.bannerUrl");

    //    con->sendCommand("vars.idleTimeout");

    //    con->sendCommand("vars.textChatModerationMode");
    //    con->sendCommand("vars.textChatSpamTriggerCount");
    //    con->sendCommand("vars.textChatSpamDetectionTime");
    //    con->sendCommand("vars.textChatSpamCoolDownTime");

        m_connection->sendCommand("mapList.list");

        m_connection->sendCommand("banList.list");
        m_connection->sendCommand("reservedSlots.list");

        // Admins

        // Banning

        // Maplist

        // Player

        // Punkbuster

        // Reserved Slots

        // Spectator list

        // Squad

        // Variables

    } else {
        m_connection->sendCommand("\"listPlayers\" \"all\"");
    }
}

//void BFBC2Widget::logEvent(const QString &event, const QString &message)
//{
//    int row = ui->tableWidget_ev_events->rowCount();

//    ui->tableWidget_ev_events->insertRow(row);
//    ui->tableWidget_ev_events->setItem(row, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")));
//    ui->tableWidget_ev_events->setItem(row, 1, new QTableWidgetItem(event));
//    ui->tableWidget_ev_events->setItem(row, 2, new QTableWidgetItem(message));
//    ui->tableWidget_ev_events->resizeColumnsToContents();
//}

//void BFBC2Widget::logChat(const QString &sender, const QString &message, const QString &target)
//{
//    ui->textEdit_ch->append(QString("[%1] <span style=\"color:#0000FF\">[%2] %3</span>: <span style=\"color:#008000\">%4</span>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"), target, sender, message));
//}

void BFBC2Widget::logConsole(int type, const QString &message)
{
    QString time = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");

    switch (type) {
        case 0: // Server con->send
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 1: // Server receive
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;

        case 2: // Punkbuster con->send
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 3: // PunkBuster receive
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;
    }
}

/* Connection */
void BFBC2Widget::onConnected()
{
    setAuthenticated(false);

//    logEvent("Connected", tr("Connected to %1:%2.").arg(con->tcpSocket->peerAddress().toString()).arg(con->tcpSocket->peerPort()));
}

void BFBC2Widget::onDisconnected()
{
//    logEvent("Disconnected", tr("Disconnected."));
}

/* Events */
void BFBC2Widget::onDataSentEvent(const QString &request)
{
    logConsole(0, request);
}

void BFBC2Widget::onDataReceivedEvent(const QString &response)
{
    logConsole(1, response);
}

void BFBC2Widget::onPlayerJoinEvent(const QString &player)
{
    logConsole(0, tr("Player <b>%1</b> joined the game.").arg(player));

    m_connection->sendCommand("\"admin.listPlayers\" \"all\"");
}

void BFBC2Widget::onPlayerAuthenticatedEvent(const QString &player, const QString &guid)
{
    logConsole(0, tr("Player <b>%1</b> authenticated with GUID: <b>%2</b>.").arg(player).arg(guid));
}

void BFBC2Widget::onPlayerLeaveEvent(const QString &player, const QString &info)
{
    logConsole(0, tr("Player <b>%1</b> left the game.").arg(player).arg(info)); // TODO: Impelment score stuffs here?

    m_connection->sendCommand("\"admin.listPlayers\" \"all\"");
}

void BFBC2Widget::onPlayerSpawnEvent(const QString &player, const QString &kit, const QStringList &weaponList)
{
    logConsole(0, tr("Player <b>%1</b> spawned as <b>%2</b> and with <b>%3</b>, <b>%4</b> and <b>%5</b> selected.").arg(player).arg(kit).arg(weaponList.at(0)).arg(weaponList.at(1)).arg(weaponList.at(2))); // TODO: Implement dynamic length on selected weapons.
}

void BFBC2Widget::onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot)
{
    if (killer != victim) {
        if (headshot) {
            logConsole(0, tr("Player <b>%1</b> headshoted player <b>%2</b> using <b>%3</b>").arg(killer).arg(victim).arg(weapon));
        } else {
            logConsole(0, tr("Player <b>%1</b> killed player <b>%2</b> with <b>%3</b>").arg(killer).arg(victim).arg(weapon));
        }
    } else {
        logConsole(0, tr("Player <b>%1</b> commited sucide using <b>%3</b>").arg(killer).arg(weapon));
    }
}

void BFBC2Widget::onPlayerChatEvent(const QString &player, const QString &message, const QString &target)
{
    Q_UNUSED(target)

    logConsole(4, tr("<b>%2</b>: %3").arg(player).arg(message));
}

void BFBC2Widget::onPlayerKickedEvent(const QString &player, const QString &reason)
{
    logConsole(0, tr("Player <b>%1</b> was kicked from the game, the reason was: <b>%2</b>.").arg(player).arg(reason));
}

void BFBC2Widget::onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logConsole(0, tr("Player <b>%1</b> changed squad to <b>%3</b>.").arg(player).arg(FrostbiteUtils::getSquadName(squadId)));
    }
}

void BFBC2Widget::onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(squadId);

    logConsole(0, tr("Player <b>%1</b> changed team to <b>%2</b>.").arg(player).arg(teamId));
}

void BFBC2Widget::onPunkBusterMessageEvent(const QString &message)
{
    logConsole(5, message);
}

void BFBC2Widget::onServerLoadingLevelEvent(const QString &levelName, int roundsPlayed, int roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    logConsole(0, tr("Loading level: <b>%1</b>").arg(levelName)); // TODO: Transelate internal level name to human readable.
}

void BFBC2Widget::onServerLevelStartedEvent()
{
    logConsole(0, tr("Level started"));
}

void BFBC2Widget::onServerRoundOverEvent(int winningTeamId)
{
    logConsole(0, tr("The round has just ended, and <b>%1</b> won").arg(winningTeamId));
}

void BFBC2Widget::onServerRoundOverPlayersEvent(const QString &playerInfo)
{
    logConsole(0, tr("The round has just ended, and <b>%1</b> is the final detailed player stats").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void BFBC2Widget::onServerRoundOverTeamScoresEvent(const QString &teamScores)
{
    logConsole(0, tr("The round has just ended, and <b>%1</b> is the final ticket/kill/life count for each team").arg(teamScores));
}

/* Commands */
// Misc
void BFBC2Widget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        // Call commands on startup.
        setAuthenticated(true);
    } else {
        int ret = QMessageBox::warning(0, tr("Error"), "Wrong password, make sure you typed in the right password and try again.");

        if (ret) {
            m_connection->hostDisconnect();
        }
    }
}

void BFBC2Widget::onServerInfoCommand(const QStringList &serverInfo)
{
    /*
    <serverName: string>
    <current playercount: integer>
    <max playercount: integer>
    <current gamemode: string>
    <current map: string>
    <roundsPlayed: integer>
    <roundsTotal: string>
    <scores: team scores>
    <onlineState: online state>
    <ranked: boolean>
    <punkBuster: boolean>
    <hasGamePassword: boolean>
    <serverUpTime: seconds>
    <roundTime: seconds>
    <gameMod: GameModId>
    <mapPack: integer>
    <externalGameIpAndPort: IpPortPair>
    <punkBusterVersion: PunkBusterVersion>
    <joinQueueEnabled: boolean>
    <region: Region>
    */

    // Players
    LevelEntry level = BFBC2LevelDictionary::getLevel(serverInfo.at(4));
    GameModeEntry gameMode = BFBC2LevelDictionary::getGameMode(serverInfo.at(3));

    ui->label_serverInfo_level->setText(QString("%1 - %2").arg(level.name).arg(gameMode.name));
    ui->label_serverInfo_mod->setText(QString("Mod: %1").arg(serverInfo.at(17)));
    ui->label_serverInfo_rounds->setText("");
    ui->label_serverInfo_state->setText("");

//    ui->label_pl_serverName->setText(serverInfo.at(0));
//    ui->label_pl_map->setText(mapName);
//    ui->label_pl_mod->setText(serverInfo.at(17));
//    ui->label_pl_gameMode->setText(serverInfo.at(3));
//    ui->label_pl_players->setText(QString("%1/%2").arg(serverInfo.at(1), serverInfo.at(2)));
//    ui->label_pl_round->setText(QString("%1/%2").arg(serverInfo.at(6), serverInfo.at(7)));
//    ui->label_pl_address->setText(serverInfo.at(19));
//    ui->label_pl_state->setText(serverInfo.at(11));
//    ui->label_pl_uptime->setText(QTime::fromString(serverInfo.at(15), "s").toString());

    // Maplist
    ui->label_ml_mod->setText(currentMod);
    ui->label_ml_currentmap_name->setText(level.name);
    //ui->label_ml_currentmap_image->setPixmap(level.image);
    ui->label_ml_currentmap_image->setPixmap(level.image());
}

void BFBC2Widget::onAdminListPlayersCommand(const PlayerList &playerList)
{
    // Clear QTreeWidget
    ui->treeWidget_pl_players->clear();

    QStringList teamIds;
    QStringList playerNames;
    QMap<QString, QString> teamItems;
    QMap<QString, QTreeWidgetItem *> playerItems;

    for (PlayerListItem player : playerList) {
        QStringList playerInfo;
        QString teamId = player.value("teamId");
        QString clanTag = player.value("clanTag");
        QString name = player.value("name");
        QString kills = player.value("kills");
        QString deaths = player.value("deaths");
        QString score = player.value("score");
        QString ping = player.value("ping");
        QString guid = player.value("guid");

        playerInfo.append(clanTag);
        playerInfo.append(name);
        playerInfo.append(kills);
        playerInfo.append(deaths);
        playerInfo.append(score);
        playerInfo.append(ping);
        playerInfo.append(guid);

        playerNames.append(name);

        // add player to parent teamItem
        QTreeWidgetItem *item = new QTreeWidgetItem(playerInfo);
        item->setData(0, Qt::UserRole, teamId);
        playerItems.insert(name, item);

        // add team item and team id into map with key player name
        teamItems.insert(name, teamId);
        teamIds.append(teamId);
    }

    teamIds.removeDuplicates();
    teamIds.sort();
    playerNames.sort();
    menu_pl_move->clear();

    for (QString id : teamIds) {
        QTreeWidgetItem *team = new QTreeWidgetItem(ui->treeWidget_pl_players);
        QString teamName = tr("Team %1").arg(id);
        team->setText(0, teamName);

        for (QString name : playerNames) {
            QTreeWidgetItem *player = playerItems.value(name);
            if (id == player->data(0, Qt::UserRole)) {
                team->addChild(player);
            }
        }
    }

    // Expand all player rows
    ui->treeWidget_pl_players->expandAll();

    // Resize columns so that they fits the content.
    for (int i = 0; i < ui->treeWidget_pl_players->columnCount(); i++) {
        ui->treeWidget_pl_players->resizeColumnToContents(i);
    }
}

void BFBC2Widget::onVarsServerNameCommand(const QString &serverName)
{
    ui->lineEdit_op_so_serverName->setText(serverName);
}

void BFBC2Widget::onVarsServerDescriptionCommand(const QString &serverDescription)
{
    ui->lineEdit_op_so_serverDescription->setText(serverDescription);
}

void BFBC2Widget::onVarsBannerUrlCommand(const QString &bannerUrl)
{
    ui->lineEdit_op_so_bannerUrl->setText(bannerUrl);
    ui->label_op_so_bannerUrl->setPixmap(QPixmap(bannerUrl));
}

void BFBC2Widget::onMapListListCommand(const QStringList &mapList)
{
    for (QString engineName : mapList) {
        LevelEntry level = BFBC2LevelDictionary::getLevel(engineName);

        ui->listWidget_ml_currentmaps->addItem(level.name);
    }

    // Sets nextMap
//    if (nextLevelIndex >= 0 && mapList.count() > 0) {
//        LevelEntry level = levelDictionary->getLevel(mapList.at(nextLevelIndex));

//        ui->label_ml_nextmap_name->setText(level.name);
//        ui->label_ml_nextmap_image->setPixmap(level.image);
//    }
}

void BFBC2Widget::onMapListNextLevelIndexCommand(int index)
{
    nextLevelIndex = index;
}

void BFBC2Widget::onBanListListCommand(const QStringList &banList)
{
    ui->tableWidget_bl->clearContents();
    ui->tableWidget_bl->setRowCount(banList.size());
}

void BFBC2Widget::onReservedSlotsListCommand(const QStringList &reservedSlotList)
{
    ui->listWidget_rs->clear();
    ui->listWidget_rs->addItems(reservedSlotList);
}

void BFBC2Widget::onVarsTextChatModerationModeCommand(const QString &mode)
{
    if (mode == "free") {
        ui->radioButton_op_tcm_free->setChecked(true);
    } else if (mode == "moderated") {
        ui->radioButton_op_tcm_moderated->setChecked(true);
    } else if (mode == "muted") {
        ui->radioButton_op_tcm_muted->setChecked(true);
    }
}

void BFBC2Widget::onVarsTextChatSpamTriggerCountCommand(int count)
{
    ui->spinBox_op_tcm_spamtriggercount->setValue(count);
}

void BFBC2Widget::onVarsTextChatSpamDetectionTimeCommand(int count)
{
    ui->spinBox_op_tcm_spamdetectiontime->setValue(count);
}

void BFBC2Widget::onVarsTextChatSpamCoolDownTimeCommand(int count)
{
    ui->spinBox_op_tcm_spamcooldowntime->setValue(count);
}

void BFBC2Widget::onVarsIdleTimeoutCommand(int seconds)
{
    ui->spinBox_op_gpo_idleTimeout->setValue(seconds);
}

// Player
void BFBC2Widget::treeWidget_pl_players_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_pl_players->itemAt(pos)) {
        // Something crash here.
        QString hideTeam = ui->treeWidget_pl_players->itemAt(pos)->parent()->text(0);

        for (QAction *team : menu_pl_move->actions()) {
            qDebug () << team->text();
            if (team->text () == hideTeam) {
                menu_pl_move->removeAction(team);
            }
        }

        menu_pl->exec(QCursor::pos());
    }
}

void BFBC2Widget::action_pl_sendmessage_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);
    bool ok;
    QString msg = QInputDialog::getText(this, tr("Send message"), tr("Message:"), QLineEdit::Normal, 0, &ok);

    if (ok && !msg.isEmpty()) {
        sendSayMessage(msg, player);
    }
}

void BFBC2Widget::action_pl_kill_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);
    killPlayer(player);
}

void BFBC2Widget::action_pl_textchatmoderation_muted_triggered() // Get this work
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    m_connection->sendCommand(QString("\"textChatModerationList.addPlayer\" \"muted\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_normal_triggered() // Get this work
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    m_connection->sendCommand(QString("\"textChatModerationList.addPlayer\" \"normal\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_voice_triggered() // Get this work
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    m_connection->sendCommand(QString("\"textChatModerationList.addPlayer\" \"voice\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_admin_triggered() // Get this work
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    m_connection->sendCommand(QString("\"textChatModerationList.addPlayer\" \"admin\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_kick_custom_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);
    bool ok;
    QString reason = QInputDialog::getText(this, tr("Kick"), tr("Kick reason:"), QLineEdit::Normal, 0, &ok);

    if (ok && !reason.isEmpty()) {
        kickPlayer(player, reason);
    }
}

void BFBC2Widget::action_pl_ban_byname_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);
    bool ok;
    QString reason = QInputDialog::getText(this, tr("Ban"), tr("Ban reason:"), QLineEdit::Normal, 0, &ok);

    if (ok && !reason.isEmpty()) {
        banPlayer("name", player, "perm", reason);
    }
}

void BFBC2Widget::action_pl_reservedslots_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    if (!player.isEmpty()) {
        m_connection->sendCommand(QString("\"reservedSlots.addPlayer\" \"%1\"").arg(player));
        m_connection->sendCommand("reservedSlots.list");
    }
}

/* Options Tab */
void BFBC2Widget::lineEdit_op_so_serverName_editingFinished()
{
    QString serverName = ui->lineEdit_op_so_serverName->text();

    if (!serverName.isEmpty()) {
        m_connection->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(serverName));
    }
}

void BFBC2Widget::lineEdit_op_so_serverDescription_editingFinished()
{
    QString serverDescription = ui->lineEdit_op_so_serverDescription->text();

    if (!serverDescription.isEmpty()) {
        m_connection->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(serverDescription));
    }
}

void BFBC2Widget::lineEdit_op_so_bannerUrl_editingFinished()
{
    QString bannerUrl = ui->lineEdit_op_so_bannerUrl->text();

    if (!bannerUrl.isEmpty()) {
        ui->label_op_so_bannerImage->setPixmap(QPixmap(bannerUrl));
        ui->label_op_so_bannerImage->show();
        m_connection->sendCommand(QString("\"vars.bannerUrl\" \"%1\"").arg(bannerUrl));

    }
}

/* Game Options */
void BFBC2Widget::checkbox_op_go_3dSpotting_clicked()
{
    m_connection->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(ui->checkBox_op_go_3dSpotting->isChecked()));
}

void BFBC2Widget::checkbox_op_go_crossHair_clicked()
{
    m_connection->sendCommand(QString("\"vars.crossHair\" \"%1\"").arg(ui->checkBox_op_go_crossHair->isChecked()));
}

void BFBC2Widget::checkbox_op_go_friendlyFire_clicked()
{
    m_connection->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(ui->checkBox_op_go_friendlyFire->isChecked()));
}

void BFBC2Widget::checkbox_op_go_hardcore_clicked()
{
    m_connection->sendCommand(QString("\"vars.hardCore\" \"%1\"").arg(ui->checkBox_op_go_hardcore->isChecked()));
}

void BFBC2Widget::checkbox_op_go_killCam_clicked()
{
    m_connection->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(ui->checkBox_op_go_killCam->isChecked()));
}

void BFBC2Widget::checkbox_op_go_miniMap_clicked()
{
    m_connection->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(ui->checkBox_op_go_miniMap->isChecked()));
}

void BFBC2Widget::checkbox_op_go_miniMapSpotting_clicked()
{
    m_connection->sendCommand(QString("\"vars.miniMapSpotting\" \"%1\"").arg(ui->checkBox_op_go_miniMapSpotting->isChecked()));
}

void BFBC2Widget::checkbox_op_go_teamBalance_clicked()
{
    m_connection->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(ui->checkBox_op_go_teamBalance->isChecked()));
}

void BFBC2Widget::checkbox_op_go_thirdPersonVehicleCameras_clicked()
{
    m_connection->sendCommand(QString("\"vars.thirdPersonVehicleCameras\" \"%1\"").arg(ui->checkBox_op_go_thirdPersonVehicleCameras->isChecked()));
}

/* Text Chat Moderation */
void BFBC2Widget::on_radioButton_op_tcm_free_clicked()
{
    m_connection->sendCommand(QString("\"vars.textChatModerationMode\" \"free\""));
}

void BFBC2Widget::on_radioButton_op_tcm_moderated_clicked()
{
    m_connection->sendCommand(QString("\"vars.textChatModerationMode\" \"moderated\""));
}

void BFBC2Widget::on_radioButton_op_tcm_muted_clicked()
{
    m_connection->sendCommand(QString("\"vars.textChatModerationMode\" \"muted\""));
}

/* Gamplay Options */
void BFBC2Widget::on_spinBox_op_gpo_idleTimeout_editingFinished()
{
    int timeout = ui->spinBox_op_gpo_idleTimeout->value();

    m_connection->sendCommand(QString("\"vars.idleTimeout\" \"%1\"").arg(timeout));
}

// Maplist
void BFBC2Widget::comboBox_ml_gamemode_currentIndexChanged(int index)
{
    // Stop the current item changed signal from being emitted
    ui->listWidget_ml_avaliablemaps->blockSignals(true);
    ui->listWidget_ml_avaliablemaps->clear();
    ui->listWidget_ml_avaliablemaps->blockSignals(false);

    // get a list of map names
    QStringList mapNames = BFBC2LevelDictionary::getLevelNames(index);

    // add the maps with the correct modd to avaliable maps
    ui->listWidget_ml_avaliablemaps->addItems(mapNames);
    ui->label_ml_previewmap_image->clear();

    //    int rounds = ui->spinBox_ml_rounds->value();

    //    QStringList mapPaths;
    //    for (int i = 0; i < ui->listWidget_ml_currentmaps->count (); i++) {
    //        mapPaths << ui->listWidget_ml_currentmaps->item (i)->data (Qt::UserRole).toString ();
    //    }

    //    con->sendCommand (QString("mapList.clear"));
    //    for (QString mapPath : mapPaths) {
    //        con->sendCommand (QString("mapList.append %1 %2").arg (mapPath).arg (rounds));
    //    }

    //    con->sendCommand (QString("mapList.save"));
    //    con->sendCommand (QString("mapList.nextLevelIndex 0"));
    //    con->sendCommand (QString("admin.runNextLevel"));
}

void BFBC2Widget::listWidget_ml_avaliablemaps_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    int index = ui->listWidget_ml_avaliablemaps->currentIndex().row();
    int gameModeIndex = ui->comboBox_ml_gamemode->currentIndex();
    LevelEntry level = BFBC2LevelDictionary::getLevel(index, gameModeIndex);

    ui->label_ml_previewmap_image->setPixmap(level.image());
}

void BFBC2Widget::on_pushButton_ml_add_clicked()
{
    /*
    mapList.load Load list of map names from file
    mapList.save Save maplist to file
    mapList.list [rounds] Retrieve current maplist
    mapList.clear Clears maplist
    mapList.remove <index> Remove map from list
    mapList.append <name, rounds> Add map with name <name> to end of maplist
    mapList.insert <index, name, rounds> Add map with name at the specified index to the maplist
    */

    // get game mode from combo box
    int gameModeIndex = ui->comboBox_ml_gamemode->currentIndex();
    int ret = 0;

    if (currentGamemode != gamemodes[gameModeIndex]) {
        commandRefreshTimer->blockSignals(true);
        QMessageBox msgBox;
        msgBox.setText("The gamemode selected is not the current gamemode on the server, this option will delete the maplist and change the gamemode on the server. Are you sure you want to continue?");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            m_connection->sendCommand(QString("\"admin.setPlaylist\" \"%1\"").arg(gamemodes[gameModeIndex]));
            m_connection->sendCommand("\"mapList.clear\"");

        } else {
            ui->listWidget_ml_currentmaps->takeItem(ui->listWidget_ml_currentmaps->count());
        }
    }

    commandRefreshTimer->blockSignals(false);

    // get selected map
    int avaliableMapIndex = ui->listWidget_ml_avaliablemaps->currentIndex().row();
    int rounds = ui->spinBox_ml_rounds->value();
    LevelEntry level = BFBC2LevelDictionary::getLevel(avaliableMapIndex, gameModeIndex);

    // create a new map item and insert it into current map list
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget_ml_currentmaps);
    item->setText(level.name);
    item->setData (Qt::UserRole, level.engineName);
    ui->listWidget_ml_currentmaps->addItem(item);

    // append the map to the server map list
    m_connection->sendCommand(QString("\"mapList.append\" \"%1\" \"%2\"").arg(level.engineName).arg(rounds));

    if (ret == QMessageBox::Yes) {
       m_connection->sendCommand("\"mapList.save\"");
       m_connection->sendCommand("\"mapList.nextLevelIndex\" \"0\"");
       m_connection->sendCommand("\"admin.runNextLevel\"");
    }

    m_connection->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2Widget::on_pushButton_ml_remove_clicked()
{
    // find selected map in current map list
    int removedMap = ui->listWidget_ml_currentmaps->currentRow();

    //remove map from server map list
    m_connection->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(removedMap));

    // stop the current item changed signal from being emitted
    ui->listWidget_ml_currentmaps->blockSignals(true);
    delete ui->listWidget_ml_currentmaps->takeItem(removedMap);
    ui->listWidget_ml_currentmaps->blockSignals(false);
}

void BFBC2Widget::on_pushButton_ml_restart_clicked()
{
    m_connection->sendCommand("\"admin.restartRound\"");
}

void BFBC2Widget::on_pushButton_ml_run_clicked()
{
    m_connection->sendCommand("\"admin.runNextLevel\"");
}

void BFBC2Widget::on_pushButton_ml_clear_clicked()
{
    m_connection->sendCommand("\"mapList.clear\"");
}

void BFBC2Widget::listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem *current)
{
    Q_UNUSED(current);

    int index = ui->listWidget_ml_currentmaps->currentRow();
    int gameModeIndex = gamemodes.indexOf(QRegExp(currentGamemode, Qt::CaseInsensitive));

    LevelEntry level = BFBC2LevelDictionary::getLevel(index, gameModeIndex);

    ui->label_ml_previewmap_image->setPixmap(level.image());
    m_connection->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2Widget::on_pushButton_ml_save_clicked()
{
    m_connection->sendCommand("\"mapList.save\"");
}

// BanList
void BFBC2Widget::listWidget_bl_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableWidget_bl->itemAt(pos)) {
        menu_bl->exec(QCursor::pos());
    }
}

void BFBC2Widget::action_bl_remove_triggered()
{
    QString id = ui->tableWidget_bl->currentItem()->text();
    QString type = ui->comboBox_bl_type->currentText().toLower();

    if (!id.isEmpty()) {
        unbanPlayer(type, id);
    }
}

void BFBC2Widget::on_pushButton_bl_ban_clicked()
{
    QString type = ui->comboBox_bl_type->currentText().toLower();
    QString id = ui->lineEdit_bl_id->text();
    QString timeout = ui->comboBox_bl_timeout->currentText().toLower();
    QString reason = ui->lineEdit_bl_reason->text();

    if (!id.isEmpty() || !reason.isEmpty()) {
        banPlayer(type, id, timeout, reason);
        ui->lineEdit_bl_id->clear();
        ui->lineEdit_bl_reason->clear();
    }
}

void BFBC2Widget::on_pushButton_bl_clear_clicked()
{
    m_connection->sendCommand("\"banList.clear\"");
}

void BFBC2Widget::on_pushButton_bl_save_clicked()
{
    m_connection->sendCommand("\"banList.save\"");
}

// Reserved slots
void BFBC2Widget::listWidget_rs_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget_rs->itemAt(pos)) {
        menu_rs->exec(QCursor::pos());
    }
}

void BFBC2Widget::action_rs_remove_triggered()
{
    QString player = ui->listWidget_rs->currentItem()->text();

    if (!player.isEmpty()) {
        m_connection->sendCommand(QString("\"reservedSlots.removePlayer\" \"%1\"").arg(player));
        m_connection->sendCommand("reservedSlots.list");
    }
}

void BFBC2Widget::on_pushButton_rs_reserve_clicked()
{
    QString player = ui->lineEdit_rs_player->text().trimmed();

    if (!player.isEmpty()) {
        ui->lineEdit_rs_player->clear();
        m_connection->sendCommand(QString("\"reservedSlots.addPlayer\" \"%1\"").arg(player));
        m_connection->sendCommand("reservedSlots.list");
    }
}

void BFBC2Widget::on_pushButton_rs_save_clicked()
{
    m_connection->sendCommand("reservedSlots.save");
}

void BFBC2Widget::on_pushButton_rs_clear_clicked()
{
    m_connection->sendCommand("reservedSlots.clear");
    m_connection->sendCommand("reservedSlots.list");
}

// Chat
void BFBC2Widget::pushButton_ch_send_clicked()
{
    int type = ui->comboBox_ch_type->currentIndex();

    QString message = ui->lineEdit_ch->text();
    int duration = ui->spinBox_ch_duration->value();
    QString group = ui->comboBox_ch_target->currentText().toLower();

    switch (type) {
    case 0:
        sendSayMessage(message, group);
        break;
    case 1:
        sendYellMessage(message, duration, group);
        break;
    }

    ui->lineEdit_ch->clear();
}

void BFBC2Widget::comboBox_ch_type_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->spinBox_ch_duration->hide();
        break;
    case 1:
        ui->spinBox_ch_duration->show();
        break;
    }
}

// Console
void BFBC2Widget::on_pushButton_co_co_send_clicked()
{
    QString cmd = ui->lineEdit_co_co->text();

    if (!cmd.isEmpty()) {
        ui->lineEdit_co_co->clear();
        m_connection->sendCommand(cmd);
    }
}

void BFBC2Widget::on_pushButton_co_pb_send_clicked()
{
    QString cmd = ui->lineEdit_co_pb->text();

    if (!cmd.isEmpty()) {
        ui->lineEdit_co_pb->clear();
        m_connection->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(cmd));
    }
}

void BFBC2Widget::slotChangePlayerTeam(const QString &player, const QString &altTeam)
{
    movePlayer(player, altTeam, "0", "true");
}

void BFBC2Widget::refreshPlayerList()
{
    m_connection->sendCommand(QString("\"admin.listPlayers\" \"all\""));
//    connect(commandHandler, SIGNAL(onplayerListChange()), this, &BFBC2Widget::slotPlayerListChange())); // TODO: Change to adminListPlayersAll
}

void BFBC2Widget::playerListUpdate(int oldRow)
{

    QString rounds = mapListU[2*oldRow+1];
    m_connection->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(oldRow));

    int index = ui->listWidget_ml_currentmaps->currentRow();
    int gameModeIndex = ui->comboBox_ml_gamemode->currentIndex();

    LevelEntry level = BFBC2LevelDictionary::getLevel(index, gameModeIndex);

    // get a list of map mods and map names and select all map names with a particular mod
//    QStringList mapNames = levelDictionaryObject->levelDictionary().at(gameModeIndex)->mapNames();
//    QStringList mapPaths = levelDictionaryObject->levelDictionary().at(gameModeIndex)->mapPaths();

//    // Find map name and map path for selected map
//    int avaliableMapIndex = mapNames.indexOf(mapName);
//    QString mapPath = mapPaths.at(avaliableMapIndex);

    // Append the map to the server map list
    m_connection->sendCommand(QString("\"mapList.insert\" \"%1\" \"%2\" \"%3\"").arg(index).arg(level.engineName).arg(rounds));

    m_connection->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2Widget::slotAddMapToServer(const QString &mapName)
{
    Q_UNUSED(mapName);

    /*
    mapList.load Load list of map names from file
    mapList.save Save maplist to file
    mapList.list [rounds] Retrieve current maplist
    mapList.clear Clears maplist
    mapList.remove <index> Remove map from list
    mapList.append <name, rounds> Add map with name <name> to end of maplist
    mapList.insert <index, name, rounds> Add map with name at the specified index to the maplist
    */


    // get game mode from combo box
    int gameModeIndex = ui->comboBox_ml_gamemode->currentIndex();
    int ret = 0;
    if (currentGamemode != gamemodes[gameModeIndex])
    {
        commandRefreshTimer->blockSignals(true);
        QMessageBox msgBox;
        msgBox.setText("The gamemode selected is not the current gamemode on the server, this option will delete the maplist and change the gamemode on the server. Are you sure you want to continue?");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            m_connection->sendCommand(QString("\"admin.setPlaylist\" \"%1\"").arg(gamemodes[gameModeIndex]));
            m_connection->sendCommand("\"mapList.clear\"");
        } else {
            ui->listWidget_ml_currentmaps->takeItem(ui->listWidget_ml_currentmaps->count() - 1);
        }
    }

    commandRefreshTimer->blockSignals(false);
    // get a list of map mods and map names and select all map names with a particular mod
//    QStringList mapNames = levelDictionaryObject->levelDictionary().at(gameModeIndex)->mapNames();
//    QStringList mapPaths = levelDictionaryObject->levelDictionary().at(gameModeIndex)->mapPaths();

//    // find map name and map path for selected map
//    int avaliableMapIndex = mapNames.indexOf(mapName);
//    QString mapPath = mapPaths.at(avaliableMapIndex);

    int index = ui->listWidget_ml_avaliablemaps->currentRow();

    LevelEntry level = BFBC2LevelDictionary::getLevel(index, gameModeIndex);

    // get the amount of rounds from combo box
    int rounds = ui->spinBox_ml_rounds->value();

    // append the map to the server map list
    m_connection->sendCommand(QString("\"mapList.append\" \"%1\" \"%2\"").arg(level.engineName).arg(rounds));

    if (ret == QMessageBox::Yes) {
        m_connection->sendCommand("\"mapList.save\"");
        m_connection->sendCommand("\"mapList.nextLevelIndex\" \"0\"");
        m_connection->sendCommand("\"admin.runNextLevel\"");
    }

    m_connection->sendCommand("\"mapList.list\" \"rounds\"");

}

void BFBC2Widget::slotRemoveMapFromServer(const QString &mapName)
{
    Q_UNUSED(mapName);

    // find selected map in current map list
    int removedMap = ui->listWidget_ml_currentmaps->currentRow();

    //remove map from server map list
    m_connection->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(removedMap));

    // fix to stop the drag event from creating a duplicate map item in avaliable maps
    int cRemovedMap = ui->listWidget_ml_avaliablemaps->count();
    cRemovedMap--;
    delete ui->listWidget_ml_avaliablemaps->takeItem(cRemovedMap);

    // stop the current item changed signal from being emitted
    ui->listWidget_ml_currentmaps->blockSignals(true);
    delete ui->listWidget_ml_currentmaps->takeItem(removedMap);
    ui->listWidget_ml_currentmaps->blockSignals(false);
    m_connection->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2Widget::slotMovePlayerTeam()
{
    QAction *team = qobject_cast<QAction *>(sender());
    if (team) {
        QString altTeam = "1";
        QTreeWidgetItem *player = ui->treeWidget_pl_players->currentItem();
        if (player->data(0, Qt::UserRole) == "1") {
            altTeam = "2";
        }

        movePlayer(player->text(1), altTeam, "0", "true");
        m_connection->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    }
}

void BFBC2Widget::setMapList(const QString &gamemode)
{
    int gameModeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gameModeIndex != -1) {
        QStringList mapNames = BFBC2LevelDictionary::getLevelNames(gameModeIndex);

        ui->listWidget_ml_avaliablemaps->clear();
        ui->listWidget_ml_avaliablemaps->addItems(mapNames);
    }
}

void BFBC2Widget::on_pushButton_rs_load_clicked()
{
    m_connection->sendCommand("reservedSlots.load");
    m_connection->sendCommand("reservedSlots.list");
}
