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

#ifndef ORBFBC2RconWord_H
#define ORBFBC2RconWord_H

#include "ORBFBC2_global.h"

#include <QDebug>
#include <QDataStream>

class OR_BFBC2_EXPORT ORBFBC2RconWord
{

public:
    explicit ORBFBC2RconWord();
    ORBFBC2RconWord(const ORBFBC2RconWord &word);
    ORBFBC2RconWord(const char* str);
    ~ORBFBC2RconWord();

    ORBFBC2RconWord& operator= (const ORBFBC2RconWord &word);
    quint32 getSize() const;
    quint32 getFullSize() const;
    char getTerminator() const;
    void loadString(const char* str);
    void loadData(const char* data, quint32 size);
    const char* getContent() const;
    void clear();

private:
    quint32 wordSize; // Number of bytes in word, excluding trailing null byte
    char* wordContent; // Word contents -- must not contain any null bytes // Not sure is this right.
    char wordTerminator; // Trailing null byte // Not sure is this right.

};

inline QDataStream& operator>>(QDataStream& in, ORBFBC2RconWord &word)
{
    QDataStream::ByteOrder oldbo;
    oldbo = in.byteOrder();

    if (oldbo != QDataStream::LittleEndian) {
        in.setByteOrder(QDataStream::LittleEndian);
    }

    quint32 size;
    char * data = 0;
    qint8 terminator;

    in >> size;

    if (size) {
        data = new char[size];
        in.readRawData(data, size);
    }

    word.loadData(data, size);

    if (data) {
        delete[] data;
    }
    in >> terminator;

    if (oldbo != QDataStream::LittleEndian) {
        in.setByteOrder(oldbo);
    }

    return in;
}

inline QDataStream &operator<< (QDataStream &out, const ORBFBC2RconWord &word)
{
    QDataStream::ByteOrder oldbo;
    oldbo = out.byteOrder();

    if (oldbo != QDataStream::LittleEndian) {
        out.setByteOrder(QDataStream::LittleEndian);
    }

    out << word.getSize();

    const char * wordContent = word.getContent();

    for (quint32 i = 0; i < word.getSize(); i++) {
        out << (quint8) wordContent[i];
    }

    out << (quint8) word.getTerminator();

    if (oldbo != QDataStream::LittleEndian) {
        out.setByteOrder(oldbo);
    }

    return out;
}

#endif // ORBFBC2RconWord_H
