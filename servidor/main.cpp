
#include <unistd.h>
#include <cstdio>
#include <netdb.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sstream>
#include <string.h>
#include "client.h"
#include "cmake-build-debug/Generador_Datos.h"


using namespace std;

void* task(void *);
void print();

static int connFd, listenFd;
const bool active = true;

int portNo,portA, portP, ClientSocket, type;
char* ip;
bool inUse;
struct sockaddr_in serverAddress, clientAddress;


int main() {

//    Generador_Datos generador_datos;
//    generador_datos.Obtener_datos("/home/elias/Escritorio/prueba.txt");

//    return 0;

    cout << "Escriba el tipo de servidor" <<endl;
    cout << "1 - Activo" <<endl;
    cout << "2 - Pasivo" <<endl;
    cin >> type;

    if (type == 1){
        cout << "Escriba el puerto para el servidor"<<endl;
        cin >>portNo;
        cout << "Escriba el puerto para la comunicacion entre servidores" << endl;
        cin >> portA;
    }else if (type == 2){
        cout << "Escriba el puerto para el servidor";
        cin >>portNo;
        cout << "Escriba la ip del servidor activo" << endl;
        cin >> ip;
        cout << "Escriba el puerto del servidor activo" << endl;
        cin >> portP;
    }else{
        cout << "Tipo de servidor invalido" << endl;
        return 0;
    }

    inUse = false;

    socklen_t len; //store size of the address



    //Set the thread Number
    pthread_t threadA[100];


    //create socket
    ClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //listenFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


    if(ClientSocket < 0)
    {
        cout << "Cannot open socket" << endl;
        return 0;
    }


    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNo);

    //bind socket
    if(bind(ClientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cout << "Cannot bind" << endl;
        return 0;
    }

    listen(ClientSocket, 100);

    int noThread = 0;

    while (active)
    {
        socklen_t len = sizeof(clientAddress);
        //cout << "Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(ClientSocket, (struct sockaddr*)&clientAddress, &len);

        if (connFd < 0)
        {
            cout << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
            cout << "Connection successful" << endl;
        }

        //pthread_t hilo;
        pthread_create(&threadA[noThread], NULL, task, NULL);
        //pthread_create(&hilo,NULL,task1,NULL);
        sleep(1);
        noThread++;
    }

    return 0;
}

void *task (void *dummyPt)
{
    std::cout << "Thread No: " << pthread_self() << std::endl;
    char test[1024];
    int datos[1024];
    bzero(test, 1025);
    /*char* buffer = new char[100];
    read(connFd, buffer, 100);

    std::string tester(buffer);

    if (tester.size() != 0){

    }*/
    bool loop = false;
    std::cout << dummyPt << std::endl;
    //char s[1024];
    while(ClientSocket > 0)
    {
        //bzero(test, 301);
    do{
        //recv(connFd,test, 1024, 0);
        recv(connFd,datos, 1024, 0);
        std::cout << datos << std::endl;
    }while (*datos != '*');

        //read(connFd, test, 300);

        //std::string tester (test);
        //std::cout << tester << std::endl;

    do {
        //if (*test == 'h') {
            std::cout << "Enter respond: ";
            //bzero(s, 301);
            //std::cin.getline(s, 300);
            std::cin >> test;
            send(connFd, test, 1024, 0);
            //write(listenFd, s, strlen(s));
        //} else {
            std::cout << test << std::endl;
        //}


        if (*test == 'e')
            break;
    }while (*test != '#');

    }
    std::cout << "\nClosing thread and conn" << std::endl;
    close(connFd);
}

//g++ /home/elias/CLionProjects/servidor/main.cpp -o servidor -pthread

