#include "player.h"

int main()
{
    list *l = (list*)malloc(sizeof(list));
    initList(l);
    loadFile(fileIn, l);
    printList(*l);
    player *p;
    inputPlayer(p);
    node *newNode = createNode(*p);
    addNode(newNode, l);

    saveFile(fileOut,*l);
    return 0;
}



// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <stdio.h>
// #include <time.h>
// bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
// {
//     if(object1.x+object1.w>=object2.x && object2.x+object2.w>=object1.x
//        && object1.y+object1.h>=object2.y && object2.y+object2.h>=object1.y)
//     {
//         return true;
//     }
//     return false;
// }
// void draw(){
    
// }
// int xmouse = 600;
// int ymouse = 500;

// int main(int argc, char* argv[])
// {
//     // Khởi tạo SDL
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window* window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

//     // SDL_RenderSetLogicalSize(renderer,8*8,8);
    
//     // Load tấm ảnh chứa các frame
//     SDL_Surface* surface = IMG_Load("image/spaceship.png");
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//     SDL_FreeSurface(surface);


//     SDL_Surface *surface2 = IMG_Load("image/bulletShip.png");
//     SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer,surface2);
//     SDL_FreeSurface(surface2);

//     // int textureWidth, textureHeight;
//     // SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    
//     // Cắt tấm ảnh thành 8 frame riêng lẻ
//     const int numFrames = 8;
//     const int frameWidth = surface->w/numFrames;
//     const int frameHeight = surface->h;

//     SDL_Rect frames[numFrames];
//     for (int i = 0; i < numFrames; i++)
//     {
//         frames[i].x = i * frameWidth;
//         frames[i].y = 0;
//         frames[i].w = 64;
//         frames[i].h = 64;
//     }
    
//     // Vòng lặp chính
//     int currentFrame = 0;
//     bool quit = false;
//     SDL_Rect rect2 = {
//             300,200,100,100
//         };
//     while (!quit)
//     {
//         // Xử lý các sự kiện
//         SDL_Event event;
//         SDL_RenderClear(renderer);
//         SDL_Rect rect ={
//                     xmouse,ymouse,frameWidth,frameHeight
//         };
//         SDL_RenderCopy(renderer, texture,&frames[currentFrame], &rect);

        
//         SDL_RenderCopy(renderer,texture2,NULL,&rect2);
//         while (SDL_PollEvent(&event))
//         {
//             if (event.type == SDL_QUIT)
//             {
//                 quit = true;
//             }
//             if(event.type == SDL_MOUSEMOTION)
//             {
//                 SDL_GetMouseState(&xmouse,&ymouse);
//                 SDL_Rect rect ={
//                     xmouse,ymouse,frameWidth,frameHeight
//                 };
//                 SDL_RenderCopy(renderer, texture,&frames[currentFrame], &rect);
//             }
//         }

//         // Xóa renderer
        

//         if(CheckCollision(rect,rect2)){
//             srand(time(0));
//             rect2.x = rand() % 800;
//             rect2.y = rand() % 800;
//         }
        
//         // Vẽ frame hiện tại
        
//         SDL_RenderPresent(renderer);

//         // Chuyển đến frame kế tiếp
//         currentFrame++;
//         if (currentFrame >= numFrames)
//         {
//             currentFrame = 0;
//         }

//         // Chờ một thời gian ngắn trước khi hiển thị frame tiếp theo
//         SDL_Delay(1000 / 60); // 60fps

//     }

//     // Giải phóng bộ nhớ
// }