#ifndef EXAMPLEPLUGINWIDGET_H
#define EXAMPLEPLUGINWIDGET_H

#include <QWidget>

#include "ExamplePlugin_global.h"

#include "ui_ExamplePluginWidget.h"

#include "ExamplePluginInterface.h"

class ExamplePluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExamplePluginWidget(QWidget *parent = 0);
    ~ExamplePluginWidget();

private:
    Ui::ExamplePluginWidget *ui;

    // ExamplePluginInterface *Interface;
};

#endif // EXAMPLEPLUGINWIDGET_H
