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

#include "FrostbiteRconPacketWord.h"

FrostbiteRconPacketWord::FrostbiteRconPacketWord(QObject *parent) :
    PacketWord(parent),
    wordSize(0),
    wordContent(0),
    wordTerminator(0)
{

}

FrostbiteRconPacketWord::FrostbiteRconPacketWord(const char *word, QObject *parent) :
    FrostbiteRconPacketWord(parent)
{
    clear();
    wordTerminator = 0;
    wordSize = strlen(word);

    if (wordSize) {
        wordContent = new char[wordSize + 1];
        strcpy(wordContent, word);
        wordContent[wordSize] = 0; // Include the null terminator.
    }
}

FrostbiteRconPacketWord::FrostbiteRconPacketWord(const FrostbiteRconPacketWord &word, QObject *parent) :
    FrostbiteRconPacketWord(parent)
{
    wordTerminator = word.getTerminator();
    wordSize = word.getSize();

    if (wordSize) {
        wordContent = new char[wordSize + 1];
        strcpy(wordContent, word.getContent());
        wordContent[wordSize] = 0; // Include the null terminator.
    }
}

FrostbiteRconPacketWord::~FrostbiteRconPacketWord()
{
    clear();
}

FrostbiteRconPacketWord &FrostbiteRconPacketWord::operator =(const FrostbiteRconPacketWord &word)
{
    if (&word != this) {
        clear();
        wordTerminator = word.getTerminator();
        wordSize = word.getSize();

        if (wordSize) {
            wordContent = new char[wordSize + 1];
            strcpy(wordContent, word.getContent());
            wordContent[wordSize] = 0; // Include the null terminator.
        }
    }

    return *this;
}

void FrostbiteRconPacketWord::clear()
{
    wordSize = 0;

    if (wordContent) {
        delete[] wordContent;
        wordContent = nullptr;
    }

    wordTerminator = 0;
}

void FrostbiteRconPacketWord::loadData(const char *data, unsigned int size)
{
    clear();
    wordTerminator = 0;
    wordSize = size;

    if (wordSize) {
        wordContent = new char[wordSize + 1];
        memcpy(wordContent, data, wordSize);
        wordContent[wordSize] = 0; // Include the null terminator.
    }
}

unsigned int FrostbiteRconPacketWord::getSize() const
{
    return wordSize;
}

unsigned int FrostbiteRconPacketWord::getFullSize() const
{
    return 4 + wordSize + 1;
}

const char* FrostbiteRconPacketWord::getContent() const
{
    return wordContent;
}

char FrostbiteRconPacketWord::getTerminator() const
{
    return wordTerminator;
}

QDataStream &operator <<(QDataStream &out, const FrostbiteRconPacketWord &word)
{
    if (out.byteOrder() != QDataStream::LittleEndian) {
        out.setByteOrder(QDataStream::LittleEndian);
    }

    out << word.getSize();
    out.writeRawData(word.getContent(), word.getSize());
    out << (signed char) word.getTerminator();

    return out;
}

QDataStream &operator >>(QDataStream &in, FrostbiteRconPacketWord &word)
{
    if (in.byteOrder() != QDataStream::LittleEndian) {
        in.setByteOrder(QDataStream::LittleEndian);
    }

    unsigned int size;
    char *data = nullptr;
    signed char terminator;

    in >> size;

    if (size) {
        data = new char[size];
        in.readRawData(data, size);
    }

    word.loadData(data, size);

    in >> terminator;

    if (data) {
        delete[] data;
    }

    return in;
}
