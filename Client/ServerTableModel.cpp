/*
 * Copyright (C) 2011 The OpenRcon Project.
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

#include "ServerTableModel.h"
#include "Constants.h"

using namespace Constants;

QVariant ServerTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > rowCount()) {
        return QVariant();
    }

    ServerEntry entry;

    switch (role) {
    case Qt::DisplayRole:
        entry = m_TableData->at(index.row());
        switch (index.column()) {
        case 0:
            return entry.game;
        case 1:
            return entry.name;
        case 2:
            return entry.host;
        case 3:
            return entry.port;
        case 4:
            return entry.password;
        default:
            break;
        }
        break;

    case Qt::DecorationRole:
        if (index.column() == 0) {
            entry = m_TableData->at(index.row());

            if (entry.game == 0) {
                //return QVariant(QIcon(QPixmap(GAME_BFBC2_ICON)));
            } else if (entry.game == 1) {
                //return QVariant(QIcon(QPixmap(GAME_BF3_ICON)));
            } else {
                qDebug() << "Unexpected game type.";
                Q_ASSERT(false);
            }
        }
        break;
    }

    return QVariant();
}


QVariant ServerTableModel::headerData(const int section, Qt::Orientation orientation, const int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Game");
        case 1:
            return tr("Name");
        case 2:
            return tr("Host");
        case 3:
            return tr("Port");
        case 4:
            return tr("Password");
        default:
            break;
        }
    }

    return QVariant();
}
