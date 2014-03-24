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

#include "FrostbiteRconPacket.h"

FrostbiteRconPacket::FrostbiteRconPacket(QObject *parent) : QObject(parent), packetSequence(0), packetSize(0), packetWordCount(0)
{

}

FrostbiteRconPacket::FrostbiteRconPacket(int origin, int type, quint32 initseq) : packetSequence(initseq & 0x3FFFFFFF), packetSize(0), packetWordCount(0)
{
    if (origin == ClientOrigin) {
        packetSequence |= 0x80000000;
    }

    if (type == Response) {
        packetSequence |= 0x40000000;
    }
}

FrostbiteRconPacket::FrostbiteRconPacket(const FrostbiteRconPacket &packet) : packetSequence(0), packetSize(0), packetWordCount(0)
{
    packetSequence = packet.getSequence();

    for (quint32 i = 0; i < packet.getWordCount(); i++) {
        packWord(packet.getWord(i));
    }
}

bool FrostbiteRconPacket::isResponse() const
{
    if (packetSequence & 0x40000000) {
        return true;
    }
    return false;
}

bool FrostbiteRconPacket::isRequest() const
{
    return !isResponse();
}

quint32 FrostbiteRconPacket::getSequenceNum() const
{
    return packetSequence & 0x3FFFFFFF;
}

void FrostbiteRconPacket::packWord(const FrostbiteRconWord &word)
{
    packetSize += word.getFullSize();
    packetWordCount++;
    packetWords.push_back(word);
}

quint32 FrostbiteRconPacket::getSequence() const
{
    return packetSequence;
}

quint32 FrostbiteRconPacket::getSize() const
{
    return packetSize;
}

quint32 FrostbiteRconPacket::getFullSize() const
{
    return 4 + 4 + 4 + packetSize;
}

quint32 FrostbiteRconPacket::getWordCount() const
{
    return packetWordCount;
}

const FrostbiteRconWord& FrostbiteRconPacket::getWord(quint32 i) const
{
    if (i < packetWordCount) {
        return packetWords[i];
    } else {
        qDebug() << QString("Wrong word index %1.").arg(i);
    }
    return *((FrostbiteRconWord *) 0);
}

void FrostbiteRconPacket::setSequence(quint32 seq)
{
    packetSequence = seq;
}

void FrostbiteRconPacket::setSequenceNum(quint32 seq)
{
    packetSequence = (packetSequence & 0xC0000000) | (seq & 0x3FFFFFFF);
}

void FrostbiteRconPacket::clear()
{
    packetSequence = 0;
    packetSize = 0;
    packetWordCount = 0;
    packetWords.clear();
}

FrostbiteRconPacket &FrostbiteRconPacket::operator= (const FrostbiteRconPacket &packet)
{
    if (&packet != this) {
        clear();
        packetSequence = packet.getSequence();
        for (quint32 i = 0; i < packet.getWordCount(); i++) {
            packWord(packet.getWord(i));
        }
    } else {
        qDebug() << "FrostbiteRconPacket::operator= (this)";
    }

    return *this;
}

FrostbiteRconPacket::~FrostbiteRconPacket()
{
    clear();
}
