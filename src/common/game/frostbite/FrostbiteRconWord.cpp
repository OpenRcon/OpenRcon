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

#include "FrostbiteRconWord.h"

FrostbiteRconWord::FrostbiteRconWord(QObject *parent) : QObject(parent), wordSize(0), wordContent(0), wordTerminator(0)
{

}

FrostbiteRconWord::FrostbiteRconWord(const char *word, QObject *parent) : QObject(parent), wordSize(0), wordContent(0), wordTerminator(0)
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

FrostbiteRconWord::FrostbiteRconWord(const FrostbiteRconWord &word, QObject *parent) : QObject(parent), wordSize(0), wordContent(0), wordTerminator(0)
{
    wordTerminator = word.getTerminator();
    wordSize = word.getSize();

    if (wordSize) {
        wordContent = new char[wordSize + 1];
        strcpy(wordContent, word.getContent());
        wordContent[wordSize] = 0; // Include the null terminator.
    }
}

FrostbiteRconWord::~FrostbiteRconWord()
{
    clear();
}

FrostbiteRconWord &FrostbiteRconWord::operator = (const FrostbiteRconWord &word)
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

void FrostbiteRconWord::clear()
{
    if (wordContent) {
        delete[] wordContent;
        wordContent = nullptr;
    }

    wordSize = 0;
    wordTerminator = 0;
}

void FrostbiteRconWord::loadData(const char *data, unsigned int size)
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

unsigned int FrostbiteRconWord::getSize() const
{
    return wordSize;
}

unsigned int FrostbiteRconWord::getFullSize() const
{
    return 4 + wordSize + 1;
}

const char* FrostbiteRconWord::getContent() const
{
    return wordContent;
}

char FrostbiteRconWord::getTerminator() const
{
    return wordTerminator;
}

QDataStream &operator<<(QDataStream &out, const FrostbiteRconWord &word)
{
    if (out.byteOrder() != QDataStream::LittleEndian) {
        out.setByteOrder(QDataStream::LittleEndian);
    }

    out << word.getSize();

    const char *wordContent = word.getContent();

    for (unsigned int i = 0; i < word.getSize(); i++) {
        out << (signed char) wordContent[i];
    }

    out << (signed char) word.getTerminator();

    return out;
}

QDataStream &operator>>(QDataStream &in, FrostbiteRconWord &word)
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
