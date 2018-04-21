//
// Created by elias on 09/04/18.
//
//192.168.0.14
//g++ /home/elias/CLionProjects/servidor/client.cpp -o client -pthread

#include "client.h"

#include "client.h"
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

int main(int argc, char* argv[])
{
    int listenFd, ClientSocket, portNo;
    bool loop = false;
    struct sockaddr_in svrAdd;
    struct hostent *server;

    if(argc < 3)
    {
        std::cerr<<"Syntax : ./client <host name> <port>"<<std::endl;
        return 0;
    }

    portNo = atoi(argv[2]);

    if((portNo > 65535) || (portNo < 2000))
    {
        std::cerr<<"Please enter port number between 2000 - 65535"<<std::endl;
        return 0;
    }

    //create client skt
    //ClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    listenFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(listenFd < 0)
    {
        std::cerr << "Cannot open socket" << std::endl;
        return 0;
    }

    server = gethostbyname(argv[1]);

    if(server == NULL)
    {
        std::cerr << "Host does not exist" << std::endl;
        return 0;
    }

    bzero((char *) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;

    bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);

    svrAdd.sin_port = htons(portNo);

    int checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));

    if (checker < 0)
    {
        std::cerr << "Cannot connect!" << std::endl;
        return 0;
    }

    //send stuff to server
    do {
        char s[1024];
        //char c[300];
        //cin.clear();
        //cin.ignore(256, '\n');
        std::cout << "Enter stuff: ";
        //bzero(s, 301);


        //write(listenFd, s, strlen(s));

        //bzero(c, 301);
        //read(ClientSocket, c, 300);
        //std::string tester (c);

        do{
            std::cin >> s;
            send(listenFd, s, 1024, 0);

        }while (*s != '*');

        memset(&s[0], 0, sizeof(s));

        do{
            recv(listenFd, s, 1024, 0);
            if(*s == 'i'){

                std::cout << s << "  *S  " << *s << std::endl;

            } else{
                std::cout << s << "  " << *s << std::endl;

            }
        }while (*s != '#');

    }while (!loop);
}