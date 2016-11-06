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

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QTreeWidgetItem>

#include "DragDropTreeWidget.h"

DragDropTreeWidget::DragDropTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setDragDropMode(DragDropMode::DragDrop);
    setAcceptDrops(true);
}

DragDropTreeWidget::~DragDropTreeWidget()
{

}

void DragDropTreeWidget::dragEnterEvent(QDragEnterEvent *event)
{
    DragDropTreeWidget *source = qobject_cast<DragDropTreeWidget *>(event->source());

    if (source) {
        event->accept();
    }
}

void DragDropTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    DragDropTreeWidget *source = qobject_cast<DragDropTreeWidget *>(event->source());

    if (source) {
        event->accept();
    }
}

void DragDropTreeWidget::dropEvent(QDropEvent *event)
{
    DragDropTreeWidget *source = qobject_cast<DragDropTreeWidget *>(event->source());

    if (source && source != this) {
        int index = source->currentIndex().row();
        QTreeWidgetItem *item = source->currentItem();

        event->accept();

        emit (itemDrop(index));
        emit (itemDrop(item));
    }
}
