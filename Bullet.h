#pragma once
#include"GraphicUnit.h"

class Bullet :public GraphicUnit{
	
	HDC* pDC, *pDCObj;
	HWND* pWnd;
	HINSTANCE* pInst;
	int x, y;
	Direction direct;
	int style;
	std::string bulletname;
public:
	std::string getName() { return bulletname; }
	void readData(GameData* bullet) {
		
	}
	Bullet(POINT p, Direction d, int style1 = 1) :x(p.x), y(p.y), direct(d), style(style1) {}
	void setDC(HDC*hdc1,HDC*hdc2) {
		pDC = hdc1;
		pDCObj = hdc2;
	}
	void setHandle(HWND* hWnd, HINSTANCE* hInst) {
		pInst = hInst;
		pWnd = hWnd;
	}
	int power() { return style*1.5; }
	int Xpos() { return x; }
	int Ypos() { return y; }
	void Move() {
#define Step 6
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
#undef Step
		}
	}
	
	void draw();
};