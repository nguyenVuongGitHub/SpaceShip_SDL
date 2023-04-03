#pragma once
#include "global.h"
// Khai báo biến toàn cục
int initMenu();
void cleanUp();

void drawMenu();
void showMenu();
void handleMenu(SDL_Event event, bool *quit);
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
    IMG_Init(IMG_INIT_PNG);
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
    IMG_Init(IMG_INIT_PNG);
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
    IMG_Init(IMG_INIT_PNG);
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

    return 0;
}

// Hàm giải phóng các tài nguyên
void cleanUp()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(startButton);
    SDL_DestroyTexture(helpButton);
    SDL_DestroyTexture(quitButton);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Hàm vẽ menu game
void drawMenu()
{
    // Xóa màn hình
    SDL_RenderClear(renderer);

    // Vẽ hình nền
    SDL_RenderCopy(renderer, background_menu, NULL, NULL);

    // Vẽ nút bắt đầu
    SDL_Rect startRect = { 450, 300, 200, 50 };
    SDL_RenderCopy(renderer, startButton, NULL, &startRect);

    // Vẽ nút help
    SDL_Rect helpRect = { 450, 400, 200, 50 };
    SDL_RenderCopy(renderer, helpButton, NULL, &helpRect);

    // Vẽ nút thoát
    SDL_Rect quitRect = { 450, 500, 200, 50 };
    SDL_RenderCopy(renderer, quitButton, NULL, &quitRect);

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

// Hàm xử lý sự kiện
void handleMenu(SDL_Event event, bool *quit)
{
    switch (event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            // Kiểm tra xem người dùng có nhấp vào nút bắt đầu không
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 300 && event.button.x <= 650 && event.button.y >= 300 && event.button.y <= 350)
            {
                gameLoop();
            }

            // Kiểm tra xem người dùng có nhấp vào nút help không
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 300 && event.button.x <= 650 && event.button.y >= 400 && event.button.y <= 450)
            {
                printf("Help button clicket!\n");
            }
            // Kiểm tra xem người dùng có nhấp vào nút thoát không
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 300 && event.button.x <= 650 && event.button.y >= 500 && event.button.y <= 550)
            {
                exit(0);
            }
            break;
    }
}
void showMenu()
{
    SDL_ShowCursor(SDL_ENABLE);
    SDL_RenderClear(renderer);
    drawMenu();
    while (gameOver == false)
    {
        SDL_Event event;
        // Xử lý sự kiện
        while (SDL_PollEvent(&event))
        {
            handleMenu(event, &gameOver); // xử lí menu
        }
        
        // Vẽ menu game
        drawMenu();
    }
}
