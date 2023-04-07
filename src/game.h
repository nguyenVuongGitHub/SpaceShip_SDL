#pragma once
#include "global.h"
#include "menu.h"
#include "monster.h"
void loadBackGround();
void loadMouse();
void loadHelp(); // tải ảnh phần hướng dẫn

void drawBackGround();
void drawMouse();
void drawHelp();

void init();
void freeAll();

void set_clip_background();
SDL_Rect background_clip[8];
//==========================

void init()
{
    
    SDL_Init(SDL_INIT_EVERYTHING);
    int index_window = 0;
    
    SDL_GetCurrentDisplayMode(index_window,&displayMode);
    window = SDL_CreateWindow("game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,displayMode.w,displayMode.h,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    s = (ship*)malloc(sizeof(ship));
    // m=(monster*)malloc(sizeof(monster));
    // SDL_ShowCursor(SDL_DISABLE);
    initMonster();
    initBulletMonster();
    initShip(s);
    set_clip();
    set_clip_background();

    loadBackGround();  
    loadMouse();
    loadHelp();
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
    }
     else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}   

void loadHelp()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image\\help.png");
    if(surface != NULL){
        background_help = SDL_CreateTextureFromSurface(renderer,surface);
        if(background_help == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }else{
            SDL_RenderCopy(renderer,background_help,NULL,NULL);
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
void drawHelp()
{
    SDL_RenderCopy(renderer,background_help,NULL,NULL);\

    // Vẽ nút bắt đầu
    SDL_Rect startRect = { 1200, 750, 200, 50 };
    SDL_RenderCopy(renderer, startButton, NULL, &startRect);

    // Vẽ nút thoát
    SDL_Rect backRect = { 200, 750, 200, 50 };
    SDL_RenderCopy(renderer, backButton, NULL, &backRect);

    SDL_GetMouseState(&mouseX,&mouseY);
    if ( mouseX >= 1200 && mouseX <= 1400 && mouseY >= 750 && mouseY <= 800)
    {
        // Vẽ nút bắt đầu
        SDL_RenderCopy(renderer, startButton2, NULL, &startRect);
    }
    if( mouseX >= 200 && mouseX <= 400 && mouseY >= 750 && mouseY <= 800)
    {
        SDL_RenderCopy(renderer, backButton2, NULL, &backRect);
    }

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
// cần viết thêm
void freeAll()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(s->texture);
    SDL_DestroyTexture(background);
    SDL_DestroyMutex(mutex_bullet);
}