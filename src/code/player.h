#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "text.h"
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

player playerer; // biến lưu thông tin người chơi
list_pr *lpr = NULL; // danh sách người chơi để lấy xếp hạng

void initPlayer(player p);
void initListPr(list_pr *l); 
node_pr *createNode(player data);
void addNode(node_pr *node, list_pr *l);
void printList(list_pr l);
void loadFile(list_pr *l);
void saveFile(list_pr *l);
void sortList(list_pr *l);
void freeListPr(list_pr *l);
void inputPlayer(player *p);
//================================================================

void initPlayer(player p)
{
    p.hp = 3;
    strcpy(p.name,"");
    p.score = 0;
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
void inputPlayer(player *p)
{
    SDL_Event e;
    bool quit = false;
    SDL_Color textColor = { 255, 255, 255 };
    int textLength = 0 ;
    text info;
    initText(&info);
    setText("INPUT YOUR NAME: ",&info);
    loadText(30,&info,pathFont,getColor(WHITE));
    setPosText(displayMode.w/2 - info.w,displayMode.h/2,&info);
    TTF_Font *font = TTF_OpenFont(pathFont,28);
    
    SDL_StartTextInput();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && textLength > 0) {
                    p->name[--textLength] = '\0';
                } else if (e.key.keysym.sym == SDLK_RETURN) {
                    quit = true;
                }
            } else if (e.type == SDL_TEXTINPUT) {
                if ((textLength + strlen(e.text.text)) < 100) {
                    strcat(p->name, e.text.text);
                    textLength += strlen(e.text.text);
                }
            }
        }

        SDL_RenderClear(renderer);
        drawText(&info);

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, p->name, textColor);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        int textWidth = 0;
        int textHeight = 0;
        SDL_QueryTexture(message, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect renderQuad = { displayMode.w/2 +2,displayMode.h/2, textWidth, textHeight };
        SDL_RenderCopy(renderer, message, NULL, &renderQuad);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
        // moveBackground();
        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    p->hp = 3;
    p->score = 0;
}