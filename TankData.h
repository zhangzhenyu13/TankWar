#pragma once
#include"GameData.h"
#include"Direction.h"
#include<windows.h>
class TankData :public GameData {
	TankData* _tank;
	Direction gesdirect,movedirect;
	
	int posx, posy;
	std::string tankname;
public:
	TankData() {
		gesdirect = UP;
		movedirect = KEEP;
		posx = 500;
		posy = 500;
		
	}
	POINT fire() {
	switch(gesdirect){
	case UP:
		return { posx + 25,posy };
		break;
	case DOWN:
		return{posx+25,posy+50};
		break;
	case LEFT:
		return{ posx,posy + 25 };
		break;
	case RIGHT:
		return{ posx + 50,posy + 25 };
		break;
	default://this must be avoid in the func
		return {posx,posy};
		break;
	}
	}
	std::string getName() {
		return tankname;
	}
	//test code
	
	void stepback() {
#define Step -5		
		switch (movedirect)
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
#undef Step 
	}
	void tankPos(Direction d) {
#define Step 5		
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
#undef Step 
		if (d != KEEP)
			gesdirect=movedirect = d;

	}
	//position 
	int Xpos() {
		return posx;
	}
	int Ypos() {
		return posy;
	}
	Direction gesDirect() {
		return gesdirect;
	}
	Direction moveDirect() {
		return movedirect;
	}
};