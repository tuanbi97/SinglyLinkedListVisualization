#include "ListFunction.h"
void LinkedList::Init(){
	n = 0; NodeSize = DEFAULT_NODE_SIZE; pHead = NULL;
}
void LinkedList::InputFromFile(SDL_Renderer *(&Renderer)){
	ifstream FileIn;
	FileIn.open("IO/input.txt");
	FileIn >> n;
	FileIn.get();
	string str;
	Node *p = NULL;
	for (int i = 0; i < n; i++){
		FileIn >> str;
		if (pHead == NULL){
			pHead = new Node;
			p = pHead;
		}
		else{
			Node *tmp = new Node;
			p->SetpNext(tmp);
			p = p->GetpNext();
		}
		p->LoadNode(Renderer, str);
		p->SetpNext(NULL);
	}
}
void LinkedList::InputRandom(SDL_Renderer *(&Renderer)){
	srand(time(NULL));
	n = rand()%10+1;
	Node *p = NULL;
	for (int i = 0; i < n; i++){
		string str = "";
		int len = rand()%2+1;
		for (int j = 0; j < len; j++){
			if (j == 0) str = str + char(rand()%9 + '1');
			else str = str + char(rand()%10 + '0');
		}
		if (pHead == NULL){
			pHead = new Node;
			p = pHead;
		}
		else{
			Node *tmp = new Node;
			p->SetpNext(tmp);
			p = p->GetpNext();
		}
		p->LoadNode(Renderer, str);
		p->SetpNext(NULL);
	}
}
void LinkedList::Save(){
	ofstream FileOut;
	FileOut.open("IO/output.txt");
	Node *p = pHead;
	while (p != NULL){
		FileOut<< p->GetData() <<" ";
		p = p->GetpNext();
	}
	FileOut.close();
}
Node* LinkedList::GetpHead(){
	return pHead;
}
int LinkedList::GetNodeSize(){
	return NodeSize;
}
/*void LinkedList::StopShowList(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
}*/
void LinkedList::SetPosList(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double x, double y, Node *pPrev, Node *pEnd){
	if (pPrev != NULL) pPrev->StopShowArrow(Renderer, Erase, 1);
	Node *tmp, *ptmp;
	if (pPrev != NULL) tmp = pPrev->GetpNext();
	else tmp = pHead;
	//double DispX = x - tmp->GetX();
	while (tmp != NULL){
		tmp->StopShowNode(Renderer, Erase);
		tmp->StopShowArrow(Renderer, Erase, 0);
		tmp = tmp->GetpNext();
	}
	if (pPrev != NULL) tmp = pPrev->GetpNext();
	else tmp = pHead;
	if (pPrev != NULL) ptmp = pPrev;
	else ptmp = NULL;
	//cout<<NodeSize<<endl;
	while (tmp != pEnd){
		//tmp->SetNode(Renderer, Erase, tmp->GetX() + DispX, y, NodeSize);
		tmp->SetNode(Renderer, Erase, x, y, NodeSize);
		//cout<<x<<" "<<y<<" "<<NodeSize<<endl;
		x = x + 2 * NodeSize;
		if (ptmp != NULL) ptmp->SetConnect(Renderer, Erase, tmp);
		ptmp = tmp;
		tmp = tmp->GetpNext();
	}
	if (pPrev != NULL && pPrev->GetpNext() != NULL) pPrev->SetConnect(Renderer, Erase, pPrev->GetpNext());
}
void LinkedList::Resize(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double NewSize, Node *pEnd){
	Node *tmp, *ptmp;
	tmp = pHead;
	while (tmp != pEnd){
		tmp->StopShowNode(Renderer, Erase);
		tmp->StopShowArrow(Renderer, Erase, 2);
		tmp = tmp->GetpNext();
	}
	tmp = pHead;
	ptmp = NULL;
	double x = pHead->GetX(), y = pHead->GetY();
	while (tmp != pEnd){
		tmp->SetNode(Renderer, Erase, x, y, NewSize);
		x = x + NewSize * 2;
		if (ptmp != NULL) ptmp->SetConnect(Renderer, Erase, tmp);
		ptmp = tmp;
		tmp = tmp->GetpNext();
	}
	NodeSize = NewSize;
	SetPosList(Renderer, Erase, pHead->GetX(), 1.0*(ScreenHeight - NodeSize) / 2, NULL, pEnd);
	//SDL_RenderPresent(Renderer);
}
void LinkedList::AnimationMoveList(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double X, double Y, Node *pPrev, Node *pEnd){
	Node *cur;
	if (pPrev == NULL) cur = pHead;
	else cur = pPrev->GetpNext();
	double x = cur->GetX(), y = cur->GetY(); 
	double s = Distance(x, y, X, Y);
	if (s == 0) return;
	double sina = (Y - y) / s;
	double cosa = (X - x) / s;
	//cout<<x<<" "<<y<<" "<<X<<" "<<Y<<endl;
	double st = 0;
	double v0 = 600;
	double vt = v0;
	double a = (-v0*v0) / (2.0*s);
	double x0 = x;
	double y0 = y;
	//cout<<sina<<" "<<cosa<<" "<<s<<" "<<Y-y<<" "<<X-x<<endl;
	clock_t t = clock();
	//cout <<x<<" "<<y<<" "<<X<<" "<<Y<<endl;
	while (vt > 0){
		double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
		st = v0*time + a*time*time / 2;
		vt = v0 + a*time;
		//cout<<st<<endl;
		//cout<<1<<endl;
		/*if (dem == 22){
			cout<<x0 + st*cosa<<" "<<y0 + st*sina<<endl;
		}*/
		SetPosList(Renderer, Erase, x0 + st * cosa, y0 + st * sina, pPrev, pEnd);
		SDL_RenderPresent(Renderer);
	}
	/*if (pPrev != NULL && pPrev->GetpNext() != NULL){
		pPrev->SetConnect(Renderer, Erase, pPrev->GetpNext());
		SDL_RenderPresent(Renderer);
	}*/
}
void LinkedList::AnimationResizeList(SDL_Renderer *(&Renderer), SDL_Texture *Erase, double NewSize, Node *pEnd){
	double s = NewSize - NodeSize;
	//cout<<x<<" "<<y<<" "<<X<<" "<<Y<<endl;
	double s0 = NodeSize;
	double st = 0;
	double v0 = 100;
	double vt = v0;
	double a = (-v0*v0) / (2.0*s);
	//cout<<sina<<" "<<cosa<<endl;
	//cout<<a<<endl;
	if (s < 0) v0 = -v0;
	st = s0;
	vt = v0;
	clock_t t = clock();
	if (s < 0){
		while (st > NewSize){
			//cout<<vt<<endl;
			double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
			st = s0 + v0*time;// + a*time*time / 2;
			//cout<<st<<endl;
			//vt = v0 + a*time;
			//cout<<st<<endl;
			Resize(Renderer, Erase, st, pEnd);
			SDL_RenderPresent(Renderer);
		}
	}
	else{
		while (st < NewSize){
			double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
			st = s0 + v0*time; //+ a*time*time / 2;
			//vt = v0 + a*time;
			//cout<<st<<endl;
			Resize(Renderer, Erase, st, pEnd);
			SDL_RenderPresent(Renderer);
		}
	}
}
void LinkedList::AnimationSetList(SDL_Renderer *(&Renderer), SDL_Texture *Erase){
	Node *p = pHead, *pPrev = NULL;
	double ListWidth = 0;
	double MaxWidth = ScreenWidth - 100;
	int dem = 0;
	while (p != NULL){
		dem++;
		if (p == pHead) ListWidth += NodeSize;
		else ListWidth += 2*NodeSize;
		if (ListWidth > MaxWidth){
			int NewSize = MaxWidth / ListWidth * NodeSize;
			AnimationResizeList(Renderer, Erase, NewSize, p);
			//Resize(Renderer, Erase, NewSize, p);
			ListWidth = NewSize*(2*dem - 1);
		}
		//cout << dem << " " <<ListWidth << endl;
		if (p == pHead){
			p->AnimationNodeAppear(Renderer, Erase, ScreenWidth/2, ScreenHeight/2, NodeSize);
		}
		else{
			p->AnimationNodeAppear(Renderer, Erase, pPrev->GetX() + 2*NodeSize + NodeSize/2, pPrev->GetY() + NodeSize/2, NodeSize);
			//cout<<1<<endl;
			pPrev->AnimationConnect(Renderer, Erase, p);
			//cout<<2<<endl;
			AnimationMoveList(Renderer, Erase, (ScreenWidth - ListWidth) / 2, ScreenHeight/2 - NodeSize/2, NULL, p->GetpNext());
			//cout<<3<<endl;
			//cout<<pHead->GetX()<<" "<<pHead->GetY()<<endl;
		}
		pPrev = p;
		p = p->GetpNext();
	}
}
bool LinkedList::AnimationInsert2(SDL_Renderer *(&Renderer), SDL_Texture *Erase, string str, int vt, int pos, bool Pause, Node *p, Node *pPrev){
	if (pos >= n && pHead != NULL) return true;
	if (pHead == NULL && (pos != 0 && pos != -1)) return true;
	if (p != NULL && p != pHead){
		AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
		p->AnimationCircle(Renderer, Erase, pPrev);
	}
	bool MoveNext = true;
	if (pHead == NULL){
		MoveNext = AnimationController(Pause, Renderer, Erase);
		if (MoveNext){
			Node *tmp = new Node;
			tmp->LoadNode(Renderer, str);
			pHead = tmp;
			pHead->AnimationNodeAppear(Renderer, Erase, ScreenWidth/2, ScreenHeight/2, NodeSize);
		}
		n++;
		return true;
	}
	if (p != NULL) MoveNext = AnimationController(Pause, Renderer, Erase);
	if (!MoveNext) return false;
	if (p == pHead){
		AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
		p->AnimationCircle(Renderer, Erase, pPrev);
		MoveNext = AnimationController(Pause, Renderer, Erase);
		if (!MoveNext) return false;
	}
	if (p == NULL){
		Node *tmp = NULL;
		if (vt == 0){
			tmp = new Node;
			tmp->LoadNode(Renderer, str);
			pHead = tmp;
			pHead->AnimationNodeAppear(Renderer, Erase, ScreenWidth/2, ScreenHeight/2, NodeSize);
			n++;
			return true;
		}
		int step = 0;
		while (true){
			if (MoveNext){
				if (step == 0){
					tmp = new Node;
					tmp->LoadNode(Renderer, str);
					tmp->AnimationNodeAppear(Renderer, Erase, pPrev->GetX() + 1.0*pPrev->GetW()/2  + NodeSize*2, pPrev->GetY() + 1.0*pPrev->GetW()/2, NodeSize);
				}
				else{
					pPrev->AnimationConnect(Renderer, Erase, tmp);
					n++;
					SetPosList(Renderer, Erase, pHead->GetX(), pHead->GetY(), NULL, NULL);
					return true;
				}
				step++;
			}
			else{
				if (step == 0){
					if (tmp != NULL){
						tmp->Close();
						delete tmp;
					}
					return false;
				}
				else{
					tmp->AnimationNodeDisappear(Renderer, Erase);
					tmp = NULL;
				}
				step--;
			}
			MoveNext = AnimationController(Pause, Renderer, Erase);
		}
	}
	else{
		if (vt == pos){
			//MoveNext = AnimationController(Pause, Renderer, Erase);
			//if (!MoveNext) return false;
			Node *tmp = NULL;
			int step = 0;
			if (pPrev == NULL){
				while (true){
					if (MoveNext){
						if (step == 0){
							tmp = new Node;
							tmp->LoadNode(Renderer, str);
							int x = p->GetX(), y = p->GetY();
							AnimationMoveList(Renderer, Erase, x + 2*NodeSize, y, pPrev, NULL);
							tmp->AnimationNodeAppear(Renderer, Erase, x + NodeSize/2, y + NodeSize/2, NodeSize);
						}
						else{
							tmp->AnimationConnect(Renderer, Erase, p);
							pHead = tmp;
							n++;
							SetPosList(Renderer, Erase, pHead->GetX(), pHead->GetY(), NULL, NULL);
							return true;
						}
						step++;
					}
					else{
						if (step == 0){
							if (tmp != NULL){
								tmp->Close();
								delete tmp;
							}
							p->AnimationCircle(Renderer, Erase, pPrev);
							MoveNext = AnimationController(Pause, Renderer, Erase);
							if (MoveNext) continue;
							else return false;
						}
						else{
							int x = tmp->GetX(), y = tmp->GetY();
							tmp->AnimationNodeDisappear(Renderer, Erase);
							tmp = NULL;
							AnimationMoveList(Renderer, Erase, x, y, pPrev, NULL);
						}
						step--;
					}
					MoveNext = AnimationController(Pause, Renderer, Erase);
				}
			}
			else{
				while (true){
					if (MoveNext){
						if (step == 0){
							tmp = new Node;
							tmp->LoadNode(Renderer, str);
							int x = p->GetX(), y = p->GetY();
							AnimationMoveList(Renderer, Erase, x + 2*NodeSize, y, pPrev, NULL);
							tmp->AnimationNodeAppear(Renderer, Erase, x + NodeSize/2, y + 200, NodeSize);
						}
						else
						if (step == 1){
							tmp->AnimationConnect(Renderer, Erase, p);
						}
						else
						if (step == 2){
							pPrev->AnimationDisconnect(Renderer, Erase);
						}
						else
						if (step == 3){
							pPrev->AnimationConnect(Renderer, Erase, tmp);
							tmp->AnimationNodeMove(Renderer, Erase, pPrev->GetX() + NodeSize*2, pPrev->GetY(), pPrev);
							n++;
							SetPosList(Renderer, Erase, pHead->GetX(), pHead->GetY(), NULL, NULL);
							return true;
						}
						step++;
					}
					else{
						if (step == 0){
							if (tmp != NULL){
								tmp->Close();
								delete tmp;
							}
							p->AnimationCircle(Renderer, Erase, pPrev);
							MoveNext = AnimationController(Pause, Renderer, Erase);
							if (MoveNext) continue;
							else return false;
						}
						else
						if (step == 1){
							tmp->AnimationNodeDisappear(Renderer, Erase);
							AnimationMoveList(Renderer, Erase, pPrev->GetX() + 200, pPrev->GetY(), pPrev, NULL);
						}
						else
						if (step == 2){
							tmp->AnimationDisconnect(Renderer, Erase);
						}
						else
						if (step == 3){
							pPrev->AnimationConnect(Renderer, Erase, p);
						}
						step--;
					}
					MoveNext = AnimationController(Pause, Renderer, Erase);
				}
			}
		}
		else{
			while (true){
				if (AnimationInsert2(Renderer, Erase, str, vt + 1, pos, Pause, p->GetpNext(), p)) return true;
				AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
				p->AnimationCircle(Renderer, Erase, pPrev);
				MoveNext = AnimationController(Pause, Renderer, Erase);
				if (!MoveNext) return false;
			}
		}
	}
}
/*void LinkedList::AnimationInsert(SDL_Renderer *(&Renderer), SDL_Texture *Erase, string str, int pos){
	if (pos != 0 && pos >= n) return;
	n++;
	Node *p = pHead, *pPrev = NULL, *tmp = NULL;
	tmp = new Node;
	tmp->LoadNode(Renderer, str);
	bool Pause = true;
	SDL_Event e;
	if (pHead == NULL){
		AnimationController(Pause, Renderer, Erase);
		NodeSize = DEFAULT_NODE_SIZE;
		tmp->AnimationNodeAppear(Renderer, Erase, ScreenWidth/2, ScreenHeight/2, NodeSize);
		pHead = tmp;
		return;
	}
	if (pos == -1){
		while (p != NULL){
			AnimationController(Pause, Renderer, Erase);
			AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
			p->AnimationCircle(Renderer, Erase, pPrev);
			pPrev = p;
			p = p->GetpNext();
		}
		AnimationController(Pause, Renderer, Erase);
		tmp->AnimationNodeAppear(Renderer, Erase, pPrev->GetX() + 1.0*pPrev->GetW()/2  + NodeSize*2, pPrev->GetY() + 1.0*pPrev->GetW()/2, NodeSize);
		AnimationController(Pause, Renderer, Erase);
		if (pPrev != NULL) pPrev->AnimationConnect(Renderer, Erase, tmp);
	}
	else{
		int dem = 0;
		while (p != NULL){
			AnimationController(Pause, Renderer, Erase);
			AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
			p->AnimationCircle(Renderer, Erase, pPrev);
			if (dem == pos){
				AnimationController(Pause, Renderer, Erase);
				int x = p->GetX(), y = p->GetY();
				AnimationMoveList(Renderer, Erase, p->GetX() + 2*NodeSize, p->GetY(), pPrev, NULL);
				if (pPrev != NULL) tmp->AnimationNodeAppear(Renderer, Erase, x + NodeSize/2, y + 200, NodeSize);
				else tmp->AnimationNodeAppear(Renderer, Erase, x + NodeSize/2, y + NodeSize/2, NodeSize);
				AnimationController(Pause, Renderer, Erase);
				tmp->AnimationConnect(Renderer, Erase, p);
				//cout<<tmp->GetX()<<" "<<tmp->GetY()<<" "<<p->GetX()<<" "<<p->GetY()<<endl;
				if (pPrev != NULL){ 
					AnimationController(Pause, Renderer, Erase);
					pPrev->AnimationDisconnect(Renderer, Erase);
				}
				if (pPrev != NULL){
					AnimationController(Pause, Renderer, Erase);
					pPrev->AnimationConnect(Renderer, Erase, tmp);
					//cout<<pPrev->GetX()<<" "<<pPrev->GetY()<<" "<<tmp->GetX()<<" "<<tmp->GetY()<<endl;
				}
				if (pPrev != NULL) tmp->AnimationNodeMove(Renderer, Erase, x, y, pPrev);
				break;
			}
			pPrev = p;
			p = p->GetpNext();
			dem++;
		}
		if (dem == 0) pHead = tmp;
	}
	if (pHead != NULL){
		SetPosList(Renderer, Erase, pHead->GetX(), pHead->GetY(), NULL, NULL);
		SDL_RenderPresent(Renderer);
	}
}*/
bool LinkedList::AnimationRemove2(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int vt, int pos, bool Pause, Node *p, Node *pPrev){
	if (n == 0 || pos >= n) return true;
	if (p != NULL && p != pHead){
		AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
		p->AnimationCircle(Renderer, Erase, pPrev);
	}
	bool MoveNext = true;
	if (p != NULL) MoveNext = AnimationController(Pause, Renderer, Erase);
	if (!MoveNext) return false;
	if (p == pHead){
		AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
		p->AnimationCircle(Renderer, Erase, pPrev);
		MoveNext = AnimationController(Pause, Renderer, Erase);
		if (!MoveNext) return false;
	}
	if (p->GetpNext() == NULL){
		if (vt == 0){
			pHead->AnimationNodeDisappear(Renderer, Erase);
			pHead = NULL;
			n--;
			return true;
		}
		int step = 0;
		while (true){
			if (MoveNext){
				if (step == 0) pPrev->AnimationDisconnect(Renderer, Erase);
				else{
					p->AnimationNodeDisappear(Renderer, Erase);
					AnimationMoveList(Renderer, Erase, pHead->GetX() + 200, pHead->GetY(), NULL, NULL);
					n--;
					SetPosList(Renderer, Erase, pHead->GetX(), pHead->GetY(), NULL, NULL);
					return true;
				}
				step++;
			}
			else{
				if (step == 0){
					p->AnimationCircle(Renderer, Erase, pPrev);
					MoveNext = AnimationController(Pause, Renderer, Erase);
					if (MoveNext) continue;
					return false;
				}
				else pPrev->AnimationConnect(Renderer, Erase, p);
				step--;
			}
			MoveNext = AnimationController(Pause, Renderer, Erase);
		}
	}
	else{
		if (vt == pos){
			//MoveNext = AnimationController(Pause, Renderer, Erase);
			//if (!MoveNext) return false;
			Node *tmp = p->GetpNext();
			int step = 0;
			if (pPrev == NULL){
				while (true){
					if (MoveNext){
						if (step == 0){
							p->AnimationDisconnect(Renderer, Erase);
						}
						else{
							int x = p->GetX(), y = p->GetY();
							pHead = tmp;
							p->AnimationNodeDisappear(Renderer, Erase);
							if (pHead != NULL) AnimationMoveList(Renderer, Erase, x, y, NULL, NULL);
							n--;
							SetPosList(Renderer, Erase, pHead->GetX(), pHead->GetY(), NULL, NULL);
							return true;
						}
						step++;
					}
					else{
						if (step == 0){
							p->AnimationCircle(Renderer, Erase, pPrev);
							MoveNext = AnimationController(Pause, Renderer, Erase);
							if (MoveNext) continue;
							else return false;
						}
						else{
							p->AnimationConnect(Renderer, Erase, tmp);
						}
						step--;
					}
					MoveNext = AnimationController(Pause, Renderer, Erase);
				}
			}
			else{
				while (true){
					if (MoveNext){
						if (step == 0){
							int x = p->GetX(), y = p->GetY();
							p->AnimationNodeMove(Renderer, Erase, x, y + 200 - NodeSize/2, pPrev);
							pPrev->AnimationDisconnect(Renderer, Erase);
						}
						else
						if (step == 1){
							pPrev->AnimationConnect(Renderer, Erase, tmp);
						}
						else
						if (step == 2){
							p->AnimationDisconnect(Renderer, Erase);
						}
						else
						if (step == 3){
							p->AnimationNodeDisappear(Renderer, Erase);
							AnimationMoveList(Renderer, Erase, pPrev->GetX() + 200, pPrev->GetY(), pPrev, NULL);
							n--;
							SetPosList(Renderer, Erase, pHead->GetX(), pHead->GetY(), NULL, NULL);
							return true;
						}
						step++;
					}
					else{
						if (step == 0){
							p->AnimationCircle(Renderer, Erase, pPrev);
							MoveNext = AnimationController(Pause, Renderer, Erase);
							if (MoveNext) continue;
							else return false;
						}
						else
						if (step == 1){
							pPrev->AnimationConnect(Renderer, Erase, p);
							p->AnimationNodeMove(Renderer, Erase, pPrev->GetX() + 200, pPrev->GetY(), pPrev);
						}
						else
						if (step == 2){
							pPrev->AnimationDisconnect(Renderer, Erase);
						}
						else
						if (step == 3){
							p->AnimationConnect(Renderer, Erase, tmp);
						}
						step--;
					}
					MoveNext = AnimationController(Pause, Renderer, Erase);
				}
			}
		}
		else{
			while (true){
				if (AnimationRemove2(Renderer, Erase, vt + 1, pos, Pause, p->GetpNext(), p)) return true;
				AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
				p->AnimationCircle(Renderer, Erase, pPrev);
				MoveNext = AnimationController(Pause, Renderer, Erase);
				if (!MoveNext) return false;
			}
		}
	}
}
/*void LinkedList::AnimationRemove(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int pos){
	if (pos >= n) return;
	if (pHead == NULL) return;
	n--;
	Node *p = pHead, *pPrev = NULL, *pNext = NULL;
	double x, y;
	bool Pause = true; 
	SDL_Event e;
	if (pos == -1 || pos == n){
		while (p != NULL){
			AnimationController(Pause, Renderer, Erase);
			AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
			p->AnimationCircle(Renderer, Erase, pPrev);
			if (p->GetpNext() == NULL){
				if (pPrev != NULL){
					AnimationController(Pause, Renderer, Erase);
					pPrev->AnimationDisconnect(Renderer, Erase);
				}
				if (p == pHead) pHead = NULL;
				AnimationController(Pause, Renderer, Erase);
				p->AnimationNodeDisappear(Renderer, Erase);
				delete p;
				if (pPrev != NULL) pPrev->SetpNext(NULL);
				if (pHead != NULL) AnimationMoveList(Renderer, Erase, pHead->GetX() + 2*NodeSize, pHead->GetY(), NULL, NULL);
				break;
			}
			pPrev = p;
			p = p->GetpNext();
		}
	}
	else{
		int dem = 0;
		while (p != NULL){
			AnimationController(Pause, Renderer, Erase);
			AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
			p->AnimationCircle(Renderer, Erase, pPrev);
			if (dem == pos){
				int x = p->GetX(), y = p->GetY();
				pNext = p->GetpNext();
				if (pPrev != NULL) p->AnimationNodeMove(Renderer, Erase, x, y + 200 - NodeSize/2, pPrev);
				if (pPrev != NULL){
					AnimationController(Pause, Renderer, Erase);
					pPrev->AnimationDisconnect(Renderer, Erase);
				}
				if (pPrev != NULL && pNext != NULL){
					AnimationController(Pause, Renderer, Erase);
					pPrev->AnimationConnect(Renderer, Erase, pNext);
				}
				if (pNext != NULL){
					AnimationController(Pause, Renderer, Erase);
					p->AnimationDisconnect(Renderer, Erase);
				}
				AnimationController(Pause, Renderer, Erase);
				p->AnimationNodeDisappear(Renderer, Erase);
				delete p;
				if (dem == 0) pHead = pNext;
				if (pHead != NULL) AnimationMoveList(Renderer, Erase, x, y, pPrev, NULL);
				break;
			}
			pPrev = p;
			p = p->GetpNext();
			dem++;
		}
	}
	if (pHead != NULL){
		SetPosList(Renderer, Erase, pHead->GetX(), pHead->GetY(), NULL, NULL);
		SDL_RenderPresent(Renderer);
	}
}*/
bool LinkedList::AnimationFind(SDL_Renderer *(&Renderer), SDL_Texture *Erase, string DataIn, int sign, bool Pause, Node *p, Node *pPrev, string &Ret){
	if (p == NULL){
		Ret = "Not Found!";
		return true;
	}
	if (p != pHead){
		AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
		p->AnimationCircle(Renderer, Erase, pPrev);
		if (Compare(p->GetData(), DataIn) == sign){
			Ret = p->GetData();
			return true;
		}
	}
	else{
		bool MoveNext = AnimationController(Pause, Renderer, Erase);
		if (MoveNext){
			AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
			p->AnimationCircle(Renderer, Erase, pPrev);
			if (Compare(p->GetData(), DataIn) == sign){
				Ret = p->GetData();
				return true;
			}
		}
		else return false;
	}
	while (true){
		bool MoveNext = AnimationController(Pause, Renderer, Erase);
		if (MoveNext){		
			if (AnimationFind(Renderer, Erase, DataIn, sign, Pause, p->GetpNext(), p, Ret)) return true;
			AnimationZoomIn(Renderer, Erase, p->GetX() + 1.0*p->GetW()/2, p->GetY() + 1.0*p->GetW()/2);
			p->AnimationCircle(Renderer, Erase, pPrev);
		}
		else return false;
	}
}
bool LinkedList::CheckInList(int x, int y){
	if (pHead == NULL) return false;
	if (x < pHead->GetX() || x > pHead->GetX() + NodeSize*(2*n-1)) return false;
	if (y < pHead->GetY() || y > pHead->GetY() + pHead->GetW()) return false;
	return true;
}
void LinkedList::AnimationZoomIn(SDL_Renderer *(&Renderer), SDL_Texture *Erase, int x, int y){
	double dist = x - pHead->GetX();
	AnimationMoveList(Renderer, Erase, ScreenWidth/2 - dist, ScreenHeight/2 - 1.0*NodeSize/2, NULL, NULL);
	double s = DEFAULT_NODE_SIZE - NodeSize;
	if (abs(s) < 0.3) return;
	//cout<<x<<" "<<y<<" "<<X<<" "<<Y<<endl;
	double s0 = NodeSize;
	double st = 0;
	double v0 = 100;
	double vt = v0;
	double a = (-v0*v0) / (2.0*s);
	//cout<<sina<<" "<<cosa<<endl;
	//cout<<a<<endl;
	if (s < 0) v0 = -v0;
	st = s0;
	vt = v0;
	clock_t t = clock();
	if (s < 0){
		while (st > DEFAULT_NODE_SIZE){
			//cout<<vt<<endl;
			double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
			st = s0 + v0*time;// + a*time*time / 2;
			//cout<<st<<endl;
			//vt = v0 + a*time;
			//cout<<st<<endl;
			Resize(Renderer, Erase, st, NULL);
			SetPosList(Renderer, Erase, 1.0*ScreenWidth/2 - 1.0*NodeSize/s0*dist, ScreenHeight/2 - NodeSize/2, NULL, NULL);
			SDL_RenderPresent(Renderer);
		}
	}
	else{
		while (st < DEFAULT_NODE_SIZE){
			double time = 1.0*(clock() - t) / CLOCKS_PER_SEC;
			st = s0 + v0*time; //+ a*time*time / 2;
			//vt = v0 + a*time;
			//cout<<st<<endl;
			Resize(Renderer, Erase, st, NULL);
			SetPosList(Renderer, Erase, 1.0*ScreenWidth/2 - 1.0*NodeSize/s0*dist, ScreenHeight/2 - NodeSize/2, NULL, NULL);
			SDL_RenderPresent(Renderer);
		}
	}
}
void LinkedList::Close(){
	n = 0;
	NodeSize = 0;
	Node *p = pHead, *tmp = NULL;
	while (p != NULL){
		tmp = p;
		tmp->Close();
		p = p->GetpNext();
	}
}