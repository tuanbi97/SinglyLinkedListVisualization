#include "NodeFunction.h"
void Node::LoadNode(SDL_Renderer *(&Renderer), string s){
	TextureNode = LoadTexture("Node/Node2.png", Renderer);
	TextureCircle = LoadTexture("Node/Circle.png",Renderer);
	data = s;
	//if (TextureNode == NULL) cout<<1<<endl;
	TEXT.LoadText(Renderer, s, DEFAULT_TEXT_COLOR, "Font/DroidSans-Bold.ttf");
	//TEXT.LoadText(Renderer, s, 0x000000, "Font/DroidSans-Bold.ttf");
	/*SDL_SetTextureBlendMode(TextureNode, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(TextureNode, 200);*/
	SDL_SetTextureBlendMode(TextureCircle, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(TextureCircle, 100);
	pArrow.LoadArrow(Renderer);
	pNext = NULL;
	w = 0; x = 0; y = 0;
}
void Node::SetNode(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, int W){
	/*SDL_Rect EraseRect = {x, y, w, w};
	SDL_RenderCopy(Renderer, Erase, NULL, &EraseRect);*/

	SDL_Rect Rect = {X, Y, W, W};
	SDL_RenderCopy(Renderer, TextureNode, NULL, &Rect);
	double CHeight = 1.0*W / 2.0;
	double CWidth = CHeight / TEXT.GetHeight() * TEXT.GetWidth();
	double k = (1.0 * TEXT.GetWidth()) / (1.0 * TEXT.GetHeight());
	double b = 1.0*W / sqrt(k*k + 1);
	double a = b * k;
	if (CWidth > a || CHeight > b){
		TEXT.SetText(Renderer, X + 1.0*W/2.0 - a/2, Y + 1.0*W/2.0 - b/2, a, b);
	}
	else{
		TEXT.SetText(Renderer, X + 1.0*W/2.0 - CWidth/2, Y + 1.0*W/2.0 - CHeight/2, CWidth, CHeight);
	}
	//SDL_RenderPresent(Renderer);
	x = X; y = Y; w = W;
}
void Node::SetConnect(SDL_Renderer *(&Renderer), SDL_Texture *Erase, Node *q){
	pNext = q;
	double delta = w / 6;
	double X = pNext->GetX();
	double Y = pNext->GetY();
	double W = pNext->GetW();
	double dist = Distance(x + 1.0*w/2, y + 1.0*w/2, X + 1.0*W/2, Y + 1.0*W/2);
	double sina = 1.0*(Y - y + 1.0*(W - w)/2) / dist;
	double cosa = 1.0*(X - x + 1.0*(W - w)/2) / dist;
	double x1 = 1.0*x + 1.0*w/2.0 + (1.0 * w / 2.0 + delta)*cosa;
	double y1 = 1.0*y + 1.0*w/2.0 + (1.0 * w / 2.0 + delta)*sina;
	double x2 = X + 1.0*W/2.0 - (1.0 * W / 2.0 + delta)*cosa;
	double y2 = Y + 1.0*W/2.0 - (1.0 * W / 2.0 + delta)*sina;
	//cout<<x<<" "<<y<<" "<<w<<":"<<X<<" "<<Y<<" "<<W<<endl;
	//cout<<x1<<" "<<y1<<":"<<x2<<" "<<y2<<endl;
	//StopShowArrow(Renderer, Erase);

	pArrow.SetPos(Renderer, Erase, x1, y1, x2, y2, w);
	
	//cout<<x<<" "<<y<<" "<<w<<endl;
	//cout<<X<<" "<<Y<<" "<<W<<endl;
	SetNode(Renderer, Erase, x, y, w);
	q->SetNode(Renderer, Erase, X, Y, W);
	//SDL_RenderPresent(Renderer);
}
void Node::SetDisconnect(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	if (pNext == NULL) return;
	pNext = NULL;
	StopShowArrow(Renderer, Erase, 1);
	//pArrow.SetPos(Renderer, Erase, 0, 0, 0, 0, w);
}
void Node::StopShowNode(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	SDL_Rect Rect = {max(x, 0), y, min(w,ScreenWidth - x), w};
	SDL_Rect Clip = {max(x, 0), y, min(w,ScreenWidth - x), w};
	//SDL_RenderCopy(Renderer, Erase, NULL, &Rect); //1
	SDL_RenderCopy(Renderer, Erase, &Clip, &Rect); //2
}
void Node::StopShowArrow(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int state){
	pArrow.StopShowArrow(Renderer, Erase);
	if (state == 1 || state == 3){
		SetNode(Renderer, Erase, x, y, w);
	}
	if (pNext != NULL)
	if (state == 2 || state == 3){
		pNext->SetNode(Renderer, Erase, pNext->GetX(), pNext->GetY(), pNext->GetW());
	}
}
void Node::AnimationNodeAppear(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, int W){
	double st = 0;
	double s = W;
	double v0 = 300;
	double vt = v0;
	double a = (-v0*v0) / (2.0*s);
	clock_t t = clock();
	while (vt >= 0){
		double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
		st = v0*time + a*time*time / 2;
		vt = v0 + a*time;
		//cout<<st<<endl;
		StopShowNode(Renderer, Erase);
		SetNode(Renderer, Erase, 1.0*X - st/2, 1.0*Y - st/2, st);
		SDL_RenderPresent(Renderer);
	}
}
void Node::AnimationNodeDisappear(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	double st = w;
	double s = -w;
	double s0 = w;
	double v0 = -300;
	double vt = v0;
	double a = (-v0*v0) / (2.0*s);
	//cout<<a<<endl;
	double centerx = x + 1.0*w / 2.0;
	double centery = y + 1.0*w / 2.0;
	clock_t t = clock();
	while (vt < 0){
		double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
		st = s0 + v0*time + a*time*time / 2;
		//cout<<w<<" "<<v0*time<<" "<<a*time*time/2<<" "<<st<<endl;
		vt = v0 + a*time;
		//cout<<st<<" "<<vt<<" "<<time<<endl;
		StopShowNode(Renderer, Erase);
		SetNode(Renderer, Erase, centerx - st/2, centery - st/2, st);
		SDL_RenderPresent(Renderer);
	}
	Close();
}
void Node::AnimationConnect(SDL_Renderer *(&Renderer), SDL_Texture *Erase, Node *q){
	pNext = q;
	double delta = w / 6;
	double X = pNext->GetX();
	double Y = pNext->GetY();
	double W = pNext->GetW();
	double dist = Distance(x + 1.0*w/2, y + 1.0*w/2, X + 1.0*W/2, Y + 1.0*W/2);
	double sina = 1.0*(Y - y + 1.0*(W - w)/2) / dist;
	double cosa = 1.0*(X - x + 1.0*(W - w)/2) / dist;
	double x1 = 1.0*x + 1.0*w/2.0 + (1.0 * w / 2.0 + delta)*cosa;
	double y1 = 1.0*y + 1.0*w/2.0 + (1.0 * w / 2.0 + delta)*sina;
	double x2 = X + 1.0*W/2.0 - (1.0 * W / 2.0 + delta)*cosa;
	double y2 = Y + 1.0*W/2.0 - (1.0 * W / 2.0 + delta)*sina;
	//cout<<x<<" "<<y<<" "<<w<<":"<<X<<" "<<Y<<" "<<W<<endl;
	//cout<<x1<<" "<<y1<<":"<<x2<<" "<<y2<<endl;
	//pArrow.AnimationArrowAppear(Renderer, Erase, x1, y1, x2, y2, w);
	sina = (y2 - y1) / Distance(x1, y1, x2, y2);
	cosa = (x2 - x1) / Distance(x1, y1, x2, y2);
	double st = 0, s = Distance(x1, y1, x2, y2);
	//double s0 = DEFAULT_ARROW_HEAD_WIDTH;
	double s0 = 0;
	double v0 = 500;
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
		StopShowArrow(Renderer, Erase, 3);
		pArrow.SetPos(Renderer, Erase, x1, y1, xp, yp, w);
		SDL_RenderPresent(Renderer);
	}
}
void Node::AnimationDisconnect(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	//pArrow.AnimationArrowDisappear(Renderer, Erase, w);
	double delta = w / 6;
	double X = pNext->GetX();
	double Y = pNext->GetY();
	double W = pNext->GetW();
	double dist = Distance(x + 1.0*w/2, y + 1.0*w/2, X + 1.0*W/2, Y + 1.0*W/2);
	double sina = 1.0*(Y - y + 1.0*(W - w)/2) / dist;
	double cosa = 1.0*(X - x + 1.0*(W - w)/2) / dist;
	double x1 = 1.0*x + 1.0*w/2.0 + (1.0 * w / 2.0 + delta)*cosa;
	double y1 = 1.0*y + 1.0*w/2.0 + (1.0 * w / 2.0 + delta)*sina;
	double x2 = X + 1.0*W/2.0 - (1.0 * W / 2.0 + delta)*cosa;
	double y2 = Y + 1.0*W/2.0 - (1.0 * W / 2.0 + delta)*sina;

	sina = (y2 - y1) / Distance(x1, y1, x2, y2);
	cosa = (x2 - x1) / Distance(x1, y1, x2, y2);
	double st = Distance(x1, y1, x2, y2), s = -Distance(x1, y1, x2, y2);
	double s0 = Distance(x1, y1, x2, y2);
	double v0 = -500, vt = v0;
	double a = (-v0*v0) / (2.0*s);
	//cout<<a<<endl;
	//st = s0 + v0*t + a * t^2/2;
	clock_t t = clock();
	while (vt < 0){
		double time = (1.0*(clock() - t)) / 1000.0;
		st = s0 + v0*time + a*time*time / 2;
		vt = v0 + a*time;
		//cout << vt <<" "<< st <<endl;
		double xp = x1 + st * cosa;
		double yp = y1 + st * sina;
		StopShowArrow(Renderer, Erase, 3);
		pArrow.SetPos(Renderer, Erase, x1, y1, xp, yp, w);
		SDL_RenderPresent(Renderer);
	}
	StopShowArrow(Renderer, Erase, 3);
	//pArrow.SetPos(Renderer, Erase, 0, 0, 0 ,0, w);
	SDL_RenderPresent(Renderer);
	pNext = NULL;
}
void Node::AnimationNodeMove(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int X, int Y, Node *pPrev){
	double s = Distance(x, y, X, Y);
	double sina = (Y - y) / s;
	double cosa = (X - x) / s;
	//cout<<x<<" "<<y<<" "<<X<<" "<<Y<<endl;
	double st = 0;
	double v0 = 400;
	double vt = v0;
	double a = (-v0*v0) / (2.0*s);
	double x0 = x;
	double y0 = y;
	//cout<<sina<<" "<<cosa<<endl;
	clock_t t = clock();
	while (vt > 0){
		double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
		st = v0*time + a*time*time / 2;
		vt = v0 + a*time;
		//cout<<st<<endl;
		StopShowNode(Renderer, Erase);
		SetNode(Renderer, Erase, x0 + st * cosa, y0 + st * sina, w);
		if (pPrev != NULL) pPrev->StopShowArrow(Renderer, Erase, 3);
		if (pPrev != NULL) pPrev->SetConnect(Renderer, Erase, pPrev->GetpNext());
		StopShowArrow(Renderer, Erase, 3);
		SetConnect(Renderer, Erase, pNext);
		SDL_RenderPresent(Renderer);
	}
}
void Node::AnimationCircle(SDL_Renderer *(&Renderer), SDL_Texture *Erase, Node *pPrev){
	int X = x + w / 2;
	int Y = y + w / 2;
	int W = w + 50;
	double st = 0;
	double s = W;
	double s0 = 0;
	double v0 = 400;
	double vt = v0;
	double a = (-v0*v0) / (2.0*s);
	clock_t t = clock();
	while (vt >= 0){
		double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
		st = v0*time + a*time*time / 2;
		vt = v0 + a*time;
		SDL_Rect Rect = {1.0 * X - st/2, 1.0*Y - st/2, st, st};
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		SDL_RenderCopy(Renderer, TextureCircle, NULL, &Rect);

		if (pPrev != NULL) pPrev->SetConnect(Renderer, Erase, pPrev->GetpNext());
		if (pNext != NULL) SetConnect(Renderer, Erase, pNext);
		SetNode(Renderer, Erase, x, y, w);
		SDL_RenderPresent(Renderer);
	}
	SDL_Delay(500);
	st = W;
	s = - W;
	s0 = W;
	v0 = - 400;
	vt = v0;
	a = (-v0*v0) / (2.0*s);
	t= clock();
	while (vt < 0){
		double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
		SDL_Rect Rect = {1.0 * X - st/2, 1.0 * Y - st/2, st, st};
		SDL_RenderCopy(Renderer, Erase, &Rect, &Rect);
		st = s0 + v0*time + a*time*time / 2;
		vt = v0 + a*time;
		Rect.x = 1.0*X - st/2; Rect.y = 1.0*Y - st/2; Rect.w = st; Rect.h = st;
		SDL_RenderCopy(Renderer, TextureCircle, NULL, &Rect);
		if (pPrev != NULL) pPrev->SetConnect(Renderer, Erase, pPrev->GetpNext());
		if (pNext != NULL) SetConnect(Renderer, Erase, pNext);
		SetNode(Renderer, Erase, x, y, w);
		SDL_RenderPresent(Renderer);
	}
}
int Node::GetX(){
	return(x);
}
int Node::GetY(){
	return(y);
}
int Node::GetW(){
	return(w);
}
Node* Node::GetpNext(){
	return(pNext);
}
string Node::GetData(){
	return data;
}
void Node:: SetpNext(Node *p){
	pNext = p;
}
void Node::Close(){
	SDL_DestroyTexture(TextureNode);
	TEXT.Close();
	pArrow.Close();
}