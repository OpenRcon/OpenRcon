/*
 * Copyright (C) 2014 The OpenRcon Project.
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

#include "CommandHandler.h"

CommandHandler::CommandHandler(QObject *parent) : QObject(parent)
{

}

CommandHandler::~CommandHandler()
{

}

/* These events is triggered everytime the client sends or receives data. */
void CommandHandler::responseDataSentEvent(const QString &request)
{
    emit(onDataSentEvent(request));
}

void CommandHandler::responseDataReceivedEvent(const QString &response)
{
    emit(onDataReceivedEvent(response));
}

void CommandHandler::responseUnknownCommand()
{
    emit (onUnknownCommand());
}

int CommandHandler::toInt(const QString &value)
{
    return value.toInt();
}

bool CommandHandler::toBool(const QString &value)
{
    return value == "true";
}
