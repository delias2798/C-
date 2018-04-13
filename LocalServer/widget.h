#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class LocalServer;
class QTcpSocket;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_iniciar_clicked();

    void on_enviat_clicked();

    void on_quitar_clicked();

    void on_enviat_pressed();

    void on_enviat_released();

private:
    Ui::Widget *ui;
    LocalServer *mLocalServer;
    QTcpSocket *mSocket;
};

#endif // WIDGET_H
