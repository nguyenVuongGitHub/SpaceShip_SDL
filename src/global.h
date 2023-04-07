#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <unistd.h>

#define MAX_BULLET 1000

int widthScreen;
int heightScreen;

int mouseX = 0, mouseY = 0;
bool gameOver;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_DisplayMode displayMode;

SDL_Renderer *renderer_bullet;
SDL_mutex *mutex_bullet;
SDL_Texture *background = NULL;
SDL_Texture *background_menu = NULL;
SDL_Texture *background_help = NULL;

SDL_Texture* mouse = NULL;
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



