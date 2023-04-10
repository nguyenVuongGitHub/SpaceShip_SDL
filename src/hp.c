#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BAR_WIDTH = 100;
const int BAR_HEIGHT = 10;
const int HEART_SIZE = 15;  // Kích thước ảnh trái tim
const int HEART_SCALE = 2;  // Tỉ lệ scale cho ảnh trái tim
const int MIN_X = 50;
const int MAX_X = SCREEN_WIDTH - BAR_WIDTH - 50;
const int FALLING_SPEED = 1;  // Tốc độ rơi của trái tim
const int FRAME_RATE = 150;  // Tốc độ khung hình

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Thanh mau", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load texture cho thanh mau
    SDL_Texture* health_bar_texture = IMG_LoadTexture(renderer, "image/heart.png");
    if (health_bar_texture == NULL) {
        printf("Khong the tai anh heart.png: %s\n", SDL_GetError());
        exit(1);
    }

    bool running = true;
    while (running) {
        // Random thời gian chạy tiếp
        int delay = rand() % 5000 + 1000;
        SDL_Delay(delay);

        // Khởi tạo lại giá trị ban đầu
        int x = rand() % (MAX_X - MIN_X + 1) + MIN_X;
        int y = -HEART_SIZE * HEART_SCALE;

        while (true) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    break;
                }
            }
            if (!running) {
                break;
            }

            // Xoa man hinh truoc khi ve
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Ve trai tim
            SDL_Rect heart_rect = { x, y, HEART_SIZE * HEART_SCALE, HEART_SIZE * HEART_SCALE };
            SDL_RenderCopy(renderer, health_bar_texture, NULL, &heart_rect);

            // Cap nhat vi tri cua trai tim
            y += FALLING_SPEED;

            // Khoi tao lai trai tim neu het
            if (y > SCREEN_HEIGHT) {
                break;
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(1000 / FRAME_RATE);
        }
    }

    // Giai phong tai nguyen
    SDL_DestroyTexture(health_bar_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
