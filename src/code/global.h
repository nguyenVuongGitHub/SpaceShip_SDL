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
const char *pathFont = "fonts/Minecraft.ttf";

// chung
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

bool hasAudio = true;
SDL_Texture* soundOn_texture = NULL;
SDL_Texture* soundOff_texture = NULL;
// menu
SDL_Texture* startButton = NULL;
SDL_Texture* helpButton = NULL;
SDL_Texture* quitButton = NULL;
SDL_Texture* backButton = NULL;
SDL_Texture* backButton2 = NULL;
SDL_Texture* startButton2 = NULL;
SDL_Texture* helpButton2 = NULL;
SDL_Texture* quitButton2 = NULL;
SDL_Texture* menuObj1 = NULL; // tàu quái màu xanh
SDL_Texture* menuObj2 = NULL; // thiên thạch
// help
SDL_Texture* mouseMove = NULL;
SDL_Texture* clickMouse = NULL;
SDL_Texture* esc = NULL;


// audio
Mix_Chunk* Menu = NULL;
Mix_Chunk* BGM = NULL;
Mix_Chunk* Boss = NULL;
Mix_Chunk* hit = NULL;
Mix_Chunk* dead = NULL;
Mix_Chunk* shot = NULL;
Mix_Chunk* eatHp = NULL;
Mix_Chunk* gameOverSong = NULL;