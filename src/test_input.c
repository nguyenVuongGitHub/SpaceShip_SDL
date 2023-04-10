#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>


int main(int argc, char* argv[]) {

    // Khởi tạo SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    // Tạo cửa sổ và bộ trình diễn
    SDL_Window* window = SDL_CreateWindow("Enter Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("fonts//Minecraft.ttf",36);
    SDL_Color textColor = {255,255,255,255};
    
    
    // Vẽ văn bản đã nhập vào hộp thoại
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "name : ", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {7, 0, textSurface->w, textSurface->h};
    

    
    // Chuỗi lưu trữ tên người dùng
    char name[256] = "name : ";
    int nameLength = 0;
    // Bắt đầu nhập văn bản
    SDL_StartTextInput();
    // Vòng lặp chính
    while (true) {
        // Xử lý các sự kiện trong SDL
        SDL_RenderClear(renderer);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(1);
            }
            if (event.type == SDL_TEXTINPUT){
                strcat(name,event.text.text);
                nameLength = strlen(name);
                textSurface = TTF_RenderText_Solid(font,name,textColor);
                textTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
                textRect.w = textSurface->w;
                textRect.h = textSurface->h;
            }
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_BACKSPACE && nameLength > 0)
                {
                    printf("length  = %d\n", nameLength);
                    name[nameLength-1] = '\0';
                    nameLength = strlen(name);
                    textSurface = TTF_RenderText_Solid(font,name,textColor);
                    textTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
                    textRect.w = textSurface->w;
                    textRect.h = textSurface->h;
                }
            }
            
        }

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
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
// #include <string.h>

// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;

// int main(int argc, char* args[]) {
//     SDL_Window* window = NULL;
//     SDL_Renderer* renderer = NULL;
//     TTF_Font* font = NULL;
//     SDL_Color textColor = { 255, 255, 255, 255 };
//     int quit = 0;
//     SDL_Event event;

//     SDL_Init(SDL_INIT_VIDEO);
//     TTF_Init();

//     window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//     renderer = SDL_CreateRenderer(window, -1, 0);
//     font = TTF_OpenFont("fonts//Minecraft.ttf", 28);

//     char inputText[100] = "";
//     int len = 0;

//     while (!quit) {
//         while (SDL_PollEvent(&event)) {
//             switch (event.type) {
//             case SDL_QUIT:
//                 quit = 1;
//                 break;
//             case SDL_KEYDOWN:
//                 if (event.key.keysym.sym == SDLK_BACKSPACE && len > 0) {
//                     // Xóa ký tự cuối cùng
//                     inputText[len - 1] = '\0';
//                     len--;
//                 }
//                 break;
//             case SDL_TEXTINPUT:
//                 // Thêm ký tự mới vào cuối chuỗi
//                 strcat(inputText, event.text.text);
//                 len++;
//                 break;
//             }

//             SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//             SDL_RenderClear(renderer);

//             int x = 15, y = 15;
//             for (int i = 0; i < len; i++) {
//                 char c = inputText[i];

//                 // Vẽ kí tự
//                 SDL_Surface* surface = TTF_RenderGlyph_Blended(font, c, textColor);
//                 SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//                 SDL_Rect destRect = { x, y, surface->w, surface->h };
//                 SDL_RenderCopy(renderer, texture, NULL, &destRect);

//                 // Giải phóng bộ nhớ
//                 SDL_FreeSurface(surface);
//                 SDL_DestroyTexture(texture);

//                 // Tăng x để chuẩn bị vẽ kí tự tiếp theo
//                 x += destRect.w;
//             }

//             SDL_RenderPresent(renderer);
//         }
//     }

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     TTF_CloseFont(font);
//     TTF_Quit();
//     SDL_Quit();

//     return 0;
// }