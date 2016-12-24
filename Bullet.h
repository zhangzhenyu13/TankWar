#pragma once
#include"GraphicUnit.h"
#include"TankData.h"
class Bullet :public GraphicUnit{
	const char Step;
	HDC* pDC, *pDCObj;
	HWND* pWnd;
	HINSTANCE* pInst;
	int x, y;
	Direction direct;
	const int style;
	const char group;
	std::string bulletname;
	TankData* owner;
public:
	bool hitTank = false;
	std::string getName() { return bulletname; }
	void readData(GameData* bullet) {
		
	}
	Bullet(TankData* owner1,POINT p, Direction d,char team=1, int style1 = 1) 
		:owner(owner1),group(team),Step(4),x(p.x), y(p.y), direct(d), style(style1) {}
	~Bullet(){
		if(owner->isAlive()&&hitTank)
		   owner->LevelUp();
	}

	void setDC(HDC*hdc1,HDC*hdc2) {
		pDC = hdc1;
		pDCObj = hdc2;
	}
	void setHandle(HWND* hWnd, HINSTANCE* hInst) {
		pInst = hInst;
		pWnd = hWnd;
	}
	char getTeam(){return group;}
	int power() { return style; }
	int Xpos() { return x; }
	int Ypos() { return y; }
	void Move() {

		switch (direct)
		{
		case UP:
			y -= Step;
			break;
		case DOWN:
			y += Step;
			break;
		case LEFT:
			x -= Step;
			break;
		case RIGHT:
			x += Step;
			break;
		case KEEP:

			break;
		default:
			break;

		}
	}
	
	void draw();
};