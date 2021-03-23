/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: 21 / 03 / 2021
 */

#include "static_list.h"

// función que crea una lista vacía
void createEmptyList(tList *L) {
    L->lastPos = LNULL;
}

// función que devuelve true si la lista está vacía
// y false si contiene algún elemento
bool isEmptyList(tList L) {
    return L.lastPos == LNULL;
}

// función que devuelve la posición del primer nodo de la lista recibida
tPosL first(tList L) {
    return 0;
}

// función que devuelve la posición del último nodo de la lista recibida
tPosL last(tList L) {
    return L.lastPos;
}

// función que devuelve la siguiente posición de una recibida
tPosL next(tPosL p, tList L) {
    return (p == L.lastPos ? LNULL : ++p);
}

// función que devuelve la anterior posición de una recibida
tPosL previous(tPosL p, tList L) {
    return --p;
}

// función que inserta un item en la posición recibida
// devuelve true si el item fue insertado y false si no ha sido posible
// si la posición recibida es NULL, el item se inserta en la última posición
bool insertItem(tItemL d, tPosL p, tList *L) {
    // si la lista está llena no podemos insertar:
    if (L->lastPos == MAX_ITEMS - 1)
        return false;
    else {
        if (p == LNULL) {   // insertamos en la última posición:
            L->lastPos++;
            L->dataUser[L->lastPos] = d;
        } else {    // insertamos en una posición intermedia:
            L->lastPos++;
            for (tPosL i = L->lastPos; i >= p; --i) {
                L->dataUser[i + 1] = L->dataUser[i];
            }
            L->dataUser[p] = d;
        }
        return true;
    }
}

// función que elimina un nodo de la posición recibida
void deleteAtPosition(tPosL p, tList *L) {
    // recorremos la lista desde la posición a eliminar:
    for (tPosL i = p; i < L->lastPos; ++i) {
        L->dataUser[i] = L->dataUser[i + 1];    // sustituimos cada item por su siguiente
    }
    L->lastPos--;
}

// función que recibe una posición de la lista y devuelve el item que contiene
tItemL getItem(tPosL p, tList L) {
    return L.dataUser[p];
}

// función que recibe una posición y sustituye su item por el recibido
void updateItem(tItemL i, tPosL p, tList *L) {
    L->dataUser[p] = i;
}

// función que busca un nombre de usuario en la lista
// y devuelve la posición en la que se encuentra
tPosL findItem(tNickname n, tList L) {
    if (isEmptyList(L))
        return LNULL;

    // recorremos toda la lista:
    for (tPosL i = 0; i <= L.lastPos; ++i) {
        if (strcmp(L.dataUser[i].nickname, n) == 0)
            return i;
    }
    return LNULL;
}
