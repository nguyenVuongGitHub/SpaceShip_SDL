#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct player
{
    long long score;
    short hp;
    char name[50];
};
typedef struct player player;
struct nodeP{
    player data;
    struct nodeP *next;
};
typedef struct nodeP node_pr;
struct list{
    node_pr *head;
    node_pr *tail;
    short size;
};
typedef struct list list_pr;

void initPlayer(player p);
void inputPlayer(player *p);
void initListPr(list_pr *l); 
node_pr *createNode(player data);
void addNode(node_pr *node, list_pr *l);
void printList(list_pr l);
void loadFile(list_pr *l);
void saveFile(list_pr *l);
void sortList(list_pr *l);
void freeListPr(list_pr *l);
//================================================================

void initPlayer(player p)
{
    p.hp = 3;
    strcpy(p.name,"");
    p.score = 0;
}
void inputPlayer(player *player)
{
    fflush(stdin);
    printf("\nnhap ten : ");
    gets(player->name);
    printf("nhap diem :");
    scanf("%d", &player->score);
}
void initListPr(list_pr *l){
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}
node_pr *createNode(player data)
{
    node_pr *newNode = (node_pr*) malloc(sizeof(node_pr));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// thêm vào cuối danh sách
void addNode(node_pr *node, list_pr *l)
{
    if(l->head == NULL){
        l->head = l->tail = node;
    }else{
        l->tail->next = node;
        l->tail = node;
    }
    l->size++;
}
void printList(list_pr l)
{
    node_pr *head = l.head;
    while(head != NULL){
        
        printf("\nTen: ");
        puts(head->data.name);
        printf("Diem: %d", head->data.score);
        head = head->next;
    }
}
void loadFile(list_pr *l)
{
    FILE *fileIn;
    char line[100];
    fileIn = fopen("src/data.txt", "r");
    
    if (fileIn == NULL) {
        
        printf("Khong mo duoc file\n");
        return;
    }
    
    while (fgets(line, 100, fileIn) != NULL) {
        char *token = strtok(line, ";");
        player pl;
        
        strcpy(pl.name, token);
        pl.score = atoi(strtok(NULL, ";"));
        
        node_pr *newNode = createNode(pl);
        
        addNode(newNode, l);
    }
    fclose(fileIn);
}
void saveFile(list_pr *l)
{
    FILE *fileOut;
    fileOut = fopen("src/data.txt", "w+");
    node_pr *head = l->head;
    while(head != NULL){
        fputs(head->data.name, fileOut);
        fprintf(fileOut, ";%d\n", head->data.score);
        head = head->next;
    }
    fclose(fileOut);
}
void sortList(list_pr *l)
{
    for(node_pr *i = l->head; i != NULL;i = i->next)
    {
        for(node_pr *j = i; j != NULL; j = j->next)
        {
            if(j->data.score > i->data.score)
            {
                player temp = i->data;
                i->data = j->data;
                j->data = temp;
                temp = i->data;
            }
        }
    }
}
void freeListPr(list_pr *l)
{
    node_pr *head = l->head;
    while(head != NULL)
    {
        head = l->head->next;
        free(l->head);
        l->head = head;
        l->head = NULL;
    }
}