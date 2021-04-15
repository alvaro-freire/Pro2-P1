/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: 08 / 04 / 2021
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
    tPosL pos;
    for (pos = L; pos->next != LNULL; pos = pos->next);
    return pos;
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

    tPosL pos;

    /* se recorre la lista hasta llegar al anterior elemento a p: */
    for (pos = L; pos->next != p; pos = pos->next);
    return pos;
}

/*
 * Función: insertItem
 * ----------------------------
 *   Inserta un item en la posición recibida
 *   si esa posición es NULL, el item se inserta en la última posición
 *
 *   i: item que se quiere insertar
 *   p: posición de la lista donde se quiere insertar el item
 *   *L: lista con la que se trabaja
 *
 *   return: true si el elemento fue insertado
 *      false si la inserción no fue posible
 */
bool insertItem(tItemL i, tPosL p, tList *L) {
    /* se crea un nodo */
    tPosL node;
    node = malloc(sizeof(struct tNode));

    if (node == LNULL || findItem(i.nickname, *L) != LNULL)
        return false;

    node->dataUser = i;

    if (isEmptyList(*L)) {
        node->next = LNULL;
        *L = node;
    } else if (p == LNULL) {
        node->next = LNULL;
        last(*L)->next = node;
    } else {
        /* se inserta el nodo en la siguiente posición a p */
        node->next = p->next;
        p->next = node;

        /* se intercambian los datos de node con p */
        node->dataUser = p->dataUser;
        p->dataUser = i;
    }
    return true;
}

/*
 * Función: deleteAtPosition
 * ----------------------------
 *   Elimina el elemento de la posición recibida
 *
 *   p: posición de la lista donde se quiere eliminar el elemento
 *   *L: lista con la que se trabaja
 *
 *   return: void
 */
void deleteAtPosition(tPosL p, tList *L) {
    /* si se quiere eliminar el primer elemento: */
    if (p == *L) {
        *L = (*L)->next;
        free(p);
        return;
    }

    tPosL prev = previous(p, *L);
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
    for (tPosL pos = L; pos != LNULL; pos = pos->next) {
        /* si se encuentra el nickname: */
        if (strcmp(pos->dataUser.nickname, n) == 0)
            return pos;
    }
    return LNULL;
}