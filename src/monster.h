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

void initMonster(monster *m);
void loadMonster(monster *m);
SDL_Rect *getRect(monster *m);
void drawMonster(monster *m);
//==================================================

void initMonster(monster *m)
{
    m->x_pos = 0;
    m->y_pos = 0;
    m->height = 0;
    m->hp = 0;
    m->type =1;
}