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
        mSocket->connectToHost("192.168.0.24",8080);
        QMessageBox::information(this,"Servidor","Iniciado");
    }

}

void Widget::on_enviat_clicked()
{


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
            QRegularExpression Int("\\bint\\b");
            QRegularExpression Char("(\\bchar\\b)");
            QRegularExpression Long("(\\blong\\b)");
            QRegularExpression Double("(\\bdouble\\b)");
            QRegularExpression variable(" \\w+ [=]");
            QRegularExpression intvariable("\\d+");
            QRegularExpression charvariable("\\w+");
            QRegularExpression FullInt("\\bint\\b \\w+ [=] \\d+[;]");
            QRegularExpression FullChar("\\bchar\\b \\w+ [=] \\w+[;]");
            QRegularExpression FullLong("\\blong\\b \\w+ [=] \\d+[;]");
            QRegularExpression FullDouble("\\bdouble\\b \\w+ [=] \\d+[;]");
            QRegularExpression Print("\\bprint\\b [<<] ");
            QRegularExpression PrintData("[*]\\w+[*]");
            QRegularExpression SumaVar("\\w [+] \\w");
            QRegularExpression SumaV1("\\w+ [+]");
            QRegularExpression SumaV2("[+] \\w+");
            QRegularExpression SumaDig("\\d+ [+] \\d+");
            QRegularExpression SumaD1("\\d+ [+]");
            QRegularExpression SumaD2("[+] \\d+");
            QRegularExpression SumaDigVar("\\d+ [+] \\w+");
            QRegularExpression SumaDV1("\\d+ [+]");
            QRegularExpression SumaDV2("[+] \\w+");
            QRegularExpression SumaVarDig("\\w+ [+] \\d+");
            QRegularExpression SumaVD1("\\w+ [+]");
            QRegularExpression SumaVD2("[+] \\d+");
            QRegularExpression RestaVar("\\w+ [-] \\w+");
            QRegularExpression RestaV1("\\w+ [-]");
            QRegularExpression RestaV2("[-] \\w+");
            QRegularExpression RestaDig("\\d+ [-] \\d+");
            QRegularExpression RestaD1("\\d+ [-]");
            QRegularExpression RestaD2("[-] \\d+");
            QRegularExpression RestaDigVar("\\d+ [-] \\w+");
            QRegularExpression RestaDV1("\\d+ [-]");
            QRegularExpression RestaDV2("[-] \\w+");
            QRegularExpression RestaVarDig("\\w+ [-] \\d+");
            QRegularExpression RestaVD1("\\w+ [-]");
            QRegularExpression RestaVD2("[-] \\d+");
            QRegularExpression MultiVar("\\w+ [*] \\w+");
            QRegularExpression MultiV1("\\w+ [*]");
            QRegularExpression MultiV2("[*] \\w+");
            QRegularExpression MultiDig("\\d+ [*] \\d+");
            QRegularExpression MultiD1("\\d+ [*]");
            QRegularExpression MultiD2("[*] \\d+");
            QRegularExpression MultiDigVar("\\d+ [*] \\w+");
            QRegularExpression MultiDV1("\\d+ [*]");
            QRegularExpression MultiDV2("[*] \\w+");
            QRegularExpression MultiVarDig("\\w+ [*] \\d+");
            QRegularExpression MultiVD1("\\w+ [*]");
            QRegularExpression MultiVD2("[*] \\d+");
            QRegularExpression DiviVar("\\w+ [*] \\w+");
            QRegularExpression DiviV1("\\w+ [*]");
            QRegularExpression DiviV2("[*] \\w+");
            QRegularExpression DiviDig("\\d+ [*] \\d+");
            QRegularExpression DiviD1("\\d+ [*]");
            QRegularExpression DiviD2("[*] \\d+");
            QRegularExpression DiviDigVar("\\d+ [*] \\w+");
            QRegularExpression DiviDV1("\\d+ [*]");
            QRegularExpression DiviDV2("[*] \\w+");
            QRegularExpression DiviVarDig("\\w+ [*] \\d+");
            QRegularExpression DiviVD1("\\w+ [*]");
            QRegularExpression DiviVD2("[*] \\d+");
            QRegularExpressionMatch SumaVarmatch = SumaVar.match(line);
            QRegularExpressionMatch SumaV1match = SumaV1.match(line);
            QRegularExpressionMatch SumaV2match = SumaV2.match(line);
            QRegularExpressionMatch SumaDigmatch = SumaDig.match(line);
            QRegularExpressionMatch SumaD1match = SumaD1.match(line);
            QRegularExpressionMatch SumaD2match = SumaD2.match(line);
            QRegularExpressionMatch SumaDigVarmatch = SumaDigVar.match(line);
            QRegularExpressionMatch SumaDV1match = SumaDV1.match(line);
            QRegularExpressionMatch SumaDV2match = SumaDV2.match(line);
            QRegularExpressionMatch SumaVarDigmatch = SumaVarDig.match(line);
            QRegularExpressionMatch SumaVD1match = SumaVD1.match(line);
            QRegularExpressionMatch SumaVD2match = SumaVD2.match(line);
            QRegularExpressionMatch RestaVarmatch = RestaVar.match(line);
            QRegularExpressionMatch RestaV1match = RestaV1.match(line);
            QRegularExpressionMatch RestaV2match = RestaV2.match(line);
            QRegularExpressionMatch RestaDigmatch = RestaDig.match(line);
            QRegularExpressionMatch RestaD1match = RestaD1.match(line);
            QRegularExpressionMatch RestaD2match = RestaD2.match(line);
            QRegularExpressionMatch RestaDigVarmatch = RestaDigVar.match(line);
            QRegularExpressionMatch RestaDV1match = RestaDV1.match(line);
            QRegularExpressionMatch RestaDV2match = RestaDV2.match(line);
            QRegularExpressionMatch RestaVarDigmatch = RestaVarDig.match(line);
            QRegularExpressionMatch RestaVD1match = RestaVD1.match(line);
            QRegularExpressionMatch RestaVD2match = RestaVD2.match(line);
            QRegularExpressionMatch MultiVarmatch = MultiVar.match(line);
            QRegularExpressionMatch MultiV1match = MultiV1.match(line);
            QRegularExpressionMatch MultiV2match = MultiV2.match(line);
            QRegularExpressionMatch MultiDigmatch = MultiDig.match(line);
            QRegularExpressionMatch MultiD1match = MultiD1.match(line);
            QRegularExpressionMatch MultiD2match = MultiD2.match(line);
            QRegularExpressionMatch MultiDigVarmatch = MultiDigVar.match(line);
            QRegularExpressionMatch MultiDV1match = MultiDV1.match(line);
            QRegularExpressionMatch MultiDV2match = MultiDV2.match(line);
            QRegularExpressionMatch MultiVarDigmatch = MultiVarDig.match(line);
            QRegularExpressionMatch MultiVD1match = MultiVD1.match(line);
            QRegularExpressionMatch MultiVD2match = MultiVD2.match(line);
            QRegularExpressionMatch DiviVarmatch = DiviVar.match(line);
            QRegularExpressionMatch DiviV1match = DiviV1.match(line);
            QRegularExpressionMatch DiviV2match = DiviV2.match(line);
            QRegularExpressionMatch DiviDigmatch = DiviDig.match(line);
            QRegularExpressionMatch DiviD1match = DiviD1.match(line);
            QRegularExpressionMatch DiviD2match = DiviD2.match(line);
            QRegularExpressionMatch DiviDigVarmatch = DiviDigVar.match(line);
            QRegularExpressionMatch DiviDV1match = DiviDV1.match(line);
            QRegularExpressionMatch DiviDV2match = DiviDV2.match(line);
            QRegularExpressionMatch DiviVarDigmatch = DiviVarDig.match(line);
            QRegularExpressionMatch DiviVD1match = DiviVD1.match(line);
            QRegularExpressionMatch DiviVD2match = DiviVD2.match(line);
            QRegularExpressionMatch Intmatch = Int.match(line);
            QRegularExpressionMatch Charmatch = Char.match(line);
            QRegularExpressionMatch Longmatch = Long.match(line);
            QRegularExpressionMatch Doublematch = Double.match(line);
            QRegularExpressionMatch variablematch = variable.match(line);
            QRegularExpressionMatch intvariablematch = intvariable.match(line);
            QRegularExpressionMatch charvariablematch = charvariable.match(line);
            QRegularExpressionMatch FullIntmatch = FullInt.match(line);
            QRegularExpressionMatch FullCharmatch = FullChar.match(line);
            QRegularExpressionMatch FullLongmatch = FullLong.match(line);
            QRegularExpressionMatch FullDoublematch = FullDouble.match(line);
            QRegularExpressionMatch printmatch = Print.match(line);
            QRegularExpressionMatch printdatamatch = PrintData.match(line);

            if(Intmatch.hasMatch()){
                if (FullIntmatch.hasMatch()){
                    recordObject.insert("Tipo","int");
                    QString nom = variablematch.captured();
                    nom.remove(QChar('='));
                    recordObject.insert("nombre",nom);
                    recordObject.insert("dato",QJsonValue::fromVariant(intvariablematch.captured()));
                    final.append(recordObject);
                }if(SumaVarmatch.hasMatch() & !intvariablematch.hasMatch()){
                    QString l = "& ";
                    QByteArray s = l.toUtf8();
                    QString SV1 = SumaV1match.captured();
                    SV1.remove(QChar('+'));
                    QJsonObject solicitud1;
                    solicitud1.insert("int",SV1);
                    QJsonDocument sol1(solicitud1);
                    QString V1(sol1.toJson(QJsonDocument::Compact));
                    QByteArray v1 = V1.toUtf8();
                    mSocket->write(s+v1);
                    if(mSocket->isReadable()){
                        connect(mSocket, &QTcpSocket::readyRead,[&](){
                                QTextStream T(mSocket);
                                QString V1 = T.readAll();
                                QMessageBox::information(this,"title",V1);


                        });


                    }

                    QString SV2 = SumaV2match.captured();
                    SV2.remove(QChar('+'));
                    QJsonObject solicitud2;
                    solicitud2.insert("int",SV2);
                    QJsonDocument sol2(solicitud2);
                    QString V2(sol2.toJson(QJsonDocument::Compact));
                    QByteArray v2 = V2.toUtf8();








                }if(SumaDigmatch.hasMatch()){
                    QString SD1 = SumaD1match.captured();
                    SD1.remove(QChar('+'));
                    int sd1 = SD1.toInt();
                    QString SD2 = SumaD2match.captured();
                    SD2.remove(QChar('+'));
                    int sd2 = SD2.toInt();
                    int SD = sd1 + sd2;
                    QString test = QString::number(SD);
                    recordObject.insert("Tipo","int");
                    QString nom = variablematch.captured();
                    nom.remove(QChar('='));
                    recordObject.insert("nombre",nom);
                    recordObject.insert("dato",test);
                    final.append(recordObject);
                    QMessageBox::information(this,"Title",test);

                }if(SumaDigVarmatch.hasMatch()){
                    QString SDV1 = SumaDV1match.captured();
                    SDV1.remove(QChar('+'));
                    int sdv1 = SDV1.toInt();
                    QString SDV2 = SumaDV2match.captured();
                    SDV2.remove(QChar('+'));

                }if(SumaVarDigmatch.hasMatch()){
                    QString SVD1 = SumaVD1match.captured();
                    SVD1.remove(QChar('+'));
                    QString SVD2 = SumaVD2match.captured();
                    SVD2.remove(QChar('+'));
                    int svd1 = SVD2.toInt();

                }if(RestaVarmatch.hasMatch()){
                    QString RV1 = RestaV1match.captured();
                    RV1.remove(QChar('-'));
                    QString RV2 = RestaV2match.captured();
                    RV2.remove(QChar('-'));

                }if(RestaDigmatch.hasMatch()){
                    QString RD1 = RestaD1match.captured();
                    RD1.remove(QChar('-'));
                    int rd1 = RD1.toInt();
                    QString RD2 = RestaD2match.captured();
                    RD2.remove(QChar('-'));
                    int rd2 = RD2.toInt();
                    int RD = rd1 - rd2;
                    QString test = QString::number(RD);
                    recordObject.insert("Tipo","int");
                    QString nom = variablematch.captured();
                    nom.remove(QChar('='));
                    recordObject.insert("nombre",nom);
                    recordObject.insert("dato",test);
                    final.append(recordObject);


                }if(RestaDigVarmatch.hasMatch()){
                    QString RDV1 = RestaDV1match.captured();
                    RDV1.remove(QChar('-'));
                    int rdv1 = RDV1.toInt();
                    QString RDV2 = RestaDV2match.captured();
                    RDV2.remove(QChar('-'));


                }if(RestaVarDigmatch.hasMatch()){
                    QString RVD1 = RestaVD1match.captured();
                    RVD1.remove(QChar('-'));
                    QString RVD2 = RestaVD2match.captured();
                    RVD2.remove(QChar('-'));
                    int rvd1 = RVD2.toInt();

                }if(MultiVarmatch.hasMatch()){
                    QString MV1 = MultiV1match.captured();
                    MV1.remove(QChar('*'));
                    QString MV2 = MultiV2match.captured();
                    MV2.remove(QChar('*'));

                }if(MultiDigmatch.hasMatch()){
                    QString MD1 = MultiD1match.captured();
                    MD1.remove(QChar('*'));
                    int md1 = MD1.toInt();
                    QString MD2 = MultiD2match.captured();
                    MD2.remove(QChar('*'));
                    int md2 = MD2.toInt();
                    int MD = md1 * md2;
                    QString test = QString::number(MD);
                    recordObject.insert("Tipo","int");
                    QString nom = variablematch.captured();
                    nom.remove(QChar('='));
                    recordObject.insert("nombre",nom);
                    recordObject.insert("dato",test);
                    final.append(recordObject);


                }if(MultiDigVarmatch.hasMatch()){
                    QString MDV1 = MultiDV1match.captured();
                    MDV1.remove(QChar('*'));
                    int mdv1 = MDV1.toInt();
                    QString MDV2 = MultiDV2match.captured();
                    MDV2.remove(QChar('*'));

                }if(MultiVarDigmatch.hasMatch()){
                    QString MVD1 = MultiVD1match.captured();
                    MVD1.remove(QChar('*'));
                    QString MVD2 = MultiVD2match.captured();
                    MVD2.remove(QChar('*'));
                    int mvd1 = MVD2.toInt();

                }if(DiviVarmatch.hasMatch()){
                    QString DV1 = DiviV1match.captured();
                    DV1.remove(QChar('/'));
                    QString DV2 = DiviV2match.captured();
                    DV2.remove(QChar('/'));

                }if(DiviDigmatch.hasMatch()){
                    QString DD1 = DiviD1match.captured();
                    DD1.remove(QChar('/'));
                    int dd1 = DD1.toInt();
                    QString DD2 = DiviD2match.captured();
                    DD2.remove(QChar('/'));
                    int dd2 = DD2.toInt();
                    int DD = dd1 / dd2;
                    QString test = QString::number(DD);
                    QMessageBox::information(this,"Title",test);
                    recordObject.insert("Tipo","int");
                    QString nom = variablematch.captured();
                    nom.remove(QChar('='));
                    recordObject.insert("nombre",nom);
                    recordObject.insert("dato",test);
                    final.append(recordObject);
                    QMessageBox::information(this,"Title",test);

                }if(DiviDigVarmatch.hasMatch()){
                    QString DDV1 = DiviDV1match.captured();
                    DDV1.remove(QChar('*'));
                    int ddv1 = DDV1.toInt();
                    QString DDV2 = DiviDV2match.captured();
                    DDV2.remove(QChar('*'));

                }if(DiviVarDigmatch.hasMatch()){
                    QString DVD1 = DiviVD1match.captured();
                    DVD1.remove(QChar('*'));
                    QString DVD2 = DiviVD2match.captured();
                    DVD2.remove(QChar('*'));
                    int dvd1 = DVD2.toInt();

                }

            }
            if(Charmatch.hasMatch()){
                if (FullCharmatch.hasMatch()){
                    recordObject.insert("Tipo","char");
                    QString nom = variablematch.captured();
                    nom.remove(QChar('='));
                    recordObject.insert("nombre",nom);;
                    recordObject.insert("dato",QJsonValue::fromVariant(charvariablematch.captured()));
                    final.append(recordObject);

                }else{
                    QMessageBox::warning(this,"Title","No match");
                    file.close();
                    code.close();
                }

            }
            if(Longmatch.hasMatch()){
                if (FullLongmatch.hasMatch()){
                    recordObject.insert("Tipo","long");
                    QString nom = variablematch.captured();
                    nom.remove(QChar('='));
                    recordObject.insert("nombre",nom);
                    recordObject.insert("dato",QJsonValue::fromVariant(intvariablematch.captured()));
                    final.append(recordObject);

                }else{
                    QMessageBox::warning(this,"Title","No match");
                    file.close();
                    code.close();
                }

            }
            if(Doublematch.hasMatch()){
                if (FullDoublematch.hasMatch()){
                    recordObject.insert("Tipo","double");
                    recordObject.insert("nombre",QJsonValue::fromVariant(variablematch.captured()));
                    recordObject.insert("dato",QJsonValue::fromVariant(intvariablematch.captured()));
                    final.append(recordObject);
                }else{
                    QMessageBox::warning(this,"Title","No match");
                    file.close();
                    code.close();
                }

            }
            if (printmatch.hasMatch()){
                QString print = printdatamatch.captured();
                print.remove(QChar('*'));
                ui->StdOut->setPlainText(print);
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
        QByteArray var = strJson2.toUtf8();

        QString text = ni.readAll();
        ui->msj->setPlainText(text);
        file.close();
        code.close();

    }

}

void Widget::on_Ask_clicked()
{
    QJsonObject solicitud;
    QString l = "* ";
    QByteArray s = l.toUtf8();
    solicitud.insert("int","f");
    QJsonDocument sol(solicitud);
    QString text(sol.toJson(QJsonDocument::Compact));
    QByteArray b = text.toUtf8();
    mSocket->write(s + b);

}
