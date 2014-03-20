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

#ifndef ORBFBC2RCONPACKET_H
#define ORBFBC2RCONPACKET_H

#include "ORBFBC2_global.h"

#include <QDataStream>
#include <QVector>

#include "ORBFBC2RconWord.h"

class OR_BFBC2_EXPORT ORBFBC2RconPacket
{

public:
    explicit ORBFBC2RconPacket();
    ORBFBC2RconPacket(int origin, int type, quint32 initseq = 0);
    ORBFBC2RconPacket(const ORBFBC2RconPacket &packet);
    ~ORBFBC2RconPacket();

    enum { ServerOrigin = 0, ClientOrigin = 1 };
    enum { Request = 0, Response = 1 };

    const ORBFBC2RconWord &getWord(quint32 i) const;
    ORBFBC2RconPacket &operator= (const ORBFBC2RconPacket &packet);
    void packWord(const ORBFBC2RconWord &word);
    quint32 getSequence() const;
    quint32 getSequenceNum() const;
    quint32 getSize() const;
    quint32 getFullSize() const;
    quint32 getWordCount() const;
    bool isResponse() const;
    bool isRequest() const;
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

    //BFBC2RconWord packetWords[MAX_WORDS];

    QVector<ORBFBC2RconWord> packetWords;

};

inline QDataStream &operator>> (QDataStream &in, ORBFBC2RconPacket &packet)
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
    ORBFBC2RconWord word;

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

inline QDataStream &operator<< (QDataStream &out, const ORBFBC2RconPacket &packet)
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

#endif // BFBC2RCONPACKET_H
