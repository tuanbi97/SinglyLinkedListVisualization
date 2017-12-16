#ifndef _ARROWFUNCTION_H_
#define _ARROWFUNCTION_H_
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
#define DEFAULT_ARROW_TAIL_WIDTH ScreenWidth/30
//#define DEFAULT_ARROW_TAIL_HEIGHT ScreenHeight/29
#define DEFAULT_ARROW_TAIL_HEIGHT ScreenHeight/50
//#define DEFAULT_ARROW_HEAD_WIDTH ScreenWidth/69
//#define DEFAULT_ARROW_HEAD_HEIGHT ScreenHeight/15
#define DEFAULT_ARROW_HEAD_WIDTH ScreenWidth/80
#define DEFAULT_ARROW_HEAD_HEIGHT ScreenHeight/23
using namespace std;
class Arrow{
private:
	int xs, ys, xt, yt;
	int TailHeight;
	int HeadHeight;
	int HeadWidth;
	SDL_Texture *ArrowHead;
	SDL_Texture *ArrowTail;
public:
	void LoadArrow(SDL_Renderer *(&Renderer));
	void SetPos(SDL_Renderer *(&Renderer),SDL_Texture *Erase, double x1, double y1, double x2, double y2, double NodeSize);
	void StopShowArrow(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	//void AnimationArrowAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double x1, double y1, double x2, double y2, double NodeSize);
	//void AnimationArrowDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double NodeSize);
	void Close();
};
#endif