#pragma once
#include "global.h"
#include "text.h"
#include "player.h"
// Khai báo biến toàn cục
text battleSky;
text play;
text help;
text textRank;
text exitMenu;
text pauseGame;
text helpPause;
text continuePause;
text exitPause;
text soundOn;
text soundOff;

short angleObj2 = 0;
short angleObj1 = 30;
// các tham số x y mặc định
short xObj1_1 = 123;
short xObj1_2 = 263;
short xObj1_3 = 800;
short xObj1_4 = 569;
short yObj1_1 = 150;
short yObj1_2 = 150;
short yObj1_3 = 175;
short yObj1_4 = 165;

short xShip = 888;
short yShip = 666;
short angleShip = 30;
bool isMoveShip = false;
int initMenu();
void initHelp();
void cleanUp();
void showRank();
void drawMenu();
void drawHeart();
void drawSound();
void showMenu();
void showHelp();
void handleMenu(SDL_Event event);
void drawMeteorite();

void drawShipMenu(int cur);
void showGameOver();
#include"handle.h"

// Hàm khởi tạo SDL và tải các tài nguyên
int initMenu()
{
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Tải tài nguyên
    IMG_Init(IMG_INIT_PNG);
    // tạo mảng heart hằng NULL
    for(int i = 0; i < 5; i++)
    {
        heart[i] = NULL;
    }
    for(int i = 0; i < 5; i ++)
    {
        heart[i] = IMG_LoadTexture(renderer,"image\\heart.png");
    }
    buff = IMG_LoadTexture(renderer,"image\\heart.png");
    buff2 = IMG_LoadTexture(renderer,"image\\shield.png");
    shield = IMG_LoadTexture(renderer,"image\\bubble.png");

    initText(&battleSky);
    setText("BATTLE SKY",&battleSky);
    loadText(100,&battleSky,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(displayMode.w/2 - 300,100,&battleSky);

    initText(&play);
    setText("PLAY",&play);
    loadText(75,&play,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(662,310,&play);

    initText(&help);
    setText("HELP",&help);
    loadText(75,&help,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(662,400,&help);

    initText(&textRank);
    setText("RANK",&textRank);
    loadText(75,&textRank,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(662,490,&textRank);

    initText(&exitMenu);
    setText("EXIT",&exitMenu);
    loadText(75,&exitMenu,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(662,580,&exitMenu);

    initText(&pauseGame);
    setText("PAUSE",&pauseGame);
    loadText(80,&pauseGame,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(662,200,&pauseGame);

    initText(&helpPause);
    setText("HELP",&helpPause);
    loadText(50,&helpPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(670,300,&helpPause);

    initText(&continuePause);
    setText("CONTINUE",&continuePause);
    loadText(50,&continuePause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(670,400,&continuePause);

    initText(&exitPause);
    setText("EXIT",&exitPause);
    loadText(50,&exitPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(670,500,&exitPause);

    initText(&soundOn);
    setText("SOUND: ON",&soundOn);
    loadText(50,&soundOn,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(670,600,&soundOn);

    initText(&soundOff);
    setText("SOUND: OFF",&soundOff);
    loadText(50,&soundOff,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    setPosText(670,600,&soundOff);

    menuObj1 = IMG_LoadTexture(renderer,"image\\SpaceThreat4.png");
    menuObj2 = IMG_LoadTexture(renderer,"image\\meteorite.png");

    backButton = IMG_LoadTexture(renderer,"image\\BackButton.png");
    backButton2 = IMG_LoadTexture(renderer,"image\\BackButton2.png");
    startButton = IMG_LoadTexture(renderer,"image\\PlayButton.png");
    startButton2 = IMG_LoadTexture(renderer,"image\\PlayButton2.png");

    soundOn_texture = IMG_LoadTexture(renderer,"image\\soundOn.png");
    soundOff_texture = IMG_LoadTexture(renderer,"image\\soundOff.png");

    return 0;
}
void initHelp()
{
    IMG_Init(IMG_INIT_PNG);
    mouseMove = IMG_LoadTexture(renderer,"image\\mouseMove.png");
    clickMouse = IMG_LoadTexture(renderer,"image\\clickMouse.png");
    esc = IMG_LoadTexture(renderer,"image\\esc.png");

}
// Hàm giải phóng các tài nguyên
void cleanUp()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(startButton);
    SDL_DestroyTexture(helpButton);
    SDL_DestroyTexture(quitButton);
    SDL_DestroyTexture(startButton2);
    SDL_DestroyTexture(helpButton2);
    SDL_DestroyTexture(quitButton2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Hàm vẽ menu game
void drawMenu()
{   
    // Vẽ hình nền
    // SDL_RenderCopy(renderer, background_menu, NULL, NULL);
    moveBackground();

    drawText(&battleSky);
    drawText(&play);
    drawText(&help);
    drawText(&textRank);
    drawText(&exitMenu);
    drawSound();
    
    SDL_Rect obj1Rect = {100,500,100,100};
    SDL_RenderCopyEx(renderer,menuObj1,NULL,&obj1Rect,angleObj1,NULL,SDL_FLIP_NONE);
    SDL_Rect obj1Rect2 = {100,350,100,100};
    SDL_RenderCopyEx(renderer,menuObj1,NULL,&obj1Rect2,angleObj1,NULL,SDL_FLIP_NONE);

    
    SDL_GetMouseState(&mouseX,&mouseY);

    if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 310 && mouseY <= 360)
    {
        // Vẽ nút play
        loadText(75,&play,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
        // SDL_RenderPresent(renderer);
    }
    else{
        loadText(75,&play,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    }
    if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 400 && mouseY <= 450)
    {
        // Vẽ nút help
        loadText(75,&help,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
        // SDL_RenderPresent(renderer);
    }
    else{
        loadText(75,&help,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    }
    if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 490 && mouseY <= 540)
    {
        // Vẽ nút rank
        loadText(75,&textRank,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
        // SDL_RenderPresent(renderer);
    }
    else{
        loadText(75,&textRank,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    }
    // kiểm tra có di vào rank không
    if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 580 && mouseY <= 630)
    {
        // Vẽ nút thoát
        loadText(75,&exitMenu,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
        // SDL_RenderPresent(renderer);
    }
    else{
        loadText(75,&exitMenu,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
    }
    if((mouseX >= 100 && mouseX <= 200 && mouseY >= 500 && mouseY <=600) || (mouseX >= 100 && mouseX <= 200 && mouseY >= 350 && mouseY <=450) )
    {
        angleObj1 = 60;
    }else angleObj1 = 30;
    //SDL_Rect rectSound = {displayMode.w - 200, displayMode.h - 200 , 100,100};
    

}

// Hàm xử lý sự kiện
void handleMenu(SDL_Event event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        
    // case SDL_MOUSEBUTTONDOWN:
        // Kiểm tra xem người dùng có nhấp vào nút bắt đầu không
        if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 650 && event.button.x <= 850 && event.button.y >= 300 && event.button.y <= 350)
        {
            inputPlayer(&playerer);
            gameLoop();
            gameOver = true;
        }

        // Kiểm tra xem người dùng có nhấp vào ginút help không
        if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 650 && event.button.x <= 850 && event.button.y >= 400 && event.button.y <= 450)
        {
            showHelp();
            gameOver = true;
        }
        if(event.button.button == SDL_BUTTON_LEFT && event.button.x >= 650 && event.button.x <= 850 && event.button.y >= 490 && event.button.y <= 540)
        {
            showRank();
        }
        // Kiểm tra xem người dùng có nhấp vào nút thoát không
        if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 650 && event.button.x <= 850 && event.button.y >= 600 && event.button.y <= 650)
        {
            gameOver = false;
        }
        /*
        xShip,
            yShip,
            150,
            150
        */
        if(event.button.button == SDL_BUTTON_LEFT && event.button.x >= xShip && event.button.x <= xShip+150 && event.button.y >= yShip && event.button.y <= yShip+150)
        {
            isMoveShip = true;
        }
        //thay đổi audio
        if(event.button.button == SDL_BUTTON_LEFT && event.button.x >= displayMode.w - 200 && event.button.x <= displayMode.w - 100 && event.button.y >=  displayMode.h - 200 && event.button.y <=  displayMode.h - 100)
        {
            if(hasAudio){
               hasAudio = false;
            }
            else{
                hasAudio = true;
            }
        }
    }
    
}
void showHelp()
{
    while(gameOver)
    {
        SDL_RenderClear(renderer);
        SDL_Event event2;
        drawHelp();
        drawMouse();
        while (SDL_PollEvent(&event2))
        {
            if(event2.type == SDL_MOUSEBUTTONDOWN)
            {
                // game
                SDL_GetMouseState(&mouseX,&mouseY);
                if ( mouseX >= 1200 && mouseX <= 1400 && mouseY >= 750 && mouseY <= 800)
                {
                    inputPlayer(&playerer);
                    gameLoop();
                    gameOver = false;
                }
                // back
                if( mouseX >= 200 && mouseX <= 400 && mouseY >= 750 && mouseY <= 800)
                {
                    return;
                }
            }
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

void showMenu()
{
    int cur = 0;
    SDL_RenderClear(renderer);
    drawMenu();
    drawMouse();
    while (gameOver)
    {
        s->status = LIVE;
        loadShip();
        if(hasAudio)
        {
            //nhạc nền menu
            if(!Mix_Playing(1))
            {
                Mix_PlayChannel(1,Menu,-1);
            }
        }else{
            Mix_HaltChannel(-1);
        }
        
        // Xóa màn hình
        SDL_RenderClear(renderer);
        SDL_Event event;
        // Xử lý sự kiện
        while (SDL_PollEvent(&event))
        {
            handleMenu(event);
             // xử lí menu
        }
        
        // printf("\n has audio : %d",hasAudio);
        if(hasAudio)
        {
             Mix_HaltChannel(2);  //dunnưgf nhạc ở kênh 2
            Mix_HaltChannel(3);  //dừng nhạc ở kênh 3
            Mix_HaltChannel(7);
            if(!Mix_Playing(1))
            {
                Mix_PlayChannel(1,Menu,-1);
            }
        }else{
            Mix_HaltChannel(-1);
        }
        // Vẽ menu game
       
        
        drawMenu();
        drawMeteorite(); // vẽ thiên thạch
        drawShipMenu(cur);
        
        cur++;
        if (cur == 8) cur = 0;
        if(isMoveShip)
        {
            xShip += cos(angleShip+15)*15;
            yShip += sin(angleShip+30)*15;
        }
        if(yShip < -10)
        {
            xShip = 720;
            yShip = 836;
        }
        drawMouse();
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

void drawHeart()
{
    for(int i = 0; i < playerer.hp; i++)
    {
        SDL_Rect r = {displayMode.w-110 - i*50 ,80,50,50};
        SDL_RenderCopy(renderer,heart[i],NULL,&r);
    }
        
}

void showRank()
{
    sortList(lpr);
    SDL_Texture *rank = NULL;
    IMG_Init(IMG_INIT_PNG);
    rank = IMG_LoadTexture(renderer,"image/broadRank.png");

    
    text title;
    initText(&title);
    setText("RANKING",&title);
    loadText(70,&title,pathFont,getColor(RED));
    setPosText(displayMode.w/2 - 150,20,&title);

    text name;
    initText(&name);
    setText("NAME",&name);
    loadText(35,&name,pathFont,getColor(RED));
    setPosText(540,160,&name);


    text score;
    initText(&score);
    setText("SCORE",&score);
    loadText(35,&score,pathFont,getColor(RED));
    setPosText(880,160,&score);

    text esc;
    initText(&esc);
    setText("ESC TO BACK",&esc);
    loadText(35,&esc,pathFont,getColor(RED));
    setPosText(displayMode.w/2 - 125,760,&esc);

    int size = lpr->size;
    text pl[size]; // mảng gồm size cái tên :v
    int i = 0;
    for(node_pr *k = lpr->head ; i < size && k!= NULL;i ++ ,k = k->next)
    {

        initText(&pl[i]);
        setText(k->data.name,&pl[i]);
        loadText(30,&pl[i],pathFont,getColor(BLACK));
        setPosText(450,200 + i*30,&pl[i]);

    }
    text pl2[size]; // mảng gồm size số điểm
    char score_[20];
    i = 0;
    
    for(node_pr *j = lpr->head ; i < size && j!= NULL;i ++ ,j = j->next)
    {
        initText(&pl2[i]);
        sprintf(score_,"%d",j->data.score);
        setText(score_,&pl2[i]);   
        loadText(30,&pl2[i],pathFont,getColor(BLACK));
        setPosText(840,200 + i*30,&pl2[i]);
    }
    // printList(*lpr);
    bool check = true;
    while(check)
    {
        SDL_RenderClear(renderer);
        
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.key.keysym.sym == SDLK_ESCAPE) check = false;
        }
        moveBackground();
        SDL_RenderCopy(renderer,rank,NULL,NULL);
        drawText(&title);
        drawText(&score);
        drawText(&name);
        drawText(&esc);
        for(int i = 0; i < size; i++)
        {
            drawText(&pl[i]);
            drawText(&pl2[i]);
        }
        drawMouse();
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

void showGameOver(){
    // bool check = true;
    text gameOverText;
    initText(&gameOverText);
    setText("GAME OVER", &gameOverText);
    loadText(70, &gameOverText, pathFont, getColor(WHITE));
    setPosText(displayMode.w/2 - 200, 100, &gameOverText);

    text playerGame;
    initText(&playerGame);
    setText("NAME: ", &playerGame);
    loadText(50, &playerGame, pathFont, getColor(WHITE));
    setPosText(200, 250, &playerGame);

    text scoreGame;
    initText(&scoreGame);
    setText("SCORE: ", &scoreGame);
    loadText(50, &scoreGame, pathFont, getColor(WHITE));
    setPosText(200, 400, &scoreGame);

    text waveGame;
    initText(&waveGame);
    setText("WAVE: ", &waveGame);
    loadText(50, &waveGame, pathFont, getColor(WHITE));
    setPosText(200, 550, &waveGame);

    text playerOver;
    char temp[20];
    initText(&playerOver);
    // sprintf(temp, "%c", playerer.name);
    setText(playerer.name, &playerOver);
    loadText(50, &playerOver, pathFont, getColor(WHITE));
    setPosText(500, 250, &playerOver);

    text scoreOver;
    initText(&scoreOver);
    sprintf(temp, "%d", playerer.score);
    setText(temp, &scoreOver);
    loadText(50, &scoreOver, pathFont, getColor(WHITE));
    setPosText(500, 400, &scoreOver);

    text waveOver;
    initText(&waveOver);
    sprintf(temp, "%d", wave);
    setText(temp, &waveOver);
    loadText(50, &waveOver, pathFont, getColor(WHITE));
    setPosText(500, 550, &waveOver);

    text restartGame;
    initText(&restartGame);
    setText("RESTART", &restartGame);
    loadText(50, &restartGame, pathFont, getColor(WHITE));
    setPosText(70, 750, &restartGame);

    text exitGame;
    initText(&exitGame);
    setText("EXIT", &exitGame);
    loadText(50, &exitGame, pathFont, getColor(WHITE));
    setPosText(1350, 750, &exitGame);

    playerer.hp = 3; // reset hp
    playerer.score = 0;
 
    wave = 0;
    while(gameOver){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEMOTION:

                    if(checkText(restartGame)){

                        loadText(50, &restartGame, pathFont, getColor(RED));
                    }
                    else{
                        loadText(50, &restartGame, pathFont, getColor(WHITE));

                    }

                    if(checkText(exitGame)){
                        loadText(50, &exitGame, pathFont, getColor(RED));
                    }
                    else{
                        loadText(50, &exitGame, pathFont, getColor(WHITE));

                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:

                    if(checkText(restartGame)){
                        freeBullets(); // giải phóng đạn 
                        freeList(lm); // giải phóng danh sách quái vật
                        freeBulletMonster(); // giải phóng đạn quái vật
                        gameLoop();
                    }
                    
                    if(checkText(exitGame)){
                        strcpy(playerer.name,"");
                        gameOver = false;
                        if(!gameOver) return; //thoát khỏi hàm tránh bị delay
                    }
                    break;
            }       
        }
        moveBackground();
        drawMouse();

        drawText(&gameOverText);
        drawText(&playerGame);
        drawText(&scoreGame);
        drawText(&waveGame);

        drawText(&playerOver);
        drawText(&scoreOver);
        drawText(&waveOver);

        drawText(&restartGame);
        drawText(&exitGame);
        SDL_RenderPresent(renderer);

    }
}
void drawMeteorite()
{
    
    SDL_Rect obj2Rect1 = {xObj1_1, yObj1_1,100,100};
    SDL_RenderCopyEx(renderer,menuObj2,NULL,&obj2Rect1,angleObj2,NULL,SDL_FLIP_NONE);
    SDL_Rect obj2Rect2 = {xObj1_2, yObj1_2,100,100};
    SDL_RenderCopyEx(renderer,menuObj2,NULL,&obj2Rect2,angleObj2,NULL,SDL_FLIP_NONE);
    SDL_Rect obj2Rect3 = {xObj1_3, yObj1_3,100,100};
    SDL_RenderCopyEx(renderer,menuObj2,NULL,&obj2Rect3,angleObj2,NULL,SDL_FLIP_NONE);
    SDL_Rect obj2Rect4 = {xObj1_4, yObj1_4,100,100};
    SDL_RenderCopyEx(renderer,menuObj2,NULL,&obj2Rect4,angleObj2,NULL,SDL_FLIP_NONE);
    angleObj2+=15;
    yObj1_1+=4;
    yObj1_2+=2;
    yObj1_3+=3;
    yObj1_4+=5;

    if(angleObj2 >= 360) angleObj2 = 0;
    if(yObj1_1 >= displayMode.h)
    {
        xObj1_1 = rand()% 1200 + 10;
        yObj1_1 = -50;
    }
    if(yObj1_2 >= displayMode.h)
    {
        xObj1_2 = rand()% 1200 + 10;
        yObj1_2 = -50;
    }
    if(yObj1_3 >= displayMode.h)
    {
        xObj1_3 = rand()% 1200 + 10;
        yObj1_3 = -50;
    } 
    if(yObj1_4 >= displayMode.h)
    {
        xObj1_4 = rand()% 1200 + 10;
        yObj1_4 = -50;
    } 
}
void drawShipMenu(int cur){
    SDL_Rect rectShip = {
            xShip,
            yShip,
            150,
            150
    };
    SDL_RenderCopyEx(renderer,s->texture,&s->frame_clip[cur],&rectShip,angleShip,NULL,SDL_FLIP_HORIZONTAL);
}
void drawSound()
{
    SDL_Rect rectSound = {displayMode.w - 200, displayMode.h - 200 , 100,100};
    if(hasAudio)
    {
        SDL_RenderCopy(renderer,soundOn_texture,NULL,&rectSound);
    }
    else{
        SDL_RenderCopy(renderer,soundOff_texture,NULL,&rectSound);   
    }

}