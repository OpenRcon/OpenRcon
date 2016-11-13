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

class BFBC2CommandHandler : public FrostbiteCommandHandler
{
    Q_OBJECT

public:
    BFBC2CommandHandler(QObject *parent = nullptr);
    ~BFBC2CommandHandler() final;

    bool parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket) final;

public slots:
    /* Send commands */
    // Misc
    void sendHelpCommand();

    // Admin
    //admin.runscript <filename>
    //admin.endRound <teamID>
    //admin.currentLevel
    //admin.supportedMaps <play list>
    //admin.setPlaylist <name>
    //admin.getPlaylist
    //admin.getPlaylists

    // Maplist
    //mapList.append <name, rounds>
    //mapList.insert <index, name, rounds>
    //mapList.nextLevelIndex [index: integer]

    // Reserved Slots
    //reservedSlots.load
    //reservedSlots.save
    //reservedSlots.addPlayer <name>
    //reservedSlots.removePlayer <name>
    //reservedSlots.clear
    //reservedSlots.list

    // Variables
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

    /* Parse commands */
    // Misc
    //help

    // Admin
    //admin.runscript <filename>
    //admin.endRound <teamID>
    //admin.currentLevel
    //admin.supportedMaps <play list>
    //admin.setPlaylist <name>
    //admin.getPlaylist
    //admin.getPlaylists

    // Maplist
    //mapList.append <name, rounds>
    //mapList.insert <index, name, rounds>
    //mapList.nextLevelIndex [index: integer]

    // Reserved Slots
    //reservedSlots.load
    //reservedSlots.save
    //reservedSlots.addPlayer <name>
    //reservedSlots.removePlayer <name>
    //reservedSlots.clear
    //reservedSlots.list

    // Variables
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
    //help

    // Admin
    //admin.runscript <filename>
    //admin.endRound <teamID>
    //admin.currentLevel
    //admin.supportedMaps <play list>
    //admin.setPlaylist <name>
    //admin.getPlaylist
    //admin.getPlaylists

    // Maplist
    //mapList.append <name, rounds>
    //mapList.insert <index, name, rounds>
    //mapList.nextLevelIndex [index: integer]

    // Reserved Slots
    //reservedSlots.load
    //reservedSlots.save
    //reservedSlots.addPlayer <name>
    //reservedSlots.removePlayer <name>
    //reservedSlots.clear
    //reservedSlots.list

    // Variables
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
