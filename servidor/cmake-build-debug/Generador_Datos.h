//
// Created by elias on 10/04/18.
//

#ifndef PUEB_GENERADOR_DATOS_H
#define PUEB_GENERADOR_DATOS_H

typedef struct __node {
    char data;
    struct __node *next;
}_NODE;


//structure to store integer data
typedef struct __intnode {
    int data;
    struct __intnode *next;
    char id;
    int level;
    char type;
}_INTNODE;

class Generador_Datos {
public:
    void Obtener_datos(const char*);

    Generador_Datos *_intcreateNewNode(int data, char id, int level, char type);

    Generador_Datos *_intinsertAtEnd(int data, char id, int level, char type, _INTNODE **head);

    Generador_Datos *_removeExtraSpaces(_NODE **head);
};


#endif //PUEB_GENERADOR_DATOS_H

