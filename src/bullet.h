#pragma once
#include "global.h"
#include "math.h"
#include "monster.h"
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
void moveBullet(bullet *b);
void drawBullet(bullet *b);
void addNewBulletToList(int numOfBullet);
void freeBulletY_posLessZero(bullet *bullets[MAX_BULLET]);
void freeBullets();
//=====================================================

void initBullet(bullet *b){
    b->x_pos = s->X-14;
    b->y_pos = s->Y-50;
    b->width= 30;
    b->height = 30;
    b->texture = NULL;
    b->speed = 0;
    // b->active = false;
    loadBullet(b);
}

void loadBullet(bullet *b)
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image/bulletShip.png");
    if(surface != NULL){
        // Tạo texture từ surface
        b->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // giải phóng surface khi không dùng nữa.
        if(b->texture == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }
    }
    else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}

void moveBullet(bullet *b)
{
    b->y_pos -= b->speed; // di chuyển 
    if (b->y_pos <= 0){
        b->active = false;
    }
}

void addNewBulletToList(int numOfBullet)
{
    bullet *newBullet = NULL;

    // Tìm đối tượng viên đạn không active trong danh sách để tái sử dụng
    for (int i = 0; i < MAX_BULLET; i++) {
        if (bullets[i]->active == false){
            newBullet = bullets[i];
            break;
        }
    }

    // Nếu không có đối tượng nào để tái sử dụng, cấp phát đối tượng mới
    if (newBullet == NULL) {
        newBullet = (bullet*)malloc(sizeof(bullet));
        bullets[numOfBullet] = newBullet;
    }

    // Khởi tạo đối tượng viên đạn
    initBullet(newBullet);

    // Cập nhật trạng thái của viên đạn và tốc độ
    newBullet->active = true;
    newBullet->speed = 11;
}
void initBullets(){
    for(int i = 0; i < MAX_BULLET; i++){    
        bullets[i] = (bullet*)malloc(MAX_BULLET*sizeof(bullet));
    }
    for(int i = 0; i < MAX_BULLET; i++){
        bullets[i]->active = false;
    }
}
void freeBullets()
{
    for(int j = 0; j < MAX_BULLET; j++)
        free(bullets[j]);
}

void drawBullet(bullet *b)
{
    SDL_Rect r = {b->x_pos,b->y_pos,b->width,b->height};
    SDL_RenderCopy(renderer,b->texture,NULL,&r);
}
