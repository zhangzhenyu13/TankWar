#pragma once
#include"GameData.h"
#include"Direction.h"
#include"StateMachine.h"
#include<windows.h>
class TankData :public GameData {
	TankData* _tank;
	Direction gesdirect,movedirect;
	char Step;
	int posx, posy;
	bool isfire;
	char health;
	std::string tankname;
	char group;
	char level;
	
public:
	int levelUPcooling;
	bool available;
	const int tankSize = 40;
	bool isPlayer = false;
	RECT viewArea(){
		RECT rect={posx-100,posy-100,posx+100,posy+100};
		return rect;
	}
	TankData(int x, int y, int team, int newlevel) :Step(2) {
		levelUPcooling = 0;
		level = newlevel;
		group = team;
		health = 1;
		gesdirect = UP;
		movedirect = KEEP;
		posx = x;
		posy = y;
		available = false;
	}
	TankData():Step(2) {
		levelUPcooling = 0;
		level=1;
		group=1;
		health=1;
		gesdirect = UP;
		movedirect = KEEP;
		posx = 500;
		posy = 500;	
		available = false;
		
	}
	TankData(POINT p):Step(2){
		levelUPcooling = 0;
		level=1;
		group=1;
		health=1;
		gesdirect = UP;
		movedirect = KEEP;
		posx = p.x;
		posy = p.y;
		available = false;
	}
	void setTeam(char gt){
		group=gt;
	}
	char getTeam(){return group;}
	bool HitByBullet(char damage=1){//is the tank dead?
		if (levelUPcooling > 0)
			return false;
		health-=damage;
		if (isAlive())
			return false;
		else
		{
			return true;
		}
	}
	void acceptAct(TankAct& act){
		movedirect=act.direct;
		isfire=act.fire;
	}
	void LevelUp(){
		static int levelStand=2,count=0;
		if(level>=5)
			return ;
		if(++count>levelStand){
		count=0;
		level++;
		health=level;
		if((1+level)%3==0)
			Step++;
		levelUPcooling = level * 400;
		levelStand = level * 2 - 1;
		}
	}
	bool isAlive(){
		if(health<=0)
			return false;
		else
			return true;
	}
	POINT fire() {
	POINT p;
	if (isfire == false) {
		p = {-1,-1};
		return p;
	}
	switch(gesdirect){
	case UP:
		p.x=posx + tankSize/2;
		p.y=posy;

		break;
	case DOWN:
		p.x=posx+ tankSize / 2;
		p.y=posy+ tankSize;
	
		break;
	case LEFT:
		p.x= posx;
		p.y=posy + tankSize / 2;
	
		break;
	case RIGHT:
		p.x=posx + tankSize;
		p.y=posy + tankSize / 2;
		
		break;
	default://this must be avoid in the func
		p.x=posx;
		p.y=posy;
		break;
	}
	return p;
	}
	std::string getName() {
		return tankname;
	}
	//test code
	void revDirect(){
		switch (movedirect)
		{
		case UP:
			movedirect=DOWN;
			break;
		case DOWN:
			movedirect=UP;
			
			break;
		case LEFT:
			movedirect=RIGHT;
			
			break;
		case RIGHT:
			movedirect=LEFT;
			
			break;
		default:
			break;
		}
	}
	void stepback() {
	
		switch (gesdirect)
		{
		case UP:
			posy += Step;
			break;
		case DOWN:
			posy -= Step;
			
			break;
		case LEFT:
			posx += Step;
			
			break;
		case RIGHT:
			posx -= Step;
			
			break;
		default:
			break;
		}

	}
	void tankPos(Direction d) {
		
		switch (d)
		{
		case UP:
			posy -= Step;
			break;
		case DOWN:
			posy += Step;
			break;
		case LEFT:
			posx -= Step;
			break;
		case RIGHT:
			posx += Step;
			break;
		default:
			break;
		}

		if (d != KEEP)
		   gesdirect=movedirect = d;
		else
			movedirect=d;

	}
	//position 
	void setPos(const POINT& p){
		posx=p.x;
		posy=p.y;
	}
	void setDirect(Direction move,Direction ges){
		movedirect=move;
		gesdirect=ges;
	}
	int Xpos() {
		return posx;
	}
	int Ypos() {
		return posy;
	}
	RECT getPos(){
		RECT rct={posx,posy,posx+ tankSize,posy+ tankSize};
		return rct;
	}
	Direction gesDirect() {
		return gesdirect;
	}
	Direction moveDirect() {
		return movedirect;
	}
	char getLevel(){
		return level;
	}
};