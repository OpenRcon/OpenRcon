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

FrostbiteRconWord::FrostbiteRconWord() : wordSize(0), wordContent(0), wordTerminator(0)
{

}

FrostbiteRconWord::FrostbiteRconWord(const char* str) : wordSize(0), wordContent(0), wordTerminator(0)
{
    loadString(str);
}

FrostbiteRconWord::FrostbiteRconWord(const FrostbiteRconWord &word) : wordSize(0), wordContent(0), wordTerminator(0)
{
    wordTerminator = word.getTerminator();
    wordSize = word.getSize();

    if (wordSize) {
        wordContent = new char[wordSize + 1];
        memcpy(wordContent, word.getContent(), wordSize);
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
            memcpy(wordContent, word.getContent(), wordSize);
            wordContent[wordSize] = 0; // Include the null terminator.
        }
    }
    return *this;
}

quint32 FrostbiteRconWord::getSize() const
{
    return wordSize;
}

quint32 FrostbiteRconWord::getFullSize() const
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

void FrostbiteRconWord::loadString(const char* str)
{
    clear();
    wordTerminator = 0;
    wordSize = strlen(str);

    if (wordSize) {
        wordContent = new char[wordSize + 1];
        memcpy(wordContent, str, wordSize);
        wordContent[wordSize] = 0; // Include the null terminator.
    }
}

void FrostbiteRconWord::loadData(const char* data, unsigned int size)
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

void FrostbiteRconWord::clear()
{
    if (wordContent) {
        delete[] wordContent;
        wordContent = 0;
    }

    wordSize = 0;
    wordTerminator = 0;
}


