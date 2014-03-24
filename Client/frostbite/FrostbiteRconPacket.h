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

#ifndef FROSTBITERCONPACKET_H
#define FROSTBITERCONPACKET_H

#include "FrostbiteRconWord.h"

//#define MAX_WORDS 100 // TODO: Think this right.

// TODO: Should qint32 be replaced by RconUint?

class FrostbiteRconPacket : QObject
{
    Q_OBJECT

public:
    enum { ServerOrigin = 0, ClientOrigin = 1 };
    enum { Request = 0, Response = 1 };

    explicit FrostbiteRconPacket(QObject *parent = 0);
    ~FrostbiteRconPacket();

    FrostbiteRconPacket(int origin, int type, quint32 initseq = 0);
    FrostbiteRconPacket(const FrostbiteRconPacket &packet);
    FrostbiteRconPacket &operator= (const FrostbiteRconPacket &packet);
    void packWord(const FrostbiteRconWord &word);
    quint32 getSequence() const;
    quint32 getSequenceNum() const;
    quint32 getSize() const;
    quint32 getFullSize() const;
    quint32 getWordCount() const;
    bool isResponse() const;
    bool isRequest() const;
    const FrostbiteRconWord &getWord(quint32 i) const;
    void setSequence(quint32 seq);
    void setSequenceNum(quint32 seq);
    void clear();

    // Packet
    /*
        Sequence
        Bit 31: 0 = The command in this command/response pair originated on the server
        1 = The command in this command/response pair originated on the client
        Bit 30: 0 = Request, 1 = Response
        Bits 29..0: Sequence number (this is used to match requests/responses in a full duplex
        transmission)
    */

    quint32 packetSequence;

    quint32 packetSize; // Total size of packet, in bytes
    quint32 packetWordCount; // Number of words following the packet header
    //RconWord packetWords[MAX_WORDS];

    QVector<FrostbiteRconWord> packetWords;

};

inline QDataStream &operator >> (QDataStream &in, FrostbiteRconPacket &packet)
{
    QDataStream::ByteOrder oldbo;
    oldbo = in.byteOrder();

    if (oldbo != QDataStream::LittleEndian) {
        in.setByteOrder(QDataStream::LittleEndian);
    }

    packet.clear();

    quint32 seq, fsize, words;

    in >> seq;
    in >> fsize;
    in >> words;
    FrostbiteRconWord word;

    packet.setSequence(seq);

    for (quint32 i = 0; i < words; i++) {
        in >> word;
        packet.packWord(word);
    }

    if (oldbo != QDataStream::LittleEndian) {
        in.setByteOrder(oldbo);
    }

    return in;
}

inline QDataStream &operator << (QDataStream &out, const FrostbiteRconPacket &packet)
{
    QDataStream::ByteOrder oldbo;
    oldbo = out.byteOrder();

    if (oldbo != QDataStream::LittleEndian) {
        out.setByteOrder(QDataStream::LittleEndian);
    }

    out << packet.getSequence();
    out << packet.getFullSize();
    out << packet.getWordCount();

    for (quint32 i = 0; i < packet.getWordCount(); i++) {
        out << packet.getWord(i);
    }

    if (oldbo != QDataStream::LittleEndian) {
        out.setByteOrder(oldbo);
    }

    return out;
}

#endif // FROSTBITERCONPACKET_H
