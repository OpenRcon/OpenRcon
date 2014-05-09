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

#include "BF4Widget.h"

BF4Widget::BF4Widget(ServerEntry *serverEntry) : BF4(serverEntry), ui(new Ui::BF4Widget)
{
    ui->setupUi(this);

    /* User Inferface */

    // ServerInfo
    timerServerInfoRoundTime = new QTimer(this);
    timerServerInfoUpTime = new QTimer(this);

    // Players
    timerPlayerList = new QTimer(this);
    clipboard = QApplication::clipboard();
    menu_pl_players = new QMenu(ui->treeWidget_pl_players);
    menu_pl_players_move = new QMenu(tr("Move"), menu_pl_players);
    action_pl_players_kill = new QAction(tr("Kick"), menu_pl_players);
    action_pl_players_kick = new QAction(tr("Ban"), menu_pl_players);
    action_pl_players_ban = new QAction(tr("Kill"), menu_pl_players);
    action_pl_players_reserveSlot = new QAction(tr("Reserve slot"), menu_pl_players);
    menu_pl_players_copyTo = new QMenu(tr("Copy"), menu_pl_players);
    action_pl_players_copyTo_name = new QAction(tr("Name"), this);
    action_pl_players_copyTo_guid = new QAction(tr("GUID"), this);

    menu_pl_players->addMenu(menu_pl_players_move);
    menu_pl_players->addAction(action_pl_players_kill);
    menu_pl_players->addAction(action_pl_players_kick);
    menu_pl_players->addAction(action_pl_players_ban);
    menu_pl_players->addAction(action_pl_players_reserveSlot);
    menu_pl_players->addMenu(menu_pl_players_copyTo);
    menu_pl_players_copyTo->addAction(action_pl_players_copyTo_name);
    menu_pl_players_copyTo->addAction(action_pl_players_copyTo_guid);

    // Chat
    ui->comboBox_ch_mode->addItem(tr("Say"));
    ui->comboBox_ch_mode->addItem(tr("Yell"));

    ui->spinBox_ch_duration->setEnabled(false);
    ui->spinBox_ch_duration->setValue(10);

    ui->comboBox_ch_target->addItem(tr("All"));
    ui->comboBox_ch_target->addItem(tr("Team"));
    ui->comboBox_ch_target->addItem(tr("Squad"));

    // Maplist
    ui->comboBox_ml_gameMode->addItems(levelDictionary->getGameModeNames());
    setavailableMaplist(0);
    ui->spinBox_ml_rounds->setValue(2);

    menu_ml_available = new QMenu(ui->treeWidget_ml_available);
    action_ml_available_add = new QAction(tr("Add"), menu_ml_available);
    menu_ml_current = new QMenu(ui->treeWidget_ml_current);
    action_ml_current_remove = new QAction(tr("Remove"), menu_ml_current);

    menu_ml_available->addAction(action_ml_available_add);
    menu_ml_current->addAction(action_ml_current_remove);

    // Banlist
    menu_bl_banList = new QMenu(ui->tableWidget_bl_banList);
    action_bl_banList_remove = new QAction(tr("Remove"), menu_bl_banList);

    menu_bl_banList->addAction(action_bl_banList_remove);

    // Reserved Slots
    menu_rs_reservedSlotsList = new QMenu(ui->listWidget_rs_reservedSlotsList);
    action_rs_reservedSlotsList_remove = new QAction(tr("Remove"), menu_rs_reservedSlotsList);

    menu_rs_reservedSlotsList->addAction(action_rs_reservedSlotsList_remove);

    // Spectator List
    menu_ss_spectatorList = new QMenu(ui->listWidget_ss_spectatorList);
    action_ss_spectatorList_remove = new QAction(tr("Remove"), menu_ss_spectatorList);

    menu_ss_spectatorList->addAction(action_ss_spectatorList_remove);

    completer = new QCompleter(commandList, this);
    ui->lineEdit_co_co->setCompleter(completer);

    /* Connection */
    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));
    connect(con, SIGNAL(onDisconnected()), this, SLOT(onDisconnected()));

    /* Events */
    connect(con, SIGNAL(onDataSentEvent(const QString&)), this, SLOT(onDataSentEvent(const QString&)));
    connect(con, SIGNAL(onDataReceivedEvent(const QString&)), this, SLOT(onDataReceivedEvent(const QString&)));

    connect(con, SIGNAL(onPlayerAuthenticatedEvent(const QString&)), this, SLOT(onPlayerAuthenticatedEvent(const QString&)));
    // Disconnect?
    connect(con, SIGNAL(onPlayerJoinEvent(const QString&, const QString&)), this, SLOT(onPlayerJoinEvent(const QString&, const QString&)));
    connect(con, SIGNAL(onPlayerLeaveEvent(const QString&, const QString&)), this, SLOT(onPlayerLeaveEvent(const QString&, const QString&)));
    connect(con, SIGNAL(onPlayerSpawnEvent(const QString&, int)), this, SLOT(onPlayerSpawnEvent(const QString&, int)));
    connect(con, SIGNAL(onPlayerKillEvent(const QString&, const QString&, const QString&, bool)), this, SLOT(onPlayerKillEvent(const QString&, const QString&, const QString&, bool)));
    connect(con, SIGNAL(onPlayerChatEvent(const QString&, const QString&, const QString&)), this, SLOT(onPlayerChatEvent(const QString&, const QString&, const QString&)));
    connect(con, SIGNAL(onPlayerSquadChangeEvent(const QString&, int, int)), this, SLOT(onPlayerSquadChangeEvent(const QString&, int, int)));
    connect(con, SIGNAL(onPlayerTeamChangeEvent(const QString&, int, int)), this, SLOT(onPlayerTeamChangeEvent(const QString&, int, int)));
    connect(con, SIGNAL(onPunkBusterMessageEvent(const QString&)), this, SLOT(onPunkBusterMessageEvent(const QString&)));
    connect(con, SIGNAL(onServerMaxPlayerCountChangeEvent()), this, SLOT(onServerMaxPlayerCountChangeEvent()));
    connect(con, SIGNAL(onServerLevelLoadedEvent(const QString&, const QString&, int, int)), this, SLOT(onServerLevelLoadedEvent(const QString&, const QString&, int, int)));
    connect(con, SIGNAL(onServerRoundOverEvent(int)), this, SLOT(onServerRoundOverEvent(int)));
    connect(con, SIGNAL(onServerRoundOverPlayersEvent(const QString&)), this, SLOT(onServerRoundOverPlayersEvent(const QString&)));
    connect(con, SIGNAL(onServerRoundOverTeamScoresEvent(const QString&)), this, SLOT(onServerRoundOverTeamScoresEvent(const QString&)));

    /* Commands */

    // Misc
    connect(con, SIGNAL(onLoginHashedCommand(bool)), this, SLOT(onLoginHashedCommand(bool)));
    connect(con, SIGNAL(onVersionCommand(const QString&, int)), this, SLOT(onVersionCommand(const QString&, int)));
    connect(con, SIGNAL(onServerInfoCommand(const ServerInfo&)), this, SLOT(onServerInfoCommand(const ServerInfo&)));
    connect(con, SIGNAL(onListPlayersCommand(const QList<PlayerInfo>&, const PlayerSubset&)), this, SLOT(onListPlayersCommand(const QList<PlayerInfo>&, const PlayerSubset&)));

    // Admin
    connect(con, SIGNAL(onAdminListPlayersCommand(const QList<PlayerInfo>&, const PlayerSubset&)), this, SLOT(onAdminListPlayersCommand(const QList<PlayerInfo>&, const PlayerSubset&)));

    // Banning
    connect(con, SIGNAL(onBanListListCommand(const BanList&)), this, SLOT(onBanListListCommand(const BanList&)));

    // FairFight
    connect(con, SIGNAL(onFairFightIsActiveCommand(bool)), this, SLOT(onFairFightIsActiveCommand(bool)));

    // Maplist
    connect(con, SIGNAL(onMapListListCommand(const MapList&)), this, SLOT(onMapListListCommand(const MapList&)));

    // Player

    // Punkbuster
    connect(con, SIGNAL(onPunkBusterIsActiveCommand(bool)), this, SLOT(onPunkBusterIsActiveCommand(bool)));

    // Reserved Slots
    connect(con, SIGNAL(onReservedSlotsListAggressiveJoinCommand(bool)), this, SLOT(onReservedSlotsListAggressiveJoinCommand(bool)));
    connect(con, SIGNAL(onReservedSlotsListListCommand(const QStringList&)), this, SLOT(onReservedSlotsListListCommand(const QStringList&)));

    // Spectator list
    connect(con, SIGNAL(onSpectatorListListCommand(const QStringList&)), this, SLOT(onSpectatorListListCommand(const QStringList&)));

    // Squad

    // Variables
    connect(con, SIGNAL(onVarsAlwaysAllowSpectatorsCommand(bool)), this, SLOT(onVarsAlwaysAllowSpectatorsCommand(bool)));
    connect(con, SIGNAL(onVarsCommanderCommand(bool)), this, SLOT(onVarsCommanderCommand(bool)));
    connect(con, SIGNAL(onVarsFriendlyFireCommand(bool)), this, SLOT(onVarsFriendlyFireCommand(bool)));
    connect(con, SIGNAL(onVarsIdleTimeoutCommand(int)), this, SLOT(onVarsIdleTimeoutCommand(int)));
    connect(con, SIGNAL(onVarsKillCamCommand(bool)), this, SLOT(onVarsKillCamCommand(bool)));
    connect(con, SIGNAL(onVarsMaxPlayersCommand(int)), this, SLOT(onVarsMaxPlayersCommand(int)));
    connect(con, SIGNAL(onVarsMaxSpectatorsCommand(int)), this, SLOT(onVarsMaxSpectatorsCommand(int)));
    connect(con, SIGNAL(onVarsServerNameCommand(const QString&)), this, SLOT(onVarsServerNameCommand(const QString&)));
    connect(con, SIGNAL(onVarsServerDescriptionCommand(const QString&)), this, SLOT(onVarsServerDescriptionCommand(const QString&)));
    connect(con, SIGNAL(onVarsServerMessageCommand(const QString&)), this, SLOT(onVarsServerMessageCommand(const QString&)));
    connect(con, SIGNAL(onVarsServerTypeCommand(const QString&)), this, SLOT(onVarsServerTypeCommand(const QString&)));

    /* User Interface */

    // Players
    connect(ui->treeWidget_pl_players, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_pl_players_customContextMenuRequested(QPoint)));
    connect(action_pl_players_kill, SIGNAL(triggered()), this, SLOT(action_pl_players_kill_triggered()));
    connect(action_pl_players_kick, SIGNAL(triggered()), this, SLOT(action_pl_players_kick_triggered()));
    connect(action_pl_players_ban, SIGNAL(triggered()), this, SLOT(action_pl_players_ban_triggered()));
    connect(action_pl_players_reserveSlot, SIGNAL(triggered()), this, SLOT(action_pl_players_reserveSlot_triggered()));
    connect(action_pl_players_copyTo_name, SIGNAL(triggered()), this, SLOT(action_pl_players_copyTo_name_triggered()));
    connect(action_pl_players_copyTo_guid, SIGNAL(triggered()), this, SLOT(action_pl_players_copyTo_guid_triggered()));

    // Update playerlist on following events.
    connect(con, SIGNAL(onPlayerAuthenticatedEvent(const QString&)), this, SLOT(updatePlayerList()));
    connect(con, SIGNAL(onPlayerLeaveEvent(const QString&, const QString&)), this, SLOT(updatePlayerList()));
    connect(con, SIGNAL(onPlayerSpawnEvent(const QString&, int)), this, SLOT(updatePlayerList()));
    connect(con, SIGNAL(onPlayerKillEvent(const QString&, const QString&, const QString&, bool)), this, SLOT(updatePlayerList()));
    connect(con, SIGNAL(onPlayerSquadChangeEvent(const QString&, int, int)), this, SLOT(updatePlayerList()));
    connect(con, SIGNAL(onPlayerTeamChangeEvent(const QString&, int, int)), this, SLOT(updatePlayerList()));

    // Events

    // Chat
    connect(ui->comboBox_ch_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ch_mode_currentIndexChanged(int)));
    connect(ui->pushButton_ch_send, SIGNAL(clicked()), this, SLOT(pushButton_ch_send_clicked()));
    connect(ui->lineEdit_ch, SIGNAL(editingFinished()), this, SLOT(pushButton_ch_send_clicked()));

    // Options -> Details
    connect(ui->lineEdit_op_so_serverName, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_serverName_editingFinished()));
    connect(ui->textEdit_op_so_serverDescription, SIGNAL(textChanged()), this, SLOT(textEdit_op_so_serverDescription_textChanged()));
    connect(ui->lineEdit_op_so_serverMessage, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_serverMessage_editingFinished()));

    // Options -> Configuration
    connect(ui->checkBox_so_co_punkBuster, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_co_punkBuster_toggled(bool)));
    connect(ui->checkBox_so_co_fairFight, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_co_fairFight_toggled(bool)));
    connect(ui->checkBox_so_co_idleTimeout, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_co_idleTimeout_toggled(bool)));
    connect(ui->spinBox_so_co_idleTimeout, SIGNAL(valueChanged(int)), this, SLOT(spinBox_so_co_idleTimeout_valueChanged(int)));
    connect(ui->checkBox_so_co_aggressiveJoin, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_co_aggressiveJoin_toggled(bool)));
    connect(ui->spinBox_so_co_maxPlayers, SIGNAL(valueChanged(int)), this, SLOT(spinBox_so_co_maxPlayers_valueChanged(int)));
    connect(ui->spinBox_so_co_maxSpectators, SIGNAL(valueChanged(int)), this, SLOT(spinBox_so_co_maxSpectators_valueChanged(int)));
    connect(ui->checkBox_so_co_alwaysAllowSpectators, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_co_alwaysAllowSpectators_toggled(bool)));
    connect(ui->checkBox_so_co_commander, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_co_commander_toggled(bool)));

    // Options -> Gameplay
    connect(ui->checkBox_so_go_friendlyFire, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_go_friendlyFire_toggled(bool)));
    connect(ui->checkBox_so_go_killCam, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_go_killCam_toggled(bool)));

    // Maplist
    connect(ui->comboBox_ml_gameMode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ml_gameMode_currentIndexChanged(int)));
    connect(ui->treeWidget_ml_available, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(treeWidget_ml_available_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
    connect(ui->treeWidget_ml_available, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_ml_available_customContextMenuRequested(QPoint)));
    connect(action_ml_available_add, SIGNAL(triggered()), this, SLOT(pushButton_ml_add_clicked()));
    connect(ui->pushButton_ml_add, SIGNAL(clicked()), this, SLOT(pushButton_ml_add_clicked()));
    connect(ui->pushButton_ml_remove, SIGNAL(clicked()), this, SLOT(pushButton_ml_remove_clicked()));
    connect(ui->treeWidget_ml_current, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(treeWidget_ml_current_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
    connect(ui->treeWidget_ml_current, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_ml_current_customContextMenuRequested(QPoint)));
    connect(action_ml_current_remove, SIGNAL(triggered()), this, SLOT(pushButton_ml_remove_clicked()));

    // Banlist
    connect(ui->tableWidget_bl_banList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableWidget_bl_banList_customContextMenuRequested(QPoint)));
    connect(action_bl_banList_remove, SIGNAL(triggered()), this, SLOT(action_bl_banList_remove_triggered()));

    // Reserved Slots
    connect(ui->listWidget_rs_reservedSlotsList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listWidget_rs_reservedSlotsList_customContextMenuRequested(QPoint)));
    connect(action_rs_reservedSlotsList_remove, SIGNAL(triggered()), this, SLOT(action_rs_reservedSlotsList_remove_triggered()));
    connect(ui->lineEdit_rs_player, SIGNAL(returnPressed()), this, SLOT(pushButton_rs_add_clicked()));
    connect(ui->pushButton_rs_add, SIGNAL(clicked()), this, SLOT(pushButton_rs_add_clicked()));
    connect(ui->pushButton_rs_load, SIGNAL(clicked()), this, SLOT(pushButton_rs_load_clicked()));
    connect(ui->pushButton_rs_save, SIGNAL(clicked()), this, SLOT(pushButton_rs_save_clicked()));
    connect(ui->pushButton_rs_clear, SIGNAL(clicked()), this, SLOT(pushButton_rs_clear_clicked()));

    // Spectator List
    connect(ui->listWidget_ss_spectatorList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listWidget_ss_spectatorList_customContextMenuRequested(QPoint)));
    connect(action_ss_spectatorList_remove, SIGNAL(triggered()), this, SLOT(action_ss_spectatorList_remove_triggered()));
    connect(ui->lineEdit_ss_player, SIGNAL(returnPressed()), this, SLOT(pushButton_ss_add_clicked()));
    connect(ui->pushButton_ss_add, SIGNAL(clicked()), this, SLOT(pushButton_ss_add_clicked()));
    connect(ui->pushButton_ss_save, SIGNAL(clicked()), this, SLOT(pushButton_ss_save_clicked()));
    connect(ui->pushButton_ss_clear, SIGNAL(clicked()), this, SLOT(pushButton_ss_clear_clicked()));

    // Console
    connect(ui->pushButton_co_co, SIGNAL(clicked()), this, SLOT(pushButton_co_co_clicked()));
    connect(ui->lineEdit_co_co, SIGNAL(editingFinished()), this, SLOT(pushButton_co_co_clicked()));

    connect(ui->pushButton_co_pb, SIGNAL(clicked()), this, SLOT(pushButton_co_pb_clicked()));
    connect(ui->lineEdit_co_pb, SIGNAL(editingFinished()), this, SLOT(pushButton_co_pb_clicked()));
}

BF4Widget::~BF4Widget()
{
    delete ui;
}

void BF4Widget::setAuthenticated(bool authenticated)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ch), authenticated);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_op), authenticated);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ml), authenticated);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_bl), authenticated);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_rs), authenticated);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ss), authenticated);

    startupCommands(authenticated);
}

void BF4Widget::startupCommands(bool authenticated)
{
    // Misc
    con->sendVersionCommand();
    con->sendServerInfoCommand();

    if (authenticated) {
        con->sendAdminEventsEnabledCommand(true);

        // Admins
        con->sendAdminListPlayersCommand(PlayerSubset::All);

        // Banning
        con->sendBanListListCommand();

        con->sendFairFightIsActiveCommand();

        // Maplist
        con->sendMapListList();

        // Player

        // Punkbuster
        con->sendPunkBusterIsActive();
        con->sendPunkBusterPbSvCommand("pb_sv_plist");

        // Reserved Slots
        con->sendReservedSlotsListAggressiveJoin();
        con->sendReservedSlotsListList();

        // Spectator list
        con->sendSpectatorListList();

        // Squad

        // Variables
        con->sendVarsAlwaysAllowSpectators();
        con->sendVarsCommander();
        con->sendVarsFriendlyFire();
        con->sendVarsIdleTimeout();
        con->sendVarsKillCam();
        con->sendVarsMaxPlayers();
        con->sendVarsMaxSpectators();
        con->sendVarsServerName();
        con->sendVarsServerDescription();
        con->sendVarsServerMessage();
        con->sendVarsServerType();
    } else {
//        timerPlayerList->stop();
//        connect(timerPlayerList, SIGNAL(timeout()), this, SLOT(updatePlayerList()));
//        timerPlayerList->start(1000);
        updatePlayerList();
    }
}

void BF4Widget::logEvent(const QString &event, const QString &message)
{
    addEvent(event, message);
}

void BF4Widget::logChat(const QString &sender, const QString &message, const QString &target)
{
    ui->textEdit_ch->append(QString("[%1] <span style=\"color:#0000FF\">[%2] %3</span>: <span style=\"color:#008000\">%4</span>").arg(QTime::currentTime().toString(), target, sender, message));
}

void BF4Widget::logConsole(int type, const QString &message)
{
    QString time = QTime::currentTime().toString();

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
void BF4Widget::onConnected()
{
    setAuthenticated(false);

    logEvent("Connected", tr("Connected to %1:%2.").arg(con->tcpSocket->peerAddress().toString()).arg(con->tcpSocket->peerPort()));
}

void BF4Widget::onDisconnected()
{
    logEvent("Disconnected", tr("Disconnected."));
}

/* Events */
void BF4Widget::onDataSentEvent(const QString &request)
{
    logConsole(0, request);
}

void BF4Widget::onDataReceivedEvent(const QString &response)
{
    logConsole(1, response);
}

void BF4Widget::onPlayerAuthenticatedEvent(const QString &player)
{
    logEvent("PlayerAuthenticated", tr("Player %1 authenticated.").arg(player));
}

void BF4Widget::onPlayerJoinEvent(const QString &player, const QString &guid)
{
    logEvent("PlayerJoin", tr("Player %1 joined the game (GUID: %2).").arg(player, guid));
}

void BF4Widget::onPlayerLeaveEvent(const QString &player, const QString &info)
{
    Q_UNUSED(info);

    logEvent("PlayerLeave", tr("Player %1 left the game.").arg(player)); // TODO: Impelment score stuffs here?
}

void BF4Widget::onPlayerSpawnEvent(const QString &player, int teamId)
{
    logEvent("PlayerSpawn", tr("Player %1 spawned, and is on team %2.").arg(player).arg(teamId));
}

void BF4Widget::onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot)
{
    QString message;

    if (killer != victim) {
        if (headshot) {
            message = tr("Player %1 headshoted player %2 using %3.").arg(killer).arg(victim).arg(weapon);
        } else {
            message = tr("Player %1 killed player %2 with %3.").arg(killer).arg(victim).arg(weapon);
        }
    } else {
        message = tr("Player %1 commited sucide using %2.").arg(killer).arg(weapon);
    }

    logEvent("PlayerKill", message);
}

void BF4Widget::onPlayerChatEvent(const QString &sender, const QString &message, const QString &target)
{
    Q_UNUSED(target);

    logEvent("PlayerChat", QString("%1: %2").arg(sender).arg(message));
    logChat(sender, message, target);
}

void BF4Widget::onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logEvent("PlayerSquadChange", tr("Player %1 changed squad to %2.").arg(player).arg(getSquadName(squadId)));
    }
}

void BF4Widget::onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(squadId);

    logEvent("PlayerTeamChange", tr("Player %1 changed team to %2.").arg(player).arg(teamId));
}

void BF4Widget::onPunkBusterMessageEvent(const QString &message)
{
    logConsole(2, message);
}

void BF4Widget::onServerMaxPlayerCountChangeEvent()
{

}

void BF4Widget::onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    LevelEntry level = levelDictionary->getLevel(levelName);
    GameModeEntry gameMode = levelDictionary->getGameMode(gameModeName);

    logEvent("ServerLevelLoaded", tr("Loading level %1 running gamemode %2.").arg(level.name).arg(gameMode.name));
}

void BF4Widget::onServerRoundOverEvent(int winningTeamId)
{
    logEvent("ServerRoundOver", tr("The round has just ended, and %1 won.").arg(winningTeamId));
}

void BF4Widget::onServerRoundOverPlayersEvent(const QString &playerInfo)
{
    logEvent("ServerRoundOverPlayers", tr("The round has just ended, and %1 is the final detailed player stats.").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void BF4Widget::onServerRoundOverTeamScoresEvent(const QString &teamScores)
{
    logEvent("ServerRoundOverTeamScores", tr("The round has just ended, and %1 is the final ticket/kill/life count for each team.").arg(teamScores));
}

/* Commands */

// Misc
void BF4Widget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        // Call commands on startup.
        setAuthenticated(true);
    } else {
        int ret = QMessageBox::warning(0, tr("Error"), "Wrong password, make sure you typed in the right password and try again.");

        if (ret) {
            con->hostDisconnect();
        }
    }
}

void BF4Widget::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(type);

    ui->label_serverInfo_version->setText(tr("<b>Version</b>: %1").arg(getVersionFromBuild(build)));
    ui->label_serverInfo_version->setToolTip(QString::number(build));
}

void BF4Widget::onServerInfoCommand(const ServerInfo &serverInfo)
{
    currentLevel = levelDictionary->getLevel(serverInfo.currentMap);
    GameModeEntry currentGameMode = levelDictionary->getGameMode(serverInfo.gameMode);
    roundTime = serverInfo.roundTime;
    serverUpTime = serverInfo.serverUpTime;

    ui->label_serverInfo_level->setText(QString("<b>%1</b> - <b>%2</b>").arg(currentLevel.name).arg(currentGameMode.name));
    ui->label_serverInfo_level->setToolTip(QString("%1 - %2").arg(currentLevel.engineName, currentGameMode.engineName));
    ui->label_serverInfo_players->setText(tr("<b>Players</b>: %1 of %2").arg(serverInfo.playerCount).arg(serverInfo.maxPlayerCount));
    ui->label_serverInfo_round->setText(tr("<b>Round</b>: %1 of %2").arg(serverInfo.roundsPlayed).arg(serverInfo.roundsTotal));

    connect(timerServerInfoRoundTime, SIGNAL(timeout()), this, SLOT(updateRoundTime()));
    timerServerInfoRoundTime->start(1000);
    updateRoundTime();

    connect(timerServerInfoUpTime, SIGNAL(timeout()), this, SLOT(updateUpTime()));
    timerServerInfoUpTime->start(1000);
    updateUpTime();

    // Set maplist.
    int gameModeIndex = levelDictionary->getGameModeNames().indexOf(currentGameMode.name);

    ui->label_ml_currentMapImage->setPixmap(currentLevel.image);
    ui->label_ml_currentMapValue->setText(currentLevel.name);

    ui->comboBox_ml_gameMode->setCurrentIndex(gameModeIndex);
    setavailableMaplist(gameModeIndex);
}

void BF4Widget::onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    listPlayers(playerList, playerSubset);
}

// Admin
void BF4Widget::onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    listPlayers(playerList, playerSubset);
}

// Banning
void BF4Widget::onBanListListCommand(const BanList &banList)
{
    setBanlist(banList);
}

// FairFight
void BF4Widget::onFairFightIsActiveCommand(bool isActive)
{
    ui->checkBox_so_co_fairFight->setChecked(isActive);
}

// Maplist
void BF4Widget::onMapListListCommand(const MapList &mapList)
{
    setCurrentMaplist(mapList);
}

// Player

// Punkbuster
void BF4Widget::onPunkBusterIsActiveCommand(bool isActive)
{
    ui->checkBox_so_co_punkBuster->setChecked(isActive);
}

// Reserved Slots
void BF4Widget::onReservedSlotsListAggressiveJoinCommand(bool enabled)
{
    ui->checkBox_so_co_aggressiveJoin->setChecked(enabled);
}

void BF4Widget::onReservedSlotsListListCommand(const QStringList &reservedSlotsList)
{
    ui->listWidget_rs_reservedSlotsList->clear();
    ui->listWidget_rs_reservedSlotsList->addItems(reservedSlotsList);
}

// Spectator list
void BF4Widget::onSpectatorListListCommand(const QStringList &spectatorList)
{
    ui->listWidget_ss_spectatorList->clear();
    ui->listWidget_ss_spectatorList->addItems(spectatorList);
}

// Squad

// Variables
void BF4Widget::onVarsAlwaysAllowSpectatorsCommand(bool enabled)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ss), !enabled);
    ui->checkBox_so_co_alwaysAllowSpectators->setChecked(enabled);
}

void BF4Widget::onVarsCommanderCommand(bool enabled)
{
    ui->checkBox_so_co_commander->setChecked(enabled);
}

void BF4Widget::onVarsFriendlyFireCommand(bool enabled)
{
    ui->checkBox_so_go_friendlyFire->setChecked(enabled);
}

void BF4Widget::onVarsIdleTimeoutCommand(int timeout)
{
    if (timeout >= 1) { // TODO: This cannot be disabled on ranked servers.
        ui->checkBox_so_co_idleTimeout->setChecked(false);
        ui->spinBox_so_co_idleTimeout->setValue(timeout);
    } else {
        ui->checkBox_so_co_idleTimeout->setChecked(true);
        ui->spinBox_so_co_idleTimeout->setEnabled(false);
    }
}

void BF4Widget::onVarsKillCamCommand(bool enabled)
{
    ui->checkBox_so_go_killCam->setChecked(enabled);
}

void BF4Widget::onVarsMaxPlayersCommand(int playerCount)
{
    ui->spinBox_so_co_maxPlayers->setValue(playerCount);
}

void BF4Widget::onVarsMaxSpectatorsCommand(int spectatorCount)
{
    ui->spinBox_so_co_maxSpectators->setValue(spectatorCount);
}

void BF4Widget::onVarsServerNameCommand(const QString &serverName)
{
    ui->lineEdit_op_so_serverName->setText(serverName);
}

void BF4Widget::onVarsServerDescriptionCommand(const QString &serverDescription)
{
    ui->textEdit_op_so_serverDescription->setText(serverDescription);
}

void BF4Widget::onVarsServerMessageCommand(const QString &serverMessage)
{
    ui->lineEdit_op_so_serverMessage->setText(serverMessage);
}

void BF4Widget::onVarsServerTypeCommand(const QString &type)
{
    ui->label_so_co_serverType->setText(type);
}

QIcon BF4Widget::getRankIcon(int rank)
{
    return QIcon(QString(":/bf4/ranks/rank_%1.png").arg(rank));
}

/* User Interface */

// ServerInfo
void BF4Widget::updateServerInfo()
{
    con->sendServerInfoCommand();
}

void BF4Widget::updateRoundTime()
{
    TimeEntry time = getTimeFromSeconds(roundTime++);
    QString text;

    if (time.days != 0) {
        text += " " + tr("%1d").arg(time.days);
    }

    if (time.hours != 0) {
        text += " " + tr("%1h").arg(time.hours);
    }

    if (time.minutes != 0) {
        text += " " + tr("%1m").arg(time.minutes);
    }

    if (time.seconds != 0) {
        text += " " + tr("%1s").arg(time.seconds);
    }

    ui->label_serverInfo_round->setToolTip(text);
}

void BF4Widget::updateUpTime()
{
    TimeEntry time = getTimeFromSeconds(serverUpTime++);
    QString text;

    if (time.days != 0) {
        text += " " + tr("%1d").arg(time.days);
    }

    if (time.hours != 0) {
        text += " " + tr("%1h").arg(time.hours);
    }

    if (time.minutes != 0) {
        text += " " + tr("%1m").arg(time.minutes);
    }

    if (time.seconds != 0) {
        text += " " + tr("%1s").arg(time.seconds);
    }

    ui->label_serverInfo_upTime->setText(tr("<b>Uptime:</b> %1").arg(text));
}

// Players
void BF4Widget::updatePlayerList()
{
    if (isAuthenticated()) {
        con->sendAdminListPlayersCommand(PlayerSubset::All);
    } else {
        con->sendListPlayersCommand(PlayerSubset::All);
    }
}

void BF4Widget::listPlayers(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        ui->treeWidget_pl_players->clear();
        menu_pl_players_move->clear();

        QList<QTreeWidgetItem *> playerItems;
        QSet<int> teamIds;

        foreach (PlayerInfo player, playerList) {
            QTreeWidgetItem *playerItem = new QTreeWidgetItem();
            playerItem->setIcon(0, getRankIcon(player.rank));
            playerItem->setText(0, player.name);
            playerItem->setText(1, getSquadName(player.squadId));
            playerItem->setText(2, QString::number(player.kills));
            playerItem->setText(3, QString::number(player.deaths));
            playerItem->setText(4, QString::number(player.score));
            playerItem->setText(5, QString::number(player.ping));
            playerItem->setText(6, player.guid);
            playerItem->setData(0, Qt::UserRole, player.teamId);

            // Add player item and team id to lists.
            playerItems.append(playerItem);
            teamIds.insert(player.teamId);
        }

        for (int teamId = 0; teamId < teamIds.size(); teamId++) {
            if (teamId > 0) { // Don't list team with id 0, as this is the neutrual team.
                QTreeWidgetItem *teamItem = new QTreeWidgetItem(ui->treeWidget_pl_players);
                teamItem->setText(0, levelDictionary->getTeam(teamId - 1));

                foreach (QTreeWidgetItem *playerItem, playerItems) {
                    if (teamId == playerItem->data(0, Qt::UserRole)) {
                        teamItem->addChild(playerItem);
                    }
                }

                // Add the team to the menu_pl_players_move menu.
                action_pl_players_move_team = new QAction(levelDictionary->getTeam(teamId - 1), menu_pl_players_move);
                menu_pl_players_move->addAction(action_pl_players_move_team);
            }
        }

        menu_pl_players_move->addSeparator();

        for (int squadId = 0; squadId < 8; squadId++) {
            action_pl_players_move_squad = new QAction(getSquadName(squadId), menu_pl_players_move);
            menu_pl_players_move->addAction(action_pl_players_move_squad);
        }

        // Expand all player rows
        ui->treeWidget_pl_players->expandAll();

        // Sort players based on their score.
        ui->treeWidget_pl_players->sortItems(4, Qt::AscendingOrder);

        // Resize columns so that they fits the content.
        for (int i = 0; i < ui->treeWidget_pl_players->columnCount(); i++) {
            ui->treeWidget_pl_players->resizeColumnToContents(i);
        }
    }
}

void BF4Widget::treeWidget_pl_players_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_pl_players->itemAt(pos)) {
        menu_pl_players->exec(QCursor::pos());
    }
}

void BF4Widget::action_pl_players_kill_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(0);

    con->sendAdminKillPlayerCommand(player);
}

void BF4Widget::action_pl_players_kick_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(0);

    con->sendAdminKickPlayerCommand(player, "Kicked by admin.");
}

void BF4Widget::action_pl_players_ban_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(0);

    con->sendBanListAddCommand("perm", player, "Banned by admin.");
}

void BF4Widget::action_pl_players_reserveSlot_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(0);

    con->sendReservedSlotsListAdd(player);
}

void BF4Widget::action_pl_players_copyTo_name_triggered()
{
    clipboard->setText(ui->treeWidget_pl_players->currentItem()->text(0));
}

void BF4Widget::action_pl_players_copyTo_guid_triggered()
{
    clipboard->setText(ui->treeWidget_pl_players->currentItem()->text(6));
}

// Event
void BF4Widget::addEvent(const QString &event, const QString &message)
{
    int row = ui->tableWidget_ev_events->rowCount();

    ui->tableWidget_ev_events->insertRow(row);
    ui->tableWidget_ev_events->setItem(row, 0, new QTableWidgetItem(QTime::currentTime().toString()));
    ui->tableWidget_ev_events->setItem(row, 1, new QTableWidgetItem(event));
    ui->tableWidget_ev_events->setItem(row, 2, new QTableWidgetItem(message));
    ui->tableWidget_ev_events->resizeColumnsToContents();
}

// Chat
void BF4Widget::comboBox_ch_mode_currentIndexChanged(int index)
{
    ui->spinBox_ch_duration->setEnabled(index != 0);
}

void BF4Widget::pushButton_ch_send_clicked()
{
    QString message = ui->lineEdit_ch->text();
    int target = ui->comboBox_ch_target->currentIndex();
    int type = ui->comboBox_ch_mode->currentIndex();
    int duration = ui->spinBox_ch_duration->value();

    if (!message.isEmpty()) {
        PlayerSubset playerSubset;
        int parameter;

        switch (target) {
        case 0:
            playerSubset = PlayerSubset::All;
            break;

        case 1:
            playerSubset = PlayerSubset::Team;
            parameter = 1;
            break;

        case 2:
            playerSubset = PlayerSubset::Team;
            parameter = 2;
            break;
        }

        switch (type) {
        case 0:
            if (parameter >= 0) {
                con->sendAdminSayCommand(message, playerSubset, parameter);
            } else {
                con->sendAdminSayCommand(message, playerSubset);
            }
            break;

        case 1:
            if (parameter >= 0) {
                con->sendAdminYellCommand(message, duration, playerSubset, parameter);
            } else {
                con->sendAdminYellCommand(message, duration, playerSubset);
            }
            break;
        }

        ui->lineEdit_ch->clear();
    }
}

// Maplist
void BF4Widget::comboBox_ml_gameMode_currentIndexChanged(int index)
{
    if (index >= 0) {
        setavailableMaplist(index);
    }
}

void BF4Widget::treeWidget_ml_available_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    LevelEntry level = levelDictionary->getLevel(ui->treeWidget_ml_available->currentItem()->text(0));

    ui->label_ml_availableSelectedMapImage->setPixmap(level.image);
}

void BF4Widget::treeWidget_ml_available_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_ml_available->itemAt(pos)) {
        menu_ml_available->exec(QCursor::pos());
    }
}

void BF4Widget::pushButton_ml_add_clicked()
{
    // Make sure that treeWidget_ml_available selected item count is greater than zero.
    if (ui->treeWidget_ml_available->selectedItems().length() > 0) {
        int rounds = ui->spinBox_ml_rounds->value();

        if (rounds > 0) {
            LevelEntry level = levelDictionary->getLevel(ui->treeWidget_ml_available->currentItem()->text(0));
            GameModeEntry gameMode = levelDictionary->getGameMode(ui->treeWidget_ml_available->currentItem()->text(1));

            ui->label_ml_currentSelectedMapImage->setPixmap(level.image);

            addCurrentMapListRow(level.name, gameMode.name, rounds);
            con->sendMapListAdd(level.engineName, gameMode.engineName, rounds);
        }
    }
}

void BF4Widget::pushButton_ml_remove_clicked()
{
    // Make sure that treeWidget_ml_current selected item count is greater than zero.
    if (ui->treeWidget_ml_current->selectedItems().length() > 0) {
        if (ui->treeWidget_ml_current->topLevelItemCount() >= 1) {
            ui->label_ml_currentSelectedMapImage->clear();
        }

        int index = ui->treeWidget_ml_current->currentIndex().row();

        ui->treeWidget_ml_current->takeTopLevelItem(index);
        con->sendMapListRemove(index);
    }
}

void BF4Widget::addavailableMapListRow(const QString &name, const QString &gameMode)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, gameMode);

    ui->treeWidget_ml_available->addTopLevelItem(item);
}

void BF4Widget::setavailableMaplist(int gameModeIndex)
{
    ui->treeWidget_ml_available->clear();

    QList<LevelEntry> levelList = levelDictionary->getLevels(gameModeIndex);
    GameModeEntry gameMode = levelDictionary->getGameMode(gameModeIndex);

    ui->label_ml_availableSelectedMapImage->setPixmap(levelList.first().image);

    for (int i = 0; i < levelList.length(); i++) {
        LevelEntry level = levelList.at(i);

        addavailableMapListRow(level.name, gameMode.name);
    }

    // Resize columns so that they fits the content.
    for (int i = 0; i < ui->treeWidget_ml_available->columnCount(); i++) {
        ui->treeWidget_ml_available->resizeColumnToContents(i);
    }
}

void BF4Widget::treeWidget_ml_current_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    LevelEntry level = levelDictionary->getLevel(ui->treeWidget_ml_current->currentItem()->text(0));
    ui->label_ml_currentSelectedMapImage->setPixmap(level.image);
}

void BF4Widget::treeWidget_ml_current_customContextMenuRequested(const QPoint &pos)
{
    if (ui->treeWidget_ml_current->itemAt(pos)) {
        menu_ml_current->exec(QCursor::pos());
    }
}

void BF4Widget::addCurrentMapListRow(const QString &name, const QString &gameMode, int rounds)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, gameMode);
    item->setText(2, QString::number(rounds));

    ui->treeWidget_ml_current->addTopLevelItem(item);
}

void BF4Widget::setCurrentMaplist(const MapList &mapList)
{
    ui->treeWidget_ml_current->clear();

    for (int i = 0; i < mapList.length(); i++) {
        MapListEntry entry = mapList.at(i);
        LevelEntry level = levelDictionary->getLevel(entry.level);
        GameModeEntry gameMode = levelDictionary->getGameMode(entry.gameMode);

        if (i == 0) {
            ui->label_ml_currentSelectedMapImage->setPixmap(level.image);
        }

        addCurrentMapListRow(level.name, gameMode.name, entry.rounds);
    }

    // Resize columns so that they fits the content.
    for (int i = 0; i < ui->treeWidget_ml_available->columnCount(); i++) {
        ui->treeWidget_ml_current->resizeColumnToContents(i);
    }
}

// BanList
void BF4Widget::tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableWidget_bl_banList->itemAt(pos)) {
        menu_bl_banList->exec(QCursor::pos());
    }
}

void BF4Widget::action_bl_banList_remove_triggered()
{
    int row = ui->tableWidget_bl_banList->currentRow();
    QString idType = ui->tableWidget_bl_banList->item(row, 0)->text();
    QString player = ui->tableWidget_bl_banList->item(row, 1)->text();

    if (!idType.isEmpty() && !player.isEmpty()) {
        ui->tableWidget_bl_banList->removeRow(row);

        con->sendBanListRemoveCommand(idType, player);
    }
}

void BF4Widget::addBanListRow(const QString &idType, const QString &id, const QString &banType, int seconds, int rounds, const QString &reason)
{
    int row = ui->tableWidget_bl_banList->rowCount();

    ui->tableWidget_bl_banList->insertRow(row);
    ui->tableWidget_bl_banList->setItem(row, 0, new QTableWidgetItem(idType));
    ui->tableWidget_bl_banList->setItem(row, 1, new QTableWidgetItem(id));
    ui->tableWidget_bl_banList->setItem(row, 2, new QTableWidgetItem(banType));
    ui->tableWidget_bl_banList->setItem(row, 3, new QTableWidgetItem(QString::number(seconds)));
    ui->tableWidget_bl_banList->setItem(row, 4, new QTableWidgetItem(QString::number(rounds)));
    ui->tableWidget_bl_banList->setItem(row, 5, new QTableWidgetItem(reason));
}

void BF4Widget::setBanlist(const BanList &banList)
{
    ui->tableWidget_bl_banList->clearContents();
    ui->tableWidget_bl_banList->setRowCount(0);

    foreach (BanListEntry entry, banList) {
        addBanListRow(entry.idType, entry.id, entry.banType, entry.seconds, entry.rounds, entry.reason);
    }
}

// Reserved Slots
void BF4Widget::listWidget_rs_reservedSlotsList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget_rs_reservedSlotsList->itemAt(pos)) {
        menu_rs_reservedSlotsList->exec(QCursor::pos());
    }
}

void BF4Widget::action_rs_reservedSlotsList_remove_triggered()
{
    QString player = ui->listWidget_rs_reservedSlotsList->currentItem()->text();

    if (!player.isEmpty()) {
        delete ui->listWidget_rs_reservedSlotsList->currentItem();

        con->sendReservedSlotsListRemove(player);
    }
}

void BF4Widget::pushButton_rs_add_clicked()
{
    QString player = ui->lineEdit_rs_player->text();

    if (!player.isEmpty()) {
        ui->lineEdit_rs_player->clear();
        ui->listWidget_rs_reservedSlotsList->addItem(player);

        con->sendReservedSlotsListAdd(player);
    }
}

void BF4Widget::pushButton_rs_load_clicked()
{
    con->sendReservedSlotsListLoad();
}

void BF4Widget::pushButton_rs_save_clicked()
{
    con->sendReservedSlotsListSave();
}

void BF4Widget::pushButton_rs_clear_clicked()
{
    con->sendReservedSlotsListClear();
}

// Spectator List
void BF4Widget::listWidget_ss_spectatorList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget_ss_spectatorList->itemAt(pos)) {
        menu_ss_spectatorList->exec(QCursor::pos());
    }
}

void BF4Widget::action_ss_spectatorList_remove_triggered()
{
    QString player = ui->listWidget_ss_spectatorList->currentItem()->text();

    if (!player.isEmpty()) {
        delete ui->listWidget_ss_spectatorList->currentItem();

        con->sendSpectatorListRemove(player);
    }
}

void BF4Widget::pushButton_ss_add_clicked()
{
    QString player = ui->lineEdit_ss_player->text();

    if (!player.isEmpty()) {
        ui->lineEdit_ss_player->clear();
        ui->listWidget_ss_spectatorList->addItem(player);

        con->sendSpectatorListAdd(player);
    }
}

void BF4Widget::pushButton_ss_save_clicked()
{
    con->sendSpectatorListSave();
}

void BF4Widget::pushButton_ss_clear_clicked()
{
    con->sendSpectatorListClear();
}

// Options -> Details
void BF4Widget::lineEdit_op_so_serverName_editingFinished()
{
    QString serverName = ui->lineEdit_op_so_serverName->text();

    if (!serverName.isEmpty()) {
        con->sendVarsServerName(serverName);
    }
}

void BF4Widget::textEdit_op_so_serverDescription_textChanged()
{
    QString serverDescription = ui->textEdit_op_so_serverDescription->toPlainText();

    if (!serverDescription.isEmpty()) {
        con->sendVarsServerDescription(serverDescription);
    }
}

void BF4Widget::lineEdit_op_so_serverMessage_editingFinished()
{
    QString serverMessage = ui->lineEdit_op_so_serverMessage->text();

    if (!serverMessage.isEmpty()) {
        con->sendVarsServerMessage(serverMessage);
    }
}

// Options -> Configuration
void BF4Widget::checkBox_so_co_punkBuster_toggled(bool checked)
{
    Q_UNUSED(checked); // TODO: Do this right.

    con->sendPunkBusterActivate();
}

void BF4Widget::checkBox_so_co_fairFight_toggled(bool checked)
{
    if (checked) {
        con->sendFairFightActivateCommand();
    } else {
        con->sendFairFightDeactivateCommand();
    }
}

void BF4Widget::checkBox_so_co_idleTimeout_toggled(bool checked)
{
    int timeout;

    if (checked) {
        ui->spinBox_so_co_idleTimeout->setEnabled(false);
        timeout = 0;
    } else {
        ui->spinBox_so_co_idleTimeout->setEnabled(true);
        timeout = ui->spinBox_so_co_idleTimeout->value();
    }

    con->sendVarsIdleTimeout(timeout);
}

void BF4Widget::spinBox_so_co_idleTimeout_valueChanged(int value)
{
    if (value >= 1) {
        con->sendVarsIdleTimeout(value);
    }
}

void BF4Widget::checkBox_so_co_aggressiveJoin_toggled(bool checked)
{
    con->sendReservedSlotsListAggressiveJoin(checked);
}

void BF4Widget::spinBox_so_co_maxPlayers_valueChanged(int value)
{
    con->sendVarsMaxPlayers(value);
}

void BF4Widget::spinBox_so_co_maxSpectators_valueChanged(int value)
{
    con->sendVarsMaxSpectators(value);
}

void BF4Widget::checkBox_so_co_alwaysAllowSpectators_toggled(bool checked)
{
    con->sendVarsAlwaysAllowSpectators(checked);
}

void BF4Widget::checkBox_so_co_commander_toggled(bool checked)
{
    con->sendVarsCommander(checked);
}

// Options -> Gameplay
void BF4Widget::checkBox_so_go_friendlyFire_toggled(bool checked)
{
    con->sendVarsFriendlyFire(checked);
}

void BF4Widget::checkBox_so_go_killCam_toggled(bool checked)
{
    con->sendVarsKillCam(checked);
}

// Console
void BF4Widget::pushButton_co_co_clicked()
{
    QString command = ui->lineEdit_co_co->text();
    ui->lineEdit_co_co->clear();

    con->sendCommand(command);
}

void BF4Widget::pushButton_co_pb_clicked()
{
    QString command = ui->lineEdit_co_pb->text();
    ui->lineEdit_co_pb->clear();

    con->sendPunkBusterPbSvCommand(command);
}
