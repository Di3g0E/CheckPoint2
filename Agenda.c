//
// Created by Diego on 11/05/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "Agenda.h"

int crearAgendaBinaria() {
    FILE *ficheroBinario = fopen("agenda.dat", "rb");
    if (ficheroBinario == NULL) {
        ficheroBinario = fopen("agenda.dat", "wb");
        if (ficheroBinario == NULL) {
            perror("Error al crear el fichero binario.\n");
            return -1;
        } else fclose(ficheroBinario);
    } else fclose(ficheroBinario);
}

int listaPersonas() {
    //  Abrimos el fichero en modo lectura:
    FILE *fb = fopen("agenda.dat", "rb");
    if (fb == NULL) {
        perror("Error de apertura.\n");
        return -1;
    }

    //  Realizamos la operación de lectura:
    contacto contacto1;

    fread(&contacto1, sizeof (contacto), 1, fb);
    while (!feof(fb)) {
        printf("%i; %s; %s; %s; %i; %s\n", contacto1.id, contacto1.nombre, contacto1.apellidos, contacto1.telefono, contacto1.edad, contacto1.tipoContacto);
        fread(&contacto1, sizeof (contacto), 1, fb);
    }

    //  Cerramos el fichero:
    fclose(fb);

    return 0;
}

int nuevaPersona() {
    contacto nuevo;

    printf("Ecribe los datos del nuevo contacto:\n"
           " ID: ");
    scanf("%i", &nuevo.id);

    printf("Nombre: ");
    scanf("%s", &nuevo.nombre);

    fflush(stdin);  // Este comando limpia el buffer y nos permite asignar los valores por teclados con menos errores
    printf("Apellidos: ");
    scanf("%[^\n]", &nuevo.apellidos);  //  "%[^\n]" le indica al 'scanf()' que guarde todos los datos que vayan entrando hasta el siguiente salto de línea
    fflush(stdin);

    printf("Telefono: ");
    scanf("%s", &nuevo.telefono);

    printf("Edad: ");
    scanf("%d", &nuevo.edad);

    printf("Tipo de contacto (FAVORITO, CONOCIDO, TRABAJO): ");
    scanf("%d", &nuevo.tipoContacto);
    fflush(stdin);

    //  Una vez guardados los datos en la variable nuevo los guardamos en nuestro fichero binario.
    //  Abrimos el fichero:
    FILE *fb = fopen("agenda.dat", "ab");
    if (fb == NULL) {
        perror("Error de apertura del fichero.\n");
        return -1;
    }

    //  Guardamos los datos al final del fichero:
    fwrite(&nuevo, sizeof (contacto), 1, fb);

    //  Cerramos el fichero:
    fclose(fb);

    return 0;
}

int borrarPersona() {
    int id = -1, confirmar = -1;

    //  Pedimos el 'id' del contacto que queremos eliminar;
    printf("Indica el numero de contacto que quieres eliminar: ");
    scanf("%i", &id);

    //  Confirmación al usuario:
    printf("¿Quiere confirmar la eliminacion del contacto?\n"
           "\t0 - SI\n"
           "\t1 - NO\n");
    scanf("%i", &confirmar);
    if (confirmar == 0) {

        //  Abrimos fichero de forma que podamos leer y escribir:
        FILE *fb = fopen("agenda.dat", "rb+");
        if (fb == NULL) {
            perror("Error al abrir.\n");
            return -1;
        }

        //  Creamos un fichero temporal en el que guardaremos los datos:
        FILE *fb_copy = fopen("ficheroTemporal", "ab");
        if (fb_copy == NULL) {
            perror("Error al crear.\n");
            return -1;
        }

        contacto registro;
        fread(&registro, sizeof (contacto), 1, fb);
        while (!feof(fb)) {
            if (id != registro.id) {
                fwrite(&registro, sizeof (contacto), 1, fb_copy);
                fread(&registro, sizeof (contacto), 1, fb);
            } else fread(&registro, sizeof (contacto), 1, fb);

        }

        //  Cerramos los ficheros, el principal y el temporal:
        fclose(fb);
        fclose(fb_copy);

        //  Eliminamos el fichero principal y renombramos el temporal:
        remove("agenda.dat");
        rename("ficheroTemporal", "agenda.dat");
    }

    return 0;
}

int guardarAgenda() {
    char nombre;

    //  Abrimos el fichero en modo lectura:
    FILE *fb = fopen("agenda.dat", "rb");
    if (fb == NULL) {
        perror("Error de apertura.\n");
        return -1;
    }

    //  Pedimos el nombre del fichero al que queremos acceder:
    printf("Escribe el nombre de la agenda ('agenda.txt'): ");
    scanf("%s", &nombre);

    //  Abrimos el fichero de texto en modo escritura;
    FILE *ft = fopen(&nombre, "w");
    if (ft == NULL) {
        perror("Error de apertura.\n");
        return -1;
    }


    //  Realizamos la operación de lectura:
    contacto contacto1;

    fread(&contacto1, sizeof (contacto), 1, fb);
    while (!feof(fb)) {
        fprintf(ft, "%d; %s; %s; %s; %d; %d\n", contacto1.id, contacto1.nombre, contacto1.apellidos, contacto1.telefono, contacto1.edad, contacto1.tipoContacto);
        fread(&contacto1, sizeof (contacto), 1, fb);
    }

    //  Cerramos el fichero:
    if (fclose(ft) != 0) {
        perror("Error de clausura.\n");
        return -1;
    }
    if (fclose(fb) != 0) {
        perror("Error de clausura.\n");
        return -1;
    }
    return 0;
}

int leerAgenda() {
    int linea[MAX_LINEA];
    char nombre;

    //  Pedimos el nombre del fichero al que queremos acceder:
    printf("Escribe el nombre de la agenda ('agenda.txt'): ");
    scanf("%s", &nombre);

    //  Abrimos el fichero:
    FILE *fichero = fopen(&nombre, "r");
    if (fichero == NULL) {
        printf("Error de apertura\n");
        return -1;
    }

    //  Realizamos la operación de lectura y escritura por pantalla:
    printf("\nContenido:\n-------\n");
    while (!feof(fichero)) {
        fgets(linea, sizeof(linea-1), fichero);
        printf("%s", linea);
    }
    printf("-------\n");

    //  Cerramos el fichero:
    if (fclose(fichero) != 0) {
        perror("Error en clausura de fichero\n");
        return -1;
    }

    return 0;
}
