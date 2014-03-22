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

#include "BF3.h"

BF3::BF3(const QString &host, const int &port, const QString &password) : Game(host, port, password), ui(new Ui::BF3)
{
    ui->setupUi(this);

    con = new BF3Connection(this);
    con->hostConnect(host, port);

    // Player menu
    menu_pl_playerBan = new QMenu(tr("Ban"), this);
    menu_pl_playerBan->addAction(ui->actionBan_byName);
    menu_pl_playerKick = new QMenu(tr("Kick"), this);
    menu_pl_playerKick->addAction(ui->actionKick_custom);
    menu_pl_playerMove = new QMenu(tr("Move"), this);
    menu_pl_playerMove->addAction(ui->actionMove);
    menu_pl_player = new QMenu(tr("Players"), this);
    menu_pl_player->addMenu(menu_pl_playerKick);
    menu_pl_player->addAction(ui->actionKill);
    menu_pl_player->addMenu(menu_pl_playerMove);

    ui->treeWidget_pl->setContextMenuPolicy(Qt::CustomContextMenu);

    QStringList commandList; 
    commandList << "demo.recordDemo ";
    commandList << "demo.stopRecording";
    commandList << "demo.ShutdownDemo";
    commandList << "game.sayAll ";
    commandList << "game.sayTeam ";
    commandList << "game.lockFps ";
    commandList << "game.allowToggleFullscreen ";
    commandList << "game.toggleFullscreen";
    commandList << "localProfile.setName ";
    commandList << "localProfile.setNick ";
    commandList << "localProfile.setGamespyNick ";
    commandList << "localProfile.setEmail ";
    commandList << "localProfile.setPassword ";
    commandList << "localProfile.setNumTimesLoggedIn ";
    commandList << "localProfile.setTotalPlayedTime ";
    commandList << "localProfile.save";
    commandList << "localProfile.addDemoBookmark ";
    commandList << "globalSettings.setDefaultUser ";
    commandList << "renderer.drawHud ";
    commandList << "renderer.drawConsole ";
    commandList << "renderer.drawFps ";
    commandList << "sv.allowNATNegotiation ";
    commandList << "sv.interface ";
    commandList << "sv.timeBeforeRestarting ";
    commandList << "sv.autoBalanceTeam ";
    commandList << "sv.teamRatioPercent ";
    commandList << "sv.autoRecord ";
    commandList << "sv.demoIndexURL ";
    commandList << "sv.demoDownloadURL ";
    commandList << "sv.autoDemoHook ";
    commandList << "sv.demoQuality ";
    commandList << "sv.adminScript ";
    commandList << "sv.sponsorText ";
    commandList << "sv.sponsorLogoURL ";
    commandList << "sv.communityLogoURL ";
    commandList << "sv.radioSpamInterval ";
    commandList << "sv.radioMaxSpamFlagCount ";
    commandList << "sv.radioBlockedDurationTime ";
    commandList << "sv.useGlobalRank ";
    commandList << "sv.useGlobalUnlocks ";
    commandList << "gameLogic.togglePause";
    commandList << "SettingsManager.stringSet ";
    commandList << "SettingsManager.boolSet ";
    commandList << "SettingsManager.IntSet ";
    commandList << "SettingsManager.floatSet ";
    commandList << "SettingsManager.u32Set ";
    commandList << "SettingsManager.stringGet ";
    commandList << "SettingsManager.boolGet ";
    commandList << "SettingsManager.intGet ";
    commandList << "SettingsManager.foatGet ";
    commandList << "SettingsManager.U32Get ";
    commandList << "controlMap.deleteControlMap ";
    commandList << "controlMap.dump ";
    commandList << "controlMap.setButtonRiseTime ";
    commandList << "controlMap.SetButtonFallTime ";
    commandList << "controlMap.SetDoubleTapTime ";
    commandList << "controlMap.addAxisToAxisMapping ";
    commandList << "controlMap.addButtonsToAxisMapping ";
    commandList << "controlMap.addKeyAndButtonToAxisMapping ";
    commandList << "controlMap.addKeysToAxisMapping ";
    commandList << "controlMap.addButtonToTriggerMapping ";
    commandList << "controlMap.AddKeyToTriggerMapping ";
    commandList << "controlMap.setAxisScale ";
    commandList << "controlMap.setYawFactor ";
    commandList << "controlMap.setPitchFactor ";
    commandList << "controlMap.addAxisToTriggerMapping ";
    commandList << "controlMap.InvertMouse ";
    commandList << "controlMap.mouseSensitivity ";
    commandList << "controlMap.keyboardSensitivity ";
    commandList << "mapList.list";
    commandList << "mapList.configFile ";
    commandList << "mapList.load";
    commandList << "mapList.save";
    commandList << "mapList.mapCount";
    commandList << "mapList.currentMap";
    commandList << "mapList.clear";
    commandList << "mapList.remove ";
    commandList << "mapList.append ";
    commandList << "mapList.insert ";
    commandList << "InputDevices.setInvertAxis";
    commandList << "InputDevices.setAxisScale";
    commandList << "admin.listPlayers";
    commandList << "admin.runNextLevel";
    commandList << "admin.currentLevel";
    commandList << "admin.nextLevel";
    commandList << "admin.restartMap";
    commandList << "admin.banPlayer ";
    commandList << "admin.banPlayerKey ";
    commandList << "admin.addAddressToBanList ";
    commandList << "admin.addKeyToBanList ";
    commandList << "admin.removeAddressFromBanList ";
    commandList << "admin.removeKeyFromBanList ";
    commandList << "admin.clearBanList";
    commandList << "admin.listBannedAddresses";
    commandList << "admin.listBannedKeys";
    commandList << "admin.kickPlayer ";

    completer = new QCompleter(commandList, this);
    ui->lineEdit_co_input->setCompleter(completer);

    connect(con, SIGNAL(logMessage(const QString&, const QString&)), this, SLOT(slotLogMessage(const QString&, const QString&)));
    connect(ui->treeWidget_pl, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeWidget_pl_customContextMenuRequested(QPoint)));
    connect(ui->lineEdit_co_input, SIGNAL(returnPressed()), this, SLOT(on_pushButton_co_send_clicked()));
}

BF3::~BF3()
{
    delete ui;
}

void BF3::treeWidget_pl_customContextMenuRequested(QPoint pos)
{
    if (ui->treeWidget_pl->itemAt(pos)) {
        menu_pl_player->exec(QCursor::pos());
    }
}

void BF3::slotLogMessage(const QString& type, const QString& msg)
{
    if (type == "error") {
        ui->textEdit_co_output->append(QString("[%1] <span style=\"color:red\">%2</span>").arg(__TIME__, msg));
    } else if (type == "info") {
        ui->textEdit_co_output->append(QString("[%1] <span style=\"color:green\">%2</span>").arg(__TIME__, msg));
    } else if (type == "response") {
        ui->textEdit_co_output->append(QString("[%1] <span style=\"color:#AAAAAA\">%2</span>").arg(__TIME__, msg));
    } else {
        ui->textEdit_co_output->append(QString("[%1] %2").arg(__TIME__, msg));
    }
}

void BF3::on_pushButton_co_send_clicked()
{
    QString cmd = ui->lineEdit_co_input->text();
    con->sendCommand(cmd);
    ui->lineEdit_co_input->clear();
}

void BF3::slotPlayerListChange()
{
    qDebug() << "slotPlayerListChange called!";
    
    // Get player list
    PlayerItem playerList = con->getPlayerList();
    
    // Clear QTreeWidget
    ui->treeWidget_pl->clear();
    
    // Used to store player fields
    QStringList playerInfo;
    
    QMap<QString, QString>::const_iterator i = playerList.constBegin();
            
    while (i != playerList.constEnd()) {
        qDebug() << "Id: " << i.key() << " User name: " << i.value() << endl;
        
        // Player Id
        playerInfo.append(i.key());
        // Player name
        playerInfo.append(i.value());

        ++i;
    }
}
