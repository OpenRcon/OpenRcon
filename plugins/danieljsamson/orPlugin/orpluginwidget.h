/*
Copyright (C) 2010 The OpenRcon Project.

This file is part of OpenRcon.

OpenRcon is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenRcon is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ORPLUGINWIDGET_H
#define ORPLUGINWIDGET_H

#include <QWidget>
#include "orplugininterface.h"
#include "orPlugin_global.h"
namespace Ui {
    class ORPLUGINSHARED_EXPORT orPluginWidget;
}

class orPluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit orPluginWidget(QWidget *parent = 0);
    ~orPluginWidget();

public slots:
    void send();
private:
    Ui::orPluginWidget *ui;
    void createGUI();
    bool loadPlugin();
    //orPluginInterface *Interface;
};

#endif // ORPLUGINWIDGET_H
