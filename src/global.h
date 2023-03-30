#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define MAX_BULLET 1000

// const int WIDTH = 5000, HEIGHT = 1000;

int mouseX = 0, mouseY = 0;


SDL_Window *window;
SDL_Renderer *renderer;
SDL_Renderer *renderer_bullet;
SDL_Texture *background = NULL;
SDL_mutex *mutex_bullet;



