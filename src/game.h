#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <unistd.h>
#include "bullet.h"
#include "ship.h"
// #include "list_bullet.h"
#include "global.h"

void loadBackGround();
void init();
void freeAll();
void drawBackGround();
//==========================

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    int index_window = 0;
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(index_window,&displayMode);

    window = SDL_CreateWindow("game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,displayMode.w,displayMode.h,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    s = (ship*)malloc(sizeof(ship));
    initShip(s);
    
    initBullets();
    loadBackGround();  
}


void loadBackGround()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_JPG);
    surface = IMG_Load("image\\background.jpg");
    if(surface != NULL){
        background = SDL_CreateTextureFromSurface(renderer,surface);
        if(background == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }else{
            SDL_RenderCopy(renderer,background,NULL,NULL);
            SDL_FreeSurface(surface);
        }   
    }else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
    
}   

void freeAll()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(s->texture);
    SDL_DestroyTexture(background);
   // SDL_DestroyTexture(bullet);
    // SDL_DestroyMutex(bulletMutex);
}
void drawBackGround()
{
    SDL_RenderCopy(renderer,background,NULL,NULL);
}