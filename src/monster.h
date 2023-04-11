#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "bulletMonster.h"
#include <math.h>

short wave = 0; // đợt quái 
short angleMove = 0;
struct monster
{
    int x_pos;
    int y_pos;
    int y_limit; // giới hạn 
    int x_limit;
    short speed;
    int Width;
    int height;
    int type;
    short hp;
    unsigned short score;
    SDL_Texture *texture;
};
typedef struct monster monster;

void initMonster(monster *m);
void drawMonster(monster *m);
void moveMonster(monster *m);
void makeBullet(monster *m); // tạo đạn
void monsterDie(monster *m); // hàm xử lí bắn đạn tỏa ra khi quái vật chết

//==================================================

void initMonster(monster *m)
{
    m->x_pos = 600;
    m->y_pos = 100;
    m->Width = 64;
    m->height = 64;
    m->y_limit = 0;
    m->x_limit = 0;
    m->speed = 0;
    m->hp = 0;
    m->type = 0;
    m->texture = NULL;
}

void loadMonster(monster *m)
{
    IMG_Init(IMG_INIT_PNG);

    const char* monster_file_path;


    if (m->type == 1) {
        monster_file_path = "image/SpaceThreat1.png";

    } else if(m->type == 2 || m->type == 7) {
        monster_file_path = "image/SpaceThreat6.png";

    }
    else if(m->type == 3) {
        monster_file_path = "image/SpaceThreat2.png";

    }
    else if(m->type == 4) {
        monster_file_path = "image/SpaceThreat5.png";

    }
    else if(m->type == 5) {
        monster_file_path = "image/SpaceThreat4.png";

    }
    else if(m->type == 6) {
        monster_file_path = "image/SpaceThreat3.png";

    }
    else if(m->type == 10)
    {
        monster_file_path = "image/SpaceBoss.png";
    }
    SDL_Surface* monster_surface = IMG_Load(monster_file_path); 
    if (monster_surface != NULL)
    {
        m->texture = SDL_CreateTextureFromSurface(renderer, monster_surface);
        
    }
    SDL_FreeSurface(monster_surface);

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
void moveMonster(monster *m)
{
    if(m->type == 1 || m->type == 5 || m->type == 6)
    {
        if(m->y_pos >= m->y_limit)
        {
            m->y_pos = m->y_limit;
        }
        m->y_pos += m->speed;
    }else if(m->type == 2)
    {
        if(m->x_pos >= m->x_limit)
        {
            m->x_pos = m->x_limit;
        }
        m->x_pos += m->speed;
    }else if(m->type == 7)
    {
        if(m->x_pos <= displayMode.w -m->x_limit+50)
        {
            m->x_pos = displayMode.w -m->x_limit+50;
        }
        m->x_pos -= m->speed;
    }else if(m->type == 4 || m->type == 3)
    {
        if(m->y_pos >= m->y_limit)
        {
            m->y_pos = m->y_limit;
            if(m->x_pos >= displayMode.w-m->Width-150)  
            {
                angleMove = 180;
            }
            else if(m->x_pos <= 150) 
            {
                angleMove = 0;
            }
            m->x_pos += m->speed * cos(angleMove*M_PI/180);
        }
        m->y_pos+= m->speed;
    }
    else if(m->type == 10) // boss 
    {
        if(m->y_pos >= m->y_limit) 
        {
            m->y_pos = m->y_limit; 
            if(m->x_pos >= displayMode.w-m->Width-150)  
            {
                angleMove = 180;
            }
            else if(m->x_pos <= 150) 
            {
                angleMove = 0;
            }
            m->x_pos += m->speed * cos(angleMove*M_PI/180);
        }
        m->y_pos+=m->speed;
    }
}

void makeBullet(monster *m)
{
    if(m->type == 1)
    {
        bullet_monster *b = NULL;
        // tận dụng lại bộ nhớ
        for(int j = 0; j < MAX_BULLET_MONSTER; j++)
        {
            if(listBulletMonster[j]->active == false)
            {
                b = listBulletMonster[j];
                break;
            }
        }
        initBulletMonster(b);
        loadBulletMonster(b,m->type);
        b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
        b->y = m->y_pos + m->height; // yMonster + hMonster
        b->w = 15;
        b->h = 15;
        b->speed = 5;
        b->active = true;
        
        SDL_GetMouseState(&mouseX,&mouseY);
        s->X = mouseX;
        s->Y = mouseY;
        b->angle = atan2(s->Y - b->y, s->X - b->x); // tính góc giữa tàu và đạn
    }
    else if(m->type == 2 && m->x_pos >= m->x_limit) // đây là khi quái đạt vị trí giới hạn (không còn di chuyển nữa)
    {
        for(int i = 1; i <= 3; i+=2) // chỉ lấy i = 1 và 3 để tính góc
        {
            bullet_monster *b = NULL;
            // tận dụng lại bộ nhớ
            for(int j = 0; j < MAX_BULLET_MONSTER; j++)
            {
                if(listBulletMonster[j]->active == false)
                {
                    b = listBulletMonster[j];
                    break;
                }
            }
            initBulletMonster(b);
            loadBulletMonster(b,m->type);
            b->x = m->x_pos + m->Width/2; 
            b->y = m->y_pos + m->height/2; 
            b->w = 15;
            b->h = 15;
            b->speed = 2;
            b->active = true;
            b->angle = (i*120); //nhân 120 để bè ra
        }
        
        
    }
    // loại 7 giống loại 2, nó đối xứng
    else if(m->type == 7 && m->x_pos <= displayMode.w -m->x_limit+50)
    {
        for(int i = 1; i <= 3; i+=2)
        {
            bullet_monster *b = NULL;
            // tận dụng lại bộ nhớ
            for(int j = 0; j < MAX_BULLET_MONSTER; j++)
            {
                if(listBulletMonster[j]->active == false)
                {
                    b = listBulletMonster[j];
                    break;
                }
            }
            initBulletMonster(b);
            loadBulletMonster(b,m->type);
            b->x = m->x_pos + m->Width/2; 
            b->y = m->y_pos + m->height/2; 
            b->w = 15;
            b->h = 15;
            b->speed = 2;
            b->active = true;
            b->angle = (i*120); 
        }
    }
    else if(m->type == 3)
    {
        bullet_monster *b = NULL;
        // tận dụng lại bộ nhớ
        for(int j = 0; j < MAX_BULLET_MONSTER; j++)
        {
            if(listBulletMonster[j]->active == false)
            {
                b = listBulletMonster[j];
                break;
            }
        }
        initBulletMonster(b);
        loadBulletMonster(b,m->type);
        b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
        b->y = m->y_pos + m->height; // yMonster + hMonster
        b->w = 15;
        b->h = 15;
        b->speed = 10;
        b->active = true;       
    }
    else if(m->type == 4)
    {
        bullet_monster *b = NULL;
        // tận dụng lại bộ nhớ
        for(int j = 0; j < MAX_BULLET_MONSTER; j++)
        {
            if(listBulletMonster[j]->active == false)
            {
                b = listBulletMonster[j];
                break;
            }
        }
        initBulletMonster(b);
        loadBulletMonster(b,m->type);
        b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
        b->y = m->y_pos + m->height; // yMonster + hMonster
        b->w = 15;
        b->h = 15;
        b->speed = 13;
        b->active = true;
    }
    else if(m->type == 6)
    {
        bullet_monster *b = NULL;
        // tận dụng lại bộ nhớ
        for(int j = 0; j < MAX_BULLET_MONSTER; j++)
        {
            if(listBulletMonster[j]->active == false)
            {
                b = listBulletMonster[j];
                break;
            }
        }
        initBulletMonster(b);
        loadBulletMonster(b,m->type);
        b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
        b->y = m->y_pos + m->height; // yMonster + hMonster
        b->w = 15;
        b->h = 15;
        b->speed = 12;
        b->active = true;
        
        SDL_GetMouseState(&mouseX,&mouseY);
        s->X = mouseX;
        s->Y = mouseY;
        b->angle = atan2(s->Y - b->y, s->X - b->x);
    }
    else if(m->type == 5)
    {
        for(int i = 1; i <= 5; i ++)
        {
            bullet_monster *b = NULL;
            // tận dụng lại bộ nhớ
            for(int j = 0; j < MAX_BULLET_MONSTER; j++)
            {
                if(listBulletMonster[j]->active == false)
                {
                    b = listBulletMonster[j];
                    break;
                }
            }
            initBulletMonster(b);
            loadBulletMonster(b,m->type);
            b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
            b->y = m->y_pos + m->height; // yMonster + hMonster
            b->w = 15;
            b->h = 15;
            b->speed = i*2;
            b->active = true;
            srand(time(0));
            b->angle = rand() % 360 + 0;
        }
    }
//==========================================================================================================
    else if(m->type == 10) //boss sẽ có các loại đnạ của quái trước
    {
        for(int i = 1; i <= 7; i++)
        {
            if(i == 1)
            {
                bullet_monster *b = NULL;
                // tận dụng lại bộ nhớ
                for(int j = 0; j < MAX_BULLET_MONSTER; j++)
                {
                    if(listBulletMonster[j]->active == false)
                    {
                        b = listBulletMonster[j];
                        break;
                    }
                }
                initBulletMonster(b);
                loadBulletMonster(b,i);
                
                b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
                b->y = m->y_pos + m->height; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 5;
                b->active = true;
                printf("cc %d\n",i);
                SDL_GetMouseState(&mouseX,&mouseY);
                s->X = mouseX;
                s->Y = mouseY;
                b->angle = atan2(s->Y - b->y, s->X - b->x); // tính góc giữa tàu và đạn
            }
            if(i == 2 || i == 7) 
            {

                for(int k = 1; k <= 3; k+=2) // chỉ lấy i = 1 và 3 để tính góc
                {
                    bullet_monster *b = NULL;
                    // tận dụng lại bộ nhớ
                    for(int j = 0; j < MAX_BULLET_MONSTER; j++)
                    {
                        if(listBulletMonster[j]->active == false)
                        {
                            b = listBulletMonster[j];
                            break;
                        }
                    }
                    initBulletMonster(b);
                    loadBulletMonster(b,i);
                    b->x = m->x_pos + m->Width/2; 
                    b->y = m->y_pos + m->height/2; 
                    b->w = 15;
                    b->h = 15;
                    b->speed = 6;
                    b->active = true;
                    b->angle = (k*120); //nhân 120 để bè ra
                }      
            }
            if(i == 3)
            {
                bullet_monster *b = NULL;
                // tận dụng lại bộ nhớ
                for(int j = 0; j < MAX_BULLET_MONSTER; j++)
                {
                    if(listBulletMonster[j]->active == false)
                    {
                        b = listBulletMonster[j];
                        break;
                    }
                }
                printf("cc %d\n",i);
                initBulletMonster(b);
                loadBulletMonster(b,i);
                b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
                b->y = m->y_pos + m->height; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 10;
                b->active = true;       
            }
            if(i == 4)
            {
                bullet_monster *b = NULL;
                // tận dụng lại bộ nhớ
                for(int j = 0; j < MAX_BULLET_MONSTER; j++)
                {
                    if(listBulletMonster[j]->active == false)
                    {
                        b = listBulletMonster[j];
                        break;
                    }
                }
                printf("cc %d\n",i);
                initBulletMonster(b);
                loadBulletMonster(b,i);
                b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
                b->y = m->y_pos + m->height; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 13;
                b->active = true;
            }
            if(i == 6)
            {
                bullet_monster *b = NULL;
                // tận dụng lại bộ nhớ
                for(int j = 0; j < MAX_BULLET_MONSTER; j++)
                {
                    if(listBulletMonster[j]->active == false)
                    {
                        b = listBulletMonster[j];
                        break;
                    }
                }
                printf("cc %d\n",i);
                initBulletMonster(b);
                loadBulletMonster(b,i);
                b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
                b->y = m->y_pos + m->height; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 5;
                b->active = true;
                
                SDL_GetMouseState(&mouseX,&mouseY);
                s->X = mouseX;
                s->Y = mouseY;
                b->angle = atan2(s->Y - b->y, s->X - b->x);
            }
            if( i == 5)
            {
                for(int k = 1; k <= 5; k ++)
                {
                    bullet_monster *b = NULL;
                    // tận dụng lại bộ nhớ
                    for(int j = 0; j < MAX_BULLET_MONSTER; j++)
                    {
                        if(listBulletMonster[j]->active == false)
                        {
                            b = listBulletMonster[j];
                            break;
                        }
                    }
                    printf("cc %d\n",i);
                    initBulletMonster(b);
                    loadBulletMonster(b,i);
                    b->x = m->x_pos + m->Width/2; // xMonster + wMonster/2
                    b->y = m->y_pos + m->height; // yMonster + hMonster
                    b->w = 15;
                    b->h = 15;
                    b->speed = k*2;
                    b->active = true;
                    srand(time(0));
                    b->angle = rand() % 360 + 0;
                }
            }
        }
        
    }
}
void monsterDie(monster *m)
{
    for(int i = 0; i < 12; i++)
    {
        bullet_monster *b = NULL;
        // tận dụng lại bộ nhớ
        for(int j = 0; j < MAX_BULLET_MONSTER; j++)
        {
            if(listBulletMonster[j]->active == false)
            {
                b = listBulletMonster[j];
                break;
            }
        }
        initBulletMonster(b);
        loadBulletMonster(b,m->type);
        b->x = m->x_pos + m->Width/2;
        b->y = m->y_pos + m->height/2;

        b->w = 15;
        b->h = 15;
        b->angle = (0+i*30);
        b->speed = 4;
        b->active = true;
    }
}