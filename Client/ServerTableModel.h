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

#ifndef SERVERTABLEMODEL_H
#define SERVERTABLEMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QPixmap>
#include <QIcon>

#include "ServerEntry.h"

class ServerTableModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ServerTableModel(QList<ServerEntry>* tableData, QObject* parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, const int role = Qt::DisplayRole) const;
    virtual QVariant headerData(const int section, Qt::Orientation orientation, const int role = Qt::DisplayRole) const;

    QList<ServerEntry> *getTableData() const;

protected:
    QList<ServerEntry> *m_TableData;

};

inline ServerTableModel::ServerTableModel(QList<ServerEntry> *tableData, QObject* parent) : QAbstractListModel(parent), m_TableData(tableData)
{

}

inline int ServerTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_TableData->count();
}

inline int ServerTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 5;
}

inline QList<ServerEntry> *ServerTableModel::getTableData() const
{
    return m_TableData;
}

#endif // SERVERTABLEMODEL_H
