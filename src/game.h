#pragma once
#include "global.h"
#include "menu.h"
void loadBackGround();
void loadMouse();
void init();
void freeAll();
void drawBackGround();
void drawMouse();
void set_clip_background();
SDL_Rect background_clip[8];
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
    set_clip();
    set_clip_background();
    loadBackGround();  
    loadMouse();
    if (initMenu() != 0)
    {
        printf("loi!! %s\n",SDL_GetError());
    }
}

void set_clip_background()
{
    for (int i = 0; i < 8; i++)
    {
        background_clip[i].x = 0;
        background_clip[i].y = i * 600;
        background_clip[i].w = 1200;
        background_clip[i].h = 600;
    }
}
void loadMouse()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image\\mouse.png");
    if(surface != NULL){
        mouse = SDL_CreateTextureFromSurface(renderer,surface);
        if(mouse == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }else{
            SDL_RenderCopy(renderer,mouse,NULL,NULL);
            SDL_FreeSurface(surface);
        }   
    }else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}
void loadBackGround()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image\\background2.png");
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

void drawBackGround(int cur)
{
    SDL_RenderCopy(renderer,background,&background_clip[cur],NULL);
}

void drawMouse()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect rectMouse = 
    {
        mouseX,mouseY,100,100
    };
    SDL_RenderCopy(renderer,mouse,NULL,&rectMouse);
}

// cần sửa
void freeAll()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(s->texture);
    SDL_DestroyTexture(background);
    SDL_DestroyMutex(mutex_bullet);
}