#include"GameAI.h"
#include<stack>
using namespace std;
#define Stack stack<TankData*>

GameResult GameAI::Handle(bool timer) {
	//robots input imitate
	for(int i=0;i<player.size();i++){
		if(tank[i]->isAlive())
			control[i]->Input(player[i]->getNextAct(2));
		else
			control[i]->Keep();
	}
	//operation response

	tankMove();
	
	fireMove();
	//
	if(tank.back()->isAlive()==false)
		return LOSER;
	else 
		return WINNER;
}
//
void GameAI::tankMove() {
	RECT rt;
	MapData* map1 = map[stage-1];//currrent stage

//actions
	for (int i = 0;i<tank.size(); i++) {
		Control* C = control[i];
		TankData* tank1 = tank[i];
		if(tank1->isAlive()==false)
			continue;
		tank1->tankPos((C->Move()));
		
		if (C->Fire() > 0) {
			Bullet* b = new Bullet(tank1->fire(), tank1->gesDirect());
			fire.push_back(b);
			glayout->addGraphicUnit(b);
		    }
		}
//amoung tanks
		Stack S;
		for(int i=0;i<tank.size();i++){
			bool coll=false;
			if(tank[i]->isAlive()==false&&tank[i]->moveDirect()==KEEP)
				continue;
			for(int j=0;j<tank.size();j++)
				if(j!=i&&tank[j]->isAlive()&&IntersectRect(&rt,&tank[i]->getPos(),&tank[j]->getPos())){
					coll=true;
					break;
				}
			if(coll)
				S.push(tank[i]);
		}
		if(tank[tank.size()-1]->isAlive()&&tank[tank.size()-1]->moveDirect()!=KEEP){
			for(int i=0;i<tank.size()-1;i++)
				if(tank[i]->isAlive()&&IntersectRect(&rt,&tank[i]->getPos(),&tank[tank.size()-1]->getPos())){
					S.push(tank[tank.size()-1]);
					break;
				}
		}
		while(S.empty()==false){
			TankData* t=S.top();
			S.pop();
			t->stepback();
		}
//tanks and map
		for(int i=0;i<tank.size();i++){
			if(tank[i]->isAlive()==false)
				continue;
		    int x = tank[i]->Xpos(), y = tank[i]->Ypos();
		    RECT rect = { x,y,x + 50,y + 50 };
			if(map1->interset(rect)){
				
				tank[i]->stepback();
			}
		}
}
//
void GameAI::fireMove() {
	MapData* map1 = map[stage-1];//current stage
	std::vector<Bullet*>::iterator it=fire.begin();
	RECT rt;
	BOOLEAN hitOn;
	for (int i = 0; i < fire.size(); i++) {
		hitOn=FALSE;
		fire[i]->Move();
		RECT bulletrect = { fire[i]->Xpos()- 2, fire[i]->Ypos() - 2, 
			               fire[i]->Xpos() + 2, fire[i]->Ypos() + 2 };
		//map bricks
		for (int j = 0; j < map1->size(); j++) {
			Brick brick = map1->getPos(j);

			if (IntersectRect(&rt, &brick.rect, &bulletrect)) {

				//try to delete the brick
				 map1->deleteBrick(j, fire[i]->power());
				//delete the bullet
				glayout->deleteGraphicUnit(fire[i]);
				it = fire.begin() + i;
				fire.erase(it);
				hitOn=TRUE;
				break;
		    }
		}
		if(hitOn)
			continue;
	//hit other tanks
		for(int j=0;j<tank.size();j++){
			if(tank[j]->isAlive()&&IntersectRect(&rt,&tank[j]->getPos(),&bulletrect)){
				//
				tank[j]->HitByBullet(fire[i]->power());
				
				//
				glayout->deleteGraphicUnit(fire[i]);
				it=fire.begin()+i;
				fire.erase(it);
				hitOn=TRUE;
				break;
			}
		}
		if(hitOn)
			continue;
	//delete bullet out of border
		if(fire[i]->Xpos()<0||fire[i]->Xpos()>1208)
			if(fire[i]->Ypos()<0||fire[i]->Ypos()>720){
				fire.erase(fire.begin()+i);
			}
	}

}

