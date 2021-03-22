/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: 21 / 03 / 2021
 */

#include "dynamic_list.h"

// función que crea una función
void createEmptyList(tList *L) {
    *L = LNULL;
}

bool isEmptyList(tList L) {
    return L == LNULL;
}

tPosL first(tList L) {
    return L;
}

tPosL last(tList L) {
    tPosL aux;
    for (aux = L; aux->next != LNULL; aux = aux->next);
    return aux;
}

tPosL next(tPosL p, tList L) {
    return p->next;
}

tPosL previous(tPosL p, tList L) {
    if (p == L)
        return LNULL;

    tPosL j;
    for (j = L; j->next != p; j = j->next);
    return j;
}

bool insertItem(tItemL d, tPosL p, tList *L) {
    // declaramos un nodo auxiliar
    tPosL aux = malloc(sizeof(struct tNode));

    if (aux == LNULL)
        return false;

    // definimos el nodo:
    aux->dataUser = d;
    aux->next = LNULL;

    // lo insertamos:
    if (isEmptyList(*L)) {
        *L = aux;
    } else if (p == LNULL) {
        last(*L)->next = aux;
    } else if (p == *L) {
        aux->next = *L;
        *L = aux;
    } else {    // para insertar un nodo por el medio de la lista:
        aux->next = p->next;
        p->next = aux;
        aux->dataUser = p->dataUser;
        p->dataUser = d;
    }
    return true;
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL prev;

    // si queremos eliminar el primer nodo de la lista
    if (p == *L) {
        *L = (*L)->next;
        free(p);
        return;
    }

    // p es el nodo que queremos eliminar
    // guardamos en prev el anterior nodo a p
    prev = previous(p, *L);

    // guardamos en next el siguiente nodo a p
    tPosL next = p->next;

    free(p);    // liberamos p de la lista
    prev->next = next;   // el next del anterior a p apunta al siguiente a p
}

tItemL getItem(tPosL p, tList L) {
    return p->dataUser;
}

void updateItem(tItemL i, tPosL p, tList *L) {
    p->dataUser = i;
}

tPosL findItem(tNickname n, tList L) {
    if (isEmptyList(L))
        return LNULL;

    // recorremos toda la lista:
    for (tPosL j = L; j != LNULL; j = j->next) {
        if (strcmp(j->dataUser.nickname, n) == 0)
            return j;
    }
    return LNULL;
}