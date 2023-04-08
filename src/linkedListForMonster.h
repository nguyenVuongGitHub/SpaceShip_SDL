#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "monster.h"

struct node
{
    monster data;
    struct node *next;
};
typedef struct node node_M;

struct MonsterList{
    node_M *head;
    node_M *tail;
    int size;
    
};
typedef struct MonsterList monsterList;

monsterList *lm = NULL;

void initMonsterList(monsterList *l);
node_M *createNode(monster data);
void push_back(monsterList *l, node_M *newNode);
node_M *getNode(monsterList *l, int index); // lấy node tại index thứ bao nhiêu giống như a[i]
void removeNode(monsterList *l,node_M *target);
int getSize(monsterList l);

//===================================
void initMonsterList(monsterList *l) {
    
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

node_M *createNode(monster data) {
    node_M *newNode = (node_M*) malloc(sizeof(node_M));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push_back(monsterList *l, node_M *newNode) {
    if (l->head == NULL) {
        l->head = newNode;
        l->tail = newNode;
    } else {
        l->tail->next = newNode;
    }
    l->tail = newNode;
    l->size++;
}

node_M *getNode(monsterList *l, int index) {
    int i = 0;
    if(index == 0)
    {
        return l->head;
    }
    node_M *currentNode = l->head;
    while (currentNode != NULL) {
        if (i == index) {
            return currentNode;
        }
        i++;
        currentNode = currentNode->next;
    }
    return NULL;
}

void removeNode(monsterList *l, node_M *target) {
    node_M *currentNode = l->head;
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
void freeList(monsterList *l)
{
    node_M *head = l->head;
    while(head != NULL)
    {
        node_M *temp = l->head;
        head = head->next;
        l->head = head;
        free(temp);

    }
}
