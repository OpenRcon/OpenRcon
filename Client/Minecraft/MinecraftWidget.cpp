#include "MinecraftWidget.h"

MinecraftWidget::MinecraftWidget(const QString &host, const int &port, const QString &password) : Minecraft(host, port, password), ui(new Ui::Minecraft)
{
    ui->setupUi(this);

    connect(con, SIGNAL(onAuthenticated(bool)), this, SLOT(slotAuthenticated(bool)));
    connect(con, SIGNAL(onPacket(QString)), this, SLOT(slotPacket(QString)));
    connect(con, SIGNAL(onUnknownCommand()), this, SLOT(slotUnknownCommand()));

    connect(ui->lineEdit_co_input, SIGNAL(returnPressed()), this, SLOT(on_pushButton_co_co_send_clicked()));
}

MinecraftWidget::~MinecraftWidget()
{
    delete ui;
}

void MinecraftWidget::logMessage(const int &type, const QString &message)
{
    QString currentTime = QString("[%1]").arg(QTime::currentTime().toString());

    if (type == 0) { // Info
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 1) { // Error
        ui->textEdit_ev_output->append(QString("%1 <span style=\"color:red\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 2) { // Send
        ui->textEdit_co_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 3) { // Receive
        ui->textEdit_co_output->append(QString("%1 <span style=\"color:#0000FF\">%2</span>").arg(currentTime).arg(message));
    } else if (type == 4) { // Chat
        ui->textEdit_ch_output->append(QString("%1 <span style=\"color:#008000\">%2</span>").arg(currentTime).arg(message));
    }
}

void MinecraftWidget::logEvent(const int &event, const QString &message)
{

}

void MinecraftWidget::slotAuthenticated(bool auth)
{
    if (auth) {
        logMessage(0, "Successfully logged in!");
    } else {
        logMessage(1, "Login failed!");
    }
}

void MinecraftWidget::slotPacket(const QString &packet)
{
    logMessage(3, packet);
}

void MinecraftWidget::slotUnknownCommand()
{
    logMessage(1, tr("Unknown command."));
}

void MinecraftWidget::on_pushButton_co_send_clicked()
{
    QString command = ui->lineEdit_co_input->text();

    con->sendCommand(command);

    ui->lineEdit_co_input->clear();
}
