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
    sequence(0),
    size(0),
    wordCount(0)
{

}

FrostbiteRconPacket::FrostbiteRconPacket(const FrostbiteRconPacket &packet, QObject *parent) :
    FrostbiteRconPacket(parent)
{
    sequence = packet.getSequence();

    for (unsigned int i = 0; i < packet.getWordCount(); i++) {
        packWord(packet.getWord(i));
    }
}

FrostbiteRconPacket::FrostbiteRconPacket(const FrostbiteRconPacketOrigin &packetOrigin, const FrostbiteRconPacketType &packetType, unsigned int initSequence, QObject *parent) :
    FrostbiteRconPacket(parent)
{
    sequence = initSequence & 0x3FFFFFFF;

    if (packetOrigin == FrostbiteRconPacketOrigin::ClientOrigin) {
        sequence |= 0x80000000;
    }

    if (packetType == FrostbiteRconPacketType::Response) {
        sequence |= 0x40000000;
    }
}

FrostbiteRconPacket::~FrostbiteRconPacket()
{
    clear();
}

FrostbiteRconPacket &FrostbiteRconPacket::operator=(const FrostbiteRconPacket &packet)
{
    if (&packet != this) {
        clear();
        sequence = packet.getSequence();

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            packWord(packet.getWord(i));
        }
    }

    return *this;
}

void FrostbiteRconPacket::clear()
{
    sequence = 0;
    size = 0;
    wordCount = 0;
    words.clear();
}

const FrostbiteRconWord &FrostbiteRconPacket::getWord(unsigned int index) const
{
    static FrostbiteRconWord emptyWord;

    // TODO: Use Q_ASSERT here?
    if (index < wordCount) {
        return words[index];
    } else {
        qDebug() << tr("Wrong word index %1.").arg(index);
    }

    return emptyWord;
}

void FrostbiteRconPacket::packWord(const FrostbiteRconWord &word)
{
    size += word.getFullSize();
    words.push_back(word);
    wordCount++;
}

unsigned int FrostbiteRconPacket::getSequence() const
{
    return sequence;
}

void FrostbiteRconPacket::setSequence(int sequence)
{
    this->sequence = sequence;
}

unsigned int FrostbiteRconPacket::getSequenceNum() const
{
    return sequence & 0x3FFFFFFF;
}

void FrostbiteRconPacket::setSequenceNum(int sequenceNum)
{
    this->sequence = (sequence & 0xC0000000) | (sequenceNum & 0x3FFFFFFF);
}

unsigned int FrostbiteRconPacket::getSize() const
{
    return size;
}

unsigned int FrostbiteRconPacket::getFullSize() const
{
    return 12 + size;
}

unsigned int FrostbiteRconPacket::getWordCount() const
{
    return wordCount;
}

bool FrostbiteRconPacket::isResponse() const
{
    return sequence & 0x40000000;
}

bool FrostbiteRconPacket::isRequest() const
{
    return sequence & 0x80000000;
}

QDataStream &operator <<(QDataStream &out, const FrostbiteRconPacket &packet)
{
    if (packet.getFullSize() <= MAX_PACKET_SIZE) {
        if (out.byteOrder() != QDataStream::LittleEndian) {
            out.setByteOrder(QDataStream::LittleEndian);
        }

        out << packet.getSequence();
        out << packet.getFullSize();
        out << packet.getWordCount();

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            out << packet.getWord(i);
        }
    }

    return out;
}

QDataStream &operator >>(QDataStream &in, FrostbiteRconPacket &packet)
{
    if (in.byteOrder() != QDataStream::LittleEndian) {
        in.setByteOrder(QDataStream::LittleEndian);
    }

    packet.clear();

    unsigned int sequence, fullSize, wordCount;
    in >> sequence;
    in >> fullSize;
    in >> wordCount;

    packet.setSequence(sequence);

    FrostbiteRconWord word;

    for (unsigned int i = 0; i < wordCount; i++) {
        in >> word;
        packet.packWord(word);
        word.clear();
    }

    return in;
}
