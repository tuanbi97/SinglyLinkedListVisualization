#include "ArrowFunction.h"
#include "ListFunction.h"
#include "MenuFunction.h"
const int BUTTON_WIDTH = 99;
const int BUTTON_HEIGHT = 99;
const int TOTAL_BUTTONS = 3;
enum LButtonSprite
{
	
	BUTTON_SPRITE_MOUSE_OVER_MOTION1 = 1,
	BUTTON_SPRITE_MOUSE_DOWN1 = 2,
	BUTTON_SPRITE_MOUSE_OVER_MOTION2 = 3,
	BUTTON_SPRITE_MOUSE_DOWN2 = 4,
	BUTTON_SPRITE_MOUSE_OVER_MOTION3 = 5,
	BUTTON_SPRITE_MOUSE_DOWN3 = 6,
	BUTTON_SPRITE_TOTAL = 7
};
SDL_Window *Window;
SDL_Renderer *Renderer;
SDL_Texture *Background;
class LTexture
{
	public:
		LTexture();
		~LTexture();
		bool loadFromFile( std::string path );
		void free();
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

class LButton{
	public:
		LButton();
		void setPosition( int x, int y );
		int handleEvent( SDL_Event* e );
		void render();
		int Event( SDL_Event* e );
	private:
		SDL_Point mPosition;
		LButtonSprite mCurrentSprite;
};
SDL_Texture* gTexture1 = NULL;
LTexture gTexture2;
LTexture gTexture3;
LTexture gTexture4;
LTexture gTexture5;
SDL_Rect gTexture2Rect;
SDL_Rect gTexture3Rect;
SDL_Rect gTexture4Rect;
SDL_Rect gTexture5Rect;
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTexture;
LButton gButtons[ TOTAL_BUTTONS ]; 
LTexture::LTexture(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture(){
	free();
}

bool LTexture::loadFromFile( std::string path ){
	free();
	SDL_Texture* newTexture = NULL;
	newTexture = LoadTexture(path, Renderer);
	mTexture = newTexture;
	return true;
}
void LTexture::free(){
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(Renderer, mTexture, clip, &renderQuad, angle, center, flip );
}
int LTexture::getWidth(){
	return mWidth;
}
int LTexture::getHeight(){
	return mHeight;
}
LButton::LButton(){
	mPosition.x = 0;
	mPosition.y = 0;
	gButtons[ 0 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_OVER_MOTION1;
	gButtons[ 1 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_OVER_MOTION2;
	gButtons[ 2 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_OVER_MOTION3;
}

void LButton::setPosition( int x, int y ){
	mPosition.x = x;
	mPosition.y = y;
}

int LButton::Event( SDL_Event* e ){
	if(e->type == SDL_MOUSEBUTTONUP ){
		int x, y;
		SDL_GetMouseState( &x, &y );
		int inside = -1;
		if(299 < x && x < 399 && 191 < y  && y < 291)
			inside = 1; //From File
		else if(499 < x && x < 599 && 333 < y && y < 433)
			inside = 0; //Random
		else if(698 < x && x < 798 && 480 < y && y < 580)
			inside = 2; //NULL
		else
			inside = -1;
		return inside;
	}
}

int LButton::handleEvent( SDL_Event* e ){
	if(e->type == SDL_MOUSEBUTTONUP ){
		int x, y;
		SDL_GetMouseState( &x, &y );
		if(LButton::Event(e) == -1){
			gButtons[ 0 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_OVER_MOTION1;
			gButtons[ 1 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_OVER_MOTION2;
			gButtons[ 2 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_OVER_MOTION3;
		}
		else if(LButton::Event(e) == 1){
			switch(e->type){
				case SDL_MOUSEBUTTONDOWN:
				gButtons[ 0 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_DOWN1;
				break;
			}
		}
		else if(LButton::Event(e) == 2){
			switch(e->type){
				case SDL_MOUSEBUTTONDOWN:
				gButtons[ 2 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_DOWN3;
				break;
			}
		}
		else{
			switch(e->type){
				case SDL_MOUSEBUTTONDOWN:
				gButtons[ 1 ].mCurrentSprite =  BUTTON_SPRITE_MOUSE_DOWN2;
				break;
			}
		}
		return Event(e);
	}
	return -1;
}
void LButton::render(){
	gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
}
void init(){
	SDL_Init(SDL_INIT_EVERYTHING);
	Window = SDL_CreateWindow("Linked List", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	Background = LoadTexture("Background/WDF_630656.jpg", Renderer);
	//Background = LoadTexture("Background/Brilliant-Purple-Wallpaper-1080p-Image-Pc-Picture.jpg", Renderer);
	gTexture1 = LoadTexture( "Background/BackgroundNew4.png", Renderer);
	gTexture2.loadFromFile( "Menu/ChooseOption_Trans.png");
	gTexture3.loadFromFile( "Menu/Trans_From File.png" );
	gTexture4.loadFromFile( "Menu/Trans_Random.png" );
	gTexture5.loadFromFile( "Menu/Trans_Empty.png" );
	gTexture2Rect.x = 0;
	gTexture2Rect.y = 0;
	gTexture2Rect.w = 446;
	gTexture2Rect.h = 49;
	
	gTexture3Rect.x = 0;
	gTexture3Rect.y = 0;
	gTexture3Rect.w = 267;
	gTexture3Rect.h = 99;

	gTexture4Rect.x = 0;
	gTexture4Rect.y = 0;
	gTexture4Rect.w = 259;
	gTexture4Rect.h = 99;

	gTexture5Rect.x = 0;
	gTexture5Rect.y = 0;
	gTexture5Rect.w = 217;
	gTexture5Rect.h = 99;
	gButtonSpriteSheetTexture.loadFromFile( "Menu/Icons2.png" );
	for( int i = 1; i < BUTTON_SPRITE_TOTAL ; ++i ){
			gSpriteClips[ i ].x = (i - 1) * 99;
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
	}
	gButtons[ 0 ].setPosition( 300, 192 );
	gButtons[ 1 ].setPosition( 500, 334 );
	gButtons[ 2 ].setPosition( 699, 481 );
}
void Close(){
	SDL_DestroyTexture( gTexture1 );
	gTexture1 = NULL;
	gTexture2.free();
	gTexture3.free();
	gTexture4.free();
	gTexture5.free(); 
	gButtonSpriteSheetTexture.free();
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyTexture(Background);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
int main(int argc, char *args[]){
	init();
	//ARROW TEST
	/*Arrow a;
	a.LoadArrow(Renderer);*/
	/*int x1 = ScreenWidth/2, y1 = ScreenHeight/2;
	int x2 = x1 + 50, y2 = y1 + 50;
	a.StopShowArrow(Renderer, Background);
	a.SetPos(Renderer, Background, x1, y1, x2, y2, DEFAULT_NODE_SIZE);
	double v = -10;
	clock_t t = clock();
	while (1.0*(clock()-t) / CLOCKS_PER_SEC <= -100.0/v){
		double time = 1.0*(clock()-t) / CLOCKS_PER_SEC;
		y2 = y1 + 50 + v * time;
		//cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
		a.StopShowArrow(Renderer, Background);
		a.SetPos(Renderer, Background, x1, y1, x2, y2, DEFAULT_NODE_SIZE);
	}*/
	//a.SetPos(Renderer, Background, ScreenWidth/2, ScreenHeight/2, ScreenWidth/2 + 100, ScreenHeight/2, 100);
	/*a.AnimationArrowAppear (Renderer, Background, ScreenWidth/2, ScreenHeight/2, ScreenWidth/2 + 100, ScreenHeight/2 + 150, 100);
	SDL_Delay(1000);
	//a.StopShowArrow(Renderer, Background);
	a.AnimationArrowDisappear(Renderer, Background, 100);*/
	
	//NODE TEST
	/*Node *r = new Node;
	r->LoadNode(Renderer, "I");
	r->AnimationNodeAppear(Renderer, Background, ScreenWidth/2 - 160, ScreenHeight/2, DEFAULT_NODE_SIZE);

	Node *p = new Node;
	p->LoadNode(Renderer, "Love");
	//p->SetNode(Renderer, Background, ScreenWidth/2, ScreenHeight/2, 100);
	p->AnimationNodeAppear(Renderer, Background, ScreenWidth/2, ScreenHeight/2, DEFAULT_NODE_SIZE);
	r->AnimationConnect(Renderer, Background, p);
	//SDL_Delay(500);
	Node *q = new Node;
	q->LoadNode(Renderer, "U");
	q->AnimationNodeAppear(Renderer, Background, ScreenWidth/2 + 160, ScreenHeight/2, DEFAULT_NODE_SIZE);
	//SDL_Delay(500);
	//p->SetConnect(Renderer, Background, q);
	p->AnimationConnect(Renderer, Background, q);
	//SDL_Delay(2000);
	Node *tmp = p->GetpNext();
	p->AnimationDisconnect(Renderer, Background);
	//SDL_Delay(500);
	tmp->AnimationNodeDisappear(Renderer, Background);
	r->AnimationDisconnect(Renderer, Background);
	//SDL_Delay(500);
	p->AnimationNodeDisappear(Renderer, Background);
	r->AnimationNodeDisappear(Renderer, Background);
	delete p; delete q; delete r;*/
	
	//MOVE NODE TEST
	/*Node *p = new Node;
	p->LoadNode(Renderer, "Replay");
	p->AnimationNodeAppear(Renderer, Background, ScreenWidth/2, ScreenHeight/2, DEFAULT_NODE_SIZE);
	SDL_Delay(500);
	p->AnimationNodeMove(Renderer, Background, p->GetX(), p->GetY() + 150);
	SDL_Delay(500);
	p->AnimationNodeDisappear(Renderer, Background);
	delete p;*/

	//MENU TEST
	/*IOTab IO;
	InsertMenu Insert;
	RemoveMenu Remove;
	FindMenu Find;
	Controller ControlAnimation;
	IO.Init(Renderer);
	IO.AnimationAppear(Renderer, Background);
	ControlAnimation.Init(Renderer);
	Find.Init(Renderer);
	Find.AnimationAppearFindButton(Renderer, Background);
	Remove.Init(Renderer);
	Remove.AnimationAppearRemoveButton(Renderer, Background);
	Insert.Init(Renderer);
	Insert.AnimationAppearInsertButton(Renderer, Background);*/

	//LIST TEST
	/*LinkedList List;
	List.Init();
	List.InputFromFile(Renderer);
	//List.SetPosList(Renderer, Background, ScreenWidth/2 - 360, ScreenHeight/2 - 40, NULL, NULL);
	//List.AnimationMoveList(Renderer, Background, ScreenWidth/2 - 500, ScreenHeight/2 - 40, NULL);
	List.AnimationSetList(Renderer, Background);*/
	/*while (true){
		int TYPE, pos;
		bool RunOnce;
		string str;
		cin>>TYPE;
		if (TYPE == 1){
			cin>>str; cin>>pos; cin>>RunOnce;
			List.AnimationInsert(Renderer, Background, str, pos, RunOnce);
		}
		else
		if (TYPE == 2){
			cin>>pos; cin>>RunOnce;
			List.AnimationRemove(Renderer, Background, pos, RunOnce);
		}
		else
		if (TYPE == 0) break;
	}*/
	bool Quit = false;
	while (!Quit){
		SDL_Event e;
		int InputType = -1;
		while( !Quit ){
			while( SDL_PollEvent( &e ) != 0 ){
				if( e.type == SDL_QUIT ) Quit = true;
					for( int i = 0; i < TOTAL_BUTTONS; ++i ){
						InputType = gButtons[ i ].handleEvent( &e );
						if (InputType >= 0) break;
					}
			}
			if (InputType >= 0) break;
			SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( Renderer );
			SDL_RenderCopy( Renderer, gTexture1, NULL, NULL );
			gTexture2.render(392, 100, &gTexture2Rect);
			SDL_RenderCopy( Renderer, NULL, NULL, &gTexture2Rect );
			gTexture3.render(300, 192, &gTexture3Rect);
			SDL_RenderCopy( Renderer, NULL, NULL, &gTexture3Rect );
			gTexture4.render(500, 334, &gTexture4Rect);
			SDL_RenderCopy( Renderer, NULL, NULL, &gTexture4Rect );
			gTexture5.render(699, 481, &gTexture5Rect);
			SDL_RenderCopy( Renderer, NULL, NULL, &gTexture5Rect );
			for (int i = 0; i < TOTAL_BUTTONS; ++i ) gButtons[ i ].render();
			SDL_RenderPresent( Renderer );
		}
		IOTab IO;
		InsertMenu Insert;
		RemoveMenu Remove;
		FindMenu Find;
		Controller ControlAnimation;
		LinkedList List;
		if (!Quit){
			SDL_RenderCopy(Renderer, Background, NULL, NULL);
			SDL_RenderPresent(Renderer);
			IO.Init(Renderer);
			IO.AnimationAppear(Renderer, Background);
			ControlAnimation.Init(Renderer);
			Find.Init(Renderer);
			Find.AnimationAppearFindButton(Renderer, Background);
			Remove.Init(Renderer);
			Remove.AnimationAppearRemoveButton(Renderer, Background);
			SDL_Texture *SaveIcon = LoadTexture("Menu/Save.png", Renderer);
			SDL_Texture *NewIcon = LoadTexture("Menu/New.png", Renderer);
			SDL_Rect Rect = {1140, 10, 50, 50};
			SDL_RenderCopy(Renderer, NewIcon, NULL, &Rect);
			Rect.x = 1140; Rect.y = 80, Rect.w = 50, Rect.h = 50;
			SDL_RenderCopy(Renderer, SaveIcon, NULL, &Rect);
			SDL_RenderPresent(Renderer);
			Insert.Init(Renderer);
			Insert.AnimationAppearInsertButton(Renderer, Background);
			List.Init();
			if (InputType == 0) List.InputRandom(Renderer);
			if (InputType == 1) List.InputFromFile(Renderer);
			List.AnimationSetList(Renderer, Background);
			bool New = false;
			while (!Quit){
				while (SDL_PollEvent(&e) != NULL){
					if (e.type == SDL_QUIT){
						Quit = true;
					}
					else
					if (e.type == SDL_KEYDOWN){
						//cout<<1<<endl;
						Node *tmp = List.GetpHead();
						if (tmp == NULL) continue;
						switch( e.key.keysym.sym ){
								case SDLK_a:
									List.SetPosList(Renderer, Background, tmp->GetX()+10, tmp->GetY(), NULL, NULL);
									SDL_RenderPresent(Renderer);
								break;
							
								case SDLK_d:
									List.SetPosList(Renderer, Background, tmp->GetX()-10, tmp->GetY(), NULL, NULL);
									SDL_RenderPresent(Renderer);
								break;
						
								case SDLK_w:
									if (List.GetNodeSize() + 4 <= 260){
										List.AnimationResizeList(Renderer, Background, List.GetNodeSize() + 4, NULL);
									}
									else List.AnimationResizeList(Renderer, Background, 260, NULL);
								break;

								case SDLK_s:
									if (List.GetNodeSize() - 4 >= 4){
										List.AnimationResizeList(Renderer, Background, List.GetNodeSize() - 4, NULL);
									}
									else List.AnimationResizeList(Renderer, Background, 4, NULL);
								break;
						}
					}
					else
					if (e.type == SDL_MOUSEBUTTONUP){
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (Remove.CheckRemoveOnclick(Renderer, Background, IO, List, ControlAnimation, x, y)){
							continue;
						}
						else
						if (Insert.CheckInsertOnclick(Renderer, Background, IO, List, ControlAnimation, x, y)){
							continue;
						}
						if (Find.CheckFindOnclick(Renderer, Background, IO, List, ControlAnimation, x, y)){
							continue;
						}
						else
						if (IO.CheckOnclick(Renderer, Background, x, y)){
							continue;
						}
						else
						if (x >= 1140 && x <= 1190 && y >= 10 && y <= 60){
							New = true;
							break;
						}
						else
						if (x >= 1140 && x <= 1190 && y >= 80 && y <= 130){
							List.Save();
							IO.OutputMode(Renderer, Background, "Saved!");
						}
						if (List.CheckInList(x, y)){
							List.AnimationZoomIn(Renderer, Background, x, y);
						}
					}
				}
				SDL_RenderPresent(Renderer);
				if (New == true) break;
			}
			IO.Close();
			ControlAnimation.Close();
			List.Close();
			Insert.Close();
			Find.Close();
		}
	}
	Close();
	return 0;
}