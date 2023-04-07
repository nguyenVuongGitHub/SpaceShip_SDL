#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
struct monster
{
    int x_pos;
    int y_pos;
    int Width;
    int height;
    int type;
    int hp;
    SDL_Texture *texture;
};
typedef struct monster monster;
struct bullet_monster{
    int x;
    int y;
    int h;
    int w;
    float radius;
    SDL_Texture *texture;
};
typedef struct bullet_monster bullet_monster;

#define PI 3.141592653589793
bullet_monster *b_m = NULL;
monster *m = NULL;
void initMonster();
void loadMonster();
SDL_Rect *getRect();
void drawMonster();
void drawBulletMonster();
void initBulletMonster();
void loadBulletMonster();
void spawn_bullets_around_enemy(int num_bullets);
//==================================================

void initMonster()
{
    m = (monster*)malloc(sizeof(monster));
    m->x_pos = 600;
    m->y_pos = 100;
    m->Width = 64;
    m->height = 64;
    m->hp = 0;
    m->type =1;
    m->texture = NULL;
    loadMonster();
}
void initBulletMonster()
{
    b_m = (bullet_monster*)malloc(sizeof(bullet_monster));
    b_m->h = 30;
    b_m->w = 30;
    b_m->x = m->x_pos;
    b_m->y = m->y_pos;
    b_m->radius = 20;
    b_m->texture = NULL;
    loadBulletMonster();
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
            SDL_Rect rect = {m->x_pos, m->y_pos, m->Width, m->height};
            // Render ảnh vào rect
            SDL_RenderCopy(renderer, m->texture, NULL, &rect);
        }
    }
    else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }  
}
void loadBulletMonster()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image/BulletThreat2.png");
    if(surface != NULL){
        // Tạo texture từ surface
        b_m->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // giải phóng surface khi không dùng nữa.
        if(b_m->texture == NULL){
                     printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }
        else{
            SDL_Rect rect = {b_m->x, b_m->y, b_m->w, b_m->h};
            // Render ảnh vào rect
            SDL_RenderCopy(renderer, b_m->texture, NULL, &rect);
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
    
    SDL_RenderCopy(renderer, m->texture, NULL, &rectMonster);
}
void drawBulletMonster()
{
    SDL_Rect rect = {
        b_m->x,b_m->y,b_m->w,b_m->h
    };
    SDL_RenderCopy(renderer,b_m->texture,NULL, &rect);
}
void spawn_bullets_around_enemy(int num_bullets) {

    float angle_between_bullets = 2 * PI / num_bullets; // Góc giữa các viên đạn
    for (int i = 0; i < num_bullets; i++) {
        // Tính toán tọa độ của viên đạn thứ i trên đường tròn
        b_m->x = m->x_pos + b_m->radius  * cos(i * angle_between_bullets);
        b_m->y = m->y_pos + b_m->radius  * sin(i * angle_between_bullets);
        // Tạo ra viên đạn tại tọa độ này
        drawBulletMonster();
        b_m->radius+=0.4;
        if(b_m->radius >= 500) b_m->radius = 20;
    }
}