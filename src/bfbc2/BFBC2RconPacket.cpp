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

#include "BFBC2RconPacket.h"

BFBC2RconPacket::BFBC2RconPacket() : packetSequence(0), packetSize(0), packetWordCount(0)
{

}

BFBC2RconPacket::BFBC2RconPacket(int origin, int type, quint32 initseq) : packetSequence(initseq & 0x3FFFFFFF), packetSize(0), packetWordCount(0)
{
    if (origin == ClientOrigin) {
        packetSequence |= 0x80000000;
    }

    if (type == Response) {
        packetSequence |= 0x40000000;
    }
}

BFBC2RconPacket::BFBC2RconPacket(const BFBC2RconPacket &packet) : packetSequence(0), packetSize(0), packetWordCount(0)
{
    packetSequence = packet.getSequence();
    for (quint32 i = 0; i < packet.getWordCount(); i++) {
        packWord(packet.getWord(i));
    }
}

bool BFBC2RconPacket::isResponse() const
{
    if (packetSequence & 0x40000000) {
        return true;
    }
    return false;
}

bool BFBC2RconPacket::isRequest() const
{
    return !isResponse();
}

quint32 BFBC2RconPacket::getSequenceNum() const
{
    return packetSequence & 0x3FFFFFFF;
}

void BFBC2RconPacket::packWord(const BFBC2RconWord &word)
{
    packetSize += word.getFullSize();
    packetWordCount++;
    packetWords.push_back(word);
}

quint32 BFBC2RconPacket::getSequence() const
{
    return packetSequence;
}

quint32 BFBC2RconPacket::getSize() const
{
    return packetSize;
}

quint32 BFBC2RconPacket::getFullSize() const
{
    return 4 + 4 + 4 + packetSize;
}

quint32 BFBC2RconPacket::getWordCount() const
{
    return packetWordCount;
}

const BFBC2RconWord& BFBC2RconPacket::getWord(quint32 i) const
{
    if (i < packetWordCount) {
        return packetWords[i];
    } else {
        qDebug() << QString("Wrong word index %1.").arg(i);
    }
    return *((BFBC2RconWord *) 0);
}

void BFBC2RconPacket::setSequence(quint32 seq)
{
    packetSequence = seq;
}

void BFBC2RconPacket::setSequenceNum(quint32 seq)
{
    packetSequence = (packetSequence & 0xC0000000) | (seq & 0x3FFFFFFF);
}

void BFBC2RconPacket::clear()
{
    packetSequence = 0;
    packetSize = 0;
    packetWordCount = 0;
    packetWords.clear();
}

BFBC2RconPacket &BFBC2RconPacket::operator= (const BFBC2RconPacket &packet)
{
    if (&packet != this) {
        clear();
        packetSequence = packet.getSequence();
        for (quint32 i = 0; i < packet.getWordCount(); i++) {
            packWord(packet.getWord(i));
        }
    } else {
        qDebug() << "BFBC2RconPacket::operator= (this)";
    }

    return *this;
}

BFBC2RconPacket::~BFBC2RconPacket()
{
    clear();
}
