#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "global.h"
enum TEXT_COLOR{
    WHITE,RED,BLACK
};
struct text
{
    const char* value;
    int x;
    int y;
    int w;
    int h;
    TTF_Font *font;
    SDL_Texture* texture;
};
typedef struct text text;
int checkText(text object1);
void initText(text *t); // khởi tạo text
void loadText(int size, text *t, const char * path, SDL_Color color); // font và size
void setPosText(int x, int y, text *t); // set vị trí cho text
void setText(const char *value,text *t); // set giá trị cho text
void drawText(text *t); // vẽ text lên màn hình
SDL_Color getColor(enum TEXT_COLOR color); // lấy màu từ enum 
//=================================================================

void initText(text *t)
{
    t->value = "";
    t->x = 0;
    t->y = 0;
    t->w = 0;
    t->h = 0;
    t->font = NULL;
    t->texture = NULL;
}

void loadText(int size, text *t, const char * path, SDL_Color color)
{ 
    if(t->texture != NULL)
    {
        SDL_DestroyTexture(t->texture);
        t->texture = NULL;
    }
    if(t->font != NULL)
    {
        TTF_CloseFont(t->font);
        t->font = NULL;
    }
    TTF_Font *font = TTF_OpenFont(path,size);
    t->font = font;
    SDL_Surface *surface = TTF_RenderText_Solid(t->font,t->value,color);
    if(surface != NULL)
    {
        t->w = surface->w;
        t->h = surface->h;
        t->texture = SDL_CreateTextureFromSurface(renderer,surface);
    }
    SDL_FreeSurface(surface);
}

void setPosText(int x, int y, text *t)
{
    t->x = x;
    t->y = y;
}

void setText(const char *value,text *t)
{
    t->value = value;
}

void drawText(text *t)
{
    SDL_Rect dstrect = { t->x, t->y, t->w, t->h };
    SDL_RenderCopy(renderer, t->texture, NULL, &dstrect);
}

SDL_Color getColor(enum TEXT_COLOR color)
{
    SDL_Color c ;

    if(color == 0)
    {
        c.r = 255;
        c.g = 255;
        c.b = 255;
        c.a = 255;
    }else if(color == 1)
    {
        c.r = 255;
        c.g = 0;
        c.b = 0;
        c.a = 255;
    }
    else if(color == 2)
    {
        c.r = 0;
        c.g = 0;
        c.b = 0;
        c.a = 255;
    }
    else{
        c.r = 255;
        c.g = 255;
        c.b = 255;
        c.a = 255;
    }
    return c;
}
int checkText(text object1){
    if(mouseX >= object1.x && mouseX <= object1.x + object1.w
    && mouseY >= object1.y && mouseY <= object1.y + object1.h){
        return true;
    }
    return false;
}