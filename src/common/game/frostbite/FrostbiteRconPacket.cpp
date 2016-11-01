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

#include <QDebug>

#include "FrostbiteRconPacket.h"
#include "FrostbiteRconPacketOrigin.h"
#include "FrostbiteRconPacketType.h"
#include "FrostbiteRconWord.h"

FrostbiteRconPacket::FrostbiteRconPacket(QObject *parent) : QObject(parent),
    packetSequence(0),
    packetSize(0),
    packetWordCount(0)
{

}

FrostbiteRconPacket::FrostbiteRconPacket(const FrostbiteRconPacket &packet, QObject *parent) :
    FrostbiteRconPacket(parent)
{
    packetSequence = packet.getSequence();

    for (unsigned int i = 0; i < packet.getWordCount(); i++) {
        packWord(packet.getWord(i));
    }
}

FrostbiteRconPacket::FrostbiteRconPacket(const FrostbiteRconPacketOrigin &packetOrigin, const FrostbiteRconPacketType &packetType, unsigned int initSequence, QObject *parent) :
    FrostbiteRconPacket(parent)
{
    packetSequence = initSequence & 0x3FFFFFFF;

    if (packetOrigin == FrostbiteRconPacketOrigin::ClientOrigin) {
        packetSequence |= 0x80000000;
    }

    if (packetType == FrostbiteRconPacketType::Response) {
        packetSequence |= 0x40000000;
    }
}

FrostbiteRconPacket::~FrostbiteRconPacket()
{
    clear();
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

void FrostbiteRconPacket::clear()
{
    packetSequence = 0;
    packetSize = 0;
    packetWordCount = 0;
    packetWords.clear();
}

const FrostbiteRconWord& FrostbiteRconPacket::getWord(unsigned int index) const
{
    static FrostbiteRconWord emptyWord;

    // TODO: Use Q_ASSERT here?
    if (index < packetWordCount) {
        return packetWords[index];
    } else {
        qDebug() << tr("Wrong word index %1.").arg(index);
    }

    return emptyWord;
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

void FrostbiteRconPacket::setSequence(int sequence)
{
    packetSequence = sequence;
}

unsigned int FrostbiteRconPacket::getSequenceNum() const
{
    return packetSequence & 0x3FFFFFFF;
}

void FrostbiteRconPacket::setSequenceNum(int sequence)
{
    packetSequence = (packetSequence & 0xC0000000) | (sequence & 0x3FFFFFFF);
}

unsigned int FrostbiteRconPacket::getSize() const
{
    return packetSize;
}

unsigned int FrostbiteRconPacket::getFullSize() const
{
    return 12 + packetSize;
}

unsigned int FrostbiteRconPacket::getWordCount() const
{
    return packetWordCount;
}

bool FrostbiteRconPacket::isResponse() const
{
    return packetSequence & 0x40000000;
}

bool FrostbiteRconPacket::isRequest() const
{
    return !isResponse();
}
