#include "TextFunction.h"
void Text::LoadText(SDL_Renderer *(&Renderer), string s, int color, string dir){
		int R = color / 65536;
		int G = (color / 256) % 256;
		int B = color % 256;
		SDL_Color Color = {R, G, B};
		TTF_Font *Font = TTF_OpenFont(dir.c_str(), DEFAULT_FONT_SIZE);
		TextTexture = LoadTextTexture(s.c_str(), Color, Font, Renderer, a, b);
		//if (TextTexture == NULL) cout<<2<<endl;
		TTF_CloseFont(Font);
}
void Text::SetText(SDL_Renderer *(&Renderer), int x, int y, int w, int h){
		SDL_Rect Rect;
		Rect.x = x; Rect.y = y; Rect.w = w; Rect.h = h;
		SDL_RenderCopy(Renderer, TextTexture, NULL, &Rect);
}
int Text::GetHeight(){
		return b;
}
int Text::GetWidth(){
		return a;
}
void Text::Close(){
	SDL_DestroyTexture(TextTexture);
}