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
        b->w = 20;
        b->h = 24;
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
            b->w = 19;
            b->h = 19;
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
            b->w = 19;
            b->h = 19;
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
        b->w = 20;
        b->h = 24;
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
        b->w = 30;
        b->h = 30;
        b->speed = 8;
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
        b->w = 20;
        b->h = 24;
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
            b->w = 20;
            b->h = 20;
            b->speed = i*2;
            b->active = true;
            srand(time(0));
            b->angle = rand() % 360 + 0;
        }
    }
//==========================================================================================================
/*
    else if(type==6.1)
    {
        if(die>=200 && die<300)
        {
            x_speed=1;
            if(!changespawn)
            {
                delay_shoot_time=400;
                for(int j=0;j<24;j++)
                {
                    for(int i=0;i<4;i++)
                    {
                        Bullet*p_bullet=new Bullet();
                        p_bullet->set_is_move(true);
                        p_bullet->LoadTexture("img//BulletThreat5.png",screen);
                        p_bullet->set_angle(15*j);
                        p_bullet->set_x_speed(2);
                        p_bullet->set_y_speed(2);
                        if(i%2==0)
                        {
                            p_bullet->set_pos(x_pos+width_frame/2-(p_bullet->GetRect().w)/2+10*(i-1),y_pos+height_frame/2);
                        }
                        else
                        {
                            p_bullet->set_pos(x_pos+width_frame/2-(p_bullet->GetRect().w)/2,y_pos+height_frame/2+10*(i-2));
                        }
                        bullet.push_back(p_bullet);
                    }
                }
                changespawn=1;
            }
            else
            {
                delay_shoot_time=500;
                for(int j=0;j<36;j++)
                {
                    Bullet*p_bullet=new Bullet();
                    p_bullet->set_is_move(true);
                    p_bullet->LoadTexture("img//BulletThreat4.png",screen);
                    p_bullet->set_angle(10*j);
                    p_bullet->set_x_speed(2);
                    p_bullet->set_y_speed(2);
                    p_bullet->set_pos(x_pos+width_frame/2-(p_bullet->GetRect().w)/2,y_pos+height_frame/2);
                    bullet.push_back(p_bullet);
                }
                changespawn=0;
            }
        }
        else if(die>=300 && die<400)
        {
            x_pos=SCREEN_WIDTH/2-width_frame/2;
            delay_shoot_time=150;
            x_speed=0;
            for(int i=0;i<12;i++)
            {
                Bullet*p_bullet1=new Bullet();
                p_bullet1->LoadTexture("img//BulletThreat5.png",screen);
                p_bullet1->set_is_move(true);
                p_bullet1->set_angle(angle+30*i);
                rotate_angle();
                if(angle>180 || angle<0)
                {
                    reverse_direction=1;
                    delay_shoot_time=1000;
                }
                p_bullet1->set_x_speed(2);
                p_bullet1->set_y_speed(2);
                p_bullet1->set_pos(x_pos+width_frame/2-(p_bullet1->GetRect().w)/2,y_pos+height_frame);
                bullet.push_back(p_bullet1);
            }
            for(int i=0;i<4;i++)
            {
                Bullet*p_bullet=new Bullet();
                if(i%2==0)
                {
                    p_bullet->LoadTexture("img//BulletThreat.png",screen);
                }
                else
                {
                    p_bullet->LoadTexture("img//BulletThreat2.png",screen);
                }
                p_bullet->set_is_move(true);
                p_bullet->set_random_angle2();
                p_bullet->set_x_speed(2);
                p_bullet->set_y_speed(2);
                p_bullet->set_pos(x_pos+width_frame/2-(p_bullet->GetRect().w)/2,y_pos+height_frame+20*i);
                bullet.push_back(p_bullet);
            }
        }
        else if(die>=100 && die <200)
        {
            x_speed=1;
            delay_shoot_time=150;
            for(int i=0;i<6;i++)
            {
                Bullet*p_bullet1=new Bullet();
                p_bullet1->LoadTexture("img//BulletThreat5.png",screen);
                p_bullet1->set_is_move(true);
                p_bullet1->set_type(2);
                p_bullet1->set_pos(100+100*i,0);
                p_bullet1->set_starting_point(120+120*i);
                bullet.push_back(p_bullet1);
            }
            for(int i=0;i<5;i++)
            {
                Bullet*p_bullet=new Bullet();
                p_bullet->LoadTexture("img//BulletThreat4.png",screen);
                p_bullet->set_is_move(true);
                p_bullet->set_type(1);
                p_bullet->set_angle(45);
                if(i==0)
                {
                    p_bullet->set_pos(200,0);
                }
                else
                {
                    p_bullet->set_pos(0,0+200*(i-1));
                }
                p_bullet->set_x_speed(2);
                p_bullet->set_y_speed(2);
                bullet.push_back(p_bullet);
            }
            for(int i=0;i<5;i++)
            {
                Bullet*p_bullet=new Bullet();
                p_bullet->LoadTexture("img//BulletThreat4.png",screen);
                p_bullet->set_is_move(true);
                p_bullet->set_type(1);
                p_bullet->set_angle(135);
                if(i==0)
                {
                    p_bullet->set_pos(SCREEN_WIDTH-200,0);
                }
                else
                {
                    p_bullet->set_pos(SCREEN_WIDTH,0+200*(i-1));
                }
                p_bullet->set_x_speed(2);
                p_bullet->set_y_speed(2);
                bullet.push_back(p_bullet);
            }
        }
        else if(die<100)
        {
            delay_shoot_time=500;
            x_speed=1;
            for(int i=0;i<24;i++)
            {
                Bullet*p_bullet=new Bullet();
                p_bullet->LoadTexture("img//BulletThreat6.png",screen);
                p_bullet->set_is_move(true);
                p_bullet->set_angle(0+15*i);
                p_bullet->set_x_speed(1);
                p_bullet->set_y_speed(2);
                p_bullet->set_pos(x_pos+width_frame/2-(p_bullet->GetRect().w)/2,y_pos+height_frame/2);
                bullet.push_back(p_bullet);
            }
            for(int i=0;i<24;i++)
            {
                Bullet*p_bullet=new Bullet();
                p_bullet->LoadTexture("img//BulletThreat2.png",screen);
                p_bullet->set_is_move(true);
                p_bullet->set_angle(0+15*i);
                p_bullet->set_x_speed(2);
                p_bullet->set_y_speed(1);
                p_bullet->set_pos(x_pos+width_frame/2-(p_bullet->GetRect().w)/2,y_pos+height_frame/2);
                bullet.push_back(p_bullet);
            }
        }
    }
*/
    else if(m->type == 10) //boss sẽ có các loại đnạ của quái trước
    {
        
        if(m->hp >= 400)
        {
            // bắn hình vuông
            for(int i=0;i<30;i++)
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
                b->angle = (0+15*i);
                b->speed = 4;
                b->active = true;
            }
            // bắn hình vuông
            for(int i=0;i<30;i++)
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
                b->speed = 4;
                b->angle = (0+15*i);
                b->active = true;
            }
            for(int i = 0; i < 1; i++)
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
                loadBulletMonster(b,1);
                b->x = m->x_pos + m->Width/2 + i*5; // xMonster + wMonster/2
                b->y = m->y_pos + m->height; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 7;
                SDL_GetMouseState(&mouseX,&mouseY);
                s->X = mouseX;
                s->Y = mouseY;
                b->angle = atan2(s->Y - b->y, s->X - b->x); // tính góc giữa tàu và đạn
                b->active = true;
            }
        }
        else if(m->hp >= 300)
        {
            // bắn hình vuông
            for(int i=0;i<30;i++)
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
                b->angle = (0+15*i);
                b->speed = 4;
                b->active = true;
            }
            // bắn hình vuông
            for(int i=0;i<30;i++)
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
                b->speed = 4;
                b->angle = (0+15*i);
                b->active = true;
            }



            // 3 for dưới đây bắn hình sin từ trên xuống
            for(int i=0;i<=10;i++)
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
                loadBulletMonster(b,3);
                b->x = 0+i*50 + 10; // xMonster + wMonster/2
                b->y = 0; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 4;
                b->angle = (0+30*i);
                b->active = true;
            }
            for(int i=0;i<=10;i++)
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
                loadBulletMonster(b,3);
                b->x = 550 + i*50 ; // xMonster + wMonster/2
                b->y = 0; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 4;
                b->angle = (0+40*i);
                b->active = true;
            }
            for(int i=0;i<=10;i++)
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
                loadBulletMonster(b,3);
                b->x = 1100 +i*50 - 10; // xMonster + wMonster/2
                b->y = 0; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 4;
                b->angle = (0+50*i);
                b->active = true;
            }
        }
        else if(m->hp > 100)
        {
            // bắn hình vuông
            for(int i = 0; i <= 50; i++)
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
                b->y = m->y_pos + m->height;// yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 3;
                b->angle = (0+7*i);
                b->active = true;
            }  
            // bắn đạn dí 
            for(int i = 0; i <= 10; i++)
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
                loadBulletMonster(b,1);
                b->x = m->x_pos + m->Width/2 + i*5; // xMonster + wMonster/2
                b->y = m->y_pos + m->height; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 4;
                SDL_GetMouseState(&mouseX,&mouseY);
                s->X = mouseX;
                s->Y = mouseY;
                b->angle = atan2(s->Y - b->y, s->X - b->x); // tính góc giữa tàu và đạn
                b->active = true;
            }
        }else{
            // bắn đạn dí
            for(int i = 0; i <= 2; i++)
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
                b->x = m->x_pos + m->Width/2 + i*50; // xMonster + wMonster/2
                b->y = m->y_pos + m->height; // yMonster + hMonster
                b->w = 15;
                b->h = 15;
                b->speed = 6;
                SDL_GetMouseState(&mouseX,&mouseY);
                s->X = mouseX;
                s->Y = mouseY;
                b->angle = atan2(s->Y - b->y, s->X - b->x); // tính góc giữa tàu và đạn
                b->active = true;
            }
            // bắn hình vuông
            for(int i=0;i<30;i++)
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
                b->angle = (0+15*i);
                b->speed = 4;
                b->active = true;
            }
            // bắn hình vuông
            for(int i=0;i<30;i++)
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
                b->speed = 4;
                b->angle = (0+15*i);
                b->active = true;
            }
        }
    }
}
void monsterDie(monster *m)
{
    if(m->type != 4 && m->type != 10)
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
    
}