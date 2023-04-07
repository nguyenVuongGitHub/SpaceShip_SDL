#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>

#define MAX_MONSTER 100
#define PI 3.141592653589793

int wave = 0; // đợt quái 
struct monster
{
    int x_pos;
    int y_pos;
    int y_limit;
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

bullet_monster *b_m = NULL;
void initMonster(monster *m);
void loadMonsterAndbullet(monster *m,bullet_monster *b_m);
void drawMonster(monster *m);
void moveMonster(monster *m);
void drawBulletMonster(bullet_monster *b_m);
void initBulletMonster(bullet_monster *b_m);
void loadBulletMonster(monster *m);
bool canSpawnBullets(monster *m);
void makeBullet(monster *m);
void spawn_bullets_around_enemy(int num_bullets,monster *m,bullet_monster *b_m);
//==================================================

void initMonster(monster *m)
{
    // m = (monster*)malloc(sizeof(monster));
    m->x_pos = 600;
    m->y_pos = 100;
    m->Width = 64;
    m->height = 64;
    m->hp = 0;
    m->type =1;
    m->texture = NULL;
}
void initBulletMonster(monster *m)
{
    b_m = (bullet_monster*)malloc(sizeof(bullet_monster));
    b_m->h = 30;
    b_m->w = 30;
    b_m->x = m->x_pos;
    b_m->y = m->y_pos;
    b_m->radius = 20;
    b_m->texture = NULL;
}
void loadMonster(monster *m)
{
    IMG_Init(IMG_INIT_PNG);

    const char* monster_file_path;
    // const char* bullet_file_path;

    if (m->type == 1) {
        monster_file_path = "image/SpaceThreat1.png";
        // bullet_file_path = "image/BulletThreat.png";
    } else if(m->type == 2) {
        monster_file_path = "image/SpaceThreat6.png";
        // bullet_file_path = "image/BulletThreat6.png";
    }
    else if(m->type == 3) {
        monster_file_path = "image/SpaceThreat2.png";
        // bullet_file_path = "image/BulletThreat.png";
    }
    else if(m->type == 4) {
        monster_file_path = "image/SpaceThreat5.png";
        // bullet_file_path = "image/BulletThreat2.png";
    }
    else if(m->type == 5) {
        monster_file_path = "image/SpaceThreat4.png";
        // bullet_file_path = "image/BulletThreat5.png";
    }
    else if(m->type == 6) {
        monster_file_path = "image/SpaceThreat3.png";
        // bullet_file_path = "image/BulletThreat.png";
    }
    SDL_Surface* monster_surface = IMG_Load(monster_file_path); 
    // SDL_Surface* bullet_monster_surface = IMG_Load(bullet_file_path);
    if (monster_surface != NULL)
    {
        m->texture = SDL_CreateTextureFromSurface(renderer, monster_surface);
        
    }
    SDL_FreeSurface(monster_surface);
    // if (bullet_monster_surface != NULL)
    // {
    //     b_m->texture = SDL_CreateTextureFromSurface(renderer, bullet_monster_surface);
        
    // }
    // SDL_FreeSurface(bullet_monster_surface);
}
void drawMonster(monster *m)
{
    
    SDL_Rect rectMonster = {
        m->x_pos,
        m->y_pos,
        m->Width,
        m->height
    };
    SDL_RenderCopy(renderer, m->texture, NULL, &rectMonster);
}
void drawBulletMonster(bullet_monster *b_m)
{
    SDL_Rect rect = {
        b_m->x,b_m->y,b_m->w,b_m->h
    };
    SDL_RenderCopy(renderer,b_m->texture,NULL, &rect);
}

// bool canSpawnBullets(monster *m)
// {
//     Uint8 CurrentTime = SDL_GetTicks();
//     int LastTime = 0;
//     bool check_can_spawn=0; 
//     int delay_shoot_time = 300;
//     if(m->type == 1 || m->type == 2 || m->type == 3 || m->type == 5 || m->type == 6 || m->type == 7)
//     {
//         if(CurrentTime>LastTime+delay_shoot_time && m->y_pos >=500)
//         {
//             LastTime=CurrentTime;
//             check_can_spawn=1;
//         }
//     }
//     else if(m->type == 4)
//     {
//         if(CurrentTime>LastTime+400)
//         {
//             LastTime=CurrentTime;
//             check_can_spawn=1;
//         }
//     }
//     return check_can_spawn;
// }
// void makeBullet(monster *m)
// {
//     if(m->type == 1)
//     {
//         spawn_bullets_around_enemy(10,m,b_m);
//     }
//     if(m->type == 2)
//     {
        
//     }
//     if(m->type == 3)
//     {
        
//     }
//     if(m->type == 4)
//     {
        
//     }
//     if(m->type == 5)
//     {
        
//     }
//     if(m->type == 6)
//     {
        
//     }
// }
// void spawn_bullets_around_enemy(int num_bullets,monster *m,bullet_monster *b_m) {

//     float angle_between_bullets = 2 * PI / num_bullets; // Góc giữa các viên đạn
//     for (int i = 0; i < num_bullets; i++) {
//         // Tính toán tọa độ của viên đạn thứ i trên đường tròn
//         b_m->x = m->x_pos + b_m->radius  * cos(i * angle_between_bullets);
//         b_m->y = m->y_pos + b_m->radius  * sin(i * angle_between_bullets);
//         // Tạo ra viên đạn tại tọa độ này
//         drawBulletMonster();
//         b_m->radius+=0.4;
//         if(b_m->radius >= 500) b_m->radius = 20;
//     }
// }