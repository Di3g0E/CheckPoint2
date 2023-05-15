#include <stdio.h>
#include "Agenda.h"

int main() {
    int opcion = -1;

    crearListaContactos();

    do {
        printf("\nIndica la operacion que quieres realizar:\n"
               "\t1 - Mostrar lista de contactos\n"
               "\t2 - Aniadir contacto\n"
               "\t3 - Eliminar contacto\n"
               "\t4 - Guardar en agenda\n"
               "\t5 - Mostrar la agenda\n"
               "\t0 - Salir\n");
        scanf("%i", &opcion);
        switch (opcion) {
            case 1:
                mostrarLista();
                break;
            case 2:
                aniadirContacto();
                break;
            case 3:
                eliminarContacto();
                break;
            case 4:
                guardarAgenda();
                break;
            case 5:
                mostrarAgenda();
                break;
            case 0:
                remove("agenda.dat");
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
