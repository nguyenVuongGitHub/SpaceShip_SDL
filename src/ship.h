#pragma once
#include <SDL2/SDL.h>

// trạng thái của tàu 
// live là còn sống
// die là đã chết -> bất tử
enum Status {
        LIVE,DIE
};

struct ship{
    int X ;
    int Y ;
    int W ;
    int H ;
    Status status;
    SDL_Rect frame_clip[8];
    SDL_Texture *texture;
};
typedef struct ship ship;
ship *s = NULL;
void initShip(ship *s);
void loadShip();
void drawShip(int cur);
//========================================================================  
void initShip(ship *s)
{
    s->X = 600;
    s->Y = 610;
    s->W = 64;
    s->H = 64;
    s->texture = NULL;
    s->status = LIVE;
    loadShip();
}
void loadShip()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    const char * pathAlive = "image/spaceship.png";
    const char * pathDie = "image/spaceshipDIE.png";

    if(s->status == LIVE)
    {
        surface = IMG_Load(pathAlive);
        s->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // giải phóng surface khi không dùng nữa.
        if(s->texture == NULL)
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        
    }else{
        surface = IMG_Load(pathDie);
        s->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // giải phóng surface khi không dùng nữa.
        if(s->texture == NULL)
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
    }
    if(surface != NULL){

    }
    else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }  
}
void set_clip()
{
    for (int i = 0; i < 8; i++)
    {
        s->frame_clip[i].x = i * 64;
        s->frame_clip[i].y = 0;
        s->frame_clip[i].w = 64;
        s->frame_clip[i].h = 64;
    }
}
void moveShip(){
    SDL_GetMouseState(&mouseX,&mouseY);
    s->X = mouseX-32;
    s->Y = mouseY;
}
void drawShip(int cur){
    SDL_GetMouseState(&mouseX,&mouseY);
    s->X = mouseX-32;
    s->Y = mouseY;
    SDL_Rect rectShip = {
            s->X,
            s->Y,
            s->W,
            s->H
    };
    SDL_RenderCopy(renderer,s->texture,&s->frame_clip[cur],&rectShip);
}