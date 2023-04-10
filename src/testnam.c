#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BAR_WIDTH = 100;
const int BAR_HEIGHT = 10;
const int MIN_X = 50;
const int MAX_X = SCREEN_WIDTH - BAR_WIDTH - 50;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Thanh mau", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load texture cho thanh mau
    SDL_Texture* health_bar_texture = IMG_LoadTexture(renderer, "image/bulletShip.png");
    if (health_bar_texture == NULL) {
        printf("Khong the tai anh health_bar.png: %s\n", SDL_GetError());
        exit(1);
    }

    int x = rand() % (MAX_X - MIN_X + 1) + MIN_X;
    int y = 50;

    int health = 100;
    int bar_width = health * BAR_WIDTH / 100;

    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Xoa man hinh truoc khi ve
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Ve thanh mau
        SDL_Rect health_bar_rect = { x, y, bar_width, BAR_HEIGHT };
        SDL_RenderCopy(renderer, health_bar_texture, NULL, &health_bar_rect);

        // Giam mau dan
        health--;
        bar_width = health * BAR_WIDTH / 100;

        // Cap nhat vi tri cua thanh mau
        y++;

        // Khoi tao lai thanh mau neu het
        if (health == 0) {
            x = rand() % (MAX_X - MIN_X + 1) + MIN_X;
            health = 100;
            bar_width = health * BAR_WIDTH / 100;
            y = 50;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    // Giai phong tai nguyen
    SDL_DestroyTexture(health_bar_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}