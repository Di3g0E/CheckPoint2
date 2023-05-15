//
// Created by Diego on 14/05/2023.
//

#ifndef FICHEROBINARIO_AGENDA1_H
#define FICHEROBINARIO_AGENDA1_H

#define MAX_CONTACTO 50 //  Cantidad máxima que entra en los strings de contacto

enum tipoCont {
    FAVORITO = 1,
    CONOCIDO = 2,
    TRABAJO = 3
};  //  Tipo de contacto que podemos tener en la agenda.

typedef struct {
    int id;
    char nombre[MAX_CONTACTO];
    char apellidos[MAX_CONTACTO];
    char telefono[MAX_CONTACTO];
    int edad;
    enum tipoCont tipoContacto;
}contacto;  //  Nuevo tipo para variables que se guardan en la agenda


int crearListaContactos();

int mostrarLista();

int aniadirContacto();

int eliminarContacto();

int guardarAgenda();

int mostrarAgenda();

#endif //FICHEROBINARIO_AGENDA1_H
