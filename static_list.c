/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: 24 / 03 / 2021
 */

#include "static_list.h"

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
    L->lastPos = LNULL;
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
    return L.lastPos == LNULL;
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
    return 0;
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
    return L.lastPos;
}

/*
 * Función: next
 * ----------------------------
 *   Busca la siguiente posición a la recibida
 *
 *   p: posición de la lista para buscar su siguiente
 *   L: lista con la que se trabaja
 *
 *   return: la siguiente posición a la recibida
 *      si recibe la última posición, devuelve -1
 */
tPosL next(tPosL p, tList L) {
    return (p == L.lastPos ? LNULL : ++p);
}

/*
 * Función: previous
 * ----------------------------
 *   Busca la anterior posición a la recibida
 *
 *   p: posición de la lista para buscar su anterior
 *
 *   return: la anterior posición a la recibida
 */
tPosL previous(tPosL p, tList L) {
    return --p;
}

/*
 * Función: insertItem
 * ----------------------------
 *   Inserta un item en la posición recibida
 *   si esa posición es -1 (nula), el item se inserta en la última posición
 *
 *   d: item que se quiere insertar
 *   p: posición de la lista donde se quiere insertar el item
 *   *L: lista con la que se trabaja
 *
 *   return: true si el elemento fue insertado
 *      false si la inserción no fue posible
 */
bool insertItem(tItemL d, tPosL p, tList *L) {
    if (L->lastPos == MAX_ITEMS - 1 || findItem(d.nickname, *L) != LNULL)
        return false;

    if (p == LNULL) {
        L->lastPos++;
        L->dataUser[L->lastPos] = d;
    } else {
        L->lastPos++;
        for (tPosL i = L->lastPos; i >= p; --i) {
            L->dataUser[i + 1] = L->dataUser[i];
        }
        L->dataUser[p] = d;
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
    for (tPosL i = p; i < L->lastPos; ++i) {
        L->dataUser[i] = L->dataUser[i + 1];
    }
    L->lastPos--;
}

/*
 * Función: getItem
 * ----------------------------
 *   Devuelve el item de una posición de la lista
 *
 *   p: posición de la lista de donde se quiere el item
 *   L: lista con la que se trabaja
 *
 *   return: el item de la posición indicada
 */
tItemL getItem(tPosL p, tList L) {
    return L.dataUser[p];
}

/*
 * Función: updateItem
 * ----------------------------
 *   Actualiza el item de una posición de la lista
 *
 *   i: nuevo item actualizado
 *   p: posición de la lista que se quiere actualizar
 *   *L: lista con la que se trabaja
 *
 *   return: void
 */
void updateItem(tItemL i, tPosL p, tList *L) {
    L->dataUser[p] = i;
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
 *      -1 si no se encontró
 */
tPosL findItem(tNickname n, tList L) {
    if (isEmptyList(L))
        return LNULL;

    for (tPosL i = 0; i <= L.lastPos; ++i) {
        if (strcmp(L.dataUser[i].nickname, n) == 0)
            return i;
    }

    return LNULL;
}
