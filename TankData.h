#pragma once
#include"GameData.h"
#include"Direction.h"
#include<windows.h>
class TankData :public GameData {
	TankData* _tank;
	Direction gesdirect,movedirect;
	char Step;
	int posx, posy;
	
	char health;
	std::string tankname;
	char group;
	char level;
public:
	RECT viewArea(){
		RECT rect={posx-100,posy-100,posx+100,posy+100};
		return rect;
	}
	TankData():Step(5) {
		level=1;
		group=1;
		health=1;
		gesdirect = UP;
		movedirect = KEEP;
		posx = 500;
		posy = 500;		
	}
	TankData(POINT p):Step(5){
		level=1;
		group=1;
		health=1;
		gesdirect = UP;
		movedirect = KEEP;
		posx = p.x;
		posy = p.y;
	}
	void setTeam(char gt){
		group=gt;
	}
	char getTeam(){return group;}
	void HitByBullet(char damage=1){
		health-=damage;
		
	}
	void LevelUp(){
		if(level>=5)
			return ;
		level++;
		health++;
		if((1+level)%3==0)
			Step++;
	}
	bool isAlive(){
		if(health<=0)
			return false;
		else
			return true;
	}
	POINT fire() {
	POINT p;
	switch(gesdirect){
	case UP:
		p.x=posx + 25;
		p.y=posy;

		break;
	case DOWN:
		p.x=posx+25;
		p.y=posy+50;
	
		break;
	case LEFT:
		p.x= posx;
		p.y=posy + 25;
	
		break;
	case RIGHT:
		p.x=posx + 50;
		p.y=posy + 25 ;
		
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
	
		switch (movedirect)
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
		RECT rct={posx,posy,posx+50,posy+50};
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