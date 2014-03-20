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

#include "BFBC2RconWord.h"

BFBC2RconWord::BFBC2RconWord() : wordSize(0), wordContent(0), wordTerminator(0)
{

}

BFBC2RconWord::BFBC2RconWord(const char* str) : wordSize(0), wordContent(0), wordTerminator(0)
{
    loadString(str);
}

BFBC2RconWord::BFBC2RconWord(const BFBC2RconWord &word) : wordSize(0), wordContent(0), wordTerminator(0)
{
    wordTerminator = word.getTerminator();
    wordSize = word.getSize();

    if (wordSize) {
        wordContent = new char[wordSize + 1];
        memcpy(wordContent, word.getContent(), wordSize);
        wordContent[wordSize] = 0; // Include the null terminator.
    }
}

BFBC2RconWord &BFBC2RconWord::operator = (const BFBC2RconWord &word)
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

quint32 BFBC2RconWord::getSize() const
{
    return wordSize;
}

quint32 BFBC2RconWord::getFullSize() const
{
    return 4 + wordSize + 1;
}

const char* BFBC2RconWord::getContent() const
{
    return wordContent;
}

char BFBC2RconWord::getTerminator() const
{
    return wordTerminator;
}

void BFBC2RconWord::loadString(const char* str)
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

void BFBC2RconWord::loadData(const char* data, quint32 size)
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

void BFBC2RconWord::clear()
{
    if (wordContent) {
        delete[] wordContent;
        wordContent = 0;
    }

    wordSize = 0;
    wordTerminator = 0;
}

BFBC2RconWord::~BFBC2RconWord()
{
    clear();
}
