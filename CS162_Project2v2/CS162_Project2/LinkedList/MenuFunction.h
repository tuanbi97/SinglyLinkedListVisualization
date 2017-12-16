#ifndef MENUFUNCTION
#define MENUFUNCTION
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
#include "ListFunction.h"
class IOTab{
private:
	SDL_Texture *IOHeader;
	SDL_Texture *IOScreen;
	TTF_Font *Font;
	string InputText, OutputText;
public:
	void Init(SDL_Renderer *(&Renderer));
	void AnimationAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void ShowText(SDL_Renderer *(&Renderer),SDL_Texture *Erase, bool CheckIO);
	void StopShowText(SDL_Renderer *(&Renderer),SDL_Texture *Erase, bool CheckIO);
	void InputMode(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void OutputMode(SDL_Renderer *(&Renderer), SDL_Texture *Erase, string s);
	bool CheckOnclick(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int x, int y);
	string GetInput();
	void Close();
};
class Controller{
private:
	SDL_Texture *PlayButton;
	SDL_Texture *NextButton;
	SDL_Texture *PrevButton;
	SDL_Texture *PlayButtonOnclick;
	SDL_Texture *NextButtonOnclick;
	SDL_Texture *PrevButtonOnclick;
public:
	void Init(SDL_Renderer *(&Renderer));
	void AnimationAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void AnimationDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void PlayOn(SDL_Renderer *(&Renderer));
	void NextOn(SDL_Renderer *(&Renderer));
	void PrevOn(SDL_Renderer *(&Renderer));
	void NextOff(SDL_Renderer *(&Renderer));
	void PrevOff(SDL_Renderer *(&Renderer));
	void Close();
};
class InsertMenu{
private:
	SDL_Texture *InsertButton;
	SDL_Texture *HeadButton;
	SDL_Texture *TailButton;
	SDL_Texture *PositionButton;
	
	SDL_Texture *InsertButtonOnclick;
	SDL_Texture *HeadButtonOnclick;
	SDL_Texture *TailButtonOnclick;
	SDL_Texture *PositionButtonOnclick;
	TTF_Font *Font;
	int x, y;
	string InputPos;
public:
	void Init(SDL_Renderer *(&Renderer));
	void AnimationAppearInsertButton(SDL_Renderer *(Renderer), SDL_Texture *Erase);
	void AnimationSubMenuAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void AnimationSubMenuDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void ShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, int Color);
	void StopShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	bool InputPosition(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	bool CheckInsertOnclick(SDL_Renderer *(&Renderer), SDL_Texture *Erase, IOTab &IO, LinkedList &List, Controller &ControlAnimation, int x, int y);
	bool CheckHeadOnclick(int x, int y);
	bool CheckTailOnclick(int x, int y);
	bool CheckPositionOnclick(int x, int y);
	void Close();
};
class RemoveMenu{
private:
	SDL_Texture *RemoveButton;
	SDL_Texture *HeadButton;
	SDL_Texture *TailButton;
	SDL_Texture *PositionButton;
	
	SDL_Texture *RemoveButtonOnclick;
	SDL_Texture *HeadButtonOnclick;
	SDL_Texture *TailButtonOnclick;
	SDL_Texture *PositionButtonOnclick;
	TTF_Font *Font;
	int x, y;
	string InputPos;
public:
	void Init(SDL_Renderer *(&Renderer));
	void AnimationAppearRemoveButton(SDL_Renderer *(Renderer), SDL_Texture *Erase);
	void AnimationSubMenuAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void AnimationSubMenuDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void ShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, int Color);
	void StopShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	bool InputPosition(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	bool CheckRemoveOnclick(SDL_Renderer *(&Renderer), SDL_Texture *Erase, IOTab &IO, LinkedList &List, Controller &ControlAnimation, int x, int y);
	bool CheckHeadOnclick(int x, int y);
	bool CheckTailOnclick(int x, int y);
	bool CheckPositionOnclick(int x, int y);
	void Close();
};
class FindMenu{
private:
	SDL_Texture *FindButton;
	SDL_Texture *FindButtonOnclick;
	
	SDL_Texture *LargerButton;
	SDL_Texture *SmallerButton;
	
	SDL_Texture *LargerButtonOnclick;
	SDL_Texture *SmallerButtonOnclick;
public:
	void Init(SDL_Renderer *(&Renderer));
	void AnimationAppearFindButton(SDL_Renderer *(Renderer), SDL_Texture *Erase);
	void AnimationSubMenuAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	void AnimationSubMenuDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase);
	bool CheckFindOnclick(SDL_Renderer *(&Renderer), SDL_Texture *Erase, IOTab &IO, LinkedList &List, Controller &ControlAnimation, int x, int y);
	bool CheckSmallerOnclick(int x, int y);
	bool CheckLargerOnclick(int x, int y);
	void Close();
};
#endif