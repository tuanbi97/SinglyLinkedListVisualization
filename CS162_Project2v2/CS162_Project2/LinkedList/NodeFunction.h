#ifndef _NODEFUNCTION_H_
#define _NODEFUNCTION_H_
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
#include "TextFunction.h"
#include "ArrowFunction.h"
#include "ScreenDef.h"
#define DEFAULT_NODE_SIZE 100
using namespace std;
class Node{ 
private:
	int x, y, w;
	SDL_Texture *TextureNode;
	SDL_Texture *TextureCircle;
	string data;
	Text TEXT;
	Arrow pArrow;
	Node *pNext;
public:
	void LoadNode(SDL_Renderer *(&Renderer), string s);
	void SetNode(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, int W);
	void SetConnect(SDL_Renderer *(&Renderer), SDL_Texture *Erase, Node *q);
	void SetDisconnect(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void StopShowNode(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void StopShowArrow(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int state);
	void AnimationNodeAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y,int W);
	void AnimationNodeDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void AnimationConnect(SDL_Renderer *(&Renderer), SDL_Texture *Erase, Node *q);
	void AnimationDisconnect(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void AnimationNodeMove(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, Node *pPrev);
	void AnimationCircle(SDL_Renderer *(&Renderer), SDL_Texture *Erase, Node *q);
	int GetX();
	int GetY();
	int GetW();
	Node *GetpNext();
	string GetData();
	void SetpNext(Node *p);
	void Close();
};
#endif