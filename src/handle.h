#pragma once
#include "game.h"
#include "ship.h"
#include "bullet.h"
// #include "list_bullet.h"
#include "global.h"
#include "SDL2/SDL_thread.h"

void gameLoop();
// bool allBulletsOffScreen(list* l);
//================================

void gameLoop()
{
    
    int i = -1; // biến đếm biểu thị cho viên đạn thứ i trong danh sách đạn
    while(true){
        SDL_Event event;
        SDL_RenderClear(renderer);
        drawBackGround();
        drawShip();
        
        while(SDL_PollEvent(&event)){
            
            if(event.type == SDL_QUIT){
                exit(0);
            }
            // bắt sự kiện di chuyển
            if(event.type == SDL_MOUSEMOTION){
                moveShip();
                // drawShip();
            }

            //bắt sự kiện bắn đạn
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                i++;
                addNewBulletToList();
   
                SDL_Thread *threadBullet = SDL_CreateThread(moveBullet,"move",(void*)i);

            }
            if(event.key.keysym.sym == SDLK_k)
                exit(0);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);  
    } 
}

