#pragma once
#include <time.h>
#include "global.h"
#include "ship.h"
#include "bullet.h"
#include "game.h"
#include "monster.h"
void gameLoop();

//================================

void gameLoop()
{
    // Khai báo một biến đếm thời gian cho bắn đạn tiếp theo
    Uint32 last_shot_time = 0;
    int cur_ship = 0; // frame hình hiện tại
    int cur_background = 0;
    int countLoop = 0;
    int i = -1; // biến đếm biểu thị cho viên đạn thứ i trong danh sách đạn
    initBullets(); // cấp phát bộ nhớ cho con trỏ
    SDL_Thread *threadBullets[MAX_BULLET];
    SDL_ShowCursor(SDL_DISABLE); // ẩn con trỏ chuột
    while(true){
        SDL_Event event;
        SDL_RenderClear(renderer);
        drawBackGround(cur_background);
        drawShip(cur_ship);
        drawMonster();
        while(SDL_PollEvent(&event)){
            
            // bắt sự kiện di chuyển
            if(event.type == SDL_MOUSEMOTION){
                moveShip();
            }

            //bắt sự kiện bắn đạn bằng chuột trái 
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LMASK)
            {
                Uint32 current_time = SDL_GetTicks();
                Uint32 time_since_last_shot = current_time - last_shot_time;

                // Kiểm tra xem đã đủ thời gian để bắn đạn tiếp theo chưa
                if (time_since_last_shot >= 3) {
                    i++; // biến đếm biểu thị vị trí viên đạn trong danh sách
                    addNewBulletToList();
                    // luồng khác để xử lí đạn
                    threadBullets[i] = SDL_CreateThread(moveBullet,"move",(void*)i);  
                    
                    // Lưu lại thời gian bắn đạn
                    last_shot_time = current_time;
                }

            }

            //esc để thoát
            if(event.key.keysym.sym == SDLK_ESCAPE){
                for(int j = 0; j <= i; j++) {
                    SDL_WaitThread(threadBullets[j], NULL);
                }
                //giải phóng bộ nhớ cho mảng con trỏ
                for(int j = 0; j < MAX_BULLET; j++)
                {
                    free(bullets[j]);
                }
                i = -1; // reset biến i
                showMenu(); // về lại menu
            }
                

        }
        // tăng khung hình
        cur_ship++;
        countLoop++;
        //4 vòng lặp thì tăng background
        if(countLoop % 4 == 0)
            cur_background++;

        if(cur_background >= 8) cur_background = 0;
        if(cur_ship >= 8) cur_ship = 0;

        // freeBulletY_posLessZero(bullets);
        // hiển thị lên màn hình
        SDL_RenderPresent(renderer);
        SDL_Delay(10);  
    } 
}
