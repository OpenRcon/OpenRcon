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
    menu_pl_players = new QMenu();
    action_pl_players_kill = new QAction(tr("Kill"), menu_pl_players);
    menu_pl_players_move = new QMenu(tr("Move"), menu_pl_players);

    menu_pl_players->addAction(action_pl_players_kill);
    menu_pl_players->addMenu(menu_pl_players_move);

    // Chat
    ui->comboBox_ch_mode->addItem(tr("Say"));
    ui->comboBox_ch_mode->addItem(tr("Yell"));

    ui->comboBox_ch_target->setEnabled(false);
    ui->comboBox_ch_target->addItem(tr("All"));
    ui->comboBox_ch_target->addItem(tr("Team"));
    ui->comboBox_ch_target->addItem(tr("Squad"));

    // Maplsit
    ui->comboBox_ml_gameMode->addItems(levels->getGameModeNames());
    setAvaliableMaplist(0);
    ui->spinBox_ml_rounds->setValue(2);

    // Chat
    commandList.append("login.plainText ");
    commandList.append("login.hashed");
    commandList.append("login.hashed ");
    commandList.append("serverinfo");
    commandList.append("logout");
    commandList.append("quit");
    commandList.append("version");
    commandList.append("currentLevel");
    commandList.append("listPlayers ");
    commandList.append("admin.eventsEnabled ");
    commandList.append("admin.help");
    commandList.append("admin.kickPlayer ");
    commandList.append("admin.killPlayer ");
    commandList.append("admin.listPlayers ");
    commandList.append("admin.movePlayer ");
    commandList.append("admin.password ");
    commandList.append("admin.say ");
    commandList.append("admin.shutDown ");
    commandList.append("admin.yell ");
    commandList.append("banList.add ");
    commandList.append("banList.clear");
    commandList.append("banList.list ");
    commandList.append("banList.load");
    commandList.append("banList.remove ");
    commandList.append("banList.save");
    commandList.append("fairFight.activate");
    commandList.append("fairfight.deactivate");
    commandList.append("fairFight.isActive");
    commandList.append("mapList.add ");
    commandList.append("mapList.availableMaps ");
    commandList.append("mapList.clear");
    commandList.append("mapList.endRound ");
    commandList.append("mapList.getMapIndices");
    commandList.append("mapList.getRounds");
    commandList.append("mapList.list ");
    commandList.append("mapList.load");
    commandList.append("mapList.remove ");
    commandList.append("mapList.restartRound");
    commandList.append("mapList.runNextRound");
    commandList.append("mapList.save");
    commandList.append("mapList.setNextMapIndex ");
    commandList.append("player.idleDuration ");
    commandList.append("player.isAlive ");
    commandList.append("player.ping ");
    commandList.append("punkBuster.activate");
    commandList.append("punkBuster.isActive");
    commandList.append("punkBuster.pb_sv_command ");
    commandList.append("reservedSlotsList.add ");
    commandList.append("reservedSlotsList.aggressiveJoin ");
    commandList.append("reservedSlotsList.clear");
    commandList.append("reservedSlotsList.list");
    commandList.append("reservedSlotsList.load");
    commandList.append("reservedSlotsList.remove ");
    commandList.append("reservedSlotsList.save");
    commandList.append("spectatorList.add ");
    commandList.append("spectatorList.clear");
    commandList.append("spectatorList.list ");
    commandList.append("spectatorList.remove ");
    commandList.append("spectatorList.save");
    commandList.append("squad.leader ");
    commandList.append("squad.listActive ");
    commandList.append("squad.listPlayers ");
    commandList.append("squad.private ");
    commandList.append("vars.3dSpotting ");
    commandList.append("vars.3pCam ");
    commandList.append("vars.alwaysAllowSpectators ");
    commandList.append("vars.autoBalance ");
    commandList.append("vars.bulletDamage ");
    commandList.append("vars.commander ");
    commandList.append("vars.crossHair ");
    commandList.append("vars.forceReloadWholeMags ");
    commandList.append("vars.friendlyFire ");
    commandList.append("vars.gameModeCounter ");
    commandList.append("vars.gamePassword ");
    commandList.append("vars.hitIndicatorsEnabled ");
    commandList.append("vars.hud ");
    commandList.append("vars.idleBanRounds ");
    commandList.append("vars.idleTimeout ");
    commandList.append("vars.killCam ");
    commandList.append("vars.maxPlayers ");
    commandList.append("vars.maxSpectators ");
    commandList.append("vars.miniMap ");
    commandList.append("vars.miniMapSpotting ");
    commandList.append("vars.mpExperience ");
    commandList.append("vars.nameTag ");
    commandList.append("vars.onlySquadLeaderSpawn ");
    commandList.append("vars.playerRespawnTime ");
    commandList.append("vars.preset ");
    commandList.append("vars.regenerateHealth ");
    commandList.append("vars.roundLockdownCountdown ");
    commandList.append("vars.roundRestartPlayerCount ");
    commandList.append("vars.roundStartPlayerCount ");
    commandList.append("vars.roundTimeLimit ");
    commandList.append("vars.roundWarmupTimeout ");
    commandList.append("vars.serverDescription ");
    commandList.append("vars.serverMessage ");
    commandList.append("vars.serverName ");
    commandList.append("vars.serverType ");
    commandList.append("vars.soldierHealth ");
    commandList.append("vars.team1FactionOverride ");
    commandList.append("vars.team2FactionOverride ");
    commandList.append("vars.team3FactionOverride ");
    commandList.append("vars.team4FactionOverride ");
    commandList.append("vars.teamKillCountForKick ");
    commandList.append("vars.teamKillKickForBan ");
    commandList.append("vars.teamKillValueDecreasePerSecond ");
    commandList.append("vars.teamKillValueForKick ");
    commandList.append("vars.teamKillValueIncrease ");
    commandList.append("vars.unlockMode ");
    commandList.append("vars.vehicleSpawnAllowed ");
    commandList.append("vars.vehicleSpawnDelay ");

    completer = new QCompleter(commandList, this);
    ui->lineEdit_co_co->setCompleter(completer);

    /* Events */
    connect(con->commandHandler, SIGNAL(onDataSent(const QString&)), this, SLOT(onDataSent(const QString&)));
    connect(con->commandHandler, SIGNAL(onDataReceived(const QString&)), this, SLOT(onDataSent(const QString&)));

    connect(con->commandHandler, SIGNAL(onPlayerAuthenticated(const QString&, const QString&)), this, SLOT(onPlayerAuthenticated(const QString&, const QString&)));
    // Disconnect?
    connect(con->commandHandler, SIGNAL(onPlayerJoin(const QString&)), this, SLOT(onPlayerJoin(const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerLeave(const QString&, const QString&)), this, SLOT(onPlayerLeave(const QString&, const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerSpawn(const QString&, const int&)), this, SLOT(onPlayerSpawn(const QString&, const int&)));
    connect(con->commandHandler, SIGNAL(onPlayerKill(const QString&, const QString&, const QString&, const bool&)), this, SLOT(onPlayerKill(const QString&, const QString&, const QString&, const bool&)));
    connect(con->commandHandler, SIGNAL(onPlayerChat(const QString&, const QString&, const QString&)), this, SLOT(onPlayerChat(const QString&, const QString&, const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerSquadChange(const QString&, const int&, const int&)), this, SLOT(onPlayerSquadChange(const QString&, const int&, const int&)));
    connect(con->commandHandler, SIGNAL(onPlayerTeamChange(const QString&, const int&, const int&)), this, SLOT(onPlayerTeamChange(const QString&, const int&, const int&)));
    connect(con->commandHandler, SIGNAL(onPunkBusterMessage(const QString&)), this, SLOT(onPunkBusterMessage(const QString&)));
    connect(con->commandHandler, SIGNAL(onServerLevelLoaded(const QString&, const QString&, const int&, const int&)), this, SLOT(onServerLevelLoaded(const QString&, const QString&, const int&, const int&)));
    connect(con->commandHandler, SIGNAL(onServerRoundOver(const int&)), this, SLOT(onServerRoundOver(const int&)));
    connect(con->commandHandler, SIGNAL(onServerRoundOverPlayers(const QString&)), this, SLOT(onServerRoundOverPlayers(const QString&)));
    connect(con->commandHandler, SIGNAL(onServerRoundOverTeamScores(const QString&)), this, SLOT(onServerRoundOverTeamScores(const QString&)));

    /* Commands */

    // Misc
    connect(con->commandHandler, SIGNAL(onLoginHashedCommand()), this, SLOT(onLoginHashedCommand()));
    connect(con->commandHandler, SIGNAL(onVersionCommand(const QString&, const int&, const QString&)), this, SLOT(onVersionCommand(const QString&, const int&, const QString&)));
    connect(con->commandHandler, SIGNAL(onServerInfoCommand(const ServerInfo&)), this, SLOT(onServerInfoCommand(const ServerInfo&)));

    // Admin
    connect(con->commandHandler, SIGNAL(onAdminListPlayersCommand(const QList<PlayerInfo>&)), this, SLOT(onAdminListPlayersCommand(const QList<PlayerInfo>&)));

    // Banning

    // FairFight
    connect(con->commandHandler, SIGNAL(onFairFightIsActiveCommand(const bool&)), this, SLOT(onFairFightIsActiveCommand(const bool&)));

    // Maplist
    connect(con->commandHandler, SIGNAL(onMapListListCommand(const MapList&)), this, SLOT(onMapListListCommand(const MapList&)));

    // Player

    // Punkbuster
    connect(con->commandHandler, SIGNAL(onPunkBusterIsActiveCommand(const bool&)), this, SLOT(onPunkBusterIsActiveCommand(const bool&)));

    // Reserved Slots

    // Spectator list

    // Squad

    // Variables
    connect(con->commandHandler, SIGNAL(onVarsMaxPlayersCommand(const int&)), this, SLOT(onVarsMaxPlayersCommand(const int&)));
    connect(con->commandHandler, SIGNAL(onVarsMaxSpectatorsCommand(const int&)), this, SLOT(onVarsMaxSpectatorsCommand(const int&)));
    connect(con->commandHandler, SIGNAL(onVarsServerNameCommand(const QString&)), this, SLOT(onVarsServerNameCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsServerDescriptionCommand(const QString&)), this, SLOT(onVarsServerDescriptionCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsServerMessageCommand(const QString&)), this, SLOT(onVarsServerMessageCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsServerTypeCommand(const QString&)), this, SLOT(onVarsServerTypeCommand(const QString&)));

    /* User Interface */

    // Players
    connect(ui->treeWidget_pl_players, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_pl_players_customContextMenuRequested(QPoint)));
    connect(action_pl_players_kill, SIGNAL(triggered()), this, SLOT(action_pl_players_kill_triggered()));

    // Update playerlist on following events.
    connect(con->commandHandler, SIGNAL(onPlayerJoin(const QString&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerLeave(const QString&, const QString&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerSpawn(const QString&, const int&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerKill(const QString&, const QString&, const QString&, const bool&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerSquadChange(const QString&, const int&, const int&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerTeamChange(const QString&, const int&, const int&)), this, SLOT(updatePlayerList()));

    // Events

    // Chat
    connect(ui->comboBox_ch_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ch_mode_currentIndexChanged(int)));
    connect(ui->pushButton_ch, SIGNAL(clicked()), this, SLOT(pushButton_ch_clicked()));
    connect(ui->lineEdit_ch, SIGNAL(editingFinished()), this, SLOT(pushButton_ch_clicked()));

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

    // Reserved Slots

    // Spectator Slots

    // Console
    connect(ui->pushButton_co_co, SIGNAL(clicked()), this, SLOT(pushButton_co_co_clicked()));
    connect(ui->lineEdit_co_co, SIGNAL(editingFinished()), this, SLOT(pushButton_co_co_clicked()));

    connect(ui->pushButton_co_pb, SIGNAL(clicked()), this, SLOT(pushButton_co_pb_clicked()));
    connect(ui->lineEdit_co_pb, SIGNAL(editingFinished()), this, SLOT(pushButton_co_pb_clicked()));
}

BF4Widget::~BF4Widget()
{
    delete ui;
    delete levels;
}

void BF4Widget::startupCommands() {
    // Misc
    con->sendCommand("\"admin.eventsEnabled\" \"true\"");
    con->sendCommand("version");
    con->sendCommand("serverInfo");

    // Admin
    con->sendCommand("\"admin.listPlayers\" \"all\"");

    // Banning

    // FairFight
    con->sendCommand("fairFight.isActive");

    // Maplist
    con->sendCommand("\"maplist.list\" \"0\"");

    // Player

    // Punkbuster
    con->sendCommand("punkBuster.isActive");
    con->sendCommand("\"punkBuster.pb_sv_command\" \"pb_sv_plist\"");

    // Reserved Slots

    // Spectator list

    // Squad

    // Variables
    con->sendCommand("vars.maxPlayers");
    con->sendCommand("vars.maxSpectators");
    con->sendCommand("vars.serverName");
    con->sendCommand("vars.serverDescription");
    con->sendCommand("vars.serverMessage");
    con->sendCommand("vars.serverType");
}

void BF4Widget::logMessage(const int &type, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QDateTime::currentDateTime().toString());

    if (type == 0) { // Info
        //ui->textEdit_ev->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 1) { // Error
        //ui->textEdit_ev->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 2) { // Server send
        ui->textEdit_co_co->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 3) { // Server receive
        ui->textEdit_co_co->append(QString("%1 <span style=\"color:#0000FF\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 4) { // Chat
        ui->textEdit_ch->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 5) { // Punkbuster
        ui->textEdit_co_pb->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    }
}

void BF4Widget::logEvent(const QString &event, const QString &message)
{
    addEvent(event, message);
}

/* Events */
void BF4Widget::onDataSent(const QString &command)
{
    logMessage(2, command);
}

void BF4Widget::onDataReceived(const QString &response)
{
    logMessage(3, response);
}

void BF4Widget::onPlayerAuthenticated(const QString &player, const QString &guid)
{
    logEvent(tr("PlayerAuthenticated"), tr("Player %1 authenticated with GUID: %2.").arg(player).arg(guid));

    logMessage(0, tr("Player <b>%1</b> authenticated with GUID: <b>%2</b>.").arg(player).arg(guid));
}

void BF4Widget::onPlayerJoin(const QString &player)
{
    logEvent(tr("PlayerJoin"), tr("Player %1 joined the game.").arg(player));

    logMessage(0, tr("Player <b>%1</b> joined the game.").arg(player));
}

void BF4Widget::onPlayerLeave(const QString &player, const QString &info)
{
    logEvent(tr("PlayerLeave"), tr("Player %1 left the game.").arg(player));

    logMessage(0, tr("Player <b>%1</b> left the game.").arg(player).arg(info)); // TODO: Impelment score stuffs here?
}

void BF4Widget::onPlayerSpawn(const QString &player, const int &teamId)
{
    logEvent(tr("PlayerSpawn"), tr("Player %1 spawned, and is on team %2.").arg(player).arg(teamId));

    logMessage(0, tr("Player <b>%1</b> spawned, and is on team <b>%2</b>.").arg(player).arg(teamId));
}

void BF4Widget::onPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot)
{
    QString message, event;

    if (killer != victim) {
        if (headshot) {
            event = tr("Player %1 headshoted player %2 using %3.").arg(killer).arg(victim).arg(weapon);
            message = tr("Player <b>%1</b> headshoted player <b>%2</b> using <b>%3</b>.").arg(killer).arg(victim).arg(weapon);
        } else {
            event = tr("Player %1 killed player %2 with %3.").arg(killer).arg(victim).arg(weapon);
            message = tr("Player <b>%1</b> killed player <b>%2</b> with <b>%3</b>.").arg(killer).arg(victim).arg(weapon);
        }
    } else {
        event = tr("Player %1 commited sucide using %3.").arg(killer).arg(weapon);
        message = tr("Player <b>%1</b> commited sucide using <b>%3</b>.").arg(killer).arg(weapon);
    }

    logEvent(tr("PlayerKill"), event);
    logMessage(0, message);
}

void BF4Widget::onPlayerChat(const QString &player, const QString &message, const QString &target)
{
    Q_UNUSED(target)

    logEvent(tr("PlayerChat"), tr("%1: %2").arg(player).arg(message));
    logMessage(4, tr("<b>%1</b>: %2").arg(player).arg(message));
}

void BF4Widget::onPlayerSquadChange(const QString &player, const int &teamId, const int &squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logEvent(tr("PlayerSquadChange"), tr("Player %1 changed squad to %3.").arg(player).arg(getSquadName(squadId)));
        logMessage(0, tr("Player <b>%1</b> changed squad to <b>%3</b>.").arg(player).arg(getSquadName(squadId)));
    }
}

void BF4Widget::onPlayerTeamChange(const QString &player, const int &teamId, const int &squadId)
{
    Q_UNUSED(squadId);

    logEvent(tr("PlayerTeamChange"), tr("Player %1 changed team to %2.").arg(player).arg(teamId));
    logMessage(0, tr("Player <b>%1</b> changed team to <b>%2</b>.").arg(player).arg(teamId));
}

void BF4Widget::onPunkBusterMessage(const QString &message)
{
    logMessage(5, message);
}

void BF4Widget::onServerMaxPlayerCountChange()
{

}

void BF4Widget::onServerLevelLoaded(const QString &levelName, const QString &gameModeName, const int &roundsPlayed, const int &roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    LevelEntry level = levels->getLevel(levelName);
    GameModeEntry gameMode = levels->getGameMode(gameModeName);

    logEvent(tr("ServerLevelLoaded"), tr("Loading level %1 running gamemode %2.").arg(level.name).arg(gameMode.name));
    logMessage(0, tr("Loading level <b>%1</b> running gamemode <b>%2</b>.").arg(level.name).arg(gameMode.name));
}

void BF4Widget::onServerRoundOver(const int &winningTeamId)
{
    logEvent(tr("ServerRoundOver"), tr("The round has just ended, and %1 won").arg(winningTeamId));
    logMessage(0, tr("The round has just ended, and <b>%1</b> won").arg(winningTeamId));
}

void BF4Widget::onServerRoundOverPlayers(const QString &playerInfo)
{
    logEvent(tr("ServerRoundOverPlayers"), tr("The round has just ended, and %1 is the final detailed player stats.").arg(playerInfo));
    logMessage(0, tr("The round has just ended, and <b>%1</b> is the final detailed player stats.").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void BF4Widget::onServerRoundOverTeamScores(const QString &teamScores)
{
    logEvent(tr("ServerRoundOverTeamScores"), tr("The round has just ended, and %1 is the final ticket/kill/life count for each team.").arg(teamScores));
    logMessage(0, tr("The round has just ended, and <b>%1</b> is the final ticket/kill/life count for each team.").arg(teamScores));
}

/* Commands */

// Misc
void BF4Widget::onLoginHashedCommand()
{
    // Call commands on startup.
    startupCommands();
}

void BF4Widget::onVersionCommand(const QString &type, const int &buildId, const QString &version)
{
    Q_UNUSED(buildId);

    logMessage(0, tr("<b>%1</b> server running version: <b>%2</b>.").arg(type, version));

    ui->label_serverInfo_version->setText(tr("Version: %1").arg(version));
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
    // Clear QTreeWidget
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

// Spectator list

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

/* Chat */
void BF4Widget::comboBox_ch_mode_currentIndexChanged(int index)
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

void BF4Widget::pushButton_ch_clicked()
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
