#ifndef _LISTFUNCTION_H_
#define _LISTFUNCTION_H_
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
#include "NodeFunction.h"
#include "ScreenDef.h"
using namespace std;
class LinkedList{
private:
	int n;
	double NodeSize;
	Node *pHead;
public:
	void Init();
	void InputFromFile(SDL_Renderer *(&Renderer));
	void InputRandom(SDL_Renderer *(&Renderer));
	void Save();
	Node *GetpHead();
	int GetNodeSize();
	void SetPosList(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double x, double y, Node *pPrev, Node *pEnd);
	void Resize(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double NewSize, Node *pEnd);
	void AnimationMoveList(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double x, double y, Node *pPrev, Node *pEnd);
	void AnimationResizeList(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double NewSize, Node *pEnd);
	void AnimationSetList(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	//void AnimationInsert(SDL_Renderer *(&Renderer), SDL_Texture *Erase, string str, int pos);
	bool AnimationInsert2(SDL_Renderer *(&Renderer), SDL_Texture *Erase, string str, int vt, int pos, bool Pause, Node *p, Node *pPrev);
	//void AnimationRemove(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int pos);
	bool AnimationRemove2(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int vt, int pos, bool Pause, Node *p, Node *pPrev);
	bool AnimationFind(SDL_Renderer *(&renderer), SDL_Texture *Erase, string DataIn, int sign, bool Pause, Node *p, Node *pPrev, string &Ret);
	bool CheckInList(int x, int y);
	void AnimationZoomIn(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int x, int y);
	void Close();
};
#endif