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

#ifndef LANGUAGEENTRY_H
#define LANGUAGEENTRY_H

#include <QString>
#include <QIcon>

struct LanguageEntry
{
    LanguageEntry()
    {

    }

    LanguageEntry(const QString &name,
                  const QString &code,
                  const QString &icon) :
        name(name),
        code(code),
        icon(QIcon(icon))
    {

    }

    QString name;
    QString code;
    QIcon icon;

};

// For use with QVariant
Q_DECLARE_METATYPE(LanguageEntry)

#endif // LANGUAGEENTRY_H
