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