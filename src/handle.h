#pragma once
#include "global.h"
#include "ship.h"
#include "bullet.h"
#include "game.h"

void gameLoop();

//================================

void gameLoop()
{
    int cur = 0; // frame hình hiện tại
    int i = -1; // biến đếm biểu thị cho viên đạn thứ i trong danh sách đạn
    
    while(true){
        SDL_Event event;
        SDL_RenderClear(renderer);
        drawBackGround();
        drawShip(cur);
        
        while(SDL_PollEvent(&event)){
            
            // bắt sự kiện di chuyển
            if(event.type == SDL_MOUSEMOTION){
                moveShip();
            }

            //bắt sự kiện bắn đạn bằng chuột trái 
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LMASK)
            {
                i++; // biến đếm biểu thị vị trí viên đạn trong danh sách
                addNewBulletToList();
                // luồng khác để xử lí đạn
                SDL_Thread *threadBullet = SDL_CreateThread(moveBullet,"move",(void*)i);  

            }
            
            //esc để thoát
            if(event.key.keysym.sym == SDLK_ESCAPE){
                showMenu();
            }
                

        }
        // tăng khung hình
        cur++;
        if(cur >= 8) cur = 0;

        SDL_RenderPresent(renderer);
        SDL_Delay(10);  
    } 
}
