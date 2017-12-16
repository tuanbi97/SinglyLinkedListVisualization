#include "ArrowFunction.h"
void Arrow::LoadArrow(SDL_Renderer *(&Renderer)){
	ArrowHead = LoadTexture("Arrow/ArrowHead2.png", Renderer);
	ArrowTail = LoadTexture("Arrow/ArrowTail2.png", Renderer);
	/*SDL_SetTextureBlendMode(ArrowHead, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(ArrowHead, 200);
	SDL_SetTextureBlendMode(ArrowTail, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(ArrowTail, 200);*/
	xs = 0; ys = 0;
	xt = 0; yt = 0;
}
void Arrow::SetPos(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double x1, double y1, double x2, double y2, double NodeSize){
	double s = Distance(x1, y1, x2, y2);
	/*SDL_Rect EraseRect = {xs, ys - HeadHeight/2, Distance(xs, ys, xt, yt), HeadHeight};
	SDL_Point PointE = {0, EraseRect.h / 2};
	SDL_RenderCopyEx(Renderer, Erase, NULL, &EraseRect, Angle(xs, ys, xt, yt), &PointE, SDL_FLIP_NONE); */

	int wt = 0;
	xs = x1; ys = y1; xt = x2; yt = y2; HeadHeight = 1.0*NodeSize / 2.5; HeadWidth = 1.0*NodeSize / 5.0; TailHeight = 1.0*NodeSize / 5.0;
	if (s >= HeadWidth){
		SDL_Rect RectTail = {x1, y1 - TailHeight / 2, Distance(x1, y1, x2, y2) - HeadWidth, TailHeight};	
		SDL_Point PointT = {0, RectTail.h / 2};
		SDL_RenderCopyEx(Renderer, ArrowTail, NULL, &RectTail, Angle(x1, y1, x2, y2), &PointT, SDL_FLIP_NONE);
		wt= RectTail.w;
	}
	SDL_Rect RectHead = {x1 + wt, y1 - HeadHeight / 2, min(1.0*HeadWidth, s), HeadHeight};
	SDL_Point PointH = {-wt, RectHead.h / 2};
	SDL_RenderCopyEx(Renderer, ArrowHead, NULL, &RectHead, Angle(x1, y1, x2, y2), &PointH, SDL_FLIP_NONE);
	//SDL_RenderPresent(Renderer);

	//cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<Angle(x1,y1,x2,y2)<<endl;
}
void Arrow::StopShowArrow(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	/*SDL_Rect EraseRect = {max(0, xs), ys - HeadHeight/2, min(Distance(xs, ys, xt, yt), 1.0*ScreenWidth - xs), HeadHeight}; //1
	//SDL_Rect EraseRect = {xs - 1, ys - 1.0*HeadHeight/2 - 1, Distance(xs, ys, xt, yt) + 1 , HeadHeight + 1}; //2
	SDL_Rect Clip = EraseRect;
	SDL_Point Point = {0, EraseRect.h / 2};
	//SDL_RenderCopyEx(Renderer, Erase, NULL, &EraseRect, Angle(xs, ys, xt, yt), &Point, SDL_FLIP_NONE); //1
	SDL_RenderCopyEx(Renderer, Erase, &Clip, &EraseRect, Angle(xs, ys, xt, yt), &Point, SDL_FLIP_NONE); //2*/
	//3
	SDL_Rect EraseRect = {min(xs,xt) - 1.0*HeadHeight/2, min(ys,yt) - 1.0*HeadHeight/2, abs(xt-xs) + 1.0*HeadHeight + 2, abs(yt-ys) + 1.0*HeadHeight + 2};
	EraseRect.x = max(EraseRect.x, 0); EraseRect.y = max(EraseRect.y, 0);
	EraseRect.w = min(EraseRect.w, ScreenWidth - EraseRect.x); 
	EraseRect.h = min(EraseRect.h, ScreenHeight - EraseRect.y); 
	SDL_RenderCopy(Renderer, Erase, &EraseRect, &EraseRect);
}
/*void Arrow::AnimationArrowAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double x1, double y1, double x2, double y2, double NodeSize){
	double sina = (y2 - y1) / Distance(x1, y1, x2, y2);
	double cosa = (x2 - x1) / Distance(x1, y1, x2, y2);
	double st = 0, s = Distance(x1, y1, x2, y2);
	//double s0 = DEFAULT_ARROW_HEAD_WIDTH;
	double s0 = 0;
	double v0 = 300;
	double vt = v0;
	double a = (-v0*v0) / (2.0*s);
	//cout<<a<<endl;
	//st = s0 + v0*t + a * t^2/2;
	//cout<<s<<endl;
	clock_t t = clock();
	while (vt > 0){
		double time = (1.0*(clock() - t)) / CLOCKS_PER_SEC;
		st = s0 + v0*time + a*time*time / 2;
		vt = v0 + a*time;
		//cout<<st<<" "<<vt<<endl;
		double xp = x1 + st * cosa;
		double yp = y1 + st * sina;
		StopShowArrow(Renderer, Erase);
		SetPos(Renderer, Erase, x1, y1, xp, yp, NodeSize);
		SDL_RenderPresent(Renderer);
	}
}
void Arrow::AnimationArrowDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double NodeSize){
	double sina = (yt - ys) / Distance(xs, ys, xt, yt);
	double cosa = (xt - xs) / Distance(xs, ys, xt, yt);
	double st = Distance(xs, ys, xt, yt), s = -Distance(xs, ys, xt, yt);
	double s0 = Distance(xs, ys, xt, yt);
	double v0 = -300, vt = v0;
	double a = (-v0*v0) / (2.0*s);
	//cout<<a<<endl;
	//st = s0 + v0*t + a * t^2/2;
	clock_t t = clock();
	while (vt < 0){
		double time = (1.0*(clock() - t)) / 1000.0;
		st = s0 + v0*time + a*time*time / 2;
		vt = v0 + a*time;
		//cout << vt <<" "<< st <<endl;
		double xp = xs + st * cosa;
		double yp = ys + st * sina;
		StopShowArrow(Renderer, Erase);
		SetPos(Renderer, Erase, xs, ys, xp, yp, NodeSize);
		SDL_RenderPresent(Renderer);
	}
	StopShowArrow(Renderer, Erase);
	SetPos(Renderer, Erase, 0, 0, 0 ,0, NodeSize);
	SDL_RenderPresent(Renderer);
	xs = 0; ys = 0; xt = 0; yt = 0; HeadHeight = 0; HeadWidth = 0; TailHeight = 0;
}*/
void Arrow::Close(){
	SDL_DestroyTexture(ArrowHead);
	SDL_DestroyTexture(ArrowTail);
}