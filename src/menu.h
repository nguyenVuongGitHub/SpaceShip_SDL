#pragma once
#include "global.h"
// Khai báo biến toàn cục
int initMenu();
void cleanUp();
void drawPause();
void drawMenu();
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
    SDL_RenderCopy(renderer, background_menu, NULL, NULL);

    // Vẽ nút bắt đầu
    SDL_Rect startRect = { 650, 300, 200, 50 };
    SDL_RenderCopy(renderer, startButton, NULL, &startRect);

    // Vẽ nút help
    SDL_Rect helpRect = { 650, 400, 200, 50 };
    SDL_RenderCopy(renderer, helpButton, NULL, &helpRect);

    // Vẽ nút thoát
    SDL_Rect quitRect = { 650, 500, 200, 50 };
    SDL_RenderCopy(renderer, quitButton, NULL, &quitRect);

    SDL_GetMouseState(&mouseX,&mouseY);
    if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 300 && mouseY <= 350)
    {
        // Vẽ nút bắt đầu
        SDL_Rect startRect = { 650, 300, 200, 50 };
        SDL_RenderCopy(renderer, startButton2, NULL, &startRect);
        // SDL_RenderPresent(renderer);
    }

    // Kiểm tra xem người dùng có nhấp vào nút help không
    if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 400 && mouseY <= 450)
    {
        // Vẽ nút help
        SDL_Rect helpRect = { 650, 400, 200, 50 };
        SDL_RenderCopy(renderer, helpButton2, NULL, &helpRect);
        // SDL_RenderPresent(renderer);
    }
    // Kiểm tra xem người dùng có nhấp vào nút thoát không
    if ( mouseX >= 650 && mouseX <= 850 && mouseY >= 500 && mouseY <= 550)
    {
        // Vẽ nút thoát
        SDL_Rect quitRect = { 650, 500, 200, 50 };
        SDL_RenderCopy(renderer, quitButton2, NULL, &quitRect);
        // SDL_RenderPresent(renderer);
    }
}

// Hàm xử lý sự kiện
void handleMenu(SDL_Event event, bool *quit)
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
            // Kiểm tra xem người dùng có nhấp vào nút thoát không
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 650 && event.button.x <= 850 && event.button.y >= 500 && event.button.y <= 550)
            {
                exit(0);
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
                SDL_GetMouseState(&mouseX,&mouseY);
                if ( mouseX >= 1200 && mouseX <= 1400 && mouseY >= 750 && mouseY <= 800)
                {
                    gameLoop();
                }
                if( mouseX >= 200 && mouseX <= 400 && mouseY >= 750 && mouseY <= 800)
                {
                    showMenu();
                }
            }
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}
void showMenu()
{
    SDL_ShowCursor(SDL_ENABLE);
    SDL_RenderClear(renderer);
    drawMenu();
    drawMouse();
    SDL_ShowCursor(SDL_DISABLE);
    while (gameOver == false)
    {
        // Xóa màn hình
        SDL_RenderClear(renderer);
        SDL_Event event;
        // Xử lý sự kiện
        while (SDL_PollEvent(&event))
        {
            handleMenu(event, &gameOver); // xử lí menu
        }
        
        // Vẽ menu game
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