#include "ExamplePluginWidget.h"

ExamplePluginWidget::ExamplePluginWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ExamplePluginWidget)
{
    ui->setupUi(this);
}

ExamplePluginWidget::~ExamplePluginWidget()
{
    delete ui;
}
