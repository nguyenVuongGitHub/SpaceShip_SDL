#pragma once
#include <SDL2/SDL.h>

struct ship{
    int X ;
    int Y ;
    int W ;
    int H ;
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
    s->W = 200;
    s->H = 200;
    s->texture = NULL;
    loadShip();
}
void loadShip()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image/ship.png");
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

void moveShip(){
    SDL_GetMouseState(&mouseX,&mouseY);
    // SDL_RenderClear(renderer);
    s->X = mouseX;
    s->Y = mouseY;
    // SDL_Rect shipRect = {mouseX-100, mouseY-100, s->W, s->H};
    
    // SDL_RenderDrawRect(renderer,&shipRect);
    // SDL_RenderCopy(renderer, background, NULL, NULL);
    // SDL_RenderCopy(renderer, s->texture, NULL, &shipRect);
    // drawShip();
}
void drawShip(){
    SDL_Rect rectShip = {
            s->X-100,
            s->Y-100,
            s->W,
            s->H
    };
    SDL_RenderCopy(renderer,s->texture,NULL,&rectShip);
}