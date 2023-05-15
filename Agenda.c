//
// Created by Diego on 14/05/2023.
//

#include "Agenda.h"
#include <stdio.h>

#define MAX_LINEA 100   //  Cantidad máxima que entra en una línea de registro


int numRegistros() {
    //  Abrimos el fichero en formato de lectura:
    FILE *fb = fopen("agenda.dat", "w");
    if (fb == NULL) {
        perror("Error de apertura.\n");
        return -1;
    }

    //  Guardamos la posición final del fichero y la comparamos con la cantidad de registros de tipo contacto que puede contener:
    fseek(fb, 0, SEEK_END);
    int posicionFinal = ftell(fb);
    fseek(fb, 0, SEEK_SET);

    int numContactos = posicionFinal / sizeof (contacto);

    //  Cerramos el fichero:
    if (fclose(fb) != 0) {
        perror("Error de clausura.\n");
        return -1;
    }

    return numContactos;
}   //  Indica el número de registros que tiene nuestro fichero binario.

int crearListaContactos() {
    FILE *fb = fopen("agenda.dat", "w");
    if (fb == NULL) {
        fb = fopen("agenda.dat", "w");
        if (fb == NULL) {
            perror("Error al crear el fichero.\n");
            return -1;
        } else fclose(fb);
    } else fclose(fb);
    return 0;
}

int mostrarLista() {
    //  Abrir fichero binario en formato de lectura:
    FILE *fb = fopen("agenda.dat", "rb");
    if (fb == NULL) {
        perror("Error de apertura.\n");
        return -1;
    }

    //  Pasarle el valor de cada registro a la variable tipo contacto y postrarla por pantalla:
    contacto agenda;
    //int numContacto = numRegistros();

    //if (numContacto < 1) printf("No hay contactos en la lista.\n");
    //else {
    printf("Lista de contactos:\n");
    fread(&agenda, sizeof(contacto), 1, fb);
    while (!feof(fb)) {
        printf("%i; %s; %s; %s; %i; ", agenda.id, agenda.nombre, agenda.apellidos, agenda.telefono, agenda.edad);
        switch (agenda.tipoContacto) {
            case 1:
                printf("FAVORITO\n");
                break;
            case 2:
                printf("CONOCIDO\n");
                break;
            case 3:
                printf("TRABAJO\n");
                break;
            default:
                printf("Sin tipo\n");
                break;
        }
        fread(&agenda, sizeof(contacto), 1, fb);
    }
    //}

    //  Cerrar fichero binario:
    if (fclose(fb) != 0) {
        perror("Error de clausura.\n");
        return -1;
    }

    return 0;
}

int aniadirContacto() {

    //  Pedimos al usuario los datos del contacto:
    contacto nuevo;
    int tipoContacto;

    printf("Escribe los datos del contacto\n"
           " Id:");
    scanf("%i", &nuevo.id);
    fflush(stdin);

    printf(" Nombre:");
    scanf("%s", &nuevo.nombre);
    fflush(stdin);

    printf(" Apellidos:");
    scanf("%[^\n]", &nuevo.apellidos);
    fflush(stdin);

    printf(" Telefono:");
    scanf("%s", &nuevo.telefono);
    fflush(stdin);

    printf(" Edad:");
    scanf("%i", &nuevo.edad);
    fflush(stdin);

    printf(" Tipo de contacto (1 - FAVORITO, 2 - CONOCIDO, 3 - TRABAJO):");
    scanf("%i", &tipoContacto);
    fflush(stdin);
    switch (tipoContacto) {
        case 1:
            nuevo.tipoContacto = FAVORITO;
            break;
        case 2:
            nuevo.tipoContacto = CONOCIDO;
            break;
        case 3:
            nuevo.tipoContacto = TRABAJO;
            break;
        default:
            nuevo.tipoContacto = CONOCIDO;
            break;
    }

    //  Abrimos fichero binario en formato de escritura que nos permita añadir al final ('append'):
    FILE *fb = fopen("agenda.dat", "ab");
    if (fb == NULL) {
        perror("Error de apertura.\n");
        return -1;
    }

    //  Guardamos los datos del nuevo contacto en el fichero:
    fwrite(&nuevo, sizeof (contacto), 1, fb);

    //  Cerramos el fichero:
    if (fclose(fb) != 0) {
        perror("Error de clausura.\n");
        return -1;
    }

    printf("\nContacto aniadido. \n");
    return 0;
}

int eliminarContacto(){
    //  Iprimimos la lista de contactos y pedimos el 'id' del contacto a eliminar:
    int id = -1, confirm = -1;

    mostrarLista();
    printf("\n");
    printf("Indica el 'id' del contacto que quieres eliminar:\n");
    scanf("%i", &id);

    //  Confirmamos la eliminación:
    printf("Continuar con la eliminacion:\n"
           "\t0 - Continuar.\n"
           "\t1 - Cancelar la operacion.\n");
    scanf("%i", &confirm);

    if (confirm == 0) {
        //  Abrimos el fichero binario en modo lectura y creamos uno temporal en modo escrituro:
        FILE *fb = fopen("agenda.dat", "rb");
        if (fb == NULL) {
            perror("Error de apertura.\n");
            return -1;
        }

        FILE *fbTemporal = fopen("temporal.dat", "ab");
        if (fbTemporal == NULL) {
            fbTemporal = fopen("temporal.dat", "ab");
            if (fbTemporal == NULL) {
                perror("Error de creacion.\n");
                return -1;
            }
        }

        //  Copiamos todos los datos en el nuevo fichero obviando el que queremos eliminar:
        contacto registro;

        fread(&registro, sizeof(contacto), 1, fb);
        while (!feof(fb)) {
            if (id == registro.id) fread(&registro, sizeof(contacto), 1, fb);
            else {
                fwrite(&registro, sizeof (contacto), 1, fbTemporal);
                fread(&registro, sizeof(contacto), 1, fb);
            }
        }

        //  Cerramos los ficheros:
        if (fclose(fbTemporal) != 0) {
            perror("Error de claurura.\n");
            return -1;
        }
        if (fclose(fb) != 0) {
            perror("Error de claurura.\n");
            return -1;
        }

        //  Eliminamos el fichero principal 'agenda.dat' y renombramos el temporal 'temporal.dat':
        remove("agenda.dat");
        rename("temporal.dat", "agenda.dat");

        printf("\nContacto eliminado.\n");
    } else printf("\nOperacion cancelada.\n");

    return 0;
}

int guardarAgenda() {
    //  Pedir el nombre del fichero de texto en el que se va a guardar la agenda:
    char nombre[MAX_CONTACTO];

    printf("\nIndica el nombre de la agenda (agenda.txt):");
    scanf("%s", &nombre);

    //  Abrir fichero binario en formato de lectura y crear fichero de texto en formato de escritura:
    FILE *fb = fopen("agenda.dat", "rb");
    if (fb == NULL) {
        perror("Error de apertura.\n");
        return -1;
    }

    FILE *ft = fopen(nombre, "w");
    if (ft == NULL) {
        perror("Error de creacion.\n");
        return -1;
    }

    //  Guardar los registros del fichero binario en el fichero de texto:
    contacto registro;

    fread(&registro, sizeof (contacto), 1, fb);
    while (!feof(fb)) {
        fprintf(ft, "%i; %s; %s; %s; %i; ", registro.id, registro.nombre, registro.apellidos, registro.telefono, registro.edad);
        switch (registro.tipoContacto) {
            case 1:
                fprintf(ft, "FAVORITO\n");
                break;
            case 2:
                fprintf(ft, "CONOCIDO\n");
                break;
            case 3:
                fprintf(ft, "TRABAJO\n");
                break;
            default:
                fprintf(ft, "Sin tipo.\n");
                break;
        }
        fread(&registro, sizeof (contacto), 1, fb);
    }

    //  Cerrar los ficheros:
    if (fclose(ft) != 0) {
        perror("Error de clausura.\n");
        return -1;
    }
    if (fclose(fb) != 0) {
        perror("Error de clausura.\n");
        return -1;
    }

    printf("Agenda guardada.\n");
    return 0;
}

int mostrarAgenda() {
    //  Pedimos el nombre de la agenda a imprimir:
    char nombre[MAX_CONTACTO];

    printf("Indica el nombre de la agenda (agenda.txt):");
    scanf("%s", &nombre);

    //  Abrimos el fichero de texto en formato de lectura:
    FILE *ft = fopen(nombre, "r");
    if (ft == NULL) {
        perror("Error de apertura.\n");
        return -1;
    }

    // Imprimir por pantalla los contactos:
    char linea[MAX_LINEA];

    printf("\nAgenda:\n---------\n");
    fgets(linea, sizeof (linea), ft);
    while (!feof(ft)) {
        printf("%s", linea);
        fgets(linea, sizeof (linea), ft);
    }
    printf("---------\n");

    //  Cerrar fichero:
    if (fclose(ft) != 0) {
        perror("Error de clausura.\n");
        return -1;
    }

    return 0;
}