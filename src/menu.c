#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

// Khai báo biến toàn cục
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* background = NULL;
SDL_Texture* startButton = NULL;
SDL_Texture* helpButton = NULL;
SDL_Texture* quitButton = NULL;

// Hàm khởi tạo SDL và tải các tài nguyên
int init()
{
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Tạo cửa sổ
    int index_window = 0;
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(index_window, &displayMode);
    window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 860, 640, 0);
    if (!window)
    {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Tạo renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Tải tài nguyên
    IMG_Init(IMG_INIT_PNG);
    background = IMG_LoadTexture(renderer, "img\\menu.png");
    if (!background)
    {
        printf("IMG_LoadTexture failed: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    IMG_Init(IMG_INIT_PNG);
    startButton = IMG_LoadTexture(renderer, "img\\PlayButton.png");
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
    helpButton = IMG_LoadTexture(renderer, "img\\HelpButton.png");
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
    quitButton = IMG_LoadTexture(renderer, "img\\ExitButton.png");
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
    SDL_RenderCopy(renderer, background, NULL, NULL);

    // Vẽ nút bắt đầu
    SDL_Rect startRect = { 300, 300, 200, 50 };
    SDL_RenderCopy(renderer, startButton, NULL, &startRect);

    // Vẽ nút help
    SDL_Rect helpRect = { 300, 400, 200, 50 };
    SDL_RenderCopy(renderer, helpButton, NULL, &helpRect);

    // Vẽ nút thoát
    SDL_Rect quitRect = { 300, 500, 200, 50 };
    SDL_RenderCopy(renderer, quitButton, NULL, &quitRect);

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

// Hàm xử lý sự kiện
void handleEvent(SDL_Event event, bool& quit)
{
    switch (event.type)
    {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Kiểm tra xem người dùng có nhấp vào nút bắt đầu không
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 300 && event.button.x <= 500 && event.button.y >= 300 && event.button.y <= 350)
            {
                printf("Start button clicked!\n");
            }

            // Kiểm tra xem người dùng có nhấp vào nút help không
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 300 && event.button.x <= 500 && event.button.y >= 400 && event.button.y <= 450)
            {
                printf("Help button clicket!\n");
            }
            // Kiểm tra xem người dùng có nhấp vào nút thoát không
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 300 && event.button.x <= 500 && event.button.y >= 500 && event.button.y <= 550)
            {
                quit = true;
            }
            break;
    }
}

// Hàm chính
int main(int argc, char* argv[])
{
    bool quit = false;
    SDL_Event event;
    // Khởi tạo SDL và tải các tài nguyên
    if (init() != 0)
    {
        return 1;
    }

    // Vòng lặp chính
    while (!quit)
    {
        // Xử lý sự kiện
        while (SDL_PollEvent(&event))
        {
            handleEvent(event, quit);
        }

        // Vẽ menu game
        drawMenu();
    }

    // Giải phóng các tài nguyên và thoát SDL
    cleanUp();

    return 0;
}
