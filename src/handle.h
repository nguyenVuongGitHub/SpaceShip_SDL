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
void collision(monsterList *l); // kiểm tra tất cả các trường hợp va chạm
//================================

void gameLoop()
{
    // Khai báo một biến đếm thời gian cho bắn đạn tiếp theo
    Uint32 last_shot_time = 0;
    int cur_ship = 0; // frame hình hiện tại
    int numOfBullet= 0; // biến đếm biểu thị cho viên đạn thứ i trong danh sách đạn
    bool holdMouse = false; // kiểm tra giữ chuột
    initBullets(); // cấp phát bộ nhớ cho con trỏ
    SDL_ShowCursor(SDL_DISABLE); // ẩn con trỏ chuột
    while(true){
        SDL_Event event;
        SDL_RenderClear(renderer);

        //nhạc nền game
        Mix_HaltChannel(1);  //dừng nhạc ở kênh số 1 (menu)
        if(wave % 10 == 0 && wave != 0){
            if(!Mix_Playing(3)){  //kiểm tra xem kênh số 3 có được phát chưa, nếu chưa thì ! sẽ trả về true
                Mix_PlayChannel(3, Boss, -1); //phát kênh số 3 (nhạc boss)
            }
            Mix_HaltChannel(2); //dừng kênh số 2 (nhạc nền game)
        }
        else{
            if(!Mix_Playing(2)){ //kiểm tra xem kênh số 2 có được phát chưa, nếu chưa thì ! sẽ trả về true
                Mix_PlayChannel(2, BGM, -1); //phát kênh số 2 (nhạc nền game)
            }
            Mix_HaltChannel(3); //dừng kênh số 3 (nhạc nền boss)
        }
        
        while(SDL_PollEvent(&event)){
            
            // bắt sự kiện di chuyển
            if(event.type == SDL_MOUSEMOTION) moveShip();
            
            //bắt sự kiện giữ chuột
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LMASK)
            {
                holdMouse = true;
            }
            if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LMASK)
            {
                holdMouse = false;
            }
            ///esc để tạm dừng
            if(event.key.keysym.sym == SDLK_ESCAPE) handlePause();
            
        }

        moveBackground();
        drawShip(cur_ship);
        

        if(holdMouse)
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

        // xử lí di chuyển đạn
        for(int i = 0; i < MAX_BULLET; i++)
        {
            if(bullets[i] != NULL && bullets[i]->active)
            {
                drawBullet(bullets[i]);
                moveBullet(bullets[i]);
            }
        }
        
        // tạo ra quái nếu danh sách rỗng
        GenerateMonster(lm);
        
        // xử lí va chạm
        collision(lm);

        // vẽ quái vật trong danh sách.
        for(int i = 0; i < lm->size; i++)
        {
            node *n = getNode(lm,i);
            moveMonster(&(n->data));
            drawMonster(&(n->data));
        }
        // tăng khung hình
        cur_ship++;

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
                    freeBullets(); // giải phóng đạn 
                    freeList(lm); // giải phóng danh sách quái vật
                    lm = (monsterList*)malloc(sizeof(monsterList)); // cấp phát nếu bấm vào chơi game tiếp
                    initMonsterList(lm);
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
                    Mix_Pause(-1);  // dừng phát nhạc tạm thời, -1 tức là tắt tất cả kênh âm thanh
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
                    Mix_Resume(-1);  // Bật lại nhạc đã tạm dừng trước đó, -1 tức là bật tất cả các kênh âm thanh
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

void collision(monsterList *l)
{

    // kiểm tra đạn tàu va chạm quái
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
            
            for(node *k = l->head; k != NULL; k = k->next)
            {
                SDL_Rect rectMonster = {
                        k->data.x_pos,
                        k->data.y_pos,
                        k->data.Width,
                        k->data.height
                };
                if(checkCollision(rectBullet,rectMonster))
                {
                    bullets[i]->active = false;
                    k->data.hp --;
                    if(k->data.hp == 0)
                    {   
                        Mix_PlayChannel(4, hit, 0);  // nhạc khi quái trúng đạn
                        node *mr = k;
                        removeNode(l,mr);
                    } 
                    
                }
            }
        }
    }

    // kiểm tra tàu va chạm quái


    // kiểm tra đạn quái va chạm tàu
    
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