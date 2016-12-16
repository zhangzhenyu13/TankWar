#pragma once
#include"GraphicLayout.h"
#include"MapData.h"
#include"TankData.h"
#include"Control.h"
#include"TankData.h"
#include"MapData.h"
#include"Bullet.h"
#include"Robot.h"
#include<vector>
enum GameResult
{
	WINNER,LOSER,COMEON
};
class GameAI {
private:
	char stage;
	std::vector<TankData*> tank;
	std::vector<MapData*> map;
	std::vector<Control*> control;
	std::vector<Robot*> player;
	std::vector<Bullet*> fire;
	GraphicLayout* glayout;
public :
	GameAI() { stage = 1; }
	void setGraph(GraphicLayout* g) {
		glayout = g;
	}
	void addControl(Control* C) {
		control.push_back(C);
	}
	void addPlayer(Robot* rb){
		player.push_back(rb);
	}
	virtual GameResult Handle(bool timer=false);
	void addMap(MapData* gm) {
		map.push_back(gm);
	}
	void addTank(TankData* gt) {
		tank.push_back(gt);
	}
	void addBullet(Bullet *gb) {
		fire.push_back(gb);
	}

	//
	void BeginGame();
	void EndGame();
	~GameAI(){
		for(int i=tank.size()-1;i>=0;i--){
			delete tank[i];
		}
		for(int i=map.size()-1;i>=0;i--){
			delete map[i];
		}
		for(int i=control.size()-1;i>=0;i--){
			delete control[i];
		}
		for(int i=player.size()-1;i>=0;i--){
			delete player[i];
		}
	}
	POINT properPos(RECT Area){
		POINT p;
		RECT rect;
		bool flag;
		do {
			flag = false;
			p.x = rand()%(Area.right-Area.left)+Area.left;
			p.y = rand()%(Area.bottom-Area.top)+Area.top;
			rect.bottom = p.y + 50;
			rect.left = p.x;
			rect.right = p.x + 50;
			rect.top = p.y;
			RECT inrect;
			for(int j = 0; j < tank.size(); j++) {
				RECT trect = {tank[j]->Xpos(), tank[j]->Ypos(), tank[j]->Xpos()+50, tank[j]->Ypos()+50};
				if (tank[j]->isAlive()&&IntersectRect(&inrect,&trect,&rect))
					flag = true;
			}
		} while(map[stage-1]->interset(rect) || flag);
		return p;
	}
protected:
	int countLevel(){
		StatusWnd* swnd=glayout->Status();
		swnd->clear();
		for(int i=0;i<tank.size();i++){
			if(tank[i]->isAlive())
			swnd->add(tank[i]->getTeam(),tank[i]->getLevel());
		}
		
		
		if(swnd->Sum(1)==0)
			return 1;
		else if(swnd->Sum(2)==0)
			return 2;
		else
			return 0;

	}
	void fireMove();
	void tankMove();

};
