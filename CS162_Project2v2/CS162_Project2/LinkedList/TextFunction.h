#ifndef _TEXT_FUNCTION_H_
#define _TEXT_FUNCTION_H_
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include "ScreenDef.h"
//#define DEFAULT_TEXT_COLOR 0x36E5E7 //Xanh nhat
//#define DEFAULT_TEXT_COLOR 0x1A59A8 // Xanh dam
#define DEFAULT_TEXT_COLOR 0xFFB02C // Cam
#define DEFAULT_FONT_SIZE 200
using namespace std;
class Text{
private:
	int a, b;
	SDL_Texture *TextTexture;
public:
	void LoadText(SDL_Renderer *(&Renderer), string s, int color, string dir);
	void SetText(SDL_Renderer *(&Renderer), int x, int y, int w, int h);
	int GetHeight();
	int GetWidth();
	void Close();
};
#endif