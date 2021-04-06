/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Pablo Lago Naveiras LOGIN 1: p.lago1
 * AUTHOR 2: Álvaro Freire Ares LOGIN 2: alvaro.freirea
 * GROUP: 3.3
 * DATE: ** / 04 / 2021
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITEMS 25
#define LNULL -1

typedef int tPosL;
typedef struct tList {
    tItemL dataUser[MAX_ITEMS];
    tPosL lastPos;
} tList;

void createEmptyList(tList *L);

bool isEmptyList(tList L);

tPosL first(tList L);

tPosL last(tList L);

tPosL next(tPosL p, tList L);

tPosL previous(tPosL p, tList L);

bool insertItem(tItemL d, tPosL p, tList *L);

void deleteAtPosition(tPosL p, tList *L);

tItemL getItem(tPosL p, tList L);

void updateItem(tItemL i, tPosL p, tList *L);

tPosL findItem(tNickname n, tList L);

#endif