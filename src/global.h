#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <unistd.h>

#define MAX_BULLET 50

int mouseX = 0, mouseY = 0;
bool gameOver = true;
bool sound = true;
const char *pathFont = "fonts/Minecraft.ttf";

SDL_Window *window;
SDL_Renderer *renderer;
SDL_DisplayMode displayMode;


SDL_Texture *background = NULL;
SDL_Texture *background_menu = NULL;
SDL_Texture *background_help = NULL;

SDL_Texture* mouse = NULL;
SDL_Texture* heart[5];
SDL_Texture* buff = NULL;
SDL_Texture* buff2 = NULL;
SDL_Texture* shield = NULL;

SDL_Texture* menuObj1 = NULL; // tàu quái màu xanh
SDL_Texture* menuObj2 = NULL; // thiên thạch

SDL_Texture* startButton = NULL;
SDL_Texture* helpButton = NULL;
SDL_Texture* quitButton = NULL;
SDL_Texture* backButton = NULL;
SDL_Texture* backButton2 = NULL;
SDL_Texture* startButton2 = NULL;
SDL_Texture* helpButton2 = NULL;
SDL_Texture* quitButton2 = NULL;

SDL_Texture* pause_01  = NULL;
SDL_Texture* pause_00  = NULL;

SDL_Texture* pause_10 = NULL;
SDL_Texture* pause_11 = NULL;

SDL_Texture* pause_21 = NULL;
SDL_Texture* pause_20 = NULL;

SDL_Texture* pause_31 = NULL;
SDL_Texture* pause_30 = NULL;

SDL_Texture* pause_41 = NULL;
SDL_Texture* pause_40 = NULL;


Mix_Chunk* Menu = NULL;
Mix_Chunk* BGM = NULL;
Mix_Chunk* Boss = NULL;
Mix_Chunk* hit = NULL;
Mix_Chunk* dead = NULL;
Mix_Chunk* shot = NULL;
Mix_Chunk* eatHp = NULL;
