#include"Tank.h"
#include<TChar.h>
using namespace Gdiplus;
using namespace std;
void Tank::draw() {
	if (_tank->isAlive() == false || _tank->available == false)
		return;
	//paint
	int rba1 = 0, rba2 = 0;
	if (_tank->getTeam() == 1)
		rba1 = _tank->levelUPcooling/10;
	else
		rba2 = _tank->levelUPcooling/10;
	HBRUSH bkbrush = CreateSolidBrush(RGB(10 + rba1, 10 + rba2, 30));
	HPEN bkpen = CreatePen(PS_DASHDOT,4,RGB(200,200,200));
	RECT rt = _tank->getPos();
	SelectObject(*pDCObj, bkbrush);
	
	if (_tank->levelUPcooling > 0) {
	   Ellipse(*pDCObj, rt.left - 10, rt.top - 10, rt.right + 10, rt.bottom + 10);
	   _tank->levelUPcooling-=10;
    }
	if (_tank->isPlayer) {
		SelectObject(*pDCObj, bkpen);
		Ellipse(*pDCObj, rt.left - 5, rt.top - 5, rt.right + 5, rt.bottom + 5);
	}
	//GdiplusImage
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
	Rect rect(_tank->Xpos(),_tank->Ypos(),_tank->tankSize,_tank->tankSize);
	
	g.DrawImage(&tank, rect);

	//release Mem
	DeleteObject(bkbrush);
	DeleteObject(bkpen);
}