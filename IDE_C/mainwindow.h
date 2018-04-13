#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDataStream>

namespace Ui {
class MainWindow;
}

class QClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Iniciar_clicked();

private:
    Ui::MainWindow *ui;
    QClient *mClient;
};

#endif // MAINWINDOW_H
