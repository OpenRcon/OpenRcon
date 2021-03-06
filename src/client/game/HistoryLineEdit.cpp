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

#include <QKeyEvent>

#include "HistoryLineEdit.h"

HistoryLineEdit::HistoryLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

HistoryLineEdit::~HistoryLineEdit()
{

}

void HistoryLineEdit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        if (!historyList.isEmpty() && it > historyList.begin()) {
            it--;
            setText(*it);
        }
        break;

    case Qt::Key_Down:
        if (!historyList.isEmpty() && it < historyList.end() ) {
            it++;

            if (it < historyList.end()) {
                setText(*it);
            } else {
                clear();
            }
        }
        break;

    case Qt::Key_Return:
        if (!text().isEmpty()) {
            historyList.append(text());
            it = historyList.end();
        }

        QLineEdit::keyPressEvent(event);
        break;

    default:
        QLineEdit::keyPressEvent(event);
        break;
    }
}
