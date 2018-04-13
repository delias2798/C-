#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QStringList>
#include<QCoreApplication>
#include<QRegularExpression>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QFile file("/home/david/IDE_C/file.txt");
    QFile code("/home/david/IDE_C/code.txt");

    if (!file.open(QFile::WriteOnly | QFile::Text ) &!code.open(QFile::WriteOnly | QFile::Text ) ){
        QMessageBox::warning(this,"Title","File not open");

    }
    QTextStream out(&file);
    QTextStream out2(&code);
    QString text  = ui->plainTextEdit->toPlainText();
    out << text;
    out2 << text;
    file.flush();
    file.close();
    code.flush();
    code.close();

}

void MainWindow::on_pushButton_2_clicked()

{


    QFile file("/home/david/IDE_C/file.txt");
    QFile code("/home/david/IDE_C/code.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text) & !code.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Title","File not open");

    }else{
        QTextStream in(&file);
        QTextStream ni(&code);
        while (!in.atEnd()){
            QString line = in.readLine();
            QRegularExpression Int("(\\bint\\b)");
            QRegularExpression Char("(\\bchar\\b)");
            QRegularExpression Long("(\\blong\\b)");
            QRegularExpression Double("(\\bdouble\\b)");
            QRegularExpression variable("\\w+");
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
                    QMessageBox::information(this,"title","ok");

                }else{
                    QMessageBox::warning(this,"Title","No match");
                    file.close();
                    code.close();
                }

            }
            if(Charmatch.hasMatch()){
                if (variablematch.hasMatch() & equalmatch.hasMatch() &charvariablematch.hasMatch() &endlinematch.hasMatch()){
                    QMessageBox::information(this,"title","ok");

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
        QString text = ni.readAll();
        ui->textBrowser->setPlainText(text);
        file.close();
        code.close();

    }





}



