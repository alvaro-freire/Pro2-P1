/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: 21 / 03 / 2021
 */

#include "dynamic_list.h"

/*
 * Función: createEmptyList
 * ----------------------------
 *   Crea una lista vacía
 *
 *   *L: lista con la que se trabaja
 *
 *   devuelve: void
 */
void createEmptyList(tList *L) {
    *L = LNULL;
}

/*
 * Función: isEmptyList
 * ----------------------------
 *   Comprueba si la lista está vacía (true)
 *   o si contiene algún elemento (false)
 *
 *   L: lista con la que se trabaja
 *
 *   devuelve: bool (true o false)
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
 *   devuelve: la posición buscada
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
 *   devuelve: la posición buscada
 */
tPosL last(tList L) {
    tPosL aux;
    for (aux = L; aux->next != LNULL; aux = aux->next);
    return aux;
}

/*
 * Función: next
 * ----------------------------
 *   Busca la siguiente posición al nodo recibido
 *
 *   p: posición de la lista para buscar su siguiente
 *
 *   devuelve: la posición buscada
 */
tPosL next(tPosL p, tList L) {
    return p->next;
}

/*
 * Función: previous
 * ----------------------------
 *   Busca la anterior posición al nodo recibido
 *
 *   p: posición de la lista para buscar su anterior
 *
 *   devuelve: la posición buscada
 */
tPosL previous(tPosL p, tList L) {
    if (p == L)
        return LNULL;   /* si la posición recibida es la primera de la lista, devuelve NULL */

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
 *   devuelve: bool (true si el elemento fue insertado o false si no fue posible)
 */
bool insertItem(tItemL d, tPosL p, tList *L) {
    tPosL aux;                             /* se declara un puntero a nodo auxiliar */
    aux = malloc(sizeof(struct tNode));    /* se le reserva espacio en memoria de un nodo */

    /* en caso de que no sea posible reservar espacio en memoria, devuelve false */
    if (aux == LNULL)
        return false;

    /* se define el nodo: */
    aux->dataUser = d;
    aux->next = LNULL;

    /* se inserta el nodo: */
    if (isEmptyList(*L)) {
        *L = aux;               /* inserta el item en la primera posición */
    } else if (p == LNULL) {
        last(*L)->next = aux;   /* inserta el item en la última posición */
    } else {
        aux->next = p->next;            /* el siguiente nodo al auxiliar es el siguiente nodo a p */
        p->next = aux;                  /* el siguiente nodo a p ahora es el nodo auxiliar */

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
 *   Elimina un elemento de la posición recibida
 *
 *   p: posición de la lista donde queremos eliminar el elemento
 *   *L: lista con la que se trabaja
 *
 *   devuelve: void
 */
void deleteAtPosition(tPosL p, tList *L) {
    tPosL prev;

    /* si se quiere eliminar el primer nodo de la lista: */
    if (p == *L) {
        *L = (*L)->next;
        free(p);
        return;
    }

    /* p es el nodo que se quiere eliminar */

    prev = previous(p, *L);   /* se guarda en prev el anterior nodo a p */
    tPosL next = p->next;     /* se guarda en next el siguiente nodo a p */

    free(p);                  /* se libera p de la lista */

    prev->next = next;        /* el anterior a p apunta al siguiente a p */
}

/*
 * Función: getItem
 * ----------------------------
 *   Devuelve el item de una posición de la lista
 *
 *   p: posición de la lista de donde se quiere el item
 *
 *   devuelve: el item de la posición indicada
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
 *   devuelve: void
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
 *   devuelve: la posición del nickname (NULL si no se encontró)
 */
tPosL findItem(tNickname n, tList L) {
    if (isEmptyList(L))
        return LNULL;   /*  */

    /* recorre toda la lista: */
    for (tPosL j = L; j != LNULL; j = j->next) {
        if (strcmp(j->dataUser.nickname, n) == 0)
            return j;
    }

    /* si no se encuentra el nickname: */
    return LNULL;
}