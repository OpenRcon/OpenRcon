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

    levels = new BF4Levels(this);

    ui->comboBox_ch_mode->addItem("Say");
    ui->comboBox_ch_mode->addItem("Yell");

    ui->comboBox_ch_target->addItem("All");
    ui->comboBox_ch_target->addItem("Team");
    ui->comboBox_ch_target->addItem("Squad");

    // Add the gamemodes to the comboBox.
    ui->comboBox_li_ml_gameMode->addItems(levels->getGameModeNames());

    // Add the levels to the level maplist.
    setAvaliableMaplist(0);

    // Set the default round count.
    ui->spinBox_li_ml_rounds->setValue(2);

    // Adds all the commands to the commandList.
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
    connect(con->commandHandler, SIGNAL(onPlayerSpawn(const QString&, const QString&, const QStringList&)), this, SLOT(onPlayerSpawn(const QString&, const QString&, const QStringList&)));
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
    connect(con->commandHandler, SIGNAL(onLoginHashedCommand()), this, SLOT(onLoginHashedCommand()));
    connect(con->commandHandler, SIGNAL(onServerInfoCommand(const QStringList&)), this, SLOT(onServerInfoCommand(const QStringList&)));
    connect(con->commandHandler, SIGNAL(onVersionCommand(const QString&, const int&, const QString&)), this, SLOT(onVersionCommand(const QString&, const int&, const QString&)));
    connect(con->commandHandler, SIGNAL(onAdminListPlayersCommand(const PlayerList&)), this, SLOT(onAdminListPlayersCommand(const PlayerList&)));
    connect(con->commandHandler, SIGNAL(onMapListListCommand(const MapList&)), this, SLOT(onMapListListCommand(const MapList&)));

    connect(con->commandHandler, SIGNAL(onVarsServerNameCommand(const QString&)), this, SLOT(onVarsServerNameCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsServerDescriptionCommand(const QString&)), this, SLOT(onVarsServerDescriptionCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsServerMessageCommand(const QString&)), this, SLOT(onVarsServerMessageCommand(const QString&)));

    /* User Interface */
    connect(ui->pushButton_ch, SIGNAL(clicked()), this, SLOT(pushButton_ch_clicked()));
    connect(ui->lineEdit_ch, SIGNAL(editingFinished()), this, SLOT(pushButton_ch_clicked()));

    connect(ui->comboBox_li_ml_gameMode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_li_ml_gameMode_currentIndexChanged(int)));
    connect(ui->tableWidget_li_ml_avaliable, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(tableWidget_li_ml_avaliable_currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)));
    connect(ui->pushButton_li_ml_add, SIGNAL(clicked()), this, SLOT(pushButton_li_ml_add_clicked()));
    connect(ui->pushButton_li_ml_remove, SIGNAL(clicked()), this, SLOT(pushButton_li_ml_remove_clicked()));
    connect(ui->tableWidget_li_ml_current, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(tableWidget_li_ml_current_currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)));

    connect(ui->lineEdit_op_so_serverName, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_serverName_editingFinished()));
    connect(ui->textEdit_op_so_serverDescription, SIGNAL(textChanged()), this, SLOT(textEdit_op_so_serverDescription_textChanged()));
    connect(ui->lineEdit_op_so_serverMessage, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_serverMessage_editingFinished()));

    connect(ui->pushButton_co_co, SIGNAL(clicked()), this, SLOT(pushButton_co_co_clicked()));
    connect(ui->lineEdit_co_co, SIGNAL(editingFinished()), this, SLOT(pushButton_co_co_clicked()));

    connect(ui->pushButton_co_pb, SIGNAL(clicked()), this, SLOT(pushButton_co_pb_clicked()));
    connect(ui->lineEdit_co_pb, SIGNAL(editingFinished()), this, SLOT(pushButton_co_pb_clicked()));

    // Update playerlist on following events.
    connect(con->commandHandler, SIGNAL(onPlayerJoin(const QString&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerLeave(const QString&, const QString&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerSpawn(const QString&, const QString&, const QStringList&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerKill(const QString&, const QString&, const QString&, const bool&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerSquadChange(const QString&, const int&, const int&)), this, SLOT(updatePlayerList()));
    connect(con->commandHandler, SIGNAL(onPlayerTeamChange(const QString&, const int&, const int&)), this, SLOT(updatePlayerList()));
}

BF4Widget::~BF4Widget()
{
    delete ui;
    delete levels;
}

void BF4Widget::logMessage(const int &type, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QTime::currentTime().toString());

    if (type == 0) { // Info
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 1) { // Error
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime).arg(message));
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

void BF4Widget::startupCommands() {
    con->sendCommand("admin.eventsEnabled true");
    con->sendCommand("version");
    con->sendCommand("serverInfo");
    con->sendCommand("admin.listPlayers all");

    con->sendCommand("vars.serverName");
    con->sendCommand("vars.serverDescription");
    con->sendCommand("vars.serverMessage");

    con->sendCommand("maplist.list 0");
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
    logMessage(0, tr("Player <b>%1</b> authenticated with GUID: <b>%2</b>.").arg(player).arg(guid));
}

void BF4Widget::onPlayerJoin(const QString &player)
{
    logMessage(0, tr("Player <b>%1</b> joined the game.").arg(player));

    con->sendCommand("\"admin.listPlayers\" \"all\"");
}

void BF4Widget::onPlayerLeave(const QString &player, const QString &info)
{
    logMessage(0, tr("Player <b>%1</b> left the game.").arg(player).arg(info)); // TODO: Impelment score stuffs here?

    con->sendCommand("\"admin.listPlayers\" \"all\"");
}

void BF4Widget::onPlayerSpawn(const QString &player, const QString &kit, const QStringList &weaponList)
{
    logMessage(0, tr("Player <b>%1</b> spawned as <b>%2</b> and with <b>%3</b>, <b>%4</b> and <b>%5</b> selected.").arg(player).arg(kit).arg(weaponList.at(0)).arg(weaponList.at(1)).arg(weaponList.at(2))); // TODO: Implement dynamic length on selected weapons.
}

void BF4Widget::onPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot)
{
    if (killer != victim) {
        if (headshot) {
            logMessage(0, tr("Player <b>%1</b> headshoted player <b>%2</b> using <b>%3</b>").arg(killer).arg(victim).arg(weapon));
        } else {
            logMessage(0, tr("Player <b>%1</b> killed player <b>%2</b> with <b>%3</b>").arg(killer).arg(victim).arg(weapon));
        }
    } else {
        logMessage(0, tr("Player <b>%1</b> commited sucide using <b>%3</b>").arg(killer).arg(weapon));
    }
}

void BF4Widget::onPlayerChat(const QString &player, const QString &message, const QString &target)
{
    Q_UNUSED(target)

    logMessage(4, tr("<b>%2</b>: %3").arg(player).arg(message));
}

void BF4Widget::onPlayerSquadChange(const QString &player, const int &teamId, const int &squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logMessage(0, tr("Player <b>%1</b> changed squad to <b>%3</b>.").arg(player).arg(getSquadName(squadId)));
    }
}

void BF4Widget::onPlayerTeamChange(const QString &player, const int &teamId, const int &squadId)
{
    Q_UNUSED(squadId);

    logMessage(0, tr("Player <b>%1</b> changed team to <b>%2</b>.").arg(player).arg(teamId));
}

void BF4Widget::onPunkBusterMessage(const QString &message)
{
    logMessage(5, message);
}

void BF4Widget::onServerMaxPlayerCountChange()
{

}

void BF4Widget::onServerLevelLoaded(const QString &levelName, const QString &gameMode, const int &roundsPlayed, const int &roundsTotal)
{
    Q_UNUSED(gameMode);
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    logMessage(0, tr("Loading level: <b>%1</b>").arg(levelName)); // TODO: Transelate internal level name to human readable.
}

void BF4Widget::onServerRoundOver(const int &winningTeamId)
{
    logMessage(0, tr("The round has just ended, and <b>%1</b> won").arg(winningTeamId));
}

void BF4Widget::onServerRoundOverPlayers(const QString &playerInfo)
{
    logMessage(0, tr("The round has just ended, and <b>%1</b> is the final detailed player stats").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void BF4Widget::onServerRoundOverTeamScores(const QString &teamScores)
{
    logMessage(0, tr("The round has just ended, and <b>%1</b> is the final ticket/kill/life count for each team").arg(teamScores));
}

/* Commands */
void BF4Widget::onLoginHashedCommand()
{
    // Call commands on startup.
    startupCommands();

    // Find a better way to do this.
//    commandRefreshTimer = new QTimer(this);
//    connect(commandRefreshTimer, SIGNAL(timeout()), this, SLOT(refreshCommands()));
//    commandRefreshTimer->start(10000);
}

void BF4Widget::onVersionCommand(const QString &type, const int &buildId, const QString &version)
{
    Q_UNUSED(buildId);

    logMessage(0, tr("<b>%1</b> server running version: <b>%2</b>.").arg(type, version));
}

void BF4Widget::onServerInfoCommand(const QStringList &serverInfo)
{
    /*
    <serverName: string>
    <current playercount: integer>
    <effective max playercount: integer>
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
    <gameIpAndPort: IpPortPair>
    <punkBusterVersion: string>
    <joinQueueEnabled: boolean>
    <region: string>
    <closestPingSite: string>
    <country: string>
    <matchMakingEnabled: boolean>
    <blazePlayerCount: integer>
    <blazeGameState: string>
    */

//    QString serverName = serverInfo.at(0);
//    int playerCount = serverInfo.at(1).toInt();
//    int maxPlayerCount = serverInfo.at(2).toInt();
//    QString gamemode = serverInfo.at(3);
//    QString currentMap = serverInfo.at(4);
//    int roundsPlayed = serverInfo.at(5).toInt();
//    int roundsTotal = serverInfo.at(6).toInt();
//    QString scores  = serverInfo.at(7);
//    QString onlineState  = serverInfo.at(8);
//    bool ranked;
//    bool punkBuster;
//    bool hasGamePassword;
//    int serverUpTime;
//    int roundTime;
//    QString gameIpAndPort;
//    QString punkBusterVersion;
//    bool joinQueueEnabled;
//    QString region;
//    QString closestPingSite;
//    QString country;
//    bool matchMakingEnabled;
//    int blazePlayerCount;
//    QString blazeGameState;
}

void BF4Widget::onAdminListPlayersCommand(const PlayerList &playerList)
{
    // Clear QTreeWidget
    ui->treeWidget_pl_playerList->clear();

    QList<int> teamIds;
    QStringList playerNames;
    QMap<QString, int> teamItems;
    QMap<QString, QTreeWidgetItem *> playerItems;

    foreach (PlayerListItem player, playerList) {
        QStringList playerInfo;
        QString name = player.value("name");
        QString guid = player.value("guid");
        int teamId = player.value("teamId").toInt();
        int squadId = player.value("rank").toInt();
        QString kills = player.value("kills");
        QString deaths = player.value("deaths");
        QString score = player.value("score");
        int rank = player.value("rank").toInt();
        QString ping = player.value("ping");

        playerInfo.append(name);
        playerInfo.append(getSquadName(squadId));
        playerInfo.append(score);
        playerInfo.append(kills);
        playerInfo.append(deaths);
        playerInfo.append(ping);
        playerInfo.append(guid);
        playerNames.append(name);

        // add player to parent teamItem
        QTreeWidgetItem *item = new QTreeWidgetItem(playerInfo);
        item->setIcon(0, getRankIcon(rank));
        item->setData(0, Qt::UserRole, teamId);
        playerItems.insert(name, item);

        // add team item and team id into map with key player name
        teamItems.insert(name, teamId);
        teamIds.append(teamId);
    }

    playerNames.sort();

    foreach (int teamId, teamIds) {
        QTreeWidgetItem *team = new QTreeWidgetItem(ui->treeWidget_pl_playerList);
        team->setText(0, tr("Team %1").arg(teamId));

        foreach (QString name, playerNames) {
            QTreeWidgetItem *player = playerItems.value(name);

            if (teamId == player->data(0, Qt::UserRole)) {
                team->addChild(player);
            }
        }
    }

    // Expand all player rows
    ui->treeWidget_pl_playerList->expandAll();
}

void BF4Widget::onMapListListCommand(const MapList &mapList)
{
    setCurrentMaplist(mapList);
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

QIcon BF4Widget::getRankIcon(const int &rank)
{
    return QIcon(QString(":/bf4/ranks/rank_%1.png").arg(rank));
}

/* User Interface */
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

void BF4Widget::comboBox_li_ml_gameMode_currentIndexChanged(int index)
{
    ui->tableWidget_li_ml_avaliable->clear();

    if (index >= 0) {
        setAvaliableMaplist(index);
    }
}

void BF4Widget::tableWidget_li_ml_avaliable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    int row = ui->tableWidget_li_ml_avaliable->currentRow();

    if (row >= 0) {
        LevelEntry level = levels->getLevel(ui->tableWidget_li_ml_avaliable->item(row, 0)->text());

        ui->label_li_ml_avaliable->setPixmap(level.image);
    }
}

void BF4Widget::pushButton_li_ml_add_clicked()
{
    int row = ui->tableWidget_li_ml_avaliable->currentRow();
    QString levelName = ui->tableWidget_li_ml_avaliable->item(row, 0)->text();
    QString gameModeName = ui->tableWidget_li_ml_avaliable->item(row, 1)->text();

    LevelEntry level = levels->getLevel(levelName);
    GameModeEntry gameMode = levels->getGameMode(gameModeName);
    int rounds = ui->spinBox_li_ml_rounds->value();

    if (rounds > 0) {
        addCurrentMapListRow(level.name, gameMode.name, rounds);

        con->sendCommand(QString("mapList.add %1 %2 %3").arg(level.engineName).arg(gameMode.engineName).arg(rounds));
    }
}

void BF4Widget::pushButton_li_ml_remove_clicked()
{
    int index = ui->tableWidget_li_ml_current->currentRow();

    if (index >= 0) {
        ui->tableWidget_li_ml_current->removeRow(index);

        con->sendCommand(QString("mapList.remove %1").arg(index));
    }
}

void BF4Widget::tableWidget_li_ml_current_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    int row = ui->tableWidget_li_ml_current->currentRow();

    if (row >= 0) {
        LevelEntry level = levels->getLevel(ui->tableWidget_li_ml_current->item(row, 0)->text());

        ui->label_li_ml_current->setPixmap(level.image);
    }
}

void BF4Widget::addAvaliableMapListRow(const QString &name, const QString &gameMode)
{
    int row = ui->tableWidget_li_ml_avaliable->rowCount();

    ui->tableWidget_li_ml_avaliable->insertRow(row);
    ui->tableWidget_li_ml_avaliable->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget_li_ml_avaliable->setItem(row, 1, new QTableWidgetItem(gameMode));
}

void BF4Widget::setAvaliableMaplist(const int &gameModeIndex)
{
    QList<LevelEntry> levelList = levels->getLevels(gameModeIndex);
    GameModeEntry gameMode = levels->getGameMode(gameModeIndex);

    ui->label_li_ml_avaliable->setPixmap(levelList.first().image);

    ui->tableWidget_li_ml_avaliable->clearContents();

    for (int i = 0; i < levelList.length(); i++) {
        LevelEntry level = levelList.at(i);

        addAvaliableMapListRow(level.name, gameMode.name);
    }
}

void BF4Widget::addCurrentMapListRow(const QString &name, const QString &gameMode, const int &rounds)
{
    int row = ui->tableWidget_li_ml_current->rowCount();

    ui->tableWidget_li_ml_current->insertRow(row);
    ui->tableWidget_li_ml_current->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget_li_ml_current->setItem(row, 1, new QTableWidgetItem(gameMode));
    ui->tableWidget_li_ml_current->setItem(row, 2, new QTableWidgetItem(QString::number(rounds)));
}

void BF4Widget::setCurrentMaplist(const MapList &mapList)
{
    ui->tableWidget_li_ml_current->clearContents();

    for (int i = 0; i < mapList.length(); i++) {
        MapListEntry entry = mapList.at(i);
        LevelEntry level = levels->getLevel(entry.level);
        GameModeEntry gameMode = levels->getGameMode(entry.gameMode);

        if (i == 0) {
            ui->label_li_ml_current->setPixmap(level.image);
        }

        addCurrentMapListRow(level.name, gameMode.name, entry.rounds);
    }
}

void BF4Widget::lineEdit_op_so_serverName_editingFinished()
{
    QString serverName = ui->lineEdit_op_so_serverName->text();

    if (!serverName.isEmpty()) {
        con->sendCommand(QString("vars.serverName %1").arg(serverName));
    }
}

void BF4Widget::textEdit_op_so_serverDescription_textChanged()
{
    QString serverDescription = ui->textEdit_op_so_serverDescription->toPlainText();

    if (!serverDescription.isEmpty()) {
        con->sendCommand(QString("vars.serverDescription %1").arg(serverDescription));
    }
}

void BF4Widget::lineEdit_op_so_serverMessage_editingFinished()
{
    QString serverMessage = ui->lineEdit_op_so_serverMessage->text();

    if (!serverMessage.isEmpty()) {
        con->sendCommand(QString("vars.serverMessage %1").arg(serverMessage));
    }
}

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

    con->sendCommand(QString("punkBuster.pb_sv_command %1").arg(command));
}

void BF4Widget::updatePlayerList()
{
    con->sendCommand("admin.listPlayers all");
}
