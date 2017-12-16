#include "ScreenDef.h"
SDL_Texture *LoadTexture(string s, SDL_Renderer *(&Renderer)){
	SDL_Surface *tmp;
	SDL_Texture *ret;
	tmp = IMG_Load(s.c_str());
	ret = SDL_CreateTextureFromSurface(Renderer, tmp);
	SDL_FreeSurface(tmp);
	return(ret);
}
SDL_Texture *LoadTextTexture(string s, SDL_Color TextColor, TTF_Font *Font, SDL_Renderer *(&Renderer), int &a, int &b){
    SDL_Surface* textSurface = TTF_RenderText_Solid(Font, s.c_str(), TextColor);
	a = textSurface->w;
	b = textSurface->h;
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, textSurface);
    SDL_FreeSurface( textSurface );
    return Texture;
}
bool AnimationController(bool &Pause, SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	if (Pause == false) return true;
	SDL_Event e;
	while (true){
		while (SDL_PollEvent(&e) != NULL){
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
				case SDLK_LEFT:{
					SDL_Rect Rect = {490, 640, 70, 40};
					SDL_Texture *tmp = LoadTexture("Menu/PrevButtonOnclick.png", Renderer);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					SDL_Delay(70);
					tmp = LoadTexture("Menu/PrevButton.png", Renderer);
					SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					return false;
				}
				case SDLK_RIGHT:{
					SDL_Rect Rect = {640, 640, 70, 40};
					SDL_Texture *tmp = LoadTexture("Menu/NextButtonOnclick.png", Renderer);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					SDL_Delay(70);
					tmp = LoadTexture("Menu/NextButton.png", Renderer);
					SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					return true;
				}
				case SDLK_q:
					SDL_Rect Rect = {560, 600, 80, 80};
					SDL_Texture *tmp = LoadTexture("Menu/PlayButtonOnclick.png", Renderer);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					Pause = false;
					return true;
				}
			}
			else
			if (e.type == SDL_MOUSEBUTTONUP){
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x >= 490 && x <= 560 && y <= 680 && y >= 640){
					SDL_Rect Rect = {490, 640, 70, 40};
					SDL_Texture *tmp = LoadTexture("Menu/PrevButtonOnclick.png", Renderer);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					SDL_Delay(70);
					tmp = LoadTexture("Menu/PrevButton.png", Renderer);
					SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					return false;
				}
				else
				if (x >= 640 && x <= 710 && y <= 680 && y >= 640){
					SDL_Rect Rect = {640, 640, 70, 40};
					SDL_Texture *tmp = LoadTexture("Menu/NextButtonOnclick.png", Renderer);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					SDL_Delay(70);
					tmp = LoadTexture("Menu/NextButton.png", Renderer);
					SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					return true;
				}
				else
				if (x >= 560 && x <= 640 && y <= 680 && y >= 600){
					SDL_Rect Rect = {560, 600, 80, 80};
					SDL_Texture *tmp = LoadTexture("Menu/PlayButtonOnclick.png", Renderer);
					SDL_RenderCopy(Renderer, tmp, NULL, &Rect);
					SDL_RenderPresent(Renderer);
					SDL_DestroyTexture(tmp);
					Pause = false;
					return true;
				}
			}
		}
	}
}
double Distance(int x1, int y1, int x2, int y2){
	return(sqrt(1.0*(x2-x1)*(x2-x1) + 1.0*(y2-y1)*(y2-y1)));
}
double Angle(int x1, int y1, int x2, int y2){
	if ((x2-x1) == 0){
		if (y2 - y1 > 0) return (90);
		else  return(-90);
	}
	double Tan = 1.0*(y2-y1)/(1.0*x2-1.0*x1);
	if (Tan == 0){
		if (x2 > x1) return 0;
		else return 180;
	}
	if (y2 - y1 < 0 && x2 - x1 < 0) return (atan(Tan) * 180 / PI - 180);
	if (y2 - y1 > 0 && x2 - x1 < 0) return (atan(Tan) * 180 / PI + 180);
	return (atan(Tan) * 180 / PI);
}
int Compare(string a, string b){
	int lena = a.length();
	int lenb = b.length();
	if (lena < lenb) return -1;
	if (lena > lenb) return 1;
	for (int i = 0; i < lena; i++){
		if (a[i] < b[i]) return -1;
		if (a[i] > b[i]) return 1;
	}
	return 0;
}