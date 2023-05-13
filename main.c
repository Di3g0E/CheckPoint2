#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"

int main() {
    int opcion = -1;

    crearAgendaBinaria();   //  Crea el fichero binario 'agenda.dat'

    // MENU INICIO:
    do {
        printf("\nSelecciona una de las siguientes opciones:\n"
               "\t1 - Listado de personas\n"
               "\t2 - Nueva persona\n"
               "\t3 - Borrar persona\n"
               "\t4 - Guardar agenda en fichero de texto\n"
               "\t5 - Leer agenda de fichero de texto\n"
               "\t0 - Salir\n");
        scanf("%i", &opcion);

        switch (opcion) {
            case 1:
                listaPersonas();
                break;
            case 2:
                nuevaPersona();
                break;
            case 3:
                listaPersonas();
                printf("\n");
                borrarPersona();
                break;
            case 4:
                guardarAgenda();
                break;
            case 5:
                leerAgenda();
                break;
            case 0:
                remove("agenda.dat");
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    } while (opcion != 0);


    return 0;
}