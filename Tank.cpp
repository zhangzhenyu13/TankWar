#include"Tank.h"
#include<TChar.h>
using namespace Gdiplus;
using namespace std;
void Tank::draw() {
	string s;
	LPWSTR up = L"tank\\tank_up.png", down = L"tank\\tank_down.png",
		left = L"tank\\tank_left.png", right = L"tank\\tank_right.png",pic=up;
	
	switch (_tank->gesDirect())
	{
	case UP:
		pic = up;
		break;
	case DOWN:
		pic = down;
		break;
	case LEFT:
		pic = left;
		break;
	case RIGHT:
		pic = right;
		break;
	default:
		break;
	}

	Image tank(pic);
	Graphics g(*pDCObj);

	Rect rect(_tank->Xpos(),_tank->Ypos(),50,50);
	
	g.DrawImage(&tank, rect);

	//release Mem

}