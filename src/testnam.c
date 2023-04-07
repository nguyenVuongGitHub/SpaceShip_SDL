#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PLAYER_SPEED 5
#define BULLET_SPEED 10
#define ENEMY_SPEED 3
#define ENEMY_FIRE_RATE 0.005
#define BULLET_MAX 100
#define ENEMY_MAX 10
#define FRAME_DURATION 16

// Cấu trúc máy bay
typedef struct {
    int x;
    int y;
    int width;
    int height;
    bool alive;
} Plane;

// Cấu trúc đạn
typedef struct {
    int x;
    int y;
    int width;
    int height;
    bool alive;
} Bullet;

// Cấu trúc máy bay địch
typedef struct {
    int x;
    int y;
    int width;
    int height;
    bool alive;
    double fireRate;
    int fireCountdown;
} EnemyPlane;

int main(int argc, char* args[]) {
    // Khởi tạo SDL
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    // Tạo cửa sổ
    SDL_Window* window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Tạo font chữ
    TTF_Font* font = TTF_OpenFont("Arial.ttf", 24);
    SDL_Color textColor = { 255, 255, 255, 255 };

    // Tạo texture cho máy bay, đạn và máy bay địch
    SDL_Surface* playerSurface = IMG_Load("plane.png");
    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    SDL_FreeSurface(playerSurface);

    SDL_Surface* bulletSurface = IMG_Load("bullet.png");
    SDL_Texture* bulletTexture = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    SDL_FreeSurface(bulletSurface);

    SDL_Surface* enemySurface = IMG_Load("enemy.png");
    SDL_Texture* enemyTexture = SDL_CreateTextureFromSurface(renderer, enemySurface);
    SDL_FreeSurface(enemySurface);

    // Khởi tạo máy bay
    Plane player = { SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 40, 32, 24, true };

    // Khởi tạo đạn
    Bullet bullets[BULLET_MAX];
    for (int i = 0; i < BULLET_MAX; i++) {
        bullets[i].x = -1000;
        bullets[i].y = -1000;
        bullets[i].width = 8;
        bullets[i].height = 8;
        bullets[i].alive = false;
    }

    // Khởi tạo máy bay địch
    EnemyPlane enemies[ENEMY_MAX];
    srand(time(NULL));
    for (int i = 0; i < ENEMY_MAX;
    enemies[i].x = rand() % (SCREEN_WIDTH - 32);
    enemies[i].y = rand() % (SCREEN_HEIGHT / 2);
    enemies[i].width = 32;
    enemies[i].height = 24;
    enemies[i].alive = true;
    enemies[i].fireRate = ENEMY_FIRE_RATE;
    enemies[i].fireCountdown = rand() % 100;
}

// Biến để lưu trữ trạng thái chơi
bool isRunning = true;

// Biến để đếm số máy bay địch đã bị tiêu diệt
int enemyDestroyed = 0;

// Vòng lặp chính
while (isRunning) {
    // Xử lý sự kiện
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }

    // Kiểm tra phím người chơi nhấn và di chuyển máy bay
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_LEFT] && player.x > 0) {
        player.x -= PLAYER_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT] && player.x < SCREEN_WIDTH - player.width) {
        player.x += PLAYER_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_SPACE]) {
        // Tìm một viên đạn trống để bắn
        for (int i = 0; i < BULLET_MAX; i++) {
            if (!bullets[i].alive) {
                bullets[i].x = player.x + player.width / 2 - bullets[i].width / 2;
                bullets[i].y = player.y - bullets[i].height;
                bullets[i].alive = true;
                break;
            }
        }
    }

    // Di chuyển đạn và kiểm tra va chạm giữa đạn và máy bay địch
    for (int i = 0; i < BULLET_MAX; i++) {
        if (bullets[i].alive) {
            bullets[i].y -= BULLET_SPEED;
            if (bullets[i].y < 0) {
                bullets[i].alive = false;
            }
            for (int j = 0; j < ENEMY_MAX; j++) {
                if (enemies[j].alive && bullets[i].x + bullets[i].width > enemies[j].x && bullets[i].x < enemies[j].x + enemies[j].width && bullets[i].y + bullets[i].height > enemies[j].y && bullets[i].y < enemies[j].y + enemies[j].height) {
                    bullets[i].alive = false;
                    enemies[j].alive = false;
                    enemyDestroyed++;
                }
            }
        }
    }

    // Di chuyển máy bay địch và cho máy bay địch bắn đạn
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].alive) {
            enemies[i].y += ENEMY_SPEED;
            if (enemies[i].y > SCREEN_HEIGHT) {
                enemies[i].alive = false;
            }
            enemies[i].fireCountdown--;
            if (enemies[i].fireCountdown <= 0) {
                enemies[i].fireCountdown = rand() % 100;
                if (rand() < enemies[i].fireRate *
                    SDL_Rect enemyBullet = {
                        .x = enemies[i].x + enemies[i].width / 2 - 2,
                        .y = enemies[i].y + enemies[i].height,
                        .w = 4,
                        .h = 8
                    };
                    for (int j = 0; j < ENEMY_BULLET_MAX; j++) {
                        if (!enemyBullets[j].alive) {
                            enemyBullets[j] = enemyBullet;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Di chuyển đạn của máy bay địch
    for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
        if (enemyBullets[i].h > 0) {
            enemyBullets[i].y += ENEMY_BULLET_SPEED;
            if (enemyBullets[i].y > SCREEN_HEIGHT) {
                enemyBullets[i].h = 0;
            }
        }
    }

    // Vẽ tất cả các đối tượng lên màn hình
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Vẽ máy bay người chơi
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &player);

    // Vẽ tất cả các viên đạn
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < BULLET_MAX; i++) {
        if (bullets[i].alive) {
            SDL_RenderFillRect(renderer, &bullets[i]);
        }
    }

    // Vẽ tất cả các máy bay địch
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].alive) {
            SDL_RenderFillRect(renderer, &enemies[i]);
        }
    }

    // Vẽ tất cả đạn của máy bay địch
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
        if (enemyBullets[i].h > 0) {
            SDL_RenderFillRect(renderer, &enemyBullets[i]);
        }
    }

    // Vẽ số máy bay địch đã bị tiêu diệt
    char destroyedString[32];
    sprintf(destroyedString, "Destroyed: %d", enemyDestroyed);
    SDL_Surface* destroyedSurface = TTF_RenderText_Solid(font, destroyedString, (SDL_Color){255, 255, 255, 255});
    SDL_Texture* destroyedTexture = SDL_CreateTextureFromSurface(renderer, destroyedSurface);
    SDL_Rect destroyedRect = {0, 0, destroyedSurface->w, destroyedSurface->h};
    SDL_RenderCopy(renderer, destroyedTexture, NULL, &destroyedRect);
    SDL_FreeSurface(destroyedSurface);
    SDL_DestroyTexture(destroyedTexture);

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);

    // Tạm dừng vòng lặp để giữ tốc độ khung hình
    SDL_Delay(1000 / FPS);
}

// Đóng SDL
SDL_DestroyRenderer(renderer);
// Hủy cửa sổ
SDL_DestroyWindow(window);

// Hủy font
TTF_CloseFont(font);

// Thoát SDL
TTF_Quit();
SDL_Quit();

return 0;
