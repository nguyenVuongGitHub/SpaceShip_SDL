#pragma once
#include "global.h"
#include "menu.h"
#include "monster.h"
#include "linkedListForMonster.h"
#include "player.h"
#include <SDL2/SDL_ttf.h>


player playerer; // biến lưu thông tin người chơi
list_pr *lpr = NULL; // danh sách người chơi để lấy xếp hạng


void loadBackGround();
void loadMouse();
void loadHelp(); // tải ảnh phần hướng dẫn

void drawMouse();
void drawHelp();

void init();
void freeAll();

void loadAudio();

void moveBackground();
SDL_Rect background_clip = {0,0,2360,1544};
//==========================

void init()
{
    
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_ShowCursor(SDL_DISABLE);
    short index_window = 0;
    
    SDL_GetCurrentDisplayMode(index_window,&displayMode);
    window = SDL_CreateWindow("game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,displayMode.w,displayMode.h,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    
    s = (ship*)malloc(sizeof(ship));
    lpr = (list_pr*)malloc(sizeof(list_pr));
    
    initListPr(lpr);
    //tên người chơi :
    strcpy(playerer.name,"con cet 30 cm");
    // playerer.name = "con cet 30 cm";
    playerer.score = 0;
    playerer.hp = 3; // khởi tạo mặc định :)) quên làm initPlayer

    loadFile(lpr);

    loadAudio();
    Mix_VolumeChunk(hit, MIX_MAX_VOLUME/2);  //chỉnh âm luọng của hit
    Mix_VolumeChunk(shot, MIX_MAX_VOLUME/3);  //chỉnh âm luọng của shot

    initShip(s);
    set_clip();
    loadBackGround();  
    loadMouse();
    loadHelp();
    if (initMenu() != 0)
    {
        printf("loi!! %s\n",SDL_GetError());
    }
    
}

void moveBackground()
{
    SDL_Rect renderquad1={background_clip.x,background_clip.y,background_clip.w,background_clip.h};
    SDL_RenderCopy(renderer,background,NULL,&renderquad1);

    SDL_Rect renderquad2={background_clip.x,background_clip.y-displayMode.h,background_clip.w,background_clip.h};
    SDL_RenderCopy(renderer,background,NULL,&renderquad2);
    background_clip.y+=1;
    if(background_clip.y>=displayMode.h)
    {
        background_clip.y=0;
    }
}
void loadMouse()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image\\mouse.png");
    if(surface != NULL){
        mouse = SDL_CreateTextureFromSurface(renderer,surface);
        if(mouse == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }else{
            SDL_RenderCopy(renderer,mouse,NULL,NULL);
            SDL_FreeSurface(surface);
        }   
    }else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}
void loadBackGround()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image\\background2.png");
    if(surface != NULL){
        background = SDL_CreateTextureFromSurface(renderer,surface);
        if(background == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }else{
                SDL_RenderCopy(renderer,background,NULL,NULL);
                SDL_FreeSurface(surface);
        
            } 
    }
     else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}   

void loadHelp()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image\\help.png");
    if(surface != NULL){
        background_help = SDL_CreateTextureFromSurface(renderer,surface);
        if(background_help == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }else{
            SDL_RenderCopy(renderer,background_help,NULL,NULL);
            SDL_FreeSurface(surface);
        }   
    }else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}

// void drawBackGround(int cur)
// {
//     SDL_RenderCopy(renderer,background,&background_clip[cur],NULL);
// }
void drawHelp()
{
    SDL_RenderCopy(renderer,background_help,NULL,NULL);

    // Vẽ nút bắt đầu
    SDL_Rect startRect = { 1200, 750, 200, 50 };
    SDL_RenderCopy(renderer, startButton, NULL, &startRect);

    // Vẽ nút thoát
    SDL_Rect backRect = { 200, 750, 200, 50 };
    SDL_RenderCopy(renderer, backButton, NULL, &backRect);

    SDL_GetMouseState(&mouseX,&mouseY);
    if ( mouseX >= 1200 && mouseX <= 1400 && mouseY >= 750 && mouseY <= 800)
    {
        // Vẽ nút bắt đầu
        SDL_RenderCopy(renderer, startButton2, NULL, &startRect);
    }
    if( mouseX >= 200 && mouseX <= 400 && mouseY >= 750 && mouseY <= 800)
    {
        SDL_RenderCopy(renderer, backButton2, NULL, &backRect);
    }

}
void drawMouse()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect rectMouse = 
    {
        mouseX,mouseY,100,100
    };
    SDL_RenderCopy(renderer,mouse,NULL,&rectMouse);
}
// cần viết thêm
void freeAll()
{
    freeBullets(); //giải phóng danh sách đạn người chơi
    freeList(lm); // giải phóng list quái vật
    freeBulletMonster();
    freeListPr(lpr); // giải phóng list người chơi
    SDL_DestroyWindow(window); // giải phóng window
    SDL_DestroyRenderer(renderer); // giải phóng renderer
    SDL_DestroyTexture(s->texture); // giải phóng texture tàu
    SDL_DestroyTexture(background); // giải phóng texture background
    Mix_FreeChunk(Menu);
    Mix_FreeChunk(BGM);
    Mix_FreeChunk(Boss);
    Mix_FreeChunk(hit);
    Mix_FreeChunk(dead);
    Mix_FreeChunk(shot);
    Mix_FreeChunk(eatHp);
    Mix_CloseAudio();
    SDL_Quit();
}

void loadAudio(){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    // Load và phát nhạc nền
    Menu = Mix_LoadWAV("audio/Menu.wav");
    BGM = Mix_LoadWAV("audio/bgm.wav");
    Boss = Mix_LoadWAV("audio/BossMusic2.wav");
    hit = Mix_LoadWAV("audio/SE_enemy_vanish.wav");
    dead = Mix_LoadWAV("audio/SE_dead.wav");
    shot = Mix_LoadWAV("audio/SE_shot.wav");
    eatHp = Mix_LoadWAV("audio/SE_powerup.wav");

    if (Menu == NULL || BGM == NULL || Boss == NULL || hit == NULL || dead == NULL || eatHp == NULL){
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}