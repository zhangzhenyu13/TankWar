#include"GameAI.h"
#include"TankFactory.h"
#include"tank.h"
#include"Map.h"
#include"StatusWnd.h"
#include<stack>
#include<string>
using namespace std;
#define Stack stack<TankData*>



void GameAI::BeginGame(){
	glayout->showStartUP = false;
		for(int i=0;i<player.size();i++){
			player[i]->ShareData(map,&tank);
		}
		player[playerRank]->enabled = false;
		//int tanks on screen
		for (int i = 0,j1=0,j2=0;i < tank.size(); i++) {
			if (tank[i]->isAlive() == false)
				continue;
			if (tank[i]->getTeam() == 1 && j1<onShow) {
				tank[i]->available = true;
				j1++;
			}
			else if(tank[i]->getTeam()==2&&j2<onShow){
				tank[i]->available = true;
				j2++;
				
			}
			else;
		}
		
}
GameResult GameAI::Handle(bool timer) {
	//robots input imitate
	for (int i = 0; i<tank.size(); i++) {
		if (tank[i]->isAlive() && tank[i]->available) {
			if (i != playerRank)
				control[i]->Input(player[i]->getNextAct(level));
		}
		else
			control[i]->Keep();
	}
	//operation response

	tankMove();
	
	fireMove();
	//
	switch (countLevel())
	{
	case 2:
		return LOSER;
		break;
	case 1:
		return WINNER;
		break;
	case 0:
		return COMEON;
		break;
	default:
		break;
	}
	
}
//
void GameAI::tankMove() {
	RECT rt;

//actions
	for (int i = 0;i<tank.size(); i++) {
		Control* C = control[i];
		TankData* tank1 = tank[i];
		if(tank1->isAlive()==false||tank1->available==false)
			continue;
		tank1->tankPos((C->Move()));
		
		if (C->Fire() > 0) {
			Bullet* b = new Bullet(tank1,tank1->fire(), tank1->gesDirect(),tank1->getTeam());
			fire.push_back(b);
			glayout->addGraphicUnit(b);
		    }
	/*	for(int j=i+1;j<tank.size();j++)
	        if(tank[i]->isAlive()&&tank[j]->isAlive()&IntersectRect(&rt,&tank[j]->getPos(),&tank[i]->getPos())) {
				int Xdis = abs(tank[i]->Xpos() - tank[j]->Xpos()), Ydis = abs(tank[i]->Ypos() - tank[j]->Ypos());
				if(Xdis > Ydis) {
					if(tank[i]->moveDirect() == RIGHT || tank[i]->moveDirect() == LEFT)
						do {
							tank[i]->stepback();
						} while(IntersectRect(&rt,&tank[j]->getPos(),&tank[i]->getPos()));
					if(tank[j]->moveDirect() == RIGHT || tank[j]->moveDirect() == LEFT)
						do {
							tank[j]->stepback();
						} while(IntersectRect(&rt,&tank[j]->getPos(),&tank[i]->getPos()));
				}
				else if(Xdis < Ydis) {
					if(tank[i]->moveDirect() == UP || tank[i]->moveDirect() == DOWN)
						do {
							tank[i]->stepback();
						} while(IntersectRect(&rt,&tank[j]->getPos(),&tank[i]->getPos()));
					if(tank[j]->moveDirect() == UP || tank[j]->moveDirect() == DOWN)
						do {
							tank[j]->stepback();
						} while(IntersectRect(&rt,&tank[j]->getPos(),&tank[i]->getPos()));
				}
		}*/
	}

//amoung tanks
		Stack S;
		for(int i=0;i<tank.size();i++){
			bool coll=false;
			if(tank[i]->isAlive()==false||
				tank[i]->moveDirect()==KEEP||
				tank[i]->available==false)
				continue;
			for(int j=0;j<tank.size();j++)
				if(j!=i&&tank[j]->isAlive()&&tank[j]->available&&
					IntersectRect(&rt,&tank[i]->getPos(),&tank[j]->getPos())){
					coll=true;
					
					break;
				}
			if(coll)
				S.push(tank[i]);
		}
		
		while(S.empty()==false){
			TankData* t=S.top();
			S.pop();
			t->stepback();
		}
//tanks and map
		for(int i=0;i<tank.size();i++){
			if(tank[i]->isAlive()==false||tank[i]->available==false)
				continue;
		   // int x = tank[i]->Xpos(), y = tank[i]->Ypos();
		    RECT rect = tank[i]->getPos();
			if(map->interset(rect)){
				
				tank[i]->stepback();
			}
		}
}
//
void GameAI::fireMove() {
	//current stage
	std::vector<Bullet*>::iterator it=fire.begin();
	RECT rt;
	BOOLEAN hitOn;
	for (int i = 0; i < fire.size(); i++) {
		hitOn=FALSE;
		fire[i]->Move();
		RECT bulletrect = { fire[i]->Xpos()- 2, fire[i]->Ypos() - 2, 
			               fire[i]->Xpos() + 2, fire[i]->Ypos() + 2 };
		//map bricks
		for (int j = 0; j < map->size(); j++) {
			Brick brick = map->getPos(j);

			if (IntersectRect(&rt, &brick.rect, &bulletrect)) {

				//try to delete the brick
				 map->deleteBrick(j, fire[i]->power());
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
			if(tank[j]->isAlive()&&tank[j]->available&&
				tank[j]->getTeam()!=fire[i]->getTeam()&&
				IntersectRect(&rt,&tank[j]->getPos(),&bulletrect)){
				//
				if(tank[j]->HitByBullet(fire[i]->power()))
					if(j==playerRank)
						playerdied=true;
				
				//
				fire[i]->hitTank = true;
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
		if(fire[i]->Xpos()<0||fire[i]->Xpos()>1200)
			if(fire[i]->Ypos()<0||fire[i]->Ypos()>750){
				fire.erase(fire.begin()+i);
			}
	}

}

void GameAI::SaveData(wstring filename) {
	wfstream file;
	file.open(filename);
	file.seekg(20, ios::beg);
	for (int i = 0; i < tank.size(); i++) {
		if (tank[i]->isAlive()) {
			file << tank[i]->Xpos() << " " << tank[i]->Ypos() << " "
				<< (int)tank[i]->getTeam() << " " << (int)tank[i]->getLevel() << endl;
		}
	}
	file << 11457680 << endl;
	file << map->size() - 4 << endl;
	for (int i = 4; i < map->size(); i++) {
		file << map->getPos(i).rect.left << " " << map->getPos(i).rect.top << " "
			<< (int)map->getPos(i).style << " " << map->getPos(i).health << endl;
	}
	file << (int)level << endl;
}
