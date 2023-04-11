// test quái bắn đạn
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
SDL_Window* window;
SDL_Renderer* renderer;

<<<<<<< HEAD
int xMonster = -10;
int yMonster = 200;
int wMonster = 100;
int hMonster = 100;
int xBullet = xMonster;
int yBullet = yMonster;
double angle = 0;
double dente_angle = 0.1;
double bullet_radius = 20;
int wBullet = 30;
int hBullet = 30;

int bullet_count = 0;
clock_t last_time = 0;
const int BULLET_INTERVAL_MS = 1000;

void init();
void drawMonster();
void moveBullet();
void drawBullet();
void spawn_bullets_around_enemy(int num_bullets);
void spawn_bullets_triangle();
void spawn_bullets_triangle2();

=======
struct bullet_monster{
    int x;
    int y;
    int h;
    int w;
    int speed;
    float radius;
    bool active;
    float angle;
    SDL_Texture *texture;
};
typedef struct bullet_monster bullet_monster;

void initBulletMonster(bullet_monster *bullet);
void loadBulletMonster(bullet_monster *bullet);
void drawBulletMonster(bullet_monster *bullet);
void moveBulletMonster(bullet_monster *bullet);
void addBulletToList(int num);
#define MAX_BULLET_MONSTER 1000
bullet_monster *listBulletMonster[MAX_BULLET_MONSTER]; // giới hạn đạn trên màn hình là 5000
//

int main(int argc, char *argv[])
{
    system("cls");
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("test đạn",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,800,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    // cấp phát bộ nhớ cho mảng các viên đạn
    for(int i = 0; i < MAX_BULLET_MONSTER; i ++)
        listBulletMonster[i] = (bullet_monster*)malloc(sizeof(bullet_monster));
    
    // cho trạng thái của các viên đạn là false - ko di chuyển
    for(int i = 0; i < MAX_BULLET_MONSTER; i++)
        listBulletMonster[i]->active = false;

    IMG_Init(IMG_INIT_PNG);
    SDL_Texture* monster = IMG_LoadTexture(renderer,"image/SpaceThreat1.png");
    SDL_Rect r = {500,0,100,100};
    int countLoop = 0;
    bool isRunning = true;
    int i = -1;
    while(isRunning)
    {
        SDL_Event event;
        SDL_RenderClear(renderer);
        
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                isRunning = false;
        }
        //thêm đạn vào danh sách

        // sau sẽ đổi thành canMakeBullet ->  quái hp > 0
        // sau 20 vòng lặp chính sẽ spam đạn về sau sẽ đổi thành getTicks để lấy bao nhiêu mili giây
        if(monster != NULL && countLoop % 20 == 0)
        {
            i++; // biến biểu thị viên đạn thứ i
            // tạo viên đạn mới và thêm vào danh sách
            // cách tạo đạn tùy theo loại quái cần spam như thế nào
            addBulletToList(i);      
        }

        //xuất đạn ra 
        for(int i = 0; i < MAX_BULLET_MONSTER; i++)
        {
            if(listBulletMonster[i] != NULL && listBulletMonster[i]->active)
            {
                printf("\n i = %d",i);
                drawBulletMonster(listBulletMonster[i]); 
                moveBulletMonster(listBulletMonster[i]);
            }
        }


        countLoop++;
        
        SDL_RenderCopyEx(renderer,monster,NULL,&r,180,NULL,SDL_FLIP_NONE); // vẽ quái
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyTexture(monster);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


//===================================
void initBulletMonster(bullet_monster *bullet)
{
    bullet = (bullet_monster*)malloc(sizeof(bullet_monster));
    bullet->h = 0;
    bullet->w = 0;
    bullet->x = -10;
    bullet->y = -10;
    bullet->angle = 0;
    bullet->radius = 0;
    bullet->texture = NULL;
    bullet->active = false;
}
void loadBulletMonster(bullet_monster *bullet)
{
    IMG_Init(IMG_INIT_PNG);

    const char* bullet_file_path;
    bullet_file_path = "image/BulletThreat.png";
    SDL_Surface* bullet_surface = IMG_Load(bullet_file_path); 
    if (bullet_surface != NULL)
    {
        bullet->texture = SDL_CreateTextureFromSurface(renderer, bullet_surface);
        
    }
    SDL_FreeSurface(bullet_surface);
}

void drawBulletMonster(bullet_monster *bullet)
{
    SDL_Rect r = {
        bullet->x, bullet->y, bullet->w, bullet->h
    };
    SDL_RenderCopy(renderer,bullet->texture,NULL,&r);
}

void moveBulletMonster(bullet_monster *bullet)
{

    SDL_Rect bullet_rect = { xBullet+3,yBullet,wBullet,hBullet};
    SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
    SDL_RenderCopyEx(renderer,bullet_monster,NULL,&bullet_rect,angle,NULL,flip);
}

void moveBullet()
{
    // srand(time(0));
    // angle=rand()%(120+120+1)-120;
    // angle = 0;
    // yBullet+=1;
    // xBullet=30*sin(PI*yBullet/100)+xMonster;
    
    // xBullet+=2*cos(angle*PI/180);
    // yBullet+=2*sin(angle*PI/180);

    // xBullet+=1;
    // yBullet=50*sin(PI*xBullet/100)+yMonster;

    // yBullet+=1;
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
        xBullet = xMonster + bullet_radius * cos(i * angle_between_bullets);
        yBullet = yMonster + bullet_radius * sin(i * angle_between_bullets);
        // Tạo ra viên đạn tại tọa độ này
        drawBullet();
        bullet_radius+=0.3; // tăng bán kính
        if(bullet_radius >= 1000)
        {
            bullet_radius = 20;
        }


        bullet->y += bullet->speed;
    if(bullet->y >= 800){
        bullet->active = false;

    }
}
void addBulletToList(int num)
{
    bullet_monster *bullet = NULL;
    // tận dụng lại danh sách bởi vì cái nào ra khởi màn hình thì là active đưa về lại false -> ko bị tràn bộ nhớ
    for(int j = 0; j < 50; j++)
    {
        if(listBulletMonster[j]->active == false)
        {
            bullet = listBulletMonster[j];
            break;
        }
    }
    
    if(bullet == NULL)
    {
        bullet = (bullet_monster*)malloc(sizeof(bullet_monster));
        listBulletMonster[num] = bullet;
    }

    initBulletMonster(bullet);
    loadBulletMonster(bullet);


    // tại đây khởi tạo x y đạn như bình thường
    bullet->x = 500 + 100/2; // xMonster + wMonster/2
    bullet->y = 0 + 100;// yMonster + hMonster
    bullet->w = 15;
    bullet->h = 15;
    bullet->speed = 2;
    bullet->active = true;
}

<<<<<<< HEAD
void spawn_random_bullet()
{
    // tọa độ min và tọa độ max 
    const float min_angle = -180.0;
    const float max_angle = 360.0;
    
    // khởi tạo rand 
    srand(time(NULL));
    
    // float bullet_angle_deg = min_angle + ((float) rand()) /(((float)RAND_MAX)/(max_angle-min_angle));
    float bullet_angle_deg = ((float) rand() / RAND_MAX) * (max_angle - min_angle) + min_angle;

    printf("%.2f\t", bullet_angle_deg);
    // chuyển độ sang rad 
    double bullet_angle_rad = (bullet_angle_deg - 90.0) * PI / 180.0;

    // tính toán vị trí của đạn 
    xBullet = xMonster + cos(bullet_angle_rad) * bullet_radius;
    yBullet = yMonster + sin(bullet_angle_rad) * bullet_radius;

    printf("%d", xBullet);
    printf("\t%d", yBullet);

    // Tạo mới đối tượng đạn và thêm vào danh sách
    drawBullet();
    bullet_radius+= 5;
    if (bullet_radius == 1000) {
        bullet_radius = 20;
    }
    }
//     if(xBullet <= 0 && (yBullet >= 0 && yBullet <= 800)){
//         xBullet = xMonster;
//         yBullet = yMonster;
//         bullet_radius = 20;
    
//     printf("\t%ld", bullet_radius);
// }


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
         
            //spawn_bullets_triangle2();
            spawn_random_bullet();
          
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    return 0;
}
=======

// void spawn_bullets_around_enemy(int num_bullets) {

//     float angle_between_bullets = 2 * PI / num_bullets; // Góc giữa các viên đạn
//     for (int i = 0; i < num_bullets; i++) {
//         // Tính toán tọa độ của viên đạn thứ i trên đường tròn
//         xBullet = xMonster + bullet_radius  * cos(i * angle_between_bullets);
//         yBullet = yMonster + bullet_radius  * sin(i * angle_between_bullets);
//         // Tạo ra viên đạn tại tọa độ này
//         drawBullet();
//         bullet_radius+=0.4;
//         if(bullet_radius >= 500) bullet_radius = 20;
//     }
// }

// void spawn_bullets_triangle()
// {   
//     for(int i = 0; i < 3; i++)
//     {
//         if(i == 0){
//             xBullet = xMonster;
//         }
//         else if(i == 1)
//         {
//             xBullet = xMonster+20;
//             yBullet+=15;
//         }
//         else if(i == 2)
//         {
//             yBullet-=15;
//             xBullet = xMonster+40;
//         }
//         yBullet+=1;
//         drawBullet();  
//         // SDL_Delay(100); 
//         if(yBullet > 800)
//         {
//             yBullet = yMonster;
//         }
//     }
// }
// void spawn_bullets_triangle2()
// {
//     float angle_between_bullets = 60.0;
//     for(int i = 0; i < 3; i++)
//     {
//         // Tính góc giữa các viên đạn
//         double bulletAngleRad = (0 - 90.0 + (i - 1) * angle_between_bullets) * M_PI / 180.0;
        
//         // Tính vị trí của viên đạn theo hình tam giác
//         xBullet = xMonster + cos(bulletAngleRad) * bullet_radius;
//         yBullet = yMonster - sin(bulletAngleRad) * bullet_radius;
        
//         // Tạo mới đối tượng đạn và thêm vào danh sách
//         drawBullet();
//         bullet_radius++;
//         if(bullet_radius == 1000)
//         {
//             bullet_radius = 20;
//         }
//     }
// }
// void spawn_quadrilateral_bullets()
// {   
//     for(int i = 0; i < 4; i++)
//     {
//         if(i == 0){
//             xBullet = xMonster;
//         }
//         else if(i == 1)
//         {
//             xBullet = xMonster+20;
//             yBullet+=15;
//         }
//         else if(i == 2)
//         {
//             // xBullet -=20;
//             yBullet -= 30; 
//         }
//         else if(i == 3)
//         {
//             yBullet+=15;
//             xBullet = xMonster+40;
//         }
//         yBullet+=1;
//         drawBullet();  
//         // SDL_Delay(100); 
//         if(yBullet > 800)
//         {
//             yBullet = yMonster;
//         }
//     }
// } 

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



>>>>>>> c58dcade014b8b46e49848d1e49e242c035d7856
