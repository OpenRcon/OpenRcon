#include "BFBC2Widget.h"

BFBC2Widget::BFBC2Widget(const QString &host, const int &port, const QString &password) : BFBC2(host, port, password), ui(new Ui::BFBC2)
{
    ui->setupUi(this);

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
    ui->lineEdit_co_co_input->setCompleter(completer);

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

    // Messages and events.
    connect(con->commandHandler, SIGNAL(onLogMessage(const int&, const QString&)), this, SLOT(slotLogMessage(const int&, const QString&)));
    connect(con->commandHandler, SIGNAL(onLogEvent(const QString&, const QString&)), this, SLOT(slotLogEvent(const QString&, const QString&)));

    connect(con->commandHandler, SIGNAL(onPlayerListChange()), this, SLOT(slotPlayerListChange())); // TODO: Change to adminListPlayersAll

    // Commands
    connect(con->commandHandler, SIGNAL(onCommandServerInfo(QStringList)), this, SLOT(slotCommandServerInfo(QStringList)));
    connect(con->commandHandler, SIGNAL(onCommandVarsTextChatModerationMode(const QString&)), this, SLOT(slotCommandVarsTextChatModerationMode(const QString&)));
    connect(con->commandHandler, SIGNAL(onCommandVarsTextChatSpamTriggerCount(const QString&)), this, SLOT(slotCommandVarsTextChatSpamTriggerCount(const QString&)));
    connect(con->commandHandler, SIGNAL(onCommandVarsTextChatSpamDetectionTime(const QString&)), this, SLOT(slotCommandVarsTextChatSpamDetectionTime(const QString&)));
    connect(con->commandHandler, SIGNAL(onCommandVarsTextChatSpamCoolDownTime(const QString&)), this, SLOT(slotCommandVarsTextChatSpamCoolDownTime(const QString&)));
    connect(con->commandHandler, SIGNAL(onCommandBanListList(QStringList)), this, SLOT(slotCommandBanListList(QStringList)));
    connect(con->commandHandler, SIGNAL(onCommandReservedSlotsList(QStringList)), this, SLOT(slotCommandReservedSlotsList(QStringList)));
    connect(con->commandHandler, SIGNAL(onCommandMapListNextLevelIndex(int&)), this, SLOT(slotCommandMapListNextLevelIndex(int&)));
    connect(con->commandHandler, SIGNAL(onCommandMapListList(QStringList)), this, SLOT(slotCommandMapListList(QStringList)));
    connect(con->commandHandler, SIGNAL(onCommandMapListListRounds(QStringList)), this, SLOT(slotCommandMapListListRounds(QStringList)));
    connect(con->commandHandler, SIGNAL(onCommandVarsServerName(const QString&)), this, SLOT(slotCommandVarsServerName(const QString&)));
    connect(con->commandHandler, SIGNAL(onCommandVarsServerDescription(const QString&)), this, SLOT(slotCommandVarsServerDescription(const QString&)));
    connect(con->commandHandler, SIGNAL(onCommandVarsBannerUrl(const QString&)), this, SLOT(slotCommandVarsBannerUrl(const QString&)));
}

BFBC2Widget::~BFBC2Widget()
{
    delete ui;
}

void BFBC2Widget::readSettings()
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

void BFBC2Widget::writeSettings()
{

}

void BFBC2Widget::slotLogMessage(const int &type, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QTime::currentTime().toString());

    if (type == 0) { // Error
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    } else if (type == 1) { // Info
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime, message));
    } else if (type == 2) { // Server send
        ui->textEdit_co_co_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    } else if (type == 3) { // Server receive
        ui->textEdit_co_co_output->append(QString("%1 <span style=\"color:#0000FF\">%2</span>").arg(currentTime, message));
    } else if (type == 4) { // Chat
        ui->textEdit_ch_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    } else if (type == 5) { // Punkbuster
        ui->textEdit_co_pb_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime, message));
    }
}

void BFBC2Widget::slotLogEvent(const QString &event, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QTime::currentTime().toString());

    ui->textEdit_ev_output->append(QString("%1 %2").arg(currentTime, message));
}

void BFBC2Widget::slotPlayerListChange()
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
    connect(teamAction, SIGNAL(ontriggered()), this, SLOT(slotMovePlayerTeam()));

    // Expand all player rows
    ui->treeWidget_pl->expandAll();
}

void BFBC2Widget::slotMovePlayerTeam()
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

void BFBC2Widget::slotCommandServerInfo(QStringList si)
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
    ui->label_pl_uptime->setText(QTime::fromString(si.at(15), "s").toString());

    // Maplist
    ui->label_ml_mod->setText(currentMod);
    ui->label_ml_currentmap_name->setText(mapName);
    ui->label_ml_currentmap_image->setPixmap(QPixmap(mapImage));
}

void BFBC2Widget::slotCommandVarsTextChatModerationMode(const QString &tcmm)
{
    if (tcmm == "free") {
        ui->radioButton_op_tcm_free->setChecked(true);
    } else if (tcmm == "moderated") {
        ui->radioButton_op_tcm_moderated->setChecked(true);
    } else if (tcmm == "muted") {
        ui->radioButton_op_tcm_muted->setChecked(true);
    }
}

void BFBC2Widget::slotCommandVarsTextChatSpamTriggerCount(const QString &tcstc)
{
    ui->spinBox_op_tcm_spamtriggercount->setValue(tcstc.toInt());
}

void BFBC2Widget::slotCommandVarsTextChatSpamDetectionTime(const QString &tcsdt)
{
    ui->spinBox_op_tcm_spamdetectiontime->setValue(tcsdt.toInt());
}

void BFBC2Widget::slotCommandVarsTextChatSpamCoolDownTime(const QString &tcscdt)
{
    ui->spinBox_op_tcm_spamcooldowntime->setValue(tcscdt.toInt());
}

void BFBC2Widget::slotCommandBanListList(QStringList bl)
{
    ui->tableWidget_bl->clearContents();
    ui->tableWidget_bl->setRowCount(bl.size());
}

void BFBC2Widget::slotCommandReservedSlotsList(QStringList rl)
{
    ui->listWidget_rs->clear();
    ui->listWidget_rs->addItems(rl);
}

void BFBC2Widget::slotCommandMapListList(QStringList ml)
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

void BFBC2Widget::slotCommandMapListNextLevelIndex(int &nm)
{
    nextLevelIndex = nm;
}

void BFBC2Widget::slotCommandVarsServerName(const QString &sn)
{
    ui->lineEdit_op_so_servername->setText(sn);
}

void BFBC2Widget::slotCommandVarsServerDescription(const QString &sd)
{
    ui->lineEdit_op_so_serverdescription->setText(sd);
}

void BFBC2Widget::slotCommandVarsBannerUrl(const QString &bu)
{
    ui->lineEdit_op_so_bannerurl->setText(bu);
    ui->label_op_so_bannerurl_image->setPixmap(QPixmap(bu));
}

void BFBC2Widget::setMapList(const QString &gamemode)
{
    int gamemodeIndex = gamemodes.indexOf(QRegExp(gamemode, Qt::CaseInsensitive));

    if(gamemodeIndex != -1) {
        QStringList mapNames = levelsObject->levels().at(gamemodeIndex)->mapNames();
        ui->listWidget_ml_avaliablemaps->clear();
        ui->listWidget_ml_avaliablemaps->addItems(mapNames);
    }
}

// Player
void BFBC2Widget::treeWidget_pl_customContextMenuRequested(QPoint pos)
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

void BFBC2Widget::action_pl_sendmessage_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);
    bool ok;
    QString msg = QInputDialog::getText(this, tr("Send message"), tr("Message:"), QLineEdit::Normal, 0, &ok);

    if (ok && !msg.isEmpty()) {
        sendSayMessage(msg, "player", player, 0);
    }
}

void BFBC2Widget::action_pl_stats_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    QDesktopServices::openUrl(QUrl(PLAYER_STATS_URL + player));
}

void BFBC2Widget::action_pl_kill_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);
    killPlayer(player);
}

void BFBC2Widget::action_pl_textchatmoderation_muted_triggered() // Get this work
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"muted\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_normal_triggered() // Get this work
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"normal\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_voice_triggered() // Get this work
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"voice\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_textchatmoderation_admin_triggered() // Get this work
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    con->sendCommand(QString("\"textChatModerationList.addPlayer\" \"admin\" \"%1\"").arg(player));
}

void BFBC2Widget::action_pl_kick_custom_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);
    bool ok;
    QString reason = QInputDialog::getText(this, tr("Kick"), tr("Kick reason:"), QLineEdit::Normal, 0, &ok);

    if (ok && !reason.isEmpty()) {
        kickPlayer(player, reason);
    }
}

void BFBC2Widget::action_pl_ban_byname_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);
    bool ok;
    QString reason = QInputDialog::getText(this, tr("Ban"), tr("Ban reason:"), QLineEdit::Normal, 0, &ok);

    if (ok && !reason.isEmpty()) {
        banPlayer("name", player, "perm", reason);
    }
}

void BFBC2Widget::action_pl_reservedslots_triggered()
{
    QString player = ui->treeWidget_pl->currentItem()->text(1);

    if (!player.isEmpty()) {
        reserveSlotForPlayer(player, true);
    }
}

// Options
void BFBC2Widget::on_pushButton_op_so_servername_apply_clicked()
{
    QString servername = ui->lineEdit_op_so_servername->text();

    if (!servername.isEmpty()) {
        con->sendCommand(QString("\"vars.serverName\" \"%1\"").arg(servername));
    }
}

void BFBC2Widget::on_pushButton_op_so_serverdescription_apply_clicked()
{
    QString serverdescription = ui->lineEdit_op_so_serverdescription->text();

    if (!serverdescription.isEmpty()) {
        con->sendCommand(QString("\"vars.serverDescription\" \"%1\"").arg(serverdescription));
    }
}

void BFBC2Widget::on_pushButton_op_so_bannerurl_apply_clicked()
{
    QString bannerurl = ui->lineEdit_op_so_bannerurl->text();

    if (!bannerurl.isEmpty()) {
        con->sendCommand(QString("\"vars.bannerUrl\" \"%1\"").arg(bannerurl));
        ui->label_op_so_bannerurl_image->setPixmap(QPixmap(bannerurl));
    }
}

// Game Options

void BFBC2Widget::on_checkbox_hardcore_mode_clicked()
{
    con->sendCommand(QString("\"vars.hardCore\" \"%1\"").arg(ui->checkBox_hardcore_mode->isChecked()));
}

void BFBC2Widget::on_checkbox_crosshair_clicked()
{
    con->sendCommand(QString("\"vars.crossHair\" \"%1\"").arg(ui->checkBox_crosshair->isChecked()));

}
void BFBC2Widget::on_checkbox_team_auto_balance_clicked()
{
con->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(ui->checkBox_auto_balance->isChecked()));
}
void BFBC2Widget::on_checkbox_3D_spotting_clicked()
{
con->sendCommand(QString("\"vars.3dSpotting\" \"%1\"").arg(ui->checkBox_3d_spotting->isChecked()));
}
void BFBC2Widget::on_checkbox_friendly_fire_clicked()
{
con->sendCommand(QString("\"vars.friendlyFire\" \"%1\"").arg(ui->checkBox_friendly_fire->isChecked()));
}
void BFBC2Widget::on_checkbox_minimap_spotting_clicked()
{
con->sendCommand(QString("\"vars.miniMapSpotting\" \"%1\"").arg(ui->checkBox_minimap_spotting->isChecked()));
}
void BFBC2Widget::on_checkbox_killcam_clicked()
{
con->sendCommand(QString("\"vars.killCam\" \"%1\"").arg(ui->checkBox_kill_cam->isChecked()));
}
void BFBC2Widget::on_checkbox_3rd_person_vehicle_cameras_clicked()
{
con->sendCommand(QString("\"vars.thirdPersonVehicleCameras\" \"%1\"").arg(ui->checkBox_3rd_person_vehicle_cameras->isChecked()));
}
void BFBC2Widget::on_checkbox_minimap_clicked()
{
con->sendCommand(QString("\"vars.miniMap\" \"%1\"").arg(ui->checkBox_minimap->isChecked()));
}

// Text Chat Moderation
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

// Maplist
void BFBC2Widget::comboBox_ml_gamemode_currentIndexChanged(int index)
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

void BFBC2Widget::listWidget_ml_avaliablemaps_currentItemChanged(QListWidgetItem*, QListWidgetItem*)
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

void BFBC2Widget::listWidget_ml_currentmaps_currentItemChanged(QListWidgetItem* current)
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
    reserveSlotForPlayer(player, false);
}

void BFBC2Widget::on_pushButton_rs_reserve_clicked()
{
    QString player = ui->lineEdit_rs_player->text();

    if (!player.isEmpty()) {
        reserveSlotForPlayer(player, true);
        ui->lineEdit_rs_player->clear();
    }
}

void BFBC2Widget::on_pushButton_rs_save_clicked()
{
    con->sendCommand("\"reservedSlots.save\"");
}

void BFBC2Widget::on_pushButton_rs_clear_clicked()
{
    con->sendCommand("\"reservedSlots.clear\"");
}

// Ingame Commands
void BFBC2Widget::listWidget_ic_customContextMenuRequested(QPoint pos)
{
    if (ui->listWidget_ic->itemAt(pos)) {
        menu_ic->exec(QCursor::pos());
    }
}

void BFBC2Widget::on_pushButton_ic_add_clicked()
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

void BFBC2Widget::action_ic_remove_triggered()
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

void BFBC2Widget::on_pushButton_ch_send_clicked()
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

void BFBC2Widget::comboBox_ch_type_currentIndexChanged(int index)
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
void BFBC2Widget::on_pushButton_co_co_send_clicked()
{
    QString cmd = ui->lineEdit_co_co_input->text();

    if (!cmd.isEmpty()) {
        con->sendCommand(cmd);
        ui->lineEdit_co_co_input->clear();
    }
}

// PunkBuster
void BFBC2Widget::on_pushButton_co_pb_send_clicked()
{
    QString cmd = ui->lineEdit_co_pb_input->text();

    if (!cmd.isEmpty()) {
        con->sendCommand(QString("\"punkBuster.pb_sv_command\" \"%1\"").arg(cmd));
        ui->lineEdit_co_pb_input->clear();
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

void BFBC2Widget::blockPlayerList()
{
    disconnect(con->commandHandler, SIGNAL(onplayerListChange()), this, SLOT(slotPlayerListChange()));
}

void BFBC2Widget::playerListUpdate(int oldRow)
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
