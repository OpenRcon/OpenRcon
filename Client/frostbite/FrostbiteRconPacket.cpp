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

FrostbiteRconPacket::FrostbiteRconPacket() : packetSequence(0), packetSize(0), packetWordCount(0)
{

}

FrostbiteRconPacket::FrostbiteRconPacket(const int &origin, const int &type, const unsigned int &initseq) : packetSequence(initseq & 0x3FFFFFFF), packetSize(0), packetWordCount(0)
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

    for (unsigned int i = 0; i < packet.getWordCount(); i++) {
        packWord(packet.getWord(i));
    }
}

FrostbiteRconPacket::~FrostbiteRconPacket()
{
    clear();
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

unsigned int FrostbiteRconPacket::getSequenceNum() const
{
    return packetSequence & 0x3FFFFFFF;
}

void FrostbiteRconPacket::packWord(const FrostbiteRconWord &word)
{
    packetSize += word.getFullSize();
    packetWords.push_back(word);
    packetWordCount++;
}

unsigned int FrostbiteRconPacket::getSequence() const
{
    return packetSequence;
}

unsigned int FrostbiteRconPacket::getSize() const
{
    return packetSize;
}

unsigned int FrostbiteRconPacket::getFullSize() const
{
    return 4 + 4 + 4 + packetSize;
}

unsigned int FrostbiteRconPacket::getWordCount() const
{
    return packetWordCount;
}

const FrostbiteRconWord& FrostbiteRconPacket::getWord(const unsigned int &index) const
{
    if (index < packetWordCount) {
        return packetWords[index];
    } else {
        qDebug() << QString("Wrong word index %1.").arg(index);
    }

    return *((FrostbiteRconWord *) 0);
}

void FrostbiteRconPacket::setSequence(const unsigned int &sequence)
{
    packetSequence = sequence;
}

void FrostbiteRconPacket::setSequenceNum(const unsigned int &sequence)
{
    packetSequence = (packetSequence & 0xC0000000) | (sequence & 0x3FFFFFFF);
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

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            packWord(packet.getWord(i));
        }
    }

    return *this;
}
