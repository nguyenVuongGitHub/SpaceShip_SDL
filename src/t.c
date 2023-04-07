// test quái bắn đạn
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* monster = NULL;
SDL_Texture* bullet_monster = NULL;
#define PI 3.14159265358979323846

int xMonster = -10;
int yMonster = 200;
int wMonster = 64;
int hMonster = 64;
int xBullet = xMonster;
int yBullet = yMonster;
double angle = 0;
double dente_angle = 0.1;
double bullet_radius = 20;
int wBullet = 30;
int hBullet = 30;


void init();
void drawMonster();
void moveBullet();
void drawBullet();
void spawn_bullets_around_enemy(int num_bullets);
void spawn_bullets_triangle();
void spawn_bullets_triangle2();
void spawn_quadrilateral_bullets();

int main(int argc, char* argv[])
{
    init();

    SDL_Event event;
    bool quit = false;
    int counLoop = 0;
    while (!quit)
    {
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        drawMonster();
        if(xMonster == 250) 
        {
            spawn_bullets_around_enemy(10);
            
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    return 0;
}

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Video", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
        
    IMG_Init(IMG_INIT_PNG);

    SDL_Surface* monster_surface = IMG_Load("image/SpaceThreat4.png"); 
    SDL_Surface* bullet_monster_surface = IMG_Load("image/BulletThreat.png");
    if (monster_surface != NULL)
    {
        monster = SDL_CreateTextureFromSurface(renderer, monster_surface);
    }
    SDL_FreeSurface(monster_surface);
    if (bullet_monster_surface != NULL)
    {
        bullet_monster = SDL_CreateTextureFromSurface(renderer, bullet_monster_surface);
        
    }
    SDL_FreeSurface(bullet_monster_surface);
}
void drawMonster()
{
    xMonster+=3;
    if(xMonster >= 250) xMonster = 250;

    SDL_Rect monster_rect = { xMonster, yMonster, wMonster, hMonster };
    SDL_RenderCopy(renderer,monster,NULL,&monster_rect);
}
void drawBullet()
{
    SDL_Rect bullet_rect = { xBullet+3,yBullet,wBullet,hBullet};
    SDL_RenderCopy(renderer,bullet_monster,NULL,&bullet_rect);
}

void moveBullet()
{
    int R = 500;
    xBullet = xMonster + R * cos(angle);
    yBullet = yMonster + R * sin(angle);

    angle+=dente_angle;
    if(yBullet >= 800 || yBullet <= 0) yBullet = yMonster;
    if(xBullet >= 1200 || xBullet <= 0) xBullet = xMonster;
}
void spawn_bullets_around_enemy(int num_bullets) {

    float angle_between_bullets = 2 * PI / num_bullets; // Góc giữa các viên đạn
    for (int i = 0; i < num_bullets; i++) {
        // Tính toán tọa độ của viên đạn thứ i trên đường tròn
        xBullet = xMonster + bullet_radius  * cos(i * angle_between_bullets);
        yBullet = yMonster + bullet_radius  * sin(i * angle_between_bullets);
        // Tạo ra viên đạn tại tọa độ này
        drawBullet();
        bullet_radius+=0.4;
        if(bullet_radius >= 500) bullet_radius = 20;
    }
}

void spawn_bullets_triangle()
{   
    for(int i = 0; i < 3; i++)
    {
        if(i == 0){
            xBullet = xMonster;
        }
        else if(i == 1)
        {
            xBullet = xMonster+20;
            yBullet+=15;
        }
        else if(i == 2)
        {
            yBullet-=15;
            xBullet = xMonster+40;
        }
        yBullet+=1;
        drawBullet();  
        // SDL_Delay(100); 
        if(yBullet > 800)
        {
            yBullet = yMonster;
        }
    }
}
void spawn_bullets_triangle2()
{
    float angle_between_bullets = 60.0;
    for(int i = 0; i < 3; i++)
    {
        // Tính góc giữa các viên đạn
        double bulletAngleRad = (0 - 90.0 + (i - 1) * angle_between_bullets) * M_PI / 180.0;
        
        // Tính vị trí của viên đạn theo hình tam giác
        xBullet = xMonster + cos(bulletAngleRad) * bullet_radius;
        yBullet = yMonster - sin(bulletAngleRad) * bullet_radius;
        
        // Tạo mới đối tượng đạn và thêm vào danh sách
        drawBullet();
        bullet_radius++;
        if(bullet_radius == 1000)
        {
            bullet_radius = 20;
        }
    }
}

// #include "player.h"

// int main()
// {
//     list *l = (list*)malloc(sizeof(list));
//     initList(l);
//     loadFile(fileIn, l);
//     printList(*l);
//     player *p;
//     inputPlayer(p);
//     node *newNode = createNode(*p);
//     addNode(newNode, l);

//     saveFile(fileOut,*l);
//     return 0;
// }



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






void spawn_quadrilateral_bullets()
{   
    for(int i = 0; i < 4; i++)
    {
        if(i == 0){
            xBullet = xMonster;
        }
        else if(i == 1)
        {
            xBullet = xMonster+20;
            yBullet+=15;
        }
        else if(i == 2)
        {
            // xBullet -=20;
            yBullet -= 30; 
        }
        else if(i == 3)
        {
            yBullet+=15;
            xBullet = xMonster+40;
        }
        yBullet+=1;
        drawBullet();  
        // SDL_Delay(100); 
        if(yBullet > 800)
        {
            yBullet = yMonster;
        }
    }
} 