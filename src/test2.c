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
const int Num_of_ThreatArray1=5;
const int Num_of_ThreatArray2=4;
const int Num_of_ThreatArray3=2;
const int Num_of_ThreatArray4=1;
const int Num_of_ThreatArray5=3;
const int Num_of_ThreatArray6=1;

int wave = 0;

int type = 0;
double angle = 0;


struct monster{
    int xMonster;
    int yMonster;
    int wMonster;
    int hMonster;
    int xBullet;
    int yBullet;
    double dente_angle;
    double bullet_radius;
};
typedef struct monster MONSTER;

MONSTER *m = (MONSTER*)malloc(sizeof(MONSTER));


void init();
void loadMonster();
void drawMonster();
void moveBullet();
void drawBullet();
void spawn_bullets_around_enemy(int num_bullets);
void monsterArrayType1();
void monsterArrayType2();
void monsterArrayType3();
void monsterArrayType4();
void monsterArrayType5();
void monsterArrayType6();
void GenerateMonster();

int main(int argc, char* argv[])
{
    
    

    init();
    loadMonster();
    printf("%d",m->xMonster);
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

        printf("%d\n",m->xMonster);
        drawMonster();
        GenerateMonster();

        // drawBullet();
        // moveBullet();
        if(m->xMonster == 250) spawn_bullets_around_enemy(20);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    free(m);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(monster);
    SDL_DestroyTexture(bullet_monster);
    return 0;
}

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Video", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
        
    // IMG_Init(IMG_INIT_PNG);

    // SDL_Surface* monster_surface = IMG_Load("image/SpaceThreat4.png"); 
    // SDL_Surface* bullet_monster_surface = IMG_Load("image/BulletThreat.png");
    // if (monster_surface != NULL)
    // {
    //     monster = SDL_CreateTextureFromSurface(renderer, monster_surface);
        
    // }
    // SDL_FreeSurface(monster_surface);
    // if (bullet_monster_surface != NULL)
    // {
    //     bullet_monster = SDL_CreateTextureFromSurface(renderer, bullet_monster_surface);
        
    // }
    // SDL_FreeSurface(bullet_monster_surface);
    m->xMonster = -1;
    m->yMonster = 200;
    m->wMonster = 100;
    m->hMonster = 100;
    m->xBullet = m->xMonster;
    m->yBullet = m->yMonster;
    m->dente_angle = 0.1;
    m->bullet_radius = 20;

}
void loadMonster(){
    IMG_Init(IMG_INIT_PNG);


    const char* monster_file_path;
    const char* bullet_file_path;

    if (type == 1) {
        monster_file_path = "image/SpaceThreat1.png";
        bullet_file_path = "image/BulletThreat.png";
    } else if(type == 2) {
        monster_file_path = "image/SpaceThreat6.png";
        bullet_file_path = "image/BulletThreat6.png";
    }
    else if(type == 3) {
        monster_file_path = "image/SpaceThreat2.png";
        bullet_file_path = "image/BulletThreat.png";
    }
    else if(type == 4) {
        monster_file_path = "image/SpaceThreat5.png";
        bullet_file_path = "image/BulletThreat2.png";
    }
    else if(type == 5) {
        monster_file_path = "image/SpaceThreat4.png";
        bullet_file_path = "image/BulletThreat5.png";
    }
    else if(type == 6) {
        monster_file_path = "image/SpaceThreat3.png";
        bullet_file_path = "image/BulletThreat.png";
    }

    
    SDL_Surface* monster_surface = IMG_Load(monster_file_path); 
    SDL_Surface* bullet_monster_surface = IMG_Load(bullet_file_path);
    if (monster_surface != NULL)
    {
        monster = SDL_CreateTextureFromSurface(renderer, monster_surface);
        
    }
    // printf("cc");
    SDL_FreeSurface(monster_surface);
    if (bullet_monster_surface != NULL)
    {
        bullet_monster = SDL_CreateTextureFromSurface(renderer, bullet_monster_surface);
        
    }
    SDL_FreeSurface(bullet_monster_surface);
}

void drawMonster()
{
    m->xMonster += 3;
    if(m->xMonster >= 250) m->xMonster = 250;

    SDL_Rect monster_rect = { m->xMonster, m->yMonster, m->wMonster, m->hMonster };
    SDL_RenderCopy(renderer,monster,NULL,&monster_rect);
}
void drawBullet()
{
    SDL_Rect bullet_rect = { m->xBullet+3,m->yBullet,30,30};
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
    // xBullet = xMonster + R * cos(angle);
    // yBullet = yMonster + R * sin(angle);

    // angle+=dente_angle;
    // if(yBullet >= 800 || yBullet <= 0) yBullet = yMonster;
    // if(xBullet >= 1200 || xBullet <= 0) xBullet = xMonster;
}
void spawn_bullets_around_enemy(int num_bullets) {

    float angle_between_bullets = 2 * PI / num_bullets; // Góc giữa các viên đạn
    for (int i = 0; i < num_bullets; i++) {
        // Tính toán tọa độ của viên đạn thứ i trên đường tròn
        m->xBullet = m->xMonster + m->bullet_radius * cos(i * angle_between_bullets);
        m->yBullet = m->yMonster + m->bullet_radius * sin(i * angle_between_bullets);
        // Tạo ra viên đạn tại tọa độ này
        drawBullet();
        m->bullet_radius+=0.3; // tăng bán kính
        if(m->bullet_radius >= 1000)
        {
            m->bullet_radius = 20;
        }
    }
}

void monsterArrayType1(){
    for(int i = 0; i < Num_of_ThreatArray1; i++){
        type = 1;
        loadMonster();
    }
}
void monsterArrayType2(){
    for(int i = 0; i < Num_of_ThreatArray2; i++){
        type = 2;
        loadMonster();
    }
}
void monsterArrayType3(){
    for(int i = 0; i < Num_of_ThreatArray3; i++){
        type = 3;
        loadMonster();
    }
}
void monsterArrayType4(){
    for(int i = 0; i < Num_of_ThreatArray4; i++){
        type = 4;
        loadMonster();
    }
}
void monsterArrayType5(){
    for(int i = 0; i < Num_of_ThreatArray5; i++){
        type = 5;
        loadMonster();
    }
}
void monsterArrayType6(){
    for(int i = 0; i < Num_of_ThreatArray6; i++){
        type = 6;
        loadMonster();
    }
}

void GenerateMonster(){
    srand(time(NULL));
    wave += 1;
    int random = rand() % 6 + 1;
    if(random == 1){
        monsterArrayType1();
    }
    else if(random == 2){
        monsterArrayType2();
    }
    else if(random == 3){
        monsterArrayType3();
    }
    else if(random == 4){
        monsterArrayType4();
    }
    else if(random == 5){
        monsterArrayType5();
    }
    else if(random == 6){
        monsterArrayType6();
    }
    
}