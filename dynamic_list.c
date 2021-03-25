/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: 24 / 03 / 2021
 */

#include "dynamic_list.h"

/*
 * Función: createEmptyList
 * ----------------------------
 *   Crea una lista vacía
 *
 *   *L: lista con la que se trabaja
 *
 *   return: void
 */
void createEmptyList(tList *L) {
    *L = LNULL;
}

/*
 * Función: isEmptyList
 * ----------------------------
 *   Comprueba si la lista está vacía
 *   o si contiene algún elemento
 *
 *   L: lista con la que se trabaja
 *
 *   return: true si la lista está vacía
 *      false si contiene algún elemento
 */
bool isEmptyList(tList L) {
    return L == LNULL;
}

/*
 * Función: first
 * ----------------------------
 *   Busca la posición del primer nodo de la lista
 *
 *   L: lista con la que se trabaja
 *
 *   return: la primera posición de la lista
 */
tPosL first(tList L) {
    return L;
}

/*
 * Función: last
 * ----------------------------
 *   Busca la posición del último nodo de la lista
 *
 *   L: lista con la que se trabaja
 *
 *   return: la última posición de la lista
 */
tPosL last(tList L) {
    tPosL aux;
    for (aux = L; aux->next != LNULL; aux = aux->next);
    return aux;
}

/*
 * Función: next
 * ----------------------------
 *   Busca la siguiente posición a la recibida
 *
 *   p: posición de la lista para buscar su siguiente
 *
 *   return: la siguiente posición a la recibida
 */
tPosL next(tPosL p, tList L) {
    return p->next;
}

/*
 * Función: previous
 * ----------------------------
 *   Busca la anterior posición a la recibida
 *
 *   p: posición de la lista para buscar su anterior
 *   L: lista con la que se trabaja
 *
 *   return: la anterior posición a la recibida
 *      si la posición recibida es la primera, return: NULL
 */
tPosL previous(tPosL p, tList L) {
    if (p == L)
        return LNULL;

    tPosL j;
    for (j = L; j->next != p; j = j->next);
    return j;
}

/*
 * Función: insertItem
 * ----------------------------
 *   Inserta un item en la posición recibida
 *   si esa posición es NULL, el item se inserta en la última posición
 *
 *   d: item que se quiere insertar
 *   p: posición de la lista donde se quiere insertar el item
 *   *L: lista con la que se trabaja
 *
 *   return: true si el elemento fue insertado
 *      false si la inserción no fue posible
 */
bool insertItem(tItemL d, tPosL p, tList *L) {
    tPosL aux;
    aux = malloc(sizeof(struct tNode));

    if (aux == LNULL || findItem(d.nickname, *L) != LNULL)
        return false;

    aux->dataUser = d;
    aux->next = LNULL;

    if (isEmptyList(*L)) {
        *L = aux;
    } else if (p == LNULL) {
        last(*L)->next = aux;
    } else {
        aux->next = p->next;
        p->next = aux;

        /* se insertó el nodo auxiliar en la siguiente posición a p
         * se intercambian los datos de aux con p */
        aux->dataUser = p->dataUser;
        p->dataUser = d;
    }
    return true;
}

/*
 * Función: deleteAtPosition
 * ----------------------------
 *   Elimina el elemento de la posición recibida
 *
 *   p: posición de la lista donde queremos eliminar el elemento
 *   *L: lista con la que se trabaja
 *
 *   return: void
 */
void deleteAtPosition(tPosL p, tList *L) {
    tPosL prev;

    if (p == *L) {
        *L = (*L)->next;
        free(p);
        return;
    }

    prev = previous(p, *L);
    tPosL next = p->next;

    free(p);

    prev->next = next;        /* el anterior a p apunta al siguiente a p */
}

/*
 * Función: getItem
 * ----------------------------
 *   Devuelve el item de una posición de la lista
 *
 *   p: posición de la lista de donde se quiere el item
 *
 *   return: el item de la posición indicada
 */
tItemL getItem(tPosL p, tList L) {
    return p->dataUser;
}

/*
 * Función: updateItem
 * ----------------------------
 *   Actualiza el item de una posición de la lista
 *
 *   i: nuevo item actualizado
 *   p: posición de la lista que se quiere actualizar
 *
 *   return: void
 */
void updateItem(tItemL i, tPosL p, tList *L) {
    p->dataUser = i;
}

/*
 * Función: findItem
 * ----------------------------
 *   Busca la posición de un nickname en la lista
 *
 *   n: nickname a buscar
 *   L: lista con la que se trabaja
 *
 *   return: la posición del nickname
 *      NULL si no se encontró
 */
tPosL findItem(tNickname n, tList L) {
    if (isEmptyList(L))
        return LNULL;

    for (tPosL j = L; j != LNULL; j = j->next) {
        if (strcmp(j->dataUser.nickname, n) == 0)
            return j;
    }

    return LNULL;
}