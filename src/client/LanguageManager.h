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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QObject>

class QString;
template<class T>
class QList;

class LanguageEntry;

class LanguageManager : public QObject
{
    Q_OBJECT

public:
    LanguageManager(QObject *parent = nullptr);
    ~LanguageManager();

    LanguageEntry getLanguage(int index) const;
    LanguageEntry getLanguage(const QString &code) const;
    QList<LanguageEntry> getLanguages() const;

private:
    QList<LanguageEntry> languageList;

};

#endif // LANGUAGEMANAGER_H
