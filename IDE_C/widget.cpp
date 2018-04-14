#include "widget.h"
#include "ui_widget.h"
#include "localserver.h"
#include <QMessageBox>
#include<QTcpSocket>
#include <QFile>
#include<QRegularExpression>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mLocalServer = new LocalServer(this);
    mSocket = new QTcpSocket(this);

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
    mLocalServer->envia(b);
    mSocket->write(b);
}

void Widget::on_quitar_clicked()
{
    close();
}

void Widget::on_enviat_pressed()
{
    QFile file("/home/david/IDE_C/file.txt");
    QFile code("/home/david/IDE_C/code.txt");

    if (!file.open(QFile::WriteOnly | QFile::Text ) &!code.open(QFile::WriteOnly | QFile::Text ) ){
        QMessageBox::warning(this,"Title","File not open");

    }
    QTextStream out(&file);
    QTextStream out2(&code);
    QString text  = ui->msj->toPlainText();
    out << text;
    out2 << text;
    file.flush();
    file.close();
    code.flush();
    code.close();






}

void Widget::on_enviat_released()
{
    QFile file("/home/david/IDE_C/file.txt");
    QFile code("/home/david/IDE_C/code.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text) & !code.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Title","File not open");

    }else{
        QTextStream in(&file);
        QTextStream ni(&code);
        QJsonObject recordObject;
        QJsonArray final;
        while (!in.atEnd()){
            QString line = in.readLine();
            QRegularExpression Int("(\\bint\\b)");
            QRegularExpression Char("(\\bchar\\b)");
            QRegularExpression Long("(\\blong\\b)");
            QRegularExpression Double("(\\bdouble\\b)");
            QRegularExpression variable(" \\w+");
            QRegularExpression equal("[=]");
            QRegularExpression start("[{]");
            QRegularExpression end("[}]");
            QRegularExpression endline("[;]");
            QRegularExpression intvariable("\\d+");
            QRegularExpression charvariable("\\w+");
            QRegularExpressionMatch Intmatch = Int.match(line);
            QRegularExpressionMatch Charmatch = Char.match(line);
            QRegularExpressionMatch Longmatch = Long.match(line);
            QRegularExpressionMatch Doublematch = Double.match(line);
            QRegularExpressionMatch variablematch = variable.match(line);
            QRegularExpressionMatch equalmatch = equal.match(line);
            QRegularExpressionMatch startmatch = start.match(line);
            QRegularExpressionMatch endmatch = end.match(line);
            QRegularExpressionMatch endlinematch = endline.match(line);
            QRegularExpressionMatch intvariablematch = intvariable.match(line);
            QRegularExpressionMatch charvariablematch = charvariable.match(line);

            if(Intmatch.hasMatch()){
                if (variablematch.hasMatch() & equalmatch.hasMatch() &intvariablematch.hasMatch() &endlinematch.hasMatch()){
                    recordObject.insert("Tipo","int");
                    recordObject.insert("nombre",QJsonValue::fromVariant(variablematch.captured()));
                    recordObject.insert("dato",QJsonValue::fromVariant(intvariablematch.captured()));
                    final.append(recordObject);
                    QJsonDocument doc(recordObject);
                    QString strJson(doc.toJson(QJsonDocument::Compact));
                    QMessageBox::information(this,"title",strJson);

                }else{
                    QMessageBox::warning(this,"Title","No match");
                    file.close();
                    code.close();
                }

            }
            if(Charmatch.hasMatch()){
                if (variablematch.hasMatch() & equalmatch.hasMatch() &charvariablematch.hasMatch() &endlinematch.hasMatch()){
                    recordObject.insert("Tipo","char");
                    recordObject.insert("nombre",QJsonValue::fromVariant(variablematch.captured()));
                    recordObject.insert("dato",QJsonValue::fromVariant(charvariablematch.captured()));
                    QJsonDocument doc(recordObject);
                    QString strJson(doc.toJson(QJsonDocument::Compact));
                    QMessageBox::information(this,"title",strJson);

                }else{
                    QMessageBox::warning(this,"Title","No match");
                    file.close();
                    code.close();
                }

            }
            if(Longmatch.hasMatch()){
                if (variablematch.hasMatch() & equalmatch.hasMatch() &intvariablematch.hasMatch() &endlinematch.hasMatch()){
                    QMessageBox::information(this,"title","ok");

                }else{
                    QMessageBox::warning(this,"Title","No match");
                    file.close();
                    code.close();
                }

            }
            if(Doublematch.hasMatch()){
                if (variablematch.hasMatch() & equalmatch.hasMatch() &intvariablematch.hasMatch() &endlinematch.hasMatch()){
                    QMessageBox::information(this,"title","ok");

                }else{
                    QMessageBox::warning(this,"Title","No match");
                    file.close();
                    code.close();
                }

            }


        }
        QJsonObject recobj;
        QJsonDocument doc;
        doc.setArray(final);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        recobj.insert("Variable",strJson);
        QJsonDocument doc2(recobj);
        QString strJson2(doc2.toJson(QJsonDocument::Compact));
        QMessageBox::information(this,"title",strJson2);
        QString text = ni.readAll();
        ui->msj->setPlainText(text);
        file.close();
        code.close();

    }

}
