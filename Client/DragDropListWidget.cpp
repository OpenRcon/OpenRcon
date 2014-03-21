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

#include "DragDropListWidget.h"

DragDropListWidget::DragDropListWidget(QWidget *parent) : QListWidget(parent)
{
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

DragDropListWidget::~DragDropListWidget()
{

}

void DragDropListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPos = event->pos();
    }

    QListWidget::mousePressEvent(event);
}

void DragDropListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();

        if (distance >= QApplication::startDragDistance()) {
            performDrag();
        }
    }

    QListWidget::mouseMoveEvent(event);
}

void DragDropListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    DragDropListWidget *source = qobject_cast<DragDropListWidget *>(event->source());

    if (source) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }

}

void DragDropListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    DragDropListWidget *source = qobject_cast<DragDropListWidget *>(event->source());

    if (source) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }

}

void DragDropListWidget::dropEvent(QDropEvent *event)
{
    DragDropListWidget *source = qobject_cast<DragDropListWidget *>(event->source());

    if (source && source != this) {
        addItem(event->mimeData()->text());
        event->setDropAction(Qt::CopyAction);
        event->accept();
        emit(dropEvent(event->mimeData()->text()));
    }

    if (source && source == this) {
        int oldRow = currentRow();
        QListWidget::dropEvent(event);
        emit(sameDropEvent(oldRow));
    }
}

void DragDropListWidget::performDrag()
{
    QListWidgetItem *item = currentItem();

    if (item) {
        QMimeData *mimeData = new QMimeData;
        QString data = item->text();
        mimeData->setText(data);
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        if (drag->exec(Qt::CopyAction) == Qt::CopyAction) {
        }
    }
}
