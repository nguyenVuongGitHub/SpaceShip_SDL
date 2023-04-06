#pragma once
#include <SDL2/SDL.h>

struct monster
{
    int x_pos;
    int y_pos;
    int Width;
    int height;
    int type;
    int hp;
    SDL_Texture *texture;
    SDL_Rect *rect;
};
typedef struct monster monster;
monster *m = NULL;
void initMonster();
void loadMonster();
SDL_Rect *getRect();
void drawMonster();
//==================================================

void initMonster()
{
    m = (monster*)malloc(sizeof(monster));
    m->x_pos = 600;
    m->y_pos = 100;
    m->Width = 200;
    m->height = 200;
    m->hp = 0;
    m->type =1;
    loadMonster();
}

void loadMonster()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image/SpaceThreat1.png");
    if(surface != NULL){
        // Tạo texture từ surface
        m->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // giải phóng surface khi không dùng nữa.
        if(m->texture == NULL){
                     printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }
        else{
            // Tạo rect để chứa ảnh
            // m->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
            // m->rect->x = m->x_pos;
            // m->rect->y = m->y_pos;
            SDL_Rect rect = {m->x_pos, m->y_pos, m->Width, m->height};
            
            // SDL_QueryTexture(m->texture, NULL, NULL, &(m->rect->w), &(m->rect->h));

            // Render ảnh vào rect
            SDL_RenderCopy(renderer, m->texture, NULL, &rect);
        }
    }
    else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }  
}



void drawMonster()
{
    SDL_Rect rectMonster = {
        m->x_pos,
        m->y_pos,
        m->Width,
        m->height
    };
    // printf("cccc");
    SDL_RenderCopy(renderer, m->texture, NULL, &rectMonster);
}

