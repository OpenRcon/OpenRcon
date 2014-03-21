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

#ifndef DRAGDROPLISTWIDGET_H
#define DRAGDROPLISTWIDGET_H

#include <QListWidget>
#include <QObject>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>
#include <QMimeData>
#include <QDrag>

class DragDropListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit DragDropListWidget(QWidget *parent = 0);
    ~DragDropListWidget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void performDrag();

    QPoint startPos;

signals:
    void dropEvent(const QString&);
    void sameDropEvent(const int&);

};

#endif // DRAGDROPLISTWIDGET_H
