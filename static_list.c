/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: 21 / 03 / 2021
 */

#include "static_list.h"

void createEmptyList(tList *L) {
    L->lastPos = LNULL;
}

bool isEmptyList(tList L) {
    return L.lastPos == LNULL;
}

tPosL first(tList L) {
    return 0;
}

tPosL last(tList L) {
    return L.lastPos;
}

tPosL next(tPosL p, tList L) {
    return (p == L.lastPos ? LNULL : ++p);
}

tPosL previous(tPosL p, tList L) {
    return --p;
}

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

void deleteAtPosition(tPosL p, tList *L) {
    // recorremos la lista desde la posición a eliminar:
    for (tPosL i = p; i < L->lastPos; ++i) {
        L->dataUser[i] = L->dataUser[i + 1];    // sustituimos cada item por su siguiente
    }
    L->lastPos--;
}

tItemL getItem(tPosL p, tList L) {
    return L.dataUser[p];
}

void updateItem(tItemL i, tPosL p, tList *L) {
    L->dataUser[p] = i;
}

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
