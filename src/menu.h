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

int initMenu();
void cleanUp();
void showRank();
void drawPause();
void drawMenu();
void drawHeart();
void showMenu();
void showHelp();
void handleMenu(SDL_Event event, bool *quit);
void drawPause_00();
void drawPause_01();
void drawPause_10();
void drawPause_11();
void drawPause_20();
void drawPause_21();
void drawPause_30();
void drawPause_31();
void drawPause_40();
void drawPause_41();

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

    background_menu = IMG_LoadTexture(renderer, "image\\background_menu.png");
    if (!background_menu)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // IMG_Init(IMG_INIT_PNG);
    startButton = IMG_LoadTexture(renderer, "image\\PlayButton.png");
    if (!startButton)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyTexture(background);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // IMG_Init(IMG_INIT_PNG);
    helpButton = IMG_LoadTexture(renderer, "image\\HelpButton.png");
    if (!helpButton)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(startButton);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // IMG_Init(IMG_INIT_PNG);
    quitButton = IMG_LoadTexture(renderer, "image\\ExitButton.png");
    if (!quitButton)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(startButton);
        SDL_DestroyTexture(helpButton);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    backButton = IMG_LoadTexture(renderer, "image\\backButton.png");
    if (!backButton)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(startButton);
        SDL_DestroyTexture(helpButton);
        SDL_DestroyTexture(quitButton);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // IMG_Init(IMG_INIT_PNG);
    startButton2 = IMG_LoadTexture(renderer, "image\\PlayButton2.png");
    if (!startButton2)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(startButton);
        SDL_DestroyTexture(helpButton);
        SDL_DestroyTexture(quitButton);
        SDL_DestroyTexture(backButton);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // IMG_Init(IMG_INIT_PNG);
    helpButton2 = IMG_LoadTexture(renderer, "image\\HelpButton2.png");
    if (!helpButton2)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(startButton);
        SDL_DestroyTexture(helpButton);
        SDL_DestroyTexture(quitButton);
        SDL_DestroyTexture(backButton);
        SDL_DestroyTexture(startButton2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // IMG_Init(IMG_INIT_PNG);
    quitButton2 = IMG_LoadTexture(renderer, "image\\ExitButton2.png");
    if (!quitButton2)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(startButton);
        SDL_DestroyTexture(helpButton);
        SDL_DestroyTexture(quitButton);
        SDL_DestroyTexture(backButton);
        SDL_DestroyTexture(startButton2);
        SDL_DestroyTexture(helpButton2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    backButton2 = IMG_LoadTexture(renderer, "image\\backButton2.png");
    if (!backButton2)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(startButton);
        SDL_DestroyTexture(helpButton);
        SDL_DestroyTexture(quitButton);
        SDL_DestroyTexture(backButton);
        SDL_DestroyTexture(startButton2);
        SDL_DestroyTexture(helpButton2);
        SDL_DestroyTexture(quitButton2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    pause_01 = IMG_LoadTexture(renderer, "image\\0-1.png"); // ảnh khi k có âm thanh
    pause_00 = IMG_LoadTexture(renderer, "image\\0-0.png"); // ảnh khi có âm thanh

    pause_10 = IMG_LoadTexture(renderer, "image\\1-0.png");
    pause_11 = IMG_LoadTexture(renderer, "image\\1-1.png");

    pause_21 = IMG_LoadTexture(renderer, "image\\2-1.png");
    pause_20 = IMG_LoadTexture(renderer, "image\\2-0.png");

    pause_31 = IMG_LoadTexture(renderer, "image\\3-1.png");
    pause_30 = IMG_LoadTexture(renderer, "image\\3-0.png");

    pause_41 = IMG_LoadTexture(renderer, "image\\4-1.png");
    pause_40 = IMG_LoadTexture(renderer, "image\\4-0.png");
    return 0;
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


    // Vẽ nút bắt đầu
    // SDL_Rect startRect = { 650, 300, 200, 50 };
    // SDL_RenderCopy(renderer, startButton, NULL, &startRect);

    // // Vẽ nút help
    // SDL_Rect helpRect = { 650, 400, 200, 50 };
    // SDL_RenderCopy(renderer, helpButton, NULL, &helpRect);
    drawText(&battleSky);
    drawText(&play);
    drawText(&help);
    drawText(&textRank);
    drawText(&exitMenu);
    // Vẽ nút thoát
    // SDL_Rect quitRect = { 650, 600, 200, 50 };
    // SDL_RenderCopy(renderer, quitButton, NULL, &quitRect);

    SDL_GetMouseState(&mouseX,&mouseY);
    // if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 300 && mouseY <= 350)
    // {
    //     // Vẽ nút bắt đầu
    //     SDL_Rect startRect = { 650, 300, 200, 50 };
    //     SDL_RenderCopy(renderer, startButton2, NULL, &startRect);
    //     // SDL_RenderPresent(renderer);
    // }

    // // Kiểm tra xem người dùng có nhấp vào nút help không
    // if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 400 && mouseY <= 450)
    // {
    //     // Vẽ nút help
    //     SDL_Rect helpRect = { 650, 400, 200, 50 };
    //     SDL_RenderCopy(renderer, helpButton2, NULL, &helpRect);
    //     // SDL_RenderPresent(renderer);
    // }
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

    // // Kiểm tra xem người dùng có nhấp vào nút thoát không
    // if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 600 && mouseY <= 650)
    // {
    //     // Vẽ nút thoát
    //     SDL_Rect quitRect = { 650, 600, 200, 50 };
    //     SDL_RenderCopy(renderer, quitButton2, NULL, &quitRect);
    //     // SDL_RenderPresent(renderer);
    // }
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
            gameLoop();
        }

        // Kiểm tra xem người dùng có nhấp vào ginút help không
        if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 650 && event.button.x <= 850 && event.button.y >= 400 && event.button.y <= 450)
        {
            showHelp();
            
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
        // break;
    }
    
}
void showHelp()
{
    while(true)
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
                    gameLoop();
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
    SDL_RenderClear(renderer);
    drawMenu();
    drawMouse();
    while (gameOver)
    {
        //nhạc nền menu
        if(!Mix_Playing(1))
        {
            Mix_PlayChannel(1,Menu,-1);
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
        
        // Vẽ menu game
        Mix_HaltChannel(2);  //dunnưgf nhạc ở kênh 2
        Mix_HaltChannel(3);  //dừng nhạc ở kênh 3
        if(!Mix_Playing(1))
        {
            Mix_PlayChannel(1,Menu,-1);
        }
        drawMenu();
        drawMouse();
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

void drawPause_00()
{
    SDL_RenderCopy(renderer,pause_00,NULL,NULL);
}
void drawPause_01()
{
    SDL_RenderCopy(renderer,pause_01,NULL,NULL);
}
void drawPause_10()
{
    SDL_RenderCopy(renderer,pause_10,NULL,NULL);
}
void drawPause_11()
{
    SDL_RenderCopy(renderer,pause_11,NULL,NULL);
}
void drawPause_20()
{
    SDL_RenderCopy(renderer,pause_20,NULL,NULL);
}
void drawPause_21()
{
    SDL_RenderCopy(renderer,pause_21,NULL,NULL);
}
void drawPause_30()
{
    SDL_RenderCopy(renderer,pause_30,NULL,NULL);
}
void drawPause_31()
{
    SDL_RenderCopy(renderer,pause_31,NULL,NULL);
}
void drawPause_40()
{
    SDL_RenderCopy(renderer,pause_40,NULL,NULL);
}
void drawPause_41()
{
    SDL_RenderCopy(renderer,pause_41,NULL,NULL);
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

                    if(mouseX >= restartGame.x && mouseX <= restartGame.x + restartGame.w
                    && mouseY >= restartGame.y && mouseY <= restartGame.y + restartGame.h){

                        loadText(50, &restartGame, pathFont, getColor(RED));
                    }
                    else{
                        loadText(50, &restartGame, pathFont, getColor(WHITE));

                    }

                    if(mouseX >= exitGame.x && mouseX <= exitGame.x + exitGame.w
                    && mouseY >= exitGame.y && mouseY <= exitGame.y + exitGame.h){
                        loadText(50, &exitGame, pathFont, getColor(RED));
                    }
                    else{
                        loadText(50, &exitGame, pathFont, getColor(WHITE));

                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:

                    if(mouseX >= restartGame.x && mouseX <= restartGame.x + restartGame.w
                    && mouseY >= restartGame.y && mouseY <= restartGame.y + restartGame.h){
                        freeBullets(); // giải phóng đạn 
                        freeList(lm); // giải phóng danh sách quái vật
                        freeBulletMonster(); // giải phóng đạn quái vật
                        gameLoop();
                    }
                    
                    if(mouseX >= exitGame.x && mouseX <= exitGame.x + exitGame.w
                    && mouseY >= exitGame.y && mouseY <= exitGame.y + exitGame.h){
                        // tạo node mới để thêm vào danh sách người chơi
                        // freeBullets(); // giải phóng đạn 
                        // freeList(lm); // giải phóng danh sách quái vật
                        // freeBulletMonster();// giải phóng đạn quái vật
                        // showMenu(); // về lại menu
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