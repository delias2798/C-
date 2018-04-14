#include "localserver.h"
#include<QTcpSocket>
#include<QTextStream>
#include<QMessageBox>


LocalServer::LocalServer(QObject *parent)
    : QTcpServer(parent)
{
      mSocket = nullptr;

      connect(this, &LocalServer::newConnection,[&](){
          mSocket = nextPendingConnection();
      });
}


void LocalServer::envia(const QByteArray &msj){
    if(mSocket){
        QTextStream T(mSocket);
        T << msj;
        mSocket ->flush();

    }

}
