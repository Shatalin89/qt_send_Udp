#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    socket = new QUdpSocket(this);

    int port = ui->lineEdit_3->text().toUInt();
    socket->bind(QHostAddress(ui->lineEdit_4->text()), port);
    QPushButton *button = new QPushButton("Send", 0);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(button, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_clicked()));

}


void MainWindow::readyRead()
{

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;


    socket->readDatagram(buffer.data(),buffer.size(), &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
    this->ui->lineEdit_2->setText(buffer);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray Data;
    QString sendtext = this->ui->lineEdit->text();
    Data.append(sendtext);
    int port = this->ui->lineEdit_3->text().toInt();
    socket->writeDatagram(Data, QHostAddress(this->ui->lineEdit_4->text()), port);
}
