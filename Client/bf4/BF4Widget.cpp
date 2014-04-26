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

BF4Widget::BF4Widget(const QString &host, const int &port, const QString &password) : BF4(host, port, password), ui(new Ui::BF4)
{
    ui->setupUi(this);

    /* User Inferface */

    // Players
    menu_pl_players = new QMenu(ui->treeWidget_pl_players);
    menu_pl_players_move = new QMenu(tr("Move"), menu_pl_players);
    action_pl_players_ban = new QAction(tr("Kill"), menu_pl_players);
    action_pl_players_kill = new QAction(tr("Kick"), menu_pl_players);
    action_pl_players_kick = new QAction(tr("Ban"), menu_pl_players);
    action_pl_players_reserveSlot = new QAction(tr("Reserve slot"), menu_pl_players);

    menu_pl_players->addMenu(menu_pl_players_move);
    menu_pl_players->addAction(action_pl_players_kill);
    menu_pl_players->addAction(action_pl_players_kick);
    menu_pl_players->addAction(action_pl_players_ban);
    menu_pl_players->addAction(action_pl_players_reserveSlot);

    // Chat
    ui->comboBox_ch_mode->addItem(tr("Say"));
    ui->comboBox_ch_mode->addItem(tr("Yell"));

    ui->spinBox_ch_duration->setEnabled(false);
    ui->spinBox_ch_duration->setValue(10);

    ui->comboBox_ch_target->addItem(tr("All"));
    ui->comboBox_ch_target->addItem(tr("Team"));
    ui->comboBox_ch_target->addItem(tr("Squad"));

    // Maplist
    ui->comboBox_ml_gameMode->addItems(levels->getGameModeNames());
    setAvaliableMaplist(0);
    ui->spinBox_ml_rounds->setValue(2);

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

    /* Events */
    connect(con->getCommandHandler(), SIGNAL(onDataSentEvent(const QString&)), this, SLOT(onDataSentEvent(const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onDataReceivedEvent(const QString&)), this, SLOT(onDataReceivedEvent(const QString&)));

    connect(con->getCommandHandler(), SIGNAL(onPlayerAuthenticatedEvent(const QString&, const QString&)), this, SLOT(onPlayerAuthenticatedEvent(const QString&, const QString&)));
    // Disconnect?
    connect(con->getCommandHandler(), SIGNAL(onPlayerJoinEvent(const QString&)), this, SLOT(onPlayerJoinEvent(const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onPlayerLeaveEvent(const QString&, const QString&)), this, SLOT(onPlayerLeaveEvent(const QString&, const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onPlayerSpawnEvent(const QString&, const int&)), this, SLOT(onPlayerSpawnEvent(const QString&, const int&)));
    connect(con->getCommandHandler(), SIGNAL(onPlayerKillEvent(const QString&, const QString&, const QString&, const bool&)), this, SLOT(onPlayerKillEvent(const QString&, const QString&, const QString&, const bool&)));
    connect(con->getCommandHandler(), SIGNAL(onPlayerChatEvent(const QString&, const QString&, const QString&)), this, SLOT(onPlayerChatEvent(const QString&, const QString&, const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onPlayerSquadChangeEvent(const QString&, const int&, const int&)), this, SLOT(onPlayerSquadChangeEvent(const QString&, const int&, const int&)));
    connect(con->getCommandHandler(), SIGNAL(onPlayerTeamChangeEvent(const QString&, const int&, const int&)), this, SLOT(onPlayerTeamChangeEvent(const QString&, const int&, const int&)));
    connect(con->getCommandHandler(), SIGNAL(onPunkBusterMessageEvent(const QString&)), this, SLOT(onPunkBusterMessageEvent(const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onServerMaxPlayerCountChangeEvent()), this, SLOT(onServerMaxPlayerCountChangeEvent()));
    connect(con->getCommandHandler(), SIGNAL(onServerLevelLoadedEvent(const QString&, const QString&, const int&, const int&)), this, SLOT(onServerLevelLoadedEvent(const QString&, const QString&, const int&, const int&)));
    connect(con->getCommandHandler(), SIGNAL(onServerRoundOverEvent(const int&)), this, SLOT(onServerRoundOverEvent(const int&)));
    connect(con->getCommandHandler(), SIGNAL(onServerRoundOverPlayersEvent(const QString&)), this, SLOT(onServerRoundOverPlayersEvent(const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onServerRoundOverTeamScoresEvent(const QString&)), this, SLOT(onServerRoundOverTeamScoresEvent(const QString&)));

    /* Commands */
    // Misc
    connect(con->getCommandHandler(), SIGNAL(onLoginHashedCommand(const bool&)), this, SLOT(onLoginHashedCommand(const bool&)));
    connect(con->getCommandHandler(), SIGNAL(onVersionCommand(const QString&, const int&, const QString&)), this, SLOT(onVersionCommand(const QString&, const int&, const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onServerInfoCommand(const ServerInfo&)), this, SLOT(onServerInfoCommand(const ServerInfo&)));

    // Admin
    connect(con->getCommandHandler(), SIGNAL(onAdminListPlayersCommand(const QList<PlayerInfo>&)), this, SLOT(onAdminListPlayersCommand(const QList<PlayerInfo>&)));

    // Banning
    connect(con->getCommandHandler(), SIGNAL(onBanListListCommand(const BanList&)), this, SLOT(onBanListListCommand(const BanList&)));

    // FairFight
    connect(con->getCommandHandler(), SIGNAL(onFairFightIsActiveCommand(const bool&)), this, SLOT(onFairFightIsActiveCommand(const bool&)));

    // Maplist
    connect(con->getCommandHandler(), SIGNAL(onMapListListCommand(const MapList&)), this, SLOT(onMapListListCommand(const MapList&)));

    // Player

    // Punkbuster
    connect(con->getCommandHandler(), SIGNAL(onPunkBusterIsActiveCommand(const bool&)), this, SLOT(onPunkBusterIsActiveCommand(const bool&)));

    // Reserved Slots
    connect(con->getCommandHandler(), SIGNAL(onReservedSlotsListListCommand(const QStringList&)), this, SLOT(onReservedSlotsListListCommand(const QStringList&)));

    // Spectator list
    connect(con->getCommandHandler(), SIGNAL(onSpectatorListListCommand(const QStringList&)), this, SLOT(onSpectatorListListCommand(const QStringList&)));

    // Squad

    // Variables
    connect(con->getCommandHandler(), SIGNAL(onVarsMaxPlayersCommand(const int&)), this, SLOT(onVarsMaxPlayersCommand(const int&)));
    connect(con->getCommandHandler(), SIGNAL(onVarsMaxSpectatorsCommand(const int&)), this, SLOT(onVarsMaxSpectatorsCommand(const int&)));
    connect(con->getCommandHandler(), SIGNAL(onVarsServerNameCommand(const QString&)), this, SLOT(onVarsServerNameCommand(const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onVarsServerDescriptionCommand(const QString&)), this, SLOT(onVarsServerDescriptionCommand(const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onVarsServerMessageCommand(const QString&)), this, SLOT(onVarsServerMessageCommand(const QString&)));
    connect(con->getCommandHandler(), SIGNAL(onVarsServerTypeCommand(const QString&)), this, SLOT(onVarsServerTypeCommand(const QString&)));

    /* User Interface */

    // Players
    connect(ui->treeWidget_pl_players, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_pl_players_customContextMenuRequested(QPoint)));
    connect(action_pl_players_kill, SIGNAL(triggered()), this, SLOT(action_pl_players_kill_triggered()));
    connect(action_pl_players_kick, SIGNAL(triggered()), this, SLOT(action_pl_players_kick_triggered()));
    connect(action_pl_players_ban, SIGNAL(triggered()), this, SLOT(action_pl_players_ban_triggered()));
    connect(action_pl_players_reserveSlot, SIGNAL(triggered()), this, SLOT(action_pl_players_reserveSlot_triggered()));

    // Update playerlist on following events.
    connect(con->getCommandHandler(), SIGNAL(onPlayerJoinEvent(const QString&)), this, SLOT(updatePlayerList()));
    connect(con->getCommandHandler(), SIGNAL(onPlayerLeaveEvent(const QString&, const QString&)), this, SLOT(updatePlayerList()));
    connect(con->getCommandHandler(), SIGNAL(onPlayerSpawnEvent(const QString&, const int&)), this, SLOT(updatePlayerList()));
    connect(con->getCommandHandler(), SIGNAL(onPlayerKillEvent(const QString&, const QString&, const QString&, const bool&)), this, SLOT(updatePlayerList()));
    connect(con->getCommandHandler(), SIGNAL(onPlayerSquadChangeEvent(const QString&, const int&, const int&)), this, SLOT(updatePlayerList()));
    connect(con->getCommandHandler(), SIGNAL(onPlayerTeamChangeEvent(const QString&, const int&, const int&)), this, SLOT(updatePlayerList()));

    // Events

    // Chat
    connect(ui->comboBox_ch_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ch_mode_currentIndexChanged(int)));
    connect(ui->pushButton_ch_send, SIGNAL(clicked()), this, SLOT(pushButton_ch_send_clicked()));
    connect(ui->lineEdit_ch, SIGNAL(editingFinished()), this, SLOT(pushButton_ch_send_clicked()));

    // Options
    connect(ui->lineEdit_op_so_serverName, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_serverName_editingFinished()));
    connect(ui->textEdit_op_so_serverDescription, SIGNAL(textChanged()), this, SLOT(textEdit_op_so_serverDescription_textChanged()));
    connect(ui->lineEdit_op_so_serverMessage, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_serverMessage_editingFinished()));

    connect(ui->checkBox_so_co_punkBuster, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_co_punkBuster_toggled(bool)));
    connect(ui->checkBox_so_co_fairFight, SIGNAL(toggled(bool)), this, SLOT(checkBox_so_co_fairFight_toggled(bool)));

    // Maplist
    connect(ui->comboBox_ml_gameMode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ml_gameMode_currentIndexChanged(int)));
    connect(ui->tableWidget_ml_avaliable, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(tableWidget_ml_avaliable_currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)));
    connect(ui->pushButton_ml_add, SIGNAL(clicked()), this, SLOT(pushButton_ml_add_clicked()));
    connect(ui->pushButton_ml_remove, SIGNAL(clicked()), this, SLOT(pushButton_ml_remove_clicked()));
    connect(ui->tableWidget_ml_current, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(tableWidget_ml_current_currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)));

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
    connect(ui->pushButton_ss_load, SIGNAL(clicked()), this, SLOT(pushButton_ss_load_clicked()));
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

void BF4Widget::startupCommands() {
    // Misc
    con->sendCommand("\"admin.eventsEnabled\" \"true\"");
    con->sendCommand("version");
    con->sendCommand("serverInfo");

    // Admins
    con->sendCommand("\"admin.listPlayers\" \"all\"");

    // Banning
    con->sendCommand("\"banList.list\" \"0\"");

    // FairFight
    con->sendCommand("fairFight.isActive");

    // Maplist
    con->sendCommand("\"mapList.list\" \"0\"");

    // Player

    // Punkbuster
    con->sendCommand("punkBuster.isActive");
    con->sendCommand("\"punkBuster.pb_sv_command\" \"pb_sv_plist\"");

    // Reserved Slots
    con->sendCommand("reservedSlotsList.list");

    // Spectator list
    con->sendCommand("spectatorList.list");

    // Squad

    // Variables
    con->sendCommand("vars.maxPlayers");
    con->sendCommand("vars.maxSpectators");
    con->sendCommand("vars.serverName");
    con->sendCommand("vars.serverDescription");
    con->sendCommand("vars.serverMessage");
    con->sendCommand("vars.serverType");
}

void BF4Widget::logEvent(const QString &event, const QString &message)
{
    addEvent(event, message);
}

void BF4Widget::logChat(const QString &sender, const QString &message, const QString &target)
{
    ui->textEdit_ch->append(QString("[%1] (%2) %3: <span style=\"color:#008000\">%3</span>").arg(QTime::currentTime().toString(), target, sender, message));
}

void BF4Widget::logConsole(const int &type, const QString &message)
{
    QString time = QTime::currentTime().toString();

    switch (type) {
        case 0: // Server send
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 1: // Server receive
            ui->textEdit_co_co->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;

        case 2: // Punkbuster send
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#008000\">%2</span>").arg(time, message));
            break;

        case 3: // PunkBuster receive
            ui->textEdit_co_pb->append(QString("[%1] <span style=\"color:#0000FF\">%2</span>").arg(time, message));
            break;
    }
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

void BF4Widget::onPlayerAuthenticatedEvent(const QString &player, const QString &guid)
{
    logEvent("PlayerAuthenticated", tr("Player %1 authenticated with GUID: %2.").arg(player).arg(guid));
}

void BF4Widget::onPlayerJoinEvent(const QString &player)
{
    logEvent("PlayerJoin", tr("Player %1 joined the game.").arg(player));
}

void BF4Widget::onPlayerLeaveEvent(const QString &player, const QString &info)
{
    Q_UNUSED(info);

    logEvent("PlayerLeave", tr("Player %1 left the game.").arg(player)); // TODO: Impelment score stuffs here?
}

void BF4Widget::onPlayerSpawnEvent(const QString &player, const int &teamId)
{
    logEvent("PlayerSpawn", tr("Player %1 spawned, and is on team %2.").arg(player).arg(teamId));
}

void BF4Widget::onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot)
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

void BF4Widget::onPlayerSquadChangeEvent(const QString &player, const int &teamId, const int &squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logEvent("PlayerSquadChange", tr("Player %1 changed squad to %2.").arg(player).arg(getSquadName(squadId)));
    }
}

void BF4Widget::onPlayerTeamChangeEvent(const QString &player, const int &teamId, const int &squadId)
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

void BF4Widget::onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, const int &roundsPlayed, const int &roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    LevelEntry level = levels->getLevel(levelName);
    GameModeEntry gameMode = levels->getGameMode(gameModeName);

    logEvent("ServerLevelLoaded", tr("Loading level %1 running gamemode %2.").arg(level.name).arg(gameMode.name));
}

void BF4Widget::onServerRoundOverEvent(const int &winningTeamId)
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
void BF4Widget::onLoginHashedCommand(const bool &auth)
{
    if (auth) {
        // Call commands on startup.
        startupCommands();
    } else {
        int ret = QMessageBox::warning(0, tr("Error"), "Wrong password, make sure you typed in the right password and try again.");

        if (ret) {
            con->hostDisconnect();
        }
    }
}

void BF4Widget::onVersionCommand(const QString &type, const int &build)
{
    Q_UNUSED(type);

    ui->label_serverInfo_version->setText(tr("Version: %1").arg(getVersionFromBuild(build)));
}

void BF4Widget::onServerInfoCommand(const ServerInfo &serverInfo)
{
    LevelEntry currentLevel = levels->getLevel(serverInfo.currentMap);
    GameModeEntry currentGameMode = levels->getGameMode(serverInfo.gameMode);

    ui->label_serverInfo_level->setText(QString("%1 - %2").arg(currentLevel.name).arg(currentGameMode.name));
    ui->label_serverInfo_players->setText(tr("Players: %1/%2").arg(serverInfo.playerCount).arg(serverInfo.maxPlayerCount));
    ui->label_serverInfo_round->setText(tr("Round: %1/%2").arg(serverInfo.roundsPlayed).arg(serverInfo.roundsTotal));

    // Set maplist.
    int gameModeIndex = levels->getGameModeNames().indexOf(currentGameMode.name);

    ui->label_ml_currentMapImage->setPixmap(currentLevel.image);
    ui->label_ml_currentMapValue->setText(currentLevel.name);

    ui->comboBox_ml_gameMode->setCurrentIndex(gameModeIndex);
    setAvaliableMaplist(gameModeIndex);
}

// Admin
void BF4Widget::onAdminListPlayersCommand(const QList<PlayerInfo> &playerList)
{
    ui->treeWidget_pl_players->clear();

    QList<int> teamIds;
    QStringList playerNames;
    QMap<QString, int> teamItems;
    QMap<QString, QTreeWidgetItem *> playerItems;

    foreach (PlayerInfo player, playerList) {
        QStringList playerInfo;
        playerInfo.append(player.name);
        playerInfo.append(getSquadName(player.squadId));
        playerInfo.append(QString::number(player.score));
        playerInfo.append(QString::number(player.kills));
        playerInfo.append(QString::number(player.deaths));
        playerInfo.append(QString::number(player.ping));
        playerInfo.append(player.guid);
        playerNames.append(player.name);

        // add player to parent teamItem
        QTreeWidgetItem *item = new QTreeWidgetItem(playerInfo);
        item->setIcon(0, getRankIcon(player.rank));
        item->setData(0, Qt::UserRole, player.teamId);
        playerItems.insert(player.name, item);

        // add team item and team id into map with key player name
        teamItems.insert(player.name, player.teamId);
        teamIds.append(player.teamId);
    }

    playerNames.sort();

    foreach (int teamId, teamIds) {
        QTreeWidgetItem *team = new QTreeWidgetItem(ui->treeWidget_pl_players);
        team->setText(0, tr("Team %1").arg(teamId));

        foreach (QString name, playerNames) {
            QTreeWidgetItem *player = playerItems.value(name);

            if (teamId == player->data(0, Qt::UserRole)) {
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

// Banning
void BF4Widget::onBanListListCommand(const BanList &banList)
{
    setBanlist(banList);
}

// FairFight
void BF4Widget::onFairFightIsActiveCommand(const bool &isActive)
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
void BF4Widget::onPunkBusterIsActiveCommand(const bool &isActive)
{
    ui->checkBox_so_co_punkBuster->setChecked(isActive);
}

// Reserved Slots
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
void BF4Widget::onVarsMaxPlayersCommand(const int &playerCount)
{
    ui->spinBox_so_co_maxPlayers->setValue(playerCount);
}

void BF4Widget::onVarsMaxSpectatorsCommand(const int &spectatorCount)
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

/* User Interface */

/* Players */
QIcon BF4Widget::getRankIcon(const int &rank)
{
    return QIcon(QString(":/bf4/ranks/rank_%1.png").arg(rank));
}

void BF4Widget::updatePlayerList()
{
    con->sendCommand("\"admin.listPlayers\" \"all\"");
}

/* Event */
void BF4Widget::addEvent(const QString &event, const QString &message)
{
    int row = ui->tableWidget_ev_events->rowCount();

    ui->tableWidget_ev_events->insertRow(row);
    ui->tableWidget_ev_events->setItem(row, 0, new QTableWidgetItem(QTime::currentTime().toString()));
    ui->tableWidget_ev_events->setItem(row, 1, new QTableWidgetItem(event));
    ui->tableWidget_ev_events->setItem(row, 2, new QTableWidgetItem(message));
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

    con->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void BF4Widget::action_pl_players_kick_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(0);

    con->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"Kicked by admin.\"").arg(player));
}

void BF4Widget::action_pl_players_ban_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(0);

    con->sendCommand(QString("\"banList.add\" \"%1\" \"perm\" \"Banned by admin.\"").arg(player));
}

void BF4Widget::action_pl_players_reserveSlot_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(0);

    con->sendCommand(QString("\"reservedSlotsList.add\" \"%1\"").arg(player));
    con->sendCommand("reservedSlotsList.list");
}

/* Chat */
void BF4Widget::comboBox_ch_mode_currentIndexChanged(const int &index)
{
    switch (index) {
        case 0:
            ui->comboBox_ch_target->setEnabled(false);
            break;

        case 1:
            ui->comboBox_ch_target->setEnabled(true);
            break;
    }
}

void BF4Widget::pushButton_ch_send_clicked()
{
    int type = ui->comboBox_ch_mode->currentIndex();

    QString message = ui->lineEdit_ch->text();
    int duration = ui->spinBox_ch_duration->value();
    QString group = ui->comboBox_ch_target->currentText().toLower();

    if (!message.isEmpty()) {
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
}

/* Maplist */
void BF4Widget::comboBox_ml_gameMode_currentIndexChanged(int index)
{
    if (index >= 0) {
        setAvaliableMaplist(index);
    }
}

void BF4Widget::tableWidget_ml_avaliable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    int row = ui->tableWidget_ml_avaliable->currentRow();

    if (row >= 0) {
        LevelEntry level = levels->getLevel(ui->tableWidget_ml_avaliable->item(row, 0)->text());

        ui->label_ml_avaliableSelectedMapImage->setPixmap(level.image);
    }
}

void BF4Widget::pushButton_ml_add_clicked()
{
    // Make sure that tableWidget_ml_avaliable selected item count is greater than zero.
    if (ui->tableWidget_ml_avaliable->selectedItems().length() > 0) {
        int rounds = ui->spinBox_ml_rounds->value();

        if (rounds > 0) {
            QModelIndexList indexList = ui->tableWidget_ml_avaliable->selectionModel()->selectedRows();

            foreach (QModelIndex index, indexList) {
                int row = index.row();

                QString levelName = ui->tableWidget_ml_avaliable->item(row, 0)->text();
                QString gameModeName = ui->tableWidget_ml_avaliable->item(row, 1)->text();

                LevelEntry level = levels->getLevel(levelName);
                GameModeEntry gameMode = levels->getGameMode(gameModeName);

                if (ui->tableWidget_ml_current->rowCount() < 1) {
                    ui->label_ml_currentSelectedMapImage->setPixmap(level.image);
                }

                con->sendCommand(QString("\"mapList.add\" \"%1\" \"%2\" \"%3\"").arg(level.engineName).arg(gameMode.engineName).arg(rounds));
                addCurrentMapListRow(level.name, gameMode.name, rounds);
            }
        }
    }
}

void BF4Widget::pushButton_ml_remove_clicked()
{
    // Make sure that tableWidget_ml_current selected item count is greater than zero.
    if (ui->tableWidget_ml_current->selectedItems().length() > 0) {
        if (ui->tableWidget_ml_current->rowCount() >= 1) {
            ui->label_ml_currentSelectedMapImage->clear();
        }

        QModelIndexList indexList = ui->tableWidget_ml_current->selectionModel()->selectedRows();

        foreach (QModelIndex index, indexList) {
            int row = index.row();

            con->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(row));
            ui->tableWidget_ml_current->removeRow(row);
        }
    }
}

void BF4Widget::tableWidget_ml_current_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    int row = ui->tableWidget_ml_current->currentRow();

    if (row >= 0) {
        LevelEntry level = levels->getLevel(ui->tableWidget_ml_current->item(row, 0)->text());

        ui->label_ml_currentSelectedMapImage->setPixmap(level.image);
    }
}

void BF4Widget::addAvaliableMapListRow(const QString &name, const QString &gameMode)
{
    int row = ui->tableWidget_ml_avaliable->rowCount();

    ui->tableWidget_ml_avaliable->insertRow(row);
    ui->tableWidget_ml_avaliable->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget_ml_avaliable->setItem(row, 1, new QTableWidgetItem(gameMode));
}

void BF4Widget::setAvaliableMaplist(const int &gameModeIndex)
{
    QList<LevelEntry> levelList = levels->getLevels(gameModeIndex);
    GameModeEntry gameMode = levels->getGameMode(gameModeIndex);

    ui->label_ml_avaliableSelectedMapImage->setPixmap(levelList.first().image);

    ui->tableWidget_ml_avaliable->clearContents();
    ui->tableWidget_ml_avaliable->setRowCount(0);

    for (int i = 0; i < levelList.length(); i++) {
        LevelEntry level = levelList.at(i);

        addAvaliableMapListRow(level.name, gameMode.name);
    }
}

void BF4Widget::addCurrentMapListRow(const QString &name, const QString &gameMode, const int &rounds)
{
    int row = ui->tableWidget_ml_current->rowCount();

    ui->tableWidget_ml_current->insertRow(row);
    ui->tableWidget_ml_current->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget_ml_current->setItem(row, 1, new QTableWidgetItem(gameMode));
    ui->tableWidget_ml_current->setItem(row, 2, new QTableWidgetItem(QString::number(rounds)));
}

void BF4Widget::setCurrentMaplist(const MapList &mapList)
{
    ui->tableWidget_ml_current->clearContents();
    ui->tableWidget_ml_current->setRowCount(0);

    for (int i = 0; i < mapList.length(); i++) {
        MapListEntry entry = mapList.at(i);
        LevelEntry level = levels->getLevel(entry.level);
        GameModeEntry gameMode = levels->getGameMode(entry.gameMode);

        if (i == 0) {
            ui->label_ml_currentSelectedMapImage->setPixmap(level.image);
        }

        addCurrentMapListRow(level.name, gameMode.name, entry.rounds);
    }
}

/* BanList */
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

        con->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(idType, player));
        con->sendCommand("\"banList.list\" \"0\"");
    }
}

void BF4Widget::addBanListRow(const QString &idType, const QString &id, const QString &banType, const int &seconds, const int &rounds, const QString &reason)
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

/* Reserved Slots */
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

        con->sendCommand(QString("\"reservedSlotsList.remove\" \"%1\"").arg(player));
        con->sendCommand("\"reservedSlotsList.list\" \"0\"");
    }
}

void BF4Widget::pushButton_rs_add_clicked()
{
    QString player = ui->lineEdit_rs_player->text();

    if (!player.isEmpty()) {
        ui->lineEdit_rs_player->clear();
        ui->listWidget_rs_reservedSlotsList->addItem(player);

        con->sendCommand(QString("\"reservedSlotsList.add\" \"%1\"").arg(player));
        con->sendCommand("reservedSlotsList.list");
    }
}

void BF4Widget::pushButton_rs_load_clicked()
{
    con->sendCommand("reservedSlotsList.load");
    con->sendCommand("reservedSlotsList.list");
}

void BF4Widget::pushButton_rs_save_clicked()
{
    con->sendCommand("reservedSlotsList.save");
    con->sendCommand("reservedSlotsList.list");
}

void BF4Widget::pushButton_rs_clear_clicked()
{
    con->sendCommand("reservedSlotsList.clear");
    con->sendCommand("reservedSlotsList.list");
}

/* Spectator List */
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

        con->sendCommand(QString("\"spectatorList.remove\" \"%1\"").arg(player));
        con->sendCommand("spectatorList.list");
    }
}

void BF4Widget::pushButton_ss_add_clicked()
{
    QString player = ui->lineEdit_ss_player->text();

    if (!player.isEmpty()) {
        ui->lineEdit_ss_player->clear();
        ui->listWidget_ss_spectatorList->addItem(player);

        con->sendCommand(QString("\"spectatorList.add\" \"%1\"").arg(player));
        con->sendCommand("spectatorList.list");
    }
}

void BF4Widget::pushButton_ss_load_clicked()
{
    con->sendCommand("spectatorList.load");
    con->sendCommand("spectatorList.list");
}

void BF4Widget::pushButton_ss_save_clicked()
{
    con->sendCommand("spectatorList.save");
    con->sendCommand("spectatorList.list");
}

void BF4Widget::pushButton_ss_clear_clicked()
{
    con->sendCommand("spectatorList.clear");
    con->sendCommand("spectatorList.list");
}

/* Options */
void BF4Widget::lineEdit_op_so_serverName_editingFinished()
{
    QString serverName = ui->lineEdit_op_so_serverName->text();

    if (!serverName.isEmpty()) {
        con->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(serverName));
    }
}

void BF4Widget::textEdit_op_so_serverDescription_textChanged()
{
    QString serverDescription = ui->textEdit_op_so_serverDescription->toPlainText();

    if (!serverDescription.isEmpty()) {
        con->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(serverDescription));
    }
}

void BF4Widget::lineEdit_op_so_serverMessage_editingFinished()
{
    QString serverMessage = ui->lineEdit_op_so_serverMessage->text();

    if (!serverMessage.isEmpty()) {
        con->sendCommand(QString("\"vars.serverMessage\" \"%1\"").arg(serverMessage));
    }
}

void BF4Widget::checkBox_so_co_punkBuster_toggled(bool checked)
{
    con->sendCommand("punkBuster.activate");

    if (checked) {

    } else {

    }
}

void BF4Widget::checkBox_so_co_fairFight_toggled(bool checked)
{
    if (checked) {
        con->sendCommand("fairFight.activate");
    } else {
        con->sendCommand("fairFight.deactivate");
    }
}

/* Console */
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

    con->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(command));
}
