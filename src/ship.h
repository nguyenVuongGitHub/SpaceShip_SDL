#pragma once
#include <SDL2/SDL.h>

struct ship{
    int X ;
    int Y ;
    int W ;
    int H ;
    SDL_Rect frame_clip[8];
    SDL_Texture *texture;
};
typedef struct ship ship;
ship *s = NULL;
void initShip();
void loadShip();
void drawShip();
//========================================================================  
void initShip(ship *s)
{
    s->X = 600;
    s->Y = 610;
    s->W = 64;
    s->H = 64;
    s->texture = NULL;
    loadShip();
}
void loadShip()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image/spaceship.png");
    if(surface != NULL){
        // Tạo texture từ surface
        s->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // giải phóng surface khi không dùng nữa.
        if(s->texture == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }
        else{
            // Tạo rect để chứa ảnh
            SDL_Rect rect = {s->X, s->Y, s->W, s->H};

            // Render ảnh vào rect
            SDL_RenderCopy(renderer, s->texture, NULL, &rect);
        }
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
    s->X = mouseX;
    s->Y = mouseY;
}
void drawShip(int cur){
    SDL_Rect rectShip = {
            s->X-32,
            s->Y-32,
            s->W,
            s->H
    };
    SDL_RenderCopy(renderer,s->texture,&s->frame_clip[cur],&rectShip);
}