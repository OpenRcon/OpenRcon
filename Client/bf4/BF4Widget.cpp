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

    // Map squad names to id.
    squadNameList.append("Alpha");
    squadNameList.append("Bravo");
    squadNameList.append("Charlie");
    squadNameList.append("Delta");
    squadNameList.append("Echo");
    squadNameList.append("Foxtrot");
    squadNameList.append("Golf");
    squadNameList.append("Hotel");

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
    ui->lineEdit_co_input->setCompleter(completer);

    // Add gamemodes to the gamemode comboBox.
    foreach (BF4GameMode *gameMode, levels->getGameModes()) {
        ui->comboBox_ml_gameMode->addItem(gameMode->getName());
    }

    // Add the levels to the levels listWidget.
    foreach (BF4Level *level, levels->getLevels(1)) {
        ui->listWidget_ml_avaliable->addItem(level->getName());
    }

    /* Events */
    connect(con->commandHandler, SIGNAL(onDataSent(const QString&)), this, SLOT(onDataSent(const QString&)));
    connect(con->commandHandler, SIGNAL(onDataReceived(const QString&)), this, SLOT(onDataSent(const QString&)));
    connect(con->commandHandler, SIGNAL(onAuthenticated()), this, SLOT(onAuthenticated()));

    connect(con->commandHandler, SIGNAL(onPlayerAuthenticated(const QString&, const QString&)), this, SLOT(onPlayerAuthenticated(const QString&, const QString&)));
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
    connect(con->commandHandler, SIGNAL(onVersionCommand(const QString&, const int&, const QString&)), this, SLOT(onVersionCommand(const QString&, const int&, const QString&)));
    connect(con->commandHandler, SIGNAL(onAdminListPlayersCommand(const PlayerList&)), this, SLOT(onAdminListPlayersCommand(const PlayerList&)));
    connect(con->commandHandler, SIGNAL(onMapListListCommand(const QStringList&)), this, SLOT(onMapListListCommand(const QStringList&)));

    /* User Interface */
    connect(ui->comboBox_ml_gameMode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ml_gameMode_currentIndexChanged(int)));
    connect(ui->listWidget_ml_avaliable, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listWidget_ml_avaliable_currentItemChanged(QListWidgetItem*, QListWidgetItem*)));

    connect(ui->pushButton_ch_send, SIGNAL(clicked()), this, SLOT(pushButton_ch_send_clicked()));
    connect(ui->lineEdit_ch_input, SIGNAL(editingFinished()), this, SLOT(pushButton_ch_send_clicked()));

    connect(ui->pushButton_co_send, SIGNAL(clicked()), this, SLOT(pushButton_co_send_clicked()));
    connect(ui->lineEdit_co_input, SIGNAL(editingFinished()), this, SLOT(pushButton_co_send_clicked()));

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
}

void BF4Widget::logMessage(const int &type, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QTime::currentTime().toString());

    if (type == 0) { // Info
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 1) { // Error
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 2) { // Server send
        ui->textEdit_co_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 3) { // Server receive
        ui->textEdit_co_output->append(QString("%1 <span style=\"color:#0000FF\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 4) { // Chat
        ui->textEdit_ch_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 5) { // Punkbuster
        //ui->textEdit_co_pb_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    }
}

void BF4Widget::startupCommands() {
    con->sendCommand("admin.eventsEnabled true");
    con->sendCommand("version");
    con->sendCommand("serverInfo");
    con->sendCommand("admin.listPlayers all");
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

void BF4Widget::onAuthenticated()
{
    // Call commands on startup.
    startupCommands();

    // Find a better way to do this.
//    commandRefreshTimer = new QTimer(this);
//    connect(commandRefreshTimer, SIGNAL(timeout()), this, SLOT(refreshCommands()));
//    commandRefreshTimer->start(10000);
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
void BF4Widget::onVersionCommand(const QString &type, const int &buildId, const QString &version)
{
    Q_UNUSED(buildId);

    logMessage(0, tr("<b>%1</b> server running version: <b>%2</b>.").arg(type, version));
}

void BF4Widget::onAdminListPlayersCommand(const PlayerList &playerList)
{
    // Clear QTreeWidget
    ui->treeWidget_pl_playerList->clear();

    QStringList teamIds;
    QStringList playerNames;
    QMap<QString, QString> teamItems;
    QMap<QString, QTreeWidgetItem *> playerItems;

    foreach (PlayerListItem player, playerList) {
        QStringList playerInfo;
        QString teamId = player.value("teamId");
        int rank = QString(player.value("rank")).toInt();
        QString name = player.value("name");
        QString kills = player.value("kills");
        QString deaths = player.value("deaths");
        QString score = player.value("score");
        QString ping = player.value("ping");
        QString guid = player.value("guid");

        playerInfo.append(name);
        playerInfo.append(kills);
        playerInfo.append(deaths);
        playerInfo.append(score);
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

    teamIds.removeDuplicates();
    teamIds.sort();
    playerNames.sort();
    //menu_pl_move->clear();

    foreach (QString id, teamIds) {
        QTreeWidgetItem *team = new QTreeWidgetItem(ui->treeWidget_pl_playerList);
        QString teamName = tr("Team %1").arg(id);
        team->setText(0, teamName);
        foreach (QString name, playerNames) {
            QTreeWidgetItem *player = playerItems.value(name);
            if (id == player->data(0, Qt::UserRole)) {
                team->addChild(player);
            }
        }
    }

    // Expand all player rows
    ui->treeWidget_pl_playerList->expandAll();
}

void BF4Widget::onMapListListCommand(const QStringList &mapList)
{
    ui->listWidget_ml_current->addItems(mapList);
}

/* User Interface */
void BF4Widget::comboBox_ml_gameMode_currentIndexChanged(int index)
{
    ui->listWidget_ml_avaliable->clear();

    foreach (BF4Level *level, levels->getLevels(index)) {
        ui->listWidget_ml_avaliable->addItem(level->getName());
    }
}

void BF4Widget::listWidget_ml_avaliable_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    BF4Level *level = levels->getLevel(ui->comboBox_ml_gameMode->currentIndex(), ui->listWidget_ml_avaliable->currentRow());
    ui->label_ml_avaliable->setPixmap(level->getImage());
}

void BF4Widget::pushButton_ch_send_clicked()
{
    int type = ui->comboBox_ch_mode->currentIndex();

    QString message = ui->lineEdit_ch_input->text();
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

    ui->lineEdit_ch_input->clear();
}

void BF4Widget::pushButton_co_send_clicked()
{
    QString command = ui->lineEdit_co_input->text();
    ui->lineEdit_co_input->clear();

    con->sendCommand(command);
}

void BF4Widget::updatePlayerList()
{
    con->sendCommand("admin.listPlayers all");
}

QIcon BF4Widget::getRankIcon(const int &rank)
{
    return QIcon(QString(":/bf4/ranks/rank_%1.png").arg(rank));
}

QString BF4Widget::getSquadName(const int &id)
{
    return squadNameList.at(id - 1);
}
