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

#include "BFBC2Widget.h"

BFBC2Widget::BFBC2Widget(const QString &host, const int &port, const QString &password) : BFBC2(host, port, password), ui(new Ui::BFBC2)
{
    ui->setupUi(this);

    ui->label_op_so_bannerImage->hide();
    ui->spinBox_ch_duration->hide();

    ui->tableWidget_bl->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_rs->setContextMenuPolicy(Qt::CustomContextMenu);

    action_pl_sendmessage = new QAction(tr("Send message"), this);
    action_pl_stats = new QAction(tr("Stats"), this);
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
    menu_pl->addAction(action_pl_stats);
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

    // Adds all the commands to the commandList.
    commandList.append("login.plainText ");
    commandList.append("login.hashed");
    commandList.append("login.hashed ");
    commandList.append("logout");
    commandList.append("quit");
    commandList.append("version");
    commandList.append("listPlayers ");
    commandList.append("eventsEnabled ");
    commandList.append("help");
    commandList.append("admin.runscript ");
    commandList.append("punkBuster.pb_sv_command ");
    commandList.append("serverInfo");
    commandList.append("admin.yell ");
    commandList.append("admin.say ");
    commandList.append("admin.runNextRound");
    commandList.append("admin.restartRound");
    commandList.append("admin.endRound ");
    commandList.append("admin.runNextLevel");
    commandList.append("admin.restartMap");
    commandList.append("admin.currentLevel");
    commandList.append("mapList.nextLevelIndex");
    commandList.append("mapList.nextLevelIndex ");
    commandList.append("admin.supportedMaps ");
    commandList.append("admin.setPlaylist ");
    commandList.append("admin.getPlaylist");
    commandList.append("admin.getPlaylists");
    commandList.append("admin.kickPlayer ");
    commandList.append("admin.listPlayers ");
    commandList.append("admin.movePlayer ");
    commandList.append("admin.killPlayer ");
    commandList.append("vars.textChatModerationMode ");
    commandList.append("vars.textChatSpamTriggerCount ");
    commandList.append("vars.textChatSpamDetectionTime ");
    commandList.append("vars.textChatSpamCoolDownTime ");
    commandList.append("textChatModerationList.load");
    commandList.append("textChatModerationList.save");
    commandList.append("textChatModerationList.add ");
    commandList.append("textChatModerationList.remove ");
    commandList.append("textChatModerationList.clear");
    commandList.append("textChatModerationList.list");
    commandList.append("textChatModerationList.list ");
    commandList.append("banList.load");
    commandList.append("banList.save");
    commandList.append("banList.add ");
    commandList.append("banList.remove ");
    commandList.append("banList.clear");
    commandList.append("banList.list");
    commandList.append("banList.list ");
    commandList.append("reservedSlots.load");
    commandList.append("reservedSlots.save");
    commandList.append("reservedSlots.addPlayer ");
    commandList.append("reservedSlots.removePlayer ");
    commandList.append("reservedSlots.clear");
    commandList.append("reservedSlots.list");
    commandList.append("mapList.load");
    commandList.append("mapList.save");
    commandList.append("mapList.list");
    commandList.append("mapList.list ");
    commandList.append("mapList.clear");
    commandList.append("mapList.remove ");
    commandList.append("mapList.append ");
    commandList.append("mapList.insert ");
    commandList.append("vars.serverName");
    commandList.append("vars.serverName ");
    commandList.append("vars.adminPassword");
    commandList.append("vars.adminPassword ");
    commandList.append("vars.gamePassword");
    commandList.append("vars.gamePassword ");
    commandList.append("vars.punkBuster");
    commandList.append("vars.punkBuster ");
    commandList.append("vars.hardCore" );
    commandList.append("vars.hardCore ");
    commandList.append("vars.ranked");
    commandList.append("vars.ranked ");
    commandList.append("vars.rankLimit");
    commandList.append("vars.rankLimit ");
    commandList.append("vars.teamBalance");
    commandList.append("vars.teamBalance ");
    commandList.append("vars.friendlyFire");
    commandList.append("vars.friendlyFire ");
    commandList.append("vars.currentPlayerLimit");
    commandList.append("vars.currentPlayerLimit ");
    commandList.append("vars.maxPlayerLimit");
    commandList.append("vars.maxPlayerLimit ");
    commandList.append("vars.playerLimit");
    commandList.append("vars.playerLimit ");
    commandList.append("vars.bannerUrl");
    commandList.append("vars.bannerUrl ");
    commandList.append("vars.serverDescription");
    commandList.append("vars.serverDescription ");
    commandList.append("vars.killCam");
    commandList.append("vars.killCam ");
    commandList.append("vars.miniMap");
    commandList.append("vars.miniMap ");
    commandList.append("vars.crossHair");
    commandList.append("vars.crossHair ");
    commandList.append("vars.3dSpotting");
    commandList.append("vars.3dSpotting ");
    commandList.append("vars.miniMapSpotting");
    commandList.append("vars.miniMapSpotting ");
    commandList.append("vars.thirdPersonVehicleCameras");
    commandList.append("vars.thirdPersonVehicleCameras ");
    commandList.append("vars.teamKillCountForKick");
    commandList.append("vars.teamKillCountForKick ");
    commandList.append("vars.teamKillValueForKick");
    commandList.append("vars.teamKillValueForKick ");
    commandList.append("vars.teamKillValueIncrease");
    commandList.append("vars.teamKillValueIncrease ");
    commandList.append("vars.teamKillValueDecreasePerSecond");
    commandList.append("vars.teamKillValueDecreasePerSecond ");
    commandList.append("vars.idleTimeout");
    commandList.append("vars.idleTimeout ");
    commandList.append("vars.profanityFilter");
    commandList.append("vars.profanityFilter ");
    commandList.append("levelVars.set ");
    commandList.append("levelVars.get ");
    commandList.append("levelVars.evaluate ");
    commandList.append("levelVars.clear ");
    commandList.append("levelVars.list ");

    completer = new QCompleter(commandList, this);
    ui->lineEdit_co_co->setCompleter(completer);

    /* Connecting signals to slots */
    /* Messages and events */
    connect(con->commandHandler, SIGNAL(onDataSent(const QString&)), this, SLOT(onDataSent(const QString&)));
    connect(con->commandHandler, SIGNAL(onDataReceived(const QString&)), this, SLOT(onDataReceived(const QString&)));

    /* Events */
    connect(con->commandHandler, SIGNAL(onPlayerJoin(const QString&)), this, SLOT(onPlayerJoin(const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerAuthenticated(const QString&, const QString&)), this, SLOT(onPlayerAuthenticated(const QString&, const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerLeave(const QString&, const QString&)), this, SLOT(onPlayerLeave(const QString&, const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerSpawn(const QString&, const QString&, const QStringList&)), this, SLOT(onPlayerSpawn(const QString&, const QString&, const QStringList&)));
    connect(con->commandHandler, SIGNAL(onPlayerKill(const QString&, const QString&, const QString&, const bool&)), this, SLOT(onPlayerKill(const QString&, const QString&, const QString&, const bool&)));
    connect(con->commandHandler, SIGNAL(onPlayerChat(const QString&, const QString&, const QString&)), this, SLOT(onPlayerChat(const QString&, const QString&, const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerKicked(const QString&, const QString&)), this, SLOT(onPlayerKicked(const QString&, const QString&)));
    connect(con->commandHandler, SIGNAL(onPlayerSquadChange(const QString&, const int&, const int&)), this, SLOT(onPlayerSquadChange(const QString&, const int&, const int&)));
    connect(con->commandHandler, SIGNAL(onPlayerTeamChange(const QString&, const int&, const int&)), this, SLOT(onPlayerTeamChange(const QString&, const int&, const int&)));
    connect(con->commandHandler, SIGNAL(onPunkBusterMessage(const QString&)), this, SLOT(onPunkBusterMessage(const QString&)));
    connect(con->commandHandler, SIGNAL(onPunkBusterVersion(const QString&)), this, SLOT(onPunkBusterVersion(const QString&)));
    connect(con->commandHandler, SIGNAL(onServerLoadingLevel(const QString&, const int&, const int&)), this, SLOT(onServerLoadingLevel(const QString&, const int&, const int&)));
    connect(con->commandHandler, SIGNAL(onServerLevelStarted()), this, SLOT(onServerLevelStarted()));
    connect(con->commandHandler, SIGNAL(onServerRoundOver(const int&)), this, SLOT(onServerRoundOver(const int&)));
    connect(con->commandHandler, SIGNAL(onServerRoundOverPlayers(const QString&)), this, SLOT(onServerRoundOverPlayers(const QString&)));
    connect(con->commandHandler, SIGNAL(onServerRoundOverTeamScores(const QString&)), this, SLOT(onServerRoundOverTeamScores(const QString&)));

    // Commands
    connect(con->commandHandler, SIGNAL(onLoginHashedCommand()), this, SLOT(onLoginHashedCommand()));

    connect(con->commandHandler, SIGNAL(onServerInfoCommand(const QStringList&)), this, SLOT(onServerInfoCommand(const QStringList&)));
    connect(con->commandHandler, SIGNAL(onAdminListPlayersCommand(const PlayerList&)), this, SLOT(onAdminListPlayersCommand(const PlayerList&)));
    connect(con->commandHandler, SIGNAL(onVarsServerNameCommand(const QString&)), this, SLOT(onVarsServerNameCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsServerDescriptionCommand(const QString&)), this, SLOT(onVarsServerDescriptionCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsBannerUrlCommand(const QString&)), this, SLOT(onVarsBannerUrlCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsTextChatModerationModeCommand(const QString&)), this, SLOT(onVarsTextChatModerationModeCommand(const QString&)));
    connect(con->commandHandler, SIGNAL(onVarsTextChatSpamTriggerCountCommand(const int&)), this, SLOT(onVarsTextChatSpamTriggerCountCommand(const int&)));
    connect(con->commandHandler, SIGNAL(onVarsTextChatSpamDetectionTimeCommand(const int&)), this, SLOT(onVarsTextChatSpamDetectionTimeCommand(const int&)));
    connect(con->commandHandler, SIGNAL(onVarsTextChatSpamCoolDownTimeCommand(const int&)), this, SLOT(onVarsTextChatSpamCoolDownTimeCommand(const int&)));
    connect(con->commandHandler, SIGNAL(onMapListListCommand(const QStringList&)), this, SLOT(onMapListListCommand(const QStringList&)));
    connect(con->commandHandler, SIGNAL(onMapListNextLevelIndexCommand(const int&)), this, SLOT(onMapListNextLevelIndexCommand(const int&)));
    connect(con->commandHandler, SIGNAL(onBanListListCommand(const QStringList&)), this, SLOT(onBanListListCommand(const QStringList&)));
    connect(con->commandHandler, SIGNAL(onReservedSlotsListCommand(const QStringList&)), this, SLOT(onReservedSlotsListCommand(const QStringList&)));
    connect(con->commandHandler, SIGNAL(onVarsIdleTimeoutCommand(const int &)), this, SLOT(onVarsIdleTimeoutCommand(const int &)));
    //connect(con->commandHandler, SIGNAL(onMapListListRoundsCommand(QStringList)), this, SLOT(onCommandMapListListRoundsCommand(QStringList))); // TODO: Check this.

    /* User Interface */

    /* Options Tab */

    /* Server Options */
    connect(ui->lineEdit_op_so_serverName, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_serverName_editingFinished()));
    connect(ui->lineEdit_op_so_serverDescription, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_serverDescription_editingFinished()));
    connect(ui->lineEdit_op_so_bannerUrl, SIGNAL(editingFinished()), this, SLOT(lineEdit_op_so_bannerUrl_editingFinished()));

    /* Game Options */
    connect(ui->checkBox_op_go_3dSpotting, SIGNAL(clicked()), this, SLOT(checkbox_op_go_3dSpotting_clicked()));
    connect(ui->checkBox_op_go_crossHair, SIGNAL(clicked()), this, SLOT(checkbox_op_go_crossHair_clicked()));
    connect(ui->checkBox_op_go_friendlyFire, SIGNAL(clicked()), this, SLOT(checkbox_op_go_friendlyFire_clicked()));
    connect(ui->checkBox_op_go_hardcore, SIGNAL(clicked()), this, SLOT(checkbox_op_go_hardcore_clicked()));
    connect(ui->checkBox_op_go_killCam, SIGNAL(clicked()), this, SLOT(checkbox_op_go_killCam_clicked()));
    connect(ui->checkBox_op_go_miniMap, SIGNAL(clicked()), this, SLOT(checkbox_op_go_miniMap_clicked()));
    connect(ui->checkBox_op_go_miniMapSpotting, SIGNAL(clicked()), this, SLOT(checkbox_op_go_miniMapSpotting_clicked()));
    connect(ui->checkBox_op_go_teamBalance, SIGNAL(clicked()), this, SLOT(checkbox_op_go_teamBalance_clicked()));
    connect(ui->checkBox_op_go_thirdPersonVehicleCameras, SIGNAL(clicked()), this, SLOT(checkbox_op_go_thirdPersonVehicleCameras_clicked()));

    // Old.
    connect(ui->treeWidget_pl_players, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_pl_players_customContextMenuRequested(QPoint)));
    connect(ui->treeWidget_pl_players, SIGNAL(dragEvent()), this, SLOT(blockPlayerList()));
    connect(ui->treeWidget_pl_players, SIGNAL(dropEvent(const QString&, const QString&)), this, SLOT(slotChangePlayerTeam(const QString&, const QString&)));
    connect(ui->treeWidget_pl_players, SIGNAL(refresh()), this, SLOT(refreshPlayerList()));

    connect(action_pl_sendmessage, SIGNAL(triggered()), this, SLOT(action_pl_sendmessage_triggered()));
    connect(action_pl_stats, SIGNAL(triggered()), this, SLOT(action_pl_stats_triggered()));

    connect(action_pl_textchatmoderation_muted, SIGNAL(triggered()), this, SLOT(action_pl_textchatmoderation_muted_triggered()));
    connect(action_pl_textchatmoderation_normal, SIGNAL(triggered()), this, SLOT(action_pl_textchatmoderation_normal_triggered()));
    connect(action_pl_textchatmoderation_voice, SIGNAL(triggered()), this, SLOT(action_pl_textchatmoderation_voice_triggered()));
    connect(action_pl_textchatmoderation_admin, SIGNAL(triggered()), this, SLOT(action_pl_textchatmoderation_admin_triggered()));

    connect(action_pl_kill, SIGNAL(triggered()), this, SLOT(action_pl_kill_triggered()));
    connect(action_pl_kick_custom, SIGNAL(triggered()), this, SLOT(action_pl_kick_custom_triggered()));
    connect(action_pl_ban_byname, SIGNAL(triggered()), this, SLOT(action_pl_ban_byname_triggered()));
    connect(action_pl_reservedslots, SIGNAL(triggered()), this, SLOT(action_pl_reservedslots_triggered()));
    connect(action_pl_move, SIGNAL(triggered()), this, SLOT(slotMovePlayerTeam()));


    connect(ui->listWidget_ml_avaliablemaps, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listWidget_ml_avaliablemaps_currentItemChanged(QListWidgetItem*, QListWidgetItem*)));
    connect(ui->listWidget_ml_currentmaps, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem*)));
    connect(ui->listWidget_ml_currentmaps, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem*)));
    connect(ui->comboBox_ml_gamemode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ml_gamemode_currentIndexChanged(int)));
    connect(ui->listWidget_ml_currentmaps, SIGNAL(dropEvent(const QString&)), this, SLOT(slotAddMapToServer(const QString&)));
    connect(ui->listWidget_ml_avaliablemaps, SIGNAL(dropEvent(const QString&)), this, SLOT(slotRemoveMapFromServer(const QString&)));
    connect(ui->listWidget_ml_currentmaps, SIGNAL(sameDropEvent(int)), this, SLOT(playerListUpdate(int)));

    connect(ui->tableWidget_bl, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listWidget_bl_customContextMenuRequested(QPoint)));
    connect(action_bl_remove, SIGNAL(triggered()), this, SLOT(action_bl_remove_triggered()));

    connect(ui->lineEdit_ch, SIGNAL(returnPressed()), this, SLOT(on_pushButton_ch_send_clicked()));
    connect(ui->comboBox_ch_type, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ch_type_currentIndexChanged(int)));

    connect(action_rs_remove, SIGNAL(triggered()), this, SLOT(action_rs_remove_triggered()));
    connect(ui->listWidget_rs, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listWidget_rs_customContextMenuRequested(QPoint)));
    connect(ui->lineEdit_rs_player, SIGNAL(returnPressed()), this, SLOT(on_pushButton_rs_reserve_clicked()));

    connect(action_ic_remove, SIGNAL(triggered()), this, SLOT(action_ic_remove_triggered()));

    connect(ui->lineEdit_co_co, SIGNAL(returnPressed()), this, SLOT(on_pushButton_co_co_send_clicked()));
    connect(ui->lineEdit_co_pb, SIGNAL(returnPressed()), this, SLOT(on_pushButton_co_pb_send_clicked()));

}

BFBC2Widget::~BFBC2Widget()
{
    delete ui;
}

void BFBC2Widget::logMessage(const int &type, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QTime::currentTime().toString());

    if (type == 0) { // Info
        ui->textEdit_ev->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    } else if (type == 1) { // Error
        ui->textEdit_ev->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime, message));
    } else if (type == 2) { // Server send
        ui->textEdit_co_co->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    } else if (type == 3) { // Server receive
        ui->textEdit_co_co->append(QString("%1 <span style=\"color:#0000FF\">%2</span>").arg(currentTime, message));
    } else if (type == 4) { // Chat
        ui->textEdit_ch->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    } else if (type == 5) { // Punkbuster
        ui->textEdit_co_pb->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    }
}

/* Events */
void BFBC2Widget::onDataSent(const QString &command)
{
    logMessage(2, command);
}

void BFBC2Widget::onDataReceived(const QString &response)
{
    logMessage(3, response);
}

void BFBC2Widget::onPlayerJoin(const QString &player)
{
    logMessage(0, tr("Player <b>%1</b> joined the game.").arg(player));

    con->sendCommand("\"admin.listPlayers\" \"all\"");
}

void BFBC2Widget::onPlayerAuthenticated(const QString &player, const QString &guid)
{
    logMessage(0, tr("Player <b>%1</b> authenticated with GUID: <b>%2</b>.").arg(player).arg(guid));
}

void BFBC2Widget::onPlayerLeave(const QString &player, const QString &info)
{
    logMessage(0, tr("Player <b>%1</b> left the game.").arg(player).arg(info)); // TODO: Impelment score stuffs here?

    con->sendCommand("\"admin.listPlayers\" \"all\"");
}

void BFBC2Widget::onPlayerSpawn(const QString &player, const QString &kit, const QStringList &weaponList)
{
    logMessage(0, tr("Player <b>%1</b> spawned as <b>%2</b> and with <b>%3</b>, <b>%4</b> and <b>%5</b> selected.").arg(player).arg(kit).arg(weaponList.at(0)).arg(weaponList.at(1)).arg(weaponList.at(2))); // TODO: Implement dynamic length on selected weapons.
}

void BFBC2Widget::onPlayerKill(const QString &killer, const QString &victim, const QString &weapon, const bool &headshot)
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

void BFBC2Widget::onPlayerChat(const QString &player, const QString &message, const QString &target)
{
    Q_UNUSED(target)

    logMessage(4, tr("<b>%2</b>: %3").arg(player).arg(message));
}

void BFBC2Widget::onPlayerKicked(const QString &player, const QString &reason)
{
    logMessage(0, tr("Player <b>%1</b> was kicked from the game, the reason was: <b>%2</b>.").arg(player).arg(reason));
}

void BFBC2Widget::onPlayerSquadChange(const QString &player, const int &teamId, const int &squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logMessage(0, tr("Player <b>%1</b> changed squad to <b>%3</b>.").arg(player).arg(getSquadName(squadId)));
    }
}

void BFBC2Widget::onPlayerTeamChange(const QString &player, const int &teamId, const int &squadId)
{
    Q_UNUSED(squadId);

    logMessage(0, tr("Player <b>%1</b> changed team to <b>%2</b>.").arg(player).arg(teamId));
}

void BFBC2Widget::onPunkBusterMessage(const QString &message)
{
    logMessage(5, message);
}

void BFBC2Widget::onPunkBusterVersion(const QString &version)
{
    logMessage(5, version);
}

void BFBC2Widget::onServerLoadingLevel(const QString &levelName, const int &roundsPlayed, const int &roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    logMessage(0, tr("Loading level: <b>%1</b>").arg(levelName)); // TODO: Transelate internal level name to human readable.
}

void BFBC2Widget::onServerLevelStarted()
{
    logMessage(0, tr("Level started"));
}

void BFBC2Widget::onServerRoundOver(const int &winningTeamId)
{
    logMessage(0, tr("The round has just ended, and <b>%1</b> won").arg(winningTeamId));
}

void BFBC2Widget::onServerRoundOverPlayers(const QString &playerInfo)
{
    logMessage(0, tr("The round has just ended, and <b>%1</b> is the final detailed player stats").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void BFBC2Widget::onServerRoundOverTeamScores(const QString &teamScores)
{
    logMessage(0, tr("The round has just ended, and <b>%1</b> is the final ticket/kill/life count for each team").arg(teamScores));
}

void BFBC2Widget::onLoginHashedCommand()
{
    // Call commands on startup.
    startupCommands();
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
    LevelEntry level = levels->getLevel(serverInfo.at(4));
    GameModeEntry gameMode = levels->getGameMode(serverInfo.at(3));

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
    ui->label_ml_currentmap_image->setPixmap(level.image);
}

void BFBC2Widget::onAdminListPlayersCommand(const PlayerList &playerList)
{
    // Clear QTreeWidget
    ui->treeWidget_pl_players->clear();

    QStringList teamIds;
    QStringList playerNames;
    QMap<QString, QString> teamItems;
    QMap<QString, QTreeWidgetItem *> playerItems;

    foreach (PlayerListItem player, playerList) {
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

    foreach (QString id, teamIds) {
        QTreeWidgetItem *team = new QTreeWidgetItem(ui->treeWidget_pl_players);
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
    foreach (QString engineName, mapList) {
        LevelEntry level = levels->getLevel(engineName);

        ui->listWidget_ml_currentmaps->addItem(level.name);
    }

    // Sets nextMap
//    if (nextLevelIndex >= 0 && mapList.count() > 0) {
//        LevelEntry level = levels->getLevel(mapList.at(nextLevelIndex));

//        ui->label_ml_nextmap_name->setText(level.name);
//        ui->label_ml_nextmap_image->setPixmap(level.image);
//    }
}

void BFBC2Widget::onMapListNextLevelIndexCommand(const int &index)
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

void BFBC2Widget::onVarsTextChatSpamTriggerCountCommand(const int &count)
{
    ui->spinBox_op_tcm_spamtriggercount->setValue(count);
}

void BFBC2Widget::onVarsTextChatSpamDetectionTimeCommand(const int &count)
{
    ui->spinBox_op_tcm_spamdetectiontime->setValue(count);
}

void BFBC2Widget::onVarsTextChatSpamCoolDownTimeCommand(const int &count)
{
    ui->spinBox_op_tcm_spamcooldowntime->setValue(count);
}

void BFBC2Widget::onVarsIdleTimeoutCommand(const int &seconds)
{
    ui->spinBox_op_gpo_idleTimeout->setValue(seconds);
}

void BFBC2Widget::startupCommands()
{
    con->sendCommand("\"eventsEnabled\" \"true\"");
    con->sendCommand("version");

    con->sendCommand("serverInfo");
    con->sendCommand("\"admin.listPlayers\" \"all\"");

    con->sendCommand("vars.serverName");
    con->sendCommand("vars.serverDescription");
    con->sendCommand("vars.bannerUrl");

//    con->sendCommand("vars.idleTimeout");

//    con->sendCommand("vars.textChatModerationMode");
//    con->sendCommand("vars.textChatSpamTriggerCount");
//    con->sendCommand("vars.textChatSpamDetectionTime");
//    con->sendCommand("vars.textChatSpamCoolDownTime");

    con->sendCommand("mapList.list");

    con->sendCommand("banList.list");
    con->sendCommand("reservedSlots.list");
}

// Player
void BFBC2Widget::treeWidget_pl_players_customContextMenuRequested(QPoint pos)
{
    if (ui->treeWidget_pl_players->itemAt(pos)) {
        // Something crash here.
        QString hideTeam = ui->treeWidget_pl_players->itemAt(pos)->parent()->text(0);
        foreach (QAction *team, menu_pl_move->actions()) {
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

void BFBC2Widget::action_pl_stats_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    QDesktopServices::openUrl(QUrl(PLAYER_STATS_URL + player));
}

void BFBC2Widget::action_pl_kill_triggered()
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);
    killPlayer(player);
}

void BFBC2Widget::action_pl_textchatmoderation_muted_triggered() // Get this work
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"muted\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_normal_triggered() // Get this work
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"normal\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_voice_triggered() // Get this work
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"voice\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_admin_triggered() // Get this work
{
    QString player = ui->treeWidget_pl_players->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"admin\" \"%1\"").arg(player));
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
        con->sendCommand(QString("\"reservedSlots.addPlayer\" \"%1\"").arg(player));
        con->sendCommand("reservedSlots.list");
    }
}

/* Options Tab */
void BFBC2Widget::lineEdit_op_so_serverName_editingFinished()
{
    QString serverName = ui->lineEdit_op_so_serverName->text();

    if (!serverName.isEmpty()) {
        con->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(serverName));
    }
}

void BFBC2Widget::lineEdit_op_so_serverDescription_editingFinished()
{
    QString serverDescription = ui->lineEdit_op_so_serverDescription->text();

    if (!serverDescription.isEmpty()) {
        con->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(serverDescription));
    }
}

void BFBC2Widget::lineEdit_op_so_bannerUrl_editingFinished()
{
    QString bannerUrl = ui->lineEdit_op_so_bannerUrl->text();

    if (!bannerUrl.isEmpty()) {
        con->sendCommand(QString("\"vars.bannerUrl\" \"%1\"").arg(bannerUrl));
        ui->label_op_so_bannerImage->setPixmap(QPixmap(bannerUrl));
        ui->label_op_so_bannerImage->show();
    }
}

/* Game Options */

void BFBC2Widget::checkbox_op_go_3dSpotting_clicked()
{
    con->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(ui->checkBox_op_go_3dSpotting->isChecked()));
}

void BFBC2Widget::checkbox_op_go_crossHair_clicked()
{
    con->sendCommand(QString("\"vars.crossHair\" \"%1\"").arg(ui->checkBox_op_go_crossHair->isChecked()));
}

void BFBC2Widget::checkbox_op_go_friendlyFire_clicked()
{
    con->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(ui->checkBox_op_go_friendlyFire->isChecked()));
}

void BFBC2Widget::checkbox_op_go_hardcore_clicked()
{
    con->sendCommand(QString("\"vars.hardCore\" \"%1\"").arg(ui->checkBox_op_go_hardcore->isChecked()));
}

void BFBC2Widget::checkbox_op_go_killCam_clicked()
{
    con->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(ui->checkBox_op_go_killCam->isChecked()));
}

void BFBC2Widget::checkbox_op_go_miniMap_clicked()
{
    con->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(ui->checkBox_op_go_miniMap->isChecked()));
}

void BFBC2Widget::checkbox_op_go_miniMapSpotting_clicked()
{
    con->sendCommand(QString("\"vars.miniMapSpotting\" \"%1\"").arg(ui->checkBox_op_go_miniMapSpotting->isChecked()));
}

void BFBC2Widget::checkbox_op_go_teamBalance_clicked()
{
    con->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(ui->checkBox_op_go_teamBalance->isChecked()));
}

void BFBC2Widget::checkbox_op_go_thirdPersonVehicleCameras_clicked()
{
    con->sendCommand(QString("\"vars.thirdPersonVehicleCameras\" \"%1\"").arg(ui->checkBox_op_go_thirdPersonVehicleCameras->isChecked()));
}

/* Text Chat Moderation */
void BFBC2Widget::on_radioButton_op_tcm_free_clicked()
{
    con->sendCommand(QString("\"vars.textChatModerationMode\" \"free\""));
}

void BFBC2Widget::on_radioButton_op_tcm_moderated_clicked()
{
    con->sendCommand(QString("\"vars.textChatModerationMode\" \"moderated\""));
}

void BFBC2Widget::on_radioButton_op_tcm_muted_clicked()
{
    con->sendCommand(QString("\"vars.textChatModerationMode\" \"muted\""));
}

void BFBC2Widget::on_pushButton_so_tcm_spamtriggercount_clicked()
{
    QString count = QString(ui->spinBox_op_tcm_spamtriggercount->value());

    con->sendCommand(QString("\"vars.textChatSpamTriggerCount\" \"%1\"").arg(count));
}

void BFBC2Widget::on_pushButton_so_tcm_spamdetectiontime_clicked()
{
    QString count = QString(ui->spinBox_op_tcm_spamdetectiontime->value());

    con->sendCommand(QString("\"vars.textChatSpamDetectionTime\" \"%1\"").arg(count));
}

void BFBC2Widget::on_pushButton_so_tcm_spamcooldowntime_clicked()
{
    QString count = QString(ui->spinBox_op_tcm_spamcooldowntime->value());

    con->sendCommand(QString("\"vars.textChatSpamCoolDownTime\" \"%1\"").arg(count));
}

/* Gamplay Options */
void BFBC2Widget::on_spinBox_op_gpo_idleTimeout_editingFinished()
{
    int timeout = ui->spinBox_op_gpo_idleTimeout->value();

    con->sendCommand(QString("\"vars.idleTimeout\" \"%1\"").arg(timeout));
}

// Maplist
void BFBC2Widget::comboBox_ml_gamemode_currentIndexChanged(int index)
{
    // Stop the current item changed signal from being emitted
    ui->listWidget_ml_avaliablemaps->blockSignals(true);
    ui->listWidget_ml_avaliablemaps->clear();
    ui->listWidget_ml_avaliablemaps->blockSignals(false);

    // get a list of map names
    QStringList mapNames = levels->getLevelNames(index);

    // add the maps with the correct modd to avaliable maps
    ui->listWidget_ml_avaliablemaps->addItems(mapNames);
    ui->label_ml_previewmap_image->clear();

    //    int rounds = ui->spinBox_ml_rounds->value();

    //    QStringList mapPaths;
    //    for (int i = 0; i < ui->listWidget_ml_currentmaps->count (); i++) {
    //        mapPaths << ui->listWidget_ml_currentmaps->item (i)->data (Qt::UserRole).toString ();
    //    }

    //    con->sendCommand (QString("mapList.clear"));
    //    foreach (QString mapPath, mapPaths) {
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
    LevelEntry level = levels->getLevel(index, gameModeIndex);

    ui->label_ml_previewmap_image->setPixmap(level.image);
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
            con->sendCommand(QString("\"admin.setPlaylist\" \"%1\"").arg(gamemodes[gameModeIndex]));
            con->sendCommand("\"mapList.clear\"");

        } else {
            delete ui->listWidget_ml_currentmaps->takeItem(ui->listWidget_ml_currentmaps->count());
        }
    }

    commandRefreshTimer->blockSignals(false);

    // get selected map
    int avaliableMapIndex = ui->listWidget_ml_avaliablemaps->currentIndex().row();
    int rounds = ui->spinBox_ml_rounds->value();
    LevelEntry level = levels->getLevel(avaliableMapIndex, gameModeIndex);

    // create a new map item and insert it into current map list
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget_ml_currentmaps);
    item->setText(level.name);
    item->setData (Qt::UserRole, level.engineName);
    ui->listWidget_ml_currentmaps->addItem(item);

    // append the map to the server map list
    con->sendCommand(QString("\"mapList.append\" \"%1\" \"%2\"").arg(level.engineName).arg(rounds));

    if (ret == QMessageBox::Yes) {
       con->sendCommand("\"mapList.save\"");
       con->sendCommand("\"mapList.nextLevelIndex\" \"0\"");
       con->sendCommand("\"admin.runNextLevel\"");
    }

    con->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2Widget::on_pushButton_ml_remove_clicked()
{
    // find selected map in current map list
    int removedMap = ui->listWidget_ml_currentmaps->currentRow();

    //remove map from server map list
    con->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(removedMap));

    // stop the current item changed signal from being emitted
    ui->listWidget_ml_currentmaps->blockSignals(true);
    delete ui->listWidget_ml_currentmaps->takeItem(removedMap);
    ui->listWidget_ml_currentmaps->blockSignals(false);
}

void BFBC2Widget::on_pushButton_ml_restart_clicked()
{
    con->sendCommand("\"admin.restartRound\"");
}

void BFBC2Widget::on_pushButton_ml_run_clicked()
{
    con->sendCommand("\"admin.runNextLevel\"");
}

void BFBC2Widget::on_pushButton_ml_clear_clicked()
{
    con->sendCommand("\"mapList.clear\"");
}

void BFBC2Widget::listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem *current)
{
    Q_UNUSED(current);

    int index = ui->listWidget_ml_currentmaps->currentRow();
    int gameModeIndex = gamemodes.indexOf(QRegExp(currentGamemode, Qt::CaseInsensitive));

    LevelEntry level = levels->getLevel(index, gameModeIndex);

    ui->label_ml_previewmap_image->setPixmap(level.image);
    con->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2Widget::on_pushButton_ml_save_clicked()
{
    con->sendCommand("\"mapList.save\"");
}

// BanList
void BFBC2Widget::listWidget_bl_customContextMenuRequested(QPoint pos)
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
    con->sendCommand("\"banList.clear\"");
}

void BFBC2Widget::on_pushButton_bl_save_clicked()
{
    con->sendCommand("\"banList.save\"");
}

// Reserved slots
void BFBC2Widget::listWidget_rs_customContextMenuRequested(QPoint pos)
{
    if (ui->listWidget_rs->itemAt(pos)) {
        menu_rs->exec(QCursor::pos());
    }
}

void BFBC2Widget::action_rs_remove_triggered()
{
    QString player = ui->listWidget_rs->currentItem()->text();

    if (!player.isEmpty()) {
        con->sendCommand(QString("\"reservedSlots.removePlayer\" \"%1\"").arg(player));
        con->sendCommand("reservedSlots.list");
    }
}

void BFBC2Widget::on_pushButton_rs_reserve_clicked()
{
    QString player = ui->lineEdit_rs_player->text().trimmed();

    if (!player.isEmpty()) {
        con->sendCommand(QString("\"reservedSlots.addPlayer\" \"%1\"").arg(player));
        con->sendCommand("reservedSlots.list");
        ui->lineEdit_rs_player->clear();
    }
}

void BFBC2Widget::on_pushButton_rs_save_clicked()
{
    con->sendCommand("reservedSlots.save");
}

void BFBC2Widget::on_pushButton_rs_clear_clicked()
{
    con->sendCommand("reservedSlots.clear");
    con->sendCommand("reservedSlots.list");
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
        con->sendCommand(cmd);
        ui->lineEdit_co_co->clear();
    }
}

void BFBC2Widget::on_pushButton_co_pb_send_clicked()
{
    QString cmd = ui->lineEdit_co_pb->text();

    if (!cmd.isEmpty()) {
        con->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(cmd));
        ui->lineEdit_co_pb->clear();
    }
}

void BFBC2Widget::slotChangePlayerTeam(const QString &player, const QString &altTeam)
{
    movePlayer(player, altTeam, "0", "true");
}

void BFBC2Widget::refreshPlayerList()
{
    con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    connect(con->commandHandler, SIGNAL(onplayerListChange()), this, SLOT(slotPlayerListChange())); // TODO: Change to adminListPlayersAll
}

void BFBC2Widget::playerListUpdate(int oldRow)
{

    QString rounds = mapListU[2*oldRow+1];
    con->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(oldRow));

    int index = ui->listWidget_ml_currentmaps->currentRow();
    int gameModeIndex = ui->comboBox_ml_gamemode->currentIndex();

    LevelEntry level = levels->getLevel(index, gameModeIndex);

    // get a list of map mods and map names and select all map names with a particular mod
//    QStringList mapNames = levelsObject->levels().at(gameModeIndex)->mapNames();
//    QStringList mapPaths = levelsObject->levels().at(gameModeIndex)->mapPaths();

//    // Find map name and map path for selected map
//    int avaliableMapIndex = mapNames.indexOf(mapName);
//    QString mapPath = mapPaths.at(avaliableMapIndex);

    // Append the map to the server map list
    con->sendCommand(QString("\"mapList.insert\" \"%1\" \"%2\" \"%3\"").arg(index).arg(level.engineName).arg(rounds));

    con->sendCommand("\"mapList.list\" \"rounds\"");
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

        if (ret == QMessageBox::Yes)
        {
            con->sendCommand(QString("\"admin.setPlaylist\" \"%1\"").arg(gamemodes[gameModeIndex]));
            con->sendCommand("\"mapList.clear\"");

        }
        else
        {
            delete ui->listWidget_ml_currentmaps->takeItem(ui->listWidget_ml_currentmaps->count()-1);
        }
    }

    commandRefreshTimer->blockSignals(false);
    // get a list of map mods and map names and select all map names with a particular mod
//    QStringList mapNames = levelsObject->levels().at(gameModeIndex)->mapNames();
//    QStringList mapPaths = levelsObject->levels().at(gameModeIndex)->mapPaths();

//    // find map name and map path for selected map
//    int avaliableMapIndex = mapNames.indexOf(mapName);
//    QString mapPath = mapPaths.at(avaliableMapIndex);

    int index = ui->listWidget_ml_avaliablemaps->currentRow();

    LevelEntry level = levels->getLevel(index, gameModeIndex);

    // get the amount of rounds from combo box
    int rounds = ui->spinBox_ml_rounds->value();

    // append the map to the server map list
    con->sendCommand(QString("\"mapList.append\" \"%1\" \"%2\"").arg(level.engineName).arg(rounds));


    if (ret == QMessageBox::Yes)
    {

        con->sendCommand("\"mapList.save\"");
        con->sendCommand("\"mapList.nextLevelIndex\" \"0\"");
        con->sendCommand("\"admin.runNextLevel\"");

    }
    con->sendCommand("\"mapList.list\" \"rounds\"");

}

void BFBC2Widget::slotRemoveMapFromServer(const QString &mapName)
{
    Q_UNUSED(mapName);

    // find selected map in current map list
    int removedMap = ui->listWidget_ml_currentmaps->currentRow();

    //remove map from server map list
    con->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(removedMap));

    // fix to stop the drag event from creating a duplicate map item in avaliable maps
    int cRemovedMap = ui->listWidget_ml_avaliablemaps->count();
    cRemovedMap--;
    delete ui->listWidget_ml_avaliablemaps->takeItem(cRemovedMap);

    // stop the current item changed signal from being emitted
    ui->listWidget_ml_currentmaps->blockSignals(true);
    delete ui->listWidget_ml_currentmaps->takeItem(removedMap);
    ui->listWidget_ml_currentmaps->blockSignals(false);
    con->sendCommand("\"mapList.list\" \"rounds\"");
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
        con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    }
}

void BFBC2Widget::setMapList(const QString &gamemode)
{
    int gameModeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gameModeIndex != -1) {
        QStringList mapNames = levels->getLevelNames(gameModeIndex);

        ui->listWidget_ml_avaliablemaps->clear();
        ui->listWidget_ml_avaliablemaps->addItems(mapNames);
    }
}

void BFBC2Widget::on_pushButton_rs_load_clicked()
{
    con->sendCommand("reservedSlots.load");
    con->sendCommand("reservedSlots.list");
}
