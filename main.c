#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"

int main() {
    //  Creamos las variables que vamos a utilizar. IMPORTANTE crear aquí las variables que usan la memoria dinámica para poder usarlas en las funciones
    int opcion = -1;
    int *cont = malloc(sizeof (int));
    int *max = malloc(sizeof (int));
    contacto *agenda = malloc(MAX * sizeof(contacto));

    *max = MAX;
    *cont = 0;

    crearAgendaBinaria();   //  Crea el fichero binario 'agenda.dat'

    //  Llenar la agenda con datos de ejemplo
    for (int i = 0; i < max[0]; i++) {
        sprintf(agenda[i].nombre, "Nombre%d", i + 1);
        sprintf(agenda[i].apellidos, "Apellidos%d", i + 1);
        sprintf(agenda[i].telefono, "Telefono%d", i + 1);
        agenda[i].edad = 20 + i;
        agenda[i].tipoContacto = FAVORITO;
    }

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
                borrarPersona(agenda, cont, max);
                break;
            case 4:
                guardarAgenda(max, agenda);
                break;
            case 5:
                leerAgenda();
                break;
            case 0:
                //  Liberamos toda la memoria dinámica que hemos utilizado y salimos
                free(max);
                free(cont);
                free(agenda);
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    } while (opcion != 0);


    return 0;
}