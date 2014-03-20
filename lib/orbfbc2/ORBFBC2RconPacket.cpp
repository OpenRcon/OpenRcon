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

#include "ORBFBC2RconPacket.h"

ORBFBC2RconPacket::ORBFBC2RconPacket() : packetSequence(0), packetSize(0), packetWordCount(0)
{

}

ORBFBC2RconPacket::ORBFBC2RconPacket(int origin, int type, quint32 initseq) : packetSequence(initseq & 0x3FFFFFFF), packetSize(0), packetWordCount(0)
{
    if (origin == ClientOrigin) {
        packetSequence |= 0x80000000;
    }

    if (type == Response) {
        packetSequence |= 0x40000000;
    }
}

ORBFBC2RconPacket::ORBFBC2RconPacket(const ORBFBC2RconPacket& packet) : packetSequence(0), packetSize(0), packetWordCount(0)
{
    packetSequence = packet.getSequence();
    for (quint32 i = 0; i < packet.getWordCount(); i++) {
        packWord(packet.getWord(i));
    }
}

ORBFBC2RconPacket::~ORBFBC2RconPacket()
{
    clear();
}

bool ORBFBC2RconPacket::isResponse() const
{
    if (packetSequence & 0x40000000) {
        return true;
    }

    return false;
}

bool ORBFBC2RconPacket::isRequest() const
{
    return !isResponse();
}

quint32 ORBFBC2RconPacket::getSequenceNum() const
{
    return packetSequence & 0x3FFFFFFF;
}

void ORBFBC2RconPacket::packWord(const ORBFBC2RconWord &word)
{
    packetSize += word.getFullSize();
    packetWordCount++;
    packetWords.push_back(word);
}

quint32 ORBFBC2RconPacket::getSequence() const
{
    return packetSequence;
}

quint32 ORBFBC2RconPacket::getSize() const
{
    return packetSize;
}

quint32 ORBFBC2RconPacket::getFullSize() const
{
    return 4 + 4 + 4 + packetSize;
}

quint32 ORBFBC2RconPacket::getWordCount() const
{
    return packetWordCount;
}

const ORBFBC2RconWord &ORBFBC2RconPacket::getWord(quint32 i) const
{
    if (i < packetWordCount) {
        return packetWords[i];
    } else {
        qDebug() << QString("Wrong word index %1.").arg(i);
    }
    return *((ORBFBC2RconWord *) 0);
}

void ORBFBC2RconPacket::setSequence(quint32 seq)
{
    packetSequence = seq;
}

void ORBFBC2RconPacket::setSequenceNum(quint32 seq)
{
    packetSequence = (packetSequence & 0xC0000000) | (seq & 0x3FFFFFFF);
}

void ORBFBC2RconPacket::clear()
{
    packetSequence = 0;
    packetSize = 0;
    packetWordCount = 0;
    packetWords.clear();
}

ORBFBC2RconPacket &ORBFBC2RconPacket::operator= (const ORBFBC2RconPacket &packet)
{
    if (&packet != this) {
        clear();
        packetSequence = packet.getSequence();
        for (quint32 i = 0; i < packet.getWordCount(); i++) {
            packWord(packet.getWord(i));
        }
    } else {
        qDebug() << "ORBFBC2RconPacket::operator= (this)";
    }

    return *this;
}
