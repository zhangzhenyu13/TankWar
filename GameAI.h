#pragma once
#include"GraphicLayout.h"
#include"MapData.h"
#include"TankData.h"
#include"Control.h"
#include"TankData.h"
#include"MapData.h"
#include"Bullet.h"
#include<vector>
class GameAI {
private:
	char stage;
	std::vector<TankData*> tank;
	std::vector<MapData*> map;
	std::vector<Control*> control;
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
	virtual void Handle(bool timer=false);
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
protected:
	void fireMove();
	void tankMove();
};