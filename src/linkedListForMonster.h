#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "monster.h"

struct node
{
    monster data;
    struct node *next;
};
typedef struct node node;

struct MonsterList{
    node *head;
    node *tail;
    int size;
    
};
typedef struct MonsterList monsterList;

monsterList *l = NULL;

void initMonsterList(monsterList *l);
node *createNode(monster data);
void push_back(monsterList *l, node *newNode);
node *getNode(monsterList *l, int index);
void remove(monsterList *l,node *target);
int getSize(monsterList l);

//===================================
void initMonsterList(monsterList *l) {
    
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

node *createNode(monster data) {
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push_back(monsterList *l, node *newNode) {
    if (l->head == NULL) {
        l->head = newNode;
        l->tail = newNode;
    } else {
        l->tail->next = newNode;
    }
    l->tail = newNode;
    l->size++;
}

node *getNode(monsterList *l, int index) {
    int i = 0;
    if(index == 0)
    {
        return l->head;
    }
    node *currentNode = l->head;
    while (currentNode != NULL) {
        if (i == index) {
            return currentNode;
        }
        i++;
        currentNode = currentNode->next;
    }
    return NULL;
}

void remove(monsterList *l, node *target) {
    node *currentNode = l->head;
    if (target == l->head) {
        l->head = l->head->next;
        free(target);
        l->size--;
        return;
    }
    while (currentNode != NULL && currentNode->next != target) {
        currentNode = currentNode->next;
    }
    if (currentNode != NULL) {
        currentNode->next = target->next;
        free(target);
        l->size--;
    }
}

int getSize(monsterList l) {
    return l.size;
}
