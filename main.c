/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: 24 / 03 / 2021
 */

#ifdef STATIC_LIST
#include "static_list.h"
#endif

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif

#ifdef TEST_LIST
#include "list/list.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

/*
 * Función: newUser
 * ----------------------------
 *   Crea un usuario con su nickname y su categoría
 *   y lo inserta en la última posición de la lista
 *
 *   username: nickname del usuario a crear
 *   category: categoría (standard o premium)
 *   *L: lista con la que se trabaja
 *
 *   return: void
 */
void newUser(tNickname username, tUserCategory category, tList *L) {
    if (findItem(username, *L) == LNULL) {
        char cat[NAME_LENGTH_LIMIT];
        tItemL i;
        i.numPlay = 0;
        i.userCategory = category;
        strcpy(i.nickname, username);

        category == standard ? strcpy(cat, "standard") : strcpy(cat, "premium");

        if (insertItem(i, LNULL, L))
            printf("* New: nick %s category %s\n", i.nickname, cat);
    } else
        printf("+ Error: New not possible\n");
}

/*
 * Función: play
 * ----------------------------
 *   Busca un usuario en la lista y si lo
 *   encuentra le añade una reproducción
 *
 *   *L: lista con la que se trabaja
 *   username: nickname del usuario a crear
 *   *video: string del nombre del vídeo a reproducir
 *
 *   return: void
 *
 */
void play(tList *L, tNickname username, char *video) {
    tItemL i;
    tPosL p = findItem(username, *L);

    if (p != LNULL) {
        i = getItem(p, *L);
        i.numPlay++;
        updateItem(i, p, L);
        tVideo v;
        strcpy(v.titleVideo, video);
        printf("* Play: nick %s plays video %s numplays %d\n", username, v.titleVideo, getItem(p, *L).numPlay);
    } else
        printf("+ Error: Play not possible\n");
}

/*
 * Función: delete
 * ----------------------------
 *   Busca un usuario en la lista y
 *   si lo encuentra lo elimina
 *
 *   *L: lista con la que se trabaja
 *   username: nickname del usuario a eliminar
 *
 *   return: void
 */
void delete(tList *L, tNickname username) {
    tPosL p = findItem(username, *L);
    char cat[NAME_LENGTH_LIMIT];

    if (p != LNULL) {
        deleteAtPosition(p, L);
        getItem(p, *L).userCategory == standard ? strcpy(cat, "standard") : strcpy(cat, "premium");
        printf("* Delete: nick %s category %s numplays %d\n", username, cat, getItem(p, *L).numPlay);
    } else
        printf("+ Error: Delete not possible\n");
}

/*
 * Función: average
 * ----------------------------
 *   Calcula la media de reproducciones por usuario de una categoría
 *
 *   nPlays: número de reproducciones de una categoría
 *   nUsers: número de usuarios de una categoría
 *
 *   return: media de reproducciones por usuario
 *      0 si el número de usuarios es 0
 */
float average(int nPlays, int nUsers) {
    if (nUsers == 0)
        return 0;

    return (float) nPlays / (float) nUsers;
}

/*
 * Función: showStats
 * ----------------------------
 *   Muestra las estadísiticas de todos
 *   los usuarios de la lista. Si la lista
 *   está vacía, muestra un error
 *
 *   L: lista con la que se trabaja
 *
 *   return: void
 */
void showStats(tList L) {
    if (!isEmptyList(L)) {
        int sUsers = 0, pUsers = 0;
        int sPlays = 0, pPlays = 0;
        char cat[NAME_LENGTH_LIMIT];

        /* bucle para contar usuarios y reproducciones: */
        for (tPosL i = first(L); i != next(last(L), L); i = next(i, L)) {
            if (getItem(i, L).userCategory == standard) {
                strcpy(cat, "standard");
                sUsers++;
                sPlays += getItem(i, L).numPlay;
            } else {
                strcpy(cat, "premium");
                pUsers++;
                pPlays += getItem(i, L).numPlay;
            }
            printf("Nick %s category %s numplays %d \n", getItem(i, L).nickname, cat, getItem(i, L).numPlay);
        }

        printf("Category   Users  Plays  Average\n");
        printf("Standard   %2d    %2d     %1.2f\n", sUsers, sPlays, average(sPlays, sUsers));
        printf("Premium    %2d    %2d     %1.2f\n", pUsers, pPlays, average(pPlays, pUsers));
    } else
        printf("+ Error: Stats not possible\n");
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *L) {
    switch (command) {
        case 'N': {
            printf("********************\n");
            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);
            newUser(param1, strcmp(param2, "standard") == 0 ? standard : premium, L);
            break;
        }
        case 'S': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            showStats(*L);
            break;
        }
        case 'P': {
            printf("********************\n");
            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);
            play(L, param1, param2);
            break;
        }
        case 'D': {
            printf("********************\n");
            printf("%s %c: nick %s\n", commandNumber, command, param1);
            delete(L, param1);
            break;
        }
        default: {
            break;
        }
    }
}

void readTasks(char *filename, tList *L) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2;

    df = fopen(filename, "rb");
    if (df != NULL) {
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, L);
        }
        fclose(df);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    tList L;
    createEmptyList(&L);

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &L);

    return 0;
}