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

#include "BFBC2.h"

BFBC2::BFBC2(const QString &host, const int &port, const QString &password) : ui(new Ui::BFBC2), host(host), port(port), password(password)
{
    ui->setupUi(this);

    con = new BFBC2Connection(this);
    connect(con->commandSignals(), SIGNAL(refresh()), this, SLOT(slotRefreshCommands()));
    connect(con->commandSignals(), SIGNAL(logMessage(const QString&, const QString&)), this, SLOT(slotLogMessage(const QString&, const QString&)));
    connect(con->commandSignals(), SIGNAL(logEvents(const QString&, const QString&)), this, SLOT(slotLogEvents(const QString&, const QString&)));
    connect(con->commandSignals(), SIGNAL(ingameCommands(const QString&, const QString&)), this, SLOT(slotIngameCommands(const QString&, const QString&)));
    connect(con->commandSignals(), SIGNAL(startConnection()), this, SLOT(slotStartConnection()));
    connect(con->commandSignals(), SIGNAL(gotSalt(const QByteArray&)), this, SLOT(slotGotSalt(const QByteArray&)));
    connect(con->commandSignals(), SIGNAL(authenticated()), this, SLOT(slotAuthenticated()));
    connect(con->commandSignals(), SIGNAL(playerListChange()), this, SLOT(slotPlayerListChange())); // TODO: Change to adminListPlayersAll

    // Events
    connect(con->commandSignals(), SIGNAL(eventOnSpawn(const QString&, const QString&)), this, SLOT(slotEventOnSpawn(const QString&, const QString&)));

    // Commands
    connect(con->commandSignals(), SIGNAL(commandServerInfo(QStringList)), this, SLOT(slotCommandServerInfo(QStringList)));
    connect(con->commandSignals(), SIGNAL(commandVarsTextChatModerationMode(const QString&)), this, SLOT(slotCommandVarsTextChatModerationMode(const QString&)));
    connect(con->commandSignals(), SIGNAL(commandVarsTextChatSpamTriggerCount(const QString&)), this, SLOT(slotCommandVarsTextChatSpamTriggerCount(const QString&)));
    connect(con->commandSignals(), SIGNAL(commandVarsTextChatSpamDetectionTime(const QString&)), this, SLOT(slotCommandVarsTextChatSpamDetectionTime(const QString&)));
    connect(con->commandSignals(), SIGNAL(commandVarsTextChatSpamCoolDownTime(const QString&)), this, SLOT(slotCommandVarsTextChatSpamCoolDownTime(const QString&)));
    connect(con->commandSignals(), SIGNAL(commandBanListList(QStringList)), this, SLOT(slotCommandBanListList(QStringList)));
    connect(con->commandSignals(), SIGNAL(commandReservedSlotsList(QStringList)), this, SLOT(slotCommandReservedSlotsList(QStringList)));
    connect(con->commandSignals(), SIGNAL(commandMapListNextLevelIndex(int&)), this, SLOT(slotCommandMapListNextLevelIndex(int&)));
    connect(con->commandSignals(), SIGNAL(commandMapListList(QStringList)), this, SLOT(slotCommandMapListList(QStringList)));
    connect(con->commandSignals(), SIGNAL(commandMapListListRounds(QStringList)), this, SLOT(slotCommandMapListListRounds(QStringList)));
    connect(con->commandSignals(), SIGNAL(commandVarsServerName(const QString&)), this, SLOT(slotCommandVarsServerName(const QString&)));
    connect(con->commandSignals(), SIGNAL(commandVarsServerDescription(const QString&)), this, SLOT(slotCommandVarsServerDescription(const QString&)));
    connect(con->commandSignals(), SIGNAL(commandVarsBannerUrl(const QString&)), this, SLOT(slotCommandVarsBannerUrl(const QString&)));

    con->hostConnect(host, port);

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

    ui->treeWidget_pl->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget_bl->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_rs->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_ic->setContextMenuPolicy(Qt::CustomContextMenu);

    // Hide the comboBox_ch_duration
    ui->comboBox_ch_duration->hide();

    comList = new BFBC2CommandList(this);
    completer = new QCompleter(comList->commandList, this);
    ui->lineEdit_co_co_input->setCompleter(completer);

    gamemodes << "RUSH" << "CONQUEST" << "SQRUSH" << "SQDM";

    connect(ui->treeWidget_pl, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_pl_customContextMenuRequested(QPoint)));
    connect(ui->treeWidget_pl, SIGNAL(dragEvent()), this, SLOT(blockPlayerList()));
    connect(ui->treeWidget_pl, SIGNAL(dropEvent(const QString&, const QString&)), this, SLOT(slotChangePlayerTeam(const QString&, const QString&)));
    connect(ui->treeWidget_pl, SIGNAL(refresh()), this, SLOT(refreshPlayerList()));

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

    connect(ui->listWidget_ml_avaliablemaps, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listWidget_ml_avaliablemaps_currentItemChanged(QListWidgetItem*, QListWidgetItem*)));
    connect(ui->listWidget_ml_currentmaps, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem*)));
    connect(ui->listWidget_ml_currentmaps, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem*)));
    connect(ui->comboBox_ml_gamemode, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ml_gamemode_currentIndexChanged(int)));
    connect(ui->listWidget_ml_currentmaps, SIGNAL(dropEvent(const QString&)), this, SLOT(slotAddMapToServer(const QString&)));
    connect(ui->listWidget_ml_avaliablemaps, SIGNAL(dropEvent(const QString&)), this, SLOT(slotRemoveMapFromServer(const QString&)));
    connect(ui->listWidget_ml_currentmaps, SIGNAL(sameDropEvent(int)), this, SLOT(playerListUpdate(int)));

    connect(ui->tableWidget_bl, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listWidget_bl_customContextMenuRequested(QPoint)));
    connect(action_bl_remove, SIGNAL(triggered()), this, SLOT(action_bl_remove_triggered()));

    connect(ui->lineEdit_ch_input, SIGNAL(returnPressed()), this, SLOT(on_pushButton_ch_send_clicked()));
    connect(ui->comboBox_ch_type, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_ch_type_currentIndexChanged(int)));

    connect(action_rs_remove, SIGNAL(triggered()), this, SLOT(action_rs_remove_triggered()));
    connect(ui->listWidget_rs, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listWidget_rs_customContextMenuRequested(QPoint)));
    connect(ui->lineEdit_rs_player, SIGNAL(returnPressed()), this, SLOT(on_pushButton_rs_reserve_clicked()));

    connect(ui->listWidget_ic, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listWidget_ic_customContextMenuRequested(QPoint)));
    connect(action_ic_remove, SIGNAL(triggered()), this, SLOT(action_ic_remove_triggered()));

    connect(ui->lineEdit_co_co_input, SIGNAL(returnPressed()), this, SLOT(on_pushButton_co_co_send_clicked()));
    connect(ui->lineEdit_co_pb_input, SIGNAL(returnPressed()), this, SLOT(on_pushButton_co_pb_send_clicked()));

    gameModeCode << "RUSH" << "CONQUEST" << "SQRUSH" << "SQDM";

    levelsObject = 0;
}

BFBC2::~BFBC2()
{
    delete ui;
    delete con;
    delete levelsObject;
    delete comList;
}

void BFBC2::readSettings()
{
    QStringList users;
    settings->beginGroup(SETTINGS_INGAMECOMMANDS);
        int size = settings->beginReadArray(SETTINGS_INGAMECOMMANDS_USERS);
            for (int i = 0; i < size; i++) {
                settings->setArrayIndex(i);
                    users << settings->value("User").toString();
            }
        settings->endArray();
    settings->endGroup();

    qDebug() << "readSettings() got this:" << users;
    ui->listWidget_ic->addItems(users);


}

void BFBC2::writeSettings()
{

}

void BFBC2::slotLogMessage(const QString &type, const QString &msg)
{
    QTime time;
    QString currentTime = QString("[%1]").arg(time.currentTime().toString());

    if (type == "error") {
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime, msg));
    } else if (type == "info") {
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, msg));
    } else if (type == "server_send") {
        ui->textEdit_co_co_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, msg));
    } else if (type == "server_receive") {
        ui->textEdit_co_co_output->append(QString("%1 <span style=\"color:#0000FF\">%2</span>").arg(currentTime, msg));
    } else if (type == "chat") {
        ui->textEdit_ch_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, msg));
    } else if (type == "pb") {
        ui->textEdit_co_pb_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, msg));
    } else {
        ui->textEdit_co_co_output->append(QString("%1 %2").arg(currentTime, msg));
    }

    qDebug() << msg;
}

void BFBC2::slotLogEvents(const QString &event, const QString &msg)
{
    Q_UNUSED(event);
    Q_UNUSED(msg);
}

void BFBC2::slotIngameCommands(const QString &player, const QString &cmd)
{
    QStringList users;

    if (users.contains(player)) {
        QString stringCmd = cmd;
        QStringList cmdList;
        cmdList = stringCmd.replace("&quot;", "\"").split(QRegExp(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));
        cmdList.replaceInStrings("\"", "");

        QString command = cmdList.first();

        if (command == "!kill") {
            killPlayer(cmdList.at(1));
        } else if (command == "!kick") {
            kickPlayer(cmdList.at(1), 0);
        } else if (command == "!ban") {
            banPlayer("name", cmdList.at(1), "perm", "Banned by administrator.");
        } else if (command == "!unban") {
            unbanPlayer("name", cmdList.at(1));
        } else if (command == "!restartmap") {
            con->sendCommand("\"admin.restartMap\"");
        } else if (command == "!nextmap") {
            con->sendCommand("\"admin.runNextLevel\"");
        } else if (command == "!yell") {
            sendYellMessage(cmdList.at(1), "5", "all", 0, 0);
        } else if (command == "!say") {
            sendSayMessage(cmdList.at(1), "all", 0, 0);
        } else if (command == "!move") { // Not finished.
            //con->sendCommand(QString("admin.movePlayer %1").arg(value));
        }
    }
}

void BFBC2::slotStartConnection()
{
    if (!con->isAuthenticated()) {        
        con->sendCommand("\"login.hashed\"");
    }
}

void BFBC2::slotGotSalt(const QByteArray &salt)
{
    if (!con->isAuthenticated()) {
        if (!password.isEmpty()) {
            authenticate(password.toUtf8().constData(), salt); // Check this, originally authenticate(password.toUtf8().constData(), salt);
        }
    }
}

void BFBC2::slotAuthenticated()
{   
    // Call commands on startup.
    slotStartupCommands();

    // Find a better way to do this.
    commandRefreshTimer = new QTimer(this);
    connect(commandRefreshTimer, SIGNAL(timeout()), this, SLOT(slotRefreshCommands()));
    commandRefreshTimer->start(10000);
}

void BFBC2::slotPlayerListChange()
{
    qDebug() << "slotPlayerListChange called!";
    PlayerList list = con->getPlayerList();

    // Clear QTreeWidget
    ui->treeWidget_pl->clear();

    QStringList teamIds;
    QStringList playerNames;
    QMap<QString, QString> teamItems;
    QMap<QString, QTreeWidgetItem *> playerItems;
    foreach (PlayerListItem playerItem, list) {
        QStringList playerInfo;
        QString teamId = playerItem["teamId"];
        QString clanTag = playerItem["clanTag"];
        QString playerName = playerItem["name"];
        QString kills = playerItem["kills"];
        QString deaths = playerItem["deaths"];
        QString score = playerItem["score"];
        QString ping = playerItem["ping"];
        QString guid = playerItem["guid"];

        playerInfo.append(clanTag);
        playerInfo.append(playerName);
        playerInfo.append(kills);
        playerInfo.append(deaths);
        playerInfo.append(score);
        playerInfo.append(ping);
        playerInfo.append(guid);

        playerNames.append(playerName);

        // add player to parent teamItem
        QTreeWidgetItem *item = new QTreeWidgetItem(playerInfo);
        item->setData(0, Qt::UserRole, teamId);
        playerItems.insert(playerName, item);

        // add team item and team id into map with key player name
        teamItems.insert(playerName, teamId);
        teamIds.append(teamId);
    }

    teamIds.removeDuplicates();

    teamIds.sort();
    playerNames.sort();
    menu_pl_move->clear();
    foreach (QString id, teamIds) {
        QTreeWidgetItem *team = new QTreeWidgetItem(ui->treeWidget_pl);
        QString teamName = tr("Team %1").arg(id);
        team->setText(0, teamName);
        foreach (QString name, playerNames) {
            QTreeWidgetItem *player = playerItems.value(name);
            if (id == player->data(0, Qt::UserRole)) {
                team->addChild(player);
            }
        }
    }

    QAction *teamAction = new QAction("Switch Sides", menu_pl_move);
    menu_pl_move->addAction (teamAction);
    connect(teamAction, SIGNAL(triggered()), this, SLOT(slotMovePlayerTeam()));

    // Expand all player rows
    ui->treeWidget_pl->expandAll();
}

void BFBC2::slotMovePlayerTeam()
{
    QAction *team = qobject_cast<QAction *>(sender());
    if (team) {
        QString altTeam = "1";
        QTreeWidgetItem *player = ui->treeWidget_pl->currentItem();
        if (player->data(0, Qt::UserRole) == "1") {
            altTeam = "2";
        }

        movePlayer(player->text(1), altTeam, "0", "true");
        con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    }
}

void BFBC2::slotStartupCommands()
{
    con->sendCommand(QString("\"eventsEnabled\" \"true\""));
    con->sendCommand(QString("\"version\""));
    con->sendCommand(QString("\"serverInfo\""));
    con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    con->sendCommand(QString("\"vars.textChatModerationMode\""));
    con->sendCommand(QString("\"vars.textChatSpamTriggerCount\""));
    con->sendCommand(QString("\"vars.textChatSpamDetectionTime\""));
    con->sendCommand(QString("\"vars.textChatSpamCoolDownTime\""));
    con->sendCommand(QString("\"mapList.nextLevelIndex\""));
    con->sendCommand(QString("\"mapList.list\""));
    con->sendCommand(QString("\"reservedSlots.list\""));
    con->sendCommand(QString("\"banList.list\""));
    con->sendCommand(QString("\"vars.serverName\""));
    con->sendCommand(QString("\"vars.serverDescription\""));
    con->sendCommand(QString("\"vars.bannerUrl\""));
}

void BFBC2::slotRefreshCommands()
{
    con->sendCommand(QString("\"serverInfo\""));
    con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    con->sendCommand(QString("\"mapList.list\""));
    con->sendCommand(QString("\"mapList.nextLevelIndex\""));
    con->sendCommand(QString("\"reservedSlots.list\""));
    con->sendCommand(QString("\"banList.list\""));
}

void BFBC2::slotEventOnSpawn(const QString &player, const QString &kit)
{
    Q_UNUSED(player);
    Q_UNUSED(kit);
}

void BFBC2::slotCommandServerInfo(QStringList si)
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
    */

    currentMod = si.at(17);
    currentGamemode = si.at(3);

    if (!levelsObject) {
        levelsObject = new BFBC2Levels(currentMod);
        this->comboBox_ml_gamemode_currentIndexChanged(0);
    }

    QString mapName = getMapName(si.at(4), si.at(3));
    QString mapImage = getMapImage(si.at(4), si.at(3));

    // Players
    ui->label_pl_servername->setText(si.at(0));
    ui->label_pl_map->setText(mapName);
    ui->label_pl_mod->setText(si.at(17));
    ui->label_pl_gamemode->setText(si.at(3));
    ui->label_pl_players->setText(QString("%1/%2").arg(si.at(1), si.at(2)));
    ui->label_pl_round->setText(QString("%1/%2").arg(si.at(6), si.at(7)));
    ui->label_pl_address->setText(si.at(19));
    ui->label_pl_state->setText(si.at(11));
    ui->label_pl_roundtime->setText(si.at(16));
    ui->label_pl_uptime->setText(si.at(15));

    // Maplist
    ui->label_ml_mod->setText(currentMod);
    ui->label_ml_currentmap_name->setText(mapName);
    ui->label_ml_currentmap_image->setPixmap(QPixmap(mapImage));
}

void BFBC2::slotCommandVarsTextChatModerationMode(const QString &tcmm)
{
    if (tcmm == "free") {
        ui->radioButton_op_tcm_free->setChecked(true);
    } else if (tcmm == "moderated") {
        ui->radioButton_op_tcm_moderated->setChecked(true);
    } else if (tcmm == "muted") {
        ui->radioButton_op_tcm_muted->setChecked(true);
    }
}

void BFBC2::slotCommandVarsTextChatSpamTriggerCount(const QString &tcstc)
{
    ui->spinBox_op_tcm_spamtriggercount->setValue(tcstc.toInt());
}

void BFBC2::slotCommandVarsTextChatSpamDetectionTime(const QString &tcsdt)
{
    ui->spinBox_op_tcm_spamdetectiontime->setValue(tcsdt.toInt());
}

void BFBC2::slotCommandVarsTextChatSpamCoolDownTime(const QString &tcscdt)
{
    ui->spinBox_op_tcm_spamcooldowntime->setValue(tcscdt.toInt());
}

void BFBC2::slotCommandBanListList(QStringList bl)
{
    ui->tableWidget_bl->clearContents();
    ui->tableWidget_bl->setRowCount(bl.size());
}

void BFBC2::slotCommandReservedSlotsList(QStringList rl)
{
    ui->listWidget_rs->clear();
    ui->listWidget_rs->addItems(rl);
}

void BFBC2::slotCommandMapListList(QStringList ml)
{
    // Sets currentmaps.
    QStringList mapNames;

    for (int i = 0; i < ml.size(); i++) {
        mapNames << getMapName(ml.at(i), currentGamemode);
    }

    ui->listWidget_ml_currentmaps->blockSignals(true);
    ui->listWidget_ml_currentmaps->clear();
    ui->listWidget_ml_currentmaps->blockSignals(false);
    ui->listWidget_ml_currentmaps->addItems(mapNames);
    // Sets nextMap

    if (nextLevelIndex >=0 && ml.count() > 0) {
        QString nextMapPath = ml.at(nextLevelIndex);
        ui->label_ml_nextmap_name->setText(getMapName(nextMapPath, currentGamemode));
        ui->label_ml_nextmap_image->setPixmap(QPixmap(getMapImage(nextMapPath, currentGamemode)));
    }
}

void BFBC2::slotCommandMapListNextLevelIndex(int &nm)
{
    nextLevelIndex = nm;
}

void BFBC2::slotCommandVarsServerName(const QString &sn)
{
    ui->lineEdit_op_so_servername->setText(sn);
}

void BFBC2::slotCommandVarsServerDescription(const QString &sd)
{
    ui->lineEdit_op_so_serverdescription->setText(sd);
}

void BFBC2::slotCommandVarsBannerUrl(const QString &bu)
{
    ui->lineEdit_op_so_bannerurl->setText(bu);
    ui->label_op_so_bannerurl_image->setPixmap(QPixmap(bu));
}

void BFBC2::authenticate(const QByteArray &pwd, const QByteArray &salt)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(salt);
    hash.addData(pwd);

    con->sendCommand(QString("\"login.hashed\" \"%1\"").arg(hash.result().toHex().toUpper().constData()));
}

QString BFBC2::getMapName(const QString &mapPath, const QString &gamemode) const
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gamemodeIndex != -1) {
        LevelList *levelList = levelsObject->levels().at(gamemodeIndex);
        int mapIndex = levelList->mapPaths().indexOf(QRegExp(mapPath, Qt::CaseInsensitive));

        if (mapIndex != -1) {
            QString mapName = levelList->mapNames ().at(mapIndex);
            return mapName;
        }
    }

    return QString();
}

QString BFBC2::getMapImage(const QString &mapPath, const QString &gamemode) const
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if (gamemodeIndex != -1) {
        LevelList *levelList = levelsObject->levels().at(gamemodeIndex);
        int mapIndex = levelList->mapPaths().indexOf(QRegExp(mapPath, Qt::CaseInsensitive));

        if (mapIndex != -1) {
            QString mapImage = levelList->mapImages().at(mapIndex);
            return mapImage;
        }
    }

    return QString();
}

void BFBC2::setMapList(const QString &gamemode)
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if(gamemodeIndex != -1) {
        QStringList mapNames = levelsObject->levels().at(gamemodeIndex)->mapNames();
        ui->listWidget_ml_avaliablemaps->clear();
        ui->listWidget_ml_avaliablemaps->addItems(mapNames);
    }
}

void BFBC2::sendSayMessage(const QString &msg, const QString &group, const QString &target1, const QString &target2)
{
    if (group == "all") {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\"").arg(msg, group));
    } else if (group == "team" || "player") {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\" \"%3\"").arg(msg, group, target1));
    } else if (group == "squad") {
        con->sendCommand(QString("\"admin.say\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(msg, group, target1, target2));
    }
}

void BFBC2::sendYellMessage(const QString &msg, const QString &duration, const QString &group, const QString &target1, const QString &target2)
{
    if (group == "all") {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\"").arg(msg, duration, group));
    } else if (group == "team" || "player") {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(msg, duration, group, target1));
    } else if (group == "squad") {
        con->sendCommand(QString("\"admin.yell\" \"%1\" \"%2\" \"%3\" \"%4\" \"%5\"").arg(msg, duration, group, target1, target2));
    }
}

void BFBC2::killPlayer(const QString &player)
{
    con->sendCommand(QString("\"admin.killPlayer\" \"%1\"").arg(player));
}

void BFBC2::kickPlayer(const QString &player, const QString &reason)
{
    con->sendCommand(QString("\"admin.kickPlayer\" \"%1\" \"%2\"").arg(player, reason));
}

void BFBC2::banPlayer(const QString &type, const QString &id, const QString &timeout, const QString &reason)
{
    // banList.add <id-type, id, timeout, reason> Add player/IP/GUID to ban list for a certain amount of time
    con->sendCommand(QString("\"banList.add\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(type, id, timeout, reason));
}

void BFBC2::unbanPlayer(const QString &type, const QString &id)
{
    con->sendCommand(QString("\"banList.remove\" \"%1\" \"%2\"").arg(type, id));
}

void BFBC2::movePlayer(const QString &player, const QString &teamId, const QString &squadId, const QString &fk)
{
    if (!player.isEmpty()) {
        con->sendCommand(QString("\"admin.movePlayer\" \"%1\" \"%2\" \"%3\" \"%4\"").arg(player, teamId, squadId, fk));
    }
}

void BFBC2::reservePlayer(const QString &player)
{
    if (!player.isEmpty()) {
        con->sendCommand(QString("\"reservedSlots.addPlayer\" \"%1\"").arg(player));
        ui->listWidget_rs->addItem(new QListWidgetItem(player, ui->listWidget_rs));
    }
}

void BFBC2::unReservePlayer(const QString &player)
{
    if (!player.isEmpty()) {
        con->sendCommand(QString("\"reservedSlots.removePlayer\" \"%1\"").arg(player));
        // TODO: Remove player from ui->listWidget_rs
    }
}

// Player

void BFBC2::treeWidget_pl_customContextMenuRequested(QPoint pos)
{
    if (ui->treeWidget_pl->itemAt(pos)) {
        // Something crash here.
        /*
        QString hideTeam = ui->treeWidget_pl->itemAt(pos)->parent()->text(0);
        foreach (QAction *team, menu_pl_move->actions()) {
            qDebug () << team->text();
            if (team->text () == hideTeam) {
                menu_pl_move->removeAction(team);
            }
        }
        */
        menu_pl->exec(QCursor::pos());
    }
}

void BFBC2::action_pl_sendmessage_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);
    bool ok;
    QString msg = QInputDialog::getText(this, tr("Send message"), tr("Message:"), QLineEdit::Normal, 0, &ok);

    if (ok && !msg.isEmpty()) {
        sendSayMessage(msg, "player", player, 0);
    }
}

void BFBC2::action_pl_stats_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    QDesktopServices::openUrl(QUrl(PLAYER_STATS_URL + player));
}

void BFBC2::action_pl_kill_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);
    killPlayer(player);
}

void BFBC2::action_pl_textchatmoderation_muted_triggered() // Get this work
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"muted\" \"%1\"").arg(player));
}

void BFBC2::action_pl_textchatmoderation_normal_triggered() // Get this work
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"normal\" \"%1\"").arg(player));
}

void BFBC2::action_pl_textchatmoderation_voice_triggered() // Get this work
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"voice\" \"%1\"").arg(player));
}

void BFBC2::action_pl_textchatmoderation_admin_triggered() // Get this work
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"admin\" \"%1\"").arg(player));
}

void BFBC2::action_pl_kick_custom_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);
    bool ok;
    QString reason = QInputDialog::getText(this, tr("Kick"), tr("Kick reason:"), QLineEdit::Normal, 0, &ok);

    if (ok && !reason.isEmpty()) {
        kickPlayer(player, reason);
    }
}

void BFBC2::action_pl_ban_byname_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);
    bool ok;
    QString reason = QInputDialog::getText(this, tr("Ban"), tr("Ban reason:"), QLineEdit::Normal, 0, &ok);

    if (ok && !reason.isEmpty()) {
        banPlayer("name", player, "perm", reason);
    }
}

void BFBC2::action_pl_reservedslots_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    if (!player.isEmpty()) {
        reservePlayer(player);
    }
}

// Options

void BFBC2::on_pushButton_op_so_servername_apply_clicked()
{
    QString servername = ui->lineEdit_op_so_servername->text();

    if (!servername.isEmpty()) {
        con->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(servername));
    }
}

void BFBC2::on_pushButton_op_so_serverdescription_apply_clicked()
{
    QString serverdescription = ui->lineEdit_op_so_serverdescription->text();

    if (!serverdescription.isEmpty()) {
        con->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(serverdescription));
    }
}

void BFBC2::on_pushButton_op_so_bannerurl_apply_clicked()
{
    QString bannerurl = ui->lineEdit_op_so_bannerurl->text();

    if (!bannerurl.isEmpty()) {
        con->sendCommand(QString("\"vars.bannerUrl\" \"%1\"").arg(bannerurl));
        ui->label_op_so_bannerurl_image->setPixmap(QPixmap(bannerurl));
    }
}

// Game Options

void BFBC2::on_checkbox_hardcore_mode()
{

    con->sendCommand(QString("\"vars.hardCore\" \"%1\"").arg(ui->check_box_hardcore_mode->isChecked()));

}
void BFBC2::on_checkbox_crosshair()
{
    con->sendCommand(QString("\"vars.crossHair\" \"%1\"").arg(ui->check_box_crosshair->isChecked()));

}
void BFBC2::on_checkbox_team_auto_balance()
{
con->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(ui->check_box_auto_balance->isChecked()));
}
void BFBC2::on_checkbox_3D_spotting()
{
con->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(ui->check_box_3d_spotting->isChecked()));
}
void BFBC2::on_checkbox_friendly_fire()
{
con->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(ui->check_box_friendly_fire->isChecked()));
}
void BFBC2::on_checkbox_minimap_spotting()
{
con->sendCommand(QString("\"vars.miniMapSpotting\" \"%1\"").arg(ui->check_box_minimap_spotting->isChecked()));
}
void BFBC2::on_checkbox_killcam()
{
con->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(ui->check_box_kill_cam->isChecked()));
}
void BFBC2::on_checkbox_3rd_person_vehicle_cameras()
{
con->sendCommand(QString("\"vars.thirdPersonVehicleCameras\" \"%1\"").arg(ui->check_box_3rd_person_vehicle_cameras->isChecked()));
}
void BFBC2::on_checkbox_minimap()
{
con->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(ui->check_box_minimap->isChecked()));
}

// Text Chat Moderation

void BFBC2::on_radioButton_op_tcm_free_clicked()
{
    con->sendCommand(QString("\"vars.textChatModerationMode\" \"free\""));
}

void BFBC2::on_radioButton_op_tcm_moderated_clicked()
{
    con->sendCommand(QString("\"vars.textChatModerationMode\" \"moderated\""));
}

void BFBC2::on_radioButton_op_tcm_muted_clicked()
{
    con->sendCommand(QString("\"vars.textChatModerationMode\" \"muted\""));
}

void BFBC2::on_pushButton_so_tcm_spamtriggercount_clicked()
{
    QString count = QString(ui->spinBox_op_tcm_spamtriggercount->value());

    con->sendCommand(QString("\"vars.textChatSpamTriggerCount\" \"%1\"").arg(count));
}

void BFBC2::on_pushButton_so_tcm_spamdetectiontime_clicked()
{
    QString count = QString(ui->spinBox_op_tcm_spamdetectiontime->value());

    con->sendCommand(QString("\"vars.textChatSpamDetectionTime\" \"%1\"").arg(count));
}

void BFBC2::on_pushButton_so_tcm_spamcooldowntime_clicked()
{
    QString count = QString(ui->spinBox_op_tcm_spamcooldowntime->value());

    con->sendCommand(QString("\"vars.textChatSpamCoolDownTime\" \"%1\"").arg(count));
}

// Maplist
void BFBC2::comboBox_ml_gamemode_currentIndexChanged(int index)
{


    // Stop the current item changed signal from being emitted
    ui->listWidget_ml_avaliablemaps->blockSignals(true);
    ui->listWidget_ml_avaliablemaps->clear();
    ui->listWidget_ml_avaliablemaps->blockSignals(false);

    // get a list of map names
    QStringList mapNames = levelsObject->levels().at(index)->mapNames();
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

void BFBC2::listWidget_ml_avaliablemaps_currentItemChanged(QListWidgetItem*, QListWidgetItem*)
{

    // get game mode from combo box
    int gameModeIndex = ui->comboBox_ml_gamemode->currentIndex();

    // get a list of map mods and map names and select all map names with a particular mod
    QStringList mapImages = levelsObject->levels().at(gameModeIndex)->mapImages();

    // find the selected map and show the preview image
    int avaliableMapIndex = ui->listWidget_ml_avaliablemaps->currentIndex().row();
    QString mapImage = mapImages.at(avaliableMapIndex);
    ui->label_ml_previewmap_image->setPixmap(QPixmap(mapImage));
}

void BFBC2::on_pushButton_ml_add_clicked()
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
    if (currentGamemode != gameModeCode[gameModeIndex])
    {
        commandRefreshTimer->blockSignals(true);
        QMessageBox msgBox;
        msgBox.setText("The gamemode selected is not the current gamemode on the server, this option will delete the maplist and change the gamemode on the server. Are you sure you want to continue?");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        ret = msgBox.exec();

        if (ret == QMessageBox::Yes)
        {
            con->sendCommand(QString("\"admin.setPlaylist\" \"%1\"").arg(gameModeCode[gameModeIndex]));
            con->sendCommand("\"mapList.clear\"");

        }
        else
        {
            delete ui->listWidget_ml_currentmaps->takeItem(ui->listWidget_ml_currentmaps->count());
        }
    }
    commandRefreshTimer->blockSignals(false);
    // get selected map
    int avaliableMapIndex = ui->listWidget_ml_avaliablemaps->currentIndex().row();

    // get a list of map mods and map names and select all map names with a particular mod
    QStringList mapNames = levelsObject->levels().at(gameModeIndex)->mapNames();
    QStringList mapPaths = levelsObject->levels().at(gameModeIndex)->mapPaths();


    // find map name and map path for selected map
    QString mapPath = mapPaths.at(avaliableMapIndex);
    QString mapName = mapNames.at(avaliableMapIndex);

    // get the amount of rounds from combo box
    int rounds = ui->spinBox_ml_rounds->value();

    // create a new map item and insert it into current map list
    QListWidgetItem *mapItem = new QListWidgetItem(ui->listWidget_ml_currentmaps);
    mapItem->setText(mapName);
    mapItem->setData (Qt::UserRole, mapPath);
    ui->listWidget_ml_currentmaps->addItem(mapItem);

    // append the map to the server map list
    con->sendCommand(QString("\"mapList.append\" \"%1\" \"%2\"").arg(mapPath).arg(rounds));

    if (ret == QMessageBox::Yes)
    {

       con->sendCommand("\"mapList.save\"");
       con->sendCommand("\"mapList.nextLevelIndex\" \"0\"");
       con->sendCommand("\"admin.runNextLevel\"");

    }

    con->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2::on_pushButton_ml_remove_clicked()
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

void BFBC2::on_pushButton_ml_restart_clicked()
{
    con->sendCommand("\"admin.restartRound\"");
}

void BFBC2::on_pushButton_ml_run_clicked()
{
    con->sendCommand("\"admin.runNextLevel\"");
}

void BFBC2::on_pushButton_ml_clear_clicked()
{
    con->sendCommand("\"mapList.clear\"");
}

void BFBC2::slotAddMapToServer(const QString &mapName)
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
    if (currentGamemode != gameModeCode[gameModeIndex])
    {
        commandRefreshTimer->blockSignals(true);
        QMessageBox msgBox;
        msgBox.setText("The gamemode selected is not the current gamemode on the server, this option will delete the maplist and change the gamemode on the server. Are you sure you want to continue?");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        ret = msgBox.exec();

        if (ret == QMessageBox::Yes)
        {
            con->sendCommand(QString("\"admin.setPlaylist\" \"%1\"").arg(gameModeCode[gameModeIndex]));
            con->sendCommand("\"mapList.clear\"");

        }
        else
        {
            delete ui->listWidget_ml_currentmaps->takeItem(ui->listWidget_ml_currentmaps->count()-1);
        }
    }
    commandRefreshTimer->blockSignals(false);
    // get a list of map mods and map names and select all map names with a particular mod
    QStringList mapNames = levelsObject->levels().at(gameModeIndex)->mapNames();
    QStringList mapPaths = levelsObject->levels().at(gameModeIndex)->mapPaths();

    // find map name and map path for selected map
    int avaliableMapIndex = mapNames.indexOf(mapName);
    QString mapPath = mapPaths.at(avaliableMapIndex);

    // get the amount of rounds from combo box
    int rounds = ui->spinBox_ml_rounds->value();

    // append the map to the server map list
    con->sendCommand(QString("\"mapList.append\" \"%1\" \"%2\"").arg(mapPath).arg(rounds));


    if (ret == QMessageBox::Yes)
    {

        con->sendCommand("\"mapList.save\"");
        con->sendCommand("\"mapList.nextLevelIndex\" \"0\"");
        con->sendCommand("\"admin.runNextLevel\"");

    }
    con->sendCommand("\"mapList.list\" \"rounds\"");

}

void BFBC2::slotRemoveMapFromServer(const QString &mapName)
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

void BFBC2::listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem* current)
{
    // get map name
    QString mapName = current->text();

    // get game mode
    int gamemodeIndex = gamemodes.indexOf(QRegExp(currentGamemode, Qt::CaseInsensitive));

    QStringList mapNames = levelsObject->levels().at(gamemodeIndex)->mapNames();
    QStringList mapImages = levelsObject->levels().at(gamemodeIndex)->mapImages();

    int avaliableMapIndex = mapNames.indexOf(mapName);
    QString mapImage = mapImages.at(avaliableMapIndex);
    ui->label_ml_previewmap_image->setPixmap(QPixmap(mapImage));
    con->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2::on_pushButton_ml_save_clicked()
{
    con->sendCommand("\"mapList.save\"");
}

// BanList
void BFBC2::listWidget_bl_customContextMenuRequested(QPoint pos)
{
    if (ui->tableWidget_bl->itemAt(pos)) {
        menu_bl->exec(QCursor::pos());
    }
}

void BFBC2::action_bl_remove_triggered()
{
    QString id = ui->tableWidget_bl->currentItem()->text();
    QString type = ui->comboBox_bl_type->currentText().toLower();

    if (!id.isEmpty()) {
        unbanPlayer(type, id);
    }
}

void BFBC2::on_pushButton_bl_ban_clicked()
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

void BFBC2::on_pushButton_bl_clear_clicked()
{
    con->sendCommand("\"banList.clear\"");
}

void BFBC2::on_pushButton_bl_save_clicked()
{
    con->sendCommand("\"banList.save\"");
}

// Reserved slots
void BFBC2::listWidget_rs_customContextMenuRequested(QPoint pos)
{
    if (ui->listWidget_rs->itemAt(pos)) {
        menu_rs->exec(QCursor::pos());
    }
}

void BFBC2::action_rs_remove_triggered()
{
    QString player = ui->listWidget_rs->currentItem()->text();
    unReservePlayer(player);
}

void BFBC2::on_pushButton_rs_reserve_clicked()
{
    QString player = ui->lineEdit_rs_player->text();

    if (!player.isEmpty()) {
        reservePlayer(player);
        ui->lineEdit_rs_player->clear();
    }
}

void BFBC2::on_pushButton_rs_save_clicked()
{
    con->sendCommand("\"reservedSlots.save\"");
}

void BFBC2::on_pushButton_rs_clear_clicked()
{
    con->sendCommand("\"reservedSlots.clear\"");
}

// Ingame Commands
void BFBC2::listWidget_ic_customContextMenuRequested(QPoint pos)
{
    if (ui->listWidget_ic->itemAt(pos)) {
        menu_ic->exec(QCursor::pos());
    }
}

void BFBC2::on_pushButton_ic_add_clicked()
{
    QString user = ui->lineEdit_ic_player->text();

    settings->beginGroup(SETTINGS_INGAMECOMMANDS);
        //int size = ui->lineEdit_ic_player->text().size();
        settings->beginWriteArray(SETTINGS_INGAMECOMMANDS_USERS);
            for (int i = 0; i < 1; i++) {
                settings->setArrayIndex(i);
                    settings->setValue("User", user);
                    ui->listWidget_ic->addItem(new QListWidgetItem(user, ui->listWidget_ic));
            }
        settings->endArray();
    settings->endGroup();
}

void BFBC2::action_ic_remove_triggered()
{
    settings->beginGroup(SETTINGS_INGAMECOMMANDS);
        //int size = ui->lineEdit_ic_player->text().size();
        settings->beginWriteArray(SETTINGS_INGAMECOMMANDS_USERS);
            for (int i = 0; i < 1; i++) {
                settings->setArrayIndex(i);
                    settings->remove("User");
            }
        settings->endArray();
    settings->endGroup();
}

// Chat

void BFBC2::on_pushButton_ch_send_clicked()
{
    int type = ui->comboBox_ch_type->currentIndex();

    QString msg = ui->lineEdit_ch_input->text();
    QString duration = ui->comboBox_ch_duration->currentText();
    QString group = ui->comboBox_ch_target->currentText().toLower();

    if (type == 0) {
        sendSayMessage(msg, group, 0, 0);
    } else if (type == 1) {
        sendYellMessage(msg, duration, group, 0, 0);
    }
    ui->lineEdit_ch_input->clear();
}

void BFBC2::comboBox_ch_type_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->comboBox_ch_duration->hide();
        break;
    case 1:
        ui->comboBox_ch_duration->show();
        break;
    }
}

// Console
void BFBC2::on_pushButton_co_co_send_clicked()
{
    QString cmd = ui->lineEdit_co_co_input->text();

    if (!cmd.isEmpty()) {
        con->sendCommand(cmd);
        ui->lineEdit_co_co_input->clear();
    }
}

// PunkBuster
void BFBC2::on_pushButton_co_pb_send_clicked()
{
    QString cmd = ui->lineEdit_co_pb_input->text();

    if (!cmd.isEmpty()) {
        con->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(cmd));
        ui->lineEdit_co_pb_input->clear();
    }
}

void BFBC2::slotChangePlayerTeam(const QString &player, const QString &altTeam)
{
    movePlayer(player, altTeam, "0", "true");
}

void BFBC2::refreshPlayerList()
{
    con->sendCommand(QString("\"admin.listPlayers\" \"all\""));
    connect(con->commandSignals(), SIGNAL(playerListChange()), this, SLOT(slotPlayerListChange())); // TODO: Change to adminListPlayersAll
}

void BFBC2::blockPlayerList()
{
    disconnect(con->commandSignals(), SIGNAL(playerListChange()), this, SLOT(slotPlayerListChange()));
}

void BFBC2::playerListUpdate(int oldRow)
{

    QString rounds = mapListU[2*oldRow+1];
    con->sendCommand(QString("\"mapList.remove\" \"%1\"").arg(oldRow));

    int currentRow = ui->listWidget_ml_currentmaps->currentRow();
    QString mapName = ui->listWidget_ml_currentmaps->item(currentRow)->text();


    // Get game mode from combo box
    int gameModeIndex = ui->comboBox_ml_gamemode->currentIndex();

    // get a list of map mods and map names and select all map names with a particular mod
    QStringList mapNames = levelsObject->levels().at(gameModeIndex)->mapNames();
    QStringList mapPaths = levelsObject->levels().at(gameModeIndex)->mapPaths();

    // Find map name and map path for selected map
    int avaliableMapIndex = mapNames.indexOf(mapName);
    QString mapPath = mapPaths.at(avaliableMapIndex);

    // Append the map to the server map list
    con->sendCommand(QString("\"mapList.insert\" \"%1\" \"%2\" \"%3\"").arg(currentRow).arg(mapPath).arg(rounds));

    con->sendCommand("\"mapList.list\" \"rounds\"");
}

void BFBC2::slotCommandMapListListRounds(QStringList ml)
{
    mapListU = ml;
}
