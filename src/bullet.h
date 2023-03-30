#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "global.h"
#include "ship.h"
#include "math.h"

struct bullet{
    int x_pos;
    int y_pos;
    int width;
    int height;
    float speed;
    bool active; // trạng thái của đạn, true -> đang di chuyển
    SDL_Texture* texture;
};
typedef struct bullet bullet;

bullet *bullets[MAX_BULLET];

//=====================================================
void loadBullet(bullet *b);
void initBullet(bullet *b);
int moveBullet(void *data);
//=====================================================

void initBullet(bullet *b){
    b->x_pos = s->X-5;
    b->y_pos = s->Y-100;
    b->width= 15;
    b->height = 15;
    b->texture = NULL;
    b->speed = 0;
    // b->active = false;
    loadBullet(b);
}

void loadBullet(bullet *b)
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image/bullet.png");
    if(surface != NULL){
        // Tạo texture từ surface
        b->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // giải phóng surface khi không dùng nữa.
        if(b->texture == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }
        else{
            // Tạo rect để chứa ảnh
            SDL_Rect rect = {b->x_pos, b->y_pos, b->width b->height};

            // Render ảnh vào rect
            SDL_RenderCopy(renderer, b->texture, NULL, &rect);
        }
    }
    else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}

int moveBullet(void *data)
{
    SDL_LockMutex(mutex_bullet);
    int i = (int)data;

    //active = true -> đang di chuyển
    while(bullets[i]->active == true) {
        bullets[i]->y_pos -= bullets[i]->speed; // di chuyển 
        if (bullets[i]->y_pos < 0) {
            break;
        }

        printf("thread i = %d and Y-bullet = %d\n",i,bullets[i]->y_pos);

        //vẽ đạn lên render
        SDL_Rect rectBullet = {
            bullets[i]->x_pos,
            bullets[i]->y_pos,  
            bullets[i]->width
            bullets[i]->height
        };
        SDL_RenderCopy(renderer,bullets[i]->texture,NULL,&rectBullet);
        SDL_Delay(10);
    }
    SDL_UnlockMutex(mutex_bullet);
    return 0;
}

void addNewBulletToList()
{
    bullet *newBullet = (bullet*)malloc(sizeof(bullet));
    initBullet(newBullet);
    
    for (int i = 0; i < MAX_BULLET; i++) {
        if (bullets[i]->active == false) {
            bullets[i] = newBullet;
            bullets[i]->active = true;
            bullets[i]->speed = 5;
            break;
        }
    }
}
void initBullets(){
    for(int i = 0; i < MAX_BULLET; i++){    
        bullets[i] = (bullet*)malloc(MAX_BULLET*sizeof(bullet));
    }
    for(int i = 0; i < MAX_BULLET; i++){
        bullets[i]->active = false;
    }
}
