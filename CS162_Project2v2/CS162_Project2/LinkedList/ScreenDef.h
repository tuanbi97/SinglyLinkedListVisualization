#ifndef _SCREENDEF_H_
#define _SCREENDEF_H_
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#define ScreenWidth 1200
#define ScreenHeight 680
#define PI 3.1415926535
#define ARROW_NODE_SPACING 12
using namespace std;
SDL_Texture *LoadTexture(string s, SDL_Renderer *(&Renderer));
SDL_Texture *LoadTextTexture(string s, SDL_Color TextColor,TTF_Font *Font, SDL_Renderer *(&Renderer), int &a, int &b);
bool AnimationController(bool &Pause, SDL_Renderer *(&Renderer), SDL_Texture *Erase);
double Distance(int x1, int y1, int x2, int y2);
double Angle(int x1, int y1, int x2, int y2);
int Compare(string a, string b);
#endif