#include "widget.h"
#include "ui_widget.h"
#include "localserver.h"
#include <QMessageBox>
#include<QTcpSocket>
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mLocalServer = new LocalServer(this);
    mSocket = new QTcpSocket(this);
    char l[1024];
    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);

        ui->msj->setPlainText(T.readAll());
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_iniciar_clicked()
{
    if(!mLocalServer->listen(QHostAddress::Any,8080)){
        QMessageBox::critical(this,"error",mLocalServer->errorString());
    }else{
        mSocket->connectToHost("192.168.0.14",8080);
        QMessageBox::information(this,"Servidor","Iniciado");
    }

}

void Widget::on_enviat_clicked()
{
    QString text  = ui->msj->toPlainText();
    QByteArray b = text.toUtf8();
    l = b.data();
    mLocalServer->envia(b);
    mSocket->write(l);
}

void Widget::on_quitar_clicked()
{
    close();
}

void Widget::on_enviat_pressed()
{


}

void Widget::on_enviat_released()
{

}
