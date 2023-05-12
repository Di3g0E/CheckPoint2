//
// Created by Diego on 11/05/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "Agenda.h"

int numeroFilasFicheroB() {
    //  Abrimos el fichero:
    FILE *fb = fopen("agenda.dat", "rb");
    if (fb == NULL) {
        perror("Error al abrir el fichero.\n");
        return -1;
    }

    //  Contamos el número de filas:
    fseek(fb, 0, SEEK_END);
    int longFichero = ftell(fb);
    fseek(fb, 0, SEEK_SET);

    int tamanoDatos = sizeof (contacto);
    int numFilas = (longFichero / tamanoDatos) + 1;

    //  Cerramos el fichero:
    fclose(fb);

    return numFilas;
}

int listaPersonas() {
    int cant = numeroFilasFicheroB();
    contacto agenda[cant];

    //  Abrir fichero:
    FILE *fb = fopen("agenda.dat", "wb");
    if (fb == NULL) {
        perror("Error al abrir el fichero.\n");
        return -1;
    }

    //  Imprimir la línea del contacto:
    while (!feof(fb)) {
        fseek(fb, sizeof(contacto), SEEK_SET);
        fread(&agenda, sizeof(contacto), cant, fb);

        //  Se escribe este comando para no repetir la impresión de la última fila:
        if (!feof(fb)) {
            printf("Agenda:\n");
            for (int i = 0; i < cant; ++i) {
                printf("%d; %s; %s; %s; %d; %d\n", i + 1, agenda[i].nombre, agenda[i].apellidos, agenda[i].telefono,
                       agenda[i].edad, agenda[i].tipoContacto);
            };

        }

        //  Cerrar el fichero:
        fclose(fb);

        return 0;
    }
}

int nuevaPersona() {
    contacto nuevo;

    printf("Ecribe los datos del nuevo contacto:\n"
           " Nombre: ");
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
    int numNuevoContacto = numeroFilasFicheroB()+1;
    fprintf(fb, "%d; %s; %s; %s; %d; %tipoCont\n", numNuevoContacto+1, nuevo.nombre, nuevo.apellidos, nuevo.telefono, nuevo.edad, nuevo.tipoContacto);

    //  Cerramos el fichero:
    fclose(fb);

    return 0;
}

int borrarPersona(contacto *agenda, int *cont, int *max) {
    int id = -1, seguro = -1;

    //  MOSTRAR AGENDA ACTUAL:
    listaPersonas(agenda, max);

    // Pide el id que se quiere eliminar de la agenda:
    printf("\nIndica el ID del usuario que deseas borrar:\t");
    scanf("%d", &id);

    // Verifica si el número es válido y si existe la persona:
    if (id < 1 || id > max[0]) {
        printf("El numero de persona es invalido.\n");
    }

    // Pide la confirmación de operación al usuario:
    printf("Usted desea borrar:\t %d;%s;%s;%s;%d;%d\n", id, agenda[id - 1].nombre, agenda[id - 1].apellidos, agenda[id - 1].telefono, agenda[id - 1].edad, agenda[id - 1].tipoContacto);
    printf("¿Quiere confirmar la eliminacion del contacto?\n"
           "\t0 - SI\n"
           "\t1 - NO\n");
    scanf("%i", &seguro);

    if (seguro == 0) {
        for (int i = id-1 ; i < max[0]; ++i) {
            agenda[i] = agenda[i+1];
        }   //  Copia el valor de la siguiente fila en la que se quiere eliminar
        printf("Persona borrada.\n");
        max[0]--;   //  Resta una unidad al tamaño de la agenda
        while (sizeof(agenda) != 1) {
            realloc(agenda, max[0]*sizeof (contacto));
            break;
        }  //  Este código es un seguro para que la agenda no se quede con contactos negativos
    } else printf("Operacion cancelada.\n");

    return max[0];
}

int guardarAgenda(int *max, contacto *agenda) {
    char nombreAgenda;

    //  Pedimos el nombre del fichero al que queremos acceder:
    printf("Escribe el nombre de la agenda ('agenda.txt'): ");
    scanf("%s", &nombreAgenda);

    //  Abrimos el fichero:
    FILE *fichero = fopen(&nombreAgenda, "w");
    if (fichero == NULL) {
        perror("Error de apertura\n");
        return -1;
    }

    //  Realizamos la operación de escritura en el fichero:
    for (int i = 0; i < max[0]; ++i) {
        fprintf(fichero, "%d; %s; %s; %s; %d; %d\n", i + 1, agenda[i].nombre, agenda[i].apellidos, agenda[i].telefono,
                agenda[i].edad, agenda[i].tipoContacto);
    }

    printf("Fichero grabado correctamente\n");

    //  Cerramos el fichero:
    if (fclose(fichero) != 0) {
        perror("Error en clausura\n");
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

    printf("Fichero abierto OK");

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
}

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

/*int guardarAgendaBinario(int *max, contacto *agenda){

    //  Abrimos el fichero:
    FILE *fichero = fopen(FICHERO, "wb");
    if (fichero == NULL) {
        perror("Error de apertura\n");
        return -1;
    }

    //  Realizamos la operación de escritura en el fichero:
    for (int i = 0; i < max[0]; ++i) {
        fprintf(fichero, "%d; %s; %s; %s; %d; %d\n", i + 1, agenda[i].nombre, agenda[i].apellidos, agenda[i].telefono,
                agenda[i].edad, agenda[i].tipoContacto);
    }

    printf("Fichero grabado correctamente\n");

    //  Cerramos el fichero:
    if (fclose(fichero) != 0) {
        perror("Error en clausura\n");
        return -1;
    }
    return 0;
}

int leerAgendaBinario();*/