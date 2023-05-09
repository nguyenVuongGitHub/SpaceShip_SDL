#pragma once
// #include "global.h"
// #include "menu.h"
#include "monster.h"
#include "linkedListForMonster.h"
// #include "player.h"
// #include "text.h"
#include <SDL2/SDL_ttf.h>
#include "music.h"




void loadBackGround();
void loadMouse();
void loadHelp(); // tải ảnh phần hướng dẫn

void drawMouse();
void drawHelp();

void init();
void freeAll();

void moveBackground();

SDL_Rect background_clip = {0,0,2360,1544};
//==========================

void init()
{
    
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_ShowCursor(SDL_DISABLE);
    short index_window = 0;
    
    SDL_GetCurrentDisplayMode(index_window,&displayMode);
    window = SDL_CreateWindow("game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,displayMode.w,displayMode.h,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    
    s = (ship*)malloc(sizeof(ship));
    lpr = (list_pr*)malloc(sizeof(list_pr));
    
    initListPr(lpr);
 


    loadFile(lpr);
    initMusic();

    initShip(s);
    set_clip();
    loadBackGround();  
    loadMouse();
    loadHelp();
    volume();
    
    if (initMenu() != 0)
    {
        printf("loi!! %s\n",SDL_GetError());
    }
    initHelp();
    
}

void moveBackground()
{
    SDL_Rect renderquad1={background_clip.x,background_clip.y,background_clip.w,background_clip.h};
    SDL_RenderCopy(renderer,background,NULL,&renderquad1);

    SDL_Rect renderquad2={background_clip.x,background_clip.y-displayMode.h,background_clip.w,background_clip.h};
    SDL_RenderCopy(renderer,background,NULL,&renderquad2);
    background_clip.y+=2;
    if(background_clip.y>=displayMode.h)
    {
        background_clip.y=0;
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
    }
     else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}   



// void drawBackGround(int cur)
// {
//     SDL_RenderCopy(renderer,background,&background_clip[cur],NULL);
// }

void drawMouse()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect rectMouse = 
    {
        mouseX,mouseY,100,100
    };
    SDL_RenderCopy(renderer,mouse,NULL,&rectMouse);
}
// cần viết thêm
void freeAll()
{
    freeBullets(); //giải phóng danh sách đạn người chơi
    freeList(lm); // giải phóng list quái vật
    freeBulletMonster();
    freeListPr(lpr); // giải phóng list người chơi
    SDL_DestroyWindow(window); // giải phóng window
    SDL_DestroyRenderer(renderer); // giải phóng renderer
    SDL_DestroyTexture(s->texture); // giải phóng texture tàu
    SDL_DestroyTexture(background); // giải phóng texture background
    desMusic();
    SDL_Quit();
}