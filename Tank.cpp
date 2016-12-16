#include"Tank.h"
#include<TChar.h>
using namespace Gdiplus;
using namespace std;
void Tank::draw() {
	if(_tank->isAlive()==false)
		return ;
	//paint
	wstring tankges;
	if(_tank->getTeam()==1)
		tankges=L"tank\\enemy\\";
	else
		tankges=L"tank\\player\\";
	
	switch (_tank->gesDirect())
	{
	case UP:
		tankges+=L"up";
		break;
	case DOWN:
		tankges+=L"down";
		
		break;
	case LEFT:
		tankges+=L"left";
		
		break;
	case RIGHT:
		tankges+=L"right";
		
		break;
	default:
		break;
	}
	wstring level[5]={L"1",L"2",L"3",L"4",L"5"};
	tankges+=level[_tank->getLevel()-1];
	tankges+=L".png";
	//
	LPCWSTR pic=tankges.c_str();
	Gdiplus::Image tank(pic);
	Graphics g(*pDCObj);
	Rect rect(_tank->Xpos(),_tank->Ypos(),50,50);
	
	g.DrawImage(&tank, rect);

	//release Mem

}