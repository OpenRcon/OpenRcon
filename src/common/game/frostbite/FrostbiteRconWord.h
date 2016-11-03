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

#ifndef FROSTBITERCONWORD_H
#define FROSTBITERCONWORD_H

#include <QObject>
#include <QDataStream>

class FrostbiteRconWord : public QObject
{
    Q_OBJECT

public:
    FrostbiteRconWord(QObject *parent = nullptr);
    FrostbiteRconWord(const char *word, QObject *parent = nullptr);
    FrostbiteRconWord(const FrostbiteRconWord &word, QObject *parent = nullptr);
    ~FrostbiteRconWord();

    FrostbiteRconWord &operator =(const FrostbiteRconWord &word);
    void clear();
    void loadData(const char *data, unsigned int size);
    unsigned int getSize() const;
    unsigned int getFullSize() const;
    const char *getContent() const;
    char getTerminator() const;

private:
    unsigned int wordSize; // Number of bytes in word, excluding trailing null byte
    char *wordContent; // Word contents -- must not contain any null bytes // Not sure is this right.
    char wordTerminator; // Trailing null byte // Not sure is this right.

};

QDataStream &operator <<(QDataStream &out, const FrostbiteRconWord &word);
QDataStream &operator >>(QDataStream &in, FrostbiteRconWord &word);

#endif // FROSTBITERCONWORD_H
