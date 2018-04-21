//
// Created by elias on 10/04/18.
//

#include <cstdio>
#include <iostream>
#include <vector>
#include "Generador_Datos.h"
#include <fstream>
#include <jsoncpp/json/value.h>


/*
 * Input: integer
 * Esta funcion toma el dato tipo char que se le otorga y luego crea un nodo con esa info.
 * Output: retorna el nuevo nodo integer creado.
 * */
Generador_Datos*Generador_Datos::_intcreateNewNode(int data, char id, int level, char type) {
    _INTNODE *newNode = nullptr;
    newNode=(_INTNODE*)malloc(sizeof(_INTNODE));
    if(newNode == nullptr) {
        printf("Memory allocation error\n");
        return nullptr;
    }
    newNode->data = data;
    newNode->next = nullptr;
    return reinterpret_cast<Generador_Datos *>(newNode);
}

/*
 * Input: int, nodo principal.
 * Esta funcion toma el dato tipo int que se le otorga y luego crea un nodo con esa info al final de la lista.
 * Output: retorna el nuevo nodo integer creado.
 * */
Generador_Datos *Generador_Datos::_intinsertAtEnd(int data, char id, int level, char type, _INTNODE **head) {
    _INTNODE *current = *head;
    if (current == nullptr) {
        *head = reinterpret_cast<_INTNODE *>(_intcreateNewNode(data, id, level, type));
    }else{
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = reinterpret_cast<__intnode *>(_intcreateNewNode(data, id, level, type));
    }
    return reinterpret_cast<Generador_Datos *>(*head);
}

/*
 * Input: int, nodo principal.
 * Busca en la lista simple algun elemento que tenga sus datos en nulo y lo elimina.
 * Output: retorna el nuevo nodo integer creado.
 * */
Generador_Datos *Generador_Datos::_removeExtraSpaces(_NODE **head) {
    _NODE*current = *head;
    while(current->next != nullptr){
        if(current->data == ' '){
            if((current->next)->data == ' '){
                _NODE* temp = current->next->next;
                free(current->next);
                current->next = temp;
            }
        }
        current = current->next;
    }
    return reinterpret_cast<Generador_Datos*>(*head);
}

void Generador_Datos::Obtener_datos(const char* direc) {
    _INTNODE *inthead = NULL;
    FILE *fp;
    char* data;
    char readData;
    bool flag = false;
    Json::Value variables;

    std::ifstream people_file("people.json", std::ifstream::binary);
    people_file >> variables;

    std::ifstream is (direc);
    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        char * buffer = new char [length];

        std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read (buffer,length);
        std::vector<char> buff((std::istreambuf_iterator<char>(is)), (std::istreambuf_iterator<char>()));

        if (is){
            std::cout << is.gcount();
            std::cout << "all characters read successfully." << std::endl;
        }
        else
            std::cout << "error: only " << is.gcount() << " could be read";
        is.close();
        // ...buffer contains the entire file...

        delete[] buffer;
    }

    std::cout << "---------------Primer intento" << std::endl;
    char line;
    int num;
    std::ifstream myfile (direc);
    //std::ofstream outfile (filename);


    myfile.seekg(0, myfile.end);
    long large = myfile.tellg();


    std::cout << "Reading " << large << " characters... ";


    int n = 0;
    std::cout << "Dir de data" << &data << std::endl;
    char var ;
    char *nn = &var;
    std::cout << "Dir de la variable " << var << 3 << &nn << std::endl;
    data = &var;
    int Mbytes = (1024);
    data = (char *) malloc(Mbytes);
    char **temp = &data;

    if (myfile.is_open())
    {
        char * buffer = new char [large];
        char* point = &buffer[large - 2];
        std::cout.write(buffer, large);
        myfile.seekg(0, myfile.beg);
        std::cout << *point << "{{{{{{{{"<< std::endl;
        std::cout << "llego" << std::endl;
        std::cout << num<< '\n';
        std::cout << line << '\n';

        for(int i=0;i<Mbytes;i++){
            myfile >> line;
            data[i] = line;
            n++;
            std::cout << n << "Posicion "<< &temp[i] << " %c " << data[i] << std::endl;
            if (&data[i] == data + Mbytes){
                std::cout << "Llego a 1023" << std::endl;
            }

            if (data[i] == '}' and data[i -1] == ']' and data[i - 2] == '}'){
                std::cout << "Terminó el documento" << std::endl;
                break;
            }


        }
        while ( myfile >> line )
        {
            std::cout << line << '\n';

        }
        myfile.close();
    }

    else std::cout << "Unable to open file";


/*
    fp=fopen(&direc,"r");

    do{
        readData = getc(fp);
        if(readData == ' '&& !flag){
            flag = false;
        }
        else{
            flag=true;
        }

        if(readData=='\t'){
            readData=' ';
        }
        /* check # character and EOF character occurs or not
        when # sign occurs keep reading data from file without adding it to list /
        if(readData == '#'){
            readData = ' ';
            char ch;
            while((ch = getc(fp)) != '\n' && ch != EOF){
            }
            readData = '\n';
        }

        //inserting each char value to linked list
        if(flag){
            std::cout << readData << std::endl;
            head = reinterpret_cast<_NODE *>(_insertAtEnd(readData, &head));
        }

    } while(readData != EOF);
    fclose(fp);

    //remove extra spaces from char type linked list
    for(int i=0;i<5;i++){
        head = reinterpret_cast<_NODE *>(_removeExtraSpaces(&head));
    }

    //separate integer data values & store them into new linked list(inthead)
    //_separateNumbDatas(head,&inthead);
    std::cout << readData << std::endl;
    std::cout << &head << std::endl;
    std::cout << &inthead << std::endl;

    //delete unnecessary character(0),which is head
    //_deleteINTFront(&inthead);

    //once intger list is created,then delete the character type list
    //_deleteCharList(&head);
    free(head);*/


}