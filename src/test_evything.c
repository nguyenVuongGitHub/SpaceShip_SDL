#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    // Khởi tạo SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // SDL_RenderSetLogicalSize(renderer,8*8,8);
    
    // Load tấm ảnh chứa các frame
    SDL_Surface* surface = IMG_Load("image/spaceship.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // int textureWidth, textureHeight;
    // SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    
    // Cắt tấm ảnh thành 8 frame riêng lẻ
    const int numFrames = 8;
    const int frameWidth = surface->w/numFrames;
    const int frameHeight = surface->h;

    SDL_Rect frames[numFrames];
    for (int i = 0; i < numFrames; i++)
    {
        frames[i].x = i * frameWidth;
        frames[i].y = 0;
        frames[i].w = 64;
        frames[i].h = 64;
    }
    SDL_Rect rect ={
        600,400,frameWidth,frameHeight
    };
    // Vòng lặp chính
    int currentFrame = 0;
    bool quit = false;
    while (!quit)
    {
        // Xử lý các sự kiện
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Xóa renderer
        SDL_RenderClear(renderer);

        
        // Vẽ frame hiện tại
        SDL_RenderCopy(renderer, texture,&frames[currentFrame], &rect);
        SDL_RenderPresent(renderer);

        // Chuyển đến frame kế tiếp
        currentFrame++;
        if (currentFrame >= numFrames)
        {
            currentFrame = 0;
        }

        // Chờ một thời gian ngắn trước khi hiển thị frame tiếp theo
        SDL_Delay(1000 / 30); // 30fps

    }

    // Giải phóng bộ nhớ
}