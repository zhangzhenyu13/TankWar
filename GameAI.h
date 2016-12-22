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
#include<fstream>
using namespace std;
const int onShow = 5;
enum GameResult
{
	WINNER,LOSER,COMEON
};
class GameAI {
private:
	bool playerdied;
	int playerRank;
	char level;
	std::vector<TankData*> tank;
	MapData* map;
	std::vector<Control*> control;
	std::vector<Robot*> player;
	std::vector<Bullet*> fire;
	GraphicLayout* glayout;
	RECT myArea, pcArea;
public :
	GameAI() {level = 1; playerdied = false; playerRank = 1; }
	Control* getPlayerInput() {
		return control[playerRank];
	}
	void setGraph(GraphicLayout* g) {
		glayout = g;
	}
	void setArea(RECT rect1,RECT rect2) {
		myArea = rect1;
		pcArea = rect2;
	}
	void setDifficulty(int r) {
		level = r;
	}
	void addControl(Control* C) {
		control.push_back(C);
	}
	void addPlayer(Robot* rb){
		player.push_back(rb);
	}
	virtual GameResult Handle(bool timer=false);
	void addMap(MapData* gm) {
		map=gm;
	}
	void addTank(TankData* gt) {
		tank.push_back(gt);
	}
	void addBullet(Bullet *gb) {
		fire.push_back(gb);
	}

	//
	void BeginGame();
	~GameAI(){
		for(int i=tank.size()-1;i>=0;i--){
			delete tank[i];
		}
			delete map;
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
		} while(map->interset(rect) || flag);
		return p;
	}
	void SaveData(wstring );
protected:
	int countLevel(){
		
		StatusWnd* swnd=glayout->Status();
		swnd->clear();
		for(int i=0;i<tank.size();i++){
			if(tank[i]->isAlive()&&tank[i]->available)
			swnd->add(tank[i]->getTeam(),tank[i]->getLevel());
		}
		//count and add
		int humanop = 0, myAlive = swnd->Sum(2), pcAlive = swnd->Sum(1);
		for (int i = 0; i < tank.size(); i++) {
			if (tank[i]->isAlive() == false||tank[i]->available)
				continue;
			if (tank[i]->getTeam() == 1&&pcAlive<onShow) {
				tank[i]->available = true;
				pcAlive++;
			}
			if(tank[i]->getTeam()==2&&myAlive<onShow){
				tank[i]->available = true;
				myAlive++;
				humanop = i;
			}
		}
		if (playerdied&&humanop > 0) {
			playerRank = humanop;
			player[humanop]->enabled = false;
			playerdied = false;
		}
		
		if(pcAlive==0)
			return 1;//pc
		else if(myAlive==0)
			return 2;//my
		else
			return 0;

	}
	void fireMove();
	void tankMove();

};
