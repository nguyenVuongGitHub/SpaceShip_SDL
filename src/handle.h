#pragma once
#include <time.h>
#include "global.h"
#include "ship.h"
#include "bullet.h"
#include "game.h"
#include "monster.h"
#include "monsterArray.h"

void gameLoop(); // vòng lặp chính
void handlePause(); // biến i biểu thị viên đạn thứ i trong danh sách 
bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2); // kiểm tra va chạm giữa hai object
void collision(); // kiểm tra tất cả các trường hợp va chạm
//================================

void gameLoop()
{
    node *head = l->head;
    // Khai báo một biến đếm thời gian cho bắn đạn tiếp theo
    Uint32 last_shot_time = 0;
    int cur_ship = 0; // frame hình hiện tại
    int cur_background = 0;
    int countLoop = 0;
    int numOfBullet= 0; // biến đếm biểu thị cho viên đạn thứ i trong danh sách đạn
    initBullets(); // cấp phát bộ nhớ cho con trỏ
    SDL_ShowCursor(SDL_DISABLE); // ẩn con trỏ chuột
    while(true){
        SDL_Event event;
        SDL_RenderClear(renderer);
        
        while(SDL_PollEvent(&event)){
            
            // bắt sự kiện di chuyển
            if(event.type == SDL_MOUSEMOTION) moveShip();
            
            //bắt sự kiện bắn đạn bằng chuột trái 
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LMASK)
            {
                Uint32 current_time = SDL_GetTicks();
                Uint32 time_since_last_shot = current_time - last_shot_time;

                // Kiểm tra xem đã đủ thời gian để bắn đạn tiếp theo chưa
                if (time_since_last_shot >= 200) {
                    
                    addNewBulletToList(numOfBullet);
                    // Lưu lại thời gian bắn đạn
                    last_shot_time = current_time;
                }
                numOfBullet++; // biến đếm biểu thị số viên đạn trong danh sách
            }
            ///esc để tạm dừng
            if(event.key.keysym.sym == SDLK_ESCAPE) handlePause();
            
        }
        drawBackGround(cur_background);
        drawShip(cur_ship);

        // xử lí di chuyển đạn
        for(int i = 0; i < MAX_BULLET; i++)
        {
            if(bullets[i] != NULL && bullets[i]->active)
            {
                drawBullet(bullets[i]);
                moveBullet(bullets[i]);
            }
        }
        
        GenerateMonster(l);
        
        // collision();
        for(int i = 0; i < l->size; i++)
        {
            node *n = getNode(l,i);
            drawMonster(&(n->data));
            printf("x = %d, y= %d\n",n->data.x_pos,n->data.y_pos);
        }
        // tăng khung hình
        cur_ship++;
        countLoop++;
        //4 vòng lặp thì tăng background
        if(countLoop % 4 == 0)
            cur_background++;

        if(cur_background >= 8) cur_background = 0;
        if(cur_ship >= 8) cur_ship = 0;

        // hiển thị lên màn hình
        SDL_RenderPresent(renderer);
        SDL_Delay(10);  
    } 
}
void handlePause()
{
    int last_mouse = 0; // biến thể hiện chuột lần cuối đang ở đâu
    bool sound = true;
    SDL_RenderClear(renderer);
    while(true)
    {
        SDL_Event event;
        SDL_RenderClear(renderer);
        SDL_GetMouseState(&mouseX,&mouseY);

        while(SDL_PollEvent(&event))
        {
            
            // help khi có sound
            if(mouseX >= 660 && mouseX <= 885 && mouseY >= 360 && mouseY <= 385 && sound)
            {
                drawPause_11();
                last_mouse = 1;
            }
            // tiếp tục - khi có sound
            else if(mouseX >= 660 && mouseX <= 885 && mouseY >= 425 && mouseY <= 450 && sound)
            {
                drawPause_21();
                if(event.type == SDL_MOUSEBUTTONDOWN) return;
                last_mouse = 2;
            }
            // thoát - khi có sound
            else if(mouseX >= 660 && mouseX <= 885 && mouseY >= 490 && mouseY <= 515 && sound)
            {
                drawPause_31();
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    freeBullets();
                    showMenu(); // về lại menu
                }
                last_mouse = 3;
            }
            // tắt sound
            else if(mouseX >= 660 && mouseX <= 885 && mouseY >= 555 && mouseY <= 580 && sound)
            {
                drawPause_41();
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    sound = false;

                }
                // drawPause_40();
                last_mouse = 4;
            }
            //như tr
            else if(mouseX >= 660 && mouseX <= 885 && mouseY >= 360 && mouseY <= 385 && !sound)
            {
                drawPause_10();
                last_mouse = 5;
            }
            //như trên
            else if(mouseX >= 660 && mouseX <= 885 && mouseY >= 425 && mouseY <= 450 && !sound)
            {
                drawPause_20();
                if(event.type == SDL_MOUSEBUTTONDOWN) return;
                last_mouse = 6;
            }
            //như trên
            else if(mouseX >= 660 && mouseX <= 885 && mouseY >= 490 && mouseY <= 515 && !sound)
            {
                drawPause_30();
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    // //giải phóng bộ nhớ cho mảng con trỏ
                    freeBullets();
                    showMenu(); // về lại menu
                }
                last_mouse = 7;
            }
            // bật sound
            else if(mouseX >= 660 && mouseX <= 885 && mouseY >= 555 && mouseY <= 580 && !sound)
            {
                drawPause_40();
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    sound = true;
                }
                // drawPause_41();
                last_mouse = 8;
            }
        }

        // hiện ảnh ra màn hình khi con chuột thoát khỏi mục ngắm
        switch (last_mouse)
        {   
        case 0:
            if(sound)
                drawPause_01();
            else drawPause_00(); 
            break;
        case 1:
            drawPause_11();
            break;
        case 2:
            drawPause_21();
            break;
        case 3:
            drawPause_31();
            break;
        case 4:
            drawPause_41();
            break;
        case 5:
            drawPause_10();
            break;
        case 6:
            drawPause_20();
            break;
        case 7:
            drawPause_30();
            break;
        case 8:
            drawPause_40();
            break;
        }
        drawMouse();
        SDL_Delay(10);
        SDL_RenderPresent(renderer);
    }
}

void collision(monster *m)
{

    // kiểm tra danh sách linkedlist
    
    SDL_Rect rectMonster = {
            m->x_pos,
            m->y_pos,
            m->Width,
            m->height
    };

    for(int i =0; i < MAX_BULLET; i++)
    {
        if(bullets[i]->active)
        {
            SDL_Rect rectBullet = {
            bullets[i]->x_pos,
            bullets[i]->y_pos,
            bullets[i]->width,
            bullets[i]->height
            };
            if(checkCollision(rectBullet,rectMonster))
            {
                bullets[i]->active = false;
                m->hp --;
                if(m->hp == 0)
                {
                    m->x_pos = rand() % 1200;
                    m->y_pos = rand() % 800;
                } 
                
            }
        }
    }
    SDL_Rect rect_ship = {s->X,s->Y,s->W,s->H};

    if(checkCollision(rect_ship,rectMonster))
    {
        s->status = DIE;
        loadShip();
    }else {
        s->status = LIVE;
        loadShip();
    } 
}
bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    
    if(object1.x+object1.w>=object2.x && object2.x+object2.w>=object1.x
        && object1.y+object1.h>=object2.y && object2.y+object2.h>=object1.y)
    {
        return true;
    }
    return false;

}