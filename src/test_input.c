#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
int main() {
    // Khởi tạo SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Tạo cửa sổ và bộ trình diễn
    SDL_Window* window = SDL_CreateWindow("Enter Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Bắt đầu nhập văn bản
    SDL_StartTextInput();

    // Chuỗi lưu trữ tên người dùng
    char name[256] = "";
    int nameLength = 0;

    // Vòng lặp chính
    SDL_bool done = SDL_FALSE;
    while (!done) {
        // Xử lý các sự kiện trong SDL
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    if (SDL_GetKeyboardFocus() == window) {
                        if (nameLength < 255) {
                            strcat(name, event.text.text);
                            nameLength = strlen(name);
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        printf("Your name is %s\n", name);
                        done = SDL_TRUE;
                    }
                    break;
            }
        }

        // Xóa toàn bộ nội dung của cửa sổ
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Vẽ hộp thoại nhập tên
        SDL_Rect rect = {100, 100, 400, 200};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);

       
    // Vẽ văn bản đã nhập vào hộp thoại
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, name, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {110, 110, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Hiển thị nội dung lên màn hình
    SDL_RenderPresent(renderer);
}
// Dừng nhập văn bản
SDL_StopTextInput();

// Giải phóng bộ nhớ và thoát SDL
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
}


