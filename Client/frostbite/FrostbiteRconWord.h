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

#ifndef FROSTBITERCONWORD_H
#define FROSTBITERCONWORD_H

#include <QDebug>
#include <QDataStream>

class FrostbiteRconWord
{

public:
    explicit FrostbiteRconWord();
    explicit FrostbiteRconWord(const FrostbiteRconWord &word);
    explicit FrostbiteRconWord(const char* str);
    FrostbiteRconWord &operator= (const FrostbiteRconWord &word);
    ~FrostbiteRconWord();

    void clear();
    void loadData(const char* data, const unsigned int &size);
    unsigned int getSize() const;
    unsigned int getFullSize() const;
    const char* getContent() const;
    char getTerminator() const;

private:
    unsigned int wordSize; // Number of bytes in word, excluding trailing null byte
    char* wordContent; // Word contents -- must not contain any null bytes // Not sure is this right.
    char wordTerminator; // Trailing null byte // Not sure is this right.

};

inline QDataStream &operator >> (QDataStream &in, FrostbiteRconWord &word)
{
    QDataStream::ByteOrder oldbo;
    oldbo = in.byteOrder();

    if (oldbo != QDataStream::LittleEndian) {
        in.setByteOrder(QDataStream::LittleEndian);
    }

    unsigned int size;
    char * data = 0;
    signed char terminator;

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

inline QDataStream &operator << (QDataStream &out, const FrostbiteRconWord &word)
{
    QDataStream::ByteOrder oldbo;
    oldbo = out.byteOrder();

    if (oldbo != QDataStream::LittleEndian) {
        out.setByteOrder(QDataStream::LittleEndian);
    }

    out << word.getSize();

    const char * wordContent = word.getContent();

    for (unsigned int i = 0; i < word.getSize(); i++) {
        out << (signed char) wordContent[i];
    }

    out << (signed char) word.getTerminator();

    if (oldbo != QDataStream::LittleEndian) {
        out.setByteOrder(oldbo);
    }

    return out;
}

#endif // FROSTBITERCONWORD_H
