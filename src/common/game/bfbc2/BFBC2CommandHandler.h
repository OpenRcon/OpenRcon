/*
 * Copyright (C) 2016 The OpenRcon Project.
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

#ifndef BFBC2COMMANDHANDLER_H
#define BFBC2COMMANDHANDLER_H

#include "FrostbiteCommandHandler.h"

class QStringList;

class BFBC2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    BFBC2CommandHandler(QObject *parent = nullptr);
    ~BFBC2CommandHandler() final;

    bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) final;

    /* Send commands */
    // Misc
    /// BFBC2 Only.
    void sendEventsEnabledCommand();
    void sendEventsEnabledCommand(bool enabled);
    void sendHelpCommand();

    // Admin
    /// BFBC2 Only.
    //admin.runscript <filename>
    //admin.runNextRound
    //admin.restartRound
    //admin.endRound <teamID>
    //admin.currentLevel
    //admin.supportedMaps <play list>
    //admin.setPlaylist <name>
    //admin.getPlaylist
    //admin.getPlaylists

    // Banning

    // Maplist
    /// BFBC2 Only.
    //mapList.append <name, rounds>
    //mapList.insert <index, name, rounds>
    //mapList.nextLevelIndex [index: integer]

    // Punkbuster

    // Reserved Slots
    /// BFBC2 Only.
    //reservedSlots.load
    //reservedSlots.save
    //reservedSlots.addPlayer <name>
    //reservedSlots.removePlayer <name>
    //reservedSlots.clear
    //reservedSlots.list

    // Variables
    /// BFBC2 Only.
    //vars.adminPassword [password]
    //vars.punkBuster [enabled]
    //vars.hardCore
    //vars.ranked
    //vars.rankLimit [rank]
    //vars.teamBalance [enabled]
    //vars.currentPlayerLimit
    //vars.maxPlayerLimit
    //vars.playerLimit [nr of players]
    //vars.bannerUrl [url]
    //vars.crossHair [enabled]
    //vars.thirdPersonVehicleCameras [enabled]
    //vars.profanityFilter [enabled]
    //vars.textChatModerationMode [moderation mode]
    //vars.textChatSpamTriggerCount [count]
    //vars.textChatSpamDetectionTime [time]
    //vars.textChatSpamCoolDownTime [time]

    // Text Chat Moderation
    //textChatModerationList.load
    //textChatModerationList.save
    //textChatModerationList.add <moderationlevel> <name>
    //textChatModerationList.remove <name>
    //textChatModerationList.clear
    //textChatModerationList.list [startOffset]

    // Level Variables
    //levelVars.set <context> <var name> <value>
    //levelVars.get <context> <var name>
    //levelVars.evaluate <var name>
    //levelVars.clear <context> [var name]
    //levelVars.list <context> [var name]

private:
    /* Parse events */
    void parsePlayerKickedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parsePunkBusterVersionEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLoadingLevelEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);
    void parseServerLevelStartedEvent(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket);

    //player.onKicked
    //punkBuster.onVersion
    //server.onLoadingLevel
    //server.onLevelStarted

    /* Parse commands */
    // Misc
    /// BFBC2 Only.
    //eventsEnabled
    //help

    // Admin
    /// BFBC2 Only.
    //admin.runscript <filename>
    //admin.runNextRound
    //admin.restartRound
    //admin.endRound <teamID>
    //admin.currentLevel
    //admin.supportedMaps <play list>
    //admin.setPlaylist <name>
    //admin.getPlaylist
    //admin.getPlaylists

    // Banning

    // Maplist
    /// BFBC2 Only.
    //mapList.append <name, rounds>
    //mapList.insert <index, name, rounds>
    //mapList.nextLevelIndex [index: integer]

    // Punkbuster

    // Reserved Slots
    /// BFBC2 Only.
    //reservedSlots.load
    //reservedSlots.save
    //reservedSlots.addPlayer <name>
    //reservedSlots.removePlayer <name>
    //reservedSlots.clear
    //reservedSlots.list

    // Variables
    /// BFBC2 Only.
    //vars.adminPassword [password]
    //vars.punkBuster [enabled]
    //vars.hardCore
    //vars.ranked
    //vars.rankLimit [rank]
    //vars.teamBalance [enabled]
    //vars.currentPlayerLimit
    //vars.maxPlayerLimit
    //vars.playerLimit [nr of players]
    //vars.bannerUrl [url]
    //vars.crossHair [enabled]
    //vars.thirdPersonVehicleCameras [enabled]
    //vars.profanityFilter [enabled]
    //vars.textChatModerationMode [moderation mode]
    //vars.textChatSpamTriggerCount [count]
    //vars.textChatSpamDetectionTime [time]
    //vars.textChatSpamCoolDownTime [time]

    // Text Chat Moderation
    //textChatModerationList.load
    //textChatModerationList.save
    //textChatModerationList.add <moderationlevel> <name>
    //textChatModerationList.remove <name>
    //textChatModerationList.clear
    //textChatModerationList.list [startOffset]

    // Level Variables
    //levelVars.set <context> <var name> <value>
    //levelVars.get <context> <var name>
    //levelVars.evaluate <var name>
    //levelVars.clear <context> [var name]
    //levelVars.list <context> [var name]

signals:
    /* Event signals */
    void onPlayerKickedEvent(const QString &player, const QString &reason);
    void onPunkBusterVersionEvent(const QString &version);
    void onServerLoadingLevelEvent(const QString &levelName, int roundsPlayed, int roundsTotal);
    void onServerLevelStartedEvent();

    /* Command signals */
    // Misc
    /// BFBC2 Only.
    //eventsEnabled
    //help

    // Admin
    /// BFBC2 Only.
    //admin.runscript <filename>
    //admin.runNextRound
    //admin.restartRound
    //admin.endRound <teamID>
    //admin.currentLevel
    //admin.supportedMaps <play list>
    //admin.setPlaylist <name>
    //admin.getPlaylist
    //admin.getPlaylists

    // Banning

    // Maplist
    /// BFBC2 Only.
    //mapList.append <name, rounds>
    //mapList.insert <index, name, rounds>
    //mapList.nextLevelIndex [index: integer]

    // Punkbuster

    // Reserved Slots
    /// BFBC2 Only.
    //reservedSlots.load
    //reservedSlots.save
    //reservedSlots.addPlayer <name>
    //reservedSlots.removePlayer <name>
    //reservedSlots.clear
    //reservedSlots.list

    // Variables
    /// BFBC2 Only.
    //vars.adminPassword [password]
    //vars.punkBuster [enabled]
    //vars.hardCore
    //vars.ranked
    //vars.rankLimit [rank]
    //vars.teamBalance [enabled]
    //vars.currentPlayerLimit
    //vars.maxPlayerLimit
    //vars.playerLimit [nr of players]
    //vars.bannerUrl [url]
    //vars.crossHair [enabled]
    //vars.thirdPersonVehicleCameras [enabled]
    //vars.profanityFilter [enabled]
    //vars.textChatModerationMode [moderation mode]
    //vars.textChatSpamTriggerCount [count]
    //vars.textChatSpamDetectionTime [time]
    //vars.textChatSpamCoolDownTime [time]

    // Text Chat Moderation
    //textChatModerationList.load
    //textChatModerationList.save
    //textChatModerationList.add <moderationlevel> <name>
    //textChatModerationList.remove <name>
    //textChatModerationList.clear
    //textChatModerationList.list [startOffset]

    // Level Variables
    //levelVars.set <context> <var name> <value>
    //levelVars.get <context> <var name>
    //levelVars.evaluate <var name>
    //levelVars.clear <context> [var name]
    //levelVars.list <context> [var name]

};

#endif // BFBC2COMMANDHANDLER_H
