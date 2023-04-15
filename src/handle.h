#pragma once
#include <time.h>
#include <stdlib.h>
#include "global.h"
#include "ship.h"
#include "bullet.h"
#include "game.h"
#include "monster.h"
#include "monsterArray.h"
#include "text.h"


text textScore;
text textHeart;
text textCurentScore;
char curentScore[20];

short random = 100; // random_buff
bool buff_is_run = false;
int x_buff;
int y_buff;
bool buff_is_run2 = false;
int x_buff2;
int y_buff2;

void generateBuff2();
void generateBuff();
void gameLoop(); // vòng lặp chính
void handlePause2();
int checkText(text object1);
bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2); // kiểm tra va chạm giữa hai object
void collision(monsterList *l); // kiểm tra tất cả các trường hợp va chạm
//================================

void gameLoop()
{   
    initText(&textScore);
    setText("SCORE : ",&textScore);
    loadText(36,&textScore,pathFont,getColor(RED));
    setPosText(100,50,&textScore);
    
    initText(&textHeart);
    setText("HEART",&textHeart);
    loadText(36,&textHeart,pathFont,getColor(RED));
    setPosText(displayMode.w-200,50,&textHeart);

    initText(&textCurentScore);
    sprintf(curentScore,"%d",playerer.score);
    setText(curentScore,&textCurentScore);
    loadText(36,&textCurentScore,pathFont,getColor(WHITE));
    setPosText(300,50,&textCurentScore);

    // Khai báo một biến đếm thời gian cho bắn đạn tiếp theo
    Uint32 last_shot_time = 0;
    short countLoop = 0;
    short countBuff1 = 1; // tạo biến này để đếm thời gian tàu, coi như là thời gian bất tử và thời gian đc bảo vệ
    short countBuff2 = 1; // tạo biến này để đếm thời gian tàu, coi như là thời gian bất tử và thời gian đc bảo vệ
    short cur_ship = 0; // frame tàu hiện tại
    bool holdMouseLeft = false; // kiểm tra giữ chuột
    bool holdMouseRight = false;
    /**
     * cấp phát và khởi tạo các thống số cần thiết cho game
    */
    lm = (monsterList*)malloc(sizeof(monsterList));
    initMonsterList(lm);
    initListBulletMonster();
    initBullets(); 


    while(gameOver){
        SDL_Event event;
        SDL_RenderClear(renderer);
        
        //nhạc nền game
        Mix_HaltChannel(1);  //dừng nhạc ở kênh số 1 (menu)
        if(wave % 10 == 0 && wave != 0 && sound){
            if(!Mix_Playing(3)){  //kiểm tra xem kênh số 3 có được phát chưa, nếu chưa thì ! sẽ trả về true
                Mix_PlayChannel(3, Boss, -1); //phát kênh số 3 (nhạc boss)
            }
            Mix_HaltChannel(2); //dừng kênh số 2 (nhạc nền game)
            Mix_HaltChannel(7);
        }
        else{
            if(!Mix_Playing(2)){ //kiểm tra xem kênh số 2 có được phát chưa, nếu chưa thì ! sẽ trả về true
                Mix_PlayChannel(2, BGM, -1); //phát kênh số 2 (nhạc nền game)
            }
            Mix_HaltChannel(3); //dừng kênh số 3 (nhạc nền boss)
            Mix_HaltChannel(7);
        }
        
        while(SDL_PollEvent(&event)){
            
            // bắt sự kiện di chuyển
            if(event.type == SDL_MOUSEMOTION) moveShip();
            
            //bắt sự kiện giữ chuột
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LMASK)
            {
                holdMouseLeft = true;
            }
            if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LMASK)
            {
                holdMouseLeft = false;
            }
            ///esc để tạm dừng
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                int curX = mouseX;
                int curY = mouseY;
                handlePause2();
                SDL_WarpMouseInWindow(window,curX,curY);
                s->status = PROTECT;
            } 
            
        }
        
        moveBackground();
        drawShip(cur_ship);
        
        // kiểm tra bắn đạn
        if(holdMouseLeft)
        {
            Mix_PlayChannel(5, shot, 0);
            Uint32 current_time = SDL_GetTicks();  
            Uint32 time_since_last_shot = current_time - last_shot_time; 

            // Kiểm tra xem đã đủ thời gian để bắn đạn tiếp theo chưa
            if (time_since_last_shot >= 150) {
                
                addNewBulletToList();
                // Lưu lại thời gian bắn đạn
                last_shot_time = current_time;
            }
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
        
        // tạo ra buff
        generateBuff();
        generateBuff2();


        //quái tạo đạn
        for(node_M *k = lm->head; k != NULL; k= k->next)
        {
            // coundLoop để giới hạn thời gian quái sinh ra đạn
            if(k->data.hp > 0 && countLoop % 100 == 0)
            {
                makeBullet(&(k->data));
            }
            
        }
        //  vẽ đạn lên màn hình
        for(int i = 0; i < MAX_BULLET_MONSTER; i++)
        {
            if(listBulletMonster[i] != NULL && listBulletMonster[i]->active)
            {
                // printf("i = %d\n",i);
                drawBulletMonster(listBulletMonster[i]); 
                moveBulletMonster(listBulletMonster[i]);
            }
        }

        // xử lí va chạm
        collision(lm);

        // vẽ quái vật trong danh sách.
        for(int i = 0; i < lm->size; i++)
        {
            node_M *n = getNode(lm,i);
            moveMonster(&(n->data));
            drawMonster(&(n->data));
        }
        // tăng khung hình
        cur_ship++;
        if(cur_ship >= 8) cur_ship = 0;

        countLoop++;
        if(countLoop == 100) countLoop = 0;

        // kiểm tra nếu vòng lặp chạy đc 300 lần thì chuyển trạng thái
        if(countBuff1 % 300 == 0 && s->status == DIE)
        {
            s->status = LIVE;
            loadShip();
            countBuff1 = 1;
        }
        if(countBuff2 % 500 == 0 && s->status == PROTECT)
        {
            s->status = LIVE;
            loadShip();
            countBuff2 = 1;
        }
        // kiểm tra lúc bắt đầu chuyển trạng thái thì mới bắt đầu đếm vòng lặp
        if(s->status == DIE) countBuff1++;
        if(s->status == PROTECT) countBuff2++;
        /*
            nếu đang đc bảo vệ thì vẽ khiên, còn nếu không thì xóa độ trong suốt về 0
        */
        if(s->status == PROTECT)
        {
            drawShipPROTECT();
        }else{
            SDL_SetTextureAlphaMod(shield,0);
        }
        
        drawHeart();
        drawText(&textHeart);
        drawText(&textScore);
        drawText(&textCurentScore);
        // hiển thị lên màn hình
        SDL_RenderPresent(renderer);
        SDL_Delay(10); 
        
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
            
            for(node_M *k = l->head; k != NULL; k = k->next)
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
                        // xóa hết đạn di của quái vật 4
                        if(k->data.type == 4) 
                        {
                            for(int i = 0; i < MAX_BULLET_MONSTER; i++)
                            { 
                                if(listBulletMonster[i]->active = true)
                                {
                                    listBulletMonster[i]->active = false;
                                }
                            }
                        }
                        monsterDie(&(k->data));
                        playerer.score += k->data.score;
                        Mix_PlayChannel(4, hit, 0);  // nhạc khi quái trúng đạn
                        node_M *mr = k;
                        removeNode(l,mr); // xóa quái khỏi danh sách -> xóa khỏi màn hình
                        mr = NULL; 
                        sprintf(curentScore,"%d",playerer.score); // cập nhật lại điểm và chuyển thành kiểu char[]
                        setText(curentScore,&textCurentScore); // thay đổi giá trị của text
                        loadText(36,&textCurentScore,pathFont,getColor(WHITE));
                    } 
                    
                }
            }
        }
    }

    // kiểm tra tàu va chạm quái
    SDL_Rect r_ship = {s->X,s->Y,s->W,s->H};
    for(node_M *i = l->head; i != NULL; i = i->next)
    {
        SDL_Rect rectMonster = {
            i->data.x_pos,
            i->data.y_pos,
            i->data.Width,
            i->data.height
        };

        if(checkCollision(r_ship,rectMonster) && s->status == LIVE)
        {
            // không phải boss thì k xóa
            if(i->data.type != 10 && i->data.type != 4)
            {
                removeNode(lm,i);
            }
            
            Mix_PlayChannel(6, dead, 0);
            s->status = DIE;
            playerer.hp--;
            loadShip();
        }
    }

    // kiểm tra đạn quái va chạm tàu
    for(int i = 0; i < MAX_BULLET_MONSTER;i++)
    {
        if(listBulletMonster[i]->active == true)
        {
            SDL_Rect rectShip = {s->X,s->Y,s->W,s->H};
            SDL_Rect bulletMonster = {listBulletMonster[i]->x,listBulletMonster[i]->y-2,listBulletMonster[i]->w-2,listBulletMonster[i]->h-2};
            
            if(checkCollision(rectShip,bulletMonster) && s->status == LIVE)
            {
                Mix_PlayChannel(6, dead, 0);
                listBulletMonster[i]->active = false;
                s->status = DIE;
                loadShip();
                playerer.hp--;
            }
        }
    }

    // kiểm tra máu người chơi, nếu hp == 0 thì về lại menu 
    if(playerer.hp <= 0)
    {
        Mix_HaltChannel(1);
        Mix_HaltChannel(2);
        Mix_HaltChannel(3);
        if(!Mix_Playing(7)){
            Mix_PlayChannel(7, gameOverSong, -1);
        }
        // tạo node mới để thêm vào danh sách người chơi
        node_pr *nodepr = createNode(playerer);
        addNode(nodepr,lpr);
        showGameOver();
        
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
void generateBuff()
{
    srand(time(0));

    // nếu nó không chạy thì mới random mới
    if(!buff_is_run)
        random = rand()%20 - 0;
    
    if(random == 0) // nếu biến random từ 0 đến 20 random ra 0 thì sẽ tạo ra x và y 
    {
        x_buff = rand() % (displayMode.w - 10 + 1) + 10;
        y_buff = -30;
        buff_is_run = true; // đổi biến run thành true để bắt đầu di chuyển
    }
    if(buff_is_run == true) // di chuyển
    {
        SDL_Rect heart_rect = { x_buff, y_buff, 30, 30};
        SDL_RenderCopy(renderer, buff, NULL, &heart_rect);

        // Cap nhat vi tri cua trai tim
        y_buff += 3;
        SDL_Rect rectShip = {s->X,s->Y,s->W,s->H}; 

        //kiểm tra va chạm tàu với quái
        if(checkCollision(heart_rect,rectShip))
        {   
            Mix_PlayChannel(-1, eatHp, 0);

            // tức là hp người chơi mà >= 5 sẽ không tăng lên nữa
            if(playerer.hp < 5)
            {
                playerer.hp++;
            }
            y_buff = -80; // reset buff
            buff_is_run = false;
        }
        // Khoi tao lai trai tim neu het
        if (y_buff >= 1000) {
            
            buff_is_run = false;
        }
        random = 100;
    }
}
void generateBuff2()
{
    srand(time(0));

    // nếu nó không chạy thì mới random mới
    if(!buff_is_run2)
        random = rand()%20 - 0;
    
    if(random == 1 && s->status != PROTECT) // nếu biến random từ 0 đến 20 random ra 1 thì sẽ tạo ra x và y 
    {
        x_buff2 = rand() % (displayMode.w - 10 + 1) + 10;
        y_buff2 = -30;
        buff_is_run2 = true; // đổi biến run thành true để bắt đầu di chuyển
    }
    if(buff_is_run2 == true) // di chuyển
    {
        SDL_Rect shield = { x_buff2, y_buff2, 50, 50};
        SDL_RenderCopy(renderer, buff2, NULL, &shield);

        // Cap nhat vi tri cua trai tim
        y_buff2 += 3;
        SDL_Rect rectShip = {s->X,s->Y,s->W,s->H}; 

        //kiểm tra va chạm tàu với quái
        if(checkCollision(shield,rectShip))
        {
            s->status = PROTECT;
            Mix_PlayChannel(-1, eatHp, 0);
            loadShip();
            y_buff2 = -100; // reset buff
            buff_is_run2 = false;
        }
        // Khoi tao lai trai tim neu het
        if (y_buff2 >= 1000) {
            
            buff_is_run2 = false;
        }
        random = 100;
    }
}

void handlePause2()
{
    while(gameOver)
    {
        SDL_Event event;
        SDL_RenderClear(renderer);
        SDL_GetMouseState(&mouseX,&mouseY);

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEMOTION:
                    if(checkText(helpPause)){
                        loadText(50,&helpPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&helpPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }

                    if(checkText(continuePause)){
                        loadText(50,&continuePause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&continuePause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }

                    if(checkText(exitPause)){
                        loadText(50,&exitPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&exitPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }

                    if(checkText(soundOn)){
                        loadText(50,&soundOn,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&soundOn,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }

                    if(checkText(soundOff)){
                        loadText(50,&soundOff,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&soundOff,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    if(checkText(helpPause)){
                        bool check = true;
                        while(check)
                        {
                            SDL_RenderCopy(renderer,background_help,NULL,NULL);
                            SDL_RenderPresent(renderer);
                            while(SDL_PollEvent(&event))
                                if(event.key.keysym.sym == SDLK_ESCAPE) check = false;
                            SDL_Delay(10);
                        }
                    }
                    
                    if(checkText(continuePause)){
                        return;
                    }

                    if(checkText(exitPause)){
                        // tạo node mới để thêm vào danh sách người chơi
                        node_pr *nodepr = createNode(playerer);
                        addNode(nodepr,lpr);
                        playerer.hp = 3;
                        wave = 0;
                        playerer.score = 0;
                        gameOver = false;
                    }

                    if(checkText(soundOn) && sound){
                        sound = false;
                        Mix_Pause(-1);  // dừng phát nhạc tạm thời, -1 tức là tắt tất cả kênh âm thanh
                        // drawText(&soundOff);
                    }

                    else if(checkText(soundOff) && !sound){
                        sound = true;
                        Mix_Resume(-1);  // Bật lại nhạc đã tạm dừng trước đó, -1 tức là bật tất cả các kênh âm thanh
                    }                    
                break;
            }
        }
    
        moveBackground();
        drawMouse();


        drawText(&pauseGame);
        drawText(&helpPause);
        drawText(&continuePause);
        drawText(&exitPause);
        if(sound){
            drawText(&soundOn);
        }
        else drawText(&soundOff);
        
        SDL_Delay(10);
        SDL_RenderPresent(renderer);
    }
}

int checkText(text object1){
    if(mouseX >= object1.x && mouseX <= object1.x + object1.w
    && mouseY >= object1.y && mouseY <= object1.y + object1.h){
        return true;
    }
    return false;
}