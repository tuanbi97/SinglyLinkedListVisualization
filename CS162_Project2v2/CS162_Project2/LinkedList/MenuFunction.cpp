#include "MenuFunction.h"
void IOTab::Init(SDL_Renderer *(&Renderer)){
	IOHeader = LoadTexture("Menu/IObar.png", Renderer);
	IOScreen = LoadTexture("Menu/IO.png", Renderer);
	SDL_SetTextureBlendMode(IOScreen, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(IOScreen, 150);
	Font = TTF_OpenFont("Font/ProFontWindows.ttf", 30);
	InputText = "";
	OutputText = "";
}
void IOTab::AnimationAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = 45;
	double s0 = -45;
	double st = s0;
	double v0 = 400;
	double vt = v0;
	double a = -v0*v0/(s*2.0);
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect = {st, 0, 45, 141};
		SDL_RenderCopy(Renderer, IOHeader, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect = {0, 0, 45, 141};
	SDL_RenderCopy(Renderer, IOHeader, NULL, &Rect);
	SDL_RenderPresent(Renderer);

	s = 366;
	s0 = -366;
	st = s0;
	v0 = 600;
	vt = v0;
	a = -v0*v0/(2.0*s);
	t = clock();
	while (vt > 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 0; Rect.y = 0; Rect.w = 366 + st + 1; Rect.h = 141;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = st; Rect.y = 0; Rect.w = 366; Rect.h = 141;
		SDL_RenderCopy(Renderer, IOScreen, NULL, &Rect);
		Rect.x = 0; Rect.y = 0; Rect.w = 45; Rect.h = 141;
		SDL_RenderCopy(Renderer, IOHeader, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect2 = {0, 0, 366, 141};
	SDL_SetTextureBlendMode(IOScreen, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(IOScreen, 150);
	/*SDL_RenderCopy(Renderer, IOScreen, NULL, &Rect2);
	Rect2.x = 0; Rect2.y = 0; Rect2.w = 45; Rect2.h = 141;
	SDL_RenderCopy(Renderer, IOHeader, NULL, &Rect);*/	
	SDL_RenderPresent(Renderer);
}
void IOTab::ShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase, bool CheckIO){
	if (CheckIO){
		SDL_Color color = {255, 255, 255};
		int a, b;
		SDL_Texture *Text = LoadTextTexture(InputText, color, Font, Renderer, a, b);
		SDL_Rect Rect = {70, 21, a, b};
		SDL_RenderCopy(Renderer, Text, NULL, &Rect);
		SDL_RenderPresent(Renderer);
		SDL_DestroyTexture(Text);
	}
	else{
		SDL_Color color = {255, 255, 255};
		int a, b;
		SDL_Texture *Text = LoadTextTexture(OutputText, color, Font, Renderer, a, b);
		SDL_Rect Rect = {70, 94, a, b};
		SDL_RenderCopy(Renderer, Text, NULL, &Rect);
		SDL_RenderPresent(Renderer);
		SDL_DestroyTexture(Text);
	}
}
void IOTab::StopShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase, bool checkIO){
	if (checkIO){
		SDL_Color color = {255, 255, 255};
		int a, b;
		SDL_Texture *Text = LoadTextTexture(InputText, color, Font, Renderer, a, b);
		SDL_Rect Rect = {70, 21, a, b};
		//cout<<InputText.length()<<" "<<a<<" "<<b<<endl;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		SDL_RenderCopy(Renderer, IOScreen, &Rect, &Rect);
		SDL_DestroyTexture(Text);
	}
	else{
		SDL_Color color = {255, 255, 255};
		int a, b;
		SDL_Texture *Text = LoadTextTexture(OutputText, color, Font, Renderer, a, b);
		SDL_Rect Rect = {70, 90, a, b};
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		SDL_RenderCopy(Renderer, IOScreen, &Rect, &Rect);
		SDL_DestroyTexture(Text);
	}
	SDL_RenderPresent(Renderer);
}
void IOTab::InputMode(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	SDL_Event e;
	bool Stop = false;
	SDL_StartTextInput();
	while (Stop == false){
		while (SDL_PollEvent(&e) != NULL){
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_BACKSPACE){
					int len = InputText.length();
					if (len > 0){
						StopShowText(Renderer, Erase, true);
						InputText.pop_back();
						len = InputText.length();
						if (len > 0) ShowText(Renderer, Erase, true);
					}
				}
				if (e.key.keysym.sym == SDLK_RETURN){
					Stop = true;
					break;
				}
			}
			else
			if (e.type == SDL_TEXTINPUT){
				int len = InputText.length();
				if (len < 9){
					if (len > 0) StopShowText(Renderer, Erase, true);
					InputText += e.text.text;
					ShowText(Renderer, Erase, true);
				}
			}
			else
			if (e.type == SDL_MOUSEBUTTONUP){
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x > 366 || y > 70){
					Stop = true;
					break;
				}
			}
		}
	}
	SDL_StopTextInput();
}
void IOTab::OutputMode(SDL_Renderer *(&Renderer), SDL_Texture *Erase, string s){
	SDL_Color color = {255, 255, 255};
	int a, b;
	if (OutputText.length() > 0) StopShowText(Renderer, Erase, false);
	OutputText = s;
	if (s.length() > 0) ShowText(Renderer, Erase, false);
}
bool IOTab::CheckOnclick(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int x, int y){
	if (x <= 366 && y <= 70){
		SDL_Texture *tmp = LoadTexture("Menu/IObarOnclick.png", Renderer);
		SDL_Rect Rect = {0, 0, 45, 70};
		SDL_RenderCopy(Renderer, tmp, &Rect, &Rect);
		SDL_RenderPresent(Renderer);
		SDL_DestroyTexture(tmp);
		InputMode(Renderer, Erase);
		SDL_Rect Rect2 = {0, 0, 45, 141};
		SDL_RenderCopy(Renderer, IOHeader, NULL, &Rect2);
		SDL_RenderPresent(Renderer);
		return true;
	}
	else return false;
}
string IOTab::GetInput(){
	return InputText;
}
void IOTab::Close(){
	SDL_DestroyTexture(IOHeader);
	SDL_DestroyTexture(IOScreen);
	TTF_CloseFont(Font);
}
void Controller::Init(SDL_Renderer *(&Renderer)){
	PlayButton = LoadTexture("Menu/PlayButton.png", Renderer);
	NextButton = LoadTexture("Menu/NextButton.png", Renderer);
	PrevButton = LoadTexture("Menu/PrevButton.png", Renderer);
	PlayButtonOnclick = LoadTexture("Menu/PlayButtonOnclick.png", Renderer);
	NextButtonOnclick = LoadTexture("Menu/NextButtonOnclick.png", Renderer);
	PrevButtonOnclick = LoadTexture("Menu/PrevButtonOnclick.png", Renderer);
}
void Controller::AnimationAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = -80;
	double s0 = 760;
	double st = s0;
	double v0 = -400;
	double vt = v0;
	double a = -v0*v0/(2.0*s);
	clock_t t = clock();
	while (vt < 0){
		double time = (1.0*clock() - t) / CLOCKS_PER_SEC;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 490; Rect.y = 600; Rect.w = 220; Rect.h = 80;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 490; Rect.y = st - 40; Rect.w = 70; Rect.h = 40;
		SDL_RenderCopy(Renderer, PrevButton, NULL, &Rect);
		Rect.x = 560; Rect.y = st - 80; Rect.w = 80; Rect.h = 80;
		SDL_RenderCopy(Renderer, PlayButton, NULL, &Rect);
		Rect.x = 640; Rect.y = st - 40; Rect.w = 70; Rect.h = 40;
		SDL_RenderCopy(Renderer, NextButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 490; Rect.y = 600; Rect.w = 220; Rect.h = 80;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	Rect.x = 490; Rect.y = 640; Rect.w = 70; Rect.h = 40;
	SDL_RenderCopy(Renderer, PrevButton, NULL, &Rect);
	Rect.x = 560; Rect.y = 600; Rect.w = 80; Rect.h = 80;
	SDL_RenderCopy(Renderer, PlayButton, NULL, &Rect);
	Rect.x = 640; Rect.y = 640; Rect.w = 70; Rect.h = 40;
	SDL_RenderCopy(Renderer, NextButton, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void Controller::AnimationDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = 80;
	double s0 = 600;
	double st = s0;
	double v0 = 400;
	double vt = v0;
	double a = -v0*v0/(2.0*s);
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*clock() - t) / CLOCKS_PER_SEC;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 490; Rect.y = 600; Rect.w = 220; Rect.h = 80;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 490; Rect.y = st + 40; Rect.w = 70; Rect.h = 40;
		SDL_RenderCopy(Renderer, PrevButton, NULL, &Rect);
		Rect.x = 560; Rect.y = st; Rect.w = 80; Rect.h = 80;
		SDL_RenderCopy(Renderer, PlayButton, NULL, &Rect);
		Rect.x = 640; Rect.y = st + 40; Rect.w = 70; Rect.h = 40;
		SDL_RenderCopy(Renderer, NextButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 490; Rect.y = 600; Rect.w = 220; Rect.h = 80;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	SDL_RenderPresent(Renderer);
}
void Controller::PlayOn(SDL_Renderer *(&Renderer)){
	SDL_Rect Rect = {560, 600, 80, 80};
	SDL_RenderCopy(Renderer, PlayButtonOnclick, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void Controller::NextOn(SDL_Renderer *(&Renderer)){
	SDL_Rect Rect = {640, 640, 70, 40};
	SDL_RenderCopy(Renderer, NextButtonOnclick, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void Controller::PrevOn(SDL_Renderer *(&Renderer)){
	SDL_Rect Rect = {490, 640, 70, 40};
	SDL_RenderCopy(Renderer, PrevButtonOnclick, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void Controller::NextOff(SDL_Renderer *(&Renderer)){
	SDL_Rect Rect = {640, 640, 70, 40};
	SDL_RenderCopy(Renderer, NextButton, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void Controller::PrevOff(SDL_Renderer *(&Renderer)){
	SDL_Rect Rect = {490, 640, 70, 40};
	SDL_RenderCopy(Renderer, PrevButton, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void Controller::Close(){
	SDL_DestroyTexture(PlayButton);
	SDL_DestroyTexture(PrevButton);
	SDL_DestroyTexture(NextButton);
	SDL_DestroyTexture(PlayButtonOnclick);
	SDL_DestroyTexture(PrevButtonOnclick);
	SDL_DestroyTexture(NextButtonOnclick);
}
void InsertMenu::Init(SDL_Renderer *(&Renderer)){
	InsertButton = LoadTexture("Menu/Insert.png", Renderer);
	HeadButton = LoadTexture("Menu/Head.png", Renderer);
	TailButton = LoadTexture("Menu/Tail.png", Renderer);
	PositionButton = LoadTexture("Menu/Position.png", Renderer);

	InsertButtonOnclick = LoadTexture("Menu/InsertOnclick.png", Renderer);
	HeadButtonOnclick = LoadTexture("Menu/HeadOnclick.png", Renderer);
	TailButtonOnclick = LoadTexture("Menu/TailOnclick.png", Renderer);
	PositionButtonOnclick = LoadTexture("Menu/PositionOnclick.png", Renderer);

	Font = TTF_OpenFont("Font/ProFontWindows.ttf", 24);
	x = 0; y = 0;
	InputPos = "";
}
void InsertMenu::AnimationAppearInsertButton(SDL_Renderer *(Renderer), SDL_Texture *Erase){
	double s = 45;
	double s0 = -45;
	double st = s0;
	double v0 = 500;
	double vt = v0;
	double a = -v0*v0/(s*2.0);
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2.0;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 45;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 369; Rect.y = st; Rect.w = 45; Rect.h = 45;
		SDL_RenderCopy(Renderer, InsertButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 45;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 45;
	SDL_RenderCopy(Renderer, InsertButton, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void InsertMenu::AnimationSubMenuAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = 45;
	double s0 = -45;
	double st = s0;
	double v0 = 500;
	double vt = v0;
	double a = -(v0*v0)/(2.0*s);
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 45;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 417; Rect.y = st; Rect.w = 89; Rect.h = 45;
		SDL_RenderCopy(Renderer, HeadButton, NULL, &Rect);
		Rect.x = 509; Rect.y = st; Rect.w = 89; Rect.h = 45;
		SDL_RenderCopy(Renderer, TailButton, NULL, &Rect);
		Rect.x = 601; Rect.y = st; Rect.w = 261; Rect.h = 45;
		SDL_RenderCopy(Renderer, PositionButton, NULL, &Rect);
		if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, st + 12, 0xFFFFFF);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 45;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	Rect.x = 417; Rect.y = 0; Rect.w = 89; Rect.h = 45;
	SDL_RenderCopy(Renderer, HeadButton, NULL, &Rect);
	Rect.x = 509; Rect.y = 0; Rect.w = 89; Rect.h = 45;
	SDL_RenderCopy(Renderer, TailButton, NULL, &Rect);
	Rect.x = 601; Rect.y = 0; Rect.w = 261; Rect.h = 45;
	SDL_RenderCopy(Renderer, PositionButton, NULL, &Rect);
	if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, 12, 0xFFFFFF);
	SDL_RenderPresent(Renderer);
}
void InsertMenu::AnimationSubMenuDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = -45;
	double s0 = 0;
	double st = s0;
	double v0 = -500;
	double vt = v0;
	double a = -(v0*v0)/(2.0*s);
	clock_t t = clock();
	while (vt < 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 45;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 417; Rect.y = st; Rect.w = 89; Rect.h = 45;
		SDL_RenderCopy(Renderer, HeadButton, NULL, &Rect);
		Rect.x = 509; Rect.y = st; Rect.w = 89; Rect.h = 45;
		SDL_RenderCopy(Renderer, TailButton, NULL, &Rect);
		Rect.x = 601; Rect.y = st; Rect.w = 261; Rect.h = 45;
		SDL_RenderCopy(Renderer, PositionButton, NULL, &Rect);
		if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, st + 12, 0xFFFFFF);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 45;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	SDL_RenderPresent(Renderer);
}
void InsertMenu::ShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, int Color){
	SDL_Color color;
	color.r = Color % 256;
	color.g = (Color / 256) % 256;
	color.b = Color / 65536;
	int a, b;
	SDL_Texture *tmp = LoadTextTexture(InputPos, color, Font, Renderer, a, b);
	SDL_Rect Rect = {X, Y, a, b};
	SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
	SDL_RenderPresent(Renderer);
	SDL_DestroyTexture(tmp);
}
void InsertMenu::StopShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	SDL_Rect Rect;
	Rect.x = 601; Rect.y = 0; Rect.w = 261; Rect.h = 45;
	SDL_RenderCopy(Renderer, PositionButtonOnclick, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
bool InsertMenu::InputPosition(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	SDL_Event e;
	bool Stop = false, DO = true;
	SDL_StartTextInput();
	while (Stop == false){
		while (SDL_PollEvent(&e) != NULL){
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_BACKSPACE){
					int len = InputPos.length();
					if (len > 0){
						StopShowText(Renderer, Erase);
						InputPos.pop_back();
						len = InputPos.length();
						if (len > 0) ShowText(Renderer, Erase, 731, 12, 0);
					}
				}
				if (e.key.keysym.sym == SDLK_RETURN){
					DO = true;
					Stop = true;
					break;
				}
			}
			else
			if (e.type == SDL_TEXTINPUT){
				int len = InputPos.length();
				if (len < 3){
					if (len > 0) StopShowText(Renderer, Erase);
					InputPos += e.text.text;
					ShowText(Renderer, Erase, 731, 12, 0);
				}
			}
			else
			if (e.type == SDL_MOUSEBUTTONUP){
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x < 601 || x > 862 || y > 45 || y < 0){
					DO = false;
					Stop = true;
					break;
				}
				else
				if (x >= 812 && x <= 862 && y >= 0 && y <= 45){
					DO = true;
					Stop = true;
					break;
				}
			}
		}
	}
	SDL_StopTextInput();
	return DO;
}
bool InsertMenu::CheckInsertOnclick(SDL_Renderer *(&Renderer), SDL_Texture *Erase, IOTab &IO, LinkedList &List,Controller &ControlAnimation, int x, int y){
	if (x < 369 || x > 414 || y < 0 || y > 45) return false;
	else{
		SDL_Rect Rect; 
		Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 45;
		SDL_RenderCopy(Renderer, InsertButtonOnclick, NULL, &Rect);
		SDL_RenderPresent(Renderer);
		AnimationSubMenuAppear(Renderer, Erase);
		bool Stop = false;
		while (Stop == false){
			SDL_Event e;
			while (SDL_PollEvent(&e) != NULL){
				if (e.type == SDL_MOUSEBUTTONUP){
					SDL_GetMouseState(&x, &y);
					if (CheckHeadOnclick(x, y)){
						Rect.x = 417; Rect.y = 0; Rect.w = 89; Rect.h = 45;
						SDL_RenderCopy(Renderer, HeadButtonOnclick, NULL, &Rect);
						SDL_RenderPresent(Renderer);
						string s = IO.GetInput();
						if (s.length() > 0){
							ControlAnimation.AnimationAppear(Renderer, Erase);
							List.AnimationInsert2(Renderer, Erase, s, 0, 0, true, List.GetpHead(), NULL);	
							ControlAnimation.AnimationDisappear(Renderer, Erase);
							//List.AnimationInsert(Renderer, Erase, s, 0);
						}
						SDL_RenderCopy(Renderer, HeadButton, NULL, &Rect);
						SDL_RenderPresent(Renderer);
					}
					else
					if (CheckTailOnclick(x, y)){
						Rect.x = 509; Rect.y = 0; Rect.w = 89; Rect.h = 45;
						SDL_RenderCopy(Renderer, TailButtonOnclick, NULL, &Rect);
						SDL_RenderPresent(Renderer);
						string s = IO.GetInput();
						if (s.length() > 0){
							ControlAnimation.AnimationAppear(Renderer, Erase);
							List.AnimationInsert2(Renderer, Erase, s, 0, -1, true, List.GetpHead(), NULL);
							ControlAnimation.AnimationDisappear(Renderer, Erase);
							//List.AnimationInsert(Renderer, Erase, s, -1);
						}
						SDL_RenderCopy(Renderer, TailButton, NULL, &Rect);
						SDL_RenderPresent(Renderer);
					}
					else
					if (CheckPositionOnclick(x, y)){
						string InputVal = IO.GetInput();
						if (InputVal.length() > 0){
							Rect.x = 601; Rect.y = 0; Rect.w = 261; Rect.h = 45;
							SDL_RenderCopy(Renderer, PositionButtonOnclick, NULL, &Rect);
							if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, 12, 0);
							SDL_RenderPresent(Renderer);
							if (InputPosition(Renderer, Erase)){
								int pos = 0;
								for (int i = 0; i<InputPos.length(); i++) pos = pos*10 + InputPos[i]-'0';
								ControlAnimation.AnimationAppear(Renderer, Erase);
								List.AnimationInsert2(Renderer, Erase, InputVal, 0, pos, true, List.GetpHead(), NULL);
								ControlAnimation.AnimationDisappear(Renderer, Erase);
								//List.AnimationInsert(Renderer, Erase, InputVal, pos);
							}
							Rect.x = 601; Rect.y = 0; Rect.w = 261; Rect.h = 45;
							SDL_RenderCopy(Renderer, PositionButton, NULL, &Rect);
							if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, 12, 0xFFFFFF);
							SDL_RenderPresent(Renderer);
						}
					}
					else
					if (IO.CheckOnclick(Renderer, Erase, x, y)){
						continue;
					}
					else{
						Stop = true;
						break;
					}
				}
			}
		}
		Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 45;
		SDL_RenderCopy(Renderer, InsertButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
		AnimationSubMenuDisappear(Renderer, Erase);
	}
	return true;
}
bool InsertMenu::CheckHeadOnclick(int x, int y){
	if (x < 417 || x > 506 || y > 45 || y < 0) return false;
	return true;
}
bool InsertMenu::CheckTailOnclick(int x, int y){
	if (x < 509 || x > 598 || y > 45 || y < 0) return false;
	return true;
}
bool InsertMenu::CheckPositionOnclick(int x, int y){
	if (x < 601 || x > 862 || y > 45 || y < 0) return false;
	return true;
}
void InsertMenu::Close(){
	SDL_DestroyTexture(InsertButton);
	SDL_DestroyTexture(HeadButton);
	SDL_DestroyTexture(TailButton);
	SDL_DestroyTexture(PositionButton);
	SDL_DestroyTexture(InsertButtonOnclick);
	SDL_DestroyTexture(HeadButtonOnclick);
	SDL_DestroyTexture(TailButtonOnclick);
	SDL_DestroyTexture(PositionButtonOnclick);
	TTF_CloseFont(Font);
}
void RemoveMenu::Init(SDL_Renderer *(&Renderer)){
	RemoveButton = LoadTexture("Menu/Remove.png", Renderer);
	HeadButton = LoadTexture("Menu/Head.png", Renderer);
	TailButton = LoadTexture("Menu/Tail.png", Renderer);
	PositionButton = LoadTexture("Menu/Position.png", Renderer);

	RemoveButtonOnclick = LoadTexture("Menu/RemoveOnclick.png", Renderer);
	HeadButtonOnclick = LoadTexture("Menu/HeadOnclick.png", Renderer);
	TailButtonOnclick = LoadTexture("Menu/TailOnclick.png", Renderer);
	PositionButtonOnclick = LoadTexture("Menu/PositionOnclick.png", Renderer);

	Font = TTF_OpenFont("Font/ProFontWindows.ttf", 24);
	x = 0; y = 0;
	InputPos = "";
}
void RemoveMenu::AnimationAppearRemoveButton(SDL_Renderer *(Renderer), SDL_Texture *Erase){
	double s = 93;
	double s0 = -45;
	double st = s0;
	double v0 = 500;
	double vt = v0;
	double a = -v0*v0/(s*2.0);
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2.0;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 93;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 369; Rect.y = st; Rect.w = 45; Rect.h = 45;
		SDL_RenderCopy(Renderer, RemoveButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 93;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	Rect.x = 369; Rect.y = 48; Rect.w = 45; Rect.h = 45;
	SDL_RenderCopy(Renderer, RemoveButton, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void RemoveMenu::AnimationSubMenuAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = 93;
	double s0 = -45;
	double st = s0;
	double v0 = 500;
	double vt = v0;
	double a = -(v0*v0)/(2.0*s);
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 93;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 417; Rect.y = st; Rect.w = 89; Rect.h = 45;
		SDL_RenderCopy(Renderer, HeadButton, NULL, &Rect);
		Rect.x = 509; Rect.y = st; Rect.w = 89; Rect.h = 45;
		SDL_RenderCopy(Renderer, TailButton, NULL, &Rect);
		Rect.x = 601; Rect.y = st; Rect.w = 261; Rect.h = 45;
		SDL_RenderCopy(Renderer, PositionButton, NULL, &Rect);
		if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, st + 12, 0xFFFFFF);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 93;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	Rect.x = 417; Rect.y = 48; Rect.w = 89; Rect.h = 45;
	SDL_RenderCopy(Renderer, HeadButton, NULL, &Rect);
	Rect.x = 509; Rect.y = 48; Rect.w = 89; Rect.h = 45;
	SDL_RenderCopy(Renderer, TailButton, NULL, &Rect);
	Rect.x = 601; Rect.y = 48; Rect.w = 261; Rect.h = 45;
	SDL_RenderCopy(Renderer, PositionButton, NULL, &Rect);
	if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, 60, 0xFFFFFF);
	SDL_RenderPresent(Renderer);
}
void RemoveMenu::AnimationSubMenuDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = -93;
	double s0 = 48;
	double st = s0;
	double v0 = -500;
	double vt = v0;
	double a = -(v0*v0)/(2.0*s);
	clock_t t = clock();
	while (vt < 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 93;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 417; Rect.y = st; Rect.w = 89; Rect.h = 45;
		SDL_RenderCopy(Renderer, HeadButton, NULL, &Rect);
		Rect.x = 509; Rect.y = st; Rect.w = 89; Rect.h = 45;
		SDL_RenderCopy(Renderer, TailButton, NULL, &Rect);
		Rect.x = 601; Rect.y = st; Rect.w = 261; Rect.h = 45;
		SDL_RenderCopy(Renderer, PositionButton, NULL, &Rect);
		if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, st + 12, 0xFFFFFF);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 93;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	SDL_RenderPresent(Renderer);
}
void RemoveMenu::ShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, int Color){
	SDL_Color color;
	color.r = Color % 256;
	color.g = (Color / 256) % 256;
	color.b = Color / 65536;
	int a, b;
	SDL_Texture *tmp = LoadTextTexture(InputPos, color, Font, Renderer, a, b);
	SDL_Rect Rect = {X, Y, a, b};
	SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
	SDL_RenderPresent(Renderer);
	SDL_DestroyTexture(tmp);
}
void RemoveMenu::StopShowText(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	SDL_Rect Rect;
	Rect.x = 601; Rect.y = 48; Rect.w = 261; Rect.h = 45;
	SDL_RenderCopy(Renderer, PositionButtonOnclick, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
bool RemoveMenu::InputPosition(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	SDL_Event e;
	bool Stop = false, DO = true;
	SDL_StartTextInput();
	while (Stop == false){
		while (SDL_PollEvent(&e) != NULL){
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_BACKSPACE){
					int len = InputPos.length();
					if (len > 0){
						StopShowText(Renderer, Erase);
						InputPos.pop_back();
						len = InputPos.length();
						if (len > 0) ShowText(Renderer, Erase, 731, 60, 0);
					}
				}
				if (e.key.keysym.sym == SDLK_RETURN){
					DO = true;
					Stop = true;
					break;
				}
			}
			else
			if (e.type == SDL_TEXTINPUT){
				int len = InputPos.length();
				if (len < 3){
					if (len > 0) StopShowText(Renderer, Erase);
					InputPos += e.text.text;
					ShowText(Renderer, Erase, 731, 60, 0);
				}
			}
			else
			if (e.type == SDL_MOUSEBUTTONUP){
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x < 601 || x > 862 || y > 93 || y < 48){
					DO = false;
					Stop = true;
					break;
				}
				else
				if (x >= 812 && x <= 862 && y >= 48 && y <= 93){
					DO = true;
					Stop = true;
					break;
				}
			}
		}
	}
	SDL_StopTextInput();
	return DO;
}
bool RemoveMenu::CheckRemoveOnclick(SDL_Renderer *(&Renderer), SDL_Texture *Erase, IOTab &IO, LinkedList &List, Controller &ControlAnimation, int x, int y){
	if (x < 369 || x > 414 || y < 48 || y > 93) return false;
	else{
		SDL_Rect Rect; 
		Rect.x = 369; Rect.y = 48; Rect.w = 45; Rect.h = 45;
		SDL_RenderCopy(Renderer, RemoveButtonOnclick, NULL, &Rect);
		SDL_RenderPresent(Renderer);
		AnimationSubMenuAppear(Renderer, Erase);
		bool Stop = false;
		while (Stop == false){
			SDL_Event e;
			while (SDL_PollEvent(&e) != NULL){
				if (e.type == SDL_MOUSEBUTTONUP){
					SDL_GetMouseState(&x, &y);
					if (CheckHeadOnclick(x, y)){
						Rect.x = 417; Rect.y = 48; Rect.w = 89; Rect.h = 45;
						SDL_RenderCopy(Renderer, HeadButtonOnclick, NULL, &Rect);
						SDL_RenderPresent(Renderer);
						if (List.GetpHead() != NULL){
							ControlAnimation.AnimationAppear(Renderer, Erase);
							List.AnimationRemove2(Renderer, Erase, 0, 0, true, List.GetpHead(), NULL);
							ControlAnimation.AnimationDisappear(Renderer, Erase);
						}
						//List.AnimationRemove(Renderer, Erase, 0);
						SDL_RenderCopy(Renderer, HeadButton, NULL, &Rect);
						SDL_RenderPresent(Renderer);
					}
					else
					if (CheckTailOnclick(x, y)){
						Rect.x = 509; Rect.y = 48; Rect.w = 89; Rect.h = 45;
						SDL_RenderCopy(Renderer, TailButtonOnclick, NULL, &Rect);
						SDL_RenderPresent(Renderer);
						if (List.GetpHead() != NULL){
							ControlAnimation.AnimationAppear(Renderer, Erase);
							List.AnimationRemove2(Renderer, Erase, 0, -1, true, List.GetpHead(), NULL);
							ControlAnimation.AnimationDisappear(Renderer, Erase);
						}
						//List.AnimationRemove(Renderer, Erase, -1);
						SDL_RenderCopy(Renderer, TailButton, NULL, &Rect);
						SDL_RenderPresent(Renderer);

					}
					else
					if (CheckPositionOnclick(x, y)){
						Rect.x = 601; Rect.y = 48; Rect.w = 261; Rect.h = 45;
						SDL_RenderCopy(Renderer, PositionButtonOnclick, NULL, &Rect);
						if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, 60, 0);
						SDL_RenderPresent(Renderer);
						if (InputPosition(Renderer, Erase)){
							int pos = 0;
							for (int i = 0; i<InputPos.length(); i++) pos = pos*10 + InputPos[i]-'0';
							ControlAnimation.AnimationAppear(Renderer, Erase);
							List.AnimationRemove2(Renderer, Erase, 0, pos, true, List.GetpHead(), NULL);
							ControlAnimation.AnimationDisappear(Renderer, Erase);
							//List.AnimationRemove(Renderer, Erase, pos);
						}
						Rect.x = 601; Rect.y = 48; Rect.w = 261; Rect.h = 45;
						SDL_RenderCopy(Renderer, PositionButton, NULL, &Rect);
						if (InputPos.length() > 0) ShowText(Renderer, Erase, 731, 60, 0xFFFFFF);
						SDL_RenderPresent(Renderer);
					}
					else{
						Stop = true;
						break;
					}
				}
			}
		}
		Rect.x = 369; Rect.y = 48; Rect.w = 45; Rect.h = 45;
		SDL_RenderCopy(Renderer, RemoveButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
		AnimationSubMenuDisappear(Renderer, Erase);
	}
	return true;
}
bool RemoveMenu::CheckHeadOnclick(int x, int y){
	if (x < 417 || x > 506 || y > 93 || y < 48) return false;
	return true;
}
bool RemoveMenu::CheckTailOnclick(int x, int y){
	if (x < 509 || x > 598 || y > 93 || y < 48) return false;
	return true;
}
bool RemoveMenu::CheckPositionOnclick(int x, int y){
	if (x < 601 || x > 862 || y > 93 || y < 48) return false;
	return true;
}
void RemoveMenu::Close(){
	SDL_DestroyTexture(RemoveButton);
	SDL_DestroyTexture(HeadButton);
	SDL_DestroyTexture(TailButton);
	SDL_DestroyTexture(PositionButton);
	SDL_DestroyTexture(RemoveButtonOnclick);
	SDL_DestroyTexture(HeadButtonOnclick);
	SDL_DestroyTexture(TailButtonOnclick);
	SDL_DestroyTexture(PositionButtonOnclick);
	TTF_CloseFont(Font);
}
void FindMenu::Init(SDL_Renderer *(&Renderer)){
	FindButton = LoadTexture("Menu/Find.png", Renderer);
	FindButtonOnclick = LoadTexture("Menu/FindOnclick.png", Renderer);
	LargerButton = LoadTexture("Menu/LargeThan.png", Renderer);
	SmallerButton = LoadTexture("Menu/SmallerThan.png", Renderer);
	LargerButtonOnclick = LoadTexture("Menu/LargeThanOnclick.png", Renderer);
	SmallerButtonOnclick = LoadTexture("Menu/SmallerThanOnclick.png", Renderer);
}
void FindMenu::AnimationAppearFindButton(SDL_Renderer *(Renderer), SDL_Texture *Erase){
	double s = 141;
	double s0 = -45;
	double st = s0;
	double v0 = 600;
	double vt = v0;
	double a = -v0*v0/(s*2.0);
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2.0;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 141;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 369; Rect.y = st; Rect.w = 45; Rect.h = 45;
		SDL_RenderCopy(Renderer, FindButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 369; Rect.y = 0; Rect.w = 45; Rect.h = 141;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	Rect.x = 369; Rect.y = 96; Rect.w = 45; Rect.h = 45;
	SDL_RenderCopy(Renderer, FindButton, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void FindMenu::AnimationSubMenuAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = 141;
	double s0 = -45;
	double st = s0;
	double v0 = 600;
	double vt = v0;
	double a = -(v0*v0)/(2.0*s);
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 141;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 417; Rect.y = st; Rect.w = 221; Rect.h = 45;
		SDL_RenderCopy(Renderer, SmallerButton, NULL, &Rect);
		Rect.x = 641; Rect.y = st; Rect.w = 221; Rect.h = 45;
		SDL_RenderCopy(Renderer, LargerButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 141;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	Rect.x = 417; Rect.y = 96; Rect.w = 221; Rect.h = 45;
	SDL_RenderCopy(Renderer, SmallerButton, NULL, &Rect);
	Rect.x = 641; Rect.y = 96; Rect.w = 221; Rect.h = 45;
	SDL_RenderCopy(Renderer, LargerButton, NULL, &Rect);
	SDL_RenderPresent(Renderer);
}
void FindMenu::AnimationSubMenuDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double s = -141;
	double s0 = 96;
	double st = s0;
	double v0 = -600;
	double vt = v0;
	double a = -(v0*v0)/(2.0*s);
	clock_t t = clock();
	while (vt < 0){
		double time = (1.0*clock() - 1.0*t) / 1000.0;
		st = s0 + v0*time + a*time*time/2;
		vt = v0 + a*time;
		SDL_Rect Rect;
		Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 141;
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		Rect.x = 417; Rect.y = st; Rect.w = 221; Rect.h = 45;
		SDL_RenderCopy(Renderer, SmallerButton, NULL, &Rect);
		Rect.x = 641; Rect.y = st; Rect.w = 221; Rect.h = 45;
		SDL_RenderCopy(Renderer, LargerButton, NULL, &Rect);
		SDL_RenderPresent(Renderer);
	}
	SDL_Rect Rect;
	Rect.x = 417; Rect.y = 0; Rect.w = 445; Rect.h = 141;
	SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
	SDL_RenderPresent(Renderer);
}
bool FindMenu::CheckFindOnclick(SDL_Renderer *(&Renderer), SDL_Texture *Erase, IOTab &IO, LinkedList &List, Controller &ControlAnimation, int x, int y){
	if (x < 369 || x > 414 || y < 96 || y > 141) return false;
	SDL_Rect Rect;
	Rect.x = 369; Rect.y = 96; Rect.w = 45; Rect.h = 45;
	SDL_RenderCopy(Renderer, FindButtonOnclick, NULL, &Rect);
	SDL_RenderPresent(Renderer);
	AnimationSubMenuAppear(Renderer, Erase);
	bool Stop = false;
	SDL_Event e;
	while (Stop == false){
		string DataIn = IO.GetInput();
		string DataOut = "";
		while (SDL_PollEvent(&e) != NULL){
			if (e.type == SDL_MOUSEBUTTONUP){
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (CheckSmallerOnclick(x, y)){
					Rect.x = 417; Rect.y = 96; Rect.w = 221; Rect.h = 45;
					SDL_RenderCopy(Renderer, SmallerButtonOnclick, NULL, & Rect);
					SDL_RenderPresent(Renderer);
					if (List.GetpHead() != NULL){
						ControlAnimation.AnimationAppear(Renderer, Erase);
						if (DataIn != "") List.AnimationFind(Renderer, Erase, DataIn, -1, true, List.GetpHead(), NULL, DataOut);
						ControlAnimation.AnimationDisappear(Renderer, Erase);
					}
					if (DataOut.length() > 0) IO.OutputMode(Renderer, Erase, DataOut);
					Rect.x = 417; Rect.y = 96; Rect.w = 221; Rect.h = 45;
					SDL_RenderCopy(Renderer, SmallerButton, NULL, & Rect);
					SDL_RenderPresent(Renderer);
				}
				else
				if (CheckLargerOnclick(x, y)){
					Rect.x = 641; Rect.y = 96; Rect.w = 221; Rect.h = 45;
					SDL_RenderCopy(Renderer, LargerButtonOnclick, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					if (List.GetpHead() != NULL){
						ControlAnimation.AnimationAppear(Renderer, Erase);
						if (DataIn != "") List.AnimationFind(Renderer, Erase, DataIn, 1, true, List.GetpHead(), NULL, DataOut);
						ControlAnimation.AnimationDisappear(Renderer, Erase);
					}
					if (DataOut.length() > 0) IO.OutputMode(Renderer, Erase, DataOut);
					Rect.x = 641; Rect.y = 96; Rect.w = 221; Rect.h = 45;
					SDL_RenderCopy(Renderer, LargerButton, NULL, &Rect);
					SDL_RenderPresent(Renderer);
				}
				else
				if (IO.CheckOnclick(Renderer, Erase, x, y)){
						continue;
				}
				else{
					AnimationSubMenuDisappear(Renderer, Erase);
					Rect.x = 369; Rect.y = 96; Rect.w = 45; Rect.h = 45;
					SDL_RenderCopy(Renderer, FindButton, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					Stop = true;
					break;
				}
			}
		}
	}
	return true;
}
bool FindMenu::CheckSmallerOnclick(int x, int y){
	if (x < 417 || x > 638 || y < 96 || y > 141) return false;
}
bool FindMenu::CheckLargerOnclick(int x, int y){
	if (x < 641 || x > 862 || y < 96 || y > 141) return false;
}
void FindMenu::Close(){
	SDL_DestroyTexture(FindButton);
	SDL_DestroyTexture(FindButtonOnclick);
	
	SDL_DestroyTexture(LargerButton);
	SDL_DestroyTexture(SmallerButton);
	
	SDL_DestroyTexture(LargerButtonOnclick);
	SDL_DestroyTexture(SmallerButtonOnclick);
}