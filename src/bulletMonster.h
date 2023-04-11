#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "global.h"

struct bullet_monster{
    int x;
    int y;
    int h;
    int w;
    int speed;
    float radius;
    bool active;
    float angle;
    int type;
    SDL_Texture *texture;
};
typedef struct bullet_monster bullet_monster;

void initListBulletMonster();
void initBulletMonster(bullet_monster *bullet);
void loadBulletMonster(bullet_monster *bullet, int type_bullet);
void drawBulletMonster(bullet_monster *bullet);
void moveBulletMonster(bullet_monster *bullet);
// void addBulletToList(int num);
#define MAX_BULLET_MONSTER 5000

bullet_monster *listBulletMonster[MAX_BULLET_MONSTER]; // giới hạn đạn trên màn hình là 5000
//===========================================
void initListBulletMonster()
{
    // cấp phát bộ nhớ cho mảng các viên đạn
    for(int i = 0; i < MAX_BULLET_MONSTER; i ++)
        listBulletMonster[i] = (bullet_monster*)malloc(sizeof(bullet_monster));
    
    // cho trạng thái của các viên đạn là false - ko di chuyển
    for(int i = 0; i < MAX_BULLET_MONSTER; i++)
        listBulletMonster[i]->active = false;

}
void initBulletMonster(bullet_monster *bullet)
{
    bullet->h = 0;
    bullet->w = 0;
    bullet->x = -10;
    bullet->y = -10;
    bullet->angle = 0;
    bullet->radius = 0;
    bullet->type = 0;
    bullet->speed = 0;
    bullet->texture = NULL;
    bullet->active = false;
}
void loadBulletMonster(bullet_monster *bullet, int type_bullet)
{
    IMG_Init(IMG_INIT_PNG);

    const char* bullet_file_path;
    if(type_bullet == 1)
    {
        bullet_file_path = "image/BulletThreat.png";
        bullet->type = type_bullet;
    }
    else if(type_bullet == 2 || type_bullet == 7)
    {
        bullet_file_path = "image/BulletThreat6.png";
        bullet->type = type_bullet;
    }
    else if(type_bullet == 3 || type_bullet == 6)
    {
        bullet_file_path = "image/BulletThreat.png";
        bullet->type = type_bullet;
    }
    else if(type_bullet == 4)
    {
        bullet_file_path = "image/BulletThreat2.png";
        bullet->type = type_bullet;
    }
    else if(type_bullet == 5)
    {
        bullet_file_path = "image/BulletThreat5.png";
        bullet->type = type_bullet;
    }
    // else if(type_bullet == 10)
    // {
        
    // }
    SDL_Surface* bullet_surface = IMG_Load(bullet_file_path); 
    if (bullet_surface != NULL)
    {
        bullet->texture = SDL_CreateTextureFromSurface(renderer, bullet_surface);
    }
    SDL_FreeSurface(bullet_surface);
}

void drawBulletMonster(bullet_monster *bullet)
{
    SDL_Rect r = {
        bullet->x, bullet->y, bullet->w, bullet->h
    };
    SDL_RenderCopy(renderer,bullet->texture,NULL,&r);
}

void moveBulletMonster(bullet_monster *bullet)
{
    if(bullet->type == 1 || bullet->type == 2 || bullet->type == 7 || bullet->type == 6 || bullet->type == 5)
    {
        bullet->x += cos(bullet->angle)*bullet->speed;
        bullet->y += sin(bullet->angle)*bullet->speed;
    }
    else if(bullet->type == 3)
    {
        bullet->y += 3;
        bullet->x += sin(bullet->y*M_PI/50.0)*bullet->speed;
    }
    else if(bullet->type == 4)
    {
        bullet->y += bullet->speed;
    }
    if(bullet->x >= displayMode.w-1 || bullet->x <= 1 || bullet->y <= 0 || bullet->y >= displayMode.h-1)
    {
        bullet->active = false;
    }
}