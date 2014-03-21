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

#include "DragDropTreeWidget.h"

DragDropTreeWidget::DragDropTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

DragDropTreeWidget::~DragDropTreeWidget()
{

}

void DragDropTreeWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPos = event->pos();
    }

    QTreeWidget::mousePressEvent(event);
}

void DragDropTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();

        if (distance >= QApplication::startDragDistance()) {
            performDrag();
        }
    }

    QTreeWidget::mouseMoveEvent(event);
}

void DragDropTreeWidget::dragEnterEvent(QDragEnterEvent *event)
{
    DragDropTreeWidget *source = qobject_cast<DragDropTreeWidget *>(event->source());

    if (source && source == this) {
        event->setDropAction(Qt::MoveAction);

        if (currentItem()->parent()) {
            event->accept();
        }
    }
}

void DragDropTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    DragDropTreeWidget *source = qobject_cast<DragDropTreeWidget *>(event->source());

    if (source && source == this) {
        event->setDropAction(Qt::MoveAction);

        if (currentItem()->parent()) {
            event->accept();
        }
    }
}

void DragDropTreeWidget::dropEvent(QDropEvent *event)
{
    DragDropTreeWidget *source = qobject_cast<DragDropTreeWidget *>(event->source());

    if (source && source == this) {
        QTreeWidgetItem *currentItem = this->currentItem();

        if (currentItem->parent()) {
            QString previousTeam = currentItem->parent()->text(0);
            previousTeam.remove("Team ");

            QTreeWidgetItem *pointItem = itemAt(event->pos());

            if (pointItem && pointItem->parent()) {
                QString currentTeam = pointItem->parent()->text(0);
                currentTeam.remove("Team ");

                if (currentTeam != previousTeam && currentTeam != "0") {
                    QTreeWidget::dropEvent(event);
                    emit(dropEvent(currentItem->text(1), currentTeam));
                } else {
                    event->ignore();
                }
            } else {
                event->ignore();
            }
                emit(refresh());
                setCurrentItem(currentItem);
        }
        event->ignore();
    }
}

void DragDropTreeWidget::performDrag()
{
    emit(dragEvent());
}
