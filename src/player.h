#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct player
{
    int score;
    char name[100];
};
typedef struct player player;
struct node{
    player data;
    struct node *next;
};
typedef struct node node;
struct list{
    node *head;
    node *tail;
};
typedef struct list list;
FILE *fileOut;
FILE *fileIn;

void inputPlayer(player *p);
void initList(list *l); 
node *createNode(player data);
void addNode(node *node, list *l);
void printList(list l);
void loadFile(FILE *fileIn,list *l);
void saveFile(FILE *fileOut, list l);


//================================================================

void inputPlayer(player *player)
{
    fflush(stdin);
    printf("\nnhap ten : ");
    gets(player->name);
    printf("nhap diem :");
    scanf("%d", &player->score);
}
void initList(list *l){
    l->head = NULL;
    l->tail = NULL;
}
node *createNode(player data)
{
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void addNode(node *node, list *l)
{
    if(l->head == NULL){
        l->head = l->tail = node;
    }else{
        l->tail->next = node;
        l->tail = node;
    }
}
void printList(list l)
{
    

    node *head = l.head;
    while(head != NULL){
        
        printf("\nTen:");
        puts(head->data.name);
        printf("Diem: %d", head->data.score);
        head = head->next;
    }
}
void loadFile(FILE *fileIn,list *l)
{
    char line[100];
    fileIn = fopen("src/data.txt", "r");
    if (fileIn == NULL) {
        printf("Khong mo duoc file\n");
        return;
    }
    while (fgets(line, 100, fileIn) != NULL) {
        char *token = strtok(line, ";");
        player pl;
        strncpy(pl.name, token, 50);
        pl.score = atoi(strtok(NULL, ";"));
        node *newNode = createNode(pl);
        addNode(newNode, l);
    }
    fclose(fileIn);
}
void saveFile(FILE *fileOut, list l)
{
    fileOut = fopen("src/data.txt", "w+");
    node *head = l.head;
    while(head != NULL){
        
        fputs(head->data.name, fileOut);
        fprintf(fileOut, ";%d\n", head->data.score);
        head = head->next;
        
    }
}