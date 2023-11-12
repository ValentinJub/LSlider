#ifndef HEADERS_H
#define HEADERS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "stdio.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
SDL_Surface* loadSurface(std::string path);
SDL_Texture* loadTexture(std::string path);
void close();

#endif
