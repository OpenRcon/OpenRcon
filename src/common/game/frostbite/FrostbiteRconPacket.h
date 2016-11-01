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

#ifndef FROSTBITERCONPACKET_H
#define FROSTBITERCONPACKET_H

#include <QVector>
#include <QDataStream>

#include "FrostbiteRconWord.h"

#define MAX_PACKET_SIZE 16384

enum class FrostbiteRconPacketOrigin;
enum class FrostbiteRconPacketType;

class FrostbiteRconPacket : public QObject
{
    Q_OBJECT

public:
    FrostbiteRconPacket(QObject *parent = nullptr);
    FrostbiteRconPacket(const FrostbiteRconPacket &packet, QObject *parent = nullptr);
    FrostbiteRconPacket(const FrostbiteRconPacketOrigin &packetOrigin, const FrostbiteRconPacketType &packetType, unsigned int initSequence = 0, QObject *parent = nullptr);
    ~FrostbiteRconPacket();
    FrostbiteRconPacket &operator=(const FrostbiteRconPacket &packet);

    void clear();
    const FrostbiteRconWord &getWord(unsigned int index) const;
    void packWord(const FrostbiteRconWord &word);
    unsigned int getSequence() const;
    void setSequence(int sequence);
    unsigned int getSequenceNum() const;
    void setSequenceNum(int sequence);
    unsigned int getSize() const;
    unsigned int getFullSize() const;
    unsigned int getWordCount() const;
    bool isResponse() const;
    bool isRequest() const;

private:
    unsigned int packetSequence;
    unsigned int packetSize; // Total size of packet, in bytes
    unsigned int packetWordCount; // Number of words following the packet header
    QVector<FrostbiteRconWord> packetWords; // RconWord packetWords[MAX_WORDS];

};

inline QDataStream &operator>> (QDataStream &in, FrostbiteRconPacket &packet)
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
    }

    return in;
}

inline QDataStream &operator<< (QDataStream &out, const FrostbiteRconPacket &packet)
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

#endif // FROSTBITERCONPACKET_H
