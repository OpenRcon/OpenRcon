#include "MinecraftWidget.h"

MinecraftWidget::MinecraftWidget(QWidget *parent) : QWidget(parent), ui(new Ui::Minecraft)
{
    ui->setupUi(this);
}

MinecraftWidget::~MinecraftWidget()
{
    delete ui;
}

void MinecraftWidget::logMessage(const int &type, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QTime::currentTime().toString());

    if (type == 0) {
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 1) {
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 2) {
        ui->textEdit_co_co_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 3) {
        ui->textEdit_co_co_output->append(QString("%1 <span style=\"color:#0000FF\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 4) {
        ui->textEdit_ch_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else {
        ui->textEdit_co_co_output->append(QString("%1 %2").arg(currentTime).arg(message));
    }
}

void MinecraftWidget::logEvents(const int &event, const QString &message)
{

}

void MinecraftWidget::on_pushButton_co_co_send_clicked()
{
    QString command = ui->lineEdit_co_co_input->text();

    ui->lineEdit_co_co_input->clear();
}
